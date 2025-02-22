/*
 * PGUREC_Globals.h
 *
 *  Created on: 10 Eki 2018
 *      Author: fozturk
 */

#ifndef PGUREC_GLOBALS_H_
#define PGUREC_GLOBALS_H_

// Master controller Reverse Switch register bit definitions */
struct REV_SWITCH_BITS {          // bits   description
   Uint16 INITIAL:1;            // 0
   Uint16 OFF:1;                // 1
   Uint16 FORWARD:1;            // 2
   Uint16 REVERSE:1;            // 3
   Uint16 rsvd:12;              // 15:4
};

union REV_SWITCH_REG {
   Uint16                 all;
   struct REV_SWITCH_BITS   bit;
};

// Master controller Main Handle register bit definitions */
struct MAIN_HANDLE_BITS {       // bits   description
   Uint16 POWERING:1;           // 0
   Uint16 NEUTRAL:1;            // 1
   Uint16 BRAKING:1;            // 2
   Uint16 EMG_BRAKE:1;          // 3
   Uint16 rsvd:12;              // 15:4
};

union MAIN_HANDLE_REG {
   Uint16                 all;
   struct MAIN_HANDLE_BITS   bit;
};

// Master controller Status register bit definitions */
struct MASTER_STA_BITS {       // bits   description
   Uint16 REV_SW_EN:1;          // 0
   Uint16 MAIN_H_EN:1;          // 1
   Uint16 POWER_OFF:1;          // 2
   Uint16 rsvd2:1;              // 3
   Uint16 rsvd3:12;             // 15:4
};

union MASTER_STA_REG {
   Uint16                 all;
   struct MASTER_STA_BITS   bit;
};

//  Define the structure of the Master Controller Object

typedef struct {
   union  REV_SWITCH_REG     REV_SW;     // Master controller Reverse Switch register
   union  MAIN_HANDLE_REG    MAIN_HAND;     // Master controller Main Handle register
   union  MAIN_HANDLE_REG    ENABLE;     // Master controller Main Handle register
   union  MASTER_STA_REG     STA;        // Master controller Status register
   float32                   TORQUEREF;  // Torque reference
}MASTERC_REGS;


// Converter control register bit definitions */
struct CONVCTL_BITS {           // bits   description
   Uint16 ENABLE:1;             // 0   1: close 0: open
   Uint16 START:1;              // 1
   Uint16 STOP:1;               // 2
   Uint16 PAUSE:1;              // 3
   Uint16 RESET:2;              // 5:4
   Uint16 ON:1;                 // 6   Reserved1
   Uint16 POWER:1;              // 7   Reserved2
   Uint16 DEGRADED:1;           // 8
   Uint16 OPMODE:3;             // 11:9
   Uint16 STATE :4;             // 15:12
};

typedef union{
   Uint16                all;
   struct CONVCTL_BITS   bit;
}CONVCTL_REG;

// Torque limiters enable register bit definitions */
struct TORQUELIM_BITS {         // bits     description
   Uint16 TOTAL:1;              // 0        Total limiting enable
   Uint16 MOTSPEED:1;           // 1        Speed based limiting enable
   Uint16 TEMP:1;               // 2        Temperature based limiting enable
   Uint16 VDC:1;                // 3        Vdc based limiting enable
   Uint16 SUPPLYH:1;            // 4        Supply voltage (high) based limiting enable
   Uint16 SUPPLYL:1;            // 5        Supply voltage (low) based limiting enable
   Uint16 INPOW:1;              // 6        Input Power based limiting enable
   Uint16 rsvd:9;               // 15:7     Reserved
};

typedef union{
   Uint16                all;
   struct TORQUELIM_BITS   bit;
}TORQUELIM_REG;

// Converter Fault register bit definitions */
struct CONVFLT_BITS {           // bits   description
    Uint16 STEST:1;             // 0
    Uint16 ADC:1;               // 1
    Uint16 SWPROT:1;            // 2
    Uint16 TEMP:1;              // 3
    Uint16 CONTAC:1;            // 4
    Uint16 HWPROT:1;            // 5
    Uint16 VSSYNC:1;            // 6
    Uint16 CTL:1;               // 7
    Uint16 PRECH:1;             // 8
    Uint16 VSPOL:1;             // 9
    Uint16 STELHS:1;            // 10      Tiva HandShake Error
    Uint16 rsvd1:5;             // 15:10   Reserved1
};

typedef union {
   Uint16                all;
   struct CONVFLT_BITS   bit;
}CONVFLT_REG;


typedef struct  {
    float32 DCinit;
    float32 DClimit;
    float32 Energy;
    Uint16  Ticker1;
    Uint16  Ticker2;
    Uint16  PCCopentime;
    Uint16  PCCmaxclosetime;
    Uint16  MCmaxclosetime;
    Uint16  DCbuildtime;
}PRECH;

#define PRECH_INIT {        \
                0.0,        /*DCinit , Precharge start DC voltage */\
                50.0,       /*DClimit , 90 % of DC voltage */\
                0.0,        /*Precharge Energy */\
                0,          /*Ticker1*/\
                0,          /*Ticker2*/\
                1600,       /*PCCopentime, 50 ms Ticker * n, Ticker period = 1/2100*/\
                800,       /*PCCmaxclosetime, 500 ms Ticker * n, Ticker period = 1/2100*/\
                1600,       /*MCmaxclosetime, 500 ms*/\
                4800,       /*DCbuildtime, 1s*/   \
                }

/*-----------------------------------------------------------------------------
    Define the structure of the Temperature Measurement Object
-----------------------------------------------------------------------------*/
typedef struct {
        float32 RectifierTemp1;       // Output: NTC   Type
        float32 RectifierTemp2;       // Output: NTC   Type
        float32 CabinTemp;            // Output: NTC   Type
        float32 ConvHumidity_Temp;    // Output: NTC   Type
        float32 ConvHumidity_Hum;     // Output: NTC   Type
        float32 MotorTemp1;           // Output: PT100 Type
        float32 MotorTemp2;           // Output: PT100 Type
        float32 MotorTemp3;           // Output: PT100 Type
        float32 GearTemp;          // Output: PT100 Type
        }
PGUREC_TEMPERATURE_CKU1 ;

typedef struct {
        float32 RectifierTemp1;       // Output: NTC   Type
        float32 RectifierTemp2;       // Output: NTC   Type
        float32 CabinTemp;            // Output: NTC   Type
        float32 CoolingFlow_Flow;    // Output: NTC   Type
        float32 CoolingFlow_Temp;    // Output: NTC   Type
        float32 MotorTemp1;          // Output: PT100 Type
        float32 MotorTemp2;          // Output: PT100 Type
        float32 MotorTemp3;          // Output: PT100 Type
        float32 GearTemp;            // Output: PT100 Type
        }
PGUREC_TEMPERATURE_CKU2 ;

/*-----------------------------------------------------------------------------
    Define the structure of the Temperature Measurement Object
-----------------------------------------------------------------------------*/
typedef struct {
        Uint16 RECTTemp1;           //  NTC   Type
        Uint16 RECTTemp2;           //  NTC   Type
        Uint16 CABINTemp;            //  NTC   Type
        Uint16 CABINHum_Temp;            //  NTC   Type
        Uint16 CABINHum_Hum;             // Output: Humidity Sensor
        Uint16 MOTTemp1;            // Output: PT100 Type
        Uint16 MOTTemp2;            // Output: PT100 Type
        Uint16 MOTTemp3;            // Output: PT100 Type
        Uint16 GEARTemp;         // Output: PT100 Type
}
PGUREC_TEMP_CHSEL_CKU1 ;

/*-----------------------------------------------------------------------------
    Define the structure of the Temperature Measurement Object
-----------------------------------------------------------------------------*/
typedef struct {
        Uint16 RECTTemp1;           //  NTC   Type
        Uint16 RECTTemp2;           //  NTC   Type
        Uint16 CABINTemp;            //  NTC   Type
        Uint16 COOLFlow_Flow;            //  NTC   Type
        Uint16 COOLFlow_Temp;            //  NTC   Type
        Uint16 MOTTemp1;            // Output: PT100 Type
        Uint16 MOTTemp2;            // Output: PT100 Type
        Uint16 MOTTemp3;            // Output: PT100 Type
        Uint16 GEARTemp;         // Output: PT100 Type
}
PGUREC_TEMP_CHSEL_CKU2 ;

/*------------------------------------------------------------------------------
    Default Initializers for the Temperature Measurement Object
------------------------------------------------------------------------------*/
#define PGUREC_TEMP_MEAS_INIT_CKU1    { 0, 0, 0, 0, 0, 0, 0, 0, 0 }
#define PGUREC_TEMP_MEAS_INIT_CKU2    { 0, 0, 0, 0, 0, 0, 0, 0, 0 }

/*------------------------------------------------------------------------------
    Default Initializers for the Temperature Protection Warning Limit Object
------------------------------------------------------------------------------*/
#define PGUREC_TEMP_WARN_INIT_CKU1     { 70.0, 70.0, 70.0, 70.0, 70.0, 70.0, 70.0, 70.0, 70.0 }
#define PGUREC_TEMP_WARN_INIT_CKU2     { 70.0, 70.0, 70.0, 70.0, 70.0, 70.0, 70.0, 70.0, 70.0 }

/*------------------------------------------------------------------------------
    Default Initializers for the Temperature Protection Error Limit Object
------------------------------------------------------------------------------*/
#define PGUREC_TEMP_ERR_INIT_CKU1      { 80.0, 80.0, 80.0, 80.0, 80.0, 80.0, 80.0, 80.0, 80.0 }
#define PGUREC_TEMP_ERR_INIT_CKU2      { 80.0, 80.0, 80.0, 80.0, 80.0, 80.0, 80.0, 80.0, 80.0}

/*------------------------------------------------------------------------------
    Default Initializers for the Temperature Channel selection and sensor type Object
------------------------------------------------------------------------------*/
#define PGUREC_TEMP_CHSEL_INIT_CKU1   { PGUREC_RECTTEMP1, PGUREC_RECTTEMP2, PGUREC_CABINTEMP, PGUREC_CONVHUM_TEMP , PGUREC_CONVHUM_HUM,    PGUREC_MOTTEMP1, PGUREC_MOTTEMP2,  PGUREC_MOTTEMP3, PGUREC_GEARTEMP  }
#define PGUREC_TEMP_CHSEL_INIT_CKU2    { PGUREC_RECTTEMP1, PGUREC_RECTTEMP2, PGUREC_CABINTEMP, PGUREC_COOLFLOW_FLOW, PGUREC_COOLFLOW_TEMP, PGUREC_MOTTEMP1, PGUREC_MOTTEMP2,  PGUREC_MOTTEMP3, PGUREC_GEARTEMP  }


// Temperature Fault register bit definitions */
struct PGUREC_TEMPSTS_BITS_CKU1 {                   // bits   description
      Uint16 RECTTemp1:1;         //  0
      Uint16 RECTTemp2:1;         //  1
//    Uint16 RSVD1:1;             //
//    Uint16 RSVD2:1;             //
//    Uint16 RSVD3:1;             //
      Uint16 CABINTemp:1;         //  2
      Uint16 CABINHum_Temp:1;     //  3
      Uint16 CABINHum_Hum:1;      //  4
//    Uint16 RSVD4:1;             //
//    Uint16 RSVD5:1;             //
      Uint16 MOTTemp1:1;          //  5
      Uint16 MOTTemp2:1;          //  6
      Uint16 MOTTemp3:1;          //  7
      Uint16 GEARTemp:1;       //  8
//      Uint16 RSVD3:1;           //
      Uint16 Rsvd:7;              //  15-9
};

typedef union{
   Uint16                       all;
   struct PGUREC_TEMPSTS_BITS_CKU1    bit;
}PGUREC_TEMPSTS_REG_CKU1;

// Temperature Fault register bit definitions */
struct PGUREC_TEMPSTS_BITS_CKU2 {                   // bits   description
      Uint16 RECTTemp1:1;          //  0
      Uint16 RECTTemp2:1;          //  1
//    Uint16 RSVD1:1;              //
//    Uint16 RSVD2:1;              //
//    Uint16 RSVD3:1;              //
      Uint16 CABINTemp:1;          //   2
//    Uint16 RSVD4:1;              //
//    Uint16 RSVD5:1;              //
      Uint16 COOLFlow_Flow:1;      //  3
      Uint16 COOLFlow_Temp:1;      //  4
      Uint16 MOTTemp1:1;           //  5
      Uint16 MOTTemp2:1;           //  6
      Uint16 MOTTemp3:1;           //  7
      Uint16 GEARTemp:1;        //  8
//    Uint16 RSVD7:1;              //
      Uint16 Rsvd:7;               //  15-9
};

typedef union{
   Uint16                       all;
   struct PGUREC_TEMPSTS_BITS_CKU2    bit;
}PGUREC_TEMPSTS_REG_CKU2;

// Software Protection Fault register bit definitions */
struct PGUREC_SWPROTFLT_BITS {         // bits   description
    Uint16 Is1OC:1;              // 0    Secondary Over Current
    Uint16 Is2OC:1;              // 1    Secondary Over Current
    Uint16 Rec1OL:1;             // 2    Rectifier Over Load
    Uint16 Rec2OL:1;             // 3    Rectifier Over Load
    Uint16 VdcOV:1;              // 4    DC voltage Over
    Uint16 VdcLV:1;              // 5   DC voltage Low
    Uint16 Is_Unbalanced:1;      // 6   DC voltage Sensor Fault
    Uint16 Rsvd:9;               //  15-7
      };

typedef union{
   Uint16                        all;
   struct PGUREC_SWPROTFLT_BITS   bit;
}PGUREC_SWPROTFLT_REG;



// Software Protection Fault register bit definitions */
struct PGUREC_SWPROTFLTCatenary_BITS {         // bits   description
    Uint16 VsOV:1;              // 0    Supply Over Voltage
    Uint16 VsLV:1;              // 1    Supply Low Voltage
    Uint16 VsWave:1;            // 2    Supply voltage waveform fault
    Uint16 VsOFreq:1;           // 3    Supply voltage waveform fault
    Uint16 VsLFreq:1;           // 4    Supply voltage waveform fault
    Uint16 Vs_Low_PF:1;              // 5    Supply voltage waveform fault
    Uint16 Rsvd:10;             //  15-5
    };

typedef union{
   Uint16                        all;
   struct PGUREC_SWPROTFLTCatenary_BITS   bit;
}PGUREC_SWPROTFLTCatenary_REG;





/*-----------------------------------------------------------------------------
 Contactor control register bit definitions  Uint32
-----------------------------------------------------------------------------*/

struct CONTACTOR_BITS {         // bits     description
   Uint16 STATUS:1;             // 0        Contactor Status 1: close 0: open
   Uint16 OPEN:1;               // 1        Contactor Open Signal
   Uint16 CLOSE:1;              // 2        Contactor Close Signal
   Uint16 rsvd:1;               // 3        Reserved
   Uint16 TIMER:12;             // 4:15     Contactor timer
};

typedef union{
   Uint16             all;
   struct CONTACTOR_BITS   bit;
}CONTACTOR_REG;

/*-----------------------------------------------------------------------------
Contactor Fault Flags bit definitions
-----------------------------------------------------------------------------*/

struct CONTACFLT_BITS {         // bits     description
   Uint16 MC_OER:1;             // 0        Main Contactor Open Error
   Uint16 MC_CER:1;             // 1        Main Contactor Close Error
   Uint16 PCC_OER:1;            // 2        Precharge Contactor Open Error
   Uint16 PCC_CER:1;            // 3        Precharge Contactor Close Error
   Uint16 ESC_NO:1;             // 4        Earting Switch Contactor not opened
   Uint16 PCC_NC:1;             // 5        Precharge Contactor not closed
   Uint16 CNTC_OP:1;            // 6        Contactors opened
   Uint16 rsvd:9;               // 7:15     Reserved
};

typedef union{
   Uint16             all;
   struct CONTACFLT_BITS   bit;
}CONTACFLT_REG;




/*-----------------------------------------------------------------------------
   PreCharge control register bit definitions
-----------------------------------------------------------------------------*/

struct PRECCTL_BITS {           // bits   description
   Uint16 START:1;              // 0
   Uint16 STATE:5;              // 5:1
   Uint16 STATUS:5;             // 10:6
   Uint16 rsvd:5;               // 15:11
};

typedef union{
   Uint16                all;
   struct PRECCTL_BITS   bit;
}PRECCTL_REG;


/*-----------------------------------------------------------------------------
    Define the structure of the Software Protection Levels Object
-----------------------------------------------------------------------------*/
typedef struct {
    float32 Is1OC;               //  Secondary-1 Over Current
    float32 Is2OC;               //  Secondary-2 Over Current
    float32 Rec1OL;              //  Rectifier-1 Over Load (kVA)
    float32 Rec2OL;              //  Rectifier-2 Over Load (kVA)
    float32 VdcOV;               //  DC voltage Over
    float32 VdcLV;               //  DC voltage Low
    float32 Is_Unbalanced;       //  Secondary Current Sensor Fault
        }
PGUREC_SWPROTLEVELS ;


typedef struct {
    float32 VsOV;               //  Supply Over Voltage
    float32 VsLV;               //  Supply Low Voltage
    float32 VsWave;             //  Supply voltage waveform fault
    float32 VsOFreq;            //  Supply Voltage Over frequency
    float32 VsLFreq;            //  Supply Voltage Low frequency
    float32 Vs_Low_PF;               //  Supply Voltage Low frequency
            }
PGUREC_SWPROTLEVELS_Catenary ;

/*------------------------------------------------------------------------------
    Default Initializers for the Software Protection Warning Limit Object
------------------------------------------------------------------------------*/
#define PGUREC_SWPROT_WARN_INIT      {   400.0,         400.0,      450.0,    450.0,                \
                                        2050.0,      1600.0,    50.0,                  \
                                     }


#define PGUREC_SWPROTCatenary_WARN_INIT      {   1500.0,   700.0,         70.0,        50.5,            \
                                                 49.5,    0.98                                         \
                                            }

/*------------------------------------------------------------------------------
    Default Initializers for the Software Protection Error Limit Object
------------------------------------------------------------------------------*/
#define PGUREC_SWPROT_ERR_INIT    {   500.0,         500.0,      500.0,    500.0,                \
                                     2150.0,      1400.0,    100.0,                  \
                                 }


#define PGUREC_SWPROTCatenary_ERR_INIT     { 1248.0,     728.0,         70.0,      50.0,          \
                                             49.0                                                \
                                          }
/*-----------------------------------------------------------------------------
    Define the structure of the Software Protection Levels Object
-----------------------------------------------------------------------------*/
typedef struct {
    float32 Is1OC;               //  Secondary-1 Over Current
    float32 Is2OC;               //  Secondary-2 Over Current
    float32 Rec1OL;              //  Rectifier-1 Over Load (kVA)
    float32 Rec2OL;              //  Rectifier-2 Over Load (kVA)
    float32 VdcOV;               //  DC voltage Over
    float32 VdcLV;               //  DC voltage Low
    float32 Is_Unbalanced;       //  Secondary Current Sensors Fault (Unbalanced load)
           }
PGUREC_SWPROTCOUNT ;


typedef struct {
    Uint16 VsOV;                //  Supply Over Voltage
    Uint16 VsLV;                //  Supply Low Voltage
    Uint16 VsWave;              //  Supply voltage waveform fault
    Uint16 VsOFreq;             //  Supply voltage over frequency
    Uint16 VsLFreq;             //  Supply voltage low frequency
    Uint16 Vs_Low_PF;                //  Supply voltage low frequency
               }
PGUREC_SWPROTCOUNTCatenary ;

/*------------------------------------------------------------------------------
    Default Initializers for the Software Protection Counter Object
------------------------------------------------------------------------------*/
#define PGUREC_SWPROT_COUNT_INIT     { 0,0,0,0,0,      \
                                      0,0          \
                                    }

#define PGUREC_SWPROTCatenary_COUNT_INIT     { 0,0,0,0,0,0}


/*-----------------------------------------------------------------------------
    Define the structure of the Software Protection Object
-----------------------------------------------------------------------------*/
typedef struct {
    float32 Is1;                 //  Secondary Current-1
    float32 Is2;                 //  Secondary Current-2
    float32 Rec1InPow;           //  Rectifier Input Power-1
    float32 Rec2InPow;           //  Rectifier Input Power-2
    float32 Vdc;                 //  DC voltage
    float32 IsDiff;              //  Difference between two secondary current sensors
        }
PGUREC_SWPROT ;


typedef struct {
    float32 Vs;                 //  Supply Voltage
    float32 VsWave;             //  Supply voltage waveform
    float32 VsFreq;             //  Supply voltage frequency
    float32 VsPowFac;           //  Supply voltage power factor
         }
PGUREC_SWPROT_Catenary ;

typedef struct {
    float32 Est         ;
    float32 EstFF       ;
    float32 EstErr      ;
    float32 ErrPll1_2pu ;
    float32 Harm        ;
}VS;

/*------------------------------------------------------------------------------
    Default Initializers for the Software Protection Object
------------------------------------------------------------------------------*/
#define PGUREC_SWPROT_INIT            {  0.0,0.0,0.0,0.0,0.0,0.0}

#define PGUREC_SWPROTCatenay_INIT     {  0.0,0.0,0.0,0.0 }


/*-----------------------------------------------------------------------------
    Define the structure of the Hardware Protection Limit Objects
-----------------------------------------------------------------------------*/
typedef struct {
        float32 VDCA1ErrVoltage;       // Output: DC Bus sensor-1 over voltage limit value
        float32 RICC1ErrVoltage;       // Output: DC Bus sensor-2 over voltage limit value
        float32 RICC2ErrVoltage;        // Output: 1 ph rectifier input over current limit value
        float32 COVErrVoltage;         // Output: Catenary over voltage limit value
        float32 Rsvd1;                 // Output: Reserved channel limit value
        float32 Rsvd2;                 // Output: Not used Channel
        }
PGUREC_HWPROT ;

/*------------------------------------------------------------------------------
    Default Initializers for the Hardware Protection DAC Limit Object
------------------------------------------------------------------------------*/
#define PGUREC_HW_PROT_DAC_LIMITS_INIT    {  2.0, 2.0, 2.0, 2.0, 2.0, 2.0 }


/*------------------------------------------------------------------------------
    Default Initializers for the Hardware Protection Levels Object
------------------------------------------------------------------------------*/
#define PGUREC_HW_PROT_LEVELS_INIT    {                                                      \
        0.0,        /* Reserved channel limit value*/                                       \
        0.0,        /* Reserved channel limit value*/                                       \
        0.0,        /* Reserved channel limit value*/                                       \
        0.0,        /* Reserved channel limit value*/                                       \
        0.0,        /* Reserved channel limit value*/                                       \
        0.0,        /* Reserved channel limit value*/                                       \
        }


typedef struct  {
    float32     Rms;
    float32     Freq;
    float32     Harm;
}SUPPLY;
typedef struct  {
    float32     Peak     ;
    float32     PeakSum  ;
    float32     Freq     ;
    float32     FreqSum  ;
    float32     Harm     ;
    float32     HarmSum  ;
    float32     Harm3    ;
    float32     Harm3Sum ;
    float32     Harm5    ;
    float32     Harm5Sum ;
    float32     Harm7    ;
    float32     Harm7Sum ;
    Uint16      Counter;
}SUPPLYMEAN;


#define SUPPLYMEAN_MACRO(v)                             \
    if(v.Counter == PGUREC_MAINISR_S_DIV/2)                            \
    {                                                   \
        v.Peak      = v.PeakSum  * (2/PGUREC_MAINISR_S_DIV);  /*  !!!(1/5)*/  \
        v.Freq      = v.FreqSum  * (2/PGUREC_MAINISR_S_DIV);  /*  !!!(1/5)*/  \
        v.Harm      = v.HarmSum  * (2/PGUREC_MAINISR_S_DIV);  /*  !!!(1/5)*/  \
        v.Harm3     = v.Harm3Sum * (2/PGUREC_MAINISR_S_DIV);  /*  !!!(1/5)*/  \
        v.Harm5     = v.Harm5Sum * (2/PGUREC_MAINISR_S_DIV);  /*  !!!(1/5)*/  \
        v.Harm7     = v.Harm7Sum * (2/PGUREC_MAINISR_S_DIV);  /*  !!!(1/5)*/  \
    }                                                   \
    v.FreqSum   = 0.0;                              \
    v.PeakSum   = 0.0;                              \
    v.HarmSum   = 0.0;                              \
    v.Harm3Sum  = 0.0;                              \
    v.Harm5Sum  = 0.0;                              \
    v.Harm7Sum  = 0.0;                              \
    v.Counter = 0;


typedef struct {
    float32 Vdc_Est ;
    float32 Vdc_BSF ;
    float32 Idc_BSF ;
}DC;

// Görünen güç hesabý için kullanýlan deðiþkenler
typedef struct  {
    float32     Power;              // Ortalama Güç
    float32     MeanSum;            // Ortalama almak için kullanýlan toplam
}POWERA;

// Gerçek güç hesabý için kullanýlan deðiþkenler
typedef struct  {
    float32     Power;              // Ortalama Güç
    float32     MeanSum;            // Ortalama almak için kullanýlan toplam
    float32     PeriodSum;          // Gerçek güç hesabý için 1 periyot boyunca güç toplamý
}POWERR;


//--MACRO VARIABLES and INSTANCES
extern MASTERC_REGS         PGUREC_MasterContr;
extern TORQUELIM_REG        TORQLIM_REG;

extern CONVCTL_REG          PGUREC_CTL_REG;
extern CONVFLT_REG          PGUREC_FLT_REG;

extern VS                   Vs;

extern PGUREC_TEMPSTS_REG_CKU1    PGUREC_TempErrFlags_CKU1;
extern PGUREC_TEMPSTS_REG_CKU1    PGUREC_TempWarnFlags_CKU1;

extern PGUREC_TEMPSTS_REG_CKU2    PGUREC_TempErrFlags_CKU2;
extern PGUREC_TEMPSTS_REG_CKU2    PGUREC_TempWarnFlags_CKU2;

extern PGUREC_SWPROTFLT_REG  PGUREC_SWProtErrFlags;
extern PGUREC_SWPROTFLT_REG  PGUREC_SWProtWarnFlags;

extern PGUREC_SWPROTFLTCatenary_REG  PGUREC_SWProtCatenaryErrFlags;
extern PGUREC_SWPROTFLTCatenary_REG  PGUREC_SWProtCatenaryWarnFlags;

extern PGUREC_TEMPERATURE_CKU1    PGUREC_Temperature_CKU1;        //  Temperature measurement instance and initialization
extern PGUREC_TEMPERATURE_CKU1    PGUREC_TemperatureLPF_CKU1;     //  Temperature measurement instance and initialization
extern PGUREC_TEMPERATURE_CKU1    PGUREC_TempWarnLimits_CKU1;     //  Temperature measurement warning limits
extern PGUREC_TEMPERATURE_CKU1    PGUREC_TempErrLimits_CKU1;      //  Temperature measurement error limits

extern PGUREC_TEMP_CHSEL_CKU1     PGUREC_Temperature_ChSel_CKU1;    //  Temperature measurement channel selection and sensor types

extern PGUREC_TEMPERATURE_CKU2    PGUREC_Temperature_CKU2;        //  Temperature measurement instance and initialization
extern PGUREC_TEMPERATURE_CKU2    PGUREC_TemperatureLPF_CKU2;      //  Temperature measurement instance and initialization
extern PGUREC_TEMPERATURE_CKU2    PGUREC_TempWarnLimits_CKU2;     //  Temperature measurement warning limits
extern PGUREC_TEMPERATURE_CKU2    PGUREC_TempErrLimits_CKU2;      //  Temperature measurement error limits

extern PGUREC_TEMP_CHSEL_CKU2     PGUREC_Temperature_ChSel_CKU2;    //  Temperature measurement channel selection and sensor types



extern PGUREC_SWPROT         PGUREC_SWProtFdbs;        //  Software Protection Feedback Signals
extern PGUREC_SWPROTLEVELS   PGUREC_SWProtWarnLimits;  //  Software Protection Feedback Signals warning limits
extern PGUREC_SWPROTLEVELS   PGUREC_SWProtErrLimits;   //  Software Protection Feedback Signals error limits
extern PGUREC_SWPROTCOUNT    PGUREC_SWProtErrTime;
extern PGUREC_SWPROTCOUNT    PGUREC_SWProtErrCount;


extern PGUREC_SWPROT_Catenary         PGUREC_SWProtFdbsCatenary;
extern PGUREC_SWPROTLEVELS_Catenary   PGUREC_SWProtWarnLimitsCatenary;           //  Feedback Signals warning limits
extern PGUREC_SWPROTLEVELS_Catenary   PGUREC_SWProtErrLimitsCatenary;            //  Feedback Signals error limits
extern PGUREC_SWPROTCOUNTCatenary     PGUREC_SWProtErrTimeCatenary;
extern PGUREC_SWPROTCOUNTCatenary     PGUREC_SWProtErrCountCatenary;



extern PGUREC_HWPROT         PGUREC_DACChannels;    //  HW Protection DAC Limits (0-3V range)
extern PGUREC_HWPROT         PGUREC_HWProtLevels;       //  HW Protection Levels (actual values)

extern CONTACTOR_REG    PCC1_REG;
extern CONTACTOR_REG    PCC2_REG;

extern CONTACTOR_REG    MCAUX_REG1;
extern CONTACTOR_REG    MCAUX_REG2;

extern PRECCTL_REG      PRECHCTL_REG1;
extern PRECCTL_REG      PRECHCTL_REG2;


extern CONTACFLT_REG    PGU_ContacErrFlags1;
extern CONTACFLT_REG    PGU_ContacErrFlags2;


extern PRECH           PreCh;


extern CONVFLT_REG          PGUDM_FLT_REG;

extern  SUPPLY          Supply;
extern  SUPPLYMEAN      SupplyMean;
extern CONVFLT_REG          PGUDM2_FLT_REG;

extern  POWERA          ApparentP_p;
extern  POWERR          RealP_p;
extern  POWERA          ApparentP_s;
extern  POWERR          RealP_s;

extern  DC              Dc;

#endif /* PGUREC_GLOBALS_H_ */
