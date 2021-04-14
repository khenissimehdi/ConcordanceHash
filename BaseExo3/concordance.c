#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define MAX_WORD_LENGTH 80
table *tab;

void add_occurrence(link *lnk, int pos)
{

    olink *current = lnk->occurrences;

    while (current->next != NULL)
    {

        current = current->next;
    }

    olink *newOc = create_olink(pos);
    current->next = newOc;
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
    
    link *oc = find(tab, hashCode, word);

    if (oc != NULL)
    {

        add_occurrence(oc, pos);
        
    }

    else
    {

        tab->bucket[hashCode] = insert_first_list(tab->bucket[hashCode], word, pos);
    }
  
  
    
}

void read_text(FILE *infile)
{


  
    char *word = (char *)malloc(MAX_WORD_LENGTH * sizeof(char));
    int pos = 0;
    while (fscanf(infile, "%s ", word) != -1)
    {
        add_occ_table(tab, word, pos);
        pos++;
    }
    free(word);
   
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

    read_text(fin);
    fclose(fin);

  
  
    int i;
    for (i = 0; i < tab->M; i++)
    {
        if (tab->bucket[i] != NULL)
        {
          

            display_list(tab->bucket[i]);
        }
    }
   
    
     for (i = 0; i < tab->M; i++)
    {
         if (tab->bucket[i] != NULL)
        {
      
            free_list(tab->bucket[i]);
        }
     
      
       
    }
 
    free(tab->bucket);
    free(tab);
   

    return 0;
}