#include "headers.h"

/* Modify this file as needed*/
int remainingtime;
//--------------------------
void handler(int signum)
{
  printf("\n\n TimeOut......\n");
  exit(9);
}
//---------------------------


int main(int agrc, char * argv[])
{
    signal(SIGALRM, handler);
    initClk();
    printf("clk inside process %d\n",getClk());
    //TODO it needs to get the remaining time from somewhere
    //remainingtime = ??;
    remainingtime=atoi(argv[1]);

    while (remainingtime > 0)
    {
        // remainingtime = ??;
        //sleep(1);
        alarm(remainingtime);
        for (int i=0;i<remainingtime;i++){
            sleep(1);
            printf("time in p1 is %d\n",getClk());
        }


        //remainingtime--;

    }
    
    destroyClk(false);
    
    return 0;
}


