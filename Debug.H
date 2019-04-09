
#ifndef	__DEBUG_H__
#define __DEBUG_H__

#ifndef  SUCCESS
#define  SUCCESS  0
#endif
#ifndef  FAIL
#define  FAIL    0xFF
#endif


#ifndef  START
#define  START  1
#endif
#ifndef  STOP
#define  STOP    0
#endif

#ifndef  DE_PRINTF
#define  DE_PRINTF     1
#endif
#define	 FREQ_SYS	     6000000	         
#ifndef  UART0_BUAD
#define  UART0_BUAD    9600
#define  UART1_BUAD    9600
#endif

void	CfgFsys( );                        
void	mDelayuS( UINT16 n );              
void	mDelaymS( UINT16 n );              
void  CH554UART0Alter();                 
void	mInitSTDIO( );                     
UINT8 CH554UART0RcvByte( );              
void  CH554UART0SendByte(UINT8 SendDat); 

void	UART1Setup( );                     
UINT8 CH554UART1RcvByte( );              
void  CH554UART1SendByte(UINT8 SendDat); 

void CH554WDTModeSelect(UINT8 mode);      
void CH554WDTFeed(UINT8 tim);            
#endif
