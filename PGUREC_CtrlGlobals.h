/*
 * PGUREC_CtrlGlobals.h
 *
 *  Created on: 15 Eki 2018
 *      Author: fozturk
 */
//  A0

#ifndef PGUREC_CTRLGLOBALS_H_
#define PGUREC_CTRLGLOBALS_H_

#define PGUREC_ADCOffsetPRD	      (1600.0)        // 1600Hz kontrol d�ng�s� = 1 Saniye
#define PGUREC_ADCChNUM		      (5)			 // Okuma yap�lan ADC kanal say�s�
#define PGUREC_TEMPChNUM_CKU1     (9)             // �l��m yap�lan s�cakl�k say�s�
#define PGUREC_TEMPChNUM_CKU2     (9)             // �l��m yap�lan s�cakl�k say�s�


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


// �eki� referans� �retimi i�in kullan�lan de�i�kenler.
typedef struct  {
	float32 Ref;				// Koldan al�nan y�ne g�re anlamland�r�lm�� de�er. min:0.0 maks:1.0
	float32 RefLimited;			// Koruma aksiyonlar� sonucu s�n�rland�r�lm�� referans de�er
	float32 TotalLimFactor;		// Toplam limitleme fakt�r� 						min:0.0 maks:1.0
	float32	SpeedLimFactor;		// H�z korumas� kaynakl� limitleme fakt�r� 			min:0.0 maks:1.0
	float32	TempLimFactor;		// S�cakl�k korumas� kaynakl� limitleme fakt�r� 	min:0.0 maks:1.0
	float32	VdcLimFactor;		// DC gerilim korumas� kaynakl� limitleme fakt�r� 	min:0.0 maks:1.0
	float32	SupplyHLimFactor;	// �ebeke korumas� kaynakl� limitleme fakt�r� 		min:0.0 maks:1.0
	float32	SupplyLLimFactor;	// �ebeke korumas� kaynakl� limitleme fakt�r� 		min:0.0 maks:1.0
	float32	InPowLimFactor;		// Giri� g�c� korumas� kaynakl� limitleme fakt�r� 	min:0.0 maks:1.0
    float32 CapacitivePowLimFactor;     // Kapasitive g�c kaynakl� limitleme fakt�r�   min:0.0 maks:1.0
    float32 InductivePowLimFactor;      // Kapasitive g�c kaynakl� limitleme fakt�r�   min:0.0 maks:1.0
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

// Rejeneratif frenlemeyi h�za ba�l� s�n�rland�rmak i�in kullan�lan de�i�kenler.
typedef struct  {
	float32 SpeedRPM;		// Motor h�z�, CCW + olarak kabul edilir.
	float32 LimFactor;		// Limiting factor min: 0.0 maks:1.0
	float32	SpeedRPMLim1;   // Rejeneratif frenin kesilece�i h�z.
	float32	SpeedRPMLim2;   // Rejeneratif frenin s�n�rland�r�lmaya ba�layaca�� h�z.
}REGEN;

#define REGEN_DEFAULTS { 	    								\
							(0.0),  /* SpeedRPM 	  */		\
							(1.0),  /* LimFactor  	  */		\
							(1.0),  /* SpeedRPMLim1 */			\
							(336.0)   /* SpeedRPMLim2 */		}

#endif /* PGUREC_CTRLGLOBALS_H_ */

