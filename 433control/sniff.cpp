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
	return 1;
}
int CheckTimer(struct timeval &tv){
	struct timeval ctv;
	gettimeofday(&ctv,NULL);
	if(ctv.tv_sec > tv.tv_sec){
		printf("Timer triggered\n");
		return 1;
	}
	else{
		return 0;
	}
}

int main(int argc, char *argv[]) {
  
     int PIN_IN = 1;
     int PIN_OUT = 0;
     
     
     if(wiringPiSetup() == -1)
       return 0;

     mySwitch = RCSwitch();
     mySwitch.enableReceive(PIN_IN);  
     struct timeval tv;
     int on = 15033511;
     int off = 15033510;
     int alloff = 15033505;    
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
			printf("stop Timer\n");
		}
          printf("Received %i\n", mySwitch.getReceivedValue() );
	  
          }
	  mySwitch.resetAvailable();
	}
    	if(ten==true){
		if(CheckTimer(tv)==1){
			ten = false;
			printf("All Switches off");
			system("sudo ./codesend 15033514");
		}
	}
  }

  exit(0);


}

