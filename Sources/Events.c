/* ###################################################################
**     Filename    : Events.c
**     Project     : MS3
**     Processor   : MKL46Z256VMC4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-03-09, 18:33, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
#include "Math.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL46Z256MC4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
float vabs, iabs, vp1, ip1, v, i, vp=0, ip, vrms1, vrms2, vrms, irms1, irms2, irms, p, pa;
int a1, cn=0, cn1=0, ms, count, count1, tm;
uint16_t  Vs, Is, Ps, Zs;
int timer=0;
int sc=0;

void Cpu_OnNMIINT(void)
{

}

/*
** ===================================================================
**     Event       :  AD1_OnEnd (module Events)
**
**     Component   :  AD1 [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void AD1_OnEnd(void)
{
extern volatile float v1;
extern volatile float i1;
v=v1;
i=i1;
vabs=fabs(v);
iabs=fabs(i);
ms=1;


if((vabs>vp1)&&(vabs>2))
{
	vp1=vabs;
	cn=0;
	
}

if((vabs<2)&&(cn==0))
{
vp=vp1;
vp1=0;
cn=1;
vrms1=((vp)/sqrt(2));
FC321_Reset();
}

FC321_GetTimeMS(&tm);

if (tm>=800)
{
vp=0;
vp1=0;
vrms=0;
vrms1=0;
}
if (count<1000)
{
	vrms2=vrms2+vrms1;
	count++;
}
if (count>=1000)
{
	vrms=(vrms2/1000);
	vrms2=0;
	count=0;
}







if((iabs>ip1))
{
	if (iabs>0.05)
	{
	ip1=iabs;
	cn1=0;
	}
}
if((iabs<0.05))
{
if((cn1==0))
{
ip=ip1;
ip1=0;
cn1=1;
irms1=((ip)/sqrt(2));
}
}
if (count1<1000)
{
	irms2=irms2+irms1;
	count1++;
}
if (count1>=1000)
{
	irms=(irms2/1000);
	irms2=0;
	count1=0;
}
if (irms<=0.110){irms=0;}
if ((vrms<=5)){vrms=0;}



}

/*
** ===================================================================
**     Event       :  AD1_OnCalibrationEnd (module Events)
**
**     Component   :  AD1 [ADC]
**     Description :
**         This event is called when the calibration has been finished.
**         User should check if the calibration pass or fail by
**         Calibration status method./nThis event is enabled only if
**         the <Interrupt service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AD1_OnCalibrationEnd(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnError (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnError(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnRxChar (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
char rev[18];
int indxrv=0,msrr;;
char rvch;
void AS1_OnRxChar(void)
{	
	AS1_RecvChar(&rvch);
	Bit1_NegVal();
	rev[indxrv]=rvch;
	indxrv++;
	Bit2_PutVal(!(rev[10]-48));
	relay_PutVal((rev[10]-48));
	if (indxrv>13)indxrv=0;
}

/*
** ===================================================================
**     Event       :  AS1_OnTxChar (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnTxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnFullRxBuf (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnFullRxBuf(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnFreeTxBuf (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnFreeTxBuf(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  Send_OnCounterRestart (module Events)
**
**     Component   :  Send [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if counter overflow/underflow or counter is
**         reinitialized by modulo or compare register matching.
**         OnCounterRestart event and Timer unit must be enabled. See
**         [SetEventMask] and [GetEventMask] methods. This event is
**         available only if a [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void Send_OnCounterRestart(LDD_TUserData *UserDataPtr)
{
	a1=1;	
}

/*
** ===================================================================
**     Event       :  TI1_OnInterrupt (module Events)
**
**     Component   :  TI1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void TI1_OnInterrupt(void)
{
if (a1==1)
{
	  Vs = vrms;
	  Is = (irms*100);
	  Ps = p;
	  Zs = (pa*100);
	  
	  AS1_ClearTxBuf();
	  AS1_SendChar('\n');
	  AS1_SendChar('s');
	  AS1_SendChar('v');
	  AS1_SendChar(((Vs/100)%10)+48);
	  AS1_SendChar(((Vs/10)%10)+48);
	  AS1_SendChar(((Vs)%10)+48);
	  	  
	  
 
	  AS1_SendChar('-');
	  
	  AS1_SendChar('i');
	  AS1_SendChar(((Is/1000)%10)+48);
	  AS1_SendChar(((Is/100)%10)+48);
	  AS1_SendChar(((Is/10)%10)+48);
	  AS1_SendChar(((Is)%10)+48);
	  
	  
	  
	  
	  AS1_SendChar('-');
	  
	  AS1_SendChar('p');
	  AS1_SendChar(((Ps/1000)%10)+48);
	  AS1_SendChar(((Ps/100)%10)+48);
	  AS1_SendChar(((Ps/10)%10)+48);
	  AS1_SendChar(((Ps)%10)+48);

	  AS1_SendChar('-');
	  
	  AS1_SendChar('z');
	  AS1_SendChar(((Zs/100000)%10)+48);
	  AS1_SendChar(((Zs/10000)%10)+48);
	  AS1_SendChar(((Zs/1000)%10)+48);
	  AS1_SendChar(((Zs/100)%10)+48);
	  AS1_SendChar(((Zs/10)%10)+48);
	  AS1_SendChar(((Zs)%10)+48);

	  AS1_SendChar('e');
	  int rele;
	  rele=(relay_GetVal());
	  AS1_SendChar(rele+48);
	  AS1_SendChar(' ');
	  AS1_SendChar('/');
      a1=0;
	
	}
}

/*
** ===================================================================
**     Event       :  TI2_OnInterrupt (module Events)
**
**     Component   :  TI2 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TI2_OnInterrupt(void)
{
	  p=vrms*irms;
	  pa=(pa+(p/3600));
	  
}

/*
** ===================================================================
**     Event       :  OVC_OnCounterRestart (module Events)
**
**     Component   :  OVC [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if counter overflow/underflow or counter is
**         reinitialized by modulo or compare register matching.
**         OnCounterRestart event and Timer unit must be enabled. See
**         [SetEventMask] and [GetEventMask] methods. This event is
**         available only if a [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void OVC_OnCounterRestart(LDD_TUserData *UserDataPtr)
{
	
	if (irms>=2.2&&sc==0)
	{
	relay_PutVal(0);
	Bit2_PutVal(1);
	FC322_Enable();
	FC322_Reset();
	sc=1;
	}
	if (sc==1)
	{FC322_GetTimeMS(&timer);
	if (timer>4000)
	{
		FC322_Disable();
		FC322_Reset();
		relay_PutVal(1);
		Bit2_PutVal(0);
		sc=0;		
	}
	}
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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
