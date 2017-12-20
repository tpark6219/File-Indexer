//
//  Indexer.h
//  Indexer
//
//  Created by Timothy Park on 10/29/15.
//  Copyright (c) 2015 Timothy Park. All rights reserved.
//

#ifndef __Indexer__Indexer__
#define __Indexer__Indexer__

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "sorted-list.h"

int DirOpen(DIR *pDir, char* PATHNAME);
char* stringtolwer(char * string);
int FileSorter();
#endif /* defined(__Indexer__Indexer__) */
