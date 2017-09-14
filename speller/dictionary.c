/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
 
 #include "dictionary.h"
 
/**
 * Returns true if word is in dictionary else false.
 */
bool tokill();
 
typedef struct node
{
    bool is_word;
    struct node *children[27];
}
node;
    
node *root; 
node *header;
int pos;
int count;
    
 bool check(const char *word)
 {
    header = root;
    for(int i = 0; i < strlen(word); i++)
    {
        if(isalpha(word[i]))
        {
            pos = tolower(word[i]) - 'a';
        }
        else if (word[i] == '\'')
        {
            pos = 96;
        }
        
        if(header->children[pos] == NULL)
        {
            return false;
        }
        else
        {
            header = header->children[pos];
        }
         
        if((i + 1) == strlen(word) && header->is_word == true)
        {
            return true;
        }
    }
    
    return false;
 }
 
 /**
  * Loads dictionary into memory. Returns true if successful else false.
  */
 bool load(const char *dictionary)
 {
    //open dictionary
    FILE *dic = fopen(dictionary, "r");
    if(dic == NULL)
    {
        return false;
    }
    
    //load dictionary's words
    char word[LENGTH + 1];
    
    //prepare the root of Trie
    root = malloc(sizeof(node));
    if(root == NULL)
    {
        return false;
    }

    while(fscanf(dic, "%s", word) != EOF)
    {
        header = root;
        for(int i = 0; i < strlen(word); i++)
        {
            // check that the char is not a '\'' and convert to ASCII value for pos
            if(isalpha(word[i]))
            {
                pos = tolower(word[i]) - 'a';
            }
            else if (word[i] == '\'')
            {
                pos = 96;
            }
            
            if (header->children[pos] == NULL)
            {
                node *child = malloc(sizeof(node));
                if(child == NULL)
                {
                    return false;
                }
                header->children[pos] = child;
                header = child;
            }
            else
            {
                header = header->children[pos];
            }
                
            //change bool value if at end of word
            if((i + 1) == strlen(word))
            {
                header->is_word = true;
                count++;
            }
        }
    }
    fclose(dic);
    
    return true;
}

 /**
  * Returns number of words in dictionary if loaded else 0 if not yet loaded.
  */
 unsigned int size(void)
 {
    
    
    return count;
 }
 
 /**
  * Unloads dictionary from memory. Returns true if successful
  */
 bool unload(void)
 {
    return tokill(root);
}

bool tokill(node *header)
{
    for(int i = 0; i < 27; i++)
    {
        if(header->children[i] != NULL)
        {
            tokill(header->children[i]);
        }  
    }
    free(header);
     
    return true;
}