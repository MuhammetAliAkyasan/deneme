/*
 * PGUREC_MainISR.c
 *
 *  Created on: 01 Sub 2021
 *      Author: GA - HFE
 */

#ifndef PGUREC_MAINISR_C_
#define PGUREC_MAINISR_C_

#include "DSP28x_Project.h"
#include "PGU_Common.h"
#include "PGUREC_Common.h"

//volatile float32 PGU_TeRefCAN                    = 0.0;

Uint16  Basarili = 0;
Uint16  RecCtrlTimeOutCnt = 0;
float32 PGUREC_VdcUpdateScale = 0.0;
float32 DenemeFrekansTest = 100.0;
float32 Precharge_DCLimit = 0.0;
float32 Volt_LabGiris = 0.0;

float32 DutyDeneme            = 0.0;
volatile Uint16 PGUtoPGUDeneme = 10.0;

volatile float32 VsPhase               = 0.0;
volatile float32 VsFreq                = 0.0;

volatile float32 IsPhase               = 0.0;
volatile float32 IsFreq                = 0.0;

volatile float32 PhaseDiff             = 0.0;
volatile float32 Vdc_ref               = 1400.0;

// Supply control and synchronization
float32   SyncOK = 0.0;
float32   SyncOKd = 0.0;
Uint16    ZC_Flag=0;
Uint16    PGUREC_BufferIlk =0;
Uint16    PGUREC_ControlTicker = 0;

Uint16    AnahtarlamaBasladi       = 0;
Uint16    AnahtarlamaBaslat_REC    = 0;
Uint16    GerilimsizAnahtarlama    = 0;
Uint16    Prech1                   = 0;
Uint16    Prech2                   = 0;

Uint16  PGUREC_CKU1= 0;
Uint16  PGUREC_CKU2= 0;

Uint16  PGUINV_FAULT=0;
Uint16 PGUINV_MotCurU=0;
Uint16 PGUINV_MotCurW=0;
Uint16 PGUINV_BreakCur=0;

volatile float32 VsSyncEnable          = 0.0;

// DC Voltage Reference Variables
Uint16  Vdc_refInitFlag = 0;
Uint16  Vs_refInitFlag = 0;

float32 wLPF        = 314.16;

// ContacRoutine Variables
Uint16 ESCStsOld    = 0;
Uint16 ESCCount     = 0;

Uint16 PCCCount     = 0;
Uint16 PCStsOld     = 0;

Uint16 PCCCount_2     = 0;
Uint16 PCStsOld_2     = 0;

Uint16 MCCount      = 0;
Uint16 MCStsOld     = 0;
Uint16 MC1_Status       = 0;

Uint16 MCCount_2      = 0;
Uint16 MCStsOld_2     = 0;
Uint16 MC2_Status      = 0;


Uint16 MCCount_Aux1      = 0;
Uint16 MCStsOld_Aux1     = 0;

Uint16 MCCount_Aux2      = 0;
Uint16 MCStsOld_Aux2     = 0;

Uint16 MCBCount      = 0;
Uint16 MCBtsOld     = 0;

 Uint16 CKU_Ident0_REC=0;
 Uint16 CKU_Ident1_REC=0;
 Uint16 CKU_Ident2_REC=0;
 Uint16 CKU_Ident3_REC=0;

 Uint16 PGUREC_Emergency_Degraded=0;
 Uint16 PGUREC_Emergency1=0;
 Uint16 PGUREC_Emergency2=0;
 Uint16 PGUREC_Emergency3=0;

 // Inverter Devreye alma sýrasýnda kullanýlan deðiþkenler
float32 PGUREC_MainIsrTotalTime  = 0.0;

Uint16  PGUREC_TivaRegWFlag      = 0;
Uint16  PGUREC_TivaRegRCount     = 0;

Uint16  PGUREC_MasterContrStat   = 0;
Uint16  PGUREC_ConvEnable        = 0;
Uint16  PGUREC_TractInh          = 0;
Uint16  PGUREC_ERTMSBrake        = 0;
Uint16  PGUREC_VCBStatus         = 0;
Uint16  PGUREC_EDBrakeCut        = 0;
Uint16  PGUREC_Trac_Null        = 0;


Uint16  RecPWMStartCnt  = 0;
Uint16  PGUREC_DC_Counter      = 0;
Uint16  PGUREC_InvTripClear    = 0;

Uint16  PowerCnt        = 0;
Uint16  ZC_Cnt          = 0;
float32 PowerFactor_p   = 0.0;
float32 PowerFactor_s   = 0.0;
float32 PowerFactorFP_s   = 0.0;

Uint16  PGUREC_EDBrakeActive     = 0.0;

Uint16  PGUREC_Reverser          = 0;
Uint16  PGUREC_ReverserNew       = 0;
Uint16  PGUREC_ReverserOld       = 0;
Uint16  PGUREC_ReverserCnt       = 0;


float32 CATENARY_HIGH_COUNT   =630000.0;  // 2100 = 1 saniye, 300 *2100, 5 dakika
float32 CATENARY_LOW_COUNT    =252000.0;  // 2100 = 1 saniye, 120 *2100, 2 dakika

float32 IRec1      = 0.0;
float32 IRec2      = 0.0;

float32 VCatenary     = 0.0;
float32 VSeconder     = 0.0;

Uint16  PGUREC_ControlEnable   = 0;

Uint16  PGUREC_FaultFlagsClear = 0;
Uint16  PGUREC_FaultReset = 0;


Uint16  PGUREC_SelfTestErrClear= 0;

//------------------------------------
// Global Variables
//------------------------------------

    //--TICK COUNTERS
Uint32  PGUREC_RecIsrTicker  = 0;        //  Rectifier ISR Ticker
Uint32  PGUREC_MainIsrTicker = 0;          //  Main ISR Ticker

Uint16  PGUREC_DOCounter = 0;
Uint16 PGUREC_Lifesign = 0;


    //--OTHERS
Uint16  PGUREC_FPGAsReset    = 0;        //  Trip Zone error clear control variable
Uint16  PGUREC_TripZoneClear = 0;

// Rectifier Structs Initialization Values
TORQUE  PGUREC_Torque          = TORQUE_DEFAULTS;                   //  Torque reference generation struct initialization
REGEN   Regen           = REGEN_DEFAULTS;                    //  Regenerative braking limit (based on speed) struct initialization

RMS             PGUREC_IRec1RMS       = RMS_DEFAULTS;
RMS             PGUREC_IRec2RMS       = RMS_DEFAULTS;
RMS             PGUREC_VRecRMS        = RMS_DEFAULTS;


PGU_FDB_REC     PGU_1PHRectFdb          =  {0.0,0.0,0.0,0.0};        //  Rectifier Feedback initialization
PGU_FDB_REC     PGU_1PHRectFdbHs        =  {0.0,0.0,0.0,0.0};        //  High Speed Feedback initialization


SUPPLY          Supply          = {0.0,0.0,0.0};                                             //  Supply initialization
SUPPLYMEAN      SupplyMean      = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0};

PGUREC_CTRL_VAR     PGUREC_RCTL_REG          = {0x0000};                                       //  Rectifier control variable initialization

DCRC            DCest           = {DCRC_IN_DEFAULTS,DCRC_OUT_DEFAULTS,DCRC_VAR_DEFAULTS,DCRC_PAR_DEFAULTS};         // DC estimation module initialization


SYNC            Sync            = SYNC_DEFAULTS;           // Grid synchronization control module initialization

QSG             VsQSG1          = QSG_DEFAULTS;            // Supply Voltage Processing module initialization
QSG             VsQSG2          = QSG_DEFAULTS;
QSG             VsQSG3          = QSG_DEFAULTS;

QSG             VdcQSG          = QSG_DEFAULTS;            // DC Voltage Processing module initialization

FLL             Fll             = FLL_DEFAULTS;            // Frequency Locked Loop module initialization

PEAK            Vspeak          = PEAK_DEFAULTS;            // Supply Voltage peak initialization
PEAK            Vdcpeak         = PEAK_DEFAULTS;            // DC Voltage peak initialization

ZEROCROSS       Zcross          = ZEROCROSS_DEFAULTS;       // Zerocross detection module initialization

PPARK           Pll_QSG_Park    = PPARK_DEFAULTS;           // Single phase PLL initialization
PPARK           Pll_QSG_Park1    = PPARK_DEFAULTS;           // Single phase PLL initialization

PLL_QSG_OSC     Pll_QSG_Osc     = PLL_QSG_OSC_DEFAULTS;
PLL_QSG_OSC     Pll_QSG_Osc1     = PLL_QSG_OSC_DEFAULTS;

RECPI           Pll_QSG_PI      = {RECPI_IN_DEFAULTS, RECPI_OUT_DEFAULTS, RECPI_VAR_DEFAULTS, RECPI_PAR_DEFAULTS};
RECPI           Pll_QSG_PI1      = {RECPI_IN_DEFAULTS, RECPI_OUT_DEFAULTS, RECPI_VAR_DEFAULTS, RECPI_PAR_DEFAULTS};

//===========================================================================
// Local Variables Instantiation
//===========================================================================

float32 PGUREC_MainIsrStartTime        = 0.0;
float32 PGUREC_MainIsrFinishTime       = 0.0;
Uint16  PGUREC_ADCOffsetCntr           = 0;
Uint16  PGUREC_NeutralCnt_PowerOff     = 0;
float32  Catenary_High          = 0.0;
float32  Catenary_Low         = 0.0;

float32  Capacitive_Power       = 0.0;
float32  Inductive_Power       = 0.0;

Uint16  Catenary_High_Warn     = 0;
Uint16  Catenary_Low_Warn     = 0;


Uint16  PGUREC_NeutralCnt              = 0;
Uint16  PGUREC_PoweringCnt             = 0;
//Uint16  BrakingCnt              = 0;
Uint16  PGUREC_EMGBrakeCnt             = 0;

float32 PGUREC_RMSPeriod             = 0.0;
Uint16  PGUREC_TivaWriteToggle       = 0;

 volatile DIOC1_RXMSG1_REG PGUREC_DIOC1_Inputs1     = {0x0000};
 volatile DIOC1_RXMSG2_REG PGUREC_DIOC1_Inputs1N    = {0xFFFF};

 volatile DIOC1_RXMSG3_REG PGUREC_DIOC1_Inputs_TCPU  = {0x0000};
 volatile DIOC1_RXMSG4_REG PGUREC_DIOC1_InputsN_TCPU = {0xFFFF};

 volatile DIOC2_RXMSG1_REG PGUREC_DIOC2_Inputs1     = {0x0000};
 volatile DIOC2_RXMSG2_REG PGUREC_DIOC2_Inputs1N    = {0xFFFF};
 volatile DIOC2_RXMSG3_REG PGUREC_DIOC2_Inputs2     = {0x0000};
 volatile DIOC2_RXMSG4_REG PGUREC_DIOC2_Inputs2N    = {0xFFFF};

 volatile DIOC1_TXMSG1_REG PGUREC_DIOC1_Outputs      = {0xFFFF};
 volatile DIOC2_TXMSG1_REG PGUREC_DIOC2_Outputs      = {0xFFFF};

 volatile TCPU_RXMSG1_REG PGUREC_TCPU_Inputs            = {0x0000};
 volatile TCPU_RXMSG2_REG PGUREC_TCPU_DIOC_Inputs       = {0x0000};
 volatile TCPU_RXMSG3_REG PGUREC_TCPU_Faults_TIC        = {0x0000};
 volatile TCPU_RXMSG4_REG PGUREC_TCPU_Faults_Others     = {0x0000};
 volatile TCPU_RXMSG5_REG PGUREC_TCPU_Fault_Action      = {0x0000};

 volatile TCPU_TXMSG_REG PGUREC_TCPU_Outputs = {0xFFFF};



void PGUREC_MainISRInit(void)
{
	PGUREC_ProtectionInit();
//	DMAInit();
	EthRxData[13]=0;
/*------------------------------------------------------------------------------
	RMS module initialization
------------------------------------------------------------------------------*/

	PGUREC_IRec1RMS.Ts   = PGUREC_TS_MAINISR;
    PGUREC_IRec2RMS.Ts   = PGUREC_TS_MAINISR;
	PGUREC_VRecRMS.Ts    = PGUREC_TS_MAINISR;

/*------------------------------------------------------------------------------
    SYNC module initialization
------------------------------------------------------------------------------*/

    Sync.Vspeak = VS_PEAK;

/*------------------------------------------------------------------------------
        DCest module initialization
------------------------------------------------------------------------------*/
    DCest.p.Enable      = 1;
    DCest.p.Tadv        = 0.75* (1.0/1600.0);
    DCest.p.w           = 2*PI*100;
    DCest.p.ThetaAdv    = DCest.p.w*DCest.p.Tadv;
    DCest.p.Cterm       = cos(DCest.p.ThetaAdv);
    DCest.p.Sterm       = sin(DCest.p.ThetaAdv);

/*------------------------------------------------------------------------------
        QSG module initialization
------------------------------------------------------------------------------*/
    VsQSG1.wc       = CENTER_FREQUENCY;
    VsQSG1.Gain     = VSQSG1_K;
    VsQSG1.Ts_12    = (PGUREC_TS_MAINISR/12);

    VsQSG2.wc       = CENTER_FREQUENCY;
    VsQSG2.Gain     = VSQSG2_K;
    VsQSG2.Ts_12    = (PGUREC_TS_MAINISR/12);

    VsQSG3.wc       = CENTER_FREQUENCY;
    VsQSG3.Gain     = VSQSG2_K;
    VsQSG3.Ts_12    = (PGUREC_TS_MAINISR/12);

    VdcQSG.wc       = 2*CENTER_FREQUENCY;
    VdcQSG.Gain     = 0.25;
    VdcQSG.Ts_12    = (PGUREC_TS_MAINISR/12);

/*------------------------------------------------------------------------------
            FLL module initialization
------------------------------------------------------------------------------*/
    Fll.Ts          = PGUREC_TS_MAINISR;
    Fll.kwg         = VSQSG2_K * (2*PI*50) * (-50);  // Gamma = -50
    Fll.VsPeakSqrMin= VS_PEAK_MIN * VS_PEAK_MIN;
    Fll.VsPeakSqrMax= VS_PEAK_MAX * VS_PEAK_MAX;
    Fll.w_ff        = CENTER_FREQUENCY;
    Fll.w_max       = 1.1 * CENTER_FREQUENCY;
    Fll.w_min       = 0.9 * CENTER_FREQUENCY;

/*------------------------------------------------------------------------------
        ZEROCROSS initialization
------------------------------------------------------------------------------*/

    Zcross.zc_cntinit   = 7;                //zc_flag 7 T_Sampleh boyunca 1
    Zcross.Threshold    = 0.0;

/*------------------------------------------------------------------------------
        Pll_QSG and Pll_QSGPI initialization
------------------------------------------------------------------------------*/

    Pll_QSG_Osc.w_ff        = CENTER_FREQUENCY;
    Pll_QSG_Osc.Ts          = PGUREC_TS_MAINISR;

    Pll_QSG_Osc1.w_ff        = CENTER_FREQUENCY;
    Pll_QSG_Osc1.Ts          = PGUREC_TS_MAINISR;

    Pll_QSG_PI.p.Enable     = 1;
    Pll_QSG_PI.p.Ki         = (PGUREC_TS_MAINISR * PLL_QSG_KI)/PLL_QSG_KP; // Ti= KP/KI, Ki=Ts/Ti, Ki=(Ts*KI)/KP
    Pll_QSG_PI.p.Kp         = PLL_QSG_KP;
    Pll_QSG_PI.p.OutMax     = PLL_QSGPI_OUTMAX;
    Pll_QSG_PI.p.OutMin     = PLL_QSGPI_OUTMIN;

    Pll_QSG_PI1.p.Enable     = 1;
    Pll_QSG_PI1.p.Ki         = (PGUREC_TS_MAINISR * PLL_QSG_KI)/PLL_QSG_KP; // Ti= KP/KI, Ki=Ts/Ti, Ki=(Ts*KI)/KP
    Pll_QSG_PI1.p.Kp         = PLL_QSG_KP;
    Pll_QSG_PI1.p.OutMax     = PLL_QSGPI_OUTMAX;
    Pll_QSG_PI1.p.OutMin     = PLL_QSGPI_OUTMIN;

}
//===============================================================================
//	Main ISR
//===============================================================================
interrupt void PGUREC_MainISR(void)
{
        PGUREC_MainIsrStartTime = ((float32)EPwm5Regs.TBCTR /(float32)EPwm5Regs.TBPRD)* 0.5 *PGUREC_TS_MAINISR * 1000000.0; //Microsecond

        //Reset the watchdog counter
        ServiceDog();


        IO_TOGGLE(PGUREC_WDTog)



        PGUREC_ControlTicker++;
        PGUREC_MainIsrTicker++;							// Verifying the ISR
        PGUREC_DOCounter++;

        if (PGUREC_Lifesign > 65534)
        {
            PGUREC_Lifesign = 0;
        }
        else
            PGUREC_Lifesign++;

        if (PGUREC_DOCounter>6300)
        {
            IO_CLR(DO_ENABLE)
            PGUREC_DOCounter=6301;
            IO_CLR(PGUREC_MCBTrip)
        }

        if (PGUREC_DIOC1_Inputs_TCPU.bit.Condansator_Pressure==0)
        {
            PGUGateOFF
            FOIOGateOFF
		    IO_SET(MCSig1)                // Open the Main Contactor-1
			IO_SET(MCSig2)                // Open the Main Contactor-2
        }

        //----------DIOC_1 to PGU----------//

        PGUREC_DIOC1_Inputs_TCPU.all          = DIOC1RXMsg.C1.uiBuffer[0].all;         // Read DIOC Inputs
        PGUREC_DIOC1_InputsN_TCPU.all         = DIOC1RXMsg.C1.uiBuffer[2].all;         // Read DIOC Inputs
        PGUREC_DIOC1_Inputs1.all              = DIOC1RXMsg.C1.uiBuffer[1].all;         // Read DIOC Inputs
        PGUREC_DIOC1_Inputs1N.all             = DIOC1RXMsg.C1.uiBuffer[3].all;         // Read DIOC Inputs

        //----------DIOC_2 to PGU----------//

        PGUREC_DIOC2_Inputs1.all           = DIOC2RXMsg.C1.uiBuffer[0].all;         // Read DIOC Inputs
        PGUREC_DIOC2_Inputs1N.all          = DIOC2RXMsg.C1.uiBuffer[2].all;         // Read DIOC Inputs
        PGUREC_DIOC2_Inputs2.all           = DIOC2RXMsg.C1.uiBuffer[1].all;         // Read DIOC Inputs
        PGUREC_DIOC2_Inputs2N.all          = DIOC2RXMsg.C1.uiBuffer[3].all;         // Read DIOC Inputs

        //----------PGUREC TO DIOC_1 ----------//

        DIOC1TXMsg.C1.uiBuffer[0].bit.bit0 = PGUREC_DIOC1_Outputs.bit.Cabin_Fan;
//        DIOC1TXMsg.C1.uiBuffer[0].bit.bit1 = PGUREC_DIOC1_Outputs.bit.RSVD1;
//        DIOC1TXMsg.C1.uiBuffer[0].bit.bit2 = PGUREC_DIOC1_Outputs.bit.CIFR;
        DIOC1TXMsg.C1.uiBuffer[0].bit.bit3 = PGUREC_DIOC1_Outputs.bit.RVSD2;
//        DIOC1TXMsg.C1.uiBuffer[0].bit.bit4 = PGUREC_DIOC1_Outputs.bit.TRAC_OK1;
//        DIOC1TXMsg.C1.uiBuffer[0].bit.bit5 = PGUREC_DIOC1_Outputs.bit.TRAC_OK2;

        //----------PGU TO DIOC_2 ----------//

//        DIOC2TXMsg.C1.uiBuffer[0].bit.bit0 = PGUREC_DIOC2_Outputs.bit.Motor1_OK;
//        DIOC2TXMsg.C1.uiBuffer[0].bit.bit1 = PGUREC_DIOC2_Outputs.bit.Motor2_OK;
        DIOC2TXMsg.C1.uiBuffer[0].bit.bit2 = PGUREC_DIOC2_Outputs.bit.HV_Presence;
        DIOC2TXMsg.C1.uiBuffer[0].bit.bit3 = PGUREC_DIOC2_Outputs.bit.Trac_DCLink_OK;
        DIOC2TXMsg.C1.uiBuffer[0].bit.bit4 = PGUREC_DIOC2_Outputs.bit.Pantograph_Permission;
//        DIOC2TXMsg.C1.uiBuffer[0].bit.bit5 = PGUREC_DIOC2_Outputs.bit.RSVD1;

        //----------TCPU_TO_PGU----------//

        PGUREC_TCPU_Inputs.all            = TCPURXMsg.C1.uiBuffer[3].all;         // Read TCPU Inputs

        PGUREC_TCPU_DIOC_Inputs.all       = TCPURXMsg.C3.uiBuffer[0].all;         // Read TCPU Inputs
        PGUREC_TCPU_Faults_TIC.all        = TCPURXMsg.C3.uiBuffer[1].all;         // Read TCPU Inputs
        PGUREC_TCPU_Faults_Others.all     = TCPURXMsg.C3.uiBuffer[2].all;         // Read TCPU Inputs
        PGUREC_TCPU_Fault_Action.all      = TCPURXMsg.C3.uiBuffer[3].all;         // Read TCPU Inputs

        //----------PGU_X to TCPU----------//

       TCPUTXMsg.C1.uiBuffer[0].all        = PGUREC_TCPU_Outputs.all;            // Write TCPU Outputs

        //----------PGU_REC to PGU_INV ----------//

//        PGUINV_FAULT                       = PGURXMsg.C1.uiBuffer[0].all;         // Read PGU_INV Msg
//        PGUINV_MotCurU                     = PGURXMsg.C1.uiBuffer[1].all;         // Read PGU_INV Msg  (Izleme amaclý)
//        PGUINV_MotCurW                     = PGURXMsg.C1.uiBuffer[2].all;         // Read PGU_INV Msg  (Izleme amaclý)
//       VCatenary                  = PGURXMsg.C1.uiBuffer[3].all;         // Read PGU_INV Msg  (Izleme amaclý)
//
//
//        PGUTXMsg.C1.uiBuffer[0].all        = PGUREC_FLT_REG.all;                  // Write PGU_INV Msg
//        PGUTXMsg.C1.uiBuffer[1].all        = PGUREC_Torque.TotalLimFactor;        // Write PGU_INV Msg
//        PGUTXMsg.C1.uiBuffer[2].all        = PGUREC_CTL_REG.bit.STATE;            // Write PGU_INV Msg
//        PGUTXMsg.C1.uiBuffer[3].all        = PGUREC_DC_Counter;                   // Write PGU_INV Msg

       GerilimsizAnahtarlama                 = PGURXMsg.C1.uiBuffer[0].bit.bit3;
       Prech1                                = PGURXMsg.C1.uiBuffer[0].bit.bit4;
       Prech2                                = PGURXMsg.C1.uiBuffer[0].bit.bit5;
       AnahtarlamaBaslat_REC                 = PGURXMsg.C1.uiBuffer[0].bit.bit6;

       if(!(GerilimsizAnahtarlama==1||Prech1==1||Prech2==1||AnahtarlamaBaslat_REC==1))
       {
           PGUREC_TCPU_Outputs.bit.PCC1_SIG = PGURXMsg.C1.uiBuffer[0].bit.bit7;
           PGUREC_TCPU_Outputs.bit.PCC2_SIG = PGURXMsg.C1.uiBuffer[0].bit.bit8;
       }


       //---------- FOIO to PGU_REC ----------// PGUREC_FLT_REG




       ///////////////////////////////////////////SÇ Düzenleme///////////////////////////////////////////////////////
       //Aþaðýdaki satýrlar eklendi.


       if (PGURXMsg.C1.uiBuffer[0].bit.bit0)
       {
           IO_SET(PGUREC_MCBTrip)

       }
       else
       {
           IO_CLR(PGUREC_MCBTrip)
       }


       if(!(GerilimsizAnahtarlama==1||Prech1==1||Prech2==1||AnahtarlamaBaslat_REC==1))
       {
           if (PGURXMsg.C1.uiBuffer[0].bit.bit1)
           {
               IO_SET(MCSig1)
           }
           else
           {
               IO_CLR(MCSig1)
           }

           if (PGURXMsg.C1.uiBuffer[0].bit.bit2)
           {
               IO_SET(MCSig2)
           }
           else
           {
               IO_CLR(MCSig2)
           }
       }


       if(Prech1 == 1 || Prech2 == 1)
       {
           PGUREC_ReverserNew = 2;
       }
       else
       {
           PGUREC_ReverserNew = 3;
           PGUREC_MasterContrStat=3;
       }



        PGUTXMsg.C1.uiBuffer[0].all        = PGUREC_TemperatureLPF_CKU1.CabinTemp;         // Write PGU_INV Msg
        PGUTXMsg.C1.uiBuffer[1].all        = PGUREC_TemperatureLPF_CKU1.ConvHumidity_Temp; // Write PGU_INV Msg
        PGUTXMsg.C1.uiBuffer[2].all        = PGUREC_TemperatureLPF_CKU1.ConvHumidity_Hum;  // Write PGU_INV Msg
        PGUTXMsg.C1.uiBuffer[3].all        = VCatenary;                                    // Write PGU_INV Msg
        PGUTXMsg.C2.uiBuffer[0].all        = PGUREC_Measure.Result.Volt_DCLink;            // Write PGU_INV Msg
        PGUTXMsg.C2.uiBuffer[1].all        = PGUREC_TemperatureLPF_CKU1.RectifierTemp1;    // Write PGU_INV Msg
        PGUTXMsg.C2.uiBuffer[2].all        = PGUREC_TemperatureLPF_CKU1.RectifierTemp2;    // Write PGU_INV Msg
//        PGUTXMsg.C2.uiBuffer[3].all        = - PGUREC_Measure.Result.Cur_RectInput1;         // Write PGU_INV Msg
//        PGUTXMsg.C3.uiBuffer[0].all        = - PGUREC_Measure.Result.Cur_RectInput2;         // Write PGU_INV Msg
        PGUTXMsg.C2.uiBuffer[3].all        = PGUREC_IRec1RMS.RMS;                          // Write PGU_INV Msg
        PGUTXMsg.C3.uiBuffer[0].all        = PGUREC_IRec2RMS.RMS;                          // Write PGU_INV Msg
        PGUTXMsg.C3.uiBuffer[1].all        = PGUREC_TemperatureLPF_CKU1.MotorTemp1;        // Write PGU_INV Msg
        PGUTXMsg.C3.uiBuffer[2].all        = PGUREC_TemperatureLPF_CKU1.MotorTemp2;        // Write PGU_INV Msg
        PGUTXMsg.C3.uiBuffer[3].all        = PGUREC_TemperatureLPF_CKU1.GearTemp;          // Write PGU_INV Msg
        PGUTXMsg.C4.uiBuffer[0].all        = PGUREC_TemperatureLPF_CKU2.CabinTemp;         // Write PGU_INV Msg
        PGUTXMsg.C4.uiBuffer[1].all        = PGUREC_TemperatureLPF_CKU2.CoolingFlow_Flow;  // Write PGU_INV Msg
        PGUTXMsg.C4.uiBuffer[2].all        = PGUREC_TemperatureLPF_CKU2.CoolingFlow_Temp;  // Write PGU_INV Msg
        PGUTXMsg.C4.uiBuffer[3].all        = PGUREC_TemperatureLPF_CKU2.RectifierTemp1;    // Write PGU_INV Msg
        PGUTXMsg.C5.uiBuffer[0].all        = PGUREC_TemperatureLPF_CKU2.RectifierTemp2;    // Write PGU_INV Msg
        PGUTXMsg.C5.uiBuffer[1].all        = PGUREC_TemperatureLPF_CKU2.MotorTemp1;        // Write PGU_INV Msg
        PGUTXMsg.C5.uiBuffer[2].all        = PGUREC_TemperatureLPF_CKU2.MotorTemp2;        // Write PGU_INV Msg
        PGUTXMsg.C5.uiBuffer[3].all        = PGUREC_TemperatureLPF_CKU2.GearTemp;          // Write PGU_INV Msg

        if((PRECHCTL_REG1.bit.STATE > 0 || PRECHCTL_REG2.bit.STATE > 0) && (PRECHCTL_REG1.bit.STATUS > 0 || PRECHCTL_REG2.bit.STATUS > 0))
        {

            if(PRECHCTL_REG1.bit.STATE == 6)
            {
                PGUTXMsg.C6.uiBuffer[0].bit.bit0   = 1;         //Prech1 Baþarýlý
            }

            if(PRECHCTL_REG2.bit.STATE == 6)
            {
                PGUTXMsg.C6.uiBuffer[0].bit.bit2   = 1;         //Prech2 Baþarýlý
            }
        }
        else
        {
            PGUTXMsg.C6.uiBuffer[0].bit.bit0       = 0;
            PGUTXMsg.C6.uiBuffer[0].bit.bit2       = 0;
        }
        if(PRECHCTL_REG1.bit.STATUS == 0 || PRECHCTL_REG2.bit.STATUS == 0)
        {
            if(PRECHCTL_REG1.bit.STATE==20||PRECHCTL_REG1.bit.STATE==21||PRECHCTL_REG1.bit.STATE==22||PRECHCTL_REG1.bit.STATE==23)
            {
                PGUTXMsg.C6.uiBuffer[0].bit.bit1   = 1;        //Prech1 Sýrasýnda Hata
            }

            if(PRECHCTL_REG2.bit.STATE==20||PRECHCTL_REG2.bit.STATE==21||PRECHCTL_REG2.bit.STATE==22||PRECHCTL_REG2.bit.STATE==23)
            {
                PGUTXMsg.C6.uiBuffer[0].bit.bit3   = 1;         //Prech2 Sýrasýnda Hata
            }
        }
        else
        {
            PGUTXMsg.C6.uiBuffer[0].bit.bit1       = 0;
            PGUTXMsg.C6.uiBuffer[0].bit.bit3       = 0;
        }

        if(PGUREC_CTL_REG.bit.STATE   == 6)
            PGUTXMsg.C6.uiBuffer[0].bit.bit4 = 1;
        else
            PGUTXMsg.C6.uiBuffer[0].bit.bit4 = 0;

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

//        Identifying CKU from ID signals

//        if(PGUREC_TCPU_DIOC_Inputs.bit.ID5 == 0 && PGUREC_DIOC1_Inputs_TCPU.bit.ID5 == 0 &&  PGUREC_DIOC1_InputsN_TCPU.bit.N_ID5 == 1)
//               {
//                PGUREC_CKU1=1;
//                PGUREC_CKU2=0;
//               }
//
//        if(PGUREC_TCPU_DIOC_Inputs.bit.ID5 == 1 && PGUREC_DIOC1_Inputs_TCPU.bit.ID5 == 1 &&  PGUREC_DIOC1_InputsN_TCPU.bit.N_ID5 == 0)
//               {
//                PGUREC_CKU2=1;
//                PGUREC_CKU1=0;
//               }
        if (PGUREC_TCPU_DIOC_Inputs.bit.ID3 == 1
                && PGUREC_DIOC1_Inputs_TCPU.bit.ID3 == 1
                && PGUREC_DIOC1_InputsN_TCPU.bit.N_ID3 == 0)
        {
            PGUREC_CKU1 = 1;
            PGUREC_CKU2 = 0;
        }

        if (PGUREC_TCPU_DIOC_Inputs.bit.ID3 == 0
                && PGUREC_DIOC1_Inputs_TCPU.bit.ID3 == 0
                && PGUREC_DIOC1_InputsN_TCPU.bit.N_ID3 == 1)
        {
            PGUREC_CKU2 = 1;
            PGUREC_CKU1 = 0;
        }
//        EthernetTest();

//        PGUREC_ReadMVBData();
//
//        PGUREC_WriteMVBData();


        if(PGUREC_ControlEnable==1)
        {

        PGUREC_ADC_CHANNEL_READ(PGUREC_Measure)
	    PGUREC_ADC_MEASUREMENT(PGUREC_Measure)				// Read ADC variables

	    REC_FDB_MACRO_1ps(PGU_1PHRectFdbHs,PGUREC_Measure)

	// RMS values

//        Volt_LabGiris=PGU_1PHRectFdbHs.Volt_Catenary*2.61;

        Volt_LabGiris=PGU_1PHRectFdbHs.Volt_Grid;//*2.61;


        PGUREC_RMSPeriod    = 0.06;

	    PGUREC_IRec1RMS.In       = -1*PGUREC_Measure.Result.Cur_RectInput1;
        PGUREC_IRec1RMS.Period   = PGUREC_RMSPeriod;
        RMS_MACRO(PGUREC_IRec1RMS)

        PGUREC_IRec2RMS.In       = -1*PGUREC_Measure.Result.Cur_RectInput2;
        PGUREC_IRec2RMS.Period   = PGUREC_RMSPeriod;
        RMS_MACRO(PGUREC_IRec2RMS)

//        VsQSG1.In               = Volt_LabGiris;
//        VsQSG1.wc               = wLPF;
//        QSG_MACRO(VsQSG1)

        PGUREC_VRecRMS.In       = VsQSG1.Alpha;
        PGUREC_VRecRMS.Period   = PGUREC_RMSPeriod;
        RMS_MACRO(PGUREC_VRecRMS)

        IRec1=PGUREC_IRec1RMS.RMS ;                  // RMS value of 1 phase rectifier input current
        IRec2=PGUREC_IRec2RMS.RMS ;                  // RMS value of 1 phase rectifier input current

        VSeconder=PGUREC_VRecRMS.RMS ;        // RMS value of rectifier input voltage

        VCatenary = PGUREC_VRecRMS.RMS/TRAFO_RATIO;    // RMS value of catenary input voltage


    //if supply exists
        if(Supply.Rms > 10.0)    // Grid control : VCatenary=3000 Vrms   (Þebeke denemesi için deðer küçük yapýldý.)
        {
            VsSyncEnable =1;
        }
        else
        {
            VsSyncEnable =0;
        }

// =================================== Supply Voltage Processing ======================================

//      Connect inputs of the VsQSG modules and call the QSG macro
        VsQSG1.In               = Volt_LabGiris;
        VsQSG1.wc               = wLPF;
        QSG_MACRO(VsQSG1)

        VsQSG2.In               = VsQSG1.Alpha;
        VsQSG2.wc               = wLPF;
        QSG_MACRO(VsQSG2)

    //  Connect inputs of the Vspeak module and call the VSPEAK macro
        Vspeak.Alpha            = VsQSG2.Alpha;
        Vspeak.Beta             = VsQSG2.Beta;
        PEAK_MACRO(Vspeak)

    //  Supply voltage harmonics
        Vs.Harm = Volt_LabGiris - VsQSG2.Alpha;


//// =================================== Supply Current Processing ======================================

        //  Connect inputs of the VsQSG modules and call the QSG macro
        VsQSG3.In               = PGU_1PHRectFdbHs.Cur_RectInput1;
        VsQSG3.wc               = wLPF;
        QSG_MACRO(VsQSG3)

//// =================================== Input Power Calculation ========================================

    //  POWER calculation
//        ApparentP_p.MeanSum = ApparentP_p.MeanSum + (PGUREC_IPrimerRMS.RMS * VCatenary );
//        RealP_p.PeriodSum   = RealP_p.PeriodSum   + (PGU_1PHRectFdbHs.Cur_Primer * PGU_1PHRectFdbHs.Volt_Catenary) * PGUREC_TS_MAINISR;      // Primer akým okumasý yok. Kapatýldý.

        ApparentP_s.MeanSum = ApparentP_s.MeanSum + (PGUREC_IRec1RMS.RMS * PGUREC_VRecRMS.RMS);
        RealP_s.PeriodSum   = RealP_s.PeriodSum   + ((PGU_1PHRectFdbHs.Cur_RectInput1) * Volt_LabGiris) * PGUREC_TS_MAINISR;

        if(Zcross.ZCD==1)
        {
            RealP_p.MeanSum = RealP_p.MeanSum + RealP_p.PeriodSum * ((wLPF)/(2.0*PI));
            RealP_p.PeriodSum = 0.0;

            RealP_s.MeanSum = RealP_s.MeanSum + RealP_s.PeriodSum * ((wLPF)/(2.0*PI));
            RealP_s.PeriodSum = 0.0;

            ZC_Cnt++;
        }

// =================================== DC Voltage Processing =========================================

    //  Connect inputs of the VdcQSG module and call the QSG macro
        VdcQSG.In               = PGU_1PHRectFdbHs.Volt_DCLink - Vdc_ref;
        VdcQSG.wc               = 2*wLPF;       // 2*CENTER_FREQUENCY
        QSG_MACRO(VdcQSG)

        Dc.Vdc_BSF      = PGU_1PHRectFdbHs.Volt_DCLink - VdcQSG.Alpha;

        DCest.i.Udc         = PGU_1PHRectFdbHs.Volt_DCLink;
        DCest.i.Ur_alpha    = VdcQSG.Alpha;
        DCest.i.Ur_beta     = VdcQSG.Beta;
        DCest.i.we          = 2*wLPF;
        DCMACRO(DCest)

        Dc.Vdc_Est      = DCest.o.UdcEst;

//  Connect inputs of the Vdcpeak module and call the VSPEAK macro
        Vdcpeak.Alpha           = VdcQSG.Alpha;
        Vdcpeak.Beta            = VdcQSG.Beta;
        PEAK_MACRO(Vdcpeak)


// ================================ Supply Synchronization  ===========================================

    //-----------------------------------------------------
    //  QSG based PLL
    //-----------------------------------------------------
    //  Connect inputs of the PARK module (Used for PLL_QSG)
    //  and call the park transformation macro
        Pll_QSG_Park.Alpha      = VsQSG1.Alpha;
        Pll_QSG_Park.Beta       = VsQSG1.Beta;
        Pll_QSG_Park.Sine       = Pll_QSG_Osc.Sine;
        Pll_QSG_Park.Cosine     = Pll_QSG_Osc.Cosine;

        PPARK_MACRO(Pll_QSG_Park);

    //  Connect inputs of the PI module (Used for PLL_QSG)
    //  and call the PI macro
        Pll_QSG_PI.i.Fdb        = (-Pll_QSG_Park.Ds);

        Pll_QSG_PI.p.Enable     = VsSyncEnable;
        RECPI_MACRO(Pll_QSG_PI)

    //  Connect inputs of the PLL_QSG_OSC module call the PLL_QSG_OSC macro
        Pll_QSG_Osc.w_err       = Pll_QSG_PI.o.Out;
        PLL_QSG_OSC_MACRO(Pll_QSG_Osc)
        VsPhase = Pll_QSG_Osc.Phase;
        VsFreq =  Pll_QSG_Osc.Freq;


// ============================ Supply Synchronization (Current Phase) ================================

    //-----------------------------------------------------
    //  QSG based PLL
    //-----------------------------------------------------
    //  Connect inputs of the PARK module (Used for PLL_QSG)
    //  and call the park transformation macro
        Pll_QSG_Park1.Alpha      = VsQSG3.Alpha;
        Pll_QSG_Park1.Beta       = VsQSG3.Beta;
        Pll_QSG_Park1.Sine       = Pll_QSG_Osc1.Sine;
        Pll_QSG_Park1.Cosine     = Pll_QSG_Osc1.Cosine;

        PPARK_MACRO(Pll_QSG_Park1);

    //  Connect inputs of the PI module (Used for PLL_QSG)
    //  and call the PI macro
        Pll_QSG_PI1.i.Fdb        = (-Pll_QSG_Park1.Ds);

        Pll_QSG_PI1.p.Enable     = VsSyncEnable;
        RECPI_MACRO(Pll_QSG_PI1)

    //  Connect inputs of the PLL_QSG_OSC module call the PLL_QSG_OSC macro
        Pll_QSG_Osc1.w_err       = Pll_QSG_PI1.o.Out;
        PLL_QSG_OSC_MACRO(Pll_QSG_Osc1)
        IsPhase = Pll_QSG_Osc1.Phase;
        IsFreq =  Pll_QSG_Osc1.Freq;


        PhaseDiff= VsPhase-IsPhase;
        PowerFactorFP_s= cos(PhaseDiff);

       if(PhaseDiff < 0)
           {
           PGUREC_RCTL_REG.bit.CapacitivePF = 1;
           PGUREC_RCTL_REG.bit.InductivePF = 0;
           Capacitive_Power = ApparentP_p.Power * PowerFactorFP_s;
           Inductive_Power  =0.0;
           }
       else if (PhaseDiff > 0)
           {
           PGUREC_RCTL_REG.bit.CapacitivePF = 0;
           PGUREC_RCTL_REG.bit.InductivePF = 1;
           Capacitive_Power = 0.0;
           Inductive_Power  = ApparentP_p.Power * PowerFactorFP_s;
           }
       else
           {
           PGUREC_RCTL_REG.bit.CapacitivePF = 0;
           PGUREC_RCTL_REG.bit.InductivePF = 0;
           Capacitive_Power = 0.0;
           Inductive_Power  = 0.0;
           }


//  //-----------------------------------------------------
//  //  Least-Square Estimation based PLL
//  //-----------------------------------------------------
//  //  Connect inputs of the PLL_LS module call the PLL_LS macro
//      Pll_Ls.In               =   PGU_1PHRectFdbHs.Vs;// 420;l*100;VsQSG.Alpha;l*200;//
//      Pll_Ls.PIcOut           =   Pll_Ls_PI.o.Out;
//
//      PLL_LS_MACRO(Pll_Ls)
//
//  //  Connect inputs of the PI module (Used for PLL_Ls)
//  //  and call the PI macro
//      Pll_Ls_PI.i.Fdb     = -Pll_Ls.Phierr;
//
//      Pll_Ls_PI.p.Enable  = VsSyncEnable;
//      RECPI_MACRO(Pll_Ls_PI);


// -------------------------------------------------------------
//  Supply Voltage Estimation
// -------------------------------------------------------------
//  Error in pu between Pll_QSG and Pll_Ls reference sine values
    //Vs.ErrPll1_2pu = Pll_QSG_Osc.Sine - Pll_Ls.Sine;

    Vs.Est      = Pll_QSG_Osc.Sine  *   Vspeak.Peak;//Pll_Ls.Peak * Pll_Ls.Sine;
    Vs.EstFF    = sin(Pll_QSG_Osc.Phase + FF_THETA) * Vspeak.Peak;
    Vs.EstErr   = Volt_LabGiris    -     Vs.Est;

// -------------------------------------------------------------
//  Synchronization control
// -------------------------------------------------------------
//  Connect inputs of the SYNC module call the SYNC macro
    Sync.Error  = Vs.EstErr;
    Sync.Enable = VsSyncEnable;
    SYNC_MACRO(Sync)
    SyncOK = Sync.Sync;

    if(SyncOK==0 && SyncOKd == 1)
    {
        PGUREC_FLT_REG.bit.VSSYNC = 1;
        PGUREC_CTL_REG.bit.STATE   = 14;       // Rectifier kontrol hata verdi
    }
    SyncOKd = SyncOK;


//  Connect inputs of the ZEROCROSS module call the ZEROCROSS macro
    Zcross.Vin   = VsQSG1.Alpha;

    Zcross.Enable = SyncOK;
    ZEROCROSS_MACRO(Zcross)
    ZC_Flag = Zcross.zc_flag;

// -------------------------------------------------------------
//  Supply Frequency Estimation
// -------------------------------------------------------------
//  Connect inputs of the FLL module call the FLL macro
    Fll.QSG_Err     = VsQSG2.Err_a;
    Fll.QSG_Beta    = VsQSG2.Beta;
    Fll.VsPeak      = Vspeak.Peak;

    Fll.Enable = VsSyncEnable;
    FLL_MACRO(Fll)

    wLPF= 314.159; //LPF(Fll.w, wLPF, 2*PI*5*PGUREC_TS_MAINISR);

// ===================================== Average calculations =====================================
   SupplyMean.Counter++;               // Averaging counter
   SupplyMean.PeakSum  += Vspeak.Peak; //Pll_Ls.Peak;
   SupplyMean.FreqSum  += wLPF * 0.159154943091895;
   SupplyMean.HarmSum  += fabs(Vs.Harm);

// ========================================= Control Loops =========================================

    if(PGUREC_ControlTicker==1)
    {
        PGUREC_TivaLifeCheck(43);
    }

    if(PGUREC_ControlTicker==2)
    {
                PGUREC_CommandRead();
                PGUREC_CommandProcess();
    }


    if(PGUREC_ControlTicker==3)
    {
        PGUREC_Protection();
        ContacRoutine();
        if(PRECHCTL_REG1.bit.STATUS==3 && Prech1==1)
                {
                      PGU_PreChargeRoutine1();
                }

        if(PRECHCTL_REG2.bit.STATUS==3 && Prech2==1)
                {
                      PGU_PreChargeRoutine2();
                }
//        PGUREC_ControlTicker = 0;

    }


    if(((float32)EPwm1Regs.TBCTR < (0.09)*(float32)EPwm1Regs.TBPRD && EPwm1Regs.TBSTS.bit.CTRDIR==1)
            ||((float32)EPwm1Regs.TBCTR>(0.91)*(float32)EPwm1Regs.TBPRD && EPwm1Regs.TBSTS.bit.CTRDIR==0))
        {
            Rec1_ISR();
            PGUREC_ControlTicker = 0;
        }

// ===================================== Duty Update =====================================

    PGUREC_VdcUpdateScale = (PGU_1PHRectFdb.Volt_DCLink/(Dc.Vdc_Est));
    PGUREC_VdcUpdateScale = sat(1.00  , 1.020 ,0.980);//sat(PGUREC_VdcUpdateScale  , 1.020 ,0.980);
//////        FillAnalogBuffer( Sync.Error,   AnaBuff.buff1, 1);
////          FillAnalogBuffer( PGUREC_Measure.Result.Cur_MotInput3,   AnaBuff.buff2, 2);
////          FillAnalogBuffer(PGU_Measure.Result.Cur_RectInput1,   AnaBuff.buff3, 3);
//////        FillAnalogBuffer(Vs.Est,   AnaBuff.buff4, 4);
////        FillAnalogBuffer(Volt_LabGiris,   AnaBuff.buff5, 5);
//////        FillAnalogBuffer(PGUREC_Measure.Result.Cur_MotInput3,   AnaBuff.buff6, 6);
//////        FillAnalogBuffer(PGUREC_Measure.Result.Cur_RectInput1,   AnaBuff.buff9, 9);
//////        FillAnalogBuffer(PGUREC_Measure.ChValue.Cur_RectInput1,   AnaBuff.buff10, 10);
//        FillAnalogBuffer(Pll_QSG_Osc.Sine,   AnaBuff.buff12, 12);
//        FillAnalogBuffer(sin(VsPhase), AnaBuff.buff13, 13);
//
//    FillAnalogBuffer(- PGUREC_Measure.Result.Cur_RectInput1,   AnaBuff.buff1, 1);
//    FillAnalogBuffer(PGU_1PHRectFdb.Cur_RectInput1,   AnaBuff.buff2, 2);
//    FillAnalogBuffer(PGU_1PHRectFdbHs.Cur_RectInput1,           AnaBuff.buff3, 3);
//    FillAnalogBuffer(Volt_LabGiris,                     AnaBuff.buff4, 4);
//    FillAnalogBuffer(VsQSG1.Alpha,                              AnaBuff.buff5, 5);

//
        if (PGUREC_MasterContrStat==2)
          {
            if(PGUREC_FLT_REG.all == 0)
            {
                FillAnalogBuffer(Pll_QSG_Osc.Sine, AnaBuff.buff14, 14);
                FillAnalogBuffer(Volt_LabGiris,   AnaBuff.buff15, 15);
                FillAnalogBuffer(-PGUREC_Measure.Result.Cur_RectInput1,   AnaBuff.buff16, 16);
            }
          }


        if(AnahtarlamaBaslat_REC == 1)
        {
            PGUREC_MasterContrStat=2;
        }
        else
        {
            PGUREC_MasterContrStat=3;
        }

        if (AnahtarlamaBaslat_REC != 1)
        {
            if(GerilimsizAnahtarlama==1 && PGUREC_Measure.Result.Volt_DCLink < 20 && (!MCAUX_REG1.bit.STATUS) && (!MCAUX_REG2.bit.STATUS) && MC1_Status && MC2_Status )
                {
                  PGURecGateON
                  FOIOGateON
                  AnahtarlamaBasladi = 1;
                }
            else if (AnahtarlamaBasladi == 1)
                {
                  FOIOGateOFF
                  PGUGateOFF
                  AnahtarlamaBasladi = 2;
                }
        }


        // Rectifier-1 Output Generation
        PGUREC1_PWM1.MfuncC      =  CLAMP(PGUREC1_PWM1.MfuncC*PGUREC_VdcUpdateScale,REC_DUTY_MIN,REC_DUTY_MAX);
        PGUREC1_PWM2.MfuncC      = -PGUREC1_PWM1.MfuncC;
        PWMDutyUpdate(PGUREC_1_PWM1,PGUREC1_PWM1.MfuncC);
        PWMDutyUpdate(PGUREC_1_PWM2,PGUREC1_PWM2.MfuncC);

        // Rectifier-2 Output Generation
        PGUREC2_PWM1.MfuncC     =  CLAMP(PGUREC2_PWM1.MfuncC*PGUREC_VdcUpdateScale,REC_DUTY_MIN,REC_DUTY_MAX);
        PGUREC2_PWM2.MfuncC      = -PGUREC2_PWM1.MfuncC;
        PWMDutyUpdate(PGUREC_2_PWM1,PGUREC2_PWM1.MfuncC);
        PWMDutyUpdate(PGUREC_2_PWM2,PGUREC2_PWM2.MfuncC);


	}
	else
	{
		if(PGUREC_ADCOffsetCntr < PGUREC_ADCOffsetPRD)
		{
            PGUREC_ADC_CHANNEL_READ(PGUREC_Measure)

		    PGUREC_ADC_OFFSET_COMP(PGUREC_Measure,0.0)	   // ADC offset compensation macro
		    PGUREC_ADCOffsetCntr++;					       // Increase sample counter
			PGUREC_ControlEnable = 0;
		}
		else
		{
			if(PGUREC_ADCOffsetCntr == PGUREC_ADCOffsetPRD)
			{
				PGUREC_ControlEnable = 1;

				PGUREC_ADC_OFFSET_COMP(PGUREC_Measure,(1.0/PGUREC_ADCOffsetPRD))
				PGUREC_ADCOffsetCntr = 1+PGUREC_ADCOffsetPRD;

//				Uint16 i = 0;
//				for(i=0 ;i<PGUREC_ADCChNUM;i++)
//				{
//					if(fabs(*((&PGUREC_Measure.Offset.Cur_RectInput1)+ i))>(*((&PGUREC_ADCOffsets.Cur_RectInput1)+ i)))
//					{
//					    PGUREC_ADCErrFlags.all |= (1<<i);
//
//					}
//				}
				if(fabs(*(&PGUREC_Measure.Offset.Cur_RectInput1))>(*(&PGUREC_ADCOffsets.Cur_RectInput1)))
                PGUREC_ADCErrFlags.bit.Cur_RectInput1= 1;
                if(fabs(*(&PGUREC_Measure.Offset.Cur_RectInput2))>(*(&PGUREC_ADCOffsets.Cur_RectInput2)))
                PGUREC_ADCErrFlags.bit.Cur_RectInput2= 1;
                if(fabs(*(&PGUREC_Measure.Offset.Volt_Grid))>(*(&PGUREC_ADCOffsets.Volt_Grid)))
                PGUREC_ADCErrFlags.bit.Volt_Grid= 1;
                if(fabs(*(&PGUREC_Measure.Offset.Volt_Catenary))>(*(&PGUREC_ADCOffsets.Volt_Catenary)))
                PGUREC_ADCErrFlags.bit.Volt_Catenary= 1;
                if(fabs(*(&PGUREC_Measure.Offset.Volt_DCLink))>(*(&PGUREC_ADCOffsets.Volt_DCLink)))
                PGUREC_ADCErrFlags.bit.Volt_DCLink= 1;

				if(PGUREC_ADCErrFlags.all > 0)
				{
				    PGUREC_FLT_REG.bit.ADC = 1 ;
				}
			}
		}
	}

 	 if(EPwm5Regs.TBSTS.bit.CTRDIR==0)
 	 {
 	    PGUREC_MainIsrFinishTime = (1.0+(float32)EPwm5Regs.TBCTR /(float32)EPwm5Regs.TBPRD)* 0.5 *PGUREC_TS_MAINISR * 1000000.0; //Microsecond
 	 }
 	 else
 	 {
 	    PGUREC_MainIsrFinishTime = ((float32)EPwm5Regs.TBCTR /(float32)EPwm5Regs.TBPRD)* 0.5 *PGUREC_TS_MAINISR * 1000000.0; //Microsecond
 	 }


 	PGUREC_MainIsrTotalTime = PGUREC_MainIsrFinishTime - PGUREC_MainIsrStartTime;

	 // Reinitialize for next ADC sequence
  	 AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;         // Reset SEQ1
   	 AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;       // Clear INT SEQ1 bit
  	 PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE
}

void PGUREC_ProtectionInit(void)
{

    TORQLIM_REG.bit.TOTAL       = 1;
    TORQLIM_REG.bit.INPOW       = 1;
    TORQLIM_REG.bit.TEMP        = 1;
    TORQLIM_REG.bit.SUPPLYH     = 1;
    TORQLIM_REG.bit.MOTSPEED    = 1;

    /*--------------------------------------------------------------------------
        Hardware_Protection module initialization
    ---------------------------------------------------------------------------*/

	PGUREC_HWProtLevels.VDCA1ErrVoltage         = 2000.0; // Hardware Fault Limit of the DC Link Maximum Voltage
	PGUREC_HWProtLevels.RICC1ErrVoltage         = 600.0; // Hardware Fault Limit of the DC Link Maximum Voltage
	PGUREC_HWProtLevels.RICC2ErrVoltage         = 600.0; // Hardware Fault Limit of the Rectifier Maximum Input Current
	PGUREC_HWProtLevels.COVErrVoltage           = 1250.0;  // Giriþe baðlanan DVM2000 limiti, Hardware Fault Limit of the Catenary Maximum Voltage

	/*--------------------------------------------------------------------------
		Software_Protection module initialization
	---------------------------------------------------------------------------*/

	//  Catenary Check

    PGUREC_SWProtErrLimitsCatenary.VsOV         = 1220.0;                  //     Supply Over Voltage Error Limit  (29 kV)
    PGUREC_SWProtErrLimitsCatenary.VsLV         = 800.0;                   //     Supply Over Voltage Error Limit  (19 kV)
    PGUREC_SWProtErrLimitsCatenary.VsWave       = Supply.Harm * 0.5;       //     Supply voltage waveform fault error Limit
    PGUREC_SWProtErrLimitsCatenary.VsOFreq      = 51.0;                    //     Supply voltage over frequency error limit
    PGUREC_SWProtErrLimitsCatenary.VsLFreq      = 49.0;                    //     Supply voltage low frequency error limit
    PGUREC_SWProtErrLimitsCatenary.Vs_Low_PF    = 0.95;                    //     Supply voltage low power factor error limit

    PGUREC_SWProtErrTimeCatenary.VsOV          = (Uint16)(100.0  /  (PGUREC_TS_SW*1000));
    PGUREC_SWProtErrTimeCatenary.VsLV          = (Uint16)(100.0  /  (PGUREC_TS_SW*1000));
    PGUREC_SWProtErrTimeCatenary.VsWave        = (Uint16)(200.0  /  (PGUREC_TS_SW*1000));
    PGUREC_SWProtErrTimeCatenary.VsOFreq       = (Uint16)(200.0  /  (PGUREC_TS_SW*1000));
    PGUREC_SWProtErrTimeCatenary.VsLFreq       = (Uint16)(3000.0 /  (PGUREC_TS_SW*1000));
    PGUREC_SWProtErrTimeCatenary.Vs_Low_PF     = (Uint16)(400.0  /  (PGUREC_TS_SW*1000));


    PGUREC_SWProtWarnLimitsCatenary.VsOV       = 1155.0;     // (27.5 kV)
    PGUREC_SWProtWarnLimitsCatenary.VsLV       = 945.0;      // (22.5 kV)
    PGUREC_SWProtWarnLimitsCatenary.VsWave     = Supply.Harm * 0.3;
    PGUREC_SWProtWarnLimitsCatenary.VsOFreq    = 50.5;
    PGUREC_SWProtWarnLimitsCatenary.VsLFreq    = 49.5;
    PGUREC_SWProtWarnLimitsCatenary.Vs_Low_PF  = 0.97;

    //  Converter Check
    PGUREC_SWProtErrLimits.Is1OC                = 450.0;         //     Secondary Over Current Error Limit
    PGUREC_SWProtErrLimits.Is2OC                = 200.0;         //     Secondary Over Current Error Limit
    PGUREC_SWProtErrLimits.Rec1OL               = 500.0;        //     Rectifier Over Load (kVA) Error Limit
    PGUREC_SWProtErrLimits.Rec2OL               = 500.0;        //     Rectifier Over Load (kVA) Error Limit
    PGUREC_SWProtErrLimits.VdcOV                = 2000.0; //1000.0;       //     DC voltage Over Error Limit
    PGUREC_SWProtErrLimits.VdcLV                = 500.0;//1000.0;         //     DC voltage Low Error Limit
    PGUREC_SWProtErrLimits.Is_Unbalanced        = 450.0;        //     DC voltage Sensor Fault Error Limit


    PGUREC_SWProtErrTime.Is1OC                  = (Uint16)(200.0   / (PGUREC_TS_SW*1000));
	PGUREC_SWProtErrTime.Is2OC 	                = (Uint16)(200.0   / (PGUREC_TS_SW*1000));
	PGUREC_SWProtErrTime.Rec1OL                 = (Uint16)(200.0   / (PGUREC_TS_SW*1000));
    PGUREC_SWProtErrTime.Rec2OL                 = (Uint16)(200.0   / (PGUREC_TS_SW*1000));
	PGUREC_SWProtErrTime.VdcOV                  = (Uint16)(100.0   / (PGUREC_TS_SW*1000));
	PGUREC_SWProtErrTime.VdcLV                  = (Uint16)(100.0   / (PGUREC_TS_SW*1000));
	PGUREC_SWProtErrTime.Is_Unbalanced          = (Uint16)(200.0   / (PGUREC_TS_SW*1000));


    PGUREC_SWProtWarnLimits.Is1OC               = 450.0;
	PGUREC_SWProtWarnLimits.Is2OC               = 450.0;
	PGUREC_SWProtWarnLimits.Rec1OL              = 450.0;
    PGUREC_SWProtWarnLimits.Rec2OL              = 450.0;
	PGUREC_SWProtWarnLimits.VdcOV               = 1950.0;
	PGUREC_SWProtWarnLimits.VdcLV               = 1300.0;
	PGUREC_SWProtWarnLimits.Is_Unbalanced       = 50.0;


    //  Temperature & Cooling Check- CKU1 (Humidity-Temperature Active)

	PGUREC_TempErrLimits_CKU1.RectifierTemp1        = 85.0;
	PGUREC_TempErrLimits_CKU1.RectifierTemp2        = 85.0;
    PGUREC_TempErrLimits_CKU1.CabinTemp             = 80.0;
    PGUREC_TempErrLimits_CKU1.ConvHumidity_Temp     = 80.0;     // (E+E Elektronik) Measuring range, temperature            -40 … 80 °C
    PGUREC_TempErrLimits_CKU1.ConvHumidity_Hum      = 95.0;     // (E+E Elektronik) Measuring range, relative humidity(RH)  0...100 % RH
    PGUREC_TempErrLimits_CKU1.MotorTemp1            = 300.0;
    PGUREC_TempErrLimits_CKU1.MotorTemp2            = 300.0;
    PGUREC_TempErrLimits_CKU1.MotorTemp3            = 2300.0;
    PGUREC_TempErrLimits_CKU1.GearTemp              = 300.0;

    PGUREC_TempWarnLimits_CKU1.RectifierTemp1        = 75.0;
	PGUREC_TempWarnLimits_CKU1.RectifierTemp2        = 75.0;
    PGUREC_TempWarnLimits_CKU1.CabinTemp             = 75.0;
    PGUREC_TempWarnLimits_CKU1.ConvHumidity_Temp     = 75.0;     // (E+E Elektronik) Measuring range, temperature            -40 … 80 °C
    PGUREC_TempWarnLimits_CKU1.ConvHumidity_Hum      = 85.0;     // (E+E Elektronik) Measuring range, relative humidity(RH)  0...100 % RH
    PGUREC_TempWarnLimits_CKU1.MotorTemp1            = 200.0;
    PGUREC_TempWarnLimits_CKU1.MotorTemp2            = 200.0;
    PGUREC_TempWarnLimits_CKU1.MotorTemp3            = 200.0;
    PGUREC_TempWarnLimits_CKU1.GearTemp              = 120.0;

    //  Temperature & Cooling Check- CKU2  (Flow-Temperature Active)

    PGUREC_TempErrLimits_CKU2.RectifierTemp1        = 85.0;
    PGUREC_TempErrLimits_CKU2.RectifierTemp2        = 85.0;
    PGUREC_TempErrLimits_CKU2.CabinTemp             = 80.0;
    PGUREC_TempErrLimits_CKU2.CoolingFlow_Temp      = 80.0;     // (E+E Elektronik) Measuring range, temperature            -40 … 80 °C
    PGUREC_TempErrLimits_CKU2.CoolingFlow_Flow      = 150.0;    // (E+E Elektronik) Measuring range, relative humidity(RH)  0...100 % RH
    PGUREC_TempErrLimits_CKU2.MotorTemp1            = 300.0;
    PGUREC_TempErrLimits_CKU2.MotorTemp2            = 300.0;
    PGUREC_TempErrLimits_CKU2.MotorTemp3            = 2300.0;
    PGUREC_TempErrLimits_CKU2.GearTemp              = 300.0;

    PGUREC_TempWarnLimits_CKU2.RectifierTemp1        = 75.0;
    PGUREC_TempWarnLimits_CKU2.RectifierTemp2        = 75.0;
    PGUREC_TempWarnLimits_CKU2.CabinTemp             = 75.0;
    PGUREC_TempWarnLimits_CKU2.CoolingFlow_Temp      = 75.0;     // (E+E Elektronik) Measuring range, temperature            -40 … 80 °C
    PGUREC_TempWarnLimits_CKU2.CoolingFlow_Flow      = 85.0;     // (E+E Elektronik) Measuring range, relative humidity(RH)  0...100 % RH
    PGUREC_TempWarnLimits_CKU2.MotorTemp1            = 200.0;
    PGUREC_TempWarnLimits_CKU2.MotorTemp2            = 200.0;
    PGUREC_TempWarnLimits_CKU2.MotorTemp3            = 200.0;
    PGUREC_TempWarnLimits_CKU2.GearTemp              = 120.0;


    PGUREC_FLT_REG.all			        = 0x0000;
	STestErrFlags.all	                = 0x0000;
	PGUREC_ADCErrFlags.all		        = 0x0000;
	PGUREC_SWProtErrFlags.all	        = 0x0000;
	PGUREC_SWProtCatenaryErrFlags.all   = 0x0000;
	PGUREC_TempErrFlags_CKU1.all	    = 0x0000;
    PGUREC_TempErrFlags_CKU2.all        = 0x0000;
	PGU_ContacErrFlags1.all             = 0x0000;
    PGU_ContacErrFlags2.all             = 0x0000;


	int ind;
    for(ind=0;ind<24;ind++)         // DualPort Ram Arýza bölgelerini temizleme
    {
        Faults[ind].all = 0;
    }
}

// Protection Routine
void PGUREC_Protection(void)
{
	// ====================================Protection==========================================

    PGUREC_SWProtFdbsCatenary.Vs               = PGUREC_VRecRMS.RMS;
    PGUREC_SWProtFdbsCatenary.VsWave           = Supply.Rms;
    PGUREC_SWProtFdbsCatenary.VsFreq           = VsFreq;
    PGUREC_SWProtFdbsCatenary.VsPowFac         = PowerFactorFP_s;  //PowerFactor_s

    PGUREC_SWProtFdbs.Is1                      = PGUREC_IRec1RMS.RMS;
    PGUREC_SWProtFdbs.Is2                      = PGUREC_IRec2RMS.RMS;
    PGUREC_SWProtFdbs.Rec1InPow                = 0.001 * ApparentP_s.Power; // kVA olarak koruma yapýldý.
    PGUREC_SWProtFdbs.Rec2InPow                = 0.001 * ApparentP_s.Power; // kVA olarak koruma yapýldý.
    PGUREC_SWProtFdbs.Vdc                      = PGUREC_Measure.Result.Volt_DCLink;
    PGUREC_SWProtFdbs.IsDiff                   = abs(PGUREC_IRec1RMS.RMS-PGUREC_IRec2RMS.RMS);

//    PGUREC_SWProtErrLimits.VdcLV       = Supply.Rms * (1.414*0.75);

// ====================================Catenary Operation Check ==========================================

// EN50163= The duration of voltage between Umax1 and Umax2 shall not exceed 5 min

//    if(PGUREC_VRecRMS.RMS>=1155 && PGUREC_VRecRMS.RMS<1220 )   // Katener geriliminin 27.5  ile 29 kV arasý olma durumu
//    {                                                        // EN50163 standartýna göre bu aralýkta mekanik trip olurken veya ED Fren durumunda
//        if(Catenary_High< CATENARY_HIGH_COUNT)
//        {
//            Catenary_High=Catenary_High+1.0;
//        }
//        else
//        {
//            Catenary_High_Warn=1;
//        }
//    }
//    else
//    {
//            Catenary_High = 0;
//            Catenary_High_Warn=0;
//    }
//
//// EN50163= The duration of voltage between Umin1 and Umin2 shall not exceed 5 min
//
//    if(PGUREC_VRecRMS.RMS>=800 && PGUREC_VRecRMS.RMS<945 )   // Katener geriliminin 19.0  ile 22.5 kV arasý olma durumu
//    {                                                        // EN50163 standartýna göre bu aralýkta mekanik trip olurken veya ED Fren durumunda
//        if(Catenary_Low< CATENARY_HIGH_COUNT)
//        {
//            Catenary_Low=Catenary_Low+1.0;
//        }
//        else
//        {
//            Catenary_Low_Warn=1;
//        }
//    }
//    else
//    {
//            Catenary_Low = 0;
//            Catenary_Low_Warn=0;
//    }
//
//    // ====================================Power Factor Protectýon ==========================================
//
//// NOT : (EN 50388)    Capacitive power factor
////  During traction mode and standstill, requirements for capacitive power factor in order to keep voltage within limits are:
////    – within the range of voltage from U min1 to U max1 as defined in EN 50163, capacitive power factors are not limited;
////    – within the range of voltage from U max1 to U max2 as defined in EN 50163, a train shall not behave like a capacitor
//
//    if (PGUREC_RCTL_REG.bit.PoweringMode == 1)      // Traction modda çalýþýrken
//    {
//         if(PGUREC_VRecRMS.RMS>=800 && PGUREC_VRecRMS.RMS<1155 )        // within the range of voltage from U min1 to U max1
//             {
//                 PGUREC_Torque.CapacitivePowLimFactor   = 1.0;                   // capacitive power factors are not limited;
//             }
//    }
//
//    if (PGUREC_RCTL_REG.bit.PoweringMode == 1)      // Traction modda çalýþýrken
//    {
//
//         if(PGUREC_MasterContr.ENABLE.bit.BRAKING==1 || PGUREC_MasterContr.ENABLE.bit.EMG_BRAKE==1)
//             {
//                 if (PGUREC_VRecRMS.RMS>=1155 && PGUREC_VRecRMS.RMS<1220 ) // within the range of voltage from U max1 to U max2
//                     {
//                         PGUREC_Torque.CapacitivePowLimFactor   = 0.0;                   // a train shall not behave like a capacitor
//                     }
//             }
//    }
//
////  During regenerative mode, capacitive power, if any, shall be limited to 150 kvar within the range of voltage from U min1 to U max1 as defined in EN 50163.
//
//    if (PGUREC_RCTL_REG.bit.RegenMode == 1 )      // Rejenatif modda çalýþýrken ve güc faktörü kapasitif iken
//    {
//        if(PGUREC_VRecRMS.RMS>=800 && PGUREC_VRecRMS.RMS<1155 )                       // Gerilim Umin1 ile Umax1 arasýnda iken
//        {
//
//        if (Capacitive_Power  >= 150.0 )                                    // Kapasitif güc 150 kVAR ile sýnýrlý ( Number of the traction unit: 4 )
//            {
//                PGUREC_Torque.CapacitivePowLimFactor   = 1.0 - (Capacitive_Power - 150.0)/(Capacitive_Power);
//            }
//        else
//            {
//                PGUREC_Torque.CapacitivePowLimFactor   = 1.0;
//            }
//        }
//
//    }
//
//    if (PGUREC_RCTL_REG.bit.PoweringMode == 1 )      // Traction modda çalýþýrken ve güc faktörü kapasitif iken
//       {
//           if (Capacitive_Power  >= 150.0 )                                    // Kapasitif güc 150 kVAR ile sýnýrlý ( Number of the traction unit: 4 )
//               {
//                   PGUREC_Torque.CapacitivePowLimFactor   = 1.0 - (Capacitive_Power - 150.0)/(Capacitive_Power);
//               }
//           else
//               {
//                   PGUREC_Torque.CapacitivePowLimFactor   = 1.0;
//               }
//        }
//
//// NOT : (EN 50388)    Inductive power factor
////   During regeneration, the inductive power factor may be allowed to decrease freely in order to keep voltage within limits.
//
//    if (PGUREC_RCTL_REG.bit.RegenMode == 1)      // Traction modda çalýþýrken
//    {
//             {
//                 PGUREC_Torque.InductivePowLimFactor   = 1.0;                   // ýnductive power factors are not limited;
//             }
//    }
//
//    if (PGUREC_RCTL_REG.bit.PoweringMode == 1 )      // Traction modda çalýþýrken ve güc faktörü kapasitif iken
//        {
//            if (Inductive_Power  >= 150.0 )                                    // Kapasitif güc 150 kVAR ile sýnýrlý ( Number of the traction unit: 4 )
//                {
//                    PGUREC_Torque.InductivePowLimFactor   = 1.0 - (Inductive_Power - 150.0)/(Inductive_Power);
//                }
//            else
//                {
//                    PGUREC_Torque.InductivePowLimFactor   = 1.0;
//                }
//         }


// Analog protection
	PGUREC_SWProtection(PGUREC_SWProtFdbs, 	PGUREC_SWProtWarnLimits,	PGUREC_SWProtErrLimits, &PGUREC_SWProtWarnFlags,	&PGUREC_SWProtErrFlags, &PGUREC_SWProtErrTime , &PGUREC_SWProtErrCount);
    PGUREC_SWProtectionCatenary(PGUREC_SWProtFdbsCatenary,  PGUREC_SWProtWarnLimitsCatenary,   PGUREC_SWProtErrLimitsCatenary, &PGUREC_SWProtCatenaryWarnFlags,  &PGUREC_SWProtCatenaryErrFlags, &PGUREC_SWProtErrTimeCatenary , &PGUREC_SWProtErrCountCatenary);

	if (PGUREC_SWProtErrFlags.all > 0) //  if (PGU_SWProtErrFlags.all > 0  ||  PGUREC_SWProtCatenaryErrFlags.all > 0)
	{
	    PGUREC_FLT_REG.bit.SWPROT   = 1; 	// Software fault
	}

//	if (PGUREC_SWProtCatenaryErrFlags.bit.VsLV || PGUREC_SWProtErrFlags.bit.IpOC )
//	    {
//	        IO_SET(PGUREC_MCBTrip);   // Catenary low voltage fault (16.5 kV) ----> TCPU opens MCB
//	    }

// Temperature protection
	if (PGUREC_CKU1 == 1  &&  PGUREC_CKU2 == 0 )   // NOT= DEGRADED MODA ALINACAK
	    {

	    PGUREC_TemperatureProtection1(PGUREC_TemperatureLPF_CKU1,   PGUREC_TempWarnLimits_CKU1,   PGUREC_TempErrLimits_CKU1, &PGUREC_TempWarnFlags_CKU1, &PGUREC_TempErrFlags_CKU1);
	        if (PGUREC_TempErrFlags_CKU1.all > 0)   // NOT= DEGRADED MODA ALINACAK
	            {
	                PGUREC_FLT_REG.bit.TEMP   = 1;     // Temperature fault
	            }
	    }

    if (PGUREC_CKU2 == 1 &&  PGUREC_CKU1 == 0)   // NOT= DEGRADED MODA ALINACAK
        {
            PGUREC_TemperatureProtection2(PGUREC_TemperatureLPF_CKU2,   PGUREC_TempWarnLimits_CKU2,   PGUREC_TempErrLimits_CKU2, &PGUREC_TempWarnFlags_CKU2, &PGUREC_TempErrFlags_CKU2);
            if (PGUREC_TempErrFlags_CKU2.all > 0)   // NOT= DEGRADED MODA ALINACAK
                {
                    PGUREC_FLT_REG.bit.TEMP   = 1;     // Temperature fault
                }
        }



	// Contactor protection
	if ((PGU_ContacErrFlags1.all > 0) && (PGU_ContacErrFlags2.all > 0))
	{
	    PGUREC_FLT_REG.bit.CONTAC   = 1;   // Contactor fault
	}

// Self test error
	if (STestErrFlags.all > 0)
	{
	    PGUREC_FLT_REG.bit.STEST  = 1; 	// Self Test fault
	}

// Hardware fault
	if((!IO_READ(PGUREC_TZ1GPIO))||(!IO_READ(PGUREC_TZ2GPIO)))   //HW hata oluþursa
	{
	    PGUREC_FLT_REG.bit.HWPROT  = 1; 	// Hardware fault
	}


	if (PGUREC_FLT_REG.all > 0)
	{
	    PGUREC_RCTL_REG.bit.Enable	 = 0;
        PRECHCTL_REG1.bit.STATUS  = 0;           // Precharge-1 initial status
        PRECHCTL_REG2.bit.STATUS  = 0;           // PreCharge-2 initial status

        PGUGateOFF
		FOIOGateOFF

		PCC1_REG.bit.OPEN = 1;
//		IO_SET(PCCSig)
        PGUREC_TCPU_Outputs.bit.PCC1_SIG=1;     // Precharge Contactor-1 Opening with CAN Communication (PGU-TCPU pin-to-pin signals are full)

        PCC2_REG.bit.OPEN = 1;
//        IO_SET(PCCSig)
        PGUREC_TCPU_Outputs.bit.PCC2_SIG=1;     // Precharge Contactor-2 Opening with CAN Communication (PGU-TCPU pin-to-pin signals are full)

		MCAUX_REG1.bit.OPEN = 1;
		IO_SET(MCSig1)

        MCAUX_REG2.bit.OPEN = 1;
        IO_SET(MCSig2)

		if( PGUREC_RCTL_REG.bit.CtrlState == 1)
		{
		    PGUREC_RCTL_REG.bit.CtrlState      = 2;    // Çalýþma sonrasýnda hata meydana geldi
		    PGUREC_CTL_REG.bit.STATE 		   = 12;   // Inverter koruma hata verdi
		}
		else if ( PGUREC_RCTL_REG.bit.CtrlState == 0)
		{
		    PGUREC_RCTL_REG.bit.CtrlState      = 3;	// Çalýþma öncesinde hata var
		}
	}
}



// Command Process Routine
void PGUREC_CommandProcess(void)
{

//----------    DC Link Discharge with reverser      ---------------//

//       if(PGUREC_MasterContr.REV_SW.bit.INITIAL==1)
//        {
//            if((!MCAUX_REG1.bit.STATUS) && (!MCAUX_REG2.bit.STATUS) && MC1_Status && MC2_Status)        // Ana kontaktör devrede deðil ise
//            {
//                IO_SET(OVPSig)          // Barayý boþaltmak için ovcrf yi kullan
//            }
//            else
//                {
//                    IO_CLR(OVPSig)
//                }
//        }
//        else
//            {
//                IO_CLR(OVPSig)
//            }


//----------    PGU_ERTMSBrake Check     ---------------//  // Aksiyon TCPU 'da alýnmayacaksa aktif edilecek

//   if(PGU_TeRefCAN != 0.0)
//   {
//       if(PGUREC_ERTMSBrake ==1)              // ERTMS Break Active  = 1
//       {
//           PGU_TeRefCAN = 0.0;
//           PGUGateOFF
//           FOIOGateOFF
//       }
//       else                                 // ERTMS Break Passive  = 0
//       {
//           PGU_TeRefCAN = ((fabs(PGU_TeRefCAN) - 400.0)/3600.0)*4000.0;    // 400-4000 Nm arasý referans 0-4000 Nm arasýna scale edildi.
//
//       }
//   }


//---------- 	PGU_TractInh Check   	 ---------------//   // Aksiyon TCPU 'da alýnmayacaksa aktif edilecek
//	if(PGU_TeRefCAN != 0.0)
//	{
//		if(PGUREC_TractInh==1)              // Traction Inhibit Passive  = 1
//		{
//
//            PGU_TeRefCAN = ((fabs(PGU_TeRefCAN) - 400.0)/3600.0)*4000.0;    // 400-4000 Nm arasý referans 0-4000 Nm arasýna scale edildi.
//
//		}
//		else                               // Traction Inhibit Active  = 0
//		{
//            PGU_TeRefCAN = 0.0;
//            PGUGateOFF
//                   FOIOGateOFF
//		}
//	}

////---------- 	Traction Null Check   	 ---------------//      // Aksiyon TCPU 'da alýnmayacaksa aktif edilecek
//	if(PGUREC_Trac_Null == 1)
//	{
//		if(PGUREC_MasterContr.MAIN_HAND.bit.BRAKING==1 || PGUREC_MasterContr.MAIN_HAND.bit.EMG_BRAKE==1)
//		{
//			PGU_TeRefCAN = 0.0;
//		}
//	}
//
//    PGUREC_MasterContr.TORQUEREF = fabs(PGU_TeRefCAN*(1/4000.0));


//----------    Converter ON - OFF Routine       ---------------//

    if(PGUREC_MasterContr.STA.bit.POWER_OFF==1)                    // Nötr pozisyonda beklenildi ve reverser yön deðiþtirdi.
    {
        PGUREC_CTL_REG.bit.POWER   = 0;                      // Anahtarlama durdurma sinyali uygulandý
    }


    if(PGUREC_MasterContr.REV_SW.bit.FORWARD==1)                   // Hareket kolu ileri yönde ise
    {
        PGUREC_CTL_REG.bit.ON = 1;                           // Konvertör devreye alma sinyali uygulandý

        if (PGUREC_MasterContr.ENABLE.bit.NEUTRAL==1)              // Cer Kolu Nötrde ise
        {
//            PGUREC_Torque.Ref = 0.0;                       // Çekiþ Referansý sýfýrlandý.
            PGUREC_CTL_REG.bit.POWER  = 0;
        }

        else if(PGUREC_MasterContr.ENABLE.bit.POWERING==1)         // Cer Kolu Güçte ise
        {
            PGUREC_CTL_REG.bit.POWER   = 1;                  // Anahtarlama baþlatma sinyali uygulandý
//            PGUREC_Torque.Ref = PGUREC_MasterContr.TORQUEREF;
        }
        else if (PGUREC_MasterContr.ENABLE.bit.BRAKING==1 || PGUREC_MasterContr.ENABLE.bit.EMG_BRAKE==1)          // Cer Kolu Frende ise
        {
            PGUREC_CTL_REG.bit.POWER   = 1;                  // Anahtarlama baþlatma sinyali uygulandý

//            if(Regen.SpeedRPM > Regen.SpeedRPMLim2)         // Rejeneratif fren sýnýrlandýrma gerekli mi?
//            {
////                PGUREC_Torque.Ref  = -PGUREC_MasterContr.TORQUEREF;
//            }
//            else if(Regen.SpeedRPM > Regen.SpeedRPMLim1)
//            {
//                Regen.LimFactor   = (Regen.SpeedRPM - Regen.SpeedRPMLim1)/(Regen.SpeedRPMLim2 - Regen.SpeedRPMLim1);
//                PGUREC_Torque.Ref          = -PGUREC_MasterContr.TORQUEREF * Regen.LimFactor; //
//            }
//            else
//            {
//                PGUREC_Torque.Ref = 0.0;                               // Referans sýfýrlandý.
//            }
        }
    }
    else if(PGUREC_MasterContr.REV_SW.bit.REVERSE==1)                          // Hareket kolu geri yönde ise
    {
        PGUREC_CTL_REG.bit.ON = 1;                                       // Konvertör devreye alma sinyali uygulandý

        if (PGUREC_MasterContr.ENABLE.bit.NEUTRAL==1)
        {
//            PGUREC_Torque.Ref = 0.0;                                   // Referans sýfýrlandý.
            PGUREC_CTL_REG.bit.POWER     = 0;                            // Anahtarlama durdurma sinyali uygulandý

        }
        else if(PGUREC_MasterContr.ENABLE.bit.POWERING==1)
        {
            PGUREC_CTL_REG.bit.POWER     = 1;                            // Anahtarlama baþlatma sinyali uygulandý
//            PGUREC_Torque.Ref          = -PGUREC_MasterContr.TORQUEREF;
        }
        else if (PGUREC_MasterContr.ENABLE.bit.BRAKING==1 || PGUREC_MasterContr.ENABLE.bit.EMG_BRAKE==1)
        {
            PGUREC_CTL_REG.bit.POWER   = 1;                            // Anahtarlama baþlatma sinyali uygulandý
//
//            if(Regen.SpeedRPM < -Regen.SpeedRPMLim2)            // Rejeneratif fren sýnýrlandýrma gerekli mi
//            {
//                PGUREC_Torque.Ref = PGUREC_MasterContr.TORQUEREF;
//            }
//            else if(Regen.SpeedRPM < -Regen.SpeedRPMLim1)
//            {
//                Regen.LimFactor   = (-Regen.SpeedRPM - Regen.SpeedRPMLim1)/(Regen.SpeedRPMLim2 - Regen.SpeedRPMLim1);
//                PGUREC_Torque.Ref          = PGUREC_MasterContr.TORQUEREF * Regen.LimFactor;  //
//            }
//            else
//            {
//                PGUREC_Torque.Ref = 0.0;   // Çekiþ referansý sýfýrlandý.
//            }
        }
    }
    else                                    // Hareket kolu baþlangýç ya da kapalý konumunda ise
    {
        PGUREC_CTL_REG.bit.ON      = 0;      // Konvertör devreden çýkarma sinyali uygulandý
        PGUREC_CTL_REG.bit.POWER   = 0;      // Anahtarlama durdurma sinyali uygulandý
//        PGUREC_Torque.Ref        = 0.0;    // Çekiþ referansý sýfýrlandý.
    }
//----------    Traction Reference Limiting    ---------------//

    PGUREC_Torque.TotalLimFactor =       PGUREC_Torque.SpeedLimFactor   * \
                                         PGUREC_Torque.TempLimFactor    * \
                                         PGUREC_Torque.VdcLimFactor * \
                                         PGUREC_Torque.SupplyHLimFactor * \
                                         PGUREC_Torque.SupplyLLimFactor * \
                                         PGUREC_Torque.InPowLimFactor;

    PGUREC_Torque.TotalLimFactor = CLAMP( PGUREC_Torque.TotalLimFactor , 0.0, 1.0);

	if (PGUREC_Torque.TotalLimFactor < 1.0)
	{
	    PGUREC_CTL_REG.bit.DEGRADED = 1;                            //  Sýcaklýk, gerilim vb durumlarda limitler aþýlýrsa kýsýtlanmýþ modda çalýþýr.
	}
	else
	{
	    PGUREC_CTL_REG.bit.DEGRADED = 0;
	}

	if(TORQLIM_REG.bit.TOTAL == 1)
	{
	    PGUREC_Torque.RefLimited	= PGUREC_Torque.TotalLimFactor * PGUREC_Torque.Ref;

	}
	else
	{
	    PGUREC_Torque.RefLimited	= PGUREC_Torque.Ref;
	}

//---------- 	Converter start flag set  	 ---------------//

	if((PGUREC_CTL_REG.bit.ON==1)&&(PGUREC_CTL_REG.bit.ENABLE==1)&&(PGUREC_CTL_REG.bit.STATE==0))
	{
	    PGUREC_CTL_REG.bit.START = 1;
	}
	else
	{
	    PGUREC_CTL_REG.bit.START = 0;
	}

//---------- 	Converter stop flag set  	 ---------------//
	if((PGUREC_CTL_REG.bit.ON==0)&&(PGUREC_CTL_REG.bit.STATE > 0))
	{
	    PGUREC_CTL_REG.bit.STOP = 1;
	}
	else
	{
	    PGUREC_CTL_REG.bit.STOP = 0;
	}

//---------- 	Converter pause flag set  	 ---------------//
    if(PGUREC_CTL_REG.bit.STATE==6 && (PGUREC_CTL_REG.bit.POWER == 0))
    {
        PGUREC_CTL_REG.bit.PAUSE =1;
	}
	else
	{
	    PGUREC_CTL_REG.bit.PAUSE =0;
	}

//---------- 	Converter start-stop operation  	 ---------------//

	if(PGUREC_CTL_REG.bit.POWER == 1)
	{
		if(PGUREC_CTL_REG.bit.STATE==3)
		{
		    PGUREC_CTL_REG.bit.STATE = 4; // PreCharge tamamlandý Rectifier kontrol baslatma durumuna gecildi
		}
		else if(PGUREC_CTL_REG.bit.STATE==9)
		{
		    PGUREC_CTL_REG.bit.RESET =1;
		    PGUREC_CTL_REG.bit.STATE =4;
		}
	}


//---------- 	Converter start operation  	 ---------------//
	if(	PGUREC_CTL_REG.bit.START == 1)
	{	PGUREC_CTL_REG.bit.START = 0;					// Baslama isareti temizlendi

		if(PGUREC_CTL_REG.bit.OPMODE==0)
		{
		    PGUREC_CTL_REG.bit.RESET	= 1;

		    PGUREC_CTL_REG.bit.STATE   = 1;            // Baslangic reset ve hata temizleme durumuna gecildi

			if ((!MCAUX_REG1.bit.STATUS && MC1_Status) || (!MCAUX_REG2.bit.STATUS && MC2_Status))
			{
				PGUREC_CTL_REG.bit.STATE	= 1;			// Baslangic reset ve hata temizleme durumuna gecildi
			}
			else
			{
				PGUREC_CTL_REG.bit.STATE	= 3;			// Ana kontaktör devrede durumu
			}
		}
	}


//---------- 	Converter Pause operation  	 ---------------//
	if( PGUREC_CTL_REG.bit.PAUSE==1 )
	{	PGUREC_CTL_REG.bit.PAUSE= 0;

	    PGUREC_CTL_REG.bit.STATE 		= 9;		// Pause state
	    PGUREC_CTL_REG.bit.OPMODE		= 0;
	    PGUREC_RCTL_REG.bit.Enable   	= 0;

	    PGUGateOFF
		FOIOGateOFF
	}


	if(PGUREC_CTL_REG.bit.STATE==9 )
	{
	    if((!IO_READ(PGUREC_TZ1GPIO))||(!IO_READ(PGUREC_TZ2GPIO)))    // Gate off durumunda HW hata oluþursa
        {
            PGUREC_FLT_REG.bit.HWPROT  = 1;        // Hardware fault
            PGUREC_CTL_REG.bit.STATE   = 15;       // Hardware Hata durumu
            PGUREC_RCTL_REG.bit.Enable = 0;

            PGUGateOFF
            FOIOGateOFF

            PCC1_REG.bit.OPEN = 1;       // Precharge kontaktörü açma sinyali uygulandý
//            PGU_IO_CLR(PCCSig)
            PGUREC_TCPU_Outputs.bit.PCC1_SIG=1;

            PCC2_REG.bit.OPEN = 1;       // Precharge kontaktörü açma sinyali uygulandý
//            PGU_IO_CLR(PCCSig)
            PGUREC_TCPU_Outputs.bit.PCC2_SIG=1;


            MCAUX_REG1.bit.OPEN = 1;        // Ana kontaktörü açma sinyali uygulandý
            IO_SET(MCSig1)

            MCAUX_REG2.bit.OPEN = 1;        // Ana kontaktörü açma sinyali uygulandý
            IO_SET(MCSig2)
        }
		if(PGUREC_FLT_REG.bit.HWPROT  == 1)
		{
		    PGUREC_CTL_REG.bit.STATE 	= 15;		// Hardware Hata durumu
		}
	}

//----------    Converter stop operation     ---------------//
	    if( PGUREC_CTL_REG.bit.STOP ==1 )
	    {   PGUREC_CTL_REG.bit.STOP = 0;

	        PGUREC_CTL_REG.bit.STATE       = 0;
	        PGUREC_CTL_REG.bit.OPMODE      = 0;
	        PGUREC_RCTL_REG.bit.Enable   = 0;

	        PRECHCTL_REG1.bit.STATUS  = 0;           // PreCharge baþlangýç durumunda, kontaktörler açýk
            PRECHCTL_REG2.bit.STATUS  = 0;           // PreCharge baþlangýç durumunda, kontaktörler açýk


            PGUGateOFF
            FOIOGateOFF


	      PCC1_REG.bit.OPEN = 1;       // Precharge kontaktörü açma sinyali uygulandý
//	      PGU_IO_SET(PCCSig)
	      PGUREC_TCPU_Outputs.bit.PCC1_SIG=1;


	      PCC2_REG.bit.OPEN = 1;       // Precharge kontaktörü açma sinyali uygulandý
//	      PGU_IO_SET(PCCSig)
	      PGUREC_TCPU_Outputs.bit.PCC2_SIG=1;


	      MCAUX_REG1.bit.OPEN = 1;        // Ana kontaktörü açma sinyali uygulandý
	      IO_SET(MCSig1)

	      MCAUX_REG2.bit.OPEN = 1;        // Ana kontaktörü açma sinyali uygulandý
	      IO_SET(MCSig2)
	    }


//---------- 	Converter Precharge start flag set ---------------//

	    if(PGUREC_CTL_REG.bit.STATE == 2)
	    {
	        if(PRECHCTL_REG1.bit.STATUS<3)
	        {
	            PRECHCTL_REG1.bit.START = 1;
	        }

	        if(PRECHCTL_REG2.bit.STATUS<3)
	        {
	            PRECHCTL_REG2.bit.START = 1;
	        }
	    }

//---------- 	Converter Reset operation  	 ---------------//

	if(PGUREC_CTL_REG.bit.RESET == 1)
	{
		PGUREC_FaultFlagsClear = 1;				// Hata bayraklarý temizleme isareti set edildi
		PGUREC_FPGAsReset		= 1;				// Fiber kartlar reset isareti set edildi
		PGUREC_TripZoneClear			= 1;				// PWM TRIP temizleme isareti set edildi

		PGUREC_CTL_REG.bit.OPMODE	= 0;
	}

	if(PGUREC_FaultReset==1)
	    {
	        PGUREC_FLT_REG.all          = 0x0000;
	    }



	if(PGUREC_FaultFlagsClear==1)
	{
	    PGUREC_FLT_REG.all			= 0x0000;
	    PGU_ContacErrFlags1.all    = 0x0000;
        PGU_ContacErrFlags2.all    = 0x0000;

	    PGUREC_SWProtErrFlags.all	= 0x0000;
	    PGUREC_SWProtCatenaryErrFlags.all  = 0x0000;
		PGUREC_TempErrFlags_CKU1.all	= 0x0000;
        PGUREC_TempErrFlags_CKU2.all   = 0x0000;

		if(STestErrFlags.all > 0)
		{
			PGUREC_SelfTestErrClear += 1;
			if(PGUREC_SelfTestErrClear>=1)
			{
			    STestErrFlags.all	= 0x0000;
			}
		}

		PGUREC_FaultFlagsClear = 2;
	}

	if (PGUREC_FPGAsReset==1)
	{
		PGUREC_FPGAsReset=2;						// Clear flag

		IO_SET(PGUREC_SGOFF)						// Apply software gate off signal
		DELAY_US(4);

		IO_SET(PGUREC_FOIORst)						// Apply FOIO reset signal
		DELAY_US(4);						// Minimum Delay 1us. It should be applied due to BP propagation delay.

		IO_SET(PGUREC_FDPCRst)						// Apply FDPC reset signal
		DELAY_US(4);						// Valid reset signal delay for FDPC

		IO_CLR(PGUREC_FDPCRst)						// Clear FDPC reset signal
		DELAY_US(4);						// Minimum Delay 2us. It should be applied due to BP propagation delay.

		IO_CLR(PGUREC_FOIORst)						// Clear FOIO reset signal
		DELAY_US(4);
	}

	if (PGUREC_TripZoneClear==1)
	{
		PGUREC_TripZoneClear = 2;						// Clear flag

		if(PGUREC_CTL_REG.bit.STATE==1)
		{
		    PGUREC_CTL_REG.bit.STATE = 2;			// Baslangic reset ve hata temizleme tamamlandi
		}

		FOIOGateOFF							// FOIO Software gate off
//		if(Prech1)
//		{
//		    PGURec2GateON
//		}
//		else if (Prech2)
//		{
//		    PGURec1GateON
//		}

		PGUREC_CTL_REG.bit.RESET = 2;
	}



	//----------    Converter Precharge operation-1    ---------------//
	    if(PRECHCTL_REG1.bit.START ==1)
	    {  PRECHCTL_REG1.bit.START = 0;

	        PreCh.Ticker1 = 0;

            if(PGUREC_FLT_REG.all == 0 && SyncOK == 1) //             if(PGUREC_FLT_REG.all == 0 && SyncOK == 0)
	        {
	            PreCh.DClimit           = sat(Supply.Rms*(1.414*0.8), 1250.0*(1.414) ,100.0*(1.414*0.80)); //sat(x,max,min)
	            PRECHCTL_REG1.bit.STATE  = 0;            // Precharge baþlangýç durumu
	            PRECHCTL_REG1.bit.STATUS = 3;            // PreCharge baþlatýldý, devam ediyor
	        }
	        else
	        {
	            PRECHCTL_REG1.bit.STATUS       = 1;            // PreCharge baþlatýlamadý
	            PGUREC_CTL_REG.bit.OPMODE      = 2;            // Hata var
	            PGUREC_CTL_REG.bit.STATE       = 10;           // PreCharge baslatilamadi
	        }
	    }



	    if(PRECHCTL_REG1.bit.STATUS == 4)
	    {

	        if ((!PCC1_REG.bit.STATUS)&&(!MCAUX_REG1.bit.STATUS) && MC1_Status)
	        {
	            PRECHCTL_REG1.bit.STATUS  = 0;           // PreCharge baþlangýç durumunda, kontaktörler açýk

	            if(PGUREC_FLT_REG.all == 0)            // Baþka hata durumu yok, sadece kontaktör sebebiyle
	            {
	                PGU_ContacErrFlags1.bit.CNTC_OP = 1; // Contactors opened

	            }
	        }

	        if(PRECHCTL_REG1.bit.STATE   == 5)
	        {
	            PGUREC_CTL_REG.bit.STATE = 3;        // Ana kontaktör devrede durumu
	            PRECHCTL_REG1.bit.STATE  = 6;        // Precharge basarili tamamlandi, konvertör aksiyon aldý durumu
	        }
	    }

	    //----------    Converter Precharge operation-2    ---------------//
	            if(PRECHCTL_REG2.bit.START ==1)
	            {  PRECHCTL_REG2.bit.START = 0;

	                PreCh.Ticker2 = 0;

	                if(PGUREC_FLT_REG.all == 0 && SyncOK == 1) //                   if(PGUREC_FLT_REG.all == 0 && SyncOK == 0)
	                {
	                    PreCh.DClimit           = sat(Supply.Rms*(1.414*0.80), 1250.0*(1.414) ,100.0*(1.414*0.80)); //sat(x,max,min)
	                    PRECHCTL_REG2.bit.STATE  = 0;            // Precharge baþlangýç durumu
	                    PRECHCTL_REG2.bit.STATUS = 3;            // PreCharge baþlatýldý, devam ediyor
	                }
	                else
	                {
	                    PRECHCTL_REG2.bit.STATUS       = 1;            // PreCharge baþlatýlamadý
	                    PGUREC_CTL_REG.bit.OPMODE      = 2;            // Hata var
	                    PGUREC_CTL_REG.bit.STATE       = 10;           // PreCharge baslatilamadi
	                }
	            }



	            if(PRECHCTL_REG2.bit.STATUS == 4)
	            {

	                if ((!PCC2_REG.bit.STATUS)&&(!MCAUX_REG2.bit.STATUS) && MC2_Status )
	                {
	                    PRECHCTL_REG2.bit.STATUS  = 0;           // PreCharge baþlangýç durumunda, kontaktörler açýk

	                    if(PGUREC_FLT_REG.all == 0)            // Baþka hata durumu yok, sadece kontaktör sebebiyle
	                    {
	                        PGU_ContacErrFlags2.bit.CNTC_OP = 1; // Contactors opened

	                    }
	                }

	                if(PRECHCTL_REG2.bit.STATE   == 5)
	                {
	                    PGUREC_CTL_REG.bit.STATE = 3;        // Ana kontaktör devrede durumu
	                    PRECHCTL_REG2.bit.STATE  = 6;        // Precharge basarili tamamlandi, konvertör aksiyon aldý durumu
	                }
	            }


// ------------------------------------------------------------------------------
//	Control start command check
// ------------------------------------------------------------------------------
	if(PGUREC_CTL_REG.bit.STATE==4 && PGUREC_FLT_REG.all == 0 && PGUREC_CTL_REG.bit.RESET == 2)
	{
	    PGUREC_RCTL_REG.bit.Enable 	= 1;
	    PGUREC_RCTL_REG.bit.CtrlStart  = 1;    // Rectifier kontrol baslatma isareti set edildi
	    Basarili = 1;

	}

// ------------------------------------------------------------------------------
//	ED_BRK check
// ------------------------------------------------------------------------------
	if(PGUREC_CTL_REG.bit.STATE==6)
	{
		if(PGUREC_MasterContr.MAIN_HAND.bit.BRAKING==1 || PGUREC_MasterContr.MAIN_HAND.bit.EMG_BRAKE==1)
		{
			PGUREC_EDBrakeActive = 1;
		}
		else
		{
			PGUREC_EDBrakeActive = 0;

		}
	}
	else
	{
		PGUREC_EDBrakeActive = 0;
	}



}

void ContacRoutine(void)
{

//    //------------------------------------------------------------------//
//    //----------  Earthing Switch Contactor Control Routine   ----------//
//    //------------------------------------------------------------------//
//        // Deþarj kontaktörü devrede deðil ise status=1
//        if(ESCStsOld !=  DIOC_Inputs_TCPU.bit.EarthSwitch)
//        {
//            ESCCount ++;
//            if(ESCCount >= 10)
//            {
//               Earth_Sw_REG.bit.STATUS = DIOC_Inputs_TCPU.bit.EarthSwitch;
//               ESCStsOld = Earth_Sw_REG.bit.STATUS;
//               ESCCount = 0;
//            }
//        }
//        else
//        {
//            ESCCount = 0;
//        }
//
//        if(Earth_Sw_REG.bit.STATUS)
//        {
//            PGU_ContacErrFlags1.bit.ESC_NO = 1;
//        }



    //------------------------------------------------------------------//
    //----------  Main Contactor Auxiliary Control Routine    ---------------//
    //------------------------------------------------------------------//
        if(MCStsOld_Aux1 !=  PGUREC_DIOC1_Inputs_TCPU.bit.MCAUX_STA1)
        {
            MCCount_Aux1 ++;
            if(MCCount_Aux1 >= 10)
            {
                MCAUX_REG1.bit.STATUS = PGUREC_DIOC1_Inputs_TCPU.bit.MCAUX_STA1;
                MCStsOld_Aux1 = MCAUX_REG1.bit.STATUS;
                MCCount_Aux1 = 0;
            }
        }
        else
        {
            MCCount_Aux1 = 0;
        }


        //------------------------------------------------------------------//
        //----------  Main Contactor Auxiliary Control Routine    ---------------//
        //------------------------------------------------------------------//
            if(MCStsOld_Aux2 !=  PGUREC_DIOC1_Inputs_TCPU.bit.MCAUX_STA2)
            {
                MCCount_Aux2 ++;
                if(MCCount_Aux2 >= 10)
                {
                    MCAUX_REG2.bit.STATUS = PGUREC_DIOC1_Inputs_TCPU.bit.MCAUX_STA2;
                    MCStsOld_Aux2 = MCAUX_REG2.bit.STATUS;
                    MCCount_Aux2 = 0;
                }
            }
            else
            {
                MCCount_Aux2 = 0;
            }



        //------------------------------------------------------------------//
        //----------  Main Contactor Control Routine    --------------------//
        //------------------------------------------------------------------//
            if(MCStsOld !=  IO_READ(MC1))
            {
                MCCount ++;
                if(MCCount >= 10)
                {
                    MC1_Status = IO_READ(MC1);
                    MCStsOld = MC1_Status;
                    MCCount = 0;
                }
            }
            else
            {
                MCCount = 0;
            }


            //------------------------------------------------------------------//
            //----------  Main Contactor Control Routine    --------------------//
            //------------------------------------------------------------------//
                if(MCStsOld_2 !=  IO_READ(MC2))
                {
                    MCCount_2 ++;
                    if(MCCount_2 >= 10)
                    {
                        MC2_Status = IO_READ(MC2);
                        MCStsOld_2 = MC2_Status;
                        MCCount_2 = 0;
                    }
                }
                else
                {
                    MCCount_2 = 0;
                }

//------------------------------------------------------------------//
//----------  PreCharge Contactor Control Routine    ---------------//
//------------------------------------------------------------------//
           if(PCStsOld !=  PGUREC_TCPU_Inputs.bit.PCC1_NO)
            {
               PCCCount ++;
               if(PCCCount >= 10)
               {
                   PCC1_REG.bit.STATUS = PGUREC_TCPU_Inputs.bit.PCC1_NO;
                   PCStsOld = PCC1_REG.bit.STATUS;
                   PCCCount = 0;
               }
            }
           else
            {
               PCCCount = 0;
            }

//------------------------------------------------------------------//
//----------  PreCharge Contactor Control Routine    ---------------//
//------------------------------------------------------------------//
           if(PCStsOld_2 !=  PGUREC_TCPU_Inputs.bit.PCC2_NO)
            {
               PCCCount_2 ++;
               if(PCCCount_2 >= 10)
               {
                   PCC2_REG.bit.STATUS = PGUREC_TCPU_Inputs.bit.PCC2_NO;
                   PCStsOld_2 = PCC2_REG.bit.STATUS;
                   PCCCount_2 = 0;
               }
            }
           else
            {
              PCCCount_2 = 0;
            }


    //------------------------------------------------------------------//
    //----------  Main Circuit Breaker Control Routine    ---------------//
    //------------------------------------------------------------------//
        if(MCBtsOld !=  IO_READ(MCB))
        {
            MCBCount ++;
            if(MCBCount >= 10)
            {
                PGUREC_VCBStatus = IO_READ(MCB);
                MCBtsOld = PGUREC_VCBStatus;
                MCBCount = 0;
            }
        }
        else
        {
            MCBCount = 0;
        }



//------------------------------------------------------------------//
//---------- Precharge Contactor CLOSE/OPEN Routine -1  ---------------//
//------------------------------------------------------------------//
    if(PCC1_REG.bit.OPEN == 1)
    {
        if(PCC1_REG.bit.CLOSE == 1)
        {
            PCC1_REG.bit.CLOSE = 0;      // Bekleyen kapama sinyalini sil,açma öncelikli
            PCC1_REG.bit.TIMER = 0;
        }

//        IO_SET(PCCSig)          // Precharge kontaktörü açma sinyali uygulandý
        PGUREC_TCPU_Outputs.bit.PCC1_SIG=1;


        if(PCC1_REG.bit.STATUS == 0)         // Contactor Status  0: open
        {
            PCC1_REG.bit.OPEN = 0;
            PCC1_REG.bit.TIMER = 0;
        }
        else
        {
            PCC1_REG.bit.TIMER+= 1;
            if(PCC1_REG.bit.TIMER >= 1050)                     // If PCC is not open in 0.5 second, contactor open error flag on
            {
                PGU_ContacErrFlags1.bit.PCC_OER = 1;         // Contactor Open Error
                PCC1_REG.bit.OPEN = 0;
                PCC1_REG.bit.TIMER = 0;
            }
        }
    }

    if(PCC1_REG.bit.CLOSE == 1)
    {
//        IO_CLR(PCCSig)          // Precharge kontaktörü kapatma sinyali uygulandý
        PGUREC_TCPU_Outputs.bit.PCC1_SIG=0;


        if(PCC1_REG.bit.STATUS == 1)        // Contactor Status  1: close
        {
            PCC1_REG.bit.CLOSE = 0;
            PCC1_REG.bit.TIMER = 0;
        }
        else
        {
            PCC1_REG.bit.TIMER += 1;
            if(PCC1_REG.bit.TIMER >= 1050)                   // If PCC is not close in 0.5 second, contactor close error flag on
            {
                PGU_ContacErrFlags1.bit.PCC_CER = 1;      // Contactor Close Error
                PCC1_REG.bit.CLOSE = 0;
                PCC1_REG.bit.TIMER = 0;
//                IO_SET(PCCSig)
                PGUREC_TCPU_Outputs.bit.PCC1_SIG=1;

            }
        }
    }

    //------------------------------------------------------------------//
    //---------- Precharge Contactor CLOSE/OPEN Routine -2  ---------------//
    //------------------------------------------------------------------//
        if(PCC2_REG.bit.OPEN == 1)
        {
            if(PCC2_REG.bit.CLOSE == 1)
            {
                PCC2_REG.bit.CLOSE = 0;      // Bekleyen kapama sinyalini sil,açma öncelikli
                PCC2_REG.bit.TIMER = 0;
            }

//            IO_SET(PCCSig)          // Precharge kontaktörü açma sinyali uygulandý
            PGUREC_TCPU_Outputs.bit.PCC2_SIG=1;


            if(PCC2_REG.bit.STATUS == 0)         // Contactor Status  0: open
            {
                PCC2_REG.bit.OPEN = 0;
                PCC2_REG.bit.TIMER = 0;
            }
            else
            {
                PCC2_REG.bit.TIMER+= 1;
                if(PCC2_REG.bit.TIMER >= 1050)                     // If PCC is not open in 0.5 second, contactor open error flag on
                {
                    PGU_ContacErrFlags2.bit.PCC_OER = 1;         // Contactor Open Error
                    PCC2_REG.bit.OPEN = 0;
                    PCC2_REG.bit.TIMER = 0;
                }
            }
        }

        if(PCC2_REG.bit.CLOSE == 1)
        {
//            IO_CLR(PCCSig)          // Precharge kontaktörü kapatma sinyali uygulandý
            PGUREC_TCPU_Outputs.bit.PCC2_SIG=0;

            if(PCC2_REG.bit.STATUS == 1)        // Contactor Status  1: close
            {
                PCC2_REG.bit.CLOSE = 0;
                PCC2_REG.bit.TIMER = 0;
            }
            else
            {
                PCC2_REG.bit.TIMER += 1;
                if(PCC2_REG.bit.TIMER >= 1050)                   // If PCC is not close in 0.5 second, contactor close error flag on
                {
                    PGU_ContacErrFlags2.bit.PCC_CER = 1;      // Contactor Close Error
                    PCC2_REG.bit.CLOSE = 0;
                    PCC2_REG.bit.TIMER = 0;
//                    IO_SET(PCCSig)
                    PGUREC_TCPU_Outputs.bit.PCC2_SIG=1;
                }
            }
        }
//------------------------------------------------------------------//
//-------------- Main Contactor CLOSE/OPEN Routine 1 -----------------//
//------------------------------------------------------------------//
    if(MCAUX_REG1.bit.OPEN == 1)
    {
        if(MCAUX_REG1.bit.CLOSE == 1)
        {
            MCAUX_REG1.bit.CLOSE = 0;       // Bekleyen kapama sinyalini sil, açma öncelikli
            MCAUX_REG1.bit.TIMER = 0;
        }

        IO_SET(MCSig1)           // Ana kontaktörü açma sinyali uygulandý

        if(MCAUX_REG1.bit.STATUS == 0  && MC1_Status == 1 )
        {
            MCAUX_REG1.bit.OPEN = 0;
            MCAUX_REG1.bit.TIMER = 0;
        }
        else
        {
            MCAUX_REG1.bit.TIMER+= 1;
            if(MCAUX_REG1.bit.TIMER >= 1050)
            {
                PGU_ContacErrFlags1.bit.MC_OER = 1;
                MCAUX_REG1.bit.OPEN = 0;
                MCAUX_REG1.bit.TIMER = 0;
            }
        }
    }


    if(MCAUX_REG1.bit.CLOSE == 1)
    {
        if(PCC1_REG.bit.STATUS == 1)
        {
            IO_CLR(MCSig1)           // Ana kontaktörü kapatma sinyali uygulandý
        }
        else
        {
            PGU_ContacErrFlags1.bit.PCC_NC = 1;
        }

        if(MCAUX_REG1.bit.STATUS == 1  && MC1_Status == 0)
        {
            MCAUX_REG1.bit.CLOSE = 0;
            MCAUX_REG1.bit.TIMER = 0;
        }
        else
        {
            MCAUX_REG1.bit.TIMER += 1;
            if(MCAUX_REG1.bit.TIMER >= 1050)
            {
                PGU_ContacErrFlags1.bit.MC_CER = 1;
                MCAUX_REG1.bit.CLOSE = 0;
                MCAUX_REG1.bit.TIMER = 0;
                IO_SET(MCSig1)       // Ana kontaktörü açma sinyali uygulandý
            }
        }
    }

MCAUX_REG1.bit.TIMER = 0;

//------------------------------------------------------------------//
//-------------- Main Contactor CLOSE/OPEN Routine 2 -----------------//
//------------------------------------------------------------------//
    if(MCAUX_REG2.bit.OPEN == 1)
    {
        if(MCAUX_REG2.bit.CLOSE == 1)
        {
            MCAUX_REG2.bit.CLOSE = 0;       // Bekleyen kapama sinyalini sil, açma öncelikli
            MCAUX_REG2.bit.TIMER = 0;
        }

        IO_SET(MCSig2)           // Ana kontaktörü açma sinyali uygulandý

        if(MCAUX_REG2.bit.STATUS == 0  && MC2_Status == 1 )
        {
            MCAUX_REG2.bit.OPEN = 0;
            MCAUX_REG2.bit.TIMER = 0;
        }
        else
        {
            MCAUX_REG2.bit.TIMER+= 1;
            if(MCAUX_REG2.bit.TIMER >= 1050)
            {
                PGU_ContacErrFlags2.bit.MC_OER = 1;
                MCAUX_REG2.bit.OPEN = 0;
                MCAUX_REG2.bit.TIMER = 0;
            }
        }
    }


    if(MCAUX_REG2.bit.CLOSE == 1)
    {
        if(PCC2_REG.bit.STATUS == 1)
        {
            IO_CLR(MCSig2)           // Ana kontaktörü kapatma sinyali uygulandý
        }
        else
        {
            PGU_ContacErrFlags2.bit.PCC_NC = 1;
        }

        if(MCAUX_REG2.bit.STATUS == 1  && MC2_Status == 0)
        {
            MCAUX_REG2.bit.CLOSE = 0;
            MCAUX_REG2.bit.TIMER = 0;
        }
        else
        {
            MCAUX_REG2.bit.TIMER += 1;
            if(MCAUX_REG2.bit.TIMER >= 1050)
            {
                PGU_ContacErrFlags2.bit.MC_CER = 1;
                MCAUX_REG2.bit.CLOSE = 0;
                MCAUX_REG2.bit.TIMER = 0;
                IO_SET(MCSig2)       // Ana kontaktörü açma sinyali uygulandý
            }
        }
    }

}
// Command Read Routine
void PGUREC_CommandRead(void)
{
//-------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------

//    PGUREC_ReadCANData();

//    PGUREC_MasterContr.TORQUEREF = PGU_TeRefCAN;    //
    PGUREC_CTL_REG.bit.ENABLE  = 1;             //


// Reverser geçiþleri arasý gecikme
	if(PGUREC_ReverserNew != PGUREC_ReverserOld)
	{
		PGUREC_ReverserCnt++;
		if(PGUREC_ReverserCnt > REVERSER_DEBOUNCE_COUNT)
		{
			PGUREC_ReverserCnt = 0;
			PGUREC_ReverserOld = PGUREC_ReverserNew;
			PGUREC_MasterContr.STA.bit.POWER_OFF = 1;  //Reverser konumu deðiþti anahtarlamayý durdur.
		}
	}
	else
	{
		PGUREC_ReverserCnt = 0;
		PGUREC_Reverser	= PGUREC_ReverserOld;
	}


// 	REVERSER_STAT:2	;       // 1:0    	11:Neutral - 10:Forward - 01:Reverse - 00:initial
	switch (PGUREC_Reverser)
	{
	case 0:	PGUREC_MasterContr.REV_SW.all 		   = 0;
			PGUREC_MasterContr.REV_SW.bit.INITIAL  = 1;
		break;
	case 1:	PGUREC_MasterContr.REV_SW.all 		   = 0;
			PGUREC_MasterContr.REV_SW.bit.REVERSE  = 1;
		break;
	case 2:	PGUREC_MasterContr.REV_SW.all 		   = 0;
			PGUREC_MasterContr.REV_SW.bit.FORWARD  = 1;
		break;
	case 3:	PGUREC_MasterContr.REV_SW.all 		   = 0;
			PGUREC_MasterContr.REV_SW.bit.OFF      = 1;
		break;
	}

//	MASTERCONT_STAT:2;       // 3:2    	11:Neutral - 10:Power	- 01:Brake   - 00:Em.Brake
	switch (PGUREC_MasterContrStat)
	{
	case 0:	PGUREC_MasterContr.MAIN_HAND.all 		   	= 0;
			PGUREC_MasterContr.MAIN_HAND.bit.EMG_BRAKE= 1;
		break;
	case 1:	PGUREC_MasterContr.MAIN_HAND.all 		   	= 0;
			PGUREC_MasterContr.MAIN_HAND.bit.BRAKING  = 1;
		break;
	case 2:	PGUREC_MasterContr.MAIN_HAND.all 		   	= 0;
			PGUREC_MasterContr.MAIN_HAND.bit.POWERING = 1;
		break;
	case 3:	PGUREC_MasterContr.MAIN_HAND.all 		   	= 0;
			PGUREC_MasterContr.MAIN_HAND.bit.NEUTRAL  = 1;
		break;
	}

// Reverse switch OFF pozisyonuna çekilmeden konverter aksiyon almamasý için
	if((PGUREC_MasterContr.REV_SW.bit.OFF==1)&&(PGUREC_MasterContr.STA.bit.REV_SW_EN == 0))
	{
		PGUREC_MasterContr.STA.bit.REV_SW_EN = 1;
	}

	if(PGUREC_MasterContr.STA.bit.REV_SW_EN == 0)
	{
		PGUREC_MasterContr.REV_SW.all =0;
	}

// Main Handle NEUTRAL pozisyonuna çekilmeden konverter aksiyon almamasý için
	if((PGUREC_MasterContr.MAIN_HAND.bit.NEUTRAL==1)&&(PGUREC_MasterContr.STA.bit.MAIN_H_EN == 0))
	{
		PGUREC_MasterContr.STA.bit.MAIN_H_EN = 1;
	}

	if(PGUREC_MasterContr.STA.bit.MAIN_H_EN == 0)
	{
		PGUREC_MasterContr.MAIN_HAND.all = 0;
	}

// NEUTRAL pozisyonunda 10 sn beklenmesi halinde anahtarlamayý durdur.
	if(PGUREC_MasterContr.MAIN_HAND.bit.NEUTRAL==1)
	{
		if(PGUREC_NeutralCnt_PowerOff< NEUTRAL_POWEROFF_COUNT)
		{
		    PGUREC_NeutralCnt_PowerOff++;
		}
		else
		{
			PGUREC_MasterContr.STA.bit.POWER_OFF=1;	// Nötr pozisyonunda belirlenen süre (10 second)kadar bekledi anahtarlamayý durdur.
		}
	}
	else
	{
	    PGUREC_NeutralCnt_PowerOff = 0;
		PGUREC_MasterContr.STA.bit.POWER_OFF=0;
	}


// Main Handle geçiþleri arasý gecikme
    if(PGUREC_MasterContr.MAIN_HAND.bit.NEUTRAL==1)
    {
        if(PGUREC_NeutralCnt<1050)
        {
            PGUREC_NeutralCnt++;
        }
        else
        {
            PGUREC_MasterContr.ENABLE.bit.NEUTRAL=1;
        }
    }
    else
    {
        PGUREC_NeutralCnt = 0;
        PGUREC_MasterContr.ENABLE.bit.NEUTRAL = 0;
    }

// Main Handle geçiþleri arasý gecikme
    if(PGUREC_MasterContr.MAIN_HAND.bit.POWERING==1)
    {
        if(PGUREC_PoweringCnt<1050)
        {
            PGUREC_PoweringCnt++;
        }
        else
        {
            PGUREC_MasterContr.ENABLE.bit.POWERING=1;
        }
    }
    else
    {
        PGUREC_PoweringCnt = 0;
        PGUREC_MasterContr.ENABLE.bit.POWERING = 0;
    }

//// Main Handle geçiþleri arasý gecikme
//    if(PGUREC_MasterContr.MAIN_HAND.bit.BRAKING==1)
//    {
//        if(BrakingCnt<1050)
//        {
//            BrakingCnt++;
//        }
//        else
//        {
//            PGUREC_MasterContr.ENABLE.bit.BRAKING=1;
//        }
//    }
//    else
//    {
//        BrakingCnt = 0;
//        PGUREC_MasterContr.ENABLE.bit.BRAKING = 0;
//    }

// Main Handle geçiþleri arasý gecikme
    if(PGUREC_MasterContr.MAIN_HAND.bit.EMG_BRAKE==1)
    {
        if(PGUREC_EMGBrakeCnt<1050)
        {
            PGUREC_EMGBrakeCnt++;
        }
        else
        {
            PGUREC_MasterContr.ENABLE.bit.EMG_BRAKE = 1;
        }
    }
    else
    {
        PGUREC_EMGBrakeCnt = 0;
        PGUREC_MasterContr.ENABLE.bit.EMG_BRAKE = 0;
    }

}

// Tiva Life Check Routine
void PGUREC_TivaLifeCheck(Uint16 Time)
{

	if(PGUREC_TivaRegWFlag == 0)
	{
		if(PGUREC_TivaWriteToggle == 0)
		{
			DSP2TivaRegs.regs.CheckReg = 0xA55A;
			PGUREC_TivaWriteToggle = 1;
		}
		else
		{
			DSP2TivaRegs.regs.CheckReg = 0x55AA;
			PGUREC_TivaWriteToggle = 0;
		}

		PGUREC_TivaRegWFlag = 1;
		PGUREC_TivaRegRCount = 0;
	}
	else
	{
		if(PGUREC_TivaRegRCount > Time)
		{
//		    PGUREC_FLT_REG.bit.STELHS = 1;
			PGUREC_TivaRegWFlag  = 0;
		}
		else
		{
			if(Tiva2DSPRegs.regs.CheckReg == ~DSP2TivaRegs.regs.CheckReg)
			{
				PGUREC_TivaRegWFlag = 0;
			}
			else
			{
				PGUREC_TivaRegRCount++;
			}
		}
	}
}

#endif /* PGUREC_MAINISR_C_ */
