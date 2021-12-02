
#include <stdio.h>

int andEx(int a, int b) {
	return a & b;
}

int orEx(int a, int b) {
	return a | b;
}

int xorEx(int a, int b) {
	return a ^ b;
}

int leftShiftEx(int a) // multiply by 2
{
	return a << 1;
}

int rightShiftEx(int a) // divide by 2
{
	return a >> 1;
}

int bitReversalEx(int a) {
	return ~a;
}

int twoComplementEx(int a) {
	return -a;
}

int kthBitCheck(int a, int k) {
	return (a & 1 << (k - 1)) > 0;
}

int kthBitSet(int a, int k) {
	return (a | 1 << (k - 1));
}

int kthBitReset(int a, int k) {
	return (a & ~(1 << (k - 1)));
}

int kthBitToggle(int a, int k) {
	return (a ^ (1 << (k - 1)));
}

int rightMostBit(int a) {
	return a & -a;
}

int resetRightMostBit(int a) {
	return a & (a - 1);
}

int isPowerOf2(int a) {
	if ((a & (a - 1)) == 0) {
		return 1;
	} else {
		return 0;
	}
}

int countBits(int a) {
	int count = 0;
	while (a > 0) {
		count += 1;
		a = a & (a - 1); // reset least significant bit.
	}
	return count;
}

int main() {
	int a = 4;
	int b = 8;
	printf("%d\n", andEx(a, b));
	printf("%d\n", orEx(a, b));
	printf("%d\n", xorEx(a, b));
	printf("%d\n", leftShiftEx(a)); // multiply by 2
	printf("%d\n", rightShiftEx(a)); // divide by 2
	printf("%d\n", bitReversalEx(a));
	printf("%d\n", twoComplementEx(a));
	printf("%d\n", kthBitCheck(a, 3));
	printf("%d\n", kthBitSet(a, 2));
	printf("%d\n", kthBitReset(a, 3));
	printf("%d\n", kthBitToggle(a, 3));
	printf("%d\n", rightMostBit(a));
	printf("%d\n", resetRightMostBit(a));
	printf("%d\n", isPowerOf2(a));

	for (int i = 0;i < 10;i++) {
		printf("%d bit count : %d\n", i, countBits(i));
	}
	return 0;
}

/*
0
12
12
8
2
-5
-4
1
6
0
0
4
0
1
0 bit count : 0
1 bit count : 1
2 bit count : 1
3 bit count : 2
4 bit count : 1
5 bit count : 2
6 bit count : 2
7 bit count : 3
8 bit count : 1
9 bit count : 2
*/