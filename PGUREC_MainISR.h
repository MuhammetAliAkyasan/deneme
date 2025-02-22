/*
 * PGUREC_MainISR.h
 *
 *  Created on: 06 May 2014   SpeedSensorDir
 *      Author: fozturk
 */

#ifndef PGUREC_MAINISR_H_
#define PGUREC_MAINISR_H_

/*-------------------------------------------------------------------------------
Next, Include project specific include files.
-------------------------------------------------------------------------------*/

#include "PGU_DSP_Math.h"

#define NEUTRAL_POWEROFF_COUNT  10*2100     // 2100 = 1 saniye, 5 saniye
//#define CATENARY_HIGH_COUNT     10*2100     // 2100 = 1 saniye, 5 saniye
#define REVERSER_DEBOUNCE_COUNT 10         // 2100 = 1 saniye, 210 = 250 ms
#define MCB_ON_COUNT 3*2100          // 2100 = 1 saniye, 6300 = 3 s


extern float32 CATENARY_HIGH_COUNT;     // 2100 = 1 saniye, 5 saniye


//extern volatile float32 PGU_TeRefCAN;

extern volatile float32 VsSyncEnable;
extern volatile Uint16 PGUtoPGUDeneme;

extern volatile float32 AlphaSin;
extern volatile float32 BetaCos;

extern float32 Volt_LabGiris;
extern float32 IRec1;
extern float32 IRec2;

extern Uint16 GerilimsizAnahtarlama;
extern Uint16 Prech1;
extern Uint16 Prech2;

extern float32 VCatenary;
extern float32 VSeconder;
extern Uint16  RecPWMStartCnt;
extern Uint16  RecCtrlTimeOutCnt;

extern Uint16 CKU_Ident0_REC;
extern Uint16 CKU_Ident1_REC;
extern Uint16 CKU_Ident2_REC;
extern Uint16 CKU_Ident3_REC;

extern Uint16  PGUINV_FAULT;
extern Uint16 PGUINV_MotCurU;
extern Uint16 PGUINV_MotCurW;
extern Uint16 PGUINV_BreakCur;


extern Uint16 PGUREC_Emergency_Degraded;
extern Uint16 PGUREC_Emergency1;
extern Uint16 PGUREC_Emergency2;
extern Uint16 PGUREC_Emergency3;

extern Uint16 MC1_Status;
extern Uint16 MC2_Status;

extern Uint16  PGUREC_CKU1;
extern Uint16  PGUREC_CKU2;

extern Uint16  PGUREC_InvTripClear;
extern Uint16  PGUREC_DC_Counter;

//Limits        Uth

extern volatile float32 VsPhase;
extern volatile float32 VsFreq;

extern volatile float32 IsPhase;
extern volatile float32 IsFreq;

extern volatile float32 PhaseDiff;

extern volatile float32 Vdc_ref;

//extern volatile float32 DCBus1;
extern Uint16   Vdc_refInitFlag;
extern Uint16   Vs_refInitFlag;
//extern Uint16   VsSyncEnable;
//------------------------------------
// Global Variables
//------------------------------------
extern float32 PGUREC_MainIsrTotalTime;

extern Uint16  PGUREC_TivaRegWFlag;
extern Uint16  PGUREC_TivaRegRCount;

extern Uint16  PGUREC_MasterContrStat;
extern Uint16  PGUREC_ConvEnable;
extern Uint16  PGUREC_TractInh;
extern Uint16  PGUREC_VCBStatus;
extern Uint16  PGUREC_ERTMSBrake;
extern Uint16  PGUREC_Trac_Null;
extern Uint16  PGUREC_EDBrakeCut;

extern Uint16  TractionSafe;

extern float32 SyncOK;
extern float32 SyncOKd;

extern Uint16  PowerCnt;
extern Uint16  ZC_Cnt;

extern Uint16  PGUINV_FAULT;

extern float32 PowerFactor_p;
extern float32 PowerFactor_s;
extern float32 PowerFactorFP_s;


extern Uint16  PGUREC_EDBrakeActive;
extern Uint16  ZC_Flag;
extern Uint16  PGUREC_Reverser;
extern Uint16  PGUREC_ReverserNew;
extern Uint16  PGUREC_ReverserOld;
extern Uint16  PGUREC_ReverserCnt;

extern Uint16  PGUREC_ControlEnable;

extern Uint16  PGUREC_FaultFlagsClear;
extern Uint16  PGUREC_FaultReset;


extern Uint16  PGUREC_SelfTestErrClear;

//--TICK COUNTERS
extern Uint32  PGUREC_RecIsrTicker;         //  Inverter ISR Ticker
extern Uint32  PGUREC_MainIsrTicker;
extern Uint16  PGUREC_DOCounter;
//--OTHERS
extern Uint16  PGUREC_FPGAsReset;           //  Trip Zone error clear control variable
extern Uint16  PGUREC_TripZoneClear;

// Initialization Values
extern  TORQUE    PGUREC_Torque;

// Initialization Values
extern  REGEN           Regen;


extern  RMS               PGUREC_IRec1RMS;
extern  RMS               PGUREC_IRec2RMS;
extern  RMS               PGUREC_VRecRMS;

extern  CLARKE_Vs         invCLARKE1;
extern  PLL_QSG_OSC       Pll_QSG_Osc1;

extern  PGUREC_CTRL_VAR    PGUREC_RCTL_REG;

extern  PGU_FDB_REC   PGU_1PHRectFdb;
extern  PGU_FDB_REC   PGU_1PHRectFdbHs;


//DIOC CAN Messages

// DIOC MSG1 Bit Definitions */
struct DIOC1_MSG1_BITS {   // bits   description
    Uint16 Level1_STA:1;                            // 0
    Uint16 Level2_STA:1;                            // 1
    Uint16 Cooling_FAN1_2_Contactors_STA:1;           // 2
    Uint16 RSVD1:1;                                 // 3
    Uint16 Cooling_PUMP_Contactor_STA:1;            // 4
    Uint16 Cooling_FAN1_MPS_STA:1;                  // 5  MPS= Motor Protection Switch
    Uint16 Cooling_FAN2_MPS_STA:1;                  // 6
    Uint16 Cooling_PUMP_MPS_STA:1;                  // 7
    Uint16 Cabin_FAN1_2_FUSE_STA:1;                 // 8
    Uint16 CKU_FAN1_2_FUSE_STA:1;                   // 9
    Uint16 MC1_NC_STA:1;                            // 10
    Uint16 MC2_NC_STA:1;                            // 11
    Uint16 RSVD2:4    ;                             // 15:12
};

typedef union{
   Uint16                all;
   struct DIOC1_MSG1_BITS   bit;
}DIOC1_RXMSG1_REG;

// DIOC MSG1 Bit Definitions */
struct DIOC1_MSG2_BITS {   // bits   description
    Uint16 N_Level1_STA:1;                            // 0
    Uint16 N_Level2_STA:1;                            // 1
    Uint16 N_Cooling_FAN1_2_Contactors_STA:1;           // 2
    Uint16 RSVD1:1;                                 // 3
    Uint16 N_Cooling_PUMP_Contactor_STA:1;            // 4
    Uint16 N_Cooling_FAN1_MPS_STA:1;                  // 5  MPS= Motor Protection Switch
    Uint16 N_Cooling_FAN2_MPS_STA:1;                  // 6
    Uint16 N_Cooling_PUMP_MPS_STA:1;                  // 7
    Uint16 N_Cabin_FAN1_2_FUSE_STA:1;                 // 8
    Uint16 N_CKU_FAN1_2_FUSE_STA:1;                   // 9
    Uint16 N_MC1_NC_STA:1;                            // 10
    Uint16 N_MC2_NC_STA:1;                            // 11
    Uint16 RSVD2:4    ;                             // 15:12
};

typedef union{
   Uint16                all;
   struct DIOC1_MSG2_BITS   bit;
}DIOC1_RXMSG2_REG;

// DIOC MSG3 Bit Definitions */
struct DIOC1_MSG3_BITS {   // bits   description
    Uint16 ID1:1;                       // 0
    Uint16 ID2:1;                       // 1
    Uint16 ID3:1;                       // 2
    Uint16 ID4_Checksum:1;              // 3
    Uint16 ID5:1;                       // 4
    Uint16 MCAUX_STA1:1;                // 5
    Uint16 MCBTrip_STA:1;               // 6
    Uint16 MCBOFF_STA:1;                // 7
    Uint16 LocoEnable:1;                // 8
    Uint16 Condansator_Pressure:1;      // 9
    Uint16 Limit_Switch:1;              // 10
    Uint16 MCAUX_STA2:1;                // 11
    Uint16 RSVD1:4;                     // 15:12
};

typedef union{
   Uint16                all;
   struct DIOC1_MSG3_BITS   bit;
}DIOC1_RXMSG3_REG;

// DIOC MSG4 Bit Definitions */
struct DIOC1_MSG4_BITS {   // bits   description
    Uint16 N_ID1:1;                       // 0
    Uint16 N_ID2:1;                       // 1
    Uint16 N_ID3:1;                       // 2
    Uint16 N_ID4_Checksum:1;              // 3
    Uint16 N_ID5:1;                       // 4
    Uint16 N_MCAUX_STA1:1;                // 5
    Uint16 N_MCBTrip_STA:1;               // 6
    Uint16 N_MCBOFF_STA:1;                // 7
    Uint16 N_LocoEnable:1;                // 8
    Uint16 N_Condansator_Pressure:1;      // 9
    Uint16 N_Limit_Switch:1;              // 10
    Uint16 N_MCAUX_STA2:1;                // 11
    Uint16 N_RSVD1:4;                     // 15:12
};

typedef union{
   Uint16                all;
   struct DIOC1_MSG4_BITS   bit;
}DIOC1_RXMSG4_REG;

// DIOC MSG1 Bit Definitions */
struct DIOC2_MSG1_BITS {   // bits   description
    Uint16 ID1:1;                                     // 0
    Uint16 ID2:1;                                     // 1
    Uint16 ID3:1;                                     // 2
    Uint16 ID4_Checksum:1;                            // 3
    Uint16 Forward:1;                                 // 4
    Uint16 Reverse:1;                                 // 5
    Uint16 Master_Cont1:1;                            // 6
    Uint16 Master_Cont2:1;                            // 7
    Uint16 Master_Cont3:1;                            // 8
    Uint16 Master_Cont4:1;                            // 9
    Uint16 Master_Cont5:1;                            // 10
    Uint16 Master_Cont6:1;                            // 11
    Uint16 RSVD2:4    ;                               // 15:12
};

typedef union{
   Uint16                all;
   struct DIOC2_MSG1_BITS   bit;
}DIOC2_RXMSG1_REG;

// DIOC MSG1 Bit Definitions */
struct DIOC2_MSG2_BITS {   // bits   description
    Uint16 N_ID1:1;                                     // 0
    Uint16 N_ID2:1;                                     // 1
    Uint16 N_ID3:1;                                     // 2
    Uint16 N_ID4_Checksum:1;                            // 3
    Uint16 N_Forward:1;                                 // 4
    Uint16 N_Reverse:1;                                 // 5
    Uint16 N_Master_Cont1:1;                            // 6
    Uint16 N_Master_Cont2:1;                            // 7
    Uint16 N_Master_Cont3:1;                            // 8
    Uint16 N_Master_Cont4:1;                            // 9
    Uint16 N_Master_Cont5:1;                            // 10
    Uint16 N_Master_Cont6:1;                            // 11
    Uint16 RSVD2:4    ;                                 // 15:12
};

typedef union{
   Uint16                all;
   struct DIOC2_MSG2_BITS   bit;
}DIOC2_RXMSG2_REG;


// DIOC MSG1 Bit Definitions */
struct DIOC2_MSG3_BITS {   // bits   description
    Uint16 RSVD1_225:1;                            // 0
    Uint16 RSVD2_225:1;                            // 1
    Uint16 RSVD3_225:1;                            // 2
    Uint16 RSVD4_225:1;                            // 3
    Uint16 RSVD5_225:1;                            // 4
    Uint16 RSVD6_225:1;                            // 5
    Uint16 RSVD7_225:1;                            // 6
    Uint16 RSVD8_225:1;                            // 7
    Uint16 Cabs_Mode_Act:1;                        // 8
    Uint16 Speed_Lim_Act:1;                        // 9
    Uint16 Normal_Mode:1;                          // 10
    Uint16 Rescue_Mode:1;                          // 11
    Uint16 RSVD5:4    ;                            // 15:12
};

typedef union{
   Uint16                all;
   struct DIOC2_MSG3_BITS   bit;
}DIOC2_RXMSG3_REG;


// DIOC MSG1 Bit Definitions */
struct DIOC2_MSG4_BITS {   // bits   description
    Uint16 N_RSVD1_225:1;                           // 0
    Uint16 N_RSVD2_225:1;                           // 1
    Uint16 N_RSVD3_225:1;                           // 2
    Uint16 N_RSVD4_225:1;                           // 3
    Uint16 N_RSVD5_225:1;                           // 4
    Uint16 N_RSVD6_225:1;                           // 5
    Uint16 N_RSVD7_225:1;                           // 6
    Uint16 N_RSVD8_225:1;                           // 7
    Uint16 N_Cabs_Mode_Act:1;                       // 8
    Uint16 N_Speed_Lim_Act:1;                       // 9
    Uint16 N_Normal_Mode:1;                         // 10
    Uint16 N_Rescue_Mode:1;                         // 11
    Uint16 N_RSVD5:4    ;                           // 15:12
};

typedef union{
   Uint16                all;
   struct DIOC2_MSG4_BITS   bit;
}DIOC2_RXMSG4_REG;


// DIOC1 MSG1 Bit Definitions */
struct DIOC1_TXMSG1_BITS {    // bits   description
    Uint16 Cabin_Fan:1;        // 0
    Uint16 RSVD1:1;            // 1
    Uint16 CIFR:1;             // 2
    Uint16 RVSD2:1;            // 3
    Uint16 TRAC_OK1:1;         // 4
    Uint16 TRAC_OK2:1;         // 5
    Uint16 RVSD3:10;           // 15:6
};

typedef union{
   Uint16                all;
   struct DIOC1_TXMSG1_BITS   bit;
}DIOC1_TXMSG1_REG;


// DIOC2 MSG1 Bit Definitions */
struct DIOC2_TXMSG1_BITS {    // bits   description
    Uint16 Motor1_OK:1;                       // 0
    Uint16 Motor2_OK:1;                       // 1
    Uint16 HV_Presence:1;                     // 2
    Uint16 Trac_DCLink_OK:1;                  // 3
    Uint16 Pantograph_Permission:1;           // 4
    Uint16 RSVD1:1;                           // 5
    Uint16 RSVD2:10;                           // 15:6
};

typedef union{
   Uint16                all;
   struct DIOC2_TXMSG1_BITS   bit;
}DIOC2_TXMSG1_REG;



extern volatile DIOC1_RXMSG1_REG PGUREC_DIOC1_Inputs1;
extern volatile DIOC1_RXMSG2_REG PGUREC_DIOC1_Inputs1N;

extern volatile DIOC1_RXMSG3_REG PGUREC_DIOC1_Inputs_TCPU;
extern volatile DIOC1_RXMSG4_REG PGUREC_DIOC1_InputsN_TCPU;

extern volatile DIOC2_RXMSG1_REG PGUREC_DIOC2_Inputs1;
extern volatile DIOC2_RXMSG2_REG PGUREC_DIOC2_Inputs1N;

extern volatile DIOC2_RXMSG3_REG PGUREC_DIOC2_Inputs2;
extern volatile DIOC2_RXMSG4_REG PGUREC_DIOC2_Inputs2N;

extern volatile DIOC1_TXMSG1_REG PGUREC_DIOC1_Outputs;
extern volatile DIOC2_TXMSG1_REG PGUREC_DIOC2_Outputs;


//TCPU CAN Messages
// TCPU MSG1 Bit Definitions */
struct TCPU_RXMSG1_BITS {   // bits   description
    Uint16 Trac_Null:1;                         // 0
    Uint16 MC1_NO:1;                            // 1
    Uint16 MC2_NO:1;                            // 2
    Uint16 PCC1_NO:1;                           // 3
    Uint16 PCC2_NO:1;                           // 4
    Uint16 Insulation_Device_STA:1;             // 5
    Uint16 Traction_ACTIVE:1;                   // 6
    Uint16 EDB_ACTIVE:1;                        // 7
    Uint16 MCB_ON:1;                            // 8
    Uint16 RSVD1:1;                             // 9
    Uint16 Trac_CuttOff:1;                      // 10
    Uint16 Emerge_LOOP:1;                       // 11
    Uint16 RSVD:4;                              // 15:12

};

typedef union{
   Uint16                all;
   struct TCPU_RXMSG1_BITS   bit;
}TCPU_RXMSG1_REG;

//TCPU CAN Messages
// TCPU MSG2 Bit Definitions */
struct TCPU_RXMSG2_BITS {   // bits   description
    Uint16 ID1:1;                       // 0
    Uint16 ID2:1;                       // 1
    Uint16 ID3:1;                       // 2
    Uint16 ID4_Checksum:1;              // 3
    Uint16 ID5:1;                       // 4
    Uint16 MCAUX_STA1:1;                // 5
    Uint16 MCBTrip_STA:1;               // 6
    Uint16 MCBOFF_STA:1;                // 7
    Uint16 LocoEnable:1;                // 8
    Uint16 Condansator_Pressure:1;      // 9
    Uint16 Limit_Switch:1;        // 10
    Uint16 MCAUX_STA2:1;                // 11
    Uint16 RSVD1:3;                     // 15:12
};

typedef union{
   Uint16                all;
   struct TCPU_RXMSG2_BITS   bit;
}TCPU_RXMSG2_REG;

//TCPU CAN Messages
// TCPU MSG3 Bit Definitions */
struct TCPU_RXMSG3_BITS {   // bits   description
    Uint16 Mot_Over_Cur:1;                       // 0
    Uint16 DC_Over_Volt:1;                       // 1
    Uint16 Rect_Input_Cur1:1;                    // 2
    Uint16 Rect_Input_Cur2:1;                    // 3
    Uint16 OVP_Over_Cur:1;                       // 4
    Uint16 RSVD1:1;                              // 5
    Uint16 Catenary_Over_Volt:1;                 // 6
    Uint16 RSVD2:1;                              // 7
    Uint16 RSVD3:1;                              // 8
    Uint16 RSVD4:6;                              // 15:9
};

typedef union{
   Uint16                all;
   struct TCPU_RXMSG3_BITS   bit;
}TCPU_RXMSG3_REG;

//TCPU CAN Messages
// TCPU MSG4 Bit Definitions */
struct TCPU_RXMSG4_BITS {   // bits   description
    Uint16 GPLV:1;                       // 0
    Uint16 Batlow:1;                     // 1
    Uint16 VD2_5V:1;                     // 2
    Uint16 VD1_5V:1;                     // 3
    Uint16 VA_5V_N:1;                    // 4
    Uint16 VA_5V_P:1;                    // 5
    Uint16 VA_24V_N:1;                   // 6
    Uint16 VA_24V_P:1;                   // 7
    Uint16 CFD:1;                        // 8
    Uint16 M1_FSP:1;                     // 9
    Uint16 M2_FSP:1;                     // 10
    Uint16 Insulation_Mont_Dev:1;        // 11
    Uint16 EDB_Active:1;                 // 12
    Uint16 MCB_ON:1;                     // 13
    Uint16 Trac_CutOff:1;                // 14
    Uint16 Emerge_Loop:1;                // 15
};

typedef union{
   Uint16                all;
   struct TCPU_RXMSG4_BITS   bit;
}TCPU_RXMSG4_REG;

//TCPU CAN Messages
// TCPU MSG2 Bit Definitions */
struct TCPU_RXMSG5_BITS {   // bits   description
    Uint16 MC_Trip:1;                  // 0
    Uint16 MCB_Trip:1;                 // 1
    Uint16 HgOff:1;                    // 2
    Uint16 Hrectrig:1;                 // 3
    Uint16 OVP:1;                      // 4
    Uint16 RSVD:11;                    // 15:5
};

typedef union{
   Uint16                all;
   struct TCPU_RXMSG5_BITS   bit;
}TCPU_RXMSG5_REG;


// TCPU MSG2 Bit Definitions */
struct TCPU_TXMSG_BITS {    // bits   description
    Uint16 MCCAUX1_SIG:1;                       // 0
    Uint16 PCC1_SIG:1;                          // 1
    Uint16 MCB_TRIP:1;                          // 2
    Uint16 RVSD1:1;                             // 3
    Uint16 TRAC_ACTIVE_SIG:1;                   // 4
    Uint16 EDB_ACTIVE_SIG:1;                    // 5
    Uint16 Cooling_Contactor_FANS:1;            // 6
    Uint16 CKU_FAN:1;                           // 7
    Uint16 Cooling_Contactor_PUMP:1;            // 8
    Uint16 MCCAUX2_SIG:1;                       // 9
    Uint16 System_RST:1;                        // 10
    Uint16 PCC2_SIG:1;                          // 11
    Uint16 RSVD:5;                              // 15:12
};

typedef union{
   Uint16                all;
   struct TCPU_TXMSG_BITS   bit;
}TCPU_TXMSG_REG;

extern volatile TCPU_RXMSG1_REG PGUREC_TCPU_Inputs;
extern volatile TCPU_RXMSG2_REG PGUREC_TCPU_DIOC_Inputs;
extern volatile TCPU_RXMSG3_REG PGUREC_TCPU_Faults_TIC;
extern volatile TCPU_RXMSG4_REG PGUREC_TCPU_Faults_Others;
extern volatile TCPU_RXMSG5_REG PGUREC_TCPU_Fault_Action;


extern volatile TCPU_TXMSG_REG PGUREC_TCPU_Outputs;

#endif /* PGUREC_MAINISR_H_ */
