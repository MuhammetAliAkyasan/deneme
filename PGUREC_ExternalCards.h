/*
 * PGUREC_ExternalCards.h
 *
 *  Created on: 30 Haz 2022
 *      Author: hasan.ertugrul
 */

#ifndef PGUREC_EXTERNALCARDS_H_
#define PGUREC_EXTERNALCARDS_H_

extern void     PGUREC_InitFOIO();
extern void     PGUREC_InitTCPU();
extern void     PGUREC_HWFaultLimitSet();
extern void     PGUREC_HWFaultLimitCalc();
extern void     PGUREC_TemperatureRead1();
extern void     PGUREC_TemperatureRead2();

#endif /* PGUDREC_EXTERNALCARDS_H_ */
