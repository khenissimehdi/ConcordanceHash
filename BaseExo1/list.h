#ifndef __LIST_H__
#define __LIST_H__

typedef struct _link {
    char *word;
    int occurrences;
    struct _link *next;
} link;

void free_list(link *lst);

link *find_list(link *lst, char word[]);
link *insert_first_list(link *lst, char word[]);

void display_list(link *lst);

#endif
