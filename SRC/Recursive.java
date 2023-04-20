import java.util.ArrayList;
import java.util.Scanner;

public class Recursive {
  public static int max;
  static int data = 32;
  static int[] notPrimes;
  static ArrayList<Long> primes = new ArrayList<Long>();
  static int amount = 0;
  static int terminalLength = 10;
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
        notPrimes = new int[Math.min((int)Math.ceil((float)max/(float)data),Integer.MAX_VALUE-2)];
        break;
      }catch(Exception clear){}
    }
    
    System.out.print("preparing    \r");
    for (int i = 0; i < notPrimes.length; i++) {
      notPrimes[i] = 0xffffffff;
    }
    notPrimes[0] = (0b11001100 | 0xffffff00);
    primes.add((long)2);
    primes.add((long)3);
    calc(2, 0,false);
    long t = java.lang.System.currentTimeMillis();
    amount = 2;
    long i = 3;
    System.out.print("running    \r");
    while (run(i)){
      if(!read(i)){
        i++;
        continue;
      }
      primes.add(i);
      calc(i,primes.size()-1,false);
      
      terminal((int)(((float)i)/((float)notPrimes.length*(float)data)*(float)terminalLength), terminalLength, currentTerm,""+i);
      // System.out.print(i + "\r");
      i++;
      amount++;
    }
    System.out.println("\nnumber of primes: " + amount + " up to: " + (data*notPrimes.length));
    System.out.println("time: " + (java.lang.System.currentTimeMillis()-t) + " mills");
    
    System.out.println("\ndo you wish to print the found primes?");
    if(scan.nextLine().toLowerCase().contains("y"))
      printPrimes();
    scan.close();
    return;
  }
  private static void calc(long i,int index, boolean isSkip) {
    long temp = i*primes.get(index);
    if(temp >= notPrimes.length * data || temp < 0) return;
    if(index >= 1){
      calc(i, index-1,true);
      calc(temp, index-1,false);
    }
    if(write(temp))//TODO: gang alle tal mad alle andre fundne prime
    calc(temp,index, false);
  }
  public static boolean read(long num){
    if(num >= notPrimes.length * data || num < 0) return false;
    return ((notPrimes[(int)((num-num%data)/data)] >> (num%data)) & 1) == 1;
  }
  public static boolean write(long num){
    if(num < notPrimes.length * data && num > 0){
      if(read(num)){
        counter++;
      }
      notPrimes[(int)((num-num%data)/data)] &= ~(1<<(num%data));
      return true;
    }
    return false;
  }
  public static boolean run(long num){
    return num < notPrimes.length*data; 
  }
  public static void terminal(int point, int end, int length, String info){
    if(point == length){
      System.out.print(("\033[" + (end+2) + "C"));
      System.out.print("\r" + cur + " " + info + "\r");
      return;
    }
    String out = "<";
    out += "-".repeat(end-1) + ">";
    char[] temp = out.toCharArray();
    for (int i = 0; i < point; i++) {
      temp[i+1] = '=';
    }
    out = new String(temp);
    System.out.print("\r" + out + " " + info + "\r");
    cur = out;
    currentTerm = point;
  }
  public static void printPrimes(){
    int count = 0; 
    for (int i = 0; i < notPrimes.length*data; i++) {
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
