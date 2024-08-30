//Brianna Cochran
// CS 271
//assembly.c


 #include <stdio.h>
 #include <string.h>
 #include <math.h>
 #include <stdlib.h>
 #include "symbolTable.h"

 void aOrC(char* string, struct SymbolTable* myTable); //modified this, see note below @LB
 int charToInt(char);
 int stringToInt(char* string);
 char intToChar(int);
 char* intToBinary(int);
 char* jumpOrDest(char* string);
 char* comp(char* afterEq);
 char* dest(char* string);
 char* jump(char* string);
 char* comp2(char* beforeSimi);
 char* beforeSimi(char* string);
 char* afterSimi(char* string);
 char* beforeEqual(char* string);
 char* afterEqual(char* string);
 char* compDest(char* cInstruct, char* cInstruct2);
 char* comp2Jump(char* cInstruct, char* cInstruct3);
 int symbol(char* string, struct SymbolTable* myTable); //modified this, see note below @LB



 void main(){
     int address = 16;
     int countLine = 0;
    FILE *fp;
    char buffer[256];

	struct SymbolTable myTable;
	myTable.head = NULL;

	/*
	@LB
		You also need to add all of the pre-defined symbols to the symbol table
	*/
	insertAtEnd(&myTable, "R0", 0);
	insertAtEnd(&myTable, "R1", 1);
	insertAtEnd(&myTable, "R2", 2);
	insertAtEnd(&myTable, "R3", 3);
	insertAtEnd(&myTable, "R4", 4);
	insertAtEnd(&myTable, "R5", 5);
	insertAtEnd(&myTable, "R6", 6);
	insertAtEnd(&myTable, "R7", 7);
	insertAtEnd(&myTable, "R8", 8);
	insertAtEnd(&myTable, "R9", 9);
	insertAtEnd(&myTable, "R10", 10);
	insertAtEnd(&myTable, "R11", 11);
	insertAtEnd(&myTable, "R12", 12);
	insertAtEnd(&myTable, "R13", 13);
	insertAtEnd(&myTable, "R14", 14);
	insertAtEnd(&myTable, "R15", 15);
	insertAtEnd(&myTable, "SCREEN", 16384);
	insertAtEnd(&myTable, "KBD", 24576);
	insertAtEnd(&myTable, "sp", 0);
	insertAtEnd(&myTable, "lcl", 1);
	insertAtEnd(&myTable, "arg", 2);
	insertAtEnd(&myTable, "this", 3);
	insertAtEnd(&myTable, "that", 4);

	//etc. A function to do this would be appropriate.
	printf("---------Symbol Table print--------------\n");
	printtable(&myTable);
    printf("---------end Symbol Table print--------------\n");

    fp = fopen("MaxL.asm", "r");

    if(fp == NULL){
        printf("Error opening file\n");
    }
    else{
        while(fgets(buffer, 256, fp) != NULL){
			buffer[strcspn(buffer, "\r\n")] = 0;

            symbol(buffer, &myTable); //modified this @LB
            printf("---------Symbol Table printloop--------------\n");
	printtable(&myTable);
    printf("---------end Symbol Table printloop--------------\n");

        }

        fclose(fp);
    }

	printf("---------Symbol Table print--------------\n");
	printtable(&myTable);
    printf("---------end Symbol Table print--------------\n");
    FILE *fp1;
    char buffer1[256];

    fp1 = fopen("MaxL.asm", "r");

    if(fp1 == NULL){
        printf("Error opening file\n");
    }
    else{
        while(fgets(buffer1, 256, fp1) != NULL){
			buffer1[strcspn(buffer1, "\r\n")] = 0;
			printf("Made it to second open file");
            aOrC(buffer1, &myTable); //modified this @LB

        }

        fclose(fp1);
    }
 }

 void aOrC(char* string, struct SymbolTable* myTable){ //modified this @LB
    int i = 0;
    int endResult = 0;

    if(string[i] == '@'){
		//you needed ' ' around your numbers here -also you want &&, not || @LB
        if(string[1] != '1' && string[1] != '2' && string[1] != '3' && string[1] != '4' && string[1] != '5' && string[1] != '6' && string[1] != '7' && string[1] != '8' && string[1] != '9'){
            endResult = symbol(string, myTable); //modified this @LB
			printf("--------------------------------HERE4 %s\n", endResult);
            intToBinary(endResult);
			printf("--------------------------------HERE5\n");
        }
        else{
            stringToInt(string);
        }


    }
    else if(string[i] == 'D' || string[i] == 'M' || string[i] == 'A' || string[i] == '0' || string[i] == '-' || string[i] == '!' || string[i] == '1'){
       jumpOrDest(string);

    }
    else if(string[i] == '('){
       endResult = symbol(string, myTable);
       intToBinary(endResult);

    }
    else{
        printf("Error not an Instruction\n");
    }



}
int symbol(char* string, struct SymbolTable* myTable){ //modified this @LB
    printf("made it to symbol table\n");

    int i = 0;
	int address = 16;

    int countLine = 0;
    if(string[i] == '@'){
            printf("Beginnning of @\n");
			//you needed ' ' around your numbers here - also you want &&, not || @LB
        if(string[1] != '1' && string[1] != '2' && string[1] != '3' && string[1] != '4' && string[1] != '5' && string[1] != '6' && string[1] != '7' && string[1] != '8' && string[1] != '9' ){
			printf("--------------------------------HERE1\n");
            char* newString = string + 1;

            if(contains(myTable, newString) == -1 ){
				printf("--------------------------------HERE2\n");
                insertAtEnd(myTable, newString, address);
                address++;

                printf("made it to end of @\n");

                return address;

            }
			else{ //you need to deal with the case where the symbol does exist @LB
				printf("--------------------------------HERE3\n");
				address = contains(myTable, string);
				return address;
			}

        }
    }
    else if(string[i] == '('){
       printf("beginning of (\n");

       int length = strlen(string);
       char* newString = malloc(sizeof(char) * (strlen(string)));


	   int originalStringPos = 1;
	   int newStringPos = 0;
	   for(newStringPos = 0; newStringPos < length-2; newStringPos++){ //the -2 ensures you get rid of the )
         newString[newStringPos] = string[originalStringPos++];
	   }

	   newString[newStringPos] = '\0';
       printf("made it to ( %s\n", newString);

       if(contains(myTable, newString) == -1 ){
        insertAtEnd(myTable, newString, countLine++);
        address++;
        printf("made it end of (\n");

        return countLine;

        }

    }
	else{
        countLine++;
        printf("made it to end symbol\n");
        address = contains(myTable, string);

        return address;

	}

}

int charToInt(char digit){
	return digit - '0';
}

char intToChar(int num){
	return num + '0';
}

int stringToInt(char* string){
	printf("--------------------------------HERE6 %s\n", string);
    char* string1 = string + 1;
	int length = strlen(string1);

	int sum = 0;
	int power = 0;
	int i = length-1; // changed here

    while(i >= 0){
        sum = sum + (charToInt(string1[i]) * pow(10,power++));
        i--;
	}
	 intToBinary(sum);

	return sum;
}

char* intToBinary(int num){
	char *result = (char*)malloc(17*sizeof(char));

	int length = 17;
	int i = 0;

	while(i < length ){

        result[i] = '0';
        i++;
	}
	int position = 15;

	while(num > 0){

        int remainder = num % 2;
        num = num / 2;

        result[position] = intToChar(remainder);
        position--;

	}

	result[16] = '\0';

	//printf("%s\n", result);

	FILE *op;
    op = fopen("out.txt", "a"); //notice the "a"

    if(op == NULL){
        printf("Error opening file\n");
    }
    else{
        //fputs writes to a file.
        fputs(result,op);
		fputs("\n", op);
        fclose(op);
    }

    //printf("%s", finalEq);


	return result;
}

char* jumpOrDest(char* string){
    int i = 0;
    char* finalNum = '0';

    for(i=0; i < strlen(string); i++){

        if(string[i] == ';'){// dest is null, ; comp is before, jump is after
           char* aft = afterSimi(string);
           char* bef = beforeSimi(string);
           char* myComp2 = comp2(bef);
           char* myJump = jump(aft);

           //printf("%s\n",comp2Jump(myComp2,myJump));
           finalNum = comp2Jump(myComp2,myJump);
        }

        else if(string[i] == '='){ // jump is null ; comp is after , dest is before
            char* after = afterEqual(string);
            char* before = beforeEqual(string);
            char* myComp = comp(after);
            char* myDest = dest(before);

           // printf("%s\n", compDest(myComp, myDest));
            finalNum = compDest(myComp, myDest);
        }
        else{
                //do nothing
        }
    }
    return finalNum;

}

char* beforeEqual(char* string){

    //position of =
    char* find = strchr(string, '=');
    int position = find - string;

    char* beforeEq = (char*)malloc(4*sizeof(char));
    beforeEq[3] = '\0';
    int i = 0;

    //beforeEqual string
    while(i < 3){
        beforeEq[i] = string[position - 1];
        i++;
        position--;

    }
    return beforeEq;
}

char* afterEqual(char* string){

    char* find = strchr(string, '=');
    int position = find - string;

    char* afterEq = (char*)malloc(4*sizeof(char));
    afterEq[3] = '\0';
    int i = 0;
    int count = 1;

    //afterEqual string
    while(i < 3){
        afterEq[i] = string[position + count];
        i++;
        count++;
    }
    return afterEq;
}

char* afterSimi(char* string){

    char* find = strchr(string, ';');
    int position = find - string;

    char* afterSi = (char*)malloc(4*sizeof(char));
    afterSi[3] = '\0';
    int i = 0;
    int count = 1;

    //after simicolin string
    while(i < 3){
        afterSi[i] = string[position + count];
        i++;
        count++;
    }
    return afterSi;
}

char* beforeSimi(char* string){
    char* find = strchr(string, ';');
    int position = find - string;

    char* beforeSi = (char*)malloc(4*sizeof(char));
    beforeSi[3] = '\0';
    int i = 0;

    //before simicolin string
    while(i < 3){
        beforeSi[i] = string[position - 1];
        i++;
        position--;

    }

    return beforeSi;
}

char* comp(char* afterEq){

    //sets beginning to 1
    char* cInstruct = (char*)malloc(17*sizeof(char));
    cInstruct[16] = '\0'; cInstruct[10] = '0'; cInstruct[11] = '0'; cInstruct[12] = '0'; cInstruct[13] = '0'; cInstruct[14] = '0'; cInstruct[15] = '0'; cInstruct[0] = '1'; cInstruct[1] = '1'; cInstruct[2] = '1';

    //checks for M
   if(strchr(afterEq, 'M') != NULL){
        cInstruct[3] = '1';

        //if m is present
        if(afterEq[0] == '0'){
            cInstruct[4] = '1'; cInstruct[5] = '0'; cInstruct[6] = '1'; cInstruct[7] = '0'; cInstruct[8] = '1'; cInstruct[9] = '0';
        }
        else if(afterEq[0] == 'D' && afterEq[1] == '|' && afterEq[2] == 'M'){
            cInstruct[4] = '0'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '1'; cInstruct[8] = '0'; cInstruct[9] = '1';

        }
        else if(afterEq[0] == 'D' && afterEq[1] == '&' && afterEq[2] == 'M'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '0'; cInstruct[9] = '0';
        }
        else if(afterEq[0] == 'M' && afterEq[1] == '-' && afterEq[2] == 'D'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '0'; cInstruct[7] = '1'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else if(afterEq[0] == 'D' && afterEq[1] == '-' && afterEq[2] == 'M'){
            cInstruct[4] = '0'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else if(afterEq[0] == 'D' && afterEq[1] == '+' && afterEq[2] == 'M'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '1'; cInstruct[9] = '0';
        }
        else if(afterEq[0] == 'M' && afterEq[1] == '-' && afterEq[2] == '1'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '1'; cInstruct[9] = '0';
        }
        else if(afterEq[0] == 'D' && afterEq[1] == '-' && afterEq[2] == '1'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '1'; cInstruct[7] = '1'; cInstruct[8] = '1'; cInstruct[9] = '0';
        }
        else if(afterEq[0] == 'M' && afterEq[1] == '+' && afterEq[2] == '1'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '1'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else if(afterEq[0] == 'D' && afterEq[1] == '+' && afterEq[2] == '1'){
            cInstruct[4] = '0'; cInstruct[5] = '1'; cInstruct[6] = '1'; cInstruct[7] = '1'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else if(afterEq[0] == '-' && afterEq[2] == 'M'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else if(afterEq[0] == '-' && afterEq[1] == 'D'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '1'; cInstruct[7] = '1'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else if(afterEq[0] == '!' && afterEq[1] == 'M'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '0'; cInstruct[9] = '1';
        }
        else if(afterEq[0] == '!' && afterEq[1] == 'D'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '1'; cInstruct[7] = '1'; cInstruct[8] = '0'; cInstruct[9] = '1';
        }
        else if(afterEq[0] == 'M'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '0'; cInstruct[9] = '0';
        }
        else if(afterEq[0] == 'D'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '1'; cInstruct[7] = '1'; cInstruct[8] = '0'; cInstruct[9] = '0';
        }
        else if(afterEq[0] == '-' && afterEq[1] == '1'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '1'; cInstruct[7] = '0'; cInstruct[8] = '1'; cInstruct[9] = '0';
        }
        else if(afterEq[0] == '1'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '1'; cInstruct[7] = '1'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else{
            printf("Error with comp");
        }
   }
   //if m is not present
   else{
        cInstruct[3] = '0';
        if(afterEq[0] == '0'){
            cInstruct[4] = '1'; cInstruct[5] = '0'; cInstruct[6] = '1'; cInstruct[7] = '0'; cInstruct[8] = '1'; cInstruct[9] = '0';
        }
        else if(afterEq[0] == 'D' && afterEq[1] == '|' && afterEq[2] == 'A'){
            cInstruct[4] = '0'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '1'; cInstruct[8] = '0'; cInstruct[9] = '1';

        }
        else if(afterEq[0] == 'D' && afterEq[1] == '&' && afterEq[2] == 'A'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '0'; cInstruct[9] = '0';
        }
        else if(afterEq[0] == 'A' && afterEq[1] == '-' && afterEq[2] == 'D'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '0'; cInstruct[7] = '1'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else if(afterEq[0] == 'D' && afterEq[1] == '-' && afterEq[2] == 'A'){
            cInstruct[4] = '0'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else if(afterEq[0] == 'D' && afterEq[1] == '+' && afterEq[2] == 'A'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '1'; cInstruct[9] = '0';
        }
        else if(afterEq[0] == 'A' && afterEq[1] == '-' && afterEq[2] == '1'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '1'; cInstruct[9] = '0';
        }
        else if(afterEq[0] == 'D' && afterEq[1] == '-' && afterEq[2] == '1'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '1'; cInstruct[7] = '1'; cInstruct[8] = '1'; cInstruct[9] = '0';
        }
        else if(afterEq[0] == 'A' && afterEq[1] == '+' && afterEq[2] == '1'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '1'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else if(afterEq[0] == 'D' && afterEq[1] == '+' && afterEq[2] == '1'){
            cInstruct[4] = '0'; cInstruct[5] = '1'; cInstruct[6] = '1'; cInstruct[7] = '1'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else if(afterEq[0] == '-' && afterEq[1] == 'A'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else if(afterEq[0] == '-' && afterEq[1] == 'D'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '1'; cInstruct[7] = '1'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else if(afterEq[0] == '!' && afterEq[1] == 'A'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '0'; cInstruct[9] = '1';
        }
        else if(afterEq[0] == '!' && afterEq[1] == 'D'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '1'; cInstruct[7] = '1'; cInstruct[8] = '0'; cInstruct[9] = '1';
        }
        else if(afterEq[0] == 'A'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '0'; cInstruct[9] = '0';
        }
        else if(afterEq[0] == 'D'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '1'; cInstruct[7] = '1'; cInstruct[8] = '0'; cInstruct[9] = '0';
        }
        else if(afterEq[0] == '-' && afterEq[1] == '1'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '1'; cInstruct[7] = '0'; cInstruct[8] = '1'; cInstruct[9] = '0';
        }
        else if(afterEq[0] == '1'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '1'; cInstruct[7] = '1'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else{
            printf("Error with comp");
        }
   }

   return cInstruct;

}

char* dest(char* beforeEq){

    char* cInstruct2 = (char*)malloc(17*sizeof(char));
    cInstruct2[16] = '\0';

    int i = 0;
    while(i< 10){
        cInstruct2[i] = '0';
        i++;
    }

    //set jump to 0
    cInstruct2[13] = '0'; cInstruct2[14] = '0'; cInstruct2[15] = '0';

    //checks the dest
    if(beforeEq[0] == 'D' && beforeEq[1] == 'M' && beforeEq[2] == 'A'){
        cInstruct2[10] = '1'; cInstruct2[11] = '1'; cInstruct2[12] = '1';
    }
    else if(beforeEq[0] == 'D'&& beforeEq[1] == 'A'){
        cInstruct2[10] = '1'; cInstruct2[11] = '1'; cInstruct2[12] = '0';
    }
    else if(beforeEq[0] == 'M' && beforeEq[0] == 'A'){
        cInstruct2[10] = '1'; cInstruct2[11] = '0'; cInstruct2[12] = '1';
    }
    else if(beforeEq[0] == 'A'){
        cInstruct2[10] = '1'; cInstruct2[11] = '0';cInstruct2[12] = '0';
    }
    else if(beforeEq[0] == 'D' && beforeEq[1] == 'M'){
        cInstruct2[10] = '0'; cInstruct2[11] = '1'; cInstruct2[12] = '1';
    }
    else if(beforeEq[0] == 'D'){
        cInstruct2[10] = '0'; cInstruct2[11] = '1'; cInstruct2[12] = '0';
    }
    else if(beforeEq[0] == 'M'){
        cInstruct2[10] = '0'; cInstruct2[11] = '0'; cInstruct2[12] = '1';
    }
    else if(beforeEq == NULL){
        cInstruct2[10] = '0'; cInstruct2[11] = '0'; cInstruct2[12] = '0';
    }
    else{
        printf("\nThere is no dest\n");
    }

    return cInstruct2;
}

char* jump(char* afterSi){

    char* cInstruct3 = (char*)malloc(17*sizeof(char));
    cInstruct3[16] = '\0';

    int i = 0;
    while(i < 13){
        cInstruct3[i] = '0';
        i++;
    }

    if(afterSi[0] == 'J' && afterSi[1] == 'G' && afterSi[2] == 'T'){
        cInstruct3[13] = '0'; cInstruct3[14] = '0'; cInstruct3[15] = '1';
    }
    else if(afterSi[0] == 'J' && afterSi[1] == 'E' && afterSi[2] == 'G'){
        cInstruct3[13] = '0'; cInstruct3[14] = '1'; cInstruct3[15] = '0';
    }
    else if(afterSi[0] == 'J' && afterSi[1] == 'G' && afterSi[2] == 'E'){
        cInstruct3[13] = '0'; cInstruct3[14] = '1'; cInstruct3[15] = '1';
    }
    else if(afterSi[0] == 'J' && afterSi[1] == 'L' && afterSi[2] == 'T'){
        cInstruct3[13] = '1'; cInstruct3[14] = '0'; cInstruct3[15] = '0';
    }
    else if(afterSi[0] == 'J' && afterSi[1] == 'N' && afterSi[2] == 'E'){
        cInstruct3[13] = '1'; cInstruct3[14] = '0'; cInstruct3[15] = '1';
    }
    else if(afterSi[0] == 'J' && afterSi[1] == 'L' && afterSi[2] == 'E'){
        cInstruct3[13] = '1'; cInstruct3[14] = '1'; cInstruct3[15] = '0';
    }
    else if(afterSi[0] == 'J' && afterSi[1] == 'M' && afterSi[2] == 'P'){
        cInstruct3[13] = '1'; cInstruct3[14] = '1'; cInstruct3[15] = '1';
    }
    else if(afterSi[0] == NULL){
        cInstruct3[13] = '0'; cInstruct3[14] = '0'; cInstruct3[15] = '0';
    }
    else{
        printf("There was no jump");
    }

    return cInstruct3;
}

char* comp2(char* beforeSi){

    //sets beginning to 1
    char* cInstruct = (char*)malloc(17*sizeof(char));

    cInstruct[16] = '\0'; cInstruct[10] = '0'; cInstruct[11] = '0'; cInstruct[12] = '0'; cInstruct[13] = '0'; cInstruct[14] = '0'; cInstruct[15] = '0'; cInstruct[0] = '1'; cInstruct[1] = '1'; cInstruct[2] = '1';

    //checks for M
   if(strchr(beforeSi, 'M') != NULL){
        cInstruct[3] = '1';

        //if m is present
        if(beforeSi[0] == '0'){
            cInstruct[4] = '1'; cInstruct[5] = '0'; cInstruct[6] = '1'; cInstruct[7] = '0'; cInstruct[8] = '1'; cInstruct[9] = '0';
        }
        else if(beforeSi[0] == 'D' && beforeSi[1] == '|' && beforeSi[2] == 'M'){
            cInstruct[4] = '0'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '1'; cInstruct[8] = '0'; cInstruct[9] = '1';
        }
        else if(beforeSi[0] == 'D' && beforeSi[1] == '&' && beforeSi[2] == 'M'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '0'; cInstruct[9] = '0';
        }
        else if(beforeSi[0] == 'M' && beforeSi[1] == '-' && beforeSi[2] == 'D'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '0'; cInstruct[7] = '1'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else if(beforeSi[0] == 'D' && beforeSi[1] == '-' && beforeSi[2] == 'M'){
            cInstruct[4] = '0'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else if(beforeSi[0] == 'D' && beforeSi[1] == '+' && beforeSi[2] == 'M'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '1'; cInstruct[9] = '0';
        }
        else if(beforeSi[0] == 'M' && beforeSi[1] == '-' && beforeSi[2] == '1'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '1'; cInstruct[9] = '0';
        }
        else if(beforeSi[0] == 'D' && beforeSi[1] == '-' && beforeSi[2] == '1'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '1'; cInstruct[7] = '1'; cInstruct[8] = '1'; cInstruct[9] = '0';
        }
        else if(beforeSi[0] == 'M' && beforeSi[1] == '+' && beforeSi[2] == '1'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '1'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else if(beforeSi[0] == 'D' && beforeSi[1] == '+' && beforeSi[2] == '1'){
            cInstruct[4] = '0'; cInstruct[5] = '1'; cInstruct[6] = '1'; cInstruct[7] = '1'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else if(beforeSi[0] == '-' && beforeSi[2] == 'M'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else if(beforeSi[0] == '-' && beforeSi[1] == 'D'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '1'; cInstruct[7] = '1'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else if(beforeSi[0] == '!' && beforeSi[1] == 'M'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '0'; cInstruct[9] = '1';
        }
        else if(beforeSi[0] == '!' && beforeSi[1] == 'D'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '1'; cInstruct[7] = '1'; cInstruct[8] = '0'; cInstruct[9] = '1';
        }
        else if(beforeSi[0] == 'M'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '0'; cInstruct[9] = '0';
        }
        else if(beforeSi[0] == 'D'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '1'; cInstruct[7] = '1'; cInstruct[8] = '0'; cInstruct[9] = '0';
        }
        else if(beforeSi[0] == '-' && beforeSi[1] == '1'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '1'; cInstruct[7] = '0'; cInstruct[8] = '1'; cInstruct[9] = '0';
        }
        else if(beforeSi[0] == '1'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '1'; cInstruct[7] = '1'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else{
            printf("Error with comp");
        }
   }
   //if m is not present
   else{
        cInstruct[3] = '0';
        if(beforeSi[0] == '0'){
            cInstruct[4] = '1'; cInstruct[5] = '0'; cInstruct[6] = '1'; cInstruct[7] = '0'; cInstruct[8] = '1'; cInstruct[9] = '0';
        }
        else if(beforeSi[0] == 'D' && beforeSi[1] == '|' && beforeSi[2] == 'A'){
            cInstruct[4] = '0'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '1'; cInstruct[8] = '0'; cInstruct[9] = '1';
        }
        else if(beforeSi[0] == 'D' && beforeSi[1] == '&' && beforeSi[2] == 'A'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '0'; cInstruct[9] = '0';
        }
        else if(beforeSi[0] == 'A' && beforeSi[1] == '-' && beforeSi[2] == 'D'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '0'; cInstruct[7] = '1'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else if(beforeSi[0] == 'D' && beforeSi[1] == '-' && beforeSi[2] == 'A'){
            cInstruct[4] = '0'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else if(beforeSi[0] == 'D' && beforeSi[1] == '+' && beforeSi[2] == 'A'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '1'; cInstruct[9] = '0';
        }
        else if(beforeSi[0] == 'A' && beforeSi[1] == '-' && beforeSi[2] == '1'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '1'; cInstruct[9] = '0';
        }
        else if(beforeSi[0] == 'D' && beforeSi[1] == '-' && beforeSi[2] == '1'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '1'; cInstruct[7] = '1'; cInstruct[8] = '1'; cInstruct[9] = '0';
        }
        else if(beforeSi[0] == 'A' && beforeSi[1] == '+' && beforeSi[2] == '1'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '1'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else if(beforeSi[0] == 'D' && beforeSi[1] == '+' && beforeSi[2] == '1'){
            cInstruct[4] = '0'; cInstruct[5] = '1'; cInstruct[6] = '1'; cInstruct[7] = '1'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else if(beforeSi[0] == '-' && beforeSi[1] == 'A'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else if(beforeSi[0] == '-' && beforeSi[1] == 'D'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '1'; cInstruct[7] = '1'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else if(beforeSi[0] == '!' && beforeSi[1] == 'A'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '0'; cInstruct[9] = '1';
        }
        else if(beforeSi[0] == '!' && beforeSi[1] == 'D'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '1'; cInstruct[7] = '1'; cInstruct[8] = '0'; cInstruct[9] = '1';
        }
        else if(beforeSi[0] == 'A'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '0'; cInstruct[7] = '0'; cInstruct[8] = '0'; cInstruct[9] = '0';
        }
        else if(beforeSi[0] == 'D'){
            cInstruct[4] = '0'; cInstruct[5] = '0'; cInstruct[6] = '1'; cInstruct[7] = '1'; cInstruct[8] = '0'; cInstruct[9] = '0';
        }
        else if(beforeSi[0] == '-' && beforeSi[1] == '1'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '1'; cInstruct[7] = '0'; cInstruct[8] = '1'; cInstruct[9] = '0';
        }
        else if(beforeSi[0] == '1'){
            cInstruct[4] = '1'; cInstruct[5] = '1'; cInstruct[6] = '1'; cInstruct[7] = '1'; cInstruct[8] = '1'; cInstruct[9] = '1';
        }
        else{
            printf("Error with comp");
        }
   }

    return cInstruct;
}
//combines comp and dest for =
//comp 0-9 dest 10-12 13-15 is 0
char* compDest(char* cInstruct, char* cInstruct2){
    char* finalEq = (char*)malloc(17*sizeof(char));
    finalEq[16] = '\0';

    finalEq[0] = cInstruct[0]; finalEq[1] = cInstruct[1]; finalEq[2] = cInstruct[2]; finalEq[3] = cInstruct[3];
    finalEq[4] = cInstruct[4]; finalEq[5] = cInstruct[5]; finalEq[6] = cInstruct[6]; finalEq[7] = cInstruct[7];
    finalEq[8] = cInstruct[8]; finalEq[9] = cInstruct[9]; finalEq[10] = cInstruct2[10]; finalEq[11] = cInstruct2[11];
    finalEq[12] = cInstruct2[12]; finalEq[13] = cInstruct2[13]; finalEq[14] = cInstruct2[14]; finalEq[15] = cInstruct2[15];

    FILE *op;
    op = fopen("out.txt", "a"); //notice the "a"

    if(op == NULL){
        printf("Error opening file\n");
    }
    else{
        //fputs writes to a file.
        fputs(finalEq, op);
		fputs("\n", op);

        fclose(op);
    }

	return finalEq;
    //printf("%s", finalEq);
}

//combines comp and jump for ;
 char* comp2Jump(char* cInstruct, char* cInstruct3){
     char* finalEq = (char*)malloc(17*sizeof(char));
     finalEq[16] = '\0';

    finalEq[0] = cInstruct[0]; finalEq[1] = cInstruct[1]; finalEq[2] = cInstruct[2]; finalEq[3] = cInstruct[3];
    finalEq[4] = cInstruct[4]; finalEq[5] = cInstruct[5]; finalEq[6] = cInstruct[6]; finalEq[7] = cInstruct[7];
    finalEq[8] = cInstruct[8]; finalEq[9] = cInstruct[9]; finalEq[10] = cInstruct3[10]; finalEq[11] = cInstruct3[11];
    finalEq[12] = cInstruct3[12]; finalEq[13] = cInstruct3[13]; finalEq[14] = cInstruct3[14]; finalEq[15] = cInstruct3[15];

    FILE *op;
    op = fopen("out.txt", "a"); //notice the "a"

    if(op == NULL){
        printf("Error opening file\n");
    }
    else{
        //fputs writes to a file.
        fputs(finalEq,op);
		fputs("\n", op);
        fclose(op);
    }
    //printf("%s", finalEq);
	return finalEq;

 }
