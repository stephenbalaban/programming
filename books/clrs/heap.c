/**
 * Heaps, heapsort, and a priority queue.
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "heap.h"

/* Aux functions */

int *
print_array(int *arr, int len)
{
	printf("[");
	int i = 0;
	for (i = 0; i < len - 1; i++) {
		printf("%d, ", arr[i]);
	}
	printf("%d", arr[i]);
	printf("]\n");
	return arr;
}


void
print_heap(Heap *heap)
{
	int i;
	printf("is_max_heap? %d\n", is_max_heap(heap, 1));
	for (i = 1; i <= heap->heap_size; i++)
	{
		printf("leaf? %d %d\t-> %d\n\t\t-> %d\n",
				is_leaf(heap, i),
				value(heap, i),
				safe_value(heap, index_left(i)),
				safe_value(heap, index_right(i)));
	}
}

int
is_max_heap(Heap *heap, int idx)
{
	int cval = value(heap, idx);
	int left_idx = index_left(idx);
	int right_idx = index_right(idx);
	if (is_leaf(heap, idx)) {
		return 1;
	} else {
		int gt_left, gt_right;
		if (valid(heap, left_idx)) {
			gt_left = value(heap, left_idx) <= cval;
			gt_left &= is_max_heap(heap, left_idx);
		} else {
			gt_left = 1;
		}
		if (valid(heap, right_idx)) {
			gt_right = value(heap, right_idx) <= cval;
			gt_right &= is_max_heap(heap, right_idx);
		} else {
			gt_right = 1;
		}
		return gt_left && gt_right;
	}
}


inline int
safe_value(Heap *heap, int index)
{
	if (index <= heap->heap_size) {
		return heap->array[index];
	} else {
		return -1337;
	}
}


/* Heap data structures & functions. */

inline void
heap_swap(Heap *heap, int idxa, int idxb)
{
	int tmp = heap->array[idxa];
	heap->array[idxa] = heap->array[idxb];
	heap->array[idxb] = tmp;
}

/**
 * Maintain the max-heap property in heap.
 */
void
max_heapify(Heap *heap, int idx)
{
	/* Find the largest element in { root, left, right } */
	int largest_idx;
	int left_idx = index_left(idx);
	int right_idx = index_right(idx);
	if (valid(heap, left_idx)
	    && (value(heap, left_idx) > value(heap, idx))) {
		largest_idx = left_idx;
	} else {
		largest_idx = idx;
	}
	if (valid(heap, right_idx)
	    && (value(heap, right_idx) > value(heap, largest_idx))) {
		largest_idx = right_idx;
	}
	printf("The largest index of c l r (%d, %d), (%d, %d) (%d, %d) == (%d, %d)\n",
			idx, value(heap, idx),
			left_idx, value(heap, left_idx),
			right_idx, value(heap, right_idx),
			largest_idx, value(heap, largest_idx));
	/* Swap idx with largest_idx */
	if (largest_idx != idx) {
		printf("Largest idx != idx!, swap (%d, %d) with (%d, %d), then "
				"heapify (%d, %d).\n",
				idx, value(heap, idx),
				largest_idx, value(heap, largest_idx),
				largest_idx, value(heap, largest_idx));
		heap_swap(heap, idx, largest_idx);
		max_heapify(heap, largest_idx);
	}
}

Heap *
build_max_heap(int *array, int array_length)
{
	Heap *heap = (Heap *)malloc(sizeof(Heap));
	heap->array = array;
	heap->length = array_length;
	heap->heap_size = array_length;
	int i;
	for (i = heap->heap_size / 2; i >= 1; i--) {
		max_heapify(heap, i);
	}
	return heap;
}

int *
hsort(int *array, int array_len)
{
	Heap *heap = build_max_heap(array, array_len);
	int i;
	for (i = heap->heap_size; i >= 2; i--) {
		heap_swap(heap, 1, i);
		heap->heap_size = heap->heap_size - 1;
		max_heapify(heap, 1);
	}
	return heap->array + 1;
}

int
test_heap(int argc, char *argv[])
{
	int array[12] = { -1888, -1, 120312, 33, 1, -30, 30, 102, 2, 4021, 31023, -1238
			};
	Heap *heap = build_max_heap(array, 11);
	print_heap(heap);
	return 0;
}

int
test_heapsort(int argc, char *argv[])
{
	int array[12] = { -1888, -1, 120312, 33, 1, -30, 30, 102, 2, 4021, 31023, -1238
			};
	int *array_sorted = hsort(array, 11);
	print_array(array_sorted, 11);
	return 0;
}

int
main (int argc, char *argv[])
{
	return test_heapsort(argc, argv);
}
