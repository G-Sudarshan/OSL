#include<stdio.h>
#include<stdlib.h>
#define MAX 100
typedef struct{
	int pid;
	int burst_time;
	int waiting_time;
	int turnaround_time;
	int arrival_time;
	int completion_time;
	int rem_burst;
	int shortest_time;
}Process;

void fcfs(Process p[],int n);
void roundrobin(Process p[],int n, int tq);
void sjf_premptive(Process p[],int n);
void sjf_non_premptive(Process p[],int n);

int main()
{
	Process p[MAX];
	int choice;
	int i, j, n, tq;

   	printf("Enter total number of process: ");
    	scanf("%d", &n);
    	printf("Enter the Arrival time for each process:\n");
    	for(i=0;i<n;i++)
    	{
    		p[i].pid = i+1;
		printf("P[%d] : ", i+1);
		scanf("%d", &p[i].arrival_time);
    	}

   	printf("Enter burst time for each process:\n");
   	for(i=0; i<n; i++) {
		p[i].pid = i+1;
		printf("P[%d] : ", i+1);
		scanf("%d", &p[i].burst_time);
		p[i].waiting_time = p[i].turnaround_time = 0;
		p[i].completion_time = p[i].rem_burst = 0;
		p[i].shortest_time=0;

    	}

	printf("+------------------------------------------------+\n");
	printf("|             CPU Scheduling Algorithms          |\n");
	printf("+------------------------------------------------+");
	puts(" ");
	printf("|                     Menu                       |\n");
	printf("|1. FCFS Scheduling                              |\n|2. Round Robin                                  |\n|3. SJF (PREMPTIVE)                              |\n|4. SJF(NON - PREEMPTIVE)                        |\n|5.Priority (PREEMPTIVE)                         |\n|6. Priority (NON - PREEMPTIVE)                  |\n");
	printf("+------------------------------------------------+\n");
	printf("\n Enter Choice: ");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			fcfs(p,n);
			break;
		case 2:
			sortstructarray(p,n);
			printf("Enter Time Quamtum: ");
			scanf("%d",&tq);
			roundrobin(p,n,tq);
        		break;
        	case 3:
        		sjf_premptive(p,n);
        		break;
        	case 4:
        		sjf_non_premptive(p,n);
        		break;

	}
	return 0;
}

void fcfs(Process p[],int n)
{
	int i,j;
	int sum_waiting_time = 0, sum_turnaround_time=0;
	int sum=0;
	//p[0].turnaround_time=p[0].burst_time;

	//calculating Completion time
	for(i=0;i<n;i++)
	{
		sum+=p[i].burst_time;
		p[i].completion_time += sum;
	}

	//calculating turnaround time

	for(i=0;i<n;i++)
	{
		p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
		sum_turnaround_time += p[i].turnaround_time;
	}

	//calculating Waiting time
	 for(i=0; i<n; i++)
	 {
            p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
            sum_waiting_time += p[i].waiting_time;

    	}

    	puts("");

    	puts("+-----+------------+--------------+-----------------+--------------+-----------------+");
    	puts("| PID | Burst Time | Arrival Time | Completion Time | Waiting Time | Turnaround Time |");
    	puts("+-----+------------+--------------+-----------------+--------------+-----------------+");

    	for(i=0; i<n; i++)
    	{
		printf("| %2d  |     %2d     |      %2d      |        %2d       |      %2d      |        %2d       |\n"
		       , p[i].pid, p[i].burst_time,p[i].arrival_time,p[i].completion_time, p[i].waiting_time, p[i].turnaround_time );
		puts("+-----+------------+--------------+-----------------+--------------+-----------------+");
    	}

    	printf("Total Waiting Time      : %-2d\n", sum_waiting_time);
    	printf("Average Waiting Time    : %-2.2lf\n", (double)sum_waiting_time / (double) n);
    	printf("Total Turnaround Time   : %-2d\n", sum_turnaround_time);
    	printf("Average Turnaround Time : %-2.2lf\n", (double)sum_turnaround_time / (double) n);

    	puts(""); // Empty line
    	puts("|          GANTT CHART          |");
    	puts("           *****           ");
    	printf(" ");

    	// Printing Top Bar
    	for(i=0; i<n; i++)
    	{
		for(j=0; j<p[i].burst_time; j++)
			printf("--");
		printf(" ");
    	}
   	 printf("\n|");


   	// printing process id in the middle
    	for(i=0; i<n; i++) {
		for(j=0; j<p[i].burst_time - 1; j++)
			printf(" ");
		printf("P%d", p[i].pid);
		for(j=0; j<p[i].burst_time - 1; j++)
			printf(" ");
		printf("|");
    	}
    	printf("\n ");

    	// printing bottom bar
    	for(i=0; i<n; i++) {
		for(j=0; j<p[i].burst_time; j++)
			printf("--");
		printf(" ");
    	}
    	printf("\n");

    	 // printing the time line
    	printf("0");
    	for(i=0; i<n; i++) {
		for(j=0; j<p[i].burst_time; j++)
			printf("  ");
		if(p[i].completion_time > 9)
			printf("\b"); // backspace : remove 1 space
		printf("%d", p[i].completion_time);

    	}
    	printf("\n");



}

void sortstructarray(Process p[],int n)
{
       int i,j;
       Process temp;
       for(i=0;i<n;i++)
       {
              for(j=i+1;j<n;j++)
              {
                     if(p[i].arrival_time > p[j].arrival_time)
                     {
                           temp = p[i];
                           p[i] = p[j];
                           p[j] = temp;
                     }
              }
       }
       return;
}

void roundrobin(Process p[],int n, int tq)
{
	int i,j,flag=0;
	float average_waiting_time=0, average_turnaround_time=0;


	int remain=n;
	for(i=0;i<n;i++)
		p[i].rem_burst = p[i].burst_time;
	int t=0; // for Current time



	for(t=0,i=0;remain!=0;)
       {
              if(p[i].rem_burst<=tq && p[i].rem_burst>0)
              {
                     t = t+ p[i].rem_burst;
                     printf(" -> [P%d] <- %d",p[i].pid,t);
                     p[i].rem_burst=0;
                     flag=1;
              }
              else if(p[i].rem_burst > 0)
              {
                     p[i].rem_burst = p[i].rem_burst - tq;
                     t = t + tq;
                     printf(" -> [P%d] <- %d",p[i].pid,t);
              }
              if(p[i].rem_burst==0 && flag==1)
              {
                     remain--;
                     p[i].turnaround_time = t-p[i].arrival_time;
                     p[i].waiting_time = t-p[i].arrival_time - p[i].burst_time;
                     average_waiting_time = average_waiting_time + t - p[i].arrival_time - p[i].burst_time;
                     average_turnaround_time = average_turnaround_time + t - p[i].arrival_time;
                     flag=0;
              }
              if(i==n-1)
                     i=0;
              else if(p[i+1].arrival_time <= t)
                     i++;
              else
                     i=0;
       }
       printf("\n\n");
	puts("+-----+------------+--------------+-----------------+--------------+");
    	puts("| PID | Burst Time | Arrival Time | Waiting Time | Turnaround Time |");
    	puts("+-----+------------+--------------+-----------------+--------------+");
       for(i=0;i<n;i++)
       {
              printf("| P%d |      %d      |       %d       |     %d      |        %d        |\n",p[i].pid,p[i].burst_time,p[i].arrival_time,p[i].waiting_time,p[i].turnaround_time);
       }
       printf("+-----+------------+--------------+-----------------+--------------+\n");
       average_waiting_time = average_waiting_time / n;
       average_turnaround_time = average_turnaround_time / n;
       printf("Average Waiting Time : %.2f\n",average_waiting_time);
       printf("Average Turnaround Time : %.2f\n",average_turnaround_time);

}

 int get(Process p[],int t,int n)
{
       int imin,min=9999,i;
       for(i=0;i<n;i++)
       {
              if(p[i].arrival_time<=t && p[i].shortest_time==0)
                     if(min>p[i].burst_time)
                     {
                           min=p[i].burst_time;
                           imin=i;
                     }
       }
       return imin;
}


 int sjf_isComplete(Process p[],int n)
{
       int i;
       for(i=0;i<n;i++)
              if(p[i].shortest_time==0)
                     return 0;
       return 1;
}

void sjf_premptive(Process p[],int n)
{
       int in=0,t=0,a,i;
       int ps[100];
       int arr[100],s=0;
       float avgtt=0,avgwt=0;
       for(i=0;i<n;i++)
		p[i].rem_burst = p[i].burst_time;

       while(1)
       {
              if(sjf_isComplete(p,n))
                     break;
              a=get(p,t,n);
              ps[in]=a;
              p[a].burst_time-=1;
              if(p[a].burst_time==0)
                     p[a].shortest_time=1;
              t=t+1;
              in++;
       }

       printf("*************\n");
       printf("GANTT CHART\n");
       printf("0");
       for(i=0;i<in-1;i++)
       {
              while(i < in-1 && ps[i]==ps[i+1])
              {
                     s++;
                     i++;
              }

              s++;
              printf(" -> [P%d] <- %d",p[ps[i]].pid,s);
              p[ps[i]].waiting_time = s - p[ps[i]].arrival_time - p[ps[i]].turnaround_time;
       }
       for(i=0;i<n;i++)
       {
              p[i].turnaround_time += p[i].waiting_time;
              avgwt += p[i].waiting_time;
              avgtt += p[i].turnaround_time;
       }
       	puts("");
	puts("+-----+------------+--------------+-----------------+--------------+");
    	puts("| PID | Burst Time | Arrival Time | Waiting Time | Turnaround Time |");
    	puts("+-----+------------+--------------+-----------------+--------------+");
       for(i=0;i<n;i++)
       {
              printf("| P%d |      %d      |       %d       |     %d      |        %d        |\n",p[i].pid,p[i].burst_time,p[i].arrival_time,p[i].waiting_time,p[i].turnaround_time);
       }
       printf("+-----+------------+--------------+-----------------+--------------+\n");
       avgwt = avgwt/n;
       avgtt = avgtt/n;
       printf("Average Waiting Time : %.2f\n",avgwt);
       printf("Average Turnaround Time : %.2f\n",avgtt);
       return;

}


int min_nonsjfprocess(Process p[], int n,int t)
{
       int i,minpro, mintime=999;
       for(i=0;i<n;i++)
       {
              if(p[i].arrival_time <= t && p[i].shortest_time == 0)
              {
                     if(mintime > p[i].burst_time)
                     {
                           mintime = p[i].burst_time;
                           minpro = i;
                     }
              }
       }
       p[minpro].shortest_time = 1;
       return minpro;
}

void sjf_non_premptive(Process p[],int n)
{
       int i,curpro,t=0,x=0,gc[100];
       float avgwt=0,avgtt=0;
       for(i=0;i<n;i++)
       {
              curpro = min_nonsjfprocess(p,n,t);
              p[curpro].waiting_time = t - p[curpro].arrival_time;
              p[curpro].turnaround_time = p[curpro].arrival_time + p[curpro].burst_time;
              t = t + p[curpro].burst_time;
              avgwt = avgwt + p[curpro].waiting_time;
              avgtt = avgtt + p[curpro].turnaround_time;
              gc[i] = curpro;
       }
       	puts("");
       	puts("");
 	puts("+-----+------------+--------------+-----------------+--------------+");
    	puts("| PID | Burst Time | Arrival Time | Waiting Time | Turnaround Time |");
    	puts("+-----+------------+--------------+-----------------+--------------+");
       for(i=0;i<n;i++)
       {
              printf("| P%d |      %d      |       %d       |     %d      |        %d        |\n",p[i].pid,p[i].burst_time,p[i].arrival_time,p[i].waiting_time,p[i].turnaround_time);
       }
       printf("+-----+------------+--------------+-----------------+--------------+\n");
       puts("");
       printf("|    Gantt Chart   |\n");
       puts("");
       printf("0");
       for(i=0;i<n;i++)
       {
              x = x + p[gc[i]].burst_time;
              printf(" -> [P%d] <- %d",p[gc[i]].pid,x);
       }
       printf("\n");
       printf("\n");
       avgwt = avgwt/n;
       avgtt = avgtt/n;
       printf("Average Waiting Time : %.2f\n",avgwt);
       printf("Average Turnaround Time : %.2f\n",avgtt);
}
