
//
//  Indexer.c
//  Indexer
//
//  Created by Timothy Park on 10/29/15.
//  Copyright (c) 2015 Timothy Park. All rights reserved.
//

#include "Indexer.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tokenizer.h"

int dirflag = 0;
int FileSorter()
{
 if(list == NULL)
 {
    return 0;

 }else if(list->head == NULL)
 {
    return 0;
 }else if( list->head->filehead == NULL) 
 {

    return 0;

 }
 struct node* pointer = list->head;
 struct filenode* curr = list->head->filehead;
 struct filenode* Newlist, *iterator, *prevIter;
 Newlist = NULL;
 iterator = Newlist;
 while(pointer != NULL)
 { curr = pointer->filehead;       
   while(curr != NULL)
   {
     if( curr  == NULL)
     { 
	break;	
     } 
     //Selection sort.
     if(curr->next != NULL)
     { curr = pointer->filehead;
       pointer->filehead = curr->next; 
       curr->next = NULL;    
     }else
     {

      curr = pointer->filehead;  
 
      pointer->filehead = NULL;
    
     } 
       
     
     
	 while(1)
         {
       		 if(Newlist == NULL) //First iteration
                 {
         		 Newlist = curr;
         		 prevIter = curr;
         		 iterator = curr->next; 
			 break;
                
		 }else if(iterator == NULL)//Only 1 node
       		 { 	
         		if(curr->count > prevIter->count)
			{
				Newlist = curr;
				curr->next = prevIter;
				prevIter->next = NULL;
				prevIter = Newlist;
				iterator = Newlist;
				break;		   
    	
			}else if(curr->count == prevIter->count)
			{
			 	if(compareChar(curr->filename,prevIter->filename) < 0 )
				{
					Newlist = curr;
					curr->next = prevIter;
					prevIter->next = NULL;
					prevIter = Newlist;
					iterator = Newlist;
					break;
				}else
				{
					Newlist->next = curr;
					curr->next = NULL;
					prevIter = Newlist;
					iterator = Newlist;
					break;
				} 
			}else if(curr->count < prevIter->count)
			{
				 Newlist->next = curr;
                                 prevIter = Newlist;
                                 iterator = Newlist;
                                 break;
			}

			
       		
	       	 }else
		 { 
			if(iterator == prevIter)  //First iteration
			{
		      	        if(curr->count > prevIter->count)
				{
					Newlist = curr;
                                	Newlist->next = iterator;
                                	prevIter = Newlist;
                                	iterator = Newlist;
  	                              	break;					
			
				}else if(curr->count == prevIter->count)
				{
					if(compareChar(curr->filename,prevIter->filename) < 0 )
					{
						Newlist = curr;
                                        	Newlist->next = iterator;
                                        	prevIter = Newlist;
                                        	iterator = Newlist;
						break;
					}else
					{			
						iterator = iterator->next;
						
					}
					
				}else
				{
					iterator = iterator->next;


				}


			}else
			{
				 if(curr->count > iterator->count)
                               	 {
                                        curr->next = iterator;
                                        prevIter->next = curr;
                                        prevIter = Newlist;
                                        iterator = Newlist;
                                        break;
                         
			       }else if(curr->count == iterator->count)
                                {
                                        if(compareChar(curr->filename,iterator->filename) < 0 )
                                        {       
                                                curr->next = iterator;
                                                prevIter->next = curr;
                                                prevIter = Newlist;
                                                iterator = Newlist;
                                                break;
                                        }else if(iterator->next == NULL)
					{	
						iterator->next = curr;
						prevIter = Newlist;
						iterator = Newlist;
						break;						
					}else
                                        {
						prevIter = iterator;
                                                iterator = iterator->next;
						
                                        }

                                }else
				{
					prevIter = iterator;
					iterator = iterator->next;

				}

			}				

		 }
         }     
    
      	curr = pointer->filehead;
	

   }    pointer->filehead = Newlist;
	Newlist = NULL;
	pointer = pointer->next;
 }
	return 1;


}

int FileParser(char* s, char* filename)
{   
    int count = 0;
    FILE *fp;
    fp = fopen(s, "r+");
    if(!fp)
    {
        printf("ERROR");
        exit(EXIT_FAILURE);
    }

    char token[20];
    int ch;
    while(fscanf(fp,"%s",token) == 1 )
    {  
        
        char * tokenP = malloc(sizeof(token));
        tokenP = token;


        tokenP = stringtolwer(token);	
        TokenizerStart(tokenP,tokenP,s);
       
    //    Call Tokenizer on token. Tokenizes the string, puts it in Sorted List.
    }
     fclose(fp);

    return 1;
}

char* stringtolwer(char* string)
{
  size_t i;
  size_t length = strlen(string);

  for(i=0; i<length; i++)
  string[i]=tolower((unsigned char)string[i]);

  return string;
}

void JSONprint(FILE *fp)
{ 
 if(fp == NULL) {
 
 printf("Error");
 exit(EXIT_FAILURE);


}if (list == NULL) 
 {
    return;
 }else if ( list->head == NULL) 
 {
   return;
 }

 struct node* pointer = list->head;
 struct filenode* curr = list->head->filehead;
fprintf(fp,"{\"list\" : [");
while( pointer != NULL) 
{   
     
     
     fprintf(fp,"\n\t{\"%s\" : [", pointer->data);
    
     curr = pointer->filehead;
    while(curr != NULL)
    {  
	 fprintf(fp,"\n\t\t{\"%s\" : %d}", curr->filename, curr->count);
	
	 curr = curr->next;
        
	 if( curr != NULL)
 	 {
 	   fprintf(fp, ",");
         }
    } 
	  fprintf(fp,"\n\t]}");   
 	  pointer = pointer->next;
         if(pointer != NULL) 
	 {
	  fprintf(fp,",");
	 }
	

}	 
 	fprintf(fp,"\n]}");

}

int DirOpen(DIR *pDir, char* PATHNAME)
{
    struct dirent *DirentPtr;
    DIR *pDir2;
    
    pDir = opendir(PATHNAME);
    while ((DirentPtr = readdir(pDir)) != NULL)
    {   char* s = malloc(sizeof(PATHNAME) + 1 + sizeof(DirentPtr->d_name));
        strcpy(s, PATHNAME);
        strcat(s, "/");
        strcat(s, DirentPtr->d_name);
        
        
        if (strcmp(DirentPtr->d_name, "..") == 0 || strcmp(DirentPtr->d_name, ".") == 0
            || strncmp(DirentPtr->d_name, ".", 1) == 0 )
        {
            continue;
        }
        
        else if(((pDir2 = opendir(s)) != NULL ) && DirentPtr->d_type == DT_DIR)
        {
            
            DirOpen(pDir2,s);             // Another Directory
        }
        
        else if(DirentPtr->d_type == DT_REG)
        {
            
            
            FileParser(s, DirentPtr->d_name);
               
            //Open text file and call tokenizer on file.
        }
       
            
    }

    closedir(pDir);
    
    return 1;
}

int FileExists(char *filename)
{  
  FILE * fp1;
  if((fp1 = fopen(filename, "r")))
  {
	fclose(fp1);
        return 1;

  }
       return 0;


}
int main(int argc, char *argv[])
{
    
    DIR *pDir;
    FILE *file, *fp;   
    if ( argc < 2 )//
    {
        printf("Input Error, Exiting...");
        return 1;
    }

       	list = (SortedListPtr)malloc(sizeof(SortedListPtr));   
        list->head == NULL;        
        



   
    char* PATHNAME = malloc(sizeof(argv[2]));
    memcpy(PATHNAME, argv[2], strlen(argv[2]) +1);
    file = fopen(argv[2], "r+");
    if( file != NULL )
    {
     FileParser(PATHNAME,argv[2]);

    }

    pDir = opendir(argv[2]);
    if( pDir == NULL && file == NULL)
    {
        printf ("Not an existing directory or File: '%s'. Exiting... \n ", argv[2]);
        return 1;
    }else if (pDir != NULL)
    {
 	DirOpen(pDir, PATHNAME);
    }
    if(!FileExists(argv[1]))
    {    
  	 
 	 fp = fopen(argv[1],"w");
    }
    else
    {   int a;
	printf("Same filename exists. Would you like to overwrite the existing file? Type 1 for Yes, 0 for No. ");
        scanf("%d", &a);
        if(a == 1) 
	{ 
        
	 fp = fopen(argv[1], "w"); 
	}else if(a == 0)
	{
	 printf("Exiting...");
	 return 1;
	}else 
	{
	 printf("Wrong input. Exiting...");
	 return 1;
	}
       
    }
   
    
    FileSorter();
    JSONprint(fp);
    fclose(fp);
    free(PATHNAME);
    return 1;
    
    
}
