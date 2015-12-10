#include <iostream>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#define MAX (1024*8*4)
int array[MAX+1];
int org_array[MAX+1];
int stack[MAX];

int quick_select(int data[], int front, int rear, int kth);

inline void exchange(int data[], int i, int j)
{
	if (i != j){
		int temp;
		temp = data[i];
		data[i] = data[j];
		data[j] = temp;
	}
}

void stooge_sort(int data[], int front, int rear)
{
	if (data[front] > data[rear])
	{
		exchange(data, front, rear);
	}

	if (rear - front > 1)
	{
		int t = (rear - front + 1) / 3;
		stooge_sort(data, front, rear - t);
		stooge_sort(data, front + t, rear);
		stooge_sort(data, front, rear - t);
	}
}

// stable, in-place sort
void bubble_sort(int data[], int front, int rear)
{
	int i;
	int j;
	int tmp;

	for(int i = rear ; i >= front; --i)
	{
		for(int j = front; j < i ; ++j)
		{
			if (data[j] > data[j+1])
			{
				tmp = data[j];
				data[j] = data[j+1];
				data[j+1] = tmp;
			}
		}
	}
}

void insertion_sort(int data[], int front, int rear)
{
	int j;
	int tmp;
	for(int i = front; i<= rear; ++i)
	{
		tmp = data[i];
		for (j = i; j > front && tmp < data[j-1] ; j--)
		{
			data[j] = data[j-1];
		}
		data[j] = tmp;
	}
}

void merge(int data[], int length, int start, int end)
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
		merge(data, rear-front + 1, front, rear);
	}
}

/*
function select(list, left, right, n)
{
    if left = right
        return left
    loop
        pivotIndex := pivot(list, left, right)
        pivotIndex := partition(list, left, right, pivotIndex)
        if n = pivotIndex
            return n
        else if n < pivotIndex
            right := pivotIndex - 1
        else
            left := pivotIndex + 1
}

pivot selection
  function pivot(list, left, right)
     // for 5 or less elements just get median
     if right - left < 5:
         return partition5(list, left, right)
     // otherwise move the medians of five-element subgroups to the first n/5 positions
     for i from left to right in steps of 5
         // get the median of the i'th five-element subgroup
         subRight := i + 4
         if subRight > right:
             subRight := right

         median5 := partition5(list, i, subRight)
         swap list[median5] and list[left + floor((i - left)/5)]

     // compute the median of the n/5 medians-of-five
     return select(list, left, left + ceil((right - left) / 5) - 1, left + (right - left)/10)
*/

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

// max of stack size : 2
void quick_sort_iterative (int arr[], int front, int rear)
{
    int top = -1;

    int max = -1;

    stack[ ++top ] = front;
    stack[ ++top ] = rear;

    while ( top >= 0 )
    {
        rear = stack[ top-- ];
        front = stack[ top-- ];

        int p = partition( arr, front, rear );

        if ( p-1 > front )
        {
            stack[ ++top ] = front;
            stack[ ++top ] = p - 1;
        }

        if ( p+1 < rear )
        {
            stack[ ++top ] = p + 1;
            stack[ ++top ] = rear;
        }

        if (max < top)
        {
        	max = top;
        }
    }
    printf("max stack index %d\n", max);
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

void select_pivot(int data[], int front, int rear)
{
	if (front == rear)
	{
		return;
	}

	int n = (rear - front + 1) / 5;
	if ((rear - front +1) % 5 != 0)
	{
		n++;
	}
	int i = 0;

	for (i = 0; front + 5*(i+1) -1 <= rear; ++i)
	{
		insertion_sort(data, front + 5*i + 0, front+ 5*i + 4);
		exchange(data, front + i, front + 5 *i +2);
	}
	if (i < n)
	{
		insertion_sort(data, front + 5*i, rear);
		exchange(data, front + i, (front + 5*i + rear)/2);
	}

	quick_select(data, front, front + n - 1, n/2);
	exchange(data, front + n/2, rear);
}

int quick_select_iterative(int data[], int front, int rear, int kth)
{
    if ( front == rear )
    {
    	return data[front];
    }

    int stack[MAX];
    int top = -1;
    int order = kth;
    int pivot_position = 0;

    stack[++top] = front;
    stack[++top] = rear;

    while(top >= 1)
    {
    	rear = stack[top--];
    	front = stack[top--];

        pivot_position = partition(data, front, rear);
        int length = pivot_position - front + 1;
        if ( length == order )
        {
        	break;
        }
        else if ( order < length )
        {
        	stack[++top] = front;
        	stack[++top] = pivot_position-1;
        }
        else
        {
        	stack[++top] = pivot_position + 1;
        	stack[++top] = rear;
        	order -= length;
        }
    }

    return data[pivot_position];
}

int quick_select(int data[], int front, int rear, int kth)
{
    if ( front == rear )
    {
    	return data[front];
    }

    select_pivot(data, front, rear);
    int pivot_position = partition(data, front, rear);

    int length = pivot_position - front + 1;
    if ( length == kth )
    {
    	return data[pivot_position];
    }
    else if ( kth < length )
    {
    	return quick_select(data, front, pivot_position - 1, kth);
    }
    else
    {
    	return quick_select(data, pivot_position + 1, rear, kth - length);
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

	for (int i = 0; i< MAX; ++i)
	{
		org_array[i] = rand() % MAX;
	}

	/*
	for (int i = 0; i< MAX; ++i)
	{
		array[i] = org_array[i];
	}
	start_time = clock();
	stooge_sort(array, 0, MAX - 1);
	end_time = clock();
	cout << "stooge_sort time : " << end_time - start_time << "ms"<< endl;
	 */
	for (int i = 0; i< MAX; ++i)
	{
		array[i] = org_array[i];
	}
	start_time = clock();
	bubble_sort(array, 0, MAX -1);
	end_time = clock();
	cout << "bubble_sort time : " << end_time - start_time << "ms"<< endl;

	for (int i = 0; i< MAX; ++i)
	{
		array[i] = org_array[i];
	}
	start_time = clock();
	insertion_sort(array, 0, MAX -1);
	end_time = clock();
	cout << "insert_sort time : " << end_time - start_time << "ms"<< endl;

	for (int i = 0; i< MAX; ++i)
	{
		array[i] = org_array[i];
	}
	start_time = clock();
	merge_sort(array, MAX, 0, MAX-1);
	end_time = clock();
	cout << "merge_sort time : " << end_time - start_time << "ms"<< endl;

	for (int i = 0; i< MAX; ++i)
	{
		array[i+1] = org_array[i];
	}
	start_time = clock();
	heap_sort(array, MAX);
	end_time = clock();
	cout << "heap_sort time : " << end_time - start_time << "ms"<< endl;

	for (int i = 0; i< MAX; ++i)
	{
		array[i] = org_array[i];
	}
	start_time = clock();
	quick_sort(array, 0, MAX-1);
	end_time = clock();
	cout << "quick_sort time : " << end_time - start_time << "ms"<< endl;

	start_time = clock();
	int result = quick_select(array, 0, MAX-1, 1);
	end_time = clock();
	assert(result == array[0]);
	cout << "quick_select time : " << end_time - start_time << "ms"<< endl;

	for (int i = 0; i< MAX; ++i)
	{
		array[i] = org_array[i];
	}
	start_time = clock();
	quick_sort_iterative(array, 0, MAX-1);
	end_time = clock();
	cout << "quick_sort_iterative time : " << end_time - start_time << "ms"<< endl;

	for(int i = 1; i < MAX -1;++i)
	{
		if (array[i] > array[i+1])
		{
			printf("assert failed [%d]%d [%d]%d\n", i, array[i], i+1, array[i+1]);
		}
		assert(array[i] <= array[i+1]);
	}
	return 0;
}
