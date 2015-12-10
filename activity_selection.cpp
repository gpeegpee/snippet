#include <iostream>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#define MAXVALUE(a, b) (a)>(b)?(a):(b)
#define MINVALUE(a, b) (a)>(b)?(b):(a)
#define MAX_SIZE (11)

int start[MAX_SIZE] = {1,3,0,5,3,5,6,8,8,2,12};
int finish[MAX_SIZE] = {4,5,6,7,8,9,10,11,12,13,14};
int select[MAX_SIZE] = {0,};

int activity_selection(int n)
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

int main() {

	time_t start_time;
	time_t end_time;

	int result;
	start_time = clock();
	result = activity_selection(14);
	end_time = clock();
	cout << "time: " << end_time - start_time << "ms"<< " result: " << result << endl;

	return 0;
}
