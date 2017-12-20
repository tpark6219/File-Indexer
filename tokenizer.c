/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Indexer.h"
#include "tokenizer.h"
#include "sorted-list.h"
/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 *
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char * ts ) {

    size_t inputlength = strlen(ts);
    TokenizerT *tokenizer = malloc(sizeof(TokenizerT));
    tokenizer->input = malloc(sizeof(char)*inputlength);
    tokenizer->start = 0;
    tokenizer->end = 0;
    tokenizer->input = ts;
    if (ts == NULL) {
        
    }
   
    return tokenizer;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
*/

void TKDestroy( TokenizerT * tk ) {
    if(tk == NULL) {
        return;
    }   free(tk);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */
char * TKTokenize ( TokenizerT * tk) {
    
    char *string = malloc(sizeof(strlen(tk->input)));
    int i = tk->end;
    int ValidFlag = -1;
    if(strlen(tk->input) == 1 && isalpha(tk->input[i]))
    {     // where input is only length 1.
        strncpy(string, &tk->input[tk->start], 1);
        tk->end = strlen(tk->input);
        return string;
        
    }else if(strlen(tk->input) ==1)
    {
        return NULL;   //Case where one character but not a valid character.
    }
    

       
    for (; i< strlen(tk->input); i++)
    {
        
        tk->end = i;
        
        if(tk->end == strlen(tk->input) - 1  && isalnum(tk->input[i]) && ValidFlag == 1)
        {  //Last iteration and it is valid.
            
            strncpy(string, &tk->input[tk->start], strlen(tk->input));
            tk->end = tk->end + 1;
            tk->start = tk->end;	
            string[strlen(tk->input)] = '\0';   
            return string;
            
        }if(tk->end == strlen(tk->input) - 1  && isalpha(tk->input[i]))
        {  //Last iteration and is alpha
            
            strncpy(string, &tk->input[tk->start], strlen(tk->input));
            tk->end = tk->end + 1;
            tk->start = tk->end;        
            string[strlen(tk->input)] = '\0';
            return string;
         
        }
        
        if(!isalpha(tk->input[i]) && ValidFlag == -1) //Starts off with number
        {
            tk->start = tk->start + 1;
            
            continue;
      
        }else if(isalpha(tk->input[i]))
        { 
            ValidFlag = 1;
            
        }else if(!isalnum(tk->input[i]) && ValidFlag == 1)
        {  
            strncpy(string, &tk->input[tk->start], tk->end - tk->start);
            string[tk->end - tk->start] = '\0';
	    tk->end = tk->end + 1;
            tk->start = tk->end;
	    
            return string;
        }
        
        
    }
    return NULL;
}


void  TKGetNextToken( TokenizerT * tk, char* filename ) {
    char *x;
    int count = 0;       
    while(tk->end != strlen(tk->input)) {
        x = TKTokenize(tk);
        if(x != NULL)
        {	 	
            SLInsert(x,filename);
            
          //TODO: Use strings to put into sorted-list
          //Pass in the filepath name. 
   
        }else {

          break;

	}

        
        

    }

    return;
}

/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

void TokenizerStart(char* input, char* filename, char* pathname) {
     TokenizerT *token =  TKCreate(input);

     TKGetNextToken(token, pathname);
    
    
}



