#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
 #include <string.h>
//-------------------------------------------------------
 /* reverse:  reverse string s in place */
 void reverse(char s[])
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
}  

 char* itoa(int n, char s[])
 {
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
     return s;
     
}  


//---------------------------------------------------------------

char snum[10];   //to use while converting from int to char

typedef struct msgbuff  // buffer to store process in
{
    int ID;
    int ArrTime;
    int RunTime;
    int Priority;
    int PID;
    int RemaingTime;
    int WatingTime;
    int resumed;
    int Stoped;
    int Running;
    int memsize;
    int memindx;
}msgbuff;


// void report_file (process prcs){
//     FILE* file = fopen ("output1.txt", "w");

//     if (prcs.RemaingTime == 0){
//         //finished process
//         // add the calculations at the end of the line 
//         fprintf(file,"At time %d process %d finished arr %d total %d remain %d wait %d \td",getClk(), prcs.ID ,  prcs.ArrTime , prcs.RunTime , prcs.RemaingTime, prcs.WatingTime); 
//     }
//     else if (prcs.RemaingTime == prcs.Running){
//         //started proces
//         fprintf(file,"At time %d process %d started arr %d total %d remain %d wait %d \t ",getClk(), prcs.ID ,  prcs.ArrTime , prcs.RunTime , prcs.RemaingTime, prcs.WatingTime); 
//     }
//     else if(prcs.resumed == 1){
//         fprintf(file,"At time %d process %d resumed arr %d total %d remain %d wait %d \t ",getClk(), prcs.ID ,  prcs.ArrTime , prcs.RunTime , prcs.RemaingTime, prcs.WatingTime); 
//     }
//     else {
//         fprintf(file,"At time %d process %d stopped arr %d total %d remain %d wait %d \t ",getClk(), prcs.ID ,  prcs.ArrTime , prcs.RunTime , prcs.RemaingTime, prcs.WatingTime); 
//     }
    
//     fclose(file);
// }

/// @brief function to equate two the pcb to message recieved
/// @param p process
/// @param message message
process eq_st(process p,msgbuff message){
    p.ArrTime=message.ArrTime;
    p.ID=message.ID;
    p.Priority=message.Priority;
    p.RunTime=message.RunTime;
    return p;
}


int main(int argc, char * argv[])
{

    //----------------  some inititalizations  --------------------
    initClk();
    printf("%d\n",getClk());
    printf("im a scheduler\n");
    printf("the algotihm type is %s\n",argv[1]);
    //-----------------------------
    int downQ;
    key_t key_down =123;
    downQ=msgget(key_down, IPC_CREAT | 0644);
    msgbuff message; 
    process p;
//---------------------------------
    heap_t *readyq_sjf = (heap_t *)calloc(1, sizeof(heap_t));
//----------------------------------
void fork_process(char* rem_time){

    int pid;
    pid= fork();
    if (pid ==0)
    {
        printf("process has been forked \n");
        char *args[]= {"./process.out",rem_time,NULL};
        execv(args[0],args);
        printf("didn'twork");
    }
    // else{
    //     wait()
    // }
}

    while (1)
    {
    int rec_val = msgrcv(downQ, &message, sizeof(message),0, !IPC_NOWAIT);

        if(rec_val==-1){
            perror("msg not recieved");
        }
        else{
        //push(readyq_sjf,p.ArrTime,&p[i]);
            printf("message recieved\n");
            printf("clk is %d\n ",getClk());
            process p=eq_st(p,message);
            printf("arr_time of p %d\n",p.ArrTime);
            printf("message id : %d\n", message.RunTime);
            push(readyq_sjf,p.RunTime,&p);
            while(readyq_sjf->len){
                process pf =*pop(readyq_sjf);
                fork_process(itoa(pf.RunTime,snum));
            }

    
            //process P_to_fork =*pop(readyq_sjf);

            //printf("run time of p1 %d\n",P_to_fork.RunTime);
        }
            printf("run time of p %d\n",top(readyq_sjf)->RunTime);

    
 




    }



}
