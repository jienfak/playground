#include <iostream>

using namespace std;

class Shape{
	public:
		virtual int getArea() = 0;

		void setWidth(int w){
			width = w ;
		}

		void setHeight(int h){
			height = h ;
		}

	protected:
		int width;
		int height;
};

class Rectangle : public Shape{
	public:
		int getArea(){
			return (width*height) ; 
		}
};

class Triangle : public Shape{
	public:
		int  getArea(){
			return (width*height)/2 ;
		}
};

int main(void){
	Triangle t = Triangle () ;
	t.setWidth(4); t.setHeight(4);
	cout <<"S(t) = "<< t.getArea() << endl;

	Rectangle r = Rectangle() ;
	r.setWidth(4); r.setHeight(4);
	cout <<"S(r) = "<< r.getArea() << endl;


	// succesful exit
	return 0;
}
