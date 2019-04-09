/* µ÷ÊÔ */
/* Ìá¹©printf×Ó³ÌÐòºÍÑÓÊ±º¯Êý */

#ifndef	__DEBUG_H__
#define __DEBUG_H__

//¶¨Òåº¯Êý·µ»ØÖµ
#ifndef  SUCCESS
#define  SUCCESS  0
#endif
#ifndef  FAIL
#define  FAIL    0xFF
#endif

//¶¨Òå¶¨Ê±Æ÷ÆðÊ¼
#ifndef  START
#define  START  1
#endif
#ifndef  STOP
#define  STOP    0
#endif

#ifndef  DE_PRINTF
#define  DE_PRINTF     1
#endif
#define	 FREQ_SYS	     6000000	         //ÏµÍ³Ö÷Æµ12MHz
#ifndef  UART0_BUAD
#define  UART0_BUAD    9600
#define  UART1_BUAD    9600
#endif

void	CfgFsys( );                        //CH554Ê±ÖÓÑ¡ÔñºÍÅäÖÃ
void	mDelayuS( UINT16 n );              // ÒÔuSÎªµ¥Î»ÑÓÊ±
void	mDelaymS( UINT16 n );              // ÒÔmSÎªµ¥Î»ÑÓÊ±
void  CH554UART0Alter();                 //CH554´®¿Ú0Òý½ÅÓ³Éäµ½P0.2/P0.3
void	mInitSTDIO( );                      //T1×÷Îª²¨ÌØÂÊ·¢ÉúÆ÷
UINT8 CH554UART0RcvByte( );              //CH554 UART0²éÑ¯·½Ê½½ÓÊÕÒ»¸ö×Ö½Ú
void  CH554UART0SendByte(UINT8 SendDat); //CH554UART0·¢ËÍÒ»¸ö×Ö½Ú

void	UART1Setup( );                     //
UINT8 CH554UART1RcvByte( );              //CH554 UART1²éÑ¯·½Ê½½ÓÊÕÒ»¸ö×Ö½Ú
void  CH554UART1SendByte(UINT8 SendDat); //CH554UART1·¢ËÍÒ»¸ö×Ö½Ú

void CH554WDTModeSelect(UINT8 mode);     //CH554¿´ÃÅ¹·Ä£Ê½ÉèÖÃ 
void CH554WDTFeed(UINT8 tim);            //CH554¿´ÃÅ¹·Î¹¹·
#endif
