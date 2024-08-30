/*
 Brianna Cochran
 CS 271
 practice.c
 */

 #include <stdio.h>
 #include <string.h>


void fizzbuzz(int num);
int smallest(int array[], int length);
int vowelCount(char* string);
void aOrC(char* string);
void jumpOrDest(char* string);

 int main(){

    fizzbuzz(5);

    int n[10];
    int i;

    for(i = 0; i <=9; i++){
        n[i] = i;
    }
    smallest(n,10);






 }
//fizzbuzz
 void fizzbuzz(int num){

    int counter = 1;

    while(counter != num + 1 ){

        if(counter % 5 == 0 && counter % 3 == 0){
            printf("FizzBuzz\n");
            counter++;
        }
        else if(counter % 5 == 0){
            printf("Buzz\n");
            counter++;
        }
        else if(counter % 3 == 0){
            printf("Fizz\n");
            counter++;
        }
        else{
            printf("%d ", counter);
            printf("\n");
            counter++;
        }

    }


 }
//finds smallest number in array
 int smallest(int array[], int length){

    int counter = 0;
    int small = array[0];

    while(counter < length){

        if(array[counter] < small ){

            small = array[counter];
            counter++;
        }
        else{
            counter++;
        }
    }

    return small;
    printf("\n");

 }
//is the sum of some of the vowels in a string
 int vowelCount(char* string){
    int i = 0;
    int sum=0;

    for(i=0; i<strlen(string); i++){
     if(string[i] == 'a' || string[i] == 'e' || string[i] == 'i' || string[i] == 'o' ){
        sum = sum + 1;
     }

    }
    printf("\n");

    return sum;
 }
//checks first position if its a A instruction or C instruction
void aOrC(char* string){
    int i = 0;

    if(string[i] == '@'){
        printf("A Instruction\n");
    }
    else if(string[i] == 'D' || string[i] == 'M' || string[i] == 'A' || string[i] == '0' || string[i] == '-' || string[i] == '!' || string[i] == '1'){
        printf("C Instruction\n");

    }
    else{
        printf("Not an Instruction\n");
    }


}
//checks string if it has a jump or Dest condition
void jumpOrDest(char* string){
    int i = 0;

    for(i=0; i < strlen(string); i++){

        if(string[i] == ';'){
            printf("Jump\n");
        }
        else if(string[i] == '='){
            printf("Dest\n");

        }
        else{
            printf("Not a Jump or Dest\n");
        }

    }
}
