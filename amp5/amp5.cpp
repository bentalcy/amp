// amp5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <amp.h>
#include <iostream>
#include <objbase.h>
#include <msxml6.h>
#include "Engine.h"

using namespace std;
using namespace concurrency;


#import <msxml3.dll> //rename_namespace(_T("MSXML"))

using namespace MSXML2;

inline void TESTHR(HRESULT _hr)
{
	if FAILED(_hr)
		throw(_hr);
}

//enum VARS { LF_LoanId=0, LF_TimeId, LF_AllDeliqHist, LF_DelqHistNum, LF_Ever30, LF_Ever60, LF_Ever90, LF_EverF, LF_Ever30P, LF_Ever60P, LF_Ever90P, LF_LastP, LF_Effdate, LF_NextDueDate, LF_NumPmtsBehind, LF_MonthsInLatestForeclosure, LF_MonthsInLatestREO, LF_MonthsInLatestNinety, LF_PPPDate, LF_MonthsToPPP, LF_OrigAmt, LF_IOFlag, LF_RecastDate, LF_MonthsToRecast, LF_OrigLTV, LF_CombLTV, LF_MissingCombLTV, LF_State, LF_Term, LF_AmortTerm, LF_MonthVariable, LF_DocFull, LF_DocLow, LF_DocNo, LF_DocType, LF_Occupancy, LF_OccupancyOwner, LF_OccupancySecond, LF_OccupancyInvestor, LF_OccupancyOther, LF_OccupancyNone, LF_PropType, LF_PropTypeSfr, LF_PropTypeCondo, LF_PropTypeCoop, LF_PropTypeUnts24, LF_PropTypeTwnhse, LF_PropTypePud, LF_PropTypeUnts5, LF_PropTypeManhse, LF_PropTypeOther, LF_PropTypeNoinfo, LF_PurpPurchase, LF_PurpCashrefi, LF_PurpNoncashRefi, LF_PurpOther, LF_Purpose, LF_CurrRate, LF_OrigRate, LF_CloseRate, LF_PmiFlag, LF_PmiLevel, LF_FirstRate, LF_OrigCreditScore, LF_MBAStat0, LF_MBAStat1, LF_MBAStat2, LF_MBAStat3, LF_Dti, LF_SvcCodeOrig, LF_SvcCodeCurrent, LF_OrigCode, LF_BankruptcyFlag, LF_Lien, LF_LossCurrent, LF_LossFinal, LF_OrigDate, LF_LoanAge, LF_SchMnthP, LF_CalcMnthP, LF_Pmt, LF_PrinPmt, LF_RemBal, LF_Prin2PmtRat, LF_Prin2Rat, LF_NumPmtsMade, LF_NumPmtsRemaining, LF_UnempChangeOrig, LF_UnempChange3M, LF_UnempChange6M, LF_UnempChange9M, LF_UnempChange12M, LF_HpaOrigLog, LF_Hpa3MLog, LF_Hpa6MLog, LF_Hpa9MLog, LF_Hpa12MLog, LF_HpaOrig, LF_Hpa3M, LF_Hpa6M, LF_Hpa9M, LF_Hpa12M, LF_OrigValue, LF_CurrValue, LF_Balance, LF_CurrLtv, LF_CurrEquity, LF_CurrCombLtv, LF_Sato30Year, LF_Sato15Year, LF_SatoArm1Year, LF_CurrSpr30Year, LF_CurrSpr15Year, LF_CurrSprArm1Year, LF_Curr2OrigPmtRat, LF_PmtsMade3M, LF_PmtsMade4M, LF_PmtsMade6M, LF_PmtsMade12M, LF_NextMbaStat, LF_Judicial, LF_DeficiencyJudgement, LF_TrusteeSale, LF_CourtSale, LF_SheriffSale, LF_FannieTimeline, LF_RelativeFannieTimelines, LF_Frm30RateChg3M, LF_Frm30FeeChg3M, LF_Frm15RateChg3M, LF_Frm15FeeChg3M, LF_Arm1RateChg3M, LF_Arm1FeeChg3M, LF_Frm30RateChg6M, LF_Frm30FeeChg6M, LF_Frm15RateChg6M, LF_Frm15FeeChg6M, LF_Arm1RateChg6M, LF_Arm1FeeChg6M, LF_Frm30RateChg9M, LF_Frm30FeeChg9M, LF_Frm15RateChg9M, LF_Frm15FeeChg9M, LF_Arm1RateChg9M, LF_Arm1FeeChg9M, LF_Frm30RateChg12M, LF_Frm30FeeChg12M, LF_Frm15RateChg12M, LF_Frm15FeeChg12M, LF_Arm1RateChg12M, LF_Arm1FeeChg12M, LF_NextMbaStatC, LF_NextMbaStat3, LF_NextMbaStat6, LF_NextMbaStat9, LF_NextMbaStatF, LF_NextMbaStatR, LF_NextMbaStatL, LF_NextMbaStat0, LF_ServicerName, LF_StateAK, LF_StateAL, LF_StateAP, LF_StateAR, LF_StateAZ, LF_StateCA, LF_StateCO, LF_StateCT, LF_StateDC, LF_StateDE, LF_StateFL, LF_StateGA, LF_StateGU, LF_StateHI, LF_StateIA, LF_StateID, LF_StateIL, LF_StateIN, LF_StateKS, LF_StateKY, LF_StateLA, LF_StateMA, LF_StateMD, LF_StateME, LF_StateMI, LF_StateMN, LF_StateMO, LF_StateMS, LF_StateMT, LF_StateNC, LF_StateND, LF_StateNE, LF_StateNH, LF_StateNJ, LF_StateNM, LF_StateNV, LF_StateNY, LF_StateOH, LF_StateOK, LF_StateOR, LF_StatePA, LF_StatePR, LF_StateRI, LF_StateSC, LF_StateSD, LF_StateTN, LF_StateTX, LF_StateUT, LF_StateVA, LF_StateVI, LF_StateVT, LF_StateWA, LF_StateWI, LF_StateWV, LF_StateWY, LF_MonthJan, LF_MonthFeb, LF_MonthMar, LF_MonthApr, LF_MonthMay, LF_MonthJun, LF_MonthJul, LF_MonthAug, LF_MonthSep, LF_MonthOct, LF_MonthNov, LF_MonthDec, LF_MbaStat1C, LF_MbaStat13, LF_MbaStat16, LF_MbaStat19, LF_MbaStat1F, LF_MbaStat1R, LF_MbaStat1N, LF_MbaStat2C, LF_MbaStat23, LF_MbaStat26, LF_MbaStat29, LF_MbaStat2F, LF_MbaStat2R, LF_MbaStat2N, LF_MbaStat3C, LF_MbaStat33, LF_MbaStat36, LF_MbaStat39, LF_MbaStat3F, LF_MbaStat3R, LF_MbaStat3N, LF_SvcAccredited, LF_SvcAls, LF_SvcAmericanhome, LF_SvcAmeriquest, LF_SvcAurora, LF_SvcBofa, LF_SvcCentex, LF_SvcChase, LF_SvcCiti, LF_SvcCntrywide, LF_SvcEmc, LF_SvcEquicredit, LF_SvcEquityone, LF_SvcFairbanks, LF_SvcGmac, LF_SvcGreenpo, LF_SvcHls, LF_SvcHomecomings, LF_SvcHomeq, LF_SvcIndymac, LF_SvcJp, LF_SvcLitton, LF_SvcLongbeach, LF_SvcNatcity, LF_SvcNationstar, LF_SvcNewcent, LF_SvcOcwen, LF_SvcOptionOne, LF_SvcOther, LF_SvcSaxon, LF_SvcSelport, LF_SvcSuntrust, LF_SvcTbw, LF_SvcWamu, LF_SvcWells, LF_SvcWilshire, LF_ercept, LF_DataType, LF_McScenNo, LF_ProjLossAmt, LF_LossSeverity, LF_FutureMBAStat , LF_NUMBER_OF_VARS};

void LoadXml(char *szFileName, vector<vector<float>>* data )
{

	try
	{
		//Qualify namespase explicitly to avoid Compiler Error C2872 "ambiguous symbol" during linking.
		//Now Msxml2.dll use the "MSXML2" namespace
		//(see http://support.microsoft.com/default.aspx?scid=kb;en-us;316317):
		MSXML2::IXMLDOMDocumentPtr docPtr;//pointer to DOMDocument object
		MSXML2::IXMLDOMNodeListPtr NodeListPtr;//indexed access. and iteration through the collection of nodes
		MSXML2::IXMLDOMNodePtr DOMNodePtr;//pointer to the node

		MSXML2::IXMLDOMNode *pIDOMNode = NULL;//pointer to element's node
		MSXML2::IXMLDOMNode *pIParentNode = NULL;//pointer to parent node
		MSXML2::IXMLDOMNode *pIAttrNode = NULL;//pointer to attribute node
		MSXML2::IXMLDOMNamedNodeMapPtr DOMNamedNodeMapPtr;//iteration through the collection of attribute nodes
		MSXML2::IXMLDOMNodeList *childList = NULL;//node list containing the child nodes


		//Variable with the name of node to find: 
		BSTR strFindText = L" ";//" " means to output every node

		//Variables to store item's name, parent, text and node type:
		BSTR bstrItemText, /*bstrItemNode,*/ bstrItemParent, bstrNodeType;

		//Variables to store attribute's name,type and text:	 
		BSTR /*bstrAttrName, bstrAttrType,*/ bstrAttrText;

		HRESULT hResult;

		int i = 0;//loop-index variable
		int n = 0;//lines counter


		//Initialize COM Library:
		CoInitialize(NULL);

		//Create an instance of the DOMDocument object:
		docPtr.CreateInstance(__uuidof(DOMDocument30));

		// Load a document:
		_variant_t varXml(szFileName);//XML file to load
		_variant_t varResult((bool)TRUE);//result 

		varResult = docPtr->load(varXml);

		if ((bool)varResult == FALSE)
		{
			printf("*** Error:failed to load XML file. ***\n");
			//MessageBox(0, "Error: failed to load XML file. Check the file name.", \
			//	"Load XML file", MB_OK | MB_ICONWARNING);
			return;
		}

		//Collect all or selected nodes by tag name:
		NodeListPtr = docPtr->getElementsByTagName(strFindText);

		//Output the number of nodes:
		//printf("Number of nodes: %d\n", (NodeListPtr->length));

		//Output root node:
		docPtr->documentElement->get_nodeName(&bstrItemText);
		//%ls formatting is for wchar_t* parameter's type (%s for char* type):
		printf("\nRoot: %ls\n", bstrItemText);


		for (i = 0; i < (NodeListPtr->length); i++)
		{

			if (pIDOMNode) pIDOMNode->Release();
			NodeListPtr->get_item(i, &pIDOMNode);


			if (pIDOMNode)
			{

				

				pIDOMNode->get_nodeTypeString(&bstrNodeType);

				//We process only elements (nodes of "element" type): 
				BSTR temp = L"element";

				if (lstrcmp((LPCTSTR)bstrNodeType, (LPCTSTR)temp) == 0)
				{
					n++;//element node's number
					/*printf("\n\n%d\n", n);//element node's number
					printf("Type: %ls\n", bstrNodeType);

					pIDOMNode->get_nodeName(&bstrItemNode);
					printf("Node: %ls\n", bstrItemNode);

					pIDOMNode->get_text(&bstrItemText);
					printf("Text: %ls\n", bstrItemText);
					*/
					pIDOMNode->get_parentNode(&pIParentNode);
					pIParentNode->get_nodeName(&bstrItemParent);
					
					/*
					printf("Parent: %ls\n", bstrItemParent);


					pIDOMNode->get_childNodes(&childList);
					printf("Child nodes: %d\n", (childList->length));
					*/
					//vector<float> loans(childList->length);

					
					//Get the attributes:
					int j = 0;//loop-index variable
					long length;// number of attributes in the collection

					DOMNamedNodeMapPtr = pIDOMNode->attributes;

					hResult = DOMNamedNodeMapPtr->get_length(&length);

					

					if (SUCCEEDED(hResult))
					{
						vector<float> loan(length);

						//Loop through the number of attributes:
						for (j = 0; j < length; j++)
						{

							

							//get attribute node:							
							DOMNamedNodeMapPtr->get_item(j, &pIAttrNode);

							////pIAttrNode->get_nodeTypeString(&bstrAttrType);//type as string
							////printf("\nAttribute type: %ls\n", bstrAttrType);
							////pIAttrNode->get_nodeType(&bstrAttrType);//enumerated type
							////printf("Attribute type: %d\n", bstrAttrType);
							
							//pIAttrNode->get_nodeName(&bstrAttrName);
							//printf("Attribute name: %ls\n", bstrAttrName);
							pIAttrNode->get_text(&bstrAttrText);
							//printf("Attribute value: %ls\n", bstrAttrText);

							loan[j] = wcstof( bstrAttrText, NULL );

						}
						if (j>0)
							data->push_back(loan);

					}

					

					//	::MessageBox(NULL, (LPCSTR) bstrItemText,"parsing", MB_OK);		
				}
			}
		}
		//Do not forget to release interfaces:
		pIDOMNode->Release();
		pIDOMNode = NULL;
		pIParentNode->Release();
		pIParentNode = NULL;

	}

	catch (...)
	{
		//MessageBox(NULL, ("*** Exception occurred ***"), ("Error message"), MB_OK);
	}


	CoUninitialize();

}




//void PopulateFirstMonth(vector<float>* data , vector<vector<float>>* loansVec, int nTime, int nLoans, int nVars)
//{
//	int nRowCounter = 0;
//	int nColCounter = 0;
//	for (auto row : *loansVec)
//	{
//		
//		for (auto col : row)
//		{
//			
//			(*data)[nRowCounter + nColCounter] = col;
//
//			nColCounter++;
//
//			//std::cout << col << " ";
//		}
//		//nRowCounter++;
//
//		nRowCounter += (nTime * nVars);
//		nColCounter = 0;
//
//		std::cout <<  nRowCounter << std::endl;
//	}
//}

int _tmain(int argc, _TCHAR* argv[])
{

	vector<vector<float>> loansVec;
	vector<vector<float>> coeffsVec;
	LoadXml("c:\\temp\\input.xml", &loansVec);


	LoadXml("c:\\temp\\Coeff.xml", &coeffsVec);

	vector<vector<float>>* pLoans = &loansVec;
	vector<vector<float>>* pCoeffsVec = &coeffsVec;

	Engine engine(&pLoans, &pCoeffsVec);

	engine.GenerateCashflows();












	/*


	int nTime = 360;

	int nLoans = loansVec.size();

	int nVars = VARS::LF_NUMBER_OF_VARS, nVarsCalc = 25;

	vector<float> loans(nLoans);

    vector<float> data(nLoans * nTime * nVars);

	PopulateFirstMonth(&data, &loansVec, nTime, nLoans, nVars);


	concurrency::extent<1> ext(nLoans);
	concurrency::extent<3> extD(nLoans, nTime, nVars);
	concurrency::extent<3> extR(nLoans, nTime, nVarsCalc);

	array_view<float, 1> avL(ext, loans);
	array_view<float, 3> avD(extD, data);
	//array_view<float, 3> avR(extR, results);


	parallel_for_each( ext,  [=]( index<1> idx) restrict (amp)
	{	
		int i = 0;
		i = idx[0];

		float prevVal = 0.0f;

		for (int ii = 1; ii <= nTime ; ii++)
		{			
			avD(i, ii, VARS::LF_LoanId) = (float)i;
			//avR(i, ii, VARS::LF_LoanId) = (float)i;

			avD(i, ii, VARS::LF_TimeId) = (float)ii;
			//avR(i, ii, VARS::LF_TimeId) = (float)ii;

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

	
	parallel_for_each(ext, [=](index<1> idx) restrict(amp)
	{
		int i = 0;
		i = idx[0];

		float prevVal = 0.0f;

		for (int ii = 0; ii < nTime; ii++)
		{			
			//going to prev month example
			if (ii>0)
				prevVal = avD(i, ii - 1, VARS::LF_Ever90);

			avD(i, ii, VARS::LF_EverF) = avD(i, ii, VARS::LF_Ever60) * prevVal;
		}
	});


	avD.synchronize();
	*/
	return 0;
}

