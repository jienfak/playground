// main class
public class Interface {
	public static void main(String args[]){
		Book b = new Book ("You suck!", "Samuel Johnson") ;
		b.print();

		Journal j = new Journal ("Jour") ;
		j.print();

		Undef un = new Undef () ;
		un.print();
	}
}

//Interface to realize
interface Printable {
	// Method of interface which is needed to realize
	// default takes if methos is not defined
	default void print(){
		System.out.println("Undefined printable(Default method)");
	}
}

// Class realising an interface(by implementing)
class Book implements Printable {
	String name;
	String author;

	Book(String name, String author){
		this.name = name ;
		this.author = author ;
	}

	public void print(){
		System.out.printf("%s (%s)\n", name, author);
	}
}

//This does it too
class Journal implements Printable {
	private String name;
	String getName(){
		return name ;
	}

	Journal(String name){
		this.name = name ;
	}

	public void print(){
		System.out.println(name);
	}

}

class Undef implements Printable {
	//void
	//it means here will be default method 'print'
}
