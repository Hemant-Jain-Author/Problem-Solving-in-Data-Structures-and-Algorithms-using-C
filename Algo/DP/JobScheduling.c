#include <stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct Job {
	int start;
	int stop;
	int value;
} Job ;

Job* createJob(int s, int f, int v) {
	Job* jb = (Job*)malloc(sizeof(Job));
	jb->start = s;
	jb->stop = f;
	jb->value = v;
	return jb;
}

int max(int a, int b) {
	return (a>b)? a : b;
}

int greater(Job *j1, Job *j2) { // swap condition for sorting.
	return j1->stop > j2->stop;
}

int maxValueJobUtil(Job* arr[], int n) {
	// Base case
	if (n == 1)
		return arr[0]->value;

	// Find Value when current job is included
	int incl = arr[n - 1]->value;
	for (int j = n - 1; j >= 0; j--) {
		if (arr[j]->stop <= arr[n - 1]->start) {
			incl += maxValueJobUtil(arr, j + 1);
			break;
		}
	}

	// Find Value when current job is excluded
	int excl = maxValueJobUtil(arr, n - 1);

	return max(incl, excl);
}

void sort(Job* arr[], int size, int (*comp)(Job* p1, Job* p2)) {
    int i, j;
	Job* temp;
    for (i = 0; i < (size - 1); i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (comp(arr[j], arr[j + 1])) {
                /* Swapping */
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int maxValueJobs(int s[], int f[], int v[], int n) {
	Job* act[n];
	for (int i = 0;i < n;i++)
		act[i] = createJob(s[i], f[i], v[i]);

	sort(act, n, greater); // sort according to finish time.
	return maxValueJobUtil(act, n);
}

int maxValueJobTDUtil(int dp[], Job* arr[], int n) {
	if (dp[n - 1] != 0)
		return dp[n - 1];

	// Find Value when current job is included
	int incl = arr[n - 1]->value;
	for (int j = n - 2; j >= 0; j--) {
		if (arr[j]->stop <= arr[n - 1]->start) {
			incl += maxValueJobTDUtil(dp, arr, j + 1);
			break;
		}
	}

	// Find Value when current job is excluded
	int excl = maxValueJobTDUtil(dp, arr, n - 1);
	dp[n - 1] = max(incl, excl);
	return dp[n - 1];
}

int maxValueJobsTD(int s[], int f[], int v[], int n) {
	Job* act[n];
	for (int i = 0;i < n;i++)
		act[i] = createJob(s[i], f[i], v[i]);

	sort(act, n, greater); // sort according to finish time.
	int dp[n];
	memset(dp, 0, sizeof(dp));
	dp[0] = act[0]->value;

	return maxValueJobTDUtil(dp, act, n);
}

int maxValueJobsBU(int s[], int f[], int v[], int n) {
	Job* act[n];
	for (int i = 0;i < n;i++)
		act[i] = createJob(s[i], f[i], v[i]);

	sort(act, n, greater); // sort according to finish time.
	int dp[n];
	dp[0] = act[0]->value;

	for (int i = 1; i < n; i++) {
		int incl = act[i]->value;
		for (int j = i - 1; j >= 0; j--) {
			if (act[j]->stop <= act[i]->start) {
				incl += dp[j];
				break;
			}
		}
		dp[i] = max(incl, dp[i - 1]);
	}
	return dp[n - 1];
}

int main() {
	int start[] = {1, 5, 0, 3, 5, 6, 8};
	int finish[] = {2, 6, 5, 4, 9, 7, 9};
	int value[] = {2, 2, 4, 3, 10, 2, 8};
	int n = 7;
	printf("%d\n", maxValueJobs(start, finish, value, n));
	printf("%d\n", maxValueJobsTD(start, finish, value, n));
	printf("%d\n", maxValueJobsBU(start, finish, value, n));
}

/*
17
17
17
*/