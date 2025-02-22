/*
 * PGUREC_Tasks.h
 *
 *  Created on: 11 Eki 2018
 *      Author: fozturk
 */

#ifndef PGUREC_TASKS_H_
#define PGUREC_TASKS_H_

// PGUREC_Tasks.c
extern void PGUREC_TaskInit(void);
extern void PGUREC_TaskLoop(void);
extern void PGUREC_A0(void);
extern void PGUREC_B0(void);
extern void PGUREC_C0(void);
extern void PGUREC_A1(void);
extern void PGUREC_A2(void);
extern void PGUREC_A3(void);
extern void PGUREC_B1(void);
extern void PGUREC_B2(void);
extern void PGUREC_B3(void);
extern void PGUREC_C1(void);
extern void PGUREC_C2(void);
extern void PGUREC_C3(void);
extern void (*PGUREC_Alpha_State_Ptr)(void);
extern void (*PGUREC_A_Task_Ptr)(void);
extern void (*PGUREC_B_Task_Ptr)(void);
extern void (*PGUREC_C_Task_Ptr)(void);

extern int16   PGUREC_VTimer0[4];     //  Virtual Timers slaved off CPU Timer 0 (A events)
extern int16   PGUREC_VTimer1[4];     //  Virtual Timers slaved off CPU Timer 1 (A events)
extern int16   PGUREC_VTimer2[4];     //  Virtual Timers slaved off CPU Timer 2 (A events)

extern float32 PriPowSign;
extern float32 SecPowSign;


#endif /* PGUREC_TASKS_H_ */
