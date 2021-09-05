#include<stdio.h>

struct process
{
    char p_name[10]; // Name of process
    int burst_time;  // burst time is time required for a process to execute
    int c_time;      // completion time is time on which process is terminated / completed
    int a_time;      // arrival time is time at which process arrives for execution
    int tat;         // TAT turn around time is time for which process was in CPU it is burst time + waiting time
    int w_time;      // waiting time is time in which process is nor=t in CPU it may be in blocked state for I/O etc
    int start_time;   // time when process starts executing
};

int main()
{
    float awt, atat; //average waiting time and avreage tat for all processes
    int no, i, total_w_time = 0,j, total_tat=0;



    printf("Enter no. of processes to be simulated for this program : ");
    scanf("%d",&no);
    struct process p[no];

     // Take input from user for details of processes

    for(i = 0 ; i < no ; i++)
    {
        printf("Enter name of process %d : ",i+1);
        scanf("%s",&p[i].p_name);

        printf("Enter arrival time of process %d : ",i+1);
        scanf("%d",&p[i].a_time);

        printf("Enter burst time of process %d : ",i+1);
        scanf("%d",&p[i].burst_time);
    }

    // In following nested for loop we are performing bubble sort to sort processes in ascending order according to their order attribute

     for(i = 0 ; i < no ; i++)
     {
         for(j = 0 ; j < no-i-1 ; j++)
        {
            if(p[j].a_time > p[j+1].a_time )
            {
              struct process temp;

              temp=p[j];
              p[j]=p[j+1];
              p[j+1]=temp;

            }
        }
     }
     p[0].start_time = 0;
     p[0].c_time = p[0].burst_time;
     p[0].w_time = 0;

      // In following for loop we are calculating arrival time, completion time, tat and waiting for each process
     for(i = 1 ; i < no ; i++)
     {
         p[i].start_time = p[i-1].c_time;
         p[i].c_time = p[i].a_time + p[i].burst_time;
         p[i].w_time = p[i-1].w_time + p[i-1].burst_time;
         p[i].tat = p[i].c_time - p[i].a_time;

     }



     //calculating total waiting time for finding out average waiting time
     for(i = 0 ; i < no ; i++)
     {
         total_w_time = total_w_time + p[i].w_time;
         total_tat = total_tat + p[i].tat;
     }

     awt = total_w_time / no;
     atat = total_tat / no;


    // Printing values in tabular format
    printf("values are : \n\n\n\n");
    printf("\n\nprocess name   Arrival Time    start time    burst time   waiting time   tat     \n\n"); // you can also print arrival and completion time here

    for(i = 0 ; i < no ; i++ )
    {
    printf("   %s            %d         %d           %d             %d       %d     %d      \n\n",p[i].p_name,p[i].a_time,p[i].start_time,p[i].burst_time,p[i].w_time,p[i].tat);
    }

    printf("\n\n\n\n\n  Average Waiting Time is %f Time units  \n\n\n\n\n\n",awt);
    printf("\n\n\n\n\n  Average tat is %f Time units  \n\n\n\n\n\n",atat);

    return 0;
}
