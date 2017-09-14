/**
 * Implements a dictionary's functionality.
 */
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

typedef struct node {
    char value;
    int index;
    struct node* next;//integer
} node;
node *node1;
node *new_node;
node *header;

int size_hash = 0;//size hashtable
int flag = 0;// switch to created hashtable 0 - created, 1 - dont created
char *hashtable = NULL;// array dictionaries words
char *hashword[LENGTH];
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
    
   if(flag == 0)// created array
   {
       
       hashtable = malloc(size_hash * LENGTH);
       flag = 1;
       node *hash_header = header;
    while(hash_header != NULL)
      {
          hashtable[hash_header->index] = hash_header->value;
          //printf("%s:%d\t", *hashtable[hash_header->index], hash_header->index);
          hash_header = hash_header->next;
      }
   }
   int k = 0, position = 0;
   
		for (int i = size_hash - 1; k <= i;)// binaries search
		{
			position = (k + i) / 2 ;
			*hashword = &hashtable[position];
			//printf("%s\n", *hashword);
			if (strcmp(*hashword, word) < 0)//compare word
				k = position + 1;
			 else if (strcmp(*hashword, word) > 0) 
				i = position - 1;
			 else 
				 return true;
		}
		return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // TODO
     FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    int i = 0;
    char word[LENGTH];
    while(!feof (dic)) //count size dictionarie
    {
    if (fgets(word, LENGTH, dic))// read word
    size_hash++;
    }
    fseek(dic, 0, SEEK_SET);//return seek to start file
    node1 = NULL;
    new_node = malloc(sizeof(node)); //адресс на следующий елемент
    header = new_node;
    if(new_node == NULL) return false; //если удалось выделить память
    while (!feof(dic)) 
    {
        fscanf(dic, "%s", word);
        new_node->value = *word;
        new_node->index = i;
        i++;
        node1 = new_node; //"слудующая" структура становится предыдущей
        if(i < size_hash)
        {
            new_node = malloc(sizeof(node)); //получаем указатель на новую "следующую" структуру
            node1->next = new_node;//присваиваем указател ьна новую структуру
            new_node->next = NULL;//новая структура последняя, указателю присваиваем ноль
        }
    }
    fclose(dic);
    node *p_header = header;
    while(p_header != NULL)
      {
          
          printf("%s:%d\t", p_header->value, p_header->index);
          p_header = p_header->next;
      }
    return true;
}
/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return size_hash;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    node *tokill;
     while(header != NULL)
      {
          tokill = header;
          header = header->next;
          free(tokill);
      }
    return true;
}
