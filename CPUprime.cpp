#include <iostream>
#include <random>
#include <chrono>
#include <cmath>
#include <vector>

using namespace std;

bool run(int num, int len);
bool read(int num, bool list []);
bool write(int num, bool list [], int len);
int terminal(int point, int end, int length);



int simple(){
  using namespace std::chrono;
  milliseconds t = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
  int amount = 0;
  int terminalLength = 100;
  int currentTerm = -1;
  int length = 20000;
  bool primes [20000];
  int i = 2;

  while(run(i,length)){
    if(read(i,primes)){
      i+=2;
      continue;
    }
    for (int j = i; j < length; j++){
      if(!write(i*j,primes,length)){break;}
    }
    i += 2;
    if(i == 4) {i--;}
    amount++;
    currentTerm = terminal((int)(((float)i)/(float)length*(float)terminalLength), 100, currentTerm);
  }
  cout << "\n";
  cout << amount;
  cout << "\n";
  cout << duration_cast< milliseconds >(system_clock::now().time_since_epoch()).count() - t.count();
  cout << "\n\n";
  return amount;
}
bool run(int num, int len){
  return (num+2 < len && num+2 >= 0);
}
bool read(int num, bool list []){
  return list[num-2];
}
bool write(int num, bool list [], int len){
  if(num - 2 < len && num-2 > 0){
    list[num-2] = false;
    return true;
  }
  return false;
}
int terminal(int point, int end, int length){
  if(point == length){
    return point;
  }
  string out = "<";
  for (int i = 0; i < end; i++)
  {
    out += "-";
  }
  for (int i = 0; i < point; i++) {
    out[i+1] = '=';
  }
  cout << (out + ">\r");
  return point;
}

// Function to perform modular exponentiation
// base: base number, exp: exponent, mod: modulus
int mod_exp(int base, int exp, int mod) {
  int result = 1;
  base %= mod;

  // Repeated squarring method for modular exponentiation
  while (exp > 0) {
    // If the exponent is odd, multiply the results by the current base
    if (exp & 1)
      result = (result * base) % mod;
    // Square the base
    base = (base * base) % mod;
    // Divide the exponent by two (right shift by 1)
    exp >>= 1;
  }
  return result;
}

// Function to perform the Miller-Rabin test for a single iteration
// n: number to test for primality, a: random witness
bool miller_rabin_test(int n, int a) {
  // Find d and s such that n-1 = d * 2^s
  int d = n-1;
  int s = 0;
  
  while (d % 2 == 0) {
    d /= 2;
    s++;
  }

  // Compute x = a^d % n using modular exponentiation
  int x = mod_exp(a,d,n);

  // If x is 1 or n-1, n is likely prime
  if (x == 1 || x == n-1)
    return true;
  
  // Iterate through the remaining powers of 2
  for (int r = 1; r < s; r++) {
    x = (x * x) % n;
    if (x == n - 1)
      return true;
  }
  // If none of the above conditions hold, n is composite
  return false;
}

bool is_prime(int n, int k = 5) {
  // Handle cases of small n
  if (n <= 1 || n == 4)
    return false;
  if (n <= 3 || n == 2)
    return true;
  
  // Set up a random number generator for witnesses
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dis(2, n - 2);

  // Perform k itterations of the Miller-Rabin test
  for (int i = 0; i < k; i++) {
    // Generate a random witness
    int a = dis(gen);
    
    // If the test fails for this witness, n is composite
    if (!miller_rabin_test(n, a))
      return false;
  }
  return true;
}

// Function to calculate the greatest common divisor (GCD) of two numbers
int gcd(int a, int b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

int complex(int length = 20000){
  using namespace std::chrono;
  int termLength = 50;
  milliseconds t = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
  int count = 0;
  int len = -1;
  for (int i = 1; i <= length; i++) {
    // Do a full Miller-Rabin test of all numbers up to length
    if (is_prime(i, 5))
      count++;
      // len = terminal((float)i/(float)length*termLength, termLength, len);
  }
  cout << duration_cast< milliseconds >(system_clock::now().time_since_epoch()).count() - t.count();
  cout << "\nMiller-Rabin test found " << count << " primes";
  return count;
}

int main(){
  // int simpelOut = simple();
  
  int complexOut = complex(10000000);
  return 0;
}