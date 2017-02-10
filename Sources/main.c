/* ###################################################################
**     Filename    : main.c
**     Project     : MS3
**     Processor   : MKL46Z256VMC4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-03-09, 18:33, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "AD1.h"
#include "AdcLdd1.h"
#include "FC321.h"
#include "RealTimeLdd1.h"
#include "TU4.h"
#include "Bit1.h"
#include "BitIoLdd1.h"
#include "Bit2.h"
#include "BitIoLdd2.h"
#include "relay.h"
#include "BitIoLdd3.h"
#include "FC322.h"
#include "RealTimeLdd2.h"
#include "TU1.h"
#include "OVC.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "Send.h"
#include "TI2.h"
#include "TimerIntLdd2.h"
#include "TU3.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU2.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Math.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
uint16_t ch1;
uint16_t ch2;
uint16_t ch3;
uint16_t ch4;
float vch1;
float vch2;
volatile float v1;
volatile float i1;
volatile float cal;
float cal2;


int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */

{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  for(;;) 
  {
	  (void)AD1_Measure(TRUE);
	  (void)AD1_GetChanValue16(0,&ch1);
	  (void)AD1_GetChanValue16(1,&ch2);
	  (void)AD1_GetChanValue16(2,&ch3);
	  (void)AD1_GetChanValue16(3,&ch4);
	  vch1=(ch1*((3.3038/65535)));
	  vch2=(ch2*(3.3038/65535));
	  v1=(201.431*(vch1-(1.648+0.001*(cal-50))));
	  cal=(ch3*0.0015259);
	  cal2=((0.00003051*(ch4-32767))/2);
	  i1=((9.0909-cal2)*(vch2-1.651));
	  
  }
  
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
