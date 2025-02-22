/* ==============================================================================
System Name:  	E5000 E5 Bucuk Tests

File Name:		PGU_REC.h

Description:	E5 Bucuk - 1 ph PWM rectifier control

Originator:		GA - HFE

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 26.03.2020	Version 1.0
=================================================================================  */

#ifndef PGU_REC_H_
#define PGU_REC_H_

/*-------------------------------------------------------------------------------
Next, Include project specific include files.
-------------------------------------------------------------------------------*/

//***********  REC  ******************


#define REC_FDB_MACRO_1ps(r,m)                                                                                   \
    r.Volt_DCLink        = m.Result.Volt_DCLink;                      /* DC link Voltage 1               */      \
    r.Cur_RectInput1     = -1*m.Result.Cur_RectInput1;                     /* 1 ph Rectifier Input Current    */      \
    r.Cur_RectInput2     = -1*m.Result.Cur_RectInput2;                     /* 1 ph Rectifier Input Current    */      \
    r.Volt_Grid          = m.Result.Volt_Grid;                     /* Catenary Voltage                */      \
    r.Volt_Catenary      = m.Result.Volt_Catenary;                     /* Catenary Voltage                */      \
    r.Volt_RectInput     = m.Result.Volt_Catenary*(TRAFO_RATIO);      /* 1 ph Rectifier Input Current    */


#endif /* PGU_REC_H_ */
