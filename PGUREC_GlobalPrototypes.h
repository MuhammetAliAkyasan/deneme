/*
 * PGUREC_GlobalPrototypes.h
 *
 *  Created on: 30 Haz 2022
 *      Author: hasan.ertugrul
 */

#ifndef PGUREC_GLOBALPROTOTYPES_H_
#define PGUREC_GLOBALPROTOTYPES_H_

extern void PGUREC_main(void);


// PGUREC_MainISR.c
extern void PGUREC_MainISRInit(void);
extern void PGUREC_ProtectionInit(void);

extern interrupt void PGUREC_MainISR(void);
extern void PGUREC_Protection(void);
extern void PGUREC_CommandProcess(void);
extern void ContacRoutine(void);
extern void PGUREC_CommandRead(void);
extern void PGU_PreChargeRoutine1(void);
extern void PGU_PreChargeRoutine2(void);

extern void PGUREC_TivaLifeCheck(Uint16 Time);

// PGUREC_TripZoneISR.c   VsSyncEnable
extern interrupt void PGUREC_TripZoneISR(void);

// PGU_REC.c - 1 Phase PWM Rectifier
extern void Rec1_Init(void);
extern void Rec1_ISR(void);


// PGU_Inv3.c - 3 Phase PWM Inverter
extern void  EthernetTest(void);


// PGUREC_Data.c
extern void PGUREC_WriteMonData(Uint16 WriteCount);
extern void PGUREC_WriteCANData(Uint16 WriteCount);
extern void PGUREC_ReadCANData(void);
extern void PGUREC_WriteFaultData(void);
extern void PGUREC_ReadMVBData(void);
extern void PGUREC_WriteMVBData(void);



#endif /* PGUDREC_GLOBALPROTOTYPES_H_ */

