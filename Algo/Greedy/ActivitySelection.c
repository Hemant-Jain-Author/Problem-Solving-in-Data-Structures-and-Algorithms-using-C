#include <stdio.h>
#include<stdlib.h>

typedef struct Activity_t
{
	int start;
	int stop;
}Activity;

Activity* createActivity(int s, int f) {
	Activity* act = (Activity*)malloc(sizeof(Activity));
	act->start = s;
	act->stop = f;
}

int compare(Activity *s1, Activity *s2) {
	return (s1->stop > s2->stop);
}

void sort(Activity* arr[], int size, int (*comp)(Activity* p1, Activity* p2)) {
    int i, j;
	Activity* temp;
    for (i = 0; i < (size - 1); i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (comp(arr[j], arr[j + 1])} {
                /* Swapping */
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void maxActivities(int s[], int f[], int n) {
	Activity* act[n];
	for (int i = 0; i < n; i++) {
		act[i] = createActivity(s[i], f[i]);
	}

	sort(act, n, compare); // sort according to finish time.
	int i = 0; // The first activity at index 0 is always gets selected.
	printf("Activities are : (%d, %d)", act[i]->start ,act[i]->stop);

	for (int j = 1; j < n; j++) {
		// Find next activity whose start time is greater than or equal
		// to the finish time of previous activity.
		if (act[j]->start >= act[i]->stop) {
			printf(" (%d, %d)", act[j]->start ,act[j]->stop);
			i = j;
		}
	}
}

int main() {
	int s[] = {1, 5, 0, 3, 5, 6, 8};
	int f[] = {2, 6, 5, 4, 9, 7, 9};
	maxActivities(s, f, sizeof(s)/sizeof(int));
	return 0;
}

/*
Activities are : (1, 2) (3, 4) (5, 6) (6, 7) (8, 9)
*/
