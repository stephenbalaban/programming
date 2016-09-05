#include <stdio.h>

#define N 32

int
main (int argc, char **argv) {
	int i = N;
	int j = N;
	int n_1 = 0,
	     n_2 = 1;
	int temp;
	while (i > 0) {
		temp = n_1;
		n_1 = n_1 + n_2;
		n_2 = temp;
		i--;
	}
	printf("F(%d) = %d\n", j, n_1);
	return 0;
}
