#include <stdio.h>
#include<stdlib.h>

typedef struct Job_t
{
	char id;
	int deadline;
	int profit;
}Job;

Job* createJob(char id, int deadline, int profit)
{
	Job* job = (Job*)malloc(sizeof(Job));
	job->id = id;
	job->deadline = deadline;
	job->profit = profit;
	return job;
}

int max(int a, int b){
	return (a > b)? a : b;
}

int less(Job *a, Job *b)
{
	return a->profit < b->profit;
}

void sort(Job * arr[], int size, int (*comp)(Job * p1, Job * p2))
{
    for (int i = 0; i < (size - 1); i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (comp(arr[j], arr[j + 1]))
            {
                /* Swapping */
                Job* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


int JobSequencing(char ids[], int deadlines[], int profits[], int n)
{
	Job* jobs[n];
	int maxDL = deadlines[0];
	for (int i = 1; i < n; i++)
		maxDL = max(maxDL, deadlines[i]);

	for (int i = 0;i < n;i++)
		jobs[i] = createJob(ids[i], deadlines[i], profits[i]);

	sort(jobs, n, less); // decreasing order.

	int result[maxDL];
	for (int i = 0; i < maxDL; i++)
		result[i] = 0;

	char answer[maxDL];
	for (int i = 0; i < maxDL; i++)
		answer[i] = '0';

	int profit = 0;

	// Iterate through all given jobs
	for (int i = 0; i < n; i++)
	{
		for (int j = jobs[i]->deadline - 1; j >= 0; j--)
		{
			if (result[j] == 0)
			{
				result[j] = 1;
				answer[j] = jobs[i]->id;
				profit += jobs[i]->profit;
				break;
			}
		}
	}
	printf("Profit is :: %d\n" , profit );
	printf("Jobs selected are::");
	for (int i = 0;i < maxDL;i++)
	{
		if (answer[i] != '0')
		{
			printf("%c " , answer[i]);
		}
	}
	return profit;
}

int main()
{
	char id[] = {'a', 'b', 'c', 'd', 'e'};
	int deadline[] = {3, 1, 2, 4, 4};
	int profit[] = {50, 40, 27, 31, 30};
	JobSequencing(id, deadline, profit, 5);
}

/*
Profit is :: 151
Jobs selected are::b e a d 
*/