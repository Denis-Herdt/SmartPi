/*
  RF_Sniffer
  
  Hacked from http://code.google.com/p/rc-switch/
  
  by @justy to provide a handy RF code sniffer
*/

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
     
     
RCSwitch mySwitch;
bool ten=false;

int SetTimer(struct timeval &tv,int sec){
	gettimeofday(&tv,NULL);
	tv.tv_sec+=sec;
	ten = true;
	printf("trigtime %d\n", tv);
	return 1;
}
int CheckTimer(struct timeval &tv){
	struct timeval ctv;
	gettimeofday(&ctv,NULL);
	if(ctv.tv_sec > tv.tv_sec){
		printf("curtime %d\n", ctv);
		printf("check 1\n");
		return 1;
	}
	else{
		return 0;
	}
}

int main(int argc, char *argv[]) {
  
     // This pin is not the first pin on the RPi GPIO header!
     // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     // for more information.
     int PIN_IN = 1;
     int PIN_OUT = 0;
     
     
     if(wiringPiSetup() == -1)
       return 0;

     mySwitch = RCSwitch();
     mySwitch.enableReceive(PIN_IN);  
     struct timeval tv;
     int on = 15033511;
     int off = 15033510;
     int alloff = 15033514;    
     while(1) {
       
      if (mySwitch.available()) {
    
        int value = mySwitch.getReceivedValue();
        if (value == 0) {
          printf("Unknown encoding");
        } else {
		if (value ==  on){
			printf("start Timer\n");
			SetTimer(tv,60*60);
		}
		if (value == off){
			ten = false;
		}
//		if ((CheckTimer(tv,60)== 1)&&(ten==true)){
//			mySwitch.enableTransmit(PIN_OUT);
//			mySwitch.send(alloff , 24);
//			printf("off");
//		}
	  printf("ten: %d", ten);
          printf("Received %i\n", mySwitch.getReceivedValue() );
	  
          }
	  mySwitch.resetAvailable();
	}
    	if(ten==true){
		if(CheckTimer(tv)==1){
			ten = false;
			printf("off");
//			mySwitch.enableTransmit(PIN_OUT);
//			mySwitch.send(alloff,24);
//			ten=false;
//			mySwitch.disableTransmit();
			system("sudo ./codesend 15033514");
			printf("off2");
		}
	}
  }

  exit(0);


}

