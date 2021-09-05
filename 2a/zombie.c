#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
void forkEx()
{
    int cpid = fork();
    if (cpid < 0)
        printf("Fork unsuccessful.\n");
    else if(cpid == 0)
    {
    
        //Sorting Algo 1
        printf("In child process.\n");
        printf("1.child process iD is %d\n",getpid());    //x
        printf("1.Parent process iD is %d\n",getppid());    //x-1
        sleep(5);
        printf("3.child process iD is %d\n",getpid());    //x
        printf("3.Parent process iD is %d\n",getppid());    //y    
        
        
    }
    else
    {
        printf("In parent process.\n");
        printf("2.parent process iD is %d\n",getpid());
        printf("2.parent of Parent process iD is %d\n",getppid());
     
        //Sorting Algo 2       
    }
       
}   
int main()
{
//    Accept 5 Nos

 

    forkEx();
    return 0;
}
