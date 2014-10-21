#include "stdafx.h"
#include "Engine.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace concurrency;
using namespace concurrency::precise_math;

#define E (2.7182818284590452353602874713526624977572470937f )

Engine::Engine(vector<vector<float>>** vecLoans, vector<vector<float>>** vecCoeffs)
{
	m_loansVec = *vecLoans;
	m_coeffVec = *vecCoeffs;
	m_nTime = 360;
	m_nLoans = m_loansVec->size();
	m_nVars = VARS::LF_NUMBER_OF_VARS;
	m_nProbNoOfRec = 25;

	//vector<float>* __data;

	m_data = new vector<float>(m_nLoans * m_nTime * m_nVars);

}

Engine::~Engine()
{

}

void Engine::PopulateFirstMonth()
{
	int nRowCounter = 0;
	int nColCounter = 0;


	for (auto row : *m_loansVec)
	{

		for (auto col : row)
		{

			(*m_data)[nRowCounter + nColCounter] = col;

			nColCounter++;

			//std::cout << col << " ";
		}
		//nRowCounter++;

		nRowCounter += (m_nTime * m_nVars);
		nColCounter = 0;

		std::cout << nRowCounter << std::endl;
	}
}

void Engine::RestructureCoeff()
{
	int nRowCounter = 0;
	int nColCounter = 0;


	for (auto row : *m_coeffVec)
	{

		for (auto col : row)
		{

			(*m_flatCoeff)[nRowCounter + nColCounter] = col;

			nColCounter++;

			//std::cout << col << " ";
		}
		//nRowCounter++;

		nRowCounter += ( m_nVars);
		nColCounter = 0;

		std::cout << nRowCounter << std::endl;
	}

}

void Engine::GenerateCashflows()
{
	PopulateFirstMonth();
	GenerateCashflowsStep1();
}

void Engine::GenerateCashflowsStep1() 
{

	vector<float> probVec(m_nProbNoOfRec, 0);

	concurrency::extent<1> extProb(m_nProbNoOfRec);
	concurrency::extent<2> extCoeff(m_nProbNoOfRec, m_nVars);
	concurrency::extent<1> ext(m_nLoans);
	concurrency::extent<3> extD(m_nLoans, m_nTime, m_nVars);

	array_view<float, 3> avD(extD, (*m_data));
	array_view<float> avProb(extProb, probVec);
	array_view<float, 2> avCoeff(extCoeff, (*m_flatCoeff));

	int __time = this->m_nTime;


	int __nProbNoOfRec = m_nProbNoOfRec; 
	int __nLoans = m_nLoans;


	parallel_for_each(ext, [avProb, avCoeff, avD, __time, __nProbNoOfRec, __nLoans](index<1> idx) restrict(amp)
	{
		//i represent a loan
		int i = 0;
		i = idx[0];

		float prevVal = 0.0f;

		//loop over time
		for (int ii = 1; ii <= __time; ii++)
		{
			avD(i, ii, VARS::LF_LoanId) = (float)i;
			//avR(i, ii, VARS::LF_LoanId) = (float)i;

			avD(i, ii, VARS::LF_TimeId) = (float)ii;
			//avR(i, ii, VARS::LF_TimeId) = (float)ii;

			
			//array_view<float, 1> loanTimeRow = avD[i][ii];

			//array<float, 1> arLoanRowTime(avD[i][ii]);


			//CalculateProbability(&loanTimeRow, &avCoeff, &avProb, 0, 0);


			/*float t = 0;
			for (unsigned int j = 0; j < __nProbNoOfRec; j++)
			{
				t = 0;
				for (unsigned int i = 0; i < __nLoans; i++)
				{
					t += avD[i][ii][j] * avCoeff[i][j];
				}

				avProb[j] = 1 - 1 / (1 + pow(E, -t));

			}*/



			avD(i, ii, VARS::LF_AllDeliqHist) = avD(i, 0, VARS::LF_AllDeliqHist) + avD(i, 0, VARS::LF_FutureMBAStat);

			avD(i, ii, VARS::LF_DelqHistNum) = avD(i, 0, VARS::LF_DelqHistNum) + (float)1;

			avD(i, ii, VARS::LF_Ever30) = avD(i, 0, VARS::LF_FutureMBAStat) == 3.0f ? 1.0f : 0.0f;

			avD(i, ii, VARS::LF_Ever60) = avD(i, 0, VARS::LF_FutureMBAStat) == 6.0f ? 1.0f : 0.0f;

			avD(i, ii, VARS::LF_EverF) = avD(i, 0, VARS::LF_FutureMBAStat) == -1.0f ? 1.0f : 0.0f; //-1 == FC


			//going to prev month example
			//prevVal = avD(i, ii - 1, VARS::LF_Ever60);

			//avD(i, ii, VARS::LF_Ever90) = avD(i, ii, VARS::LF_Ever60) * 3.1415 + prevVal;
		}
	});


	parallel_for_each(ext, [avD, __time](index<1> idx) restrict(amp)
	{
		int i = 0;
		i = idx[0];

		float prevVal = 0.0f;

		for (int ii = 0; ii < __time; ii++)
		{
			//going to prev month example
			if (ii>0)
				prevVal = avD(i, ii - 1, VARS::LF_Ever90);

			avD(i, ii, VARS::LF_EverF) = avD(i, ii, VARS::LF_Ever60) * prevVal;
		}
	});


	avD.synchronize();

}



////inline void CalculateProbability(array_view<float>* loan, array_view<float, 2>* coeff, array_view<float>* probVec, int nLoanSize, int nProbNumOfVars) 
inline void CalculateProbability(array<float>& loan, array<float, 2>& coeff, array<float>& probVec, int nLoanSize, int nProbNumOfVars) restrict(amp)
{

	float t = 0;
	for (int j = 0; j < nProbNumOfVars; j++)
	{
		t = 0;
		for (int i = 0; i < nLoanSize; i++)
		{
			t += loan[i] * coeff[j][i];
		}

		probVec[j] = 1 - 1 / (1 + pow( E , - t));

	}
}




////inline void CalculateProbability(array_view<float>* loan, array_view<float, 2>* coeff, array_view<float>* probVec, int nLoanSize, int nProbNumOfVars) 
//void CalculateProbability(vector<float> loan, vector<vector<float>> coeff, vector<float>& probVec, int nLoanSize, int nProbNumOfVars)
//{
//	/*
//	parallel_for_each(probVec->extent, [=](index<1> idx)restrict(amp){
//	
//		float t = 0;
//
//		int row = idx[0];
//
//		for (int i = 0; i < nLoanSize; i++)
//		{
//			t += (*loan)(i) * (*coeff)(row, i);			
//		}
//
//		(*probVec)[row] = 1 - 1 / (1 + pow(E, -t));
//
//	});*/
//
//	float t = 0;
//	for (unsigned int j = 0; j < nProbNumOfVars; j++)
//	{
//		t = 0;
//		for (unsigned int i = 0; i < nLoanSize; i++)
//		{
//			t += loan[i] * coeff[j][i];
//		}
//
//		probVec[j] = 1 - 1 / (1 + pow( E , - t));
//
//	}
//}
//

