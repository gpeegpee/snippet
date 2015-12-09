#include <iostream>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#define MAXVALUE(a, b) (a)>(b)?(a):(b)
#define MINVALUE(a, b) (a)>(b)?(b):(a)

#define MAX_SIZE (6)
int optimal_value1[MAX_SIZE+1];
int optimal_value2[MAX_SIZE+1];
int line1[MAX_SIZE+2];
int line2[MAX_SIZE+2];

int station_cost1[MAX_SIZE+1] = {0, 7, 9, 3, 4, 8, 4};
int station_cost2[MAX_SIZE+1] = {0, 8, 5, 6, 4, 5, 7};
int transfer_cost1[MAX_SIZE+1] = {0, 2, 2, 3, 1, 3, 4};
int transfer_cost2[MAX_SIZE+1] = {0, 4, 2, 1, 2, 2, 1};

int bottom_up_solve()
{
	optimal_value1[1] = station_cost1[1] + transfer_cost1[1];
	optimal_value2[1] = station_cost2[1] + transfer_cost2[1];

	for (int i = 2; i<= MAX_SIZE; ++i)
	{
		if (optimal_value1[i-1] + station_cost1[i] <= optimal_value2[i-1] + transfer_cost2[i] + station_cost1[i])
		{
			optimal_value1[i] = optimal_value1[i-1] + station_cost1[i];
			line1[i] = 1;
		}
		else
		{
			optimal_value1[i] = optimal_value2[i-1] + transfer_cost2[i] + station_cost1[i];
			line1[i] = 2;
		}

		if (optimal_value2[i-1] + station_cost2[i] <= optimal_value1[i-1] + transfer_cost1[i] + station_cost2[i])
		{
			optimal_value2[i] = optimal_value2[i-1] + station_cost2[i];
			line2[i] = 2;
		}
		else
		{
			optimal_value2[i] = optimal_value1[i-1] + transfer_cost1[i] + station_cost2[i];
			line2[i] = 1;
		}
	}

	if (optimal_value1[MAX_SIZE] + 3 <= optimal_value2[MAX_SIZE] + 2)
	{
		line1[MAX_SIZE+1] = 1;
		line2[MAX_SIZE+1] = 1;
		return optimal_value1[MAX_SIZE] + 3;
	}
	else
	{
		line1[MAX_SIZE+1] = 2;
		line2[MAX_SIZE+1] = 2;
		return optimal_value2[MAX_SIZE] + 2;
	}
}

int get_optimal_value(int station, int n)
{
	if (n == 1)
	{
		if (station == 1)
		{
			optimal_value1[1] = station_cost1[1] + transfer_cost1[1];
			return optimal_value1[1];
		}
		else
		{
			optimal_value2[1] = station_cost2[1] + transfer_cost2[1];
			return optimal_value2[1];
		}
	}

	if (station == 1)
	{
		if (optimal_value1[n] != -1)
		{
			return optimal_value1[n];
		}

		int o1 = get_optimal_value(1, n-1) + station_cost1[n];
		int o2 = get_optimal_value(2, n-1) + transfer_cost2[n] + station_cost1[n];
		if (o1 <= o2)
		{
			line1[n] = 1;
			optimal_value1[n] = o1;
			return o1;
		}
		else
		{
			line1[n] = 2;
			optimal_value1[n] = o2;
			return o2;
		}
	}
	else
	{
		if (optimal_value2[n] != -1)
		{
			return optimal_value2[n];
		}

		int o1 = get_optimal_value(2, n-1) + station_cost2[n];
		int o2 = get_optimal_value(1, n-1) + transfer_cost1[n] + station_cost2[n];

		if (o1 <= o2)
		{
			line2[n] = 2;
			optimal_value2[n] = o1;
			return o1;
		}
		else
		{
			line2[n] = 1;
			optimal_value2[n] = o2;
			return o2;
		}
	}
}

int top_down_solve(int n)
{
	for (int i = 1; i<= MAX_SIZE; ++i)
	{
		optimal_value1[i] = -1;
		optimal_value2[i] = -1;
	}
	int result1 = get_optimal_value(1, n);
	int result2 = get_optimal_value(2, n);

	if (result1 + 3 <= result2 + 2)
	{
		return result1 + 3;
	}
	else
	{
		return result2 + 2;
	}
}

int main() {

	time_t start_time;
	time_t end_time;

	int result;
	start_time = clock();
	result = top_down_solve(MAX_SIZE);
	end_time = clock();
	cout << "time: " << end_time - start_time << "ms"<< " result: " << result << endl;

	for (int i = 2; i<= MAX_SIZE; ++i)
	{
		printf("%d ", line1[i]);
	}
	printf("\n");
	for (int i = 2; i<= MAX_SIZE; ++i)
	{
		printf("%d ", line2[i]);
	}
	printf("\n");
	for (int i = 1; i<= MAX_SIZE; ++i)
	{
		printf("%d ", optimal_value1[i]);
	}
	printf("\n");
	for (int i = 1; i<= MAX_SIZE; ++i)
	{
		printf("%d ", optimal_value2[i]);
	}
	printf("\n");

	return 0;
}
