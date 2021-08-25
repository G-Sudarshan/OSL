// C++ program to demonstrate sorting in parent and
// printing result in child processes using fork()
#include <iostream>
#include <unistd.h>
#include <algorithm>
using namespace std;

// Driver code
int main()
{
	int a[] = { 1, 6, 3, 4, 9, 2, 7, 5, 8, 10 };
	int n = sizeof(a)/sizeof(a[0]);
	int id = fork();

	// Checking value of process id returned by fork
	if (id > 0) {
		cout << "Parent process \n";

		sort(a, a+n);

		// Displaying Array
		cout << " sorted numbers are ";
		for (int i = 0; i < n; i++)
			cout << "\t" << a[i];

		cout << "\n";

	}

	// If n is 0 i.e. we are in child process
	else {
		cout << "Child process \n";
		cout << "\n numbers to be sorted are ";
		for (int i = 0; i < n; i++)
			cout << "\t" << a[i];
	}

	return 0;
}
