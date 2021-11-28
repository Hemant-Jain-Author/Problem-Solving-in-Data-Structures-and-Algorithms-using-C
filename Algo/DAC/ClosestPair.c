#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Point_t
{
	int x; 
	int y;
} Point;

Point* createPoint(int a, int b)
{
	Point *pt = (Point *)malloc(sizeof(Point));
	pt->x = a;
	pt->y = b;
	return pt;
}

int xCompare(Point *p1, Point *p2)
{
	return (p1->x > p2->x);
}

int yCompare(Point *p1, Point *p2)
{
	return (p1->y > p2->y);
}

void sort(Point* arr[], int size, int (*comp)(Point* p1, Point* p2))
{
    int i, j;
	Point* temp;
    for (i = 0; i < (size - 1); i++)
    {
        for (j = 0; j < size - i - 1; j++)
        {
            if (comp(arr[j], arr[j + 1]))
            {
                /* Swapping */
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

double closestPairBF(int arr[][2], int n)
{
	double dmin = 999999;
	for (int i = 0; i < n - 1 ; i++)
	{
		for (int j = i + 1; j < n ; j++)
		{
			double val = sqrt((arr[i][0] - arr[j][0]) * (arr[i][0] - arr[j][0]) + 
								(arr[i][1] - arr[j][1]) * (arr[i][1] - arr[j][1]));
			dmin = min(dmin, val);
		}
	}
	return dmin;
}

double distance(Point *a, Point *b)
{
	return sqrt((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
}

double stripMin(Point* q[], int n, double d)
{
	double dmin = d;

	// Find the distance between all the points in the strip. 
	// Array q is sorted according to the y axis coordinate.
	// The inner loop will run at most 6 times for each point.
	for (int i = 0; i < n; ++i)
	{
		for (int j = i + 1; j < n && (q[j]->y - q[i]->y) < dmin; ++j)
		{
			dmin = min(dmin, distance(q[i],q[j]));
		}
	}
	return dmin;
}

double closestPairUtil(Point* p[], int start, int stop, Point* q[], int n)
{
	if (stop - start < 1)
	{
		return 999999;
	}

	if (stop - start == 1)
	{
		return distance(p[start], p[stop]);
	}

	// Find the middle point
	int mid = (start + stop) / 2;
	double dl = closestPairUtil(p, start, mid, q, n);
	double dr = closestPairUtil(p, mid + 1, stop, q, n);
	double d = min(dl, dr);

	// Build an array strip[] that contains points whose x axis coordinate
	// in the range p[mid]-d and p[mid]+d
	// Points are already sorted according to y axis.
	Point* strip[n];
	int j = 0;
	for (int i = 0; i < n; i++)
	{
		if (abs(q[i]->x - p[mid]->x) < d)
		{
			strip[j] = q[i];
			j++;
		}
	}
	// Find the closest points in strip and compare with d.
	return min(d, stripMin(strip, j, d));
}

double closestPairDC(int arr[][2], int n)
{
	Point* p[n];
	Point* q[n];
	for (int i = 0; i < n; i++)
	{
		p[i] = createPoint(arr[i][0], arr[i][1]);
		q[i] = createPoint(arr[i][0], arr[i][1]);
	}
	sort(p, n, &xCompare); // Sort according to x axis.
	sort(q, n, &yCompare); // Sort according to y axis.
	return closestPairUtil(p, 0, n - 1, q, n);
}

int main()
{
	int arr[][2] = {{648, 896}, {269, 879}, {250, 922}, {453, 347}, {213, 17}};
	printf("Smallest distance is: %lf\n" , closestPairBF(arr, 5) );
	printf("Smallest distance is: %lf\n" , closestPairDC(arr, 5) );
	return 0;
}

/*
Smallest distance is: 47.010637
Smallest distance is: 47.010637
*/