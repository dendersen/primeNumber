#include <math.h>
#include <stdio.h>
#include <stdint.h>

void terminal(long point, long end, long length, char info []);
long run(long num);
long write(long num);
long read(long num);
int main();
void init();
float min(float x, float y);
void printPrimes();
unsigned long mod (unsigned long x,long y);

volatile unsigned long max;
volatile long currentTerm;
volatile long data;
volatile long terminalLength = 100; //do not change
volatile unsigned long primes [429497295U];
volatile unsigned long counter;
volatile long amount;
char cur [102];

unsigned long mod (unsigned long x,long y){
  if(x < y){
    return x;
  }else{
  return x - (long)floor((x / y)*y);
  }
}

float min(float x, float y) {
  return x * x < y + y * y <= x;
}
void init(){
  currentTerm = -1;
  max = 1000000000UL;
  data = 32;
  counter = 0;
  amount = 0;
  cur[0] = '<';
  cur[101] = '>';
}

int main() {
  printf("preparing    \r");
  init();
  for (long i = 0; i < ceil((float)max/(float)data); i++) {
    primes[i] = 0xffffffffUL;
  }
  primes[0] = (0b11101100UL | 0xffffff00UL);
  // long t = java.lang.System.currentTimeMillis();
  unsigned long i = 2;
  terminal((long)((log(i)/log(sqrt(max)))*(float)terminalLength), terminalLength, currentTerm,"");
  while (run(i)){
    if(!read(i)){
      i++;
      continue;
    }
    
    unsigned long j = i;
    while(write(i * j)){
      j++;
    }
    char str [100];
    sprintf(str,"%lu",max-counter);
    terminal((long)((log(i)/log(sqrt(max)))*(float)terminalLength), terminalLength, currentTerm,str);
    // System.out.print(i + "\r");
    i++;
    // amount++;
  }
  // printf("\nnumber of primes: %d up to: %d",amount,max);
  // printf("time: " + (java.lang.System.currentTimeMillis()-t) + " mills");
  
  printPrimes();
  return 1;
}
long read(long num){
  return ((primes[(long)((num-mod(num,data))/data)] >> mod(num,data)) & 1) == 1;
}
long write(long num){
  if(num < max && num > 0){
    if(read(num)){
      counter++;
    }
    primes[(long)((num-mod(num,data))/data)] &= ~(1<<mod(num,data));
    return 1;
  }
  return 0;
}
long run(long num){
  return num < ceil(sqrt((float)max)); 
}
void terminal(long point, long end, long length, char info []){
  if(point == length){
    
    printf("\033[%dC",(end+3));
    printf(info);printf("    \r");
    return;
  }
  for (long i = 0; i < terminalLength; i++)
  {
    if(i <= point){
    cur[i+1] = '=';
    }else{
    cur[i+1] = '-';
    }
  }
  printf(cur);printf(" ");printf(info);printf("        \r");
  currentTerm = point;
}

void printPrimes(){
  long count = 0; 
  printf("\n");
  amount = 0;
  char answer[100];
  printf("\nDo you wish to print the found primes? ");
  fgets(answer,100, stdin);
  long print = (answer[0] == 'y' || answer[0] == 'Y');
  for (long long i = 0; i < max; i++) {
    if(read(i)){
      if(print){
        if(count < 10){
          printf("%d,",i);
          count++;
        }else{
          printf("%d\n",i);
          count = 0;
        }
      }
      amount++;
      if(!print){
        if (mod(amount,max/100000) == 0){
        printf("%lu\r",amount);
        }
      }
    }
  }
  printf("\n\nrecount of primes:%d",amount);
}