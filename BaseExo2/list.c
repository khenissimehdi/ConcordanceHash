#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/**
 * Create a link representing 1 occurence of the string 'word'.
 * The string is copied and must be freed when the link is freed.
 */
link *create_link(char word[])
{
    link *lnk = malloc(sizeof(link));
    lnk->word = malloc(strlen(word) + 1);
    strcpy(lnk->word, word);
    lnk->occurrences = NULL;
    lnk->next = NULL;
    return lnk;
}

void free_link(link *lnk)
{
    free(lnk->word);
    free(lnk);
}

void display_list(link *lst)
{
    while (lst)
    {

        if (lst->occurrences != NULL)
        {

            olink *current = lst->occurrences;
            printf("%s : ", lst->word);
            /*printf("%d ,", current->pos);*/
            while (current != NULL)
            {
                if (current->next != NULL)
                {
                    printf("%d ,", current->pos);
                }
                else
                {
                    printf("%d ", current->pos);
                }

                current = current->next;
            }
            putchar('\n');
        }
        else
        {
            printf("%s : %d\n", lst->word, 0);
        }

        lst = lst->next;
    }
}
olink *create_olink(int pos)
{
    olink *occurence = malloc(sizeof(olink));
    occurence->next = NULL;
    occurence->pos = pos;
    return occurence;
}
void free_list(link *lst)
{
    while (lst)
    {
        link *tmp = lst;
        lst = lst->next;
        free_link(tmp);
    }
}

int equal(char *w1, char *w2)
{
    return strcmp(w1, w2) == 0;
}

link *find_list(link *lst, char word[])
{
    link *ptr = lst;
    while (ptr != NULL && !equal(ptr->word, word))
        ptr = ptr->next;
    return ptr;
}

link *insert_first_list(link *lst, char word[], int pos)
{
    link *tmp = create_link(word);
    tmp->occurrences = create_olink(pos);
    tmp->next = lst;

    return tmp;
}
