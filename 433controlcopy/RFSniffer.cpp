/*
  RF_Sniffer
  
  Hacked from http://code.google.com/p/rc-switch/
  
  by @justy to provide a handy RF code sniffer
*/

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
     
     
RCSwitch mySwitch;
 


int main(int argc, char *argv[]) {
  
     // This pin is not the first pin on the RPi GPIO header!
     // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     // for more information.
    int receiverPIN = 1;
	int LEDredPIN 	= 1;
	int LEDgreenPIN = 2;
	int LEDbluePIN 	= 3;
	 
     
     if(wiringPiSetup() == -1)
       return 0;

     mySwitch = RCSwitch();
     mySwitch.enableReceive(receiverPIN); 
     
	 pinMode(LEDredPIN,   OUTPUT);
	 pinMode(LEDgreenPIN, OUTPUT);
	 pinMode(LEDbluePIN,  OUTPUT);
    
     while(1) {
  
      if (mySwitch.available()) {
    
        int value = mySwitch.getReceivedValue();
		
		switch(value) {
		case 11734380:						//code entsprechend ändern
			digitalWrite(LEDbluePIN, 1);
			break;
		case 12269868:						//code entsprechend ändern
			digitalWrite(LEDbluePIN, 0);
			break;
		case 12365029:						//code entsprechend ändern
			digitalWrite(LEDredPIN, 1);
			break;
		case 11854229:						//code entsprechend ändern
			digitalWrite(LEDgreenPIN, 0);
			break;
		case 0:
		default:
			printf("Unknown encoding");
		}
    
        mySwitch.resetAvailable();
    
      } else {
	  
		digitalWrite(LEDredPIN, 0);
		digitalWrite(LEDgreenPIN, 0);
	  }
      
  
  }

  exit(0);


}

