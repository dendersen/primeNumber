import java.util.Scanner;

/**
 * main
 */
public class Exlude {
  public static int max;
  static int data = 32;
  // static int[] primes = new int[Integer.MAX_VALUE-2]; //highest possible
  static int[] primes;
  static int amount = 0;
  static int terminalLength = 100;
  static int currentTerm = -1;
  static long counter = 0;
  static String cur = "";

  public static void main(String[] args) {
    
    System.in.mark(terminalLength);
    Scanner scan = new Scanner(System.in);
    System.out.println("\nhow far do you wish to search");
    while(true){
      String number = scan.nextLine();
      try{
        max = Integer.parseInt(number);
        primes = new int[Math.min((int)Math.ceil((float)max/(float)data),Integer.MAX_VALUE-2)];
        break;
      }catch(Exception clear){}
    }
    
    System.out.print("preparing    \r");
    for (int i = 0; i < primes.length; i++) {
      primes[i] = 0xffffffff;
    }
    primes[0] = (0b11101100 | 0xffffff00);
    long t = java.lang.System.currentTimeMillis();
    long i = 2;
    System.out.print("running    \r");
    while (run(i)){
      if(!read(i)){
        i++;
        continue;
      }

      long j = i;
      while(write(i * j)){
        j++;
      }
      
      terminal((int)(((float)i)/((float)primes.length*(float)data)*(float)terminalLength), terminalLength, currentTerm,""+(data*primes.length-counter));
      // System.out.print(i + "\r");
      i++;
      amount++;
    }
    System.out.println("\nnumber of primes: " + amount + " up to: " + (data*primes.length));
    System.out.println("time: " + (java.lang.System.currentTimeMillis()-t) + " mills");
    
    System.out.println("\ndo you wish to print the found primes?");
    if(scan.nextLine().toLowerCase().contains("y"))
      printPrimes();
    scan.close();
    return;
  }
  public static boolean read(long num){
    return ((primes[(int)((num-num%data)/data)] >> (num%data)) & 1) == 1;
  }
  public static boolean write(long num){
    if(num < primes.length * data && num > 0){
      if(read(num)){
        counter++;
      }
      primes[(int)((num-num%data)/data)] &= ~(1<<(num%data));
      return true;
    }
    return false;
  }
  public static boolean run(long num){
    return num < primes.length*data; 
  }
  public static void terminal(int point, int end, int length, String info){
    if(point == length){
      System.out.print(("\033[" + (end+2) + "C"));
      System.out.print(cur + " " + info + "\r");
      return;
    }
    String out = "<";
    out += "-".repeat(end-1) + ">";
    char[] temp = out.toCharArray();
    for (int i = 0; i < point; i++) {
      temp[i+1] = '=';
    }
    out = new String(temp);
    System.out.print(out + " " + info + "        \r");
    cur = out;
    currentTerm = point;
  }
  public static void printPrimes(){
    int count = 0; 
    for (int i = 0; i < primes.length*data; i++) {
      // System.out.println((int)primes[i]);
      if(read(i)){
        if(count < 10){
          System.out.print(i + ",");
          count++;
        }else{
          System.out.print(i + ",");
          count = 0;
        }
      }
    }
  }
}