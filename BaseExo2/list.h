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
void free_list(link *lst);
olink *create_olink(int pos);
link *find_list(link *lst, char word[]);
link *insert_first_list(link *lst, char word[], int pos);

void display_list(link *lst);

#endif
