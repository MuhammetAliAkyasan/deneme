/*
 * PGUREC_ADC.h
 *
 *  Created on: 10 Eki 2018
 *      Author: fozturk
 */

#ifndef PGUREC_ADC_H_
#define PGUREC_ADC_H_

#define DCOFFSET              1.50            // DC offset for AC Channels , 1.50V
#define DCOFFSET1             1.498
#define DCOFFSET2             1.490
#define DCOFFSET3             1.494
#define DCOFFSET4             1.51
#define ADCCONVRATIO          (3.0/4095.0)    // ADC conversion ratio , 3.0/4095.0,  0-3 V:0-4095 Decimal
#define PGUREC_AICCHGAIN       1.0/1.0        // Analog Input Card channel gain
#define PGUREC_AICCHGAIN1      1.0/0.95       // Analog Input Card channel gain
#define PGUREC_AICCHGAIN2      1.0/0.98       // Analog Input Card channel gain
#define PGUREC_AICCHGAIN3      1.0/0.99       // Analog Input Card channel gain
#define PGUREC_AICCHGAIN4      1.0/0.93       // Analog Input Card channel gain

// Sensor Conversion Ratios
#define HRS1000                5000.0          // PETERCEM Current Sensor Ratio [A/A]
#define LTC1000_RATIO          5000.0          // LEM LTC_1000 Current Sensor Ratio [A/A]
#define LTC600S_RATIO          3000.0          // LEM LTC_600S Current Sensor Ratio [A/A]
#define DVM2000_RATIO          40000.0         // LEM DVM2000 Voltage Sensor Ratio [V/A]
#define Catenary_VT_RATIO      67820.0             // Voltage Transformer Ratio (Current Out))

#define RES_VOLT_Grid           27.4 //56.0     // DC Bus Voltage Sensor Measurement Resistor Value
#define RES_VOLT_DCBus          47.0 //56.0     // DC Bus Voltage Sensor Measurement Resistor Value
#define RES_CUR_RECT            8.20 //4.70           // 1ph PWM Rectifier Input Current Measurement Resistor Value
#define RES_VOLT_CAT            22.0            // Catenary Voltage Measurement Resistor Value - 6.2/10

#define PGUREC_ADC_ERR_INIT                    {0x0000}
//**************************************************************************
// ADC Channels and MACROs for PGU
//**************************************************************************
/*-----------------------------------------------------------------------------
    Define ADC Channels for PGU
-----------------------------------------------------------------------------*/

#define ADC_Res1           0    // Reserved Channel measurement                    @ ADC A0
#define ADC_Res2           1    // Reserved Channel measurement                    @ ADC A1
#define ADC_Res3           2    // Reserved Channel measurement                    @ ADC A2
#define ADC_VDC            3    // DC bus voltage measurement                      @ ADC A3
#define ADC_I_REC1         4    // 1ph PWM Rectifier Input Current (Sensor 1)      @ ADC A4
#define ADC_I_REC2         5    // 1ph PWM Rectifier Input Current (Sensor 2)      @ ADC A5
#define ADC_Res4           6    // Reserved Channel measurement                    @ ADC A6
#define ADC_V_Grid         7    // Reserved Channel measurement                    @ ADC A7
#define ADC_Res6           8    // Catanery Voltage                                @ ADC B0
#define ADC_Res7           9    // Reserved Channel measurement                    @ ADC B1
#define ADC_V_Catenary     10   // Reserved Channel measurement                    @ ADC B2
#define ADC_V_Ref          11   // 1.5 V Referans Current                          @ ADC B3
#define ADC_Res8           12   // Reserved Channel measurement                    @ ADC B4
#define ADC_Res9           13   // Reserved Channel measurement                    @ ADC B5
#define ADC_Res10          14   // Reserved Channel measurement                    @ ADC B6
#define ADC_Res11          15   // Reserved Channel measurement                    @ ADC B7

/*-----------------------------------------------------------------------------
    Define ADC Conversions for PGU
-----------------------------------------------------------------------------*/
#define PGUREC_ADC_CHANNELS   {                                                             \
                                ADC_VDC,         /* @ ADC A0 */ /*ADCRESULT0 */   \
                                ADC_VDC,         /* @ ADC A1 */ /*ADCRESULT1 */   \
                                ADC_VDC,         /* @ ADC A2 */ /*ADCRESULT2 */   \
                                ADC_I_REC1,         /* @ ADC A3 */ /*ADCRESULT3 */   \
                                ADC_I_REC1,         /* @ ADC A4 */ /*ADCRESULT4 */   \
                                ADC_I_REC1,         /* @ ADC A5 */ /*ADCRESULT5 */   \
                                ADC_I_REC2,           /* @ ADC A6 */ /*ADCRESULT6 */   \
                                ADC_I_REC2,           /* @ ADC A7 */ /*ADCRESULT7 */   \
                                                                                     \
                                ADC_I_REC2,           /* @ ADC B0*/ /*ADCRESULT8  */    \
                                ADC_V_Catenary,          /* @ ADC B1*/ /*ADCRESULT9  */    \
                                ADC_V_Catenary,          /* @ ADC B2*/ /*ADCRESULT10 */    \
                                ADC_V_Catenary,          /* @ ADC B3*/ /*ADCRESULT11 */    \
                                ADC_V_Grid,       /* @ ADC B4*/ /*ADCRESULT12 */    \
                                ADC_V_Grid,        /* @ ADC B5*/ /*ADCRESULT13 */    \
                                ADC_V_Grid,     /* @ ADC B6*/ /*ADCRESULT14 */    \
                                ADC_Res1,                                       \
                              }

/*-----------------------------------------------------------------------------
    Define the structure of the ADC Channels Object for PGU
-----------------------------------------------------------------------------*/
typedef struct {
                    float32 Volt_DCLink;             // Output: DC Bus Voltage Sensor-1 Measurement
                    float32 Cur_RectInput1;            // Output: 1 ph Rectifier Input Current Sensor Measurement
                    float32 Cur_RectInput2;            // Output: 1 ph Rectifier Input Current Sensor Measurement
                    float32 Volt_Grid;                // Output: Grid Voltage Measurement
                    float32 Volt_Catenary;            // Output: Cetanary Voltage Measurement
                }
PGUREC_MEASUREMENTVARIABLES;

typedef struct {
    PGUREC_MEASUREMENTVARIABLES     Result;        // Result = (ChValue-DCOffset)*Ratio-Offset;
    PGUREC_MEASUREMENTVARIABLES     ChValue;       // ChValue = ADCRESULTX *(3.0/4095.0);  ChValue: 0-3V range
    PGUREC_MEASUREMENTVARIABLES     DCOffset;      // Calibration Offset
    PGUREC_MEASUREMENTVARIABLES     Ratio;         // Ratio = (Sensor Ratio/R);
    PGUREC_MEASUREMENTVARIABLES     Offset;        // Measurement Offset
}
PGUREC_MEASUREMENT;

/*------------------------------------------------------------------------------
    Default Initializers for the ADC Measurement Object
------------------------------------------------------------------------------*/
#define PGUREC_MEASUREMENT_INIT {                                                      \
                                /*Result*/                                             \
                                0, 0, 0, 0, 0,                                         \
                                /*ChValue*/                                            \
                                0, 0, 0, 0, 0,                                         \
                                /*DCOffset*/                                           \
                                0.0, DCOFFSET, DCOFFSET, DCOFFSET,DCOFFSET,            \
                                /*Ratio*/                                              \
                                0, 0, 0, 0, 0,                                         \
                                /*Offset*/                                             \
                                0, 0, 0, 0, 0,                                         \
                              }
/*-----------------------------------------------------------------------------
    Measurement fault register bit definitions for PGUREC
-----------------------------------------------------------------------------*/
struct PGUREC_ADC_FLT_BITS {
                                        // bits   description
        Uint16 Volt_DCLink:1;           // 1
        Uint16 Cur_RectInput1:1;        // 2
        Uint16 Cur_RectInput2:1;        // 3
        Uint16 Volt_Grid:1;             // 4
        Uint16 Volt_Catenary:1;         // 5
        Uint16 Rsrvd:10;                // 15:6

};


typedef union{
   Uint16                       all;
   struct PGUREC_ADC_FLT_BITS    bit;
}PGUREC_ADC_FLT_REG;

/*-----------------------------------------------------------------------------
    Default Initializers for the PGUREC_MEASUREMENT_FLT_REG
-----------------------------------------------------------------------------*/
#define PGUREC_ADC_OFFSET_INIT {                 \
                20.0,    /* Volt_DCLink;    */      \
                60.0,    /* Cur_RectInput1;    */      \
                60.0,    /* Cur_RectInput2;    */      \
                60.0,   /* Volt_Grid;    */      \
                250.0,   /* Volt_Catenary;        */      \
                }

/*------------------------------------------------------------------------------
    PGUREC Measurement Ratio Calc. Macro
------------------------------------------------------------------------------*/
#define PGUREC_ADC_RATIO_CALC(v)                                                             \
                v.Ratio.Volt_DCLink        =   PGUREC_AICCHGAIN2*(DVM2000_RATIO       / RES_VOLT_DCBus      );                 \
                v.Ratio.Cur_RectInput1     =   PGUREC_AICCHGAIN2*(HRS1000             / RES_CUR_RECT);                 \
                v.Ratio.Cur_RectInput2     =   PGUREC_AICCHGAIN2*(HRS1000             / RES_CUR_RECT);                 \
                v.Ratio.Volt_Grid          =   PGUREC_AICCHGAIN2*(DVM2000_RATIO       / RES_VOLT_Grid);                 \
                v.Ratio.Volt_Catenary      =   PGUREC_AICCHGAIN2*(Catenary_VT_RATIO   / RES_VOLT_CAT );   /*  Potential Transformer Ratio= 1,000V/1mA  */                                      \


/*------------------------------------------------------------------------------
    PGUREC Measurement Ratio Calc. Macro
------------------------------------------------------------------------------*/
#define PGUREC_ADC_CHANNEL_READ(v)                                                                                                  \
                v.ChValue.Volt_DCLink          =   (AdcMirror.ADCRESULT0+AdcMirror.ADCRESULT1+AdcMirror.ADCRESULT2)*(1.0/3.0) * ADCCONVRATIO;         \
                v.ChValue.Cur_RectInput1       =   (AdcMirror.ADCRESULT3+AdcMirror.ADCRESULT4+AdcMirror.ADCRESULT5)*(1.0/3.0) * ADCCONVRATIO;        \
                v.ChValue.Cur_RectInput2       =   (AdcMirror.ADCRESULT6+AdcMirror.ADCRESULT7+AdcMirror.ADCRESULT8)*(1.0/3.0) * ADCCONVRATIO;        \
                v.ChValue.Volt_Grid            =   (AdcMirror.ADCRESULT12+AdcMirror.ADCRESULT13+AdcMirror.ADCRESULT14)*(1.0/3.0) * ADCCONVRATIO;        \
                v.ChValue.Volt_Catenary        =   (AdcMirror.ADCRESULT9+AdcMirror.ADCRESULT10+AdcMirror.ADCRESULT11)*(1.0/3.0) * ADCCONVRATIO;       \

/*------------------------------------------------------------------------------
    PGUREC Measurement Read Macro
------------------------------------------------------------------------------*/
#define PGUREC_ADC_MEASUREMENT(v)                                                                                                                                 \
    v.Result.Volt_DCLink            = ((v.ChValue.Volt_DCLink         - v.DCOffset.Volt_DCLink     ) * v.Ratio.Volt_DCLink)      - v.Offset.Volt_DCLink;           \
    v.Result.Cur_RectInput1         = ((v.ChValue.Cur_RectInput1       - v.DCOffset.Cur_RectInput1    ) * v.Ratio.Cur_RectInput1)     - v.Offset.Cur_RectInput1;   \
    v.Result.Cur_RectInput2         = ((v.ChValue.Cur_RectInput2       - v.DCOffset.Cur_RectInput2    ) * v.Ratio.Cur_RectInput2)     - v.Offset.Cur_RectInput2;   \
    v.Result.Volt_Grid              = ((v.ChValue.Volt_Grid           - v.DCOffset.Volt_Grid         ) * v.Ratio.Volt_Grid)     - v.Offset.Volt_Grid;              \
    v.Result.Volt_Catenary          = ((v.ChValue.Volt_Catenary       - v.DCOffset.Volt_Catenary    ) * v.Ratio.Volt_Catenary)     - v.Offset.Volt_Catenary;       \


#define PGUREC_ADC_OFFSET_COMP(v,div)                                                                                                  \
if(div==0.0)                                                                                                                        \
{                                                                                                                                   \
    v.Offset.Volt_DCLink        += ((v.ChValue.Volt_DCLink         - v.DCOffset.Volt_DCLink       ) * v.Ratio.Volt_DCLink       ) ;   \
    v.Offset.Cur_RectInput1     += ((v.ChValue.Cur_RectInput1      - v.DCOffset.Cur_RectInput1    ) * v.Ratio.Cur_RectInput1    ) ;   \
    v.Offset.Cur_RectInput2     += ((v.ChValue.Cur_RectInput2      - v.DCOffset.Cur_RectInput2    ) * v.Ratio.Cur_RectInput2    ) ;   \
    v.Offset.Volt_Grid          += ((v.ChValue.Volt_Grid           - v.DCOffset.Volt_Grid         ) * v.Ratio.Volt_Grid         ) ;    \
    v.Offset.Volt_Catenary      += ((v.ChValue.Volt_Catenary       - v.DCOffset.Volt_Catenary     ) * v.Ratio.Volt_Catenary     ) ;    \
}  \
else                                              \
{                                                 \
    v.Offset.Volt_DCLink        = 0.0;             \
    v.Offset.Cur_RectInput1    *= div;             \
    v.Offset.Cur_RectInput2    *= div;             \
    v.Offset.Volt_Grid         *= div;             \
    v.Offset.Volt_Catenary     *= div;             \
}                                                 \

//**************************************************************************
//
//**************************************************************************

extern Uint16                       PGUREC_DSPADCChSel[16];       //  ADC init macro channel assignment for PGUREC


extern PGUREC_MEASUREMENT              PGUREC_Measure;               //  ADC measurement instance and initialization
extern PGUREC_MEASUREMENTVARIABLES     PGUREC_ADCOffsets;            //  ADC measurement offset instance
extern PGUREC_ADC_FLT_REG              PGUREC_ADCErrFlags;

#endif /* PGUREC_ADC_H_ */

