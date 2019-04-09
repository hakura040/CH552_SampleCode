/********************************** (C) COPYRIGHT *******************************
* File Name          : Debug.C
* Author             : WCH
* Version            : V1.2
* Date               : 2018/02/26
* Description        : CH554 DEBUG Interface
*******************************************************************************/

#include "CH554.H"
#include "Debug.H"

/*******************************************************************************
* Function Name  : CfgFsys( )
* Description    : 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/ 
void	CfgFsys( )  
{
#if OSC_EN_XT	
		SAFE_MOD = 0x55;
		SAFE_MOD = 0xAA;
    CLOCK_CFG |= bOSC_EN_XT;                          //
    CLOCK_CFG &= ~bOSC_EN_INT;                         
#endif	
		SAFE_MOD = 0x55;
		SAFE_MOD = 0xAA;
#if FREQ_SYS == 24000000	
		CLOCK_CFG = CLOCK_CFG & ~ MASK_SYS_CK_SEL | 0x06;  // 24MHz	
#endif	
#if FREQ_SYS == 16000000		
		CLOCK_CFG = CLOCK_CFG & ~ MASK_SYS_CK_SEL | 0x05;  // 16MHz	
#endif
#if FREQ_SYS == 12000000		
		CLOCK_CFG = CLOCK_CFG & ~ MASK_SYS_CK_SEL | 0x04;  // 12MHz
#endif	
#if FREQ_SYS == 6000000		
		CLOCK_CFG = CLOCK_CFG & ~ MASK_SYS_CK_SEL | 0x03;  // 6MHz	
#endif	
#if FREQ_SYS == 3000000	
		CLOCK_CFG = CLOCK_CFG & ~ MASK_SYS_CK_SEL | 0x02;  // 3MHz	
#endif
#if FREQ_SYS == 750000	
		CLOCK_CFG = CLOCK_CFG & ~ MASK_SYS_CK_SEL | 0x01;  // 750KHz
#endif
#if FREQ_SYS == 187500	
		CLOCK_CFG = CLOCK_CFG & ~ MASK_SYS_CK_SEL | 0x00;  // 187.5KHz	
#endif
		SAFE_MOD = 0x00;
}

/*******************************************************************************
* Function Name  : mDelayus(UNIT16 n)
* Description    : usÑÓÊ±º¯Êý
* Input          : UNIT16 n
* Output         : None
* Return         : None
*******************************************************************************/ 
void	mDelayuS( UINT16 n )  // ÒÔuSÎªµ¥Î»ÑÓÊ±
{
#ifdef	FREQ_SYS
#if		FREQ_SYS <= 6000000
		n >>= 2;
#endif
#if		FREQ_SYS <= 3000000
		n >>= 2;
#endif
#if		FREQ_SYS <= 750000
		n >>= 4;
#endif
#endif
	while ( n ) {  // total = 12~13 Fsys cycles, 1uS @Fsys=12MHz
		++ SAFE_MOD;  // 2 Fsys cycles, for higher Fsys, add operation here
#ifdef	FREQ_SYS
#if		FREQ_SYS >= 14000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 16000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 18000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 20000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 22000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 24000000
		++ SAFE_MOD;
#endif
#endif
		-- n;
	}
}

/*******************************************************************************
* Function Name  : mDelayms(UNIT16 n)
* Description    : msÑÓÊ±º¯Êý
* Input          : UNIT16 n
* Output         : None
* Return         : None
*******************************************************************************/
void	mDelaymS( UINT16 n )                                                  // ÒÔmSÎªµ¥Î»ÑÓÊ±
{
	while ( n ) {
#ifdef	DELAY_MS_HW
		while ( ( TKEY_CTRL & bTKC_IF ) == 0 );
		while ( TKEY_CTRL & bTKC_IF );
#else
		mDelayuS( 1000 );
#endif
		-- n;
	}
}                                         

/*******************************************************************************
* Function Name  : CH554UART0Alter()
* Description    : CH554´®¿Ú0Òý½ÅÓ³Éä,´®¿ÚÓ³Éäµ½P1.2ºÍP1.3
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH554UART0Alter()
{
    PIN_FUNC |= bUART0_PIN_X;                                                  //´®¿ÚÓ³Éäµ½P1.2ºÍP1.3
}

/*******************************************************************************
* Function Name  : mInitSTDIO()
* Description    : CH554´®¿Ú0³õÊ¼»¯,Ä¬ÈÏÊ¹ÓÃT1×÷UART0µÄ²¨ÌØÂÊ·¢ÉúÆ÷,Ò²¿ÉÒÔÊ¹ÓÃT2
                   ×÷Îª²¨ÌØÂÊ·¢ÉúÆ÷
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void	mInitSTDIO( )
{
    UINT32 x;
    UINT8 x2; 

    SM0 = 0;
    SM1 = 1;
    SM2 = 0;                                                                   //´®¿Ú0Ê¹ÓÃÄ£Ê½1
                                                                               //Ê¹ÓÃTimer1×÷Îª²¨ÌØÂÊ·¢ÉúÆ÷
    RCLK = 0;                                                                  //UART0½ÓÊÕÊ±ÖÓ
    TCLK = 0;                                                                  //UART0·¢ËÍÊ±ÖÓ
    PCON |= SMOD;
    x = 10 * FREQ_SYS / UART0_BUAD / 16;                                       //Èç¹û¸ü¸ÄÖ÷Æµ£¬×¢ÒâxµÄÖµ²»ÒªÒç³ö                            
    x2 = x % 10;
    x /= 10;
    if ( x2 >= 5 ) x ++;                                                       //ËÄÉáÎåÈë

    TMOD = TMOD & ~ bT1_GATE & ~ bT1_CT & ~ MASK_T1_MOD | bT1_M1;              //0X20£¬Timer1×÷Îª8Î»×Ô¶¯ÖØÔØ¶¨Ê±Æ÷
    T2MOD = T2MOD | bTMR_CLK | bT1_CLK;                                        //Timer1Ê±ÖÓÑ¡Ôñ
    TH1 = 0-x;                                                                 //12MHz¾§Õñ,buad/12ÎªÊµ¼ÊÐèÉèÖÃ²¨ÌØÂÊ
    TR1 = 1;                                                                   //Æô¶¯¶¨Ê±Æ÷1
    TI = 1;
    REN = 1;                                                                   //´®¿Ú0½ÓÊÕÊ¹ÄÜ
}

/*******************************************************************************
* Function Name  : CH554UART0RcvByte()
* Description    : CH554UART0½ÓÊÕÒ»¸ö×Ö½Ú
* Input          : None
* Output         : None
* Return         : SBUF
*******************************************************************************/
UINT8  CH554UART0RcvByte( )
{
    while(RI == 0);                                                            //²éÑ¯½ÓÊÕ£¬ÖÐ¶Ï·½Ê½¿É²»ÓÃ
    RI = 0;
    return SBUF;
}

/*******************************************************************************
* Function Name  : CH554UART0SendByte(UINT8 SendDat)
* Description    : CH554UART0·¢ËÍÒ»¸ö×Ö½Ú
* Input          : UINT8 SendDat£»Òª·¢ËÍµÄÊý¾Ý
* Output         : None
* Return         : None
*******************************************************************************/
void CH554UART0SendByte(UINT8 SendDat)
{
	SBUF = SendDat;                                                              //²éÑ¯·¢ËÍ£¬ÖÐ¶Ï·½Ê½¿É²»ÓÃÏÂÃæ2ÌõÓï¾ä,µ«·¢ËÍÇ°ÐèTI=0
	while(TI ==0);
	TI = 0;
}

/*******************************************************************************
* Function Name  : UART1Setup()
* Description    : CH554´®¿Ú1³õÊ¼»¯
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void	UART1Setup( )
{
   U1SM0 = 0;                                                                   //UART1Ñ¡Ôñ8Î»Êý¾ÝÎ»
   U1SMOD = 1;                                                                  //¿ìËÙÄ£Ê½
   U1REN = 1;                                                                   //Ê¹ÄÜ½ÓÊÕ
   SBAUD1 = 0 - FREQ_SYS/16/UART1_BUAD;
}

/*******************************************************************************
* Function Name  : CH554UART1RcvByte()
* Description    : CH554UART1½ÓÊÕÒ»¸ö×Ö½Ú
* Input          : None
* Output         : None
* Return         : SBUF
*******************************************************************************/
UINT8  CH554UART1RcvByte( )
{
    while(U1RI == 0);                                                           //²éÑ¯½ÓÊÕ£¬ÖÐ¶Ï·½Ê½¿É²»ÓÃ
    U1RI = 0;
    return SBUF1;
}

/*******************************************************************************
* Function Name  : CH554UART1SendByte(UINT8 SendDat)
* Description    : CH554UART1·¢ËÍÒ»¸ö×Ö½Ú
* Input          : UINT8 SendDat£»Òª·¢ËÍµÄÊý¾Ý
* Output         : None
* Return         : None
*******************************************************************************/
void CH554UART1SendByte(UINT8 SendDat)
{
	SBUF1 = SendDat;                                                             //²éÑ¯·¢ËÍ£¬ÖÐ¶Ï·½Ê½¿É²»ÓÃÏÂÃæ2ÌõÓï¾ä,µ«·¢ËÍÇ°ÐèTI=0
	while(U1TI ==0);
	U1TI = 0;
}

/*******************************************************************************
* Function Name  : CH554WDTModeSelect(UINT8 mode)
* Description    : CH554¿´ÃÅ¹·Ä£Ê½Ñ¡Ôñ
* Input          : UINT8 mode 
                   0  timer
                   1  watchDog
* Output         : None
* Return         : None
*******************************************************************************/
void CH554WDTModeSelect(UINT8 mode)
{
   SAFE_MOD = 0x55;
   SAFE_MOD = 0xaa;                                                             //½øÈë°²È«Ä£Ê½
   if(mode){
     GLOBAL_CFG |= bWDOG_EN;                                                    //Æô¶¯¿´ÃÅ¹·¸´Î»
   }
   else GLOBAL_CFG &= ~bWDOG_EN;	                                            //Æô¶¯¿´ÃÅ¹·½ö½ö×÷Îª¶¨Ê±Æ÷
   SAFE_MOD = 0x00;                                                             //ÍË³ö°²È«Ä£Ê½
   WDOG_COUNT = 0;                                                              //¿´ÃÅ¹·¸³³õÖµ
}

/*******************************************************************************
* Function Name  : CH554WDTFeed(UINT8 tim)
* Description    : CH554¿´ÃÅ¹·¶¨Ê±Ê±¼äÉèÖÃ
* Input          : UINT8 tim ¿´ÃÅ¹·¸´Î»Ê±¼äÉèÖÃ
                   00H(6MHz)=2.8s
                   80H(6MHz)=1.4s
* Output         : None
* Return         : None
*******************************************************************************/
void CH554WDTFeed(UINT8 tim)
{
   WDOG_COUNT = tim;                                                             //¿´ÃÅ¹·¼ÆÊýÆ÷¸³Öµ	
}

// /*******************************************************************************
// * Function Name  : CH554SoftReset()
// * Description    : CH554Èí¸´Î»
// * Input          : None
// * Output         : None
// * Return         : None
// *******************************************************************************/
// void CH554SoftReset( )
// {
//     SAFE_MOD = 0x55;
//     SAFE_MOD = 0xAA;
//     GLOBAL_CFG	|=bSW_RESET;
// }

// /*******************************************************************************
// * Function Name  : CH554USBDevWakeup()
// * Description    : CH554Éè±¸Ä£Ê½»½ÐÑÖ÷»ú£¬·¢ËÍKÐÅºÅ
// * Input          : None
// * Output         : None
// * Return         : None
// *******************************************************************************/
// void CH554USBDevWakeup( )
// {
//   UDEV_CTRL |= bUD_LOW_SPEED;
//   mDelaymS(2);
//   UDEV_CTRL &= ~bUD_LOW_SPEED;	
// }
