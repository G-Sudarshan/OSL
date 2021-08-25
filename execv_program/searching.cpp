// C++ program to demonstrate sorting in parent and
// printing result in child processes using fork()
#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <stdlib.h>
using namespace std;

// Driver code

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}



int main(int argc, int *argv[])
{
		cout << "Child process" <<endl;

		int * pItem;
        int key = 40;
        pItem = (int*) bsearch (&key, argv, 6, sizeof (int), compare);
        if (pItem!=NULL)
        printf ("%d is in the array.\n",*pItem);
        else
        printf ("%d is not in the array.\n",key);

	return 0;
}
