#include<stdio.h>
#include<stdlib.h>

void tohUtil(int num, char from, char to, char temp) {
	if (num < 1)
		return;

	tohUtil(num - 1, from, temp, to);
	printf("Move disk %d from peg %c to peg %c.\n", num, from, to );
	tohUtil(num - 1, temp, to, from);
}

void toh(int num) {
	printf("The sequence of moves involved in the Tower of Hanoi are :\n" );
	tohUtil(num, 'A', 'C', 'B');
}

int main() {
	toh(3);
	return 0;
}

/*
The sequence of moves involved in the Tower of Hanoi are :
Move disk 1 from peg A to peg C
Move disk 2 from peg A to peg B
Move disk 1 from peg C to peg B
Move disk 3 from peg A to peg C
Move disk 1 from peg B to peg A
Move disk 2 from peg B to peg C
Move disk 1 from peg A to peg C
*/