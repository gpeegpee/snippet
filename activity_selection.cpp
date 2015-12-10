#include <iostream>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#define MAXVALUE(a, b) (a)>(b)?(a):(b)
#define MINVALUE(a, b) (a)>(b)?(b):(a)
#define MAX_SIZE (1000)
#define MAX_TIME (1000)

int start[MAX_SIZE];
int finish[MAX_SIZE];
int select[MAX_SIZE];

inline void exchange(int data[], int i, int j)
{
	if (i != j){
		int temp;
		temp = data[i];
		data[i] = data[j];
		data[j] = temp;

		temp = start[i];
		start[i] = start[j];
		start[j] = temp;
	}
}

int partition(int data[], int front, int rear)
{
	// 1. front == rear (OK)
	// 2. front + 1 == rear ( 2 item) (OK)
	// 3. smaller_index < rear (seek_index > smaller_index)

	int pivot_position = rear;
	int pivot_value = data[rear];

	int smaller_index = front -1;

	for (int seek_index = front; seek_index < rear; ++seek_index)
	{
		if (data[seek_index] <= pivot_value)
		{
			++smaller_index;
			exchange(data, smaller_index, seek_index);
		}
	}
	++smaller_index;
	exchange(data, smaller_index, pivot_position);
	return smaller_index;
}

void quick_sort(int data[], int front, int rear)
{
	if (front < rear)
	{
		int pivot_position = partition(data, front, rear);
		quick_sort(data, front, pivot_position -1);
		quick_sort(data, pivot_position +1, rear);
	}
}

void quick_sort_iter(int data[], int front, int rear)
{
	if (front < rear)
	{
		int pivot_position = partition(data, front, rear);
		quick_sort(data, front, pivot_position -1);
		quick_sort(data, pivot_position +1, rear);
	}
}

int activity_selection_verify(int n)
{
	for(int i = 0; i < n; ++i)
	{
		if (select[i] == 0)
		{
			continue;
		}

		for(int j = i; j < n; ++j)
		{
			if (select[j] == 0)
			{
				continue;
			}
			else
			{
				if (start[j] < finish[i] && finish[j] > finish[i])
				{
					return -1;
				}
				else if (finish[j] > start[i] && start[j] < start[i])
				{
					return -1;
				}
			}
		}
	}
	return 0;
}

int activity_selection_greedy(int n)
{
	if (n <= 0)
	{
		return 0;
	}

	int i = 0;
	for (i = 1; i< n; ++i)
	{
		select[i] = 0;
	}

	select[0] = 1;
	i = 0;
	int count = 1;
	for(int j = 1; j < n; ++j)
	{
		if (start[j] >= finish[i])
		{
			select[j] = 1;
			i = j;
			count++;
		}
	}

	return count;
}

int max_num[MAX_TIME][MAX_TIME+1];
int activity_selection_dynamic_top_solve(int front, int rear, int num)
{
	if (front == rear)
	{
		return 0;
	}

	if (max_num[front][rear] != -1)
	{
		return max_num[front][rear];
	}

	int q = 0;
	for(int i = 0; i< num; ++i)
	{
		if (start[i] < front || finish[i] > rear)
		{
			continue;
		}
		q = MAXVALUE(activity_selection_dynamic_top_solve(front, start[i], num) + activity_selection_dynamic_top_solve(finish[i], rear, num) + 1, q);
	}

	max_num[front][rear] = q;
	//printf("max_num[%d][%d] %d\n", front, rear, q);
	return q;
}

int activiey_selection_dynamic_top_down(int num)
{
	for(int i = 0; i< MAX_TIME; ++i)
	{
		for(int j = i; j<= MAX_TIME; ++j)
		{
			max_num[i][j] = -1;
		}
	}
	return activity_selection_dynamic_top_solve(0, MAX_TIME, num);
}


int activity_selection_dynamic_bottom_solve(int front, int rear, int num)
{
	for(int i = 0; i< MAX_TIME; ++i)
	{
		for(int j = i; j<= MAX_TIME; ++j)
		{
			max_num[i][j] = -1;
		}
	}

	return 0;
}

int activiey_selection_dynamic_bottom_up(int num)
{
	for(int i = 0; i< MAX_TIME; ++i)
	{
		for(int j = i; j<= MAX_TIME; ++j)
		{
			max_num[i][j] = -1;
		}
	}
	return activity_selection_dynamic_bottom_solve(0, MAX_TIME, num);
}

int main() {

	time_t start_time;
	time_t end_time;

	for(int i = 0; i< MAX_SIZE; ++i)
	{
		do {
			finish[i] = rand() % MAX_TIME;
		} while (finish[i] == 0);
	}

	for(int i = 0; i< MAX_SIZE; ++i)
	{
		do {
			start[i] = rand() % MAX_TIME;
		} while(start[i] >= finish[i]);
	}

	int result;
	quick_sort(finish, 0, MAX_SIZE -1);

	for(int i = 0; i< MAX_SIZE -1; ++i)
	{
		assert(finish[i] <= finish[i+1]);
	}

	/*
	printf("[S] ");
	for(int i = 0; i< MAX_SIZE; ++i)
	{
		printf("%2d ", start[i]);
	}
	printf("\n");
	printf("[F] ");
	for(int i = 0; i< MAX_SIZE; ++i)
	{
		printf("%2d ", finish[i]);
	}
	printf("\n");
	*/
	start_time = clock();
	result = activity_selection_greedy(MAX_SIZE);
	end_time = clock();
	cout << "time: " << end_time - start_time << "ms"<< " result: " << result << endl;

	start_time = clock();
	result = activiey_selection_dynamic_top_down(MAX_SIZE);
	end_time = clock();
	cout << "time: " << end_time - start_time << "ms"<< " result: " << result << endl;

	assert(activity_selection_verify(MAX_SIZE) == 0);

	return 0;
}
