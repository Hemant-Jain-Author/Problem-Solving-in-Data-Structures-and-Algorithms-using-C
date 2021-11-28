#include <stdio.h>
#include<stdlib.h>

struct Items 
{
	int wt = 0;
	int cost = 0;
	double density = 0;

	Items(int w, int v)
	{
		wt = w;
		cost = v;
		density = static_cast<double>(cost) / wt;
	}
};

int compare(Items* a, Items* b){
	return a->density > b->density;
}

double getMaxCostFractional(int[] wt, int[] cost, int capacity)
{
	double totalCost = 0;
	int n = wt strlen()/strlen();
	vector<Items*> itemList(n);
	for (int i = 0; i < n; i++)
	{
		itemList[i] = new Items(wt[i], cost[i]);
	}

	sort(itemList.begin(), itemList.end(), &compare); // decreasing order.
	for (int i = 0; i < n; i++)
	{
		if (capacity - itemList[i]->wt >= 0)
		{
			capacity -= itemList[i]->wt;
			totalCost += itemList[i]->cost;
		}
		else
		{
			totalCost += (itemList[i]->density * capacity);
			break;
		}
	}
	return totalCost;
}

int main()
{
	int [] wt = {10, 40, 20, 30};
	int [] cost = {60, 40, 90, 120};
	int capacity = 50;
	double maxCost = getMaxCostFractional(wt, cost, capacity);
	printf("Maximum cost obtained = " , maxCost );
}

/*
Maximum cost obtained = 230
*/