#include "table.h"

// string -> hash
unsigned hash(char *s)
{
	unsigned hashvalue;

	for (hashvalue = 0; *s != '\0'; s++)
		hashvalue = *s + 31 * hashvalue;
	return hashvalue % HASHSIZE;
}

// char -> updated table
TEP lookup(Table table, char *s)
{
	TEP te;

	for (te = table->array[hash(s)]; te != NULL; te = te->next)
		if (strcmp(s, te->key) == 0)
			return te;
	return NULL;
}

// char -> updated table
TEP insert(Table table, char *key, char *val)
{
	TEP te;
	unsigned hashval;

	if ((te = lookup(table, key)) == NULL) { /* entry not found */
		te = talloc();
		if (te == NULL || (te->key = strdup(key)) == NULL)
			return NULL;
		hashval = hash(key);
		te->next = table->array[hashval];
		table->array[hashval] = te;
	} else { /* we've already put one into the table */
		free((void *) te->val);
	}
	if ((te->val = strdup(val)) == NULL)
		return NULL;
	return te;
}

Table
creat_hashtable()
{
	return creat_hashtable_with_size(HASHSIZE);
}

Table
creat_hashtable_with_size(int hash_size)
{
	Table hashtable = (Table)malloc(sizeof(Table));
	/* An array of Table Entries */
	hashtable->array = (TEP *)malloc(sizeof(TEP) * hash_size);
	hashtable->hash_size = hash_size;
	return hashtable;
}

void
free_hashtable(Table table)
{
	/* Free all table entries */
	for (int i = 0; i < table->hash_size; i++)
		for (TEP t = table->array[i]; t != NULL;) {
			TEP next = t->next;
			free(t);
			t = next;
		}
	/* Free table array */
	free(table->array);
	free(table);
}
