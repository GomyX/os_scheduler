#include "headers.h"



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

int main(int argc, char * argv[])
{
    //initClk();
    printf("im a scheduler\n");
    printf("the algotihm type is %s\n",argv[1]);


    int downQ;
    key_t key_down =123;
    downQ=msgget(key_down, IPC_CREAT | 0644);

    msgbuff message; 
    while (1)
    {
    int rec_val = msgrcv(downQ, &message, sizeof(message),0, !IPC_NOWAIT);
    if(rec_val==-1){
        perror("msg not recieved");
    }
        printf("message is : %d\n", message.Priority);
        // process *p;
        // p->ID=message.ID;
        // p->ArrTime=message.ArrTime;
        // p->Priority=message.Priority;
        // p->RunTime=message.RunTime;
        // report_file(*p);
    }


    //TODO implement the scheduler :)
    //upon termination release the clock resources
    // sleep(4);
    //destroyClk(true);
}
