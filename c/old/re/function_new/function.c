int f(int a, int b){
	int x = 0 ;
	for(int i=a; i<=b ; ++i){ x += i ; }
	return x ; 
}

int main(void){
	f(1, 2);
	return 0 ;
}
