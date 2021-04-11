#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define MAX_WORD_LENGTH 80

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
            oc->occurrences = oc->occurrences + 1;
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