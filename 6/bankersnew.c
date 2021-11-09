#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int n,m,i,j;
int allocation_matrix[10][10],max_matrix[10][10],need_matrix[10][10];
int available_matrix[10],work_matrix[10],request_matrix[10];
struct process
{
	int pid[10];
	int flag;
}p[10];

void input();
void safe_sequence();
void request_process();
void print();

int main()
{
	int ch;
	do{
		printf("\n\n");
		printf("+-------------------------------------+\n");
		printf("+         Banker's Algorithm          +\n");
		printf("+-------------------------------------+\n");
		printf("|               Menu                  |\n");
		printf("| 1. Input Data                       |\n");
		printf("| 2. Safe sequence                    |\n");
		printf("| 3. Request a Process                |\n");
		printf("| 4. Print Matrices                   |\n");
		printf("| 5. Exit                             |\n");
		printf("+-------------------------------------+\n");
		printf("\n Enter Choice: ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: 
				input();
				break;
			case 2:
				safe_sequence();
				break;
			case 3:
				request_process();
				break;
			case 4:
				print();
				break;
		}
		
	}while(ch!=5);
	return 0;
}


void input()
{
	printf("\n Enter Total Number of Processes: ");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("\nEnter Process Id [p%d]: ",i);
		scanf("%d",p[i].pid);
	}
	printf("\n Enter the number of Resources: \n");
	scanf("%d",&m);
	printf("\n Enter Allocation Matrix: ");
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
			scanf("%d",&allocation_matrix[i][j]);
	}
	printf("\n Enter Max Matrix: \n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
			scanf("%d",&max_matrix[i][j]);
	}
	 printf("\n Need Matrix: \n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			need_matrix[i][j]=max_matrix[i][j]-allocation_matrix[i][j];
			printf(" %d ",need_matrix[i][j]);
			printf("\n");
		}
	}
	printf("\n");
	printf("Enter Available Matrix: \n");
	for(i=0;i<m;i++)
		scanf("%d",&available_matrix[i]);
		
}

void safe_sequence()
{
	int ss=0,chk=0,check_process=0,count=0;
	int safe_seq[10];
	for(j=0;j<m;j++)
		work_matrix[j]=available_matrix[j];
	for(i=0;i<n;i++)
		p[i].flag=0;
	printf("\n\nWork Matrix:\n");
	while(count!=n)
	{
		for(i=0;i<n;i++)
		{
			chk=0;
			for(j=0;j<m;j++)
			{
				if(p[i].flag==0)
				{
					if (need_matrix[i][j] > work_matrix[j])
                        			break;
					else if(need_matrix[i][j]<=work_matrix[j]);
					chk++;
				}
				
				if(chk==m)
				{
					for(j=0;j<m;j++)
					{
						work_matrix[j]=work_matrix[j]+allocation_matrix[i][j];
						printf("[%d]->",work_matrix[j]);
						p[i].flag=1;
						safe_seq[ss]=*p[i].pid;
						
					}
					
					ss++;
					count++;
				}
			}
		}
	}
	for(i=0;i<n;i++)
	{
		if(p[i].flag==1)
			check_process++;
	}
	if(check_process>=n)
	{
		printf("\n\nSystem is in Safe State\n");
		for(i=0;i<n;i++)
			printf(" [ %d ] -> ",safe_seq[i]);
	}
	else
	printf("\n\n System is in Not State \n");	
}

void request_process()
{
	int pro;
	printf("\n Enter the Process Number Of Request:  \n");
	scanf("%d",&pro);
	printf(" Enter the Requested array:  \n");
	for(i=0;i<m;i++)
		scanf("%d",&request_matrix[i]);  
	for(j=0;j<m;j++)
	{
		if(request_matrix[j]<=need_matrix[pro][j])
		{
			if(request_matrix[j]<=available_matrix[j])
			{
				available_matrix[j]=available_matrix[j]-request_matrix[j];
				allocation_matrix[pro][j]=allocation_matrix[pro][j]+request_matrix[j];
				need_matrix[pro][j]=need_matrix[pro][j]-request_matrix[j];
				printf(" avail: %d",available_matrix[j]);
			}
			else
			{
				printf("Resource Unavailable");
			}
			printf("\t need : %d",need_matrix[pro][j]);
		}
		else
		{
			printf("process has some Error \n");
			
		}
	}
}

void print()
{
	printf("Max matrix:  \n");
	for(i=0;i<n;++i)
	{
		for(j=0;j<m;j++)
			printf(" %d ",max_matrix[i][j]);
		printf("\n");
	}
	printf("Allocation matrix : \n");
	for(i=0;i<n;++i)
	{
		for(j=0;j<m;j++)
			printf(" %d ",allocation_matrix[i][j]);
		printf("\n");
	}
	printf("Need matrix :\n");
	for(i=0;i<n;++i)
	{
		for(j=0;j<m;j++)
			printf(" %d ",need_matrix[i][j]);
		printf("\n");
	}
	printf(" \n Availiable :");
	for(i=0;i<m;i++)
		printf(" %d ",available_matrix[i]);
}




