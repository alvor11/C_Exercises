/**
 * Implements a dictionary's functionality.
 */
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "dictionary.h"

typedef struct node {
    char value[46];
    int index;
    struct node* next;//integer
} node;
node* node1 = NULL;
       node* new_node = malloc(sizeof(node)); //адресс на следующий елемент
       node* header = new_node;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
   int k = 0, position = 0;
   char *heshword[LENGTH];
		for (int i = size; k <= i;)
		{
			position = (k + i) / 2 ;
			heshword = hashtable[position];
			printf("position %d: word %s\n", position, hashtable[position]);
			if (heshword < word) 
				k = position + 1;
			 else if (heshword > word) 
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
    int size = 0;
    char word[LENGTH + 1];
    while(!feof (dic)) 
    {
    if (fgets(word, LENGTH + 1, dic))
    size++;
    }
    
       node* node1 = NULL;
       node* new_node = malloc(sizeof(node)); //адресс на следующий елемент
       node* header = new_node;
       if(new_node == NULL) return false; //если удалось выделить память
       fseek(dic, 0, SEEK_SET);
    while (!feof(dic)) 
    {
        fscanf(dic, "%s",new_node->value);
            new_node->index = i;
            i++;
            node1 = new_node; //"слудующая" структура становится предыдущей
            if(i < size)
            {
            new_node = malloc(sizeof(node)); //получаем указатель на новую "следующую" структуру
            node1->next = new_node;
            new_node->next = NULL;// в поле "предыдущей" структуры устанавлтваем
            //указатель на начало новой "след" структуры
            }
      }
      fclose(dic);
      while(header != NULL)
      {
          //printf("%s = %i\n", header->value, header->index);
          hashtable[header->index] = header->value;
          header = header->next;
      }
     
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}
