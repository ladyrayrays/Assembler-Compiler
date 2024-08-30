#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

struct Symbol
{
	char* symbol;
	int address;
	struct Symbol* next;
};

struct SymbolTable
{
	struct Symbol* head;
};


void printtable(struct SymbolTable* table)
{
	struct Symbol* temp = NULL;
	temp = table->head;
	while( temp != NULL )
	{
		printf("%s\n", temp->symbol);
		printf("%d\n", temp->address);
		temp = temp -> next;
	}
}

void insertAtEnd(struct SymbolTable* table, char* symbol, int item)
{
	if(table->head == NULL)
	{
		table->head = malloc(sizeof(struct Symbol));

		int length = strlen(symbol);
		table->head->symbol = malloc(sizeof(char) * length);
		strcpy(table->head->symbol, symbol);
		table->head->address = item;
		table->head->next = NULL;
	}
	else
	{
	    struct Symbol* temp = NULL;
	    temp = table->head;

	    while(temp->next!= NULL){
            temp = temp->next;
	    }

	    struct Symbol* newNode = NULL;
		newNode = malloc(sizeof(struct Symbol));

		int length1 = strlen(symbol);
		newNode->symbol = malloc(sizeof(char) * length1);
		strcpy(newNode->symbol, symbol);
		newNode->address = item;
		newNode->next = NULL;
		temp->next = newNode;

	}
}


int contains(struct SymbolTable* table, char* symbol){
    struct Symbol* temp = NULL;
    temp = table->head;

    while(temp!= NULL){
        if(strcmp(temp->symbol, symbol) == 0){

            return temp->address;
        }
        temp = temp->next;
    }
    return -1;
}
void destroytable(struct SymbolTable* table)
{
	struct Symbol* temp = table->head;
	while(temp != NULL){
		table->head = temp->next;
		free(temp->symbol);
		free(temp);
		temp = table->head;
	}
}

#endif
