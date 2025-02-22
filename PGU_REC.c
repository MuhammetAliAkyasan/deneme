/* ==============================================================================
System Name:    YEMU LOCO

File Name:      PGU_REC.c

Description:    YEMU_LOCO - 1 ph PWM Rectifier Control

Originator:     YEMU

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 01-10-2018 Version 1.0
=================================================================================  */

#include "DSP28x_Project.h"
#include "PGU_Common.h"
#include "PGUREC_Common.h"

#include "PGUREC_MainISR.h"

//***********  REC  ******************

//===========================================================================
// Instantiation
//===========================================================================

    RESONANT2   R50c            = RESONANT2_DEFAULTS;
    RESONANT2   R50c_2          = RESONANT2_DEFAULTS;

    ISFF        Isff            = ISFF_DEFAULTS;
    RECPI       Vdc_PI          = {RECPI_IN_DEFAULTS, RECPI_OUT_DEFAULTS, RECPI_VAR_DEFAULTS, RECPI_PAR_DEFAULTS};
    FFC         FFComp          = {FFC_IN_DEFAULTS, FFC_OUT_DEFAULTS, FFC_VAR_DEFAULTS, FFC_PAR_DEFAULTS};
    FFC         FFComp2          = {FFC_IN_DEFAULTS, FFC_OUT_DEFAULTS, FFC_VAR_DEFAULTS, FFC_PAR_DEFAULTS};
    DG          DutyGen         = {DG_IN_DEFAULTS, DG_OUT_DEFAULTS, DG_VAR_DEFAULTS, DG_PAR_DEFAULTS};
    DG          DutyGen_2         = {DG_IN_DEFAULTS, DG_OUT_DEFAULTS, DG_VAR_DEFAULTS, DG_PAR_DEFAULTS};

    DC              Dc              = {0.0,0.0,0.0};
    POWERA          ApparentP_p     = {0.0,0.0};
    POWERR          RealP_p         = {0.0,0.0,0.0};
    POWERA          ApparentP_s     = {0.0,0.0};
    POWERR          RealP_s         = {0.0,0.0,0.0};


void Rec1_Init(void)
{
    /*------------------------------------------------------------------------------
            Resonant2 modules initialization
    ------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    -----  Ýlk çalýþan PR Parametreleri - Düzgün Sonuç
   float32 A50c[3]     = {0.0142607544893433,-0.000496335246681469,-0.0147570897360248};
   float32 B50c[3]     = {0.0,-1.97471848726624, 0.997023590784222};
   //float32 S50c[5]     = { 0,0,0,0,0};
   w  = 2*pi*50; Ts = 1/2100; Ki = 10; Tt = 1.5*(1/2100);  deltaw = w*0.02;

   -----------------------------------------------------------------------------*/
    //1050 Hz anahtarlamada çalýþan PR controller parametreleri
//    float32 A50c[3]     = {0.0427504527576383,-0.0014878985912746,-0.0442383513489129};
//    float32 B50c[3]     = {0.0,-1.97325018725564, 0.9955387058356};
// w  = 2*pi*50; Ts = 1/2100; Ki = 20; Tt = 1.5*(1/2100);  deltaw = w*0.03;

    //800 Hz anahtarlama için
    float32 A50c[3]     = {0.0541750823575249,-0.00333687831603189,-0.0575119606735568};
    float32 B50c[3]     = {0.0,-1.95584705832013, 0.994164367470955};


//    float32 A50c[3]     = {0.027839542696975,-0.00125930549316295,-0.0290988481901379};
//    float32 B50c[3]     = {0.0,-1.95584705832013, 0.994164367470955};
////     w  = 2*pi*50; Ts = 1/1600; Ki = 10; Tt = 1.125*(1/1600);  deltaw = w*0.03;

    R50c.Enable = 1;
    R50c.A[0]       = A50c[0];
    R50c.A[1]       = A50c[1];
    R50c.A[2]       = A50c[2];
    R50c.B[1]       = B50c[1];
    R50c.B[2]       = B50c[2];

    R50c_2.Enable = 1;
    R50c_2.A[0]       = A50c[0];
    R50c_2.A[1]       = A50c[1];
    R50c_2.A[2]       = A50c[2];
    R50c_2.B[1]       = B50c[1];
    R50c_2.B[2]       = B50c[2];


    /*------------------------------------------------------------------------------
        ISFF initialization
    ------------------------------------------------------------------------------*/
    Isff.Vspeak     = VS_PEAK;
    Isff.Vspeaksat  = VS_PEAK_MIN;
    Isff.Vspeakmin  = VS_PEAK_MIN;
    Isff.Vspeakmax  = VS_PEAK_MAX;
    Isff.Kff        = ISFF_K;

    /*------------------------------------------------------------------------------
        PICTRL initialization
    ------------------------------------------------------------------------------*/
    Vdc_PI.p.Enable = 1;
    Vdc_PI.p.Kp     = RECPI_KP;
    Vdc_PI.p.OutMax = RECPI_OUTMAX;
    Vdc_PI.p.OutMin = RECPI_OUTMIN;
    Vdc_PI.p.Ki     = (PGUREC_TS*RECPI_KI)/RECPI_KP;//(Ti= KP/KI),(Ki= Ts/Ti),Ki=(Ts*KI)/KP
    Vdc_PI.p.Kc     = RECPI_KC;

    /*--------------------------------------------------------------------------
        FFCOMP initialization
    ---------------------------------------------------------------------------*/
    FFComp.p.R      = RS;
    FFComp.p.wLs    = 2*PI*50*Ls;
    FFComp.p.Theta  = FF_THETA;

    /*--------------------------------------------------------------------------
        FFCOMP initialization
    ---------------------------------------------------------------------------*/
    FFComp2.p.R      = RS;
    FFComp2.p.wLs    = 2*PI*50*Ls;
    FFComp2.p.Theta  = FF_THETA;

    /*--------------------------------------------------------------------------
        DUTYGEN initialization
    ---------------------------------------------------------------------------*/
    DutyGen.p.Enable= 1;
    DutyGen.p.Dmax  = REC_DUTY_MAX;
    DutyGen.p.Dmin  = REC_DUTY_MIN;
    DutyGen.p.Kp    = RECIS_KP;
    DutyGen.p.VrMax = REC_VR_MAX;
    DutyGen.p.VrMin = REC_VR_MIN;

    /*--------------------------------------------------------------------------
        DUTYGEN initialization
    ---------------------------------------------------------------------------*/
    DutyGen_2.p.Enable= 1;
    DutyGen_2.p.Dmax  = REC_DUTY_MAX;
    DutyGen_2.p.Dmin  = REC_DUTY_MIN;
    DutyGen_2.p.Kp    = RECIS_KP;
    DutyGen_2.p.VrMax = REC_VR_MAX;
    DutyGen_2.p.VrMin = REC_VR_MIN;

}
Uint16 PGUREC_BuffCntr_Rec = 0;
//=================================================================================
//	E5000 Rectifier Control - 1 Phase PWM Rectifier
//=================================================================================
void Rec1_ISR(void)
{
    // Verifying the ISR
        PGUREC_RecIsrTicker++;


//        IO_SET(PGUREC_DORes2)                          // Start of ISR Indicator

    if(PGUREC_RCTL_REG.bit.CtrlStart==1)
        {

            if(ZC_Flag ==1 && PGUREC_RCTL_REG.bit.Enable == 1)
            {
                PGUREC_RCTL_REG.bit.CtrlState  = 1;

                PGUREC_CTL_REG.bit.STATE   = 5;        // Rectifier kontrol dongusu devreye alindi
                PGUREC_RCTL_REG.bit.CtrlStart=  0;
                RecCtrlTimeOutCnt = 0;
            }
            else if(RecCtrlTimeOutCnt >= 1000)
            {
                PGUREC_CTL_REG.bit.STATE       = 13;       // Rectifier kontrol dongusu devreye alinamadý
                PGUREC_RCTL_REG.bit.CtrlStart  = 0;
                RecCtrlTimeOutCnt = 0;
            }
            else
            {
                RecCtrlTimeOutCnt++;
            }
        }

// ------------------------------------------------------------------------------
//  Connect Rectifier analog feedbacks
// ------------------------------------------------------------------------------

//	UdcLPF= PGUREC_Measure.Result.Volt_DCLink1;
        REC_FDB_MACRO_1ps(PGU_1PHRectFdb,PGUREC_Measure)

//-------------------------------------------------------------------------------
//  Average calculations   SupplyMean.PeakSum
//-------------------------------------------------------------------------------
	SUPPLYMEAN_MACRO(SupplyMean)

	Supply.Freq = SupplyMean.Freq;
	Supply.Harm = SupplyMean.Harm;
	Supply.Rms  = SupplyMean.Peak * 0.707;

//	IO_CLR(PGUREC_DORes2)                          // ISR Indicator

//------------------------------------------------------------------//
//--------------------------Kontrol Baþlangýç-----------------------//
//------------------------------------------------------------------//

// ------------------------------------------------------------------------------
//  Connect inputs of the Isff module and call the ISFF macro
// ------------------------------------------------------------------------------
//  Isff.Vdc            = Dc.Vdc_BSF;                   //Rec.Vdc;
//  Isff.Idc            = Dc.Idc_BSF;                   //Rec.Idc;

//    Isff.DCpower        = sat(InvPin  , 1250000.0 ,-1250000.0);
    Isff.DCpower        = sat(0.0  , 1250000.0 ,-1250000.0);

    Isff.Vspeak         = SupplyMean.Peak;              //Vspeak.Peak;

    ISFF_MACRO(Isff)


// ------------------------------------------------------------------------------
//  Connect inputs of the VDC PI controller
//  and call the PICTRL_MACRO for VDC PI controller
// ------------------------------------------------------------------------------
    Vdc_PI.i.Ref        = sat(Vdc_ref  ,VDC_REF_MAX ,VDC_REF_MIN);
    Vdc_PI.i.Fdb        = sat(Dc.Vdc_BSF,VDC_MAX,VDC_MIN);  //Rec.Vdc

    Vdc_PI.p.Enable     = PGUREC_RCTL_REG.bit.CtrlState;
    RECPI_MACRO(Vdc_PI)


// ------------------------------------------------------------------------------
//  Connect inputs of the FFComp module and call the FFCOMP_MACRO
// ------------------------------------------------------------------------------
    FFComp.i.IsRefVCp   = Vdc_PI.o.Out;
    FFComp.i.Is         = PGU_1PHRectFdb.Cur_RectInput1;
    FFComp.i.Is_ff      = 0.0;//Isff.Isff;
    FFComp.i.VsPhase    = VsPhase;
    FFComp.i.VsPeak     = SupplyMean.Peak; //Vspeak.Peak;
    FFComp.i.VsHarm     = 0.0;

    FFC_MACRO(FFComp)

// ------------------------------------------------------------------------------
//  Connect inputs of the FFComp module and call the FFCOMP_MACRO
// ------------------------------------------------------------------------------
    FFComp2.i.IsRefVCp   = Vdc_PI.o.Out;
    FFComp2.i.Is         = PGU_1PHRectFdb.Cur_RectInput2;
    FFComp2.i.Is_ff      = 0.0;//Isff.Isff;
    FFComp2.i.VsPhase    = VsPhase;
    FFComp2.i.VsPeak     = SupplyMean.Peak; //Vspeak.Peak;
    FFComp2.i.VsHarm     = 0.0;

    FFC_MACRO(FFComp2)

// ------------------------------------------------------------------------------
//  Connect inputs of the RESONANT2 module and call the RESONANT2_MACRO
// ------------------------------------------------------------------------------
    R50c.In             = FFComp.o.IsErr;

    R50c.Enable         = PGUREC_RCTL_REG.bit.CtrlState;
    RESONANT2_MACRO(R50c)

// ------------------------------------------------------------------------------
//  Connect inputs of the RESONANT2 module and call the RESONANT2_MACRO
// ------------------------------------------------------------------------------
    R50c_2.In             = FFComp2.o.IsErr;

    R50c_2.Enable         = PGUREC_RCTL_REG.bit.CtrlState;
    RESONANT2_MACRO(R50c_2)

// ------------------------------------------------------------------------------
//  Connect inputs of the DutyGen module
// ------------------------------------------------------------------------------
    DutyGen.i.IsErr     = FFComp.o.IsErr;
    DutyGen.i.Resonant  = R50c.Out;     //sat(R50c.Out,1000.0,-1000.0);//0.0;0.0;//
    DutyGen.i.Vdc       = Dc.Vdc_Est; //;       //Rec.Vdc;Rec.Vdc
    DutyGen.i.Vf        = FFComp.o.Vf;

    DutyGen.p.Enable    = PGUREC_RCTL_REG.bit.CtrlState;
    DG_MACRO(DutyGen)

    PGUREC2_PWM1.MfuncC      =  DutyGen.o.Duty;
    PGUREC2_PWM2.MfuncC      = -PGUREC1_PWM1.MfuncC;

// ------------------------------------------------------------------------------
//  Connect inputs of the DutyGen module
// ------------------------------------------------------------------------------
    DutyGen_2.i.IsErr     = FFComp2.o.IsErr;
    DutyGen_2.i.Resonant  = R50c_2.Out;           //sat(R50c.Out,1000.0,-1000.0);//0.0;0.0;//
    DutyGen_2.i.Vdc       = Dc.Vdc_Est; //;       //Rec.Vdc;Rec.Vdc
    DutyGen_2.i.Vf        = FFComp2.o.Vf;

    DutyGen_2.p.Enable    = PGUREC_RCTL_REG.bit.CtrlState;
    DG_MACRO(DutyGen_2)

    PGUREC1_PWM1.MfuncC      =  DutyGen_2.o.Duty;
    PGUREC1_PWM2.MfuncC      = -PGUREC2_PWM1.MfuncC;

//DC Voltage Reference Calculation

     if (PGUREC_RCTL_REG.bit.CtrlState==1)
     {
         if(Vdc_refInitFlag==0)
         {
             Vdc_refInitFlag = 1;
             Vdc_ref = sat(PGUREC_Measure.Result.Volt_DCLink*1.02,VDC_REF_MAX ,VDC_REF_MIN);
         }

         if (Vdc_ref < VDC_REF_MAX)
         {
             Vdc_ref = Vdc_ref + 0.075;
         }

     }
     else
     {
         Vdc_refInitFlag = 0;
     }

 // ====================================Monitoring==========================================
    if(Vdc_refInitFlag == 1)
    {
        if(PGUREC_BuffCntr_Rec<1024)
           {
               PGUREC_BuffCntr_Rec++;

                     FillAnalogBuffer(FFComp.o.IsErr,   AnaBuff.buff1, 1);
                     FillAnalogBuffer(R50c.Out, AnaBuff.buff2, 2);
//                   FillAnalogBuffer(Id_PI.o.Out, AnaBuff.buff3, 3);
//                   FillAnalogBuffer(invPARK2.Is_d, AnaBuff.buff4, 4);
//                   FillAnalogBuffer(invPARK2.Is_q, AnaBuff.buff5, 5);
                     FillAnalogBuffer(PGUREC_Measure.Result.Cur_RectInput1,   AnaBuff.buff6, 6);
                     FillAnalogBuffer((-1)*PGUREC_Measure.Result.Cur_RectInput1, AnaBuff.buff7, 7);
                     FillAnalogBuffer(Vdc_PI.o.Out, AnaBuff.buff8, 8);
//                   FillAnalogBuffer(V_dLPF, AnaBuff.buff9, 9);
                     FillAnalogBuffer(PGUREC1_PWM1.MfuncC, AnaBuff.buff10, 10);
//                   FillAnalogBuffer(invPARK1.Qs, AnaBuff.buff11, 11);
//                   FillAnalogBuffer(cos(Pll_QSG_Osc1.Phase), AnaBuff.buff12, 12);
                     FillAnalogBuffer(Volt_LabGiris, AnaBuff.buff13, 13);
//                   FillAnalogBuffer(PGUREC_Measure.Result.Volt_DCLink, AnaBuff.buff14, 14);
////                 FillAnalogBuffer(-PGUREC_Measure.Result.Cur_RectInput1, AnaBuff.buff15, 15);
                     FillAnalogBuffer(FFComp.o.Vf, AnaBuff.buff12, 12);
                     FillAnalogBuffer(DutyGen.v.CCOut,   AnaBuff.buff4, 4);
          }
    }
//   FillAnalogBuffer(DutyGen.v.CCOut,   AnaBuff.buff4, 4);
//   FillAnalogBuffer(FFComp.o.IsErr, AnaBuff.buff9, 9);
//   FillAnalogBuffer(PGUREC_Measure.Result.Cur_RectInput1, AnaBuff.buff10, 10);
//   FillAnalogBuffer(PGUREC_Measure.Result.Volt_DCLink, AnaBuff.buff11, 11);
//   FillAnalogBuffer(PGUREC_Measure.Result.Cur_RectInput1, AnaBuff.buff12, 12);
//   FillAnalogBuffer(R50c.Out, AnaBuff.buff13, 13);
//   FillAnalogBuffer(Volt_LabGiris,   AnaBuff.buff1, 1);

//-------------------------------------------------------------------------------
//  Power Calculation
//-------------------------------------------------------------------------------
    PowerCnt++;
    if(PowerCnt == 300)
    {
        ApparentP_p.Power   = ApparentP_p.MeanSum * (1.0/((PGUREC_MAINISR_S_DIV/2)*300));
        ApparentP_p.MeanSum = 0.0;

        ApparentP_s.Power   = ApparentP_s.MeanSum * (1.0/((PGUREC_MAINISR_S_DIV/2)*300));
        ApparentP_s.MeanSum = 0.0;

        if(ZC_Cnt > 0)
        {
            RealP_p.Power       = RealP_p.MeanSum * (1.0/(float32)ZC_Cnt);
            RealP_p.MeanSum     = 0.0;

            RealP_s.Power       = RealP_s.MeanSum * (1.0/(float32)ZC_Cnt);
            RealP_s.MeanSum     = 0.0;
        }
        else
        {
            RealP_p.Power       = 0.0;
            RealP_p.MeanSum     = 0.0;

            RealP_s.Power       = 0.0;
            RealP_s.MeanSum     = 0.0;
        }

        PowerFactor_p = (RealP_p.Power / ApparentP_p.Power);
        PowerFactor_s = (RealP_s.Power / ApparentP_s.Power);

        PowerCnt    = 0;
        ZC_Cnt      = 0;
    }


// ==================================== Main control loop ==========================================


	if(PGUREC_RCTL_REG.bit.CtrlState==1)
	    {
	        if(PGUREC_RCTL_REG.bit.Enable !=1)
	        {
	            PGUREC_RCTL_REG.bit.CtrlState  = 0;
	        }

	        if(RecPWMStartCnt < 2) // Clear initialization trip after control start
	        {
	            RecPWMStartCnt++;
	        }
	        else
	        {
	            if(RecPWMStartCnt==2)
	            {
	                RecPWMStartCnt  = 3;
	                PGUREC_InvTripClear    = 1;

	                FOIOGateON
//                    DELAY_US(150);
	                if(Prech1)
	                {
	                    PGURec2GateON
	                }
	                else if (Prech2)
	                {
	                    PGURec1GateON
	                }



	                PGUREC_CTL_REG.bit.STATE       = 6;    // Rectifier anahtarlama basladi
	                PGUREC_CTL_REG.bit.OPMODE      = 1;
	                //MonitorRegs.STATUS.CONV_OP_STAT = 1;
	            }
//	            if(PGUREC_DC_Counter < 1500)
//	            {
//	                PGUREC_DC_Counter ++;
//	            }
	        }

	        if(FFComp.v.IsRefSump > 5.0) //5A %1 güc
	        {
	            PGUREC_RCTL_REG.bit.PoweringMode = 1;
	            PGUREC_RCTL_REG.bit.RegenMode = 0;
	        }
	        else if(FFComp.v.IsRefSump < -5.0)
	        {
	            PGUREC_RCTL_REG.bit.PoweringMode = 0;
	            PGUREC_RCTL_REG.bit.RegenMode = 1;
	        }
	        else
	        {
	            PGUREC_RCTL_REG.bit.PoweringMode   = 0;
	            PGUREC_RCTL_REG.bit.RegenMode      = 0;
	        }
	    }
	    else
	    {
	        if(PGUREC_CTL_REG.bit.STATE >= 6)
	        {
	            PGUGateOFF
	            FOIOGateOFF
	        }

	        RecPWMStartCnt  = 0;
//	        PGUREC_DC_Counter      = 0;

	        PGUREC_CTL_REG.bit.OPMODE  = 0;

	        PGUREC_RCTL_REG.bit.PoweringMode   = 0;
	        PGUREC_RCTL_REG.bit.RegenMode      = 0;
	        //MonitorRegs.STATUS.CONV_OP_STAT = 0;
	    }
}

//// Rec ISR Ends Here
