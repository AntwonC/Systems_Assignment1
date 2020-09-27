#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "mymalloc.h" //or something

double testA();
double testB();
double testC();
double testD();
double testE();
double testF();

int main(int argc, char * argv[]){
    double testA_totalTime = 0;
    double testB_totalTime = 0;
    double testC_totalTime = 0;
    double testD_totalTime = 0;
    double testE_totalTime = 0;
    double testF_totalTime = 0;
    int i = 0;

    for(i = 0; i < 1; i++){
      // testA_totalTime += testA();
       // testB_totalTime += testB();
     //   testC_totalTime += testC();
     //   testD_totalTime += testD();
     //   testE_totalTime += testE();
        testF_totalTime += testF();
    }
    printf("Totals:\n");
  //  printf("A: %f\n", testA_totalTime);
  //  printf("B: %f\n", testB_totalTime);
    //printf("C: %f\n", testC_totalTime);
    //printf("D: %f\n", testD_totalTime);
   // printf("E: %f\n", testE_totalTime);
    printf("F: %f\n", testF_totalTime);
    printf("\nAverages:\n");
 //  printf("A: %f\n", testA_totalTime/(double)100);
  //  printf("B: %f\n", testB_totalTime/(double)100);
   // printf("C: %f\n", testC_totalTime/(double)100);
    //printf("D: %f\n", testD_totalTime/(double)100);
   // printf("E: %f\n", testE_totalTime/(double)100);
   printf("F: %f\n", testF_totalTime/(double)100);

    return 0;
}

double testA(){
    int i = 0;
    char* vari;
    struct timeval t0;
    struct timeval t1;
	
    gettimeofday(&t0, NULL);
    for(i = 0; i < 150; i++){
        vari = (char*) malloc(1 * sizeof(char));
        free(vari);
    }
    gettimeofday(&t1, NULL);

    return (double)(t1.tv_sec-t0.tv_sec) + ((t1.tv_usec-t0.tv_usec) / (double)1000000);
}


double testB(){
    int i = 0;
    int j = 0;

    char* vari;
    char* store[50];
    struct timeval t0;
    struct timeval t1;

    gettimeofday(&t0, NULL);
    for(j = 0; j < 3; j++){
        for(i = 0; i < 50; i++){
            vari = (char*) malloc(1 * sizeof(char));
            store[i] = vari;
        }
        for(i = 0; i < 50; i++){
            free(store[i]);
        }
    }
    gettimeofday(&t1, NULL);
    return (double)(t1.tv_sec-t0.tv_sec) + ((t1.tv_usec-t0.tv_usec) / (double)1000000);
}

double testC(){
    srand(time(NULL));
    int mallocCount = 0;
    int freeCount = 0;
    int randNum = 0;
    char* vari;
    char* toFree[50];
    struct timeval t0;
    struct timeval t1;
    gettimeofday(&t0, NULL);
    while (mallocCount < 50){
        randNum = (rand() % (2));
	//printf("%d\n", randNum);
        if(randNum){
            vari = (char*) malloc(1 * sizeof(char));
            toFree[mallocCount] = vari;
            mallocCount++;
        }
        else if(freeCount != mallocCount){
            free(toFree[freeCount]);
		//printmyblock();
            freeCount++;
        }
    }
    while(freeCount < 50){
        free(toFree[freeCount]);
	//printmyblock();
        freeCount++;
    }
    gettimeofday(&t1, NULL);

    return (double)(t1.tv_sec-t0.tv_sec) + ((t1.tv_usec-t0.tv_usec) / (double)1000000);
} 

double testD(){
    srand(time(NULL));
    int mallocCount = 0;
    int freeCount = 0;
    int randNum = 0;
    int randNum2 = 0;
    char* vari;
    char* toFree[50];
    struct timeval t0;
    struct timeval t1;

    gettimeofday(&t0, NULL);
    while (mallocCount < 50){
        
        randNum = (rand() % (2));
    
        randNum2 = (rand() % (64)) + 1;
        
        if(randNum){
            vari = (char*) malloc(randNum2 * sizeof(char));
            if(vari != NULL){
                toFree[mallocCount] = vari;
                mallocCount++;
            }
            else{
                //hmmm
            }
        }
        else if(freeCount != mallocCount){
            free(toFree[freeCount]);
            freeCount++;
        }
    }

    while(freeCount < 50){
        free(toFree[freeCount]);
        freeCount++;
    }
    gettimeofday(&t1, NULL);

    return (double)(t1.tv_sec-t0.tv_sec) + ((t1.tv_usec-t0.tv_usec) / (double)1000000);
}

double testE(){
    srand(time(NULL)); 
    int randNum = 0; 
    int randNum2 = 0;

    int num = (rand() % (99) ) + 1;  // Picks to run x amount of times. 
    int* vari; 
  
    int mallocCount = 0; // Keep track of number of mallocs 
    int* store_Malloc[50]; // Do this 50 times

    int freeCount = 0; 

    struct timeval t0; 
    struct timeval t1; 

    gettimeofday(&t0, NULL);

    // Mallocs 50 times till 50 times. 
   while ( mallocCount < num )   {

        randNum = (rand() % (2) ); 
        randNum2 = (rand() % (74)) + 1; 

        if ( randNum )  {

            vari = (int*) malloc(randNum2 * sizeof(int)); 

            if ( vari != NULL ) {
                store_Malloc[mallocCount] = vari; 
                mallocCount++; 
            }  

        }  
   }

   while ( freeCount < num ) {

         randNum = (rand() % (2) ); 
        
        if ( randNum )  {
            free(store_Malloc[freeCount]); 
        }   else { // Double free test 
            free(store_Malloc[freeCount]); 
            free(store_Malloc[freeCount]); 
        }
        
        freeCount++; 
        
   }

      gettimeofday(&t1, NULL);

    return (double)(t1.tv_sec-t0.tv_sec) + ((t1.tv_usec-t0.tv_usec) / (double)1000000);
    
}


double testF()  {

    srand(time(NULL)); 
    struct timeval t0; 
    struct timeval t1; 

     gettimeofday(&t0, NULL);

        int* vari; 
        int* two; 
        int* sum; 

        long* variTwo; 
        long* add; 
        long* l_sum; 

        short* variThree; 
        short* subtract; 
        short* s_sum; 

        char* string; 

        int p = 0; 

        vari = (int*) malloc(1 * sizeof(int)); // A regular int, 4 bytes
        two = (int*) malloc(1 * sizeof(int)); // A regular int, 4 bytes
        sum = (int*) malloc(1 * sizeof(int)); // A regular int, 4 bytes

        // Adding two ints. Dereference to give value 
        *vari = 4; 
        *two = 3; 
        
        *sum = *vari + *two; // gives the sum correctly. Can use the malloced pointer

        //printf("What is sum?%d\n", *sum); 
        

        variTwo = (long*) malloc(1 * sizeof(long)); // Malloc a long, 8 bytes
        add = (long*) malloc(1 * sizeof(long)); // Malloc a long, 8 bytes
        l_sum = (long*) malloc(1 * sizeof(long)); // Malloc a long, 8 bytes

        *variTwo = 5555555555; 
        *add = 1111111111; 

        *l_sum = *variTwo + *add; 
        //printf("%ld\n", *l_sum); 
            

          variThree = (short*) malloc(1 * sizeof(short));  // Malloc a short, 2 bytes 
          subtract = (short*) malloc(1 * sizeof(short));  // Malloc a short, 2 bytes 
          s_sum = (short*) malloc(1 * sizeof(short));  // Malloc a short, 2 bytes 

          *variThree = 30000; 
          *subtract = 29000; 

          *s_sum = *variThree - *subtract; 

        //  printf("%d\n", *s_sum); 

          
          string = (char*) malloc(5 * sizeof(char)); // Mallocs a string for 5 chars 

        


            for(p = 0; p < 5; p++)  {
                string[p] = 'h'; 
            } 

            string[p] = '\0'; 

           // printf("%s\n", string); 


        free(vari); 
        free(variTwo); 
        free(variThree); 
        free(string); 
        

      gettimeofday(&t1, NULL);

   return (double)(t1.tv_sec-t0.tv_sec) + ((t1.tv_usec-t0.tv_usec) / (double)1000000);
}
/*double testF(){

    srand(time(NULL)); 
    struct timeval t0; 
    struct timeval t1; 

   
    int randNum = 0;

    int mallocCount = 0; 

    int* vari; 

    gettimeofday(&t0, NULL);

    while ( mallocCount < 50 )  {

        randNum = (rand() % (2) );  
        printf("What is randnum? %d\n", randNum); 

        vari = (int*) malloc(1 * sizeof(int)); 
        int p; 

        free(vari); 
        
        if ( randNum )  { // Handle freeing non-pointer
            free(p); 
        }

        mallocCount++; 
    }

    // Test malloc for saturation of memory 
    vari = (int*) malloc(1249 * sizeof(int));  // 4 bytes x 1235 = 4996
    vari = (int*) malloc(1 * sizeof(int)); // Allocating 4 bytes will lead to oversaturation 

    free(vari); 

    gettimeofday(&t1, NULL);

    return (double)(t1.tv_sec-t0.tv_sec) + ((t1.tv_usec-t0.tv_usec) / (double)1000000);
}  */
