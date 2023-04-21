#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

unsigned long long mod (long long x,long long y){
  if(x < y){
    return x;
  }else{
  return x - (long long)floor((x / y)*y);
  }
}

void printProgress(long long progress, long long totalSteps) {
  static long long last_percentage = -1;
  static char progressBar[51] = "==================================================";
  const long long barWidth = 50;

  long long int_percentage = (100 * progress) / totalSteps;

  if (int_percentage == last_percentage) {
    return;
  }

  long long progressWidth = (barWidth * progress) / totalSteps;

  if (last_percentage >= 0) {
    progressBar[(barWidth * last_percentage) / 100] = '=';
  }

  if (progressWidth < barWidth) {
    progressBar[progressWidth] = '#';
  }

  printf("\r[%s] %3lld%%: %lld out of %lld", progressBar, int_percentage, progress, totalSteps);
  fflush(stdout);

  last_percentage = int_percentage;
}


bool *getPrimes(long long  limit, long long  *primeCount) {
  // Initialize a BitSet with size limit + 1
  bool *sieve = (bool *)calloc(limit + 1, sizeof(bool));
  sieve[2] = true;
  sieve[3] = true;

  // Calculate the square root of the limit
  long long  sqrtLimit = (long long )sqrt(limit);

  // Loop through all possible values
  for (long long  x = 1; x <= sqrtLimit; x++) {
    printProgress(x, sqrtLimit);
    for (long long  y = 1; y <= sqrtLimit; y++) {
      long long n;

      // Calculate n using first equation
      n = (4 * x * x) + (y * y);
      if (n <= limit && (n % 12 == 1 || n % 12 == 5)) {
        sieve[n] = !sieve[n];
      }

      // Calculate n using second equation
      n = (3 * x * x) + (y * y);
      if (n <= limit && n % 12 == 7) {
        sieve[n] = !sieve[n];
      }

      // Calculate n using third equation
      n = (3 * x * x) - (y * y);
      if (x > y && n <= limit && n % 12 == 11) {
        sieve[n] = !sieve[n];
      }
    }
  }

  // Sieve out the square of prime numbers' multiples
  for (long long  n = 5; n <= sqrtLimit; n++) {
    if (sieve[n]) {
      long long squareN = n * n;
      for (long long k = squareN; k <= limit; k += squareN) {
        sieve[k] = false;
      }
    }
  }

  long long  count = 0;
    for (long long  i = 0; i <= limit; i++) {
      if (sieve[i]) {
        count++;
      }
    }

  *primeCount = count;
  return sieve;
}

int main() {
  long long  limit = 1000000000UL;
  long long  primeCount = 0;
  bool *primes = getPrimes(limit, &primeCount);

  printf("\nNumber of primes up to %lld: %lld\n", limit, primeCount);

  printf("\r");
  for (long long  i = 0; i < 100; i++) {
      printf(" ");
  }
  printf("\r");
  char answer[100];
  printf("\nDo you wish to print the found primes? ");
  fgets(answer,100, stdin);
  long long  j = 0;
  if (answer[0] == 'y' || answer[0] == 'Y') {
    for (long long  i = 0; i <= limit; i++) {
      if (primes[i]) {
        printf("%lld,", i);
        j++;
        if (mod(j, 10) == 0) {
          printf("\n");
        }
      }
    }
  }
  printf("\nNumber of primes up to %lld: %lld\n", limit, primeCount);

  free(primes);
  return 0;
}