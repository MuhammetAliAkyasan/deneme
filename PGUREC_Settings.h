/*
 * PGUREC_Settings.h
 *
 *  Created on: 30 Haz 2022
 *      Author: hasan.ertugrul
 */

#ifndef PGUREC_SETTINGS_H_
#define PGUREC_SETTINGS_H_

#define PLL_QSG_KP          0.98
#define PLL_QSG_KI          9.98
#define PLL_QSGPI_OUTMAX    10000.0
#define PLL_QSGPI_OUTMIN    -10000.0
#define CENTER_FREQUENCY     2*PI*50.0
#define VSQSG1_K            (1.414)
#define VSQSG2_K            (2)
#define VS_PEAK             (1450.0)//
#define VS_PEAK_MIN         (100.0)
#define VS_PEAK_MAX         (1800.0)//

#define TRAFO_RATIO         (0.042)         // 1050/25000

#define ISFF_K              (2.0)           // Normal katsayý = 2

#define RECPI_KP            (2.5)           //(0.25)//(2.5)//(1.0)           // 2 , 120  //1.3
#define RECPI_KI            (1.0)           //(0.00375)//(1.0)//(1.0)//(40.0)            //details in pid_reg3.h  //110
#define RECPI_KC            (0.0)           //details in pid_reg3.h

#define RS                  (0.1)           //Sekonder= 0.8V/9.93A = 86 mohm, Primer = 0.7V/8.8A= 79 mohm
#define Ls                  (0.0035)        //(0.0045)
#define FF_THETA            (0.2945243)     //(0.23562)//(0.2945243)     //(0.224399)//       // Feedforward angle for delayed signal sine1  0.286

#define REC_DUTY_MAX        (0.97)
#define REC_DUTY_MIN        (-0.97)

#define REC_VR_MAX          (1900.0)
#define REC_VR_MIN          (-1900.0)

#define RECIS_KP            (1.867)//(2.4)//(2.0)           // (1.5) 1.0 , 1.6

#define RECPI_OUTMAX        (250.0)//(250.0)//(100.0)
#define RECPI_OUTMIN        (-250.0)//(-250.0)//(-100.0)
#define VDC_MAX             (2000.0)////(840.0)//
#define VDC_MIN             (1400.0)////(560.0)//
#define VDC_REF_MAX         (1800.0)////(720.0)//
#define VDC_REF_MIN         (1250.0)//(560.0)//


#define PGUREC_1_PWM1      1               // Rectifier-1 U leg PWM @ EPWM1
#define PGUREC_1_PWM2      2               // Rectifier-1 V leg PWM @ EPWM2
#define PGUREC_2_PWM1      3               // Rectifier-2 U leg PWM @ EPWM1
#define PGUREC_2_PWM2      4               // Rectifier-2 V leg PWM @ EPWM2
#define PGUREC_RSV1        5               // Reserved PWM @ EPWM5
#define PGUREC_RSV2        6               // Reserved PWM @ EPWM6

#define ms_100          160                // 1600 = 1s;

#define PGUREC_FOIORst             GPADAT.bit.GPIO26         //PT_DSPClk
#define PGUREC_FDPCRst             GPADAT.bit.GPIO27         //PT_SWReset
#define PGUREC_SGOFF               GPBDAT.bit.GPIO48         // PGU_OptoEnable
#define PGUREC_WDTog               GPBTOGGLE.bit.GPIO49      //DSP_WDOG_TOGGLE
#define PGUREC_TZ1GPIO             GPADAT.bit.GPIO12         // TripZone1- FP_CFD
#define PGUREC_TZ2GPIO             GPADAT.bit.GPIO13         // TripZone2- TCPU_HgOFF
#define PGUREC_TZ3GPIO             GPADAT.bit.GPIO14         // TripZone3- FP_CFD2 (Unused)
#define PGUREC_TZ4GPIO             GPADAT.bit.GPIO15         // TripZone4- TP_Trip (Unused)

#define GPIO_FORWARD               GPBDAT.bit.GPIO50         // R-SP_A_BP
#define GPIO_REVERSE               GPBDAT.bit.GPIO51         // R-SP_B_BP
#define PGUREC_MCBTrip             GPBDAT.bit.GPIO58         // R-PT_IO1  MCB_Trip   ---> PT_IO5
#define PGUREC_to_PGUINV           GPBDAT.bit.GPIO59         // R-PT_IO2 (R-PT_IO2)  ---> I-RSV1_BP(pin goes to MCU input)
#define MCSig1                     GPBDAT.bit.GPIO60         // PT_IO3 Main contactor-1 auxiliary relay open/close
#define MCSig2                     GPBDAT.bit.GPIO61         // PT_IO4 Main contactor-2 auxiliary relay open/close

// Precharge contactors drive from CAN communication.

#define DO_ENABLE                  GPADAT.bit.GPIO20         // Digital output enable signal

//#define Normal_Mode                GPADAT.bit.GPIO22         // R-TP_IO1 <--- D2-DT_DI3_BP  (DIOC2_DI3=Normal Mode)(DIOC-2 TCU-ID geliyor. SetSeri de yok.)
#define MC1                        GPADAT.bit.GPIO23         // TP_IO2    (Main contactor1 NA)
#define MC2                        GPADAT.bit.GPIO25         // TP_IO3    (Main contactor2 NA)
//#define Rescue_Mode                GPADAT.bit.GPIO21         // R-TP_IO4 <--- D2-DT_DI4_BP  (DIOC2_DI4=Rescue Mode)(DIOC-2 TCU-ID geliyor. SetSeri de yok.)
#define MCB                        GPADAT.bit.GPIO24         // TP_IO5    (MCB On Status)

//// Over Voltage Protection
//#define OVPSig                     GPADAT.bit.GPIO7          // Over Voltage Protection  Null

// Task Periods
#define PGUREC_TASKA_PERIOD        mSec1
#define PGUREC_TASKB_PERIOD        mSec50
#define PGUREC_TASKC_PERIOD        mSec10

// Temperature Sensor types
#define NTCTYPE             0
#define NTC2TYPE            1
#define HUMTYPE_NTC         7
#define FLOWTYPE_NTC        8


// Cooling System Sensor types
#define HUMTYPE             2
#define FLOWTYPE            3
#define PT100TYPE           5


//--TIC channels--
#ifdef  LAB_DYNO

// NTC channels,        Sensor Type: 0
#define PGUREC_RECTTEMP1      0x0800  // Most significant two bytes:"ChNo", Least significant two bytes:"Sensor Type"
#define PGUREC_RECTTEMP2      0x0A00  // Most significant two bytes:"ChNo", Least significant two bytes:"Sensor Type"
//// PT100 chaneels,    Sensor Type: 1
#define PGUREC_MOTTEMP1      0x0301  // Most significant two bytes:"ChNo", Least significant two bytes:"Sensor Type"


#else

// NTC (30K) channels,      Sensor Type: 0
#define PGUREC_RECTTEMP1       0x0000  // Most significant two bytes:"ChNo", Least significant two bytes:"Sensor Type"
#define PGUREC_RECTTEMP2       0x0100  // Most significant two bytes:"ChNo", Least significant two bytes:"Sensor Type"

// NTC2 (2.2K) channels,    Sensor Type: 1
#define PGUREC_CABINTEMP       0x0400  // Most significant two bytes:"ChNo", Least significant two bytes:"Sensor Type"

// Humidity channels,       Sensor Type: 2
#define PGUREC_CONVHUM_TEMP    0x0607  // Most significant two bytes:"ChNo", Least significant two bytes:"Sensor Type"
#define PGUREC_CONVHUM_HUM     0x0702  // Most significant two bytes:"ChNo", Least significant two bytes:"Sensor Type"

//// Flow channels,           Sensor Type: 3
#define PGUREC_COOLFLOW_TEMP   0x0908  // Most significant two bytes:"ChNo", Least significant two bytes:"Sensor Type"
#define PGUREC_COOLFLOW_FLOW   0x0803  // Most significant two bytes:"ChNo", Least significant two bytes:"Sensor Type"

// PT100 channels,          Sensor Type: 5
#define PGUREC_MOTTEMP1        0x0A05  // Most significant two bytes:"ChNo", Least significant two bytes:"Sensor Type"
#define PGUREC_MOTTEMP2        0x0B05  // Most significant two bytes:"ChNo", Least significant two bytes:"Sensor Type"
#define PGUREC_MOTTEMP3        0x0C05  // Most significant two bytes:"ChNo", Least significant two bytes:"Sensor Type"
#define PGUREC_GEARTEMP        0x0D05  // Most significant two bytes:"ChNo", Least significant two bytes:"Sensor Type"

#endif

#endif /* PGUDREC_SETTINGS_H_ */
