//Brianna Cochran
// CS 271
// Compiler.c


#include "symbolTable.h"
 #include <stdio.h>
 #include <string.h>
 #include <math.h>
 #include <stdlib.h>


char* parse(char*);
void getSymbol(char*);
int getUniNum();
void keywordConstant(char*);
void unaryOp(char*);
void Op(char*);
void expressionList(char*);
void subroutineCall(char*);
void term(char*);
void expression(char*);
void returnStatement(char*);
void doStatement(char*);
void whileStatement(char*);
void ifStatement(char*);
void letStatement(char*);
void statement(char*);
void statements(char*);
void varDec(char*);
void subroutineBody(char*);
void parameterList(char*);
void subroutineDec(char*);
void type(char*);
void classVarDec(char*);
void class1(char*);

 int main(){

     FILE *fp;
    char buffer[256];

    fp = fopen("test.txt", "r");

    if(fp == NULL){
        printf("Error opening file\n");
    }
    else{
        while(fgets(buffer, 256, fp) != NULL){
			buffer[strcspn(buffer, "\r\n")] = 0;

			//parse(buffer);

        }
        fclose(fp);
    }

    FILE *fp1;
    char buffer1[256];

    fp1 = fopen("out.txt", "r");

    if(fp1 == NULL){
        printf("Error opening file\n");
    }
    else{
        while(fgets(buffer1, 256, fp1) != NULL){
			buffer1[strcspn(buffer1, "\r\n")] = 0;

			getSymbol(buffer1);

        }
        fclose(fp1);
    }
 }

 int getUniNum(){
    static int num = 0;
    num++;
    return num;
}

//this gives you the symbol in a line. I was trying to figure out to take that and make a get symbol that will go through it.
//was going to create a getkeword that does the same as getsymbol but just contains the word between < >.
//however that would also have the same issue getsymbol
 void getSymbol(char* string){
    int numb = getUniNum();
    char* buffer = (char*)malloc(1000*sizeof(char));
    buffer[999] = '\0';
    int j = 0;
    char* find = strchr(string, '>');
    if(find == NULL){
    }
    else{
        int i = find - string;
        i++;

        while(string[i] != '<' ){
            //I get some random symbols here most likely spaces
            buffer[j] = string[i];
            i++;
            j++;
        }
       // printf("%s",buffer);
    }
 }

 //the next functions I was trying to layout the recursive functions, but ran into some issues
 //Some of my conditions need a specific function to not give an error. I attempted some function() == true, but they don't work
 //don't know exactly how to fix that

 void class1(char* buffer){
     if(strcmp(buffer,"class") == 0){
        //next symbol
        if(strcmp(buffer,"identifier") == 0){
            //next symbol
            if(strcmp(buffer,"{") == 0){
                //next symbol
                while(classVarDec(buffer) == true){
                    //next symbol
                }
                while(subroutineDec(buffer) == true){
                    //next symbold
                }
                if(strcmp(buffer,"}") == 0){

                }
                else{
                    printf("Error in class1");
                }
            }
            else{
                printf("Error in class1");
            }
        }
        else{
            printf("Error in class1");
        }
     }
     else{
        printf("Error in class1");
     }
 }

 void classVarDec(char* buffer){
     if(strcmp(buffer,"static") == 0 || strcmp(buffer,"fied") == 0){
        //next symbol
        type(buffer);
        //next symbol
        if(strcmp(buffer,"identifier") == 0){
            //next symbol
            while(strcmp(buffer,",") == 0){
                //next symbol
                if(strcmp(buffer,"identifier") == 0){
                    //next symbol
                }
                else{
                    printf("error in classVarDec");
                }
            }
            if(strcmp(buffer,";") == 0){

            }
            else{
                printf("Error in classVarDec");
            }
        }
        else{
            printf("Error in classVarDec");
        }
     }
     else{
        printf("Error in classVarDec");
     }
 }

 void type(char* buffer){
     if(strcmp(buffer,"int") == 0 || strcmp(buffer,"char") == 0 || strcmp(buffer,"boolean") == 0 || strcmp(buffer,"identifier") == 0){

     }
     else{
        printf("Error in type");
     }
 }

 void subroutineDec(char* buffer){
     if(strcmp(buffer,"constructor") == 0 || strcmp(buffer,"function") == 0 || strcmp(buffer,"method") == 0){
        //next symbol
        if(strcmp(buffer,"void") == 0 || type(buffer) == true){
            //next symbol
            if(strcmp(buffer,"identifier") == 0){
                //next symbol
                if(strcmp(buffer,"(") == 0){
                    //next symbol
                    parameterList(buffer);
                    //next symbol
                    if(strcmp(buffer,")") == 0){
                        //next symbol
                        subroutineBody(buffer);
                    }
                    else{
                        printf("Error in subroutine Dec");
                    }
                }
                else{
                    printf("Error in subroutine Dec");
                }
            }
            else{
                printf("Error in subroutine Dec");
            }
        }
        else{
            printf("Error in subroutine Dec");
        }
     }
     else{
        printf("Error in subroutine Dec");
     }
 }

 void parameterList(char* buffer){
     type(buffer);
     //next symbol
     if(strcmp(buffer,"identifier") == 0){
        //next symbol
        while(strcmp(buffer,",") == 0){
            //next symbol
            type(buffer);
            //next symbol
            if(strcmp(buffer,"identifier") == 0){
                //next symbol
            }
        }
     }
     else{
        printf("Error in parameterList");
     }
 }


 void subroutineBody(char* buffer){
     if(strcmp(buffer,"{") == 0){
        //next symbol
        while(varDec(buffer) == true){
            //next symbol
        }
        statements(buffer);
        //next symbol
        if(strcmp(buffer,"}") == 0){

        }
        else{
            printf("Error in subroutine body");
        }
     }
     else{
        printf("Error in subroutine body");
     }
 }

 void varDec(char* buffer){
     if(strcmp(buffer,"var") == 0){
        //next symbol
        type(buffer);
        //next symbol
        if(strcmp(buffer,"identifier") == 0){
            //next symbol
            while(strcmp(buffer,",") == 0){
                //next symbol
                if(strcmp(buffer,"identifier") == 0){
                    //next symbol
                }
                else{
                    printf("Error in varDec");
                }
            }
        }
        else{
            printf("Error in varDec");
        }
     }
     else{
        printf("Error in varDec");
     }
 }

 void statements(char* buffer){
     if(statement(buffer) == true){
        while(statement(buffer) == true){
            //next symbol
        }
     }
     else{
        //this if fine
     }

 }

 void statement(char* buffer){
     if(letStatement(buffer) == true || ifStatement(buffer) == true || whileStatement(buffer) == true || doStatement(buffer) == true || returnStatement(buffer) == true){

     }
     else{
        printf("Error in statement");
     }
 }

 void letStatement(char* buffer){
     if(strcmp(buffer,"let") == 0){
        //next symbol
        if(strcmp(buffer,"identifier") == 0){
            //next symbol
            if(strcmp(buffer,"[") == 0){
                //next symbol
                expression(buffer);
                //next symbol
                if(strcmp(buffer,"]") == 0){
                    //next symbol
                    if(strcmp(buffer,"=") == 0){
                        //next symbol
                        expression(buffer);
                        //next symbol
                        if(strcmp(buffer,";") == 0){

                        }
                        else{
                            printf("Error in let statements");
                        }
                    }
                    else{
                        printf("Error in let statements");
                    }
                }
                else{
                    printf("Error in let statements");
                }
            }
            else if(strcmp(buffer,"=") == 0){
                //next symbol
                expression(buffer);
                //next symbol
                if(strcmp(buffer,";") == 0){

                }
                else{
                    printf("Error in let statements");
                }
            }
            else{
                printf("Error in let statements");
            }

        }
        else{
            printf("Error in let statements");
        }
     }
     else{
        printf("Error in let statements");
     }
 }

 void ifStatement(char* buffer){
     if(strcmp(buffer,"if") == 0){
        //next symbol
        if(strcmp(buffer,"(") == 0){
            //next symbol
            expression(buffer);
            //next symbol
            if(strcmp(buffer,")") == 0){
                //next symbol
                if(strcmp(buffer,"{") == 0){
                    //next symbol
                    statements(buffer);
                    //next symbol
                    if(strcmp(buffer,"}") == 0){
                        //next symbol
                        if(strcmp(buffer,"else") == 0){
                            //next symbol
                            if(strcmp(buffer,"{") == 0){
                                //next symbol
                                statements(buffer);
                                //next symbol
                                if(strcmp(buffer,"}") == 0){

                                }
                                else{
                                    printf("Error in if statements");
                                }
                            }
                            else{
                                printf("Error in if statements");
                            }
                        }
                        else{
                            //this is okay
                        }
                    }
                    else{
                        printf("Error in if statements");
                    }
                }
                else{
                    printf("Error in if statements");
                }
            }
            else{
                printf("Error in if statements");
            }
        }
        else{
            printf("Error in if statements");
        }
     }
     else{
        printf("Error in if statements");
     }
 }

void whileStatement(char* buffer){
    if(strcmp(buffer,"while") == 0){
        //next symbol
        if(strcmp(buffer,"(") == 0){
            //next symbol
            expression(buffer);
            //next symbol
            if(strcmp(buffer,")") == 0){
                //next symbol
                if(strcmp(buffer,"{") == 0){
                    //next symbol
                    statements(buffer);
                    //next smybol
                    if(strcmp(buffer,"}") == 0){

                    }
                    else{
                        printf("Error in while statements");
                    }
                }
                else{
                    printf("Error in while statements");
                }
            }
            else{
                printf("Error in while statements");
            }
        }
        else{
            printf("Error in while statements");
        }
    }
    else{
        printf("Error in while statements");
    }

}
 void doStatement(char* buffer){
   if(strcmp(buffer,"do") == 0){
        //next symbol
        if(subroutineCall(buffer) == true){
            //next symbol
            if(strcmp(buffer,";") == 0){

            }
            else{
                printf("Error in doStatement");
            }
        }
        else{
            printf("Error in do Statement");
        }
   }
   else{
    printf("Error in do Statement");
   }
 }

 void returnStatement(char* buffer){
     if(strcmp(buffer,"return") == 0){
            //next symbol
        if(expression(buffer) == true){
            //next symbol
            if(strcmp(buffer,";") == 0){

            }
            else{
                printf("Error in returnStatement");
            }
        }
        else if(strcmp(buffer,";") == 0){

        }
        else{
            printf("Error in returnStatement");
        }
     }
 }

 void expression(char* buffer){
     while(term(buffer) == true){
        //next symbol
        if(op(buffer) == true){

        }
        else if(term(buffer) == true){

        }
        else{
            printf("Error in expression");
        }
     }
 }

 void term(char* buffer){
     if(strcmp(buffer,"integerConstant") == 0 || strcmp(buffer,"stringConstant") == 0 || strcmp(buffer,"keyword") == 0 || strcmp(buffer,"identifier") == 0){

     }
     if(strcmp(buffer,"identifier") == 0){
        //nest symbol
        if(strcmp(buffer,"[") == 0){
            //next symbol
            expression(buffer);
            //next symbol
            if(strcmp(buffer, "]") == 0){

            }
        }
        else if(strcmp(buffer,"[")  != 0){
            //back symbol
        }
        else{
            printf("Error in Term");
        }
     }
     else if(subroutine(buffer) == true){
        subroutineCall(buffer);
     }
     else if(strcmp(buffer,"(") == 0){
        //next symbol
        expression(buffer);
        //next symbol
        if(strcmp(buffer,")") == 0){

        }
     }
     else if(unaryOp(buffer) == true){
        //next symbol
        term(buffer);
     }
     else{
        printf("error in term");
     }
}

 void subroutineCall(char* buffer){
     if(strcmp(buffer,"identifier") == 0){
        //next symbol
        if(strcmp(buffer,"(") == 0){
            //net symbol
            expressionList(buffer);
            //next symbol
            if(strcmp(buffer,")") == 0){

            }
            else{
                printf("Error with subroutineCall");
            }
        }
        else if(strcmp(buffer,".") == 0){
            //next symbol
            if(strcmp(buffer,"identifier") == 0){
                //next symbol
                if(strcmp(buffer,"(") == 0){
                    //next symbol
                    expressionList(buffer);
                    //next symbol
                    if(strcmp(buffer,")") == 0){

                    }
                    else{
                        printf("Error with subroutineCall");
                    }
                }
                else{
                    printf("Error in subroutineCall");
                }
            }
            else{
                printf("Error in subroutineCall");
            }
        }
        else{
            printf("Error in subroutineCall");
        }
     }
     else{
        printf("Error in subroutineCall");
     }
 }

 void expressionList(char* buffer){
     expression(buffer);
     //next symbol
     while(strcmp(buffer,",") == 0){
        //next symbol
        expression(buffer);
        //maybe next symbol here as well
     }
 }
 void Op(char* buffer){
     if(strcmp(buffer,"+") == 0 || strcmp(buffer,"-") == 0 || strcmp(buffer,"*") == 0 || strcmp(buffer,"/") == 0 || strcmP(buffer,"&") == 0 || strcmp(buffer,"|") == 0 || strcmp(buffer,"<") == 0 || strcmp(buffer,">") == 0 || strcmp(buffer,"=") == 0){

     }
     else{
        printf("Error in OP");
     }
 }
 void unaryOp(char* buffer){
     if(strcmp(buffer,"-") == 0 || strcmp(buffer,"~" == 0)){

     }
     else{
        printf("Error in unaryOp");
     }

 }

 void keywordConstant(char* buffer){
     if(strcmp(buffer,"true") == 0 || strcmp(buffer,"false") == 0 || strcmp(buffer,"null") == 0 || strcmp(buffer,"this") == 0){
        //wee good
     }
     else{
        printf("Error in Keyword Constant");
     }

 }

 char* parse(char* string){
     struct SymbolTable myTable;
     myTable.head = NULL;

     insertAtEnd(&myTable, "class", 1);
     insertAtEnd(&myTable, "constructor", 2);
     insertAtEnd(&myTable, "function", 3);
     insertAtEnd(&myTable, "method", 4);
     insertAtEnd(&myTable, "field", 5);
     insertAtEnd(&myTable, "static", 6);
     insertAtEnd(&myTable, "var", 7);
     insertAtEnd(&myTable, "int", 8);
     insertAtEnd(&myTable, "char", 9);
     insertAtEnd(&myTable, "boolean", 10);
     insertAtEnd(&myTable, "void", 11);
     insertAtEnd(&myTable, "true", 12);
     insertAtEnd(&myTable, "false", 13);
     insertAtEnd(&myTable, "null", 14);
     insertAtEnd(&myTable, "this", 15);
     insertAtEnd(&myTable, "let", 16);
     insertAtEnd(&myTable, "do", 17);
     insertAtEnd(&myTable, "if", 18);
     insertAtEnd(&myTable, "else", 19);
     insertAtEnd(&myTable, "while", 20);
     insertAtEnd(&myTable, "return", 21);
     insertAtEnd(&myTable, "{", 22);
     insertAtEnd(&myTable, "}", 23);
     insertAtEnd(&myTable, "(", 24);
     insertAtEnd(&myTable, ")", 25);
     insertAtEnd(&myTable, "[", 26);
     insertAtEnd(&myTable, "]", 27);
     insertAtEnd(&myTable, ".", 28);
     insertAtEnd(&myTable, ",", 29);
     insertAtEnd(&myTable, ";", 30);
     insertAtEnd(&myTable, "+", 31);
     insertAtEnd(&myTable, "-", 32);
     insertAtEnd(&myTable, "*", 33);
     insertAtEnd(&myTable, "/", 34);
     insertAtEnd(&myTable, "&", 35);
     insertAtEnd(&myTable, "|", 36);
     insertAtEnd(&myTable, "<", 37);
     insertAtEnd(&myTable, ">", 38);
     insertAtEnd(&myTable, "=", 39);
     insertAtEnd(&myTable, "~", 40);


     printf("here");

     char* buffer[100];
     strcpy(buffer,"");

     char* whatItIs = (char*)malloc(100*sizeof(char));
     whatItIs[99] = '\0';

     char* correctVer = (char*)malloc(1000*sizeof(char));
     correctVer[999] = '\0';
     strcpy(correctVer,"");




     int i = 0;
     printf("here1");
     while(string[i] != '\0'){
        char* temp[50];
        temp[0] = string[i];
        strncat(buffer,temp,1);
        printf("%s\n",buffer);

        if(string[i] == '"'){
            printf("here3");
            strcpy(buffer,"");
            i++;
            char* temp1[50];
            while(string[i] != '"'){
                printf("here4");
                temp1[0] = string[i];
                strncat(buffer,temp1,1);
                printf("%s\n",buffer);
                i++;
            }
            strcpy(whatItIs,"\n<stringConstant> ");
            strcat(whatItIs,buffer);
            strcat(whatItIs," </stringConstant>");
            printf("%s\n",whatItIs);
            strcat(correctVer,whatItIs);
            printf("%s\n",correctVer);
            strcpy(buffer,"");
        }
        else if(string[i] == ' '){
            printf("here5");
            if(contains(&myTable,buffer) == -1){
                printf("here6");
                    int j = 0;
                    if(isdigit(buffer[j]) != 0){
                        printf("here20");
                        strcpy(whatItIs,"<integerConstant> ");
                        strcat(whatItIs,buffer);
                        strcat(whatItIs," </integerConstant>");
                        printf("%s\n",whatItIs);
                        strcat(correctVer,whatItIs);
                        printf("%s\n",correctVer);
                        strcpy(buffer,"");
                    }
                    else if(strcmp(buffer," ") == 0){
                        printf("no");
                        strcpy(buffer,"");

                    }
                    else{
                        strcpy(whatItIs,"\n<identifier> ");
                        strcat(whatItIs,buffer);
                        strcat(whatItIs," </identifier>");
                        printf("here21");
                        printf("%s\n",whatItIs);
                        strcat(correctVer,whatItIs);
                        printf("%s\n",correctVer);
                        //free(buffer);
                        strcpy(buffer,"");

                    }
            }
            else if(contains(&myTable,buffer) <= 21){
                printf("here9");
                strcpy(whatItIs,"<keyword> ");
                strcat(whatItIs,buffer);
                strcat(whatItIs," </keyword>");
                printf("%s\n",whatItIs);
                strcat(correctVer,whatItIs);
                printf("%s\n",correctVer);
                strcpy(buffer,"");
            }
            else if(contains(&myTable,buffer) >= 22){
                printf("here10");
                strcpy(whatItIs,"\n<symbol> ");
                strcat(whatItIs,buffer);
                strcat(whatItIs," </symbol>");
                printf("%s\n",whatItIs);
                strcat(correctVer,whatItIs);
                printf("%s\n",correctVer);
                strcpy(buffer,"");
            }
        }
        else if(contains(&myTable,temp) >= 22){
            printf("symbolish\n");
            strcpy(whatItIs,"\n<symbol> ");
            strcat(whatItIs,buffer);
            strcat(whatItIs," </symbol>");
            printf("%s\n", whatItIs);
            strcat(correctVer,whatItIs);
            printf("%s\n",correctVer);
            strcpy(buffer,"");
        }

        else if(isdigit(string[i]) != 0){
            printf("hrer12");
            i++;
            char* temp2[50];
            while(isdigit(string[i]) != 0 ){
                temp2[0] = string[i];
                strncat(buffer,temp2,1);
                i++;
            }
            i--;
            strcpy(whatItIs,"\n<integerConstant> ");
            strcat(whatItIs,buffer);
            strcat(whatItIs," </integerConstant>");
            printf("%s\n",whatItIs);
            strcat(correctVer,whatItIs);
            printf("%s\n",correctVer);
            strcpy(buffer,"");
        }
        else{
            int k = i + 1;
            temp[0] = string[k];

            if(contains(&myTable,buffer) != -1){
                if(contains(&myTable,buffer) <= 21){
                    printf("here2000");
                    strcpy(whatItIs,"\n<keyword> ");
                    strcat(whatItIs,buffer);
                    strcat(whatItIs," </keyword>");
                    printf("%s\n",whatItIs);
                    strcat(correctVer,whatItIs);
                    printf("%s\n",correctVer);
                    strcpy(buffer,"");
                }
            }

            else if(contains(&myTable,temp) >= 22){
                printf("howdie");
                strcpy(whatItIs,"\n<identifier> ");
                strcat(whatItIs,buffer);
                strcat(whatItIs," </identifier>");
                printf("%s\n", whatItIs);
                strcat(correctVer,whatItIs);
                printf("%s\n",correctVer);
                strcpy(buffer,"");
            }

        }
        i++;
     }
     printf("outside");
     printf("finish");
        FILE *op;
        op = fopen("out.txt", "a");

        if(op == NULL){
            printf("Error opening file\n");
        }
        else{
            fputs(correctVer,op);
            fputs("\n", op);
            fclose(op);
        }
     return whatItIs;

 }
