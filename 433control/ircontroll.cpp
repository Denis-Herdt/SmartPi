#include <wiringPi.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lirc/lirc_client.h>
#include <time.h>
#include <unistd.h>

int main(){
	struct lirc_config *config;
	char *code;
	char *c;
	bool b1 =false;
	bool b2 =false;
	bool b3 =false;

	if(lirc_init("lirc",1)==-1)
		exit(1);
	if(lirc_readconfig(NULL,&config,NULL)==0){
		while(lirc_nextcode(&code)==0){
			if(code==NULL) continue;{
					if(strstr(code,"BTN_1")){
						printf("Button 1 pressed\n");
						if(b1==false){
							system("sudo ./send 15033519");
							b1 = true;
							break;
						}else{
							system("sudo ./send 15033518");
							b1 = false;
							break;
						}
					}
					if(strstr (code,"BTN_2")){
						printf("Button 2 pressed\n");
						if(b2==false){
							system("sudo ./send 15033517");
							b2=true;
						}else{
							system("sudo ./send 15033516");
							b2=false;
						}
					}
					if(strstr (code,"BTN_3")){
						printf("Button 3 pressed\n");
						if(b3==false){
							system("sudo ./send 15033515");
							b3=true;
							goto breakif;
						}else{
							system("sudo ./send 15033514");
							b3=false;
							goto breakif;
						}
					}
			}
			breakif:
			sleep(1);
			free(code);
		}
		lirc_freeconfig(config);
	}
	lirc_deinit();
	exit(EXIT_SUCCESS);
}
