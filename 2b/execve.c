#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int main(int argc, char *argv[])
{
    int integer_array[10],search;
    char* char_array[10];
    char *newenviron[] = { NULL };

    int no_of_elements;

    int id=fork();
    if(id > 0)
   {
    printf("\nEnter how many elements you want to add in array : ");
    scanf("%d",&no_of_elements);

    printf("\nEnter Array elements : \n");
    for(int i=0;i<no_of_elements;i++)
    {
	printf("Enter %d element : ",i+1);
        scanf("%d",&integer_array[i]);
    }

    printf("\nArray elements are: ");
    for(int i=0;i<no_of_elements;i++)
    {
        printf("%d\t",integer_array[i]);
    }

   qsort (integer_array, no_of_elements, sizeof(int), compare);


    int i;
    printf("\n\nAFter sorting array elements are : ");
    for(i=0;i<no_of_elements;i++)
    {
        printf("%d\t",integer_array[i]);
    }

    // printf("\n\nEnter element to search: ");
    // scanf("%d",&search);
    integer_array[i] = search;

    for (i=0; i < no_of_elements+1; i++)
    {
             char a[sizeof(int)];
             snprintf(a, sizeof(int), "%d", integer_array[i]);

            char_array[i] = malloc(sizeof(a));
            strcpy(char_array[i], a);
    }
    char_array[i]=NULL;

       execve(argv[1], char_array, newenviron);
        perror("Error in execve call...");
    }
}
