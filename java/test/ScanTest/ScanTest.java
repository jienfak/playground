import java.util.Scanner ;

public class ScanTest{
	public static void main(String args[]){
		Scanner stdin = new Scanner (System.in) ;
		String value;
		while(true){
			value = stdin.nextLine() ;
			System.out.println("You entered '"+value+"'");
		}
	}
}
