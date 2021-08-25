/* execve.c */

            #include <stdio.h>
            #include <stdlib.h>
            #include <unistd.h>

            int compare (const void * a, const void * b)
            {
            return ( *(int*)a - *(int*)b );
            }

            int main(int argc, char *argv[])
            {
                //char *newargv[] = { NULL, "hello", "world", NULL };
                char *newenviron[] = { NULL };
                int *a[] = { 50, 20, 60, 40, 10, 30 };
	            int n = sizeof(a)/sizeof(a[0]);

                qsort(a, n, sizeof(int), compare);

                printf("sorted numbers are ");
                for (int i = 0; i < n; i++)
                    printf(" %d",a[i]);

                printf("\n\n");
                              

                if (argc != 2) {
                    fprintf(stderr, "Usage: %s <file-to-exec>\n", argv[0]);
                    exit(EXIT_FAILURE);
                }

                // newargv[0] = argv[1];

                 execve(argv[1], a, newenviron);
               
                perror("execve");   /* execve() returns only on error */
                exit(EXIT_FAILURE);
                return 0;
            }
