//-----------------------------------------------------------------------------
// HashTest.c
// Demonstrate functions rotate_left(), pre_hash(), hash() and showBits()
//
//      compile:  gcc -o HashTest HashTest.c
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 180

const int tableSize = 101;

// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) {
   int sizeInBits = 8*sizeof(unsigned int);
   shift = shift & (sizeInBits - 1);
   if ( shift == 0 )
      return value;
   return (value << shift) | (value >> (sizeInBits - shift));
}

// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char* input) { 
   unsigned int result = 0xBAE86554;
   while (*input) { 
      result ^= *input++;
      result = rotate_left(result, 5);
   }
   return result;
}

// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char* key){
   return pre_hash(key)%tableSize;
}

// showBits()
// print out the bits in an unsigned int
void showBits(unsigned int x) {
   int i;
   int sizeInBits = 8*sizeof(unsigned int);
   char symbol[2] = {'0','1'};
   char* binary = malloc(sizeInBits + 1);

   memset(binary, 0, sizeInBits + 1);

   for (i=0; i<sizeInBits; i++) {
       binary[sizeInBits-i-1] = symbol[(x>>i) & 0x01];
   }
   
   printf("%s\n", binary);
   free(binary);
}

int main(void){
   FILE* in = fopen("hashTestInput", "r");
   FILE* out = fopen("hashTestStats", "w");
   char line[MAX_LEN];
   int frequency[tableSize];
   int i, lineCount=0;
   double min, max, relfreq;

   for(i=0; i<tableSize; i++){
      frequency[i] = 0;
   }

   while( fgets(line, MAX_LEN, in)!=NULL ){
      lineCount++;
      frequency[hash(line)]++;
   }

   min = max = 100*frequency[0]/(double)lineCount;
   for(i=0; i<tableSize; i++){
      relfreq = 100*frequency[i]/(double)lineCount;
      fprintf(out, "%d: %.2f\n", i, relfreq);
      min = (relfreq<min)?relfreq:min;
      max = (relfreq>max)?relfreq:max;
   }
   fprintf(out, "\nrange: %.2f - %.2f\n", min, max);

   printf("\nNumber of bytes in unsigned int = %d\n", sizeof(unsigned int));
   showBits(0xBAE86554);
   showBits(rotate_left(0xBAE86554, 5));
   showBits(0xBAE86554 << 5);
   showBits(0xBAE86554 >> (8*sizeof(unsigned int) - 5) );
   showBits( (0xBAE86554 << 5) | (0xBAE86554 >> (8*sizeof(unsigned int) - 5) ) );

   return 0;
}