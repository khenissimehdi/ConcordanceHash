#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define MAX_WORD_LENGTH 80
table *tab;
olink *create_olink(int pos)
{
    olink *occurence = malloc(sizeof(olink));
    occurence->next = NULL;
    occurence->pos = pos;
    return occurence;
}
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
unsigned hash2(char *elt)
{
    int i;
    unsigned h;
    h = 0;
    for (i = 0; elt[i] != '\0'; i++)
    {
        h = 31 * h + elt[i];
    }
    return h;
}

unsigned hash(char *elt, int M)
{
    int i;
    unsigned h;

    h = 0;

    for (i = 0; elt[i] != '\0'; i++)
    {
        h += ((i + 1) * elt[i]);
    }
    unsigned a = h % M;

    return a;
}

link *find(table *tab, unsigned hashCode, char *elt)
{

    return find_list(tab->bucket[hashCode], elt);
}

void add_occ_table(table *tab, char word[], int pos)
{

    unsigned hashCode = hash(word, tab->M);
    /*printf("%d  :  \n", hashCode);*/

    /*link *newWord = create_link(word);*/
    /*if (tab->bucket[hashCode] != NULL)
    {
        printf("%s : %s : %d : %d \n", word, tab->bucket[hashCode]->word, strcmp(tab->bucket[hashCode]->word, word), hashCode);
    }*/
    link *oc = find(tab, hashCode, word);
    if (oc != NULL)
    {

        add_occurrence(oc, pos);
    }

    else
    {

        tab->bucket[hashCode] = insert_first_list(tab->bucket[hashCode], word);
    }
}

link *read_text(FILE *infile)
{

    /* if (tab->bucket[90] == NULL)
    {
        printf("yes its equal to null");
    }*/

    link *lst = NULL;
    char *word = (char *)malloc(MAX_WORD_LENGTH * sizeof(char));
    while (fscanf(infile, "%s ", word) != -1)
    {
        /*link *oc = NULL;
        if (lst != NULL)
        {
            oc = find_list(lst, word);
        }

        if (oc != NULL)
        {
           
            add_occurrence(oc, 1);
        }
        else
        {
            lst = insert_first_list(lst, word);
        }*/
        add_occ_table(tab, word, 1);
    }
    free(word);
    return lst;
}

int main(int argc, char **argv)
{
    tab = create_table(1);

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
    /* printf(" hello %s\n", tab->bucket[5]->word);*/
    int i;
    for (i = 0; i < tab->M; i++)
    {
        if (tab->bucket[i] != NULL)
        {

            display_list(tab->bucket[0]);
        }
    }
    printf("%s : \n", tab->bucket[0]->word);

    /*  link *c = tab->bucket[0] = lst;
    printf("%s \n", c->word);*/

    /* printf("total number of words = %d\n", words);*/

    /*free_list(lst);*/

    return 0;
}