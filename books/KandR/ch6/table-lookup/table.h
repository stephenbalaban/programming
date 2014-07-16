#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constants
#define HASHSIZE 101
#define talloc() (TEP) malloc(sizeof(TableEntry))

typedef struct tentry TableEntry;
typedef struct tentry *TEP;
typedef struct table *Table;

// structs and types
struct tentry {
	TEP next;
	char *key;
	char *val;
};
struct table {
	TEP *array;
	int hash_size;
};

// variables

// functions
unsigned hash(char *s);
Table creat_hashtable();
Table creat_hashtable_with_size(int hash_size);
TEP lookup(Table table, char *s);
TEP insert(Table table, char *key, char *val);
void free_hashtable(Table table);
