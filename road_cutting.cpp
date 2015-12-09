#include <iostream>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#define STICK_SIZE (10)
#define MAXVALUE(a, b) (a)>(b)?(a):(b)

int max_price[STICK_SIZE+1];

void init_max_price()
{
	for(int i = 0; i < STICK_SIZE +1; ++i)
	{
		max_price[i] = -1;
	}
}

int dynamic_solve_top_down(int data[], int stick_size)
{
	if (max_price[stick_size] > 0)
	{
		return max_price[stick_size];
	}

	int q = -1;

	if (stick_size == 0)
	{
		return 0;
	}
	else
	{
		for(int i = 1; i<= stick_size; ++i)
		{
			q = MAXVALUE(q, data[i] + dynamic_solve_top_down(data, stick_size -i));
		}
	}
	max_price[stick_size] = q;
	return q;
}

int dynamic_solve_bottom_up(int data[], int stick_size)
{
	max_price[0] = 0;
	for (int i = 1; i <= stick_size ; ++i)
	{
		int q = -1;
		for (int j = 1; j <= i; ++j)
		{
			q = MAXVALUE(q, data[j] + max_price[i-j]);
		}
		max_price[i] = q;
	}
	return max_price[stick_size];
}

int naive_dynamic_solve(int data[], int stick_size)
{
	if (stick_size == 0)
	{
		return 0;
	}

	int q = -1;

	for (int i = 1; i<= stick_size; ++i)
	{
		q = MAXVALUE(q, data[i] + naive_dynamic_solve(data, stick_size - i));
	}
	return q;
}

int main() {

	time_t start_time;
	time_t end_time;

	int data[STICK_SIZE+1] = {0,1,5,8,9,10,17,17,20,24,30};
	int result;

	cout << "[dynamic_solve_bottom_up]" << endl;
	start_time = clock();
	for (int i = 1; i<= STICK_SIZE; ++i)
	{
		result = dynamic_solve_bottom_up(data, i);
		cout << "[" << i << "]" << result <<endl;
	}
	end_time = clock();
	cout << "time: " << end_time - start_time << "ms"<< endl;

	cout << "[dynamic_solve_top_down]" << endl;
	start_time = clock();
	for (int i = 1; i<= STICK_SIZE; ++i)
	{
		result = dynamic_solve_top_down(data, i);
		cout << "[" << i << "]" << result <<endl;
	}
	end_time = clock();
	cout << "time: " << end_time - start_time << "ms"<< endl;

	cout << "[naive_solve]" << endl;
	start_time = clock();
	for (int i = 1; i<= STICK_SIZE; ++i)
	{
		result = naive_dynamic_solve(data, i);
		cout << "[" << i << "]" << result <<endl;
	}
	end_time = clock();
	cout << "time: " << end_time - start_time << "ms"<< endl;

	return 0;
}
