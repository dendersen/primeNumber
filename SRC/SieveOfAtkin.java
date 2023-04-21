import java.util.BitSet;
import java.util.Scanner;
/**
 * SieveOfAtkin
 */
public class SieveOfAtkin {
  public static void main(String[] args) {
    int limit = Integer.MAX_VALUE-2;
    long t = java.lang.System.currentTimeMillis();
    int[] primes = getPrimes(limit);
    int primeCount = primes.length;
    System.out.println("Number of primes up to " + limit + ": " + primeCount);
    System.out.println("time: " + (java.lang.System.currentTimeMillis()-t) + " mills");
    System.out.println("\ndo you wish to print the found primes?");
    Scanner scan = new Scanner(System.in);
    if(scan.nextLine().toLowerCase().contains("y"))
       for (int prime : primes) {
        System.out.print(prime + " ");
       }
    scan.close();
  }

  public static int[] getPrimes(int limit) {
    // Initialize a BitSet with size limit + 1
    BitSet sieve = new BitSet(limit + 1);
    sieve.set(2, true);
    sieve.set(3, true);

    // Calculate the square root of the limit
    int sqrtLimit = (int) Math.sqrt(limit);

    // Loop through all possible values
    for (int x = 1; x <= sqrtLimit; x++) {
      for (int y = 1; y <= sqrtLimit; y++) {
        long n;

        // Calculate n using first equation
        n = (4 * x * x) + (y * y);
        if (n <= limit && (n % 12 == 1 || n % 12 == 5)) {
          sieve.flip((int) n);
        }

        // Calculate n using second equation
        n = (3 * x * x) + (y * y);
        if (n <= limit && n % 12 == 7) {
          sieve.flip((int) n);
        }

        // Calculate n using third equation
        n = (3 * x * x) - (y * y);
        if (x > y && n <= limit && n % 12 == 11) {
          sieve.flip((int) n);
        }
      }
    }

    // Sieve out the square of prime numbers' multiples
    for (int n = 5; n <= sqrtLimit; n++) {
      if (sieve.get(n)) {
        long squareN = n * n;
        for (long k = squareN; k <= limit; k += squareN) {
          sieve.set((int) k, false);
        }
      }
    }

    // Collect prime numbers from the BitSet
    int[] primes = sieve.stream().toArray();
    return primes;
  } 
}