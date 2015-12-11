#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>
#include <assert.h>
#include <time.h>

using namespace std;

#define MAX (1024*8*32)
static int pagesize = 100;
static int memsize = 2;

inline void exchange(int data[], int i, int j)
{
	if (i != j){
		int temp;
		temp = data[i];
		data[i] = data[j];
		data[j] = temp;
	}
}

int partition(int data[], int front, int rear)
{
	int pivot_position = rear;
	int pivot_value = data[rear];

	int smaller_index = front - 1;
	for (int seek_index = front ; seek_index < rear; ++seek_index)
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

// stack overflow can be occurred
void quick_sort(int data[], int front, int rear)
{
	if (front < rear)
	{
		int pivot_position = partition(data, front, rear);
		quick_sort(data, front, pivot_position - 1);
		quick_sort(data, pivot_position+1, rear);
	}
}

void merge(int data[], int start, int end)
{
	int* tmp = (int*)calloc(MAX, sizeof(int));
	int mid = (start + end) / 2;
    int i = start;
    int j = mid + 1;
    int k = start;

    while (i <= mid && j <= end)
    {
        if (data[i] <= data[j])
        {
            tmp[k] = data[i];
            ++i;
        }
        else
        {
        	tmp[k] = data[j];
        	++j;
        }
        ++k;
    }

    int t = i > mid ? j:i;
    for (;k <= end;k++, t++)
    {
    	tmp[k] = data[t];
    }

    for (k = start;k <= end;k++)
    {
    	data[k] = tmp[k];
    }
    free(tmp);
}

void merge_sort(int data[], int length, int front, int rear)
{
	if (front < rear)
	{
		int mid = (front + rear) /2;
		merge_sort(data, length, front, mid);
		merge_sort(data, length, mid+1, rear);
		merge(data, front, rear);
	}
}

void maxheapify(int data[], int length, int root_index)
{
	int left_child = 2 * root_index;
	int right_child = 2* root_index + 1;
	int largest = 0;

	if (left_child <= length && data[left_child] > data[root_index])
	{
		largest = left_child;
	}
	else
	{
		largest = root_index;
	}

	if (right_child <= length && data[right_child] > data[largest])
	{
		largest = right_child;
	}

	if (largest != root_index)
	{
		exchange(data, root_index, largest);
		maxheapify(data, length, largest);
	}
}

void heap_sort(int data[], int length)
{
	// build max heap
	for (int i = length/2 ; i > 0; --i)
	{
		maxheapify(data, length, i);
	}

	int root_index = 1;

	// deleteMax
	for (int i = length; i > 1; --i)
	{
		exchange(data, root_index, i);
		maxheapify(data, i -1, 1);
	}
}

int main() {

	time_t start_time;
	time_t end_time;

	std::ifstream outFile("binary", std::ifstream::binary);

    int x;
    for (int i = 0; i < 10; ++i)
    {
    	x = i;
    	//outFile.write((char*)&x, sizeof(int));
    }

    outFile.close();
    ofstream infile("binary", std::ofstream::binary);
    infile.read((char*)&x, sizeof(int));

	int field_id = 0;
	int *buffer = (int*)calloc(pagesize*memsize, sizeof(buffer));

	start_time = clock();
	while (true)
	{
		for (int i = 0; i< pagesize*memsize; ++i)
		{
			//buffer[i] =
		}
		quick_sort(buffer, 0, pagesize*memsize - 1);
	}

	int *buffer1 = (int*)calloc(pagesize, sizeof(buffer1));
	int *buffer2 = (int*)calloc(pagesize, sizeof(buffer2));
	int nRun = 0;

	for (int i = field_id ; i > 1; i/=2)
	{
		int j = 0;
		int c = 0;

		while (j < i)
		{
			ofstream outFile("output.txt",ios::binary);

			ifstream in1("temp_", ios::binary);
			ifstream in2("temp_", ios::binary);

			for (int k = 0; k < pagesize ; ++k)
			{
			}

			//merge_sort(array, MAX, 0, MAX-1);
			c++;
		}
		++nRun;
	}

	end_time = clock();
	cout << "merge_sort time : " << end_time - start_time << "ms"<< endl;

	/*
	for(int i = 1; i < MAX -1;++i)
	{
		if (array[i] > array[i+1])
		{
			printf("assert failed [%d]%d [%d]%d\n", i, array[i], i+1, array[i+1]);
		}
		assert(array[i] <= array[i+1]);
	}*/
	return 0;
}
