#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_search(const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main(int argc, char *argv[],char *en[])
{
    int i,j,c,search;
    int arr[argc];

    for (j = 0; j < argc-1; j++)
    {
        int n=atoi(argv[j]);
        arr[j]=n;
    }
    // search=atoi(argv[j]);

    printf("\n\nEnter element to search: ");
    scanf("%d",&search);

    printf("Array elements are : \n");
    for(int i=0;i<argc-1;i++)
    {
	printf("%d\t",arr[i]);
    }
    //printf("Enter element to search in array : ");
    //scanf("%d",&search);

    int *item = (int*) bsearch (&search, arr, argc-1, sizeof (int), compare_search);
    if(item != NULL)
        printf("\nElement %d Found in array!\n",search);
    else
        printf("\nElement %d Not Found in array...!\n",search);
}
