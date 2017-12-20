//
//  tokenizer.h
//  Indexer
//
//  Created by Timothy Park on 10/30/15.
//  Copyright (c) 2015 Timothy Park. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include "Indexer.h"
#include "sorted-list.h"
#ifndef Indexer_tokenizer_h
#define Indexer_tokenizer_h


struct TokenizerT_  {
    char *input;
    int start;
    int end;
    
};


typedef struct TokenizerT_ TokenizerT;


TokenizerT *TKCreate( char * ts );

void TokenizerStart(char* input, char* filename, char* pathname);

void TKDestroy( TokenizerT * tk );

char * TKTokenize ( TokenizerT * tk);

void TKGetNextToken( TokenizerT * tk, char* filename );

#endif
