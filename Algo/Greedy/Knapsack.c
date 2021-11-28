
#include <stdio.h>
#include<stdlib.h>

typedef struct Item_t
{
	int wt;
	int cost;
	double density;
}Item;

Item* createItem(int w, int v)
{
	Item* item = (Item*)malloc(sizeof(Item));
	item->wt = w;
	item->cost = v;
	item->density = (double)v / w;
	return item;
}

int less(Item *a, Item *b)
{
	return a->density < b->density;
}

void sort(Item * arr[], int size, int (*comp)(Item * p1, Item * p2))
{
    int i, j;
    for (i = 0; i < (size - 1); i++)
    {
        for (j = 0; j < size - i - 1; j++)
        {
            if (comp(arr[j], arr[j + 1]))
            {
                /* Swapping */
                Item* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int getMaxCostGreedy(int wt[], int cost[], int n, int capacity)
{
	int totalCost = 0;
	Item* itemList[n];
	for (int i = 0; i < n; i++)
		itemList[i] = createItem(wt[i], cost[i]);

	sort(itemList, n, less);

	for (int i = 0; i < n && capacity > 0; i++)
	{
		if (capacity - itemList[i]->wt >= 0)
		{
			capacity -= itemList[i]->wt;
			totalCost += itemList[i]->cost;
		}
	}
	return totalCost;
}

int main()
{
	int wt[] = {10, 40, 20, 30};
	int cost[] = {60, 40, 90, 120};
	int n = 4;
	int capacity = 50;
	int maxCost = getMaxCostGreedy(wt, cost, n, capacity);
	printf("Maximum cost obtained = %d\n", maxCost );
}

/*
Maximum cost obtained = 150
*/