#ifndef __LIST_H__
#define __LIST_H__

typedef struct _olink
{
    int pos;
    struct _olink *next;
} olink;

typedef struct _link
{
    char *word;
    olink *occurrences; /* liste des occurrences */
    struct _link *next;
} link;

typedef struct _table
{
    link **bucket;
    int M;    /* nombre de seaux */
    int size; /* nombre de mots dans la table */
} table;

void free_list(link *lst);
table *create_table(int M);
link *create_link(char word[]);
link *find_list(link *lst, char word[]);
link *insert_first_list(link *lst, char word[]);

void display_list(link *lst);

#endif
