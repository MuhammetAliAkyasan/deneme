/*
 *PGUREC_SWProtection.h
 *
 *  Created on: 11 Eki 2018
 *      Author: fozturk
 */

#ifndef PGUREC_SWPROTECTION_H_
#define PGUREC_SWPROTECTION_H_

#define FOIOGateOFF     IO_SET(PGUREC_SGOFF)
#define FOIOGateON      IO_CLR(PGUREC_SGOFF)

#define PGUGateOFF                        \
        EALLOW;                             \
        EPwm4Regs.TZFRC.bit.OST = 1;        \
        EPwm3Regs.TZFRC.bit.OST = 1;        \
        EPwm2Regs.TZFRC.bit.OST = 1;        \
        EPwm1Regs.TZFRC.bit.OST = 1;        \
        EDIS;

//#define PGUInvGateOFF                        \
//        EALLOW;                             \
//        EPwm6Regs.TZFRC.bit.OST = 1;        \
//        EPwm5Regs.TZFRC.bit.OST = 1;        \
//        EPwm3Regs.TZFRC.bit.OST = 1;        \
//        EDIS;

//#define PGUInvGateON                                                             \
//        EALLOW;                                                                 \
//        EPwm5Regs.TZFLG.all = 0;                                                \
//        EPwm5Regs.TZCLR.all = 0x4;      /* Clear trip zone OST event*/          \
//        EPwm6Regs.TZFLG.all = 0;                                                \
//        EPwm6Regs.TZCLR.all = 0x5;      /* Clear trip zone OST and INT event*/          \
//        EDIS;                                                                   \
//        PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

//#define PGUInvGateON                                                             \
//        EALLOW;                                                                 \
//        EPwm3Regs.TZFLG.all = 0;                                                \
//        EPwm3Regs.TZCLR.all = 0x4;      /* Clear trip zone OST event*/          \
//        EPwm5Regs.TZFLG.all = 0;                                                \
//        EPwm5Regs.TZCLR.all = 0x4;      /* Clear trip zone OST event*/          \
//        EPwm6Regs.TZFLG.all = 0;                                                \
//        EPwm6Regs.TZCLR.all = 0x4;      /* Clear trip zone OST and INT event*/          \
//        EDIS;

#define PGURecGateON                                                               \
        EALLOW;                                                                 \
        EPwm4Regs.TZFLG.all = 0;                                                \
        EPwm4Regs.TZCLR.all = 0x4;      /* Clear trip zone OST event*/          \
        EPwm3Regs.TZFLG.all = 0;                                                \
        EPwm3Regs.TZCLR.all = 0x4;      /* Clear trip zone OST event*/          \
        EPwm2Regs.TZFLG.all = 0;                                                \
        EPwm2Regs.TZCLR.all = 0x4;      /* Clear trip zone OST event*/          \
        EPwm1Regs.TZFLG.all = 0;                                                \
        EPwm1Regs.TZCLR.all = 0x5;      /* Clear trip zone OST event*/          \
        EDIS;                                                                   \
        PieCtrlRegs.PIEACK.all = PIEACK_GROUP2; // Acknowledge this interrupt to receive more interrupts    from group 2    (EPWM1_TZINT)
//
#define PGURec2GateON                                                               \
        EALLOW;                                                                 \
        EPwm4Regs.TZFLG.all = 0;                                                \
        EPwm4Regs.TZCLR.all = 0x4;      /* Clear trip zone OST event*/          \
        EPwm3Regs.TZFLG.all = 0;                                                \
        EPwm3Regs.TZCLR.all = 0x5;      /* Clear trip zone OST event*/          \
        EDIS;                                                                   \
        PieCtrlRegs.PIEACK.all = PIEACK_GROUP2; // Acknowledge this interrupt to receive more interrupts    from group 2    (EPWM1_TZINT)

#define PGURec1GateON                                                               \
        EALLOW;                                                                 \
        EPwm2Regs.TZFLG.all = 0;                                                \
        EPwm2Regs.TZCLR.all = 0x4;      /* Clear trip zone OST event*/          \
        EPwm1Regs.TZFLG.all = 0;                                                \
        EPwm1Regs.TZCLR.all = 0x5;      /* Clear trip zone OST event*/          \
        EDIS;                                                                   \
        PieCtrlRegs.PIEACK.all = PIEACK_GROUP2; // Acknowledge this interrupt to receive more interrupts    from group 2    (EPWM1_TZINT)




//
//#define PGURecUGateON                                                               \
//        EALLOW;                                                                 \
//        EPwm1Regs.TZFLG.all = 0;                                                \
//        EPwm1Regs.TZCLR.all = 0x4;      /* Clear trip zone OST event*/          \
//        EDIS;
//#define PGURecVGateON                                                               \
//        EALLOW;                                                                 \
//        EPwm2Regs.TZFLG.all = 0;                                                \
//        EPwm2Regs.TZCLR.all = 0x4;      /* Clear trip zone OST event*/          \
//        EDIS;
//#define PGUInvUGateON                                                               \
//        EALLOW;                                                                 \
//        EPwm3Regs.TZFLG.all = 0;                                                \
//        EPwm3Regs.TZCLR.all = 0x4;      /* Clear trip zone OST event*/          \
//        EDIS;                                                                   \
//        PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
//#define PGUInvVGateON                                                               \
//        EALLOW;                                                                 \
//        EPwm4Regs.TZFLG.all = 0;                                                \
//        EPwm4Regs.TZCLR.all = 0x4;      /* Clear trip zone OST event*/          \
//        EDIS;                                                                   \
//        PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
//#define PGUInvWGateON                                                               \
//        EALLOW;                                                                 \
//        EPwm6Regs.TZFLG.all = 0;                                                \
//        EPwm6Regs.TZCLR.all = 0x4;      /* Clear trip zone OST event*/          \
//        EDIS;
//#define PGUInvUVGateON                                                               \
//        EALLOW;                                                                 \
//        EPwm3Regs.TZFLG.all = 0;                                                \
//        EPwm3Regs.TZCLR.all = 0x4;      /* Clear trip zone OST event*/          \
//        EPwm5Regs.TZFLG.all = 0;                                                \
//        EPwm5Regs.TZCLR.all = 0x4;      /* Clear trip zone OST event*/          \
//        EDIS;

extern void     PGUREC_TemperatureProtection1(PGUREC_TEMPERATURE_CKU1 temp,PGUREC_TEMPERATURE_CKU1 warn,       PGUREC_TEMPERATURE_CKU1 err,       PGUREC_TEMPSTS_REG_CKU1 *warnflag, PGUREC_TEMPSTS_REG_CKU1 *errflag);
extern void     PGUREC_TemperatureProtection2(PGUREC_TEMPERATURE_CKU2 temp,PGUREC_TEMPERATURE_CKU2 warn,       PGUREC_TEMPERATURE_CKU2 err,       PGUREC_TEMPSTS_REG_CKU2 *warnflag, PGUREC_TEMPSTS_REG_CKU2 *errflag);
extern void     PGUREC_SWProtection(PGUREC_SWPROT Fdbs, PGUREC_SWPROTLEVELS WarnLimits, PGUREC_SWPROTLEVELS   ErrLimits, PGUREC_SWPROTFLT_REG * WarnFlags, PGUREC_SWPROTFLT_REG * ErrFlags, PGUREC_SWPROTCOUNT * ErrTime,PGUREC_SWPROTCOUNT * ErrCount);
extern void     PGUREC_SWProtectionCatenary(PGUREC_SWPROT_Catenary Fdbs, PGUREC_SWPROTLEVELS_Catenary WarnLimits, PGUREC_SWPROTLEVELS_Catenary ErrLimits, PGUREC_SWPROTFLTCatenary_REG * WarnFlags, PGUREC_SWPROTFLTCatenary_REG * ErrFlags , PGUREC_SWPROTCOUNTCatenary * ErrTime,PGUREC_SWPROTCOUNTCatenary * ErrCount);

#endif /* PGUREC_SWPROTECTION_H_ */
