/* ==============================================================================
System Name:    E5000 LOCO

File Name:      PGU_Inv3.c

Description:    E5000_LOCO - 1 ph PWM rectifier control

Originator:     E5000 project group

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 01-10-2018 Version 1.0
=================================================================================  */

#include "DSP28x_Project.h"
#include "PGU_Common.h"
#include "PGUREC_Common.h"

struct PGU_ETHRX_BITS {         // bits   description
    Uint16 PreCharge_Eth:1;             // 0    RampUp
    Uint16 MainContactor_Eth:1;           // 1    RampDown
    Uint16 MCB_Trip_Eth:1;               // 2    MELS1 - Cer naklinde arýza var ikaz lambasý
    Uint16 Reserved_Eth:1;              // 3    MSG1 - CKÜ patinaj ikaz lambasý
    Uint16 Traction_Eth:1;            // 4    Traction Active Signal
    Uint16 Edb_Eth:1;                  // 5    Pump Contactor - 5QA01
    Uint16 CabinFan_Eth:1;            // 6    Fan Contactor - 5QA02
    Uint16 CKUFan_Eth:1;             // 7    Discharge Contactor - 7QA01
    Uint16 CIFR_Eth:1;                 // 8    HVAC Contactor - 5QA04
    Uint16 SystemReset_Eth:1;            // 9 BEE4 Signal - QA02
    Uint16 Reserved2_Eth:6;             // 15:10 Reserved
    };

typedef union{
   Uint16                        all;
   struct PGU_ETHRX_BITS   bit;
}PGU_ETHRX_REG;
//
//struct PGU_ETHTX_BITS {         // bits   description
//    Uint16 MCCAUX_SIG:1;                      // 0
//    Uint16 PCC_SIG:1;                         // 1
//    Uint16 MCB_TRIP:1;                        // 2
//    Uint16 RVSD1:1;                           // 3
//    Uint16 TRAC_ACTIVE_SIG:1;                 // 4
//    Uint16 EDB_ACTIVE_SIG:1;                  // 5
//    Uint16 Cabin_FAN:1;                       // 6
//    Uint16 CKU_FAN:1;                         // 7
//    Uint16 CIFR:1;                            // 8
//    Uint16 System_RST:1;                      // 9
//    Uint16 Level1_STA:1;                // 0
//    Uint16 Level2_STA:1;                // 1
//    Uint16 Prefuse:1;                   // 2
//    Uint16 Emerge_DEGRADED:1;           // 3
//    Uint16 Emerge_POWER1:1;             // 4
//    Uint16 Emerge_POWER2:1;             // 5
//    Uint16 Emerge_POWER3:1;             // 6
//    Uint16 Direction_Forward:1;         // 7
//    Uint16 Direction_Backward:1;        // 8
//    Uint16 ID0:1;                       // 0
//    Uint16 ID1:1;                       // 1
//    Uint16 ID2:1;                       // 2
//    Uint16 ID3:1;                       // 3
//    Uint16 LimitSwitch:1;               // 4
//    Uint16 EarthSwitch:1;               // 5
//    Uint16 MCBTrip_STA:1;               // 6
//    Uint16 MCAUX_STA:1;                 // 7
//    Uint16 LocoEnable:1;                // 8
//    Uint16 MCBOFF_STA:1;                // 9
//    };
//
//typedef union{
//   Uint16                        all;
//   struct PGU_ETHTX_BITS   bit;
//}PGU_ETHTX_REG;
//
//
//


PGU_ETHRX_REG     PGU_DO_EthRx          = {0x0000};
//PGU_ETHTX_REG     PGU_DI_EthTx          = {0x0000};

void EthernetTest(void)
{

    PGU_DO_EthRx.all = EthRxData[13];//MonitorData[221];


//    if(PGU_DO_EthRx.bit.PreCharge_Eth == 1)
//            {
//                    IO_CLR(PCCSig)
//            }
//    else
//            {
//                    IO_SET(PCCSig)
//            }

//    if(PGU_DO_EthRx.bit.Traction_Eth == 1)
//            {
//                  IO_CLR(PGUREC_TractionON)
//            }
//    else
//            {
//                 IO_SET(PGUREC_TractionON)
//            }

//    if(PGU_DO_EthRx.bit.MainContactor_Eth == 1)
//            {
//                  IO_CLR(MCSig)
//            }
//    else
//            {
//                 IO_SET(MCSig)
//            }

    if(PGU_DO_EthRx.bit.MCB_Trip_Eth == 1)
            {
                //  IO_CLR(PGUREC_MCBTrip)
            }
    else
            {

               //  IO_SET(PGUREC_MCBTrip)
            }

    if(PGU_DO_EthRx.bit.CKUFan_Eth == 1)
            {
                    PGUREC_TCPU_Outputs.bit.CKU_FAN=0;
            }
    else
            {

                    PGUREC_TCPU_Outputs.bit.CKU_FAN=1;
            }

//    if(PGU_DO_EthRx.bit.CabinFan_Eth == 1)
//            {
//                  PGUREC_TCPU_Outputs.bit.Cabin_FAN=0;
//            }
//    else
//            {
//
//                  PGUREC_TCPU_Outputs.bit.Cabin_FAN=1;
//            }
//
//    if(PGU_DO_EthRx.bit.CIFR_Eth == 1)
//            {
//                  PGUREC_TCPU_Outputs.bit.CIFR=0;
//            }
//    else
//            {
//
//                  PGUREC_TCPU_Outputs.bit.CIFR=1;
//            }

    if(PGU_DO_EthRx.bit.Edb_Eth == 1)
            {
                    PGUREC_TCPU_Outputs.bit.EDB_ACTIVE_SIG=0;
            }
    else
            {

                    PGUREC_TCPU_Outputs.bit.EDB_ACTIVE_SIG=1;
            }

    if(PGU_DO_EthRx.bit.Reserved_Eth == 1)
            {
                    PGUREC_TCPU_Outputs.bit.RVSD1=0;
            }
    else
            {

                    PGUREC_TCPU_Outputs.bit.RVSD1=1;
            }

//    MonitorData[130]=DIOC_Inputs_TCPU.bit.EarthSwitch;
//    MonitorData[131]=DIOC_Inputs_TCPU.bit.LimitSwitch;
//    MonitorData[132]=DIOC_Inputs_TCPU.bit.MCBTrip_STA;
//    MonitorData[133]=DIOC_Inputs_TCPU.bit.LocoEnable;
//    MonitorData[134]=DIOC_Inputs_TCPU.bit.MCAUX_STA;
//    MonitorData[136]=DIOC_Inputs_TCPU.bit.MCBOFF_STA;
//    MonitorData[137]=DIOC_Inputs_TCPU.bit.ID0;
//    MonitorData[138]=DIOC_Inputs_TCPU.bit.ID1;
//    MonitorData[139]=DIOC_Inputs_TCPU.bit.ID2;
//    MonitorData[140]=DIOC_Inputs_TCPU.bit.ID3;
    MonitorData[141]=!PGUREC_TCPU_Inputs.bit.EDB_ACTIVE; //418
    MonitorData[142]=!PGUREC_TCPU_Inputs.bit.Emerge_LOOP; //420
//    MonitorData[143]=!PGUREC_TCPU_Inputs.bit.RSVD1; //422
    MonitorData[144]=!PGUREC_TCPU_Inputs.bit.Traction_ACTIVE; //424
    MonitorData[145]=!PGUREC_TCPU_Inputs.bit.Insulation_Device_STA; //426
//    MonitorData[146]=!IO_READ(PCCSig); //428
//    MonitorData[147]=!IO_READ(MCSig); //430
    MonitorData[148]=!PGUREC_TCPU_Inputs.bit.MCB_ON; //432
    MonitorData[149]=!PGUREC_TCPU_Inputs.bit.MC1_NO; //434
    MonitorData[150]=!PGUREC_TCPU_Inputs.bit.MC2_NO; //436
    MonitorData[151]=!PGUREC_TCPU_Inputs.bit.PCC1_NO; //438
    MonitorData[152]=!PGUREC_TCPU_Inputs.bit.PCC2_NO; //440
    MonitorData[153]=!PGUREC_TCPU_Inputs.bit.Trac_CuttOff; //442
//    MonitorData[154]=!IO_READ(EDB_CUTOUT);  //444
//    MonitorData[155]=!DIOC_Inputs1.bit.Direction_Backward; //446
//    MonitorData[156]=!DIOC_Inputs1.bit.Direction_Forward; //448
//    MonitorData[157]=!DIOC_Inputs1.bit.Emerge_DEGRADED; //450
//    MonitorData[158]=!DIOC_Inputs1.bit.Emerge_POWER1; //452
//    MonitorData[159]=!DIOC_Inputs1.bit.Emerge_POWER2; //454
//    MonitorData[160]=!DIOC_Inputs1.bit.Emerge_POWER3;  //456
    MonitorData[161]=!PGUREC_DIOC1_Inputs1.bit.Level1_STA; //458
    MonitorData[162]=!PGUREC_DIOC1_Inputs1.bit.Level2_STA; //460
//    MonitorData[163]=!DIOC_Inputs1.bit.Prefuse;  //462



}



