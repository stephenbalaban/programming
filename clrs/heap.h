typedef struct Tuple Tuple;
struct Tuple {
	int left;
	int right;
};

typedef struct Heap Heap;
struct Heap {
	int *array;
	int length;
	int heap_size;
};

int *print_array(int *arr, int len);
void print_heap(Heap *heap);
int is_max_heap(Heap *heap, int idx);
inline int safe_value(Heap *heap, int index);
inline void heap_swap(Heap *heap, int idxa, int idxb);
void max_heapify(Heap *heap, int idx);
Heap *build_max_heap(int *array, int array_length);
int *hsort(int *array, int array_len);
int test_heap(int argc, char *argv[]);
int test_heapsort(int argc, char *argv[]);

inline int index_parent(int index) { return index >> 1; };
inline int index_left(int index)   { return index << 1; };
inline int index_right(int index)  { return (index << 1) + 1; };
inline int value(Heap *heap, int index) { return heap->array[index]; };
inline int valid(Heap *heap, int index) { return index <= heap->heap_size; };
inline int is_leaf(Heap *heap, int index) { return index > heap->length / 2; };
inline int safe_value(Heap *heap, int index);

/* priority queue functions */
void insert(Heap *heap, int x);
int maximum(Heap *heap);
int extract_max(Heap *heap);
void increase_key(Heap *heap, int x, int k);
