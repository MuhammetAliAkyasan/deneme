/*
 * PGUREC_CtrlGlobals.h
 *
 *  Created on: 15 Eki 2018
 *      Author: fozturk
 */
//  A0

#ifndef PGUREC_CTRLGLOBALS_H_
#define PGUREC_CTRLGLOBALS_H_

#define PGUREC_ADCOffsetPRD	      (1600.0)        // 1600Hz kontrol döngüsü = 1 Saniye
#define PGUREC_ADCChNUM		      (5)			 // Okuma yapýlan ADC kanal sayýsý
#define PGUREC_TEMPChNUM_CKU1     (9)             // Ölçüm yapýlan sýcaklýk sayýsý
#define PGUREC_TEMPChNUM_CKU2     (9)             // Ölçüm yapýlan sýcaklýk sayýsý


// Rectifier control register bit definitions */
struct RCTL_BITS {          	// bits   description
   Uint16 Enable:2;         	// 0
   Uint16 CtrlState:2;          // 1
   Uint16 CtrlStart:1;          // 2
   Uint16 TripSource:1;         // 3
   Uint16 TripForce:1;        	// 4
   Uint16 Reset:1;       		// 6
   Uint16 PoweringMode:1;       // 7
   Uint16 RegenMode:1;       	// 8
   Uint16 CapacitivePF:1;       // 9
   Uint16 InductivePF:1;       // 10
   Uint16 rsvd2:4;       		// 15-11
};

typedef union{
   Uint16             	 all;
   struct RCTL_BITS   bit;
}PGUREC_CTRL_VAR;


typedef struct  {

    float32 Volt_DCLink;          // Output: 1 ph Rectifier Input Voltage Sensor Measurement
    float32 Cur_RectInput1;
    float32 Cur_RectInput2;
    float32 Volt_Grid;        // Input : 1 ph Rect Input Voltage 1
    float32 Volt_Catenary;        // Input : 1 ph Rect Input Voltage 1
    float32 Volt_RectInput;       // Input : 1 ph Rect Input Voltage 1
}PGU_FDB_REC;


// Çekiþ referansý üretimi için kullanýlan deðiþkenler.
typedef struct  {
	float32 Ref;				// Koldan alýnan yöne göre anlamlandýrýlmýþ deðer. min:0.0 maks:1.0
	float32 RefLimited;			// Koruma aksiyonlarý sonucu sýnýrlandýrýlmýþ referans deðer
	float32 TotalLimFactor;		// Toplam limitleme faktörü 						min:0.0 maks:1.0
	float32	SpeedLimFactor;		// Hýz korumasý kaynaklý limitleme faktörü 			min:0.0 maks:1.0
	float32	TempLimFactor;		// Sýcaklýk korumasý kaynaklý limitleme faktörü 	min:0.0 maks:1.0
	float32	VdcLimFactor;		// DC gerilim korumasý kaynaklý limitleme faktörü 	min:0.0 maks:1.0
	float32	SupplyHLimFactor;	// Þebeke korumasý kaynaklý limitleme faktörü 		min:0.0 maks:1.0
	float32	SupplyLLimFactor;	// Þebeke korumasý kaynaklý limitleme faktörü 		min:0.0 maks:1.0
	float32	InPowLimFactor;		// Giriþ gücü korumasý kaynaklý limitleme faktörü 	min:0.0 maks:1.0
    float32 CapacitivePowLimFactor;     // Kapasitive güc kaynaklý limitleme faktörü   min:0.0 maks:1.0
    float32 InductivePowLimFactor;      // Kapasitive güc kaynaklý limitleme faktörü   min:0.0 maks:1.0
}TORQUE;

#define TORQUE_DEFAULTS { 	    							\
							(0.0),  /* Ref             */	\
							(0.0),  /* RefLimited      */	\
							(1.0),  /* TotalLimFactor  */	\
							(1.0),  /* SpeedLimFactor  */	\
							(1.0),  /* TempLimFactor   */	\
							(1.0),  /* VdcLimFactor    */	\
							(1.0),  /* SupplyHLimFactor*/	\
							(1.0),  /* SupplyLLimFactor*/	\
							(1.0)   /* InPowLimFactor  */   }

// Rejeneratif frenlemeyi hýza baðlý sýnýrlandýrmak için kullanýlan deðiþkenler.
typedef struct  {
	float32 SpeedRPM;		// Motor hýzý, CCW + olarak kabul edilir.
	float32 LimFactor;		// Limiting factor min: 0.0 maks:1.0
	float32	SpeedRPMLim1;   // Rejeneratif frenin kesileceði hýz.
	float32	SpeedRPMLim2;   // Rejeneratif frenin sýnýrlandýrýlmaya baþlayacaðý hýz.
}REGEN;

#define REGEN_DEFAULTS { 	    								\
							(0.0),  /* SpeedRPM 	  */		\
							(1.0),  /* LimFactor  	  */		\
							(1.0),  /* SpeedRPMLim1 */			\
							(336.0)   /* SpeedRPMLim2 */		}

#endif /* PGUREC_CTRLGLOBALS_H_ */

