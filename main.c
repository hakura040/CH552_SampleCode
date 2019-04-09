#include "Public/CH554.H"
#include "Public/Debug.H"
#include <string.h>
#include "USB_Serial/USB_Serial.h"


char covdata[50];


void main()
{
    CfgFsys( );                                   //Clock selection configuration   
    mDelaymS(30);                                 //Power-on delay
    USBDeviceCfg();                               //Device mode configuration
    USBDeviceEndPointCfg();			  //Endpoint configuration
    USBDeviceIntCfg();
    UEP0_T_LEN = 0;
    UEP1_T_LEN = 0;	                          //Pre-use send length must be cleared	
    UEP2_T_LEN = 0;	    
    while(1)
    {  
	SendData("Hello World \n");
 	mDelaymS(100);                           //Analog microcontroller to do other things
    }
}
