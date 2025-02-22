/*
 * PGUREC_PWM.h
 *
 *  Created on: 10 Eki 2018
 *      Author: fozturk
 */

#ifndef PGUREC_PWM_H_
#define PGUREC_PWM_H_

//**************************************************************************
// Default PWMGEN Initializer Object for PGUREC
//**************************************************************************
/*-----------------------------------------------------------------------------
    Define the structure of the PWM Driver Object
-----------------------------------------------------------------------------*/
typedef struct {
        Uint16 PeriodMax;       // Parameter: PWM Half-Period in CPU clock cycles
        Uint16 Deadband;        // Parameter: PWM deadband in CPU clock cycles
        float32 MfuncC;         // Input: EPWMx A&B Duty cycle ratio   ETSEL.bit.SOCAEN
        }
PWMGEN ;

// Rectifier Parameters
#define PGUREC_ISR_FREQUENCY        0.8                                                  // Rectifier  ISR = 1050 Hz
#define PGUREC_MAINISR_S_DIV        8.0                                                  // Main ISR Sampling period / Rectifier Switching period
#define PGUREC_TS_SW                0.001/PGUREC_ISR_FREQUENCY                           // Rectifier Switching period (sec)
#define PGUREC_TS                   0.001/PGUREC_ISR_FREQUENCY/2.0                       // Rectifier Sampling period (sec)
#define PGUREC_TS_MAINISR           0.001/PGUREC_ISR_FREQUENCY/PGUREC_MAINISR_S_DIV
#define PGUREC_PWM_PERIOD           SYSTEM_FREQUENCY*1000000*PGUREC_TS_SW/4.0            // TBPRD = TBfreq / PWMfreq / 2 = (SYSCLKOUT / TBprescale) / PWMfreq / 2

#define PGUREC_MAINISR_PWM_PERIOD   PGUREC_PWM_PERIOD/PGUREC_MAINISR_S_DIV          // HS control loop period

#define PGUREC_PWM_DEADBAND         DB_4uS

#define PGUREC_RECPWM_GEN_INIT  {   PGUREC_MAINISR_PWM_PERIOD * PGUREC_MAINISR_S_DIV , \
                                    PGUREC_PWM_DEADBAND    ,   \
                                    0.0         ,   \
                                }

#define PGUREC_ISR_PWM_GEN_INIT {   PGUREC_MAINISR_PWM_PERIOD , \
                                    PGUREC_PWM_DEADBAND    ,   \
                                    0.0         ,       \
                                }

extern PWMGEN      PGUREC1_PWM1;            //  Rec-1 PWM instance and initialization
extern PWMGEN      PGUREC1_PWM2;            //  Rec-1 PWM instance and initialization

extern PWMGEN      PGUREC2_PWM1;            //  Rec-2 PWM instance and initialization
extern PWMGEN      PGUREC2_PWM2;            //  Rec-2 PWM instance and initialization

extern PWMGEN      PGUREC_IsrPWM;           //  ISR PWM instance and initialization


#endif /* PGUREC_PWM_H_ */
