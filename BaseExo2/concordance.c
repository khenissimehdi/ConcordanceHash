#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define MAX_WORD_LENGTH 80


void add_occurrence(link *lnk, int pos)
{
    if (lnk->occurrences == NULL)
    {

        olink *newOc = create_olink(pos);

        lnk->occurrences = newOc;
        /* printf("%s , %d \n", lnk->word, lnk->occurrences->pos);*/
        return;
    }

    else
    {

        if (lnk->occurrences->next == NULL)
        {

            olink *newOc = create_olink(pos + 1);
            lnk->occurrences->next = newOc;
        }

        int posBis = lnk->occurrences->pos;

        olink *current = lnk->occurrences;

        while (current->next != NULL)
        {
            /*printf("%s \n", lnk->word);*/

            current = current->next;
            posBis = posBis + 1;
        }

        olink *newOc = create_olink(posBis);

        current->next = newOc;
        /*printf("%s , %d \n", lnk->word, current->next->pos);*/
    }
}

link *read_text(FILE *infile)
{
    link *lst = NULL;
    char *word = (char *)malloc(MAX_WORD_LENGTH * sizeof(char));
    while (fscanf(infile, "%s ", word) != -1)
    {
        link *oc = NULL;
        if (lst != NULL)
        {
            oc = find_list(lst, word);
        }

        if (oc != NULL)
        {
            /* printf("%s \n", word);*/
            add_occurrence(oc, 1);
        }
        else
        {
            lst = insert_first_list(lst, word);
        }
    }
    free(word);
    return lst;
}

int main(int argc, char **argv)
{

    if (argc < 2)
    {
        fprintf(stderr, "Usage: concordance <in_file>\n");
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL)
    {
        fprintf(stderr, "Error opening file for reading: %s\n", argv[1]);
        return 1;
    }

    link *lst = read_text(fin);
    fclose(fin);

    int words = 0;
    link *ptr;
    for (ptr = lst; ptr != NULL; ptr = ptr->next)
    {

        words++;
    }
    display_list(lst);

    printf("total number of words = %d\n", words);

    free_list(lst);

    return 0;
}