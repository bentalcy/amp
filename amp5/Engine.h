#include "stdafx.h"

#include <vector>
#include <amp.h>
#include <amp_math.h>

using namespace std;
using namespace concurrency;

enum VARS { LF_LoanId = 0, LF_TimeId, LF_AllDeliqHist, LF_DelqHistNum, LF_Ever30, LF_Ever60, LF_Ever90, LF_EverF, LF_Ever30P, LF_Ever60P, LF_Ever90P, LF_LastP, LF_Effdate, LF_NextDueDate, LF_NumPmtsBehind, LF_MonthsInLatestForeclosure, LF_MonthsInLatestREO, LF_MonthsInLatestNinety, LF_PPPDate, LF_MonthsToPPP, LF_OrigAmt, LF_IOFlag, LF_RecastDate, LF_MonthsToRecast, LF_OrigLTV, LF_CombLTV, LF_MissingCombLTV, LF_State, LF_Term, LF_AmortTerm, LF_MonthVariable, LF_DocFull, LF_DocLow, LF_DocNo, LF_DocType, LF_Occupancy, LF_OccupancyOwner, LF_OccupancySecond, LF_OccupancyInvestor, LF_OccupancyOther, LF_OccupancyNone, LF_PropType, LF_PropTypeSfr, LF_PropTypeCondo, LF_PropTypeCoop, LF_PropTypeUnts24, LF_PropTypeTwnhse, LF_PropTypePud, LF_PropTypeUnts5, LF_PropTypeManhse, LF_PropTypeOther, LF_PropTypeNoinfo, LF_PurpPurchase, LF_PurpCashrefi, LF_PurpNoncashRefi, LF_PurpOther, LF_Purpose, LF_CurrRate, LF_OrigRate, LF_CloseRate, LF_PmiFlag, LF_PmiLevel, LF_FirstRate, LF_OrigCreditScore, LF_MBAStat0, LF_MBAStat1, LF_MBAStat2, LF_MBAStat3, LF_Dti, LF_SvcCodeOrig, LF_SvcCodeCurrent, LF_OrigCode, LF_BankruptcyFlag, LF_Lien, LF_LossCurrent, LF_LossFinal, LF_OrigDate, LF_LoanAge, LF_SchMnthP, LF_CalcMnthP, LF_Pmt, LF_PrinPmt, LF_RemBal, LF_Prin2PmtRat, LF_Prin2Rat, LF_NumPmtsMade, LF_NumPmtsRemaining, LF_UnempChangeOrig, LF_UnempChange3M, LF_UnempChange6M, LF_UnempChange9M, LF_UnempChange12M, LF_HpaOrigLog, LF_Hpa3MLog, LF_Hpa6MLog, LF_Hpa9MLog, LF_Hpa12MLog, LF_HpaOrig, LF_Hpa3M, LF_Hpa6M, LF_Hpa9M, LF_Hpa12M, LF_OrigValue, LF_CurrValue, LF_Balance, LF_CurrLtv, LF_CurrEquity, LF_CurrCombLtv, LF_Sato30Year, LF_Sato15Year, LF_SatoArm1Year, LF_CurrSpr30Year, LF_CurrSpr15Year, LF_CurrSprArm1Year, LF_Curr2OrigPmtRat, LF_PmtsMade3M, LF_PmtsMade4M, LF_PmtsMade6M, LF_PmtsMade12M, LF_NextMbaStat, LF_Judicial, LF_DeficiencyJudgement, LF_TrusteeSale, LF_CourtSale, LF_SheriffSale, LF_FannieTimeline, LF_RelativeFannieTimelines, LF_Frm30RateChg3M, LF_Frm30FeeChg3M, LF_Frm15RateChg3M, LF_Frm15FeeChg3M, LF_Arm1RateChg3M, LF_Arm1FeeChg3M, LF_Frm30RateChg6M, LF_Frm30FeeChg6M, LF_Frm15RateChg6M, LF_Frm15FeeChg6M, LF_Arm1RateChg6M, LF_Arm1FeeChg6M, LF_Frm30RateChg9M, LF_Frm30FeeChg9M, LF_Frm15RateChg9M, LF_Frm15FeeChg9M, LF_Arm1RateChg9M, LF_Arm1FeeChg9M, LF_Frm30RateChg12M, LF_Frm30FeeChg12M, LF_Frm15RateChg12M, LF_Frm15FeeChg12M, LF_Arm1RateChg12M, LF_Arm1FeeChg12M, LF_NextMbaStatC, LF_NextMbaStat3, LF_NextMbaStat6, LF_NextMbaStat9, LF_NextMbaStatF, LF_NextMbaStatR, LF_NextMbaStatL, LF_NextMbaStat0, LF_ServicerName, LF_StateAK, LF_StateAL, LF_StateAP, LF_StateAR, LF_StateAZ, LF_StateCA, LF_StateCO, LF_StateCT, LF_StateDC, LF_StateDE, LF_StateFL, LF_StateGA, LF_StateGU, LF_StateHI, LF_StateIA, LF_StateID, LF_StateIL, LF_StateIN, LF_StateKS, LF_StateKY, LF_StateLA, LF_StateMA, LF_StateMD, LF_StateME, LF_StateMI, LF_StateMN, LF_StateMO, LF_StateMS, LF_StateMT, LF_StateNC, LF_StateND, LF_StateNE, LF_StateNH, LF_StateNJ, LF_StateNM, LF_StateNV, LF_StateNY, LF_StateOH, LF_StateOK, LF_StateOR, LF_StatePA, LF_StatePR, LF_StateRI, LF_StateSC, LF_StateSD, LF_StateTN, LF_StateTX, LF_StateUT, LF_StateVA, LF_StateVI, LF_StateVT, LF_StateWA, LF_StateWI, LF_StateWV, LF_StateWY, LF_MonthJan, LF_MonthFeb, LF_MonthMar, LF_MonthApr, LF_MonthMay, LF_MonthJun, LF_MonthJul, LF_MonthAug, LF_MonthSep, LF_MonthOct, LF_MonthNov, LF_MonthDec, LF_MbaStat1C, LF_MbaStat13, LF_MbaStat16, LF_MbaStat19, LF_MbaStat1F, LF_MbaStat1R, LF_MbaStat1N, LF_MbaStat2C, LF_MbaStat23, LF_MbaStat26, LF_MbaStat29, LF_MbaStat2F, LF_MbaStat2R, LF_MbaStat2N, LF_MbaStat3C, LF_MbaStat33, LF_MbaStat36, LF_MbaStat39, LF_MbaStat3F, LF_MbaStat3R, LF_MbaStat3N, LF_SvcAccredited, LF_SvcAls, LF_SvcAmericanhome, LF_SvcAmeriquest, LF_SvcAurora, LF_SvcBofa, LF_SvcCentex, LF_SvcChase, LF_SvcCiti, LF_SvcCntrywide, LF_SvcEmc, LF_SvcEquicredit, LF_SvcEquityone, LF_SvcFairbanks, LF_SvcGmac, LF_SvcGreenpo, LF_SvcHls, LF_SvcHomecomings, LF_SvcHomeq, LF_SvcIndymac, LF_SvcJp, LF_SvcLitton, LF_SvcLongbeach, LF_SvcNatcity, LF_SvcNationstar, LF_SvcNewcent, LF_SvcOcwen, LF_SvcOptionOne, LF_SvcOther, LF_SvcSaxon, LF_SvcSelport, LF_SvcSuntrust, LF_SvcTbw, LF_SvcWamu, LF_SvcWells, LF_SvcWilshire, LF_ercept, LF_DataType, LF_McScenNo, LF_ProjLossAmt, LF_LossSeverity, LF_FutureMBAStat, LF_NUMBER_OF_VARS };


class Engine
{
public:
	Engine(vector<vector<float>>** vecLoans, vector<vector<float>>** vecCoeffs);

	void GenerateCashflows() ;

	~Engine();

private:
	vector<float>* m_data;
	vector<float>* m_flatCoeff;
	vector<vector<float>>* m_loansVec; 
	vector<vector<float>>* m_coeffVec;
	
	int m_nTime; 
	int m_nLoans; 
	int m_nVars;
	int m_nProbNoOfRec;

	void PopulateFirstMonth();
	void GenerateCashflowsStep1();
	void RestructureCoeff();


};
