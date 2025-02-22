#include "main.h"

//====================================================
//	MAIN LOOP
//====================================================
void main(void)
{

// ***************************************************
// DSP System, clock, pin and interrupt initializations
// ***************************************************

  	InitSysCtrl();								// System Control and Clock Settings
	InitDSPPeripherals();                       // DSP Pin Function Assignments
	InitPieCtrl();								// PIE Control Initialization
	InitPieVectTable();							// Initialize PIE vector table to a known state.

// ***************************************************
// DSP Peripheral Configurations PGUREC_ADCErrFlags
// ***************************************************

   ConfigXintf();                              // Configure Xintf Faults

// ***************************************************
// Copy time critical code and Flash setup code to RAM
// The  ***_loadstart, ***_loadend, and ***_runstart
// symbols are created by the linker. Refer to the linker command files.
// ***************************************************

    memcpy(&ramfuncs_runstart,&ramfuncs_loadstart,(Uint32)&ramfuncs_loadsize);
    memcpy(&econst_runstart,&econst_loadstart,(Uint32)&econst_loadsize);
    memcpy(&text_runstart,&text_loadstart,(Uint32)&text_loadsize);

// ***************************************************
// Call Flash Initialization to setup flash waitstates
// This function must reside in RAM
// ***************************************************

   InitFlash();                                // Call the flash wrapper init function

// ***************************************************
// DSP BIST Tests
// ***************************************************
   #if (BISTTEST)

//DualRamTestResult = I2CBasedRAMTest(&STestErr);

   DualRamTestResult = memTestAll((Uint16 *)DUALRAM_BASE, DUALRAM_LENGTH, 0x0000);

   if(DualRamTestResult != NULL)
       {
         STestErrFlags.bit.DUALRAM = 1;
       }

   ExtRamTestResult = memTestAll((Uint16 *)EXTRAM_BASE, EXTRAM_LENGTH, 0x0000);

   if(ExtRamTestResult != NULL)
       {
         STestErrFlags.bit.EXTRAM = 1;
       }

//ExtFlashTestResult = Check_SST_39VF800A();

   if(ExtFlashTestResult == 1)
       {
        STestErrFlags.bit.EXTFLASH = 1;
       }

// Emulator reset sonrasý I2CBasedRAMTest() fonksiyonunu tekrar çaðýrmamak için kontrol eklenecek..

   #endif

   GA = Tiva2DSPRegs.regs.GA;

 //  GA = 1;     // GA=1 ise PGU_REC, GA=2 ise PGU_INV


  //GA = (GA>3 ? 3 : GA);

   BuildTimeInit();

// ***************************************************
// SPI cofiguration for Temperature Measurement
// ***************************************************
   InitSPIADC();                               // Initialize SPI ADC

// ***************************************************
// SPI cofiguration for Hardware Fault
// ***************************************************
   InitSPIDAC();                               // Initialize SPI DAC
   InitSPIDAC2();                              // Initialize SPI DAC2

  while (EnableFlag==FALSE)                   // Waiting for enable flag set
      {
        DebugTicker++;
      }

#ifdef  LAB_DYNO

    ActivePGUCard = PGUREC;
    PGUREC_main();

#else
    if (GA==1)
    {
        ActivePGUCard = PGUREC;
        PGUREC_main();
    }
    else if (GA==2)
    {
        ActivePGUCard = PGUINV;
        PGUINV_main();
    }
    else
    {
        ActivePGUCard = PGU;
        // Kart atamasý hatalý.
    }
#endif

    // IDLE loop. Just sit and loop forever
    for(;;)
    {
        MonitorData[39] = GA;
        DELAY_US(1000*1000);
    }

} //END MAIN CODE

