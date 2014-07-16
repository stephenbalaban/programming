/**
 * "Table Lookup"
 * Author: Stephen A. Balaban, October 2012
 * From The C Programming Language - Chapter 6 - Table Lookup
 */
#include <stdio.h>
#include "table.h"

static Table hashtable;

void plookup(Table hashtab, char* key)
{
	TEP result;
	char* val;
	if ((result = lookup(hashtab, key)) != NULL)
	    val = result->val;
	else 
	    val = "Not Found";
	printf("lookup(hashtab, \"%s\") -> \"%s\"\n", key, val);
}

void load(Table hashtab) 
{
	insert(hashtab, "Roni","Routh");
	insert(hashtab, "Marilyn","Vereen");
	insert(hashtab, "Gilma","Stansell");
	insert(hashtab, "Rogelio","Pelaez");
	insert(hashtab, "Dusti","Mccollum");
	insert(hashtab, "Tamesha","Latson");
	insert(hashtab, "Shanita","Capuano");
	insert(hashtab, "Nancie","Montas");
	insert(hashtab, "Brittany","Coates");
	insert(hashtab, "Gregory","Avey");
	insert(hashtab, "Marlana","Eber");
	insert(hashtab, "Jacinda","Carrero");
	insert(hashtab, "Caroll","Burditt");
	insert(hashtab, "Karie","Morein");
	insert(hashtab, "Celia","Sorg");
	insert(hashtab, "Claudine","Pendarvis");
	insert(hashtab, "Myles","Steimle");
	insert(hashtab, "Jolie","Araki");
	insert(hashtab, "Hang","Jantzen");
	insert(hashtab, "Phung","Thakkar");
	insert(hashtab, "Kellye","Rippe");
	insert(hashtab, "Britta","Widell");
	insert(hashtab, "Katelin","Aday");
	insert(hashtab, "Charissa","Welty");
	insert(hashtab, "Agatha","Sain");
	insert(hashtab, "Albertha","Reddick");
	insert(hashtab, "Genie","Spruell");
	insert(hashtab, "Judith","Hornbaker");
	insert(hashtab, "Yuri","Draughn");
	insert(hashtab, "Clemente","Mcshane");
	insert(hashtab, "Layne","Crepeau");
	insert(hashtab, "Mable","Macneil");
	insert(hashtab, "Mariana","Lankford");
	insert(hashtab, "Joette","Joshi");
	insert(hashtab, "Alice","Conner");
	insert(hashtab, "Lianne","Raco");
	insert(hashtab, "Raguel","Hillebrand");
	insert(hashtab, "Adelaide","Ebling");
	insert(hashtab, "Beckie","Wyss");
	insert(hashtab, "Kendal","Lee");
	insert(hashtab, "Julene","Billingslea");
	insert(hashtab, "Richie","Mohammed");
	insert(hashtab, "Antonette","Maples");
	insert(hashtab, "Tamie","Engstrom");
	insert(hashtab, "Loise","Stimson");
	insert(hashtab, "Milda","Sedgwick");
	insert(hashtab, "Hong","Gumbs");
	insert(hashtab, "Junita","Mccubbin");
	insert(hashtab, "Frank","Whitesides");
	insert(hashtab, "Brenda","Hayhurst");
	insert(hashtab, "Stephen", "Balaban");
}

void print_hashtab(Table hashtab)
{
	int i;
	TEP tep;
	for (i = 0; i < hashtab->hash_size; i++) {
		printf("HKEY <%d> ->>> ", i);
		for (TEP t = hashtab->array[i]; t != NULL; t = t->next) {
			printf("TEP<%s, %s>, ", t->key, t->val);
		}
		printf("\n");
	}
}

int main(int argc, char* argv[])
{
	hashtable = creat_hashtable();

	load(hashtable);
	plookup(hashtable, "Stephen");
	plookup(hashtable, "Frank");
	print_hashtab(hashtable);

	free_hashtable(hashtable);
}
