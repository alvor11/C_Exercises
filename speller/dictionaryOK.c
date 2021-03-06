/**
 * Implements a dictionary's functionality.
 */
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

typedef struct node {
    char value[45];
    int index;
    struct node* next;//integer
} node;
node *node1;
node *new_node;
node *header;
node *first_node;

int size_hash = 0;//size hashtable
//int flag = 0;// switch to created hashtable 0 - created, 1 - dont created
//char *hashtable[];// array dictionaries words
char *hashword[LENGTH];
//char *hashtable[] = malloc(LENGTH);
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
   //char *hashtable[size_hash]; 
   //if(flag == 0)// created array
  //{
       
       
       //flag = 1;
       header = first_node;
     while(header != NULL)
      {
          if(strcmp(header->value, word) == 0)
          {
              return true;
              break;
          }
          else header = header->next;
          
          /*hashtable[header->index] = header->value;
          printf("%s = %i\n", hashtable[header->index], header->index);
          header = header->next;*/
      }
  // }
   /*int k = 0, position = 0;
   
		for (int i = size_hash - 1; k <= i;)// binaries search
		{
			position = (k + i) / 2 ;
			*hashword = hashtable[position];
			//printf("%s\n", *hashword);
			if (strcmp(*hashword, word) < 0)//compare word
				k = position + 1;
			 else if (strcmp(*hashword, word) > 0) 
				i = position - 1;
			 else 
				 return true;
		}*/
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
    if (fgets(word, LENGTH, dic) != 0)// read word
    size_hash++;
    }
    fseek(dic, 0, SEEK_SET);//return seek to start file
    node1 = NULL;
    new_node = malloc(sizeof(node)); //адресс на следующий елемент
    first_node = new_node;
    if(new_node == NULL) return false; //если удалось выделить память
    while (!feof(dic)) 
    {
        fscanf(dic, "%s", new_node->value);
        //new_node->value = *word;
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
    /*while(header != NULL)
      {
          printf("%s = %i\n", header->value, header->index);
          header = header->next;
      }*/
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
