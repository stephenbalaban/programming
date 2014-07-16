#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define debug(...)

int const DEBUG_ON = 1;

typedef struct Node Node;
typedef struct Node Stack;
struct Node {
	int val;
	Node *next;
};

Stack *
stack_push(Stack *head, int val)
{
	Node *n = (Node *)malloc(sizeof(Node));
	n->val = val;
	n->next = head;
	return n;
}

int
stack_peek(Stack *head, int *success)
{
	if (head != NULL) {
		int val = head->val;
		*success = 1;
		return val;
	} else {
		*success = 0;
		return 0;
	}
}

int
random_integer()
{
	static int j = 0;
	srand(time(0) + j);
	j++;
	return rand();
}

int *
random_array(int len)
{
	int *arr = malloc(len * sizeof(int));
	for (int i = 0; i < len; i++) {
		arr[i] = random_integer();
	}
	return arr;
}


int *
stack_to_array(Node *stack, int stacklen, int reverse) {
	int *array = (int *)malloc(sizeof(int) * stacklen);
	int i;
	int success;
	if (reverse) {
		for (i = 0; i < stacklen; i++) {
			array[i] = stack_peek(stack, &success);
			stack = stack->next;
		}
	} else {
		for (i = stacklen - 1; i >= 0; i--) {
			array[i] = stack_peek(stack, &success);
			stack = stack->next;
		}
	}
	return array;
}

int *
merge(int *p, int plen, int *q, int qlen)
{
	Node *merged = NULL;
	int *pend = p + plen;
	int *qend = q + qlen;
	while (p < pend && q < qend) {
		if (*p <= *q) {
			debug("Pushing: %d\n", *p);
			merged = stack_push(merged, *p);
			p++;
		} else {
			debug("Pushing: %d\n", *q);
			merged = stack_push(merged, *q);
			q++;
		}
	}
	while (p < pend) {
		debug("Pushing: %d\n", *p);
		merged = stack_push(merged, *p);
		p++;
	}
	while (q < qend) {
		debug("Pushing: %d\n", *q);
		merged = stack_push(merged, *q);
		q++;
	}
	return stack_to_array(merged, plen + qlen, 0);
}
/**
 * End is inclusive.
 */
int *
msort(int *start, int *end)
{
	if (start < end) {
		int alen = (end - start + 1) / 2;
		int blen = (end - start + 1) - alen;
		int *halfend = start + alen - 1;
		return merge(msort(start, halfend), alen,
		             msort(halfend + 1, end), blen);
	} else {
		return start; /* one element, already sorted. */
	}
}

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

int
int_cmp(const int *a, const int *b)
{
	return *a > *b;
}

int
test_quicksort(int argc, char *argv[]) {
	int len;
	if (argc > 1) {
		len = atoi(argv[1]);
	} else {
		len = 1000;
	}
	if (len > 0) {
		int *arr = random_array(len);
		qsort(arr, len, sizeof(int), int_cmp);
	} else {
		fprintf(stderr, "Can't sort 0 length array.\n");
	}
}

int
test_msort(int argc, char *argv[])
{
	int len;
	if (argc > 1) {
		len = atoi(argv[1]);
	} else {
		len = 1000;
	}
	if (len > 0) {
		int *arr = random_array(len);
		int *sorted = msort(arr, arr + len - 1);
		print_array(sorted, len);
		free(sorted);
	} else {
		fprintf(stderr, "Can't sort 0 length array.\n");
	}
}

int
test_merge(int argc, char *argv[])
{
	int alen = 5;
	int tlen = alen + alen;
	int arr[5] = {1, 2, 3, 1000, 30000 };
	int arr2[5] = {10, 11, 30, 1000, 1001 };
	free(print_array(merge(arr, alen, arr2, alen), tlen));
}

int
test_stack(int argc, char *argv[])
{
	Node *t = NULL;
	t = stack_push(stack_push(stack_push(stack_push(stack_push(t, 1), 2), 3), 4), 5);
	print_array(stack_to_array(t, 5, 0), 5);
}

int
main(int argc, char* argv[])
{
	test_msort(argc, argv);
}
