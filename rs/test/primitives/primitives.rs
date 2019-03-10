fn main(){
	// let var_name: type = value ;
	let logical: bool = true ;
	
	let a_float: f64  = 1.0 ;  // Regular annotation. (64-bit float)
	let an_integet    = 5i32 ; // Suffix annotation.  (32-bit integer)
	
	// Or a default will be used.
	let default_float   = 3.0 ; // `f64` .
	let default_integer = 7 ;   // `i32` .
	
	// A type can also be inferred from context.
	let mut inferred_type = 12 ;          // Type `i64` is inferred from another line.
	inferred_type = 4294967238472384126 ; // |------^
	
	// A mutable variable's value can be changed.
	let mut mutable = 12 ;// Mutable `i32`.
	mutable = 21 ;

	// Error! The type of a variable can't be changed!
	//mutable = true ;
	
	// Variable can be overwritten with shadowing.
	let mutable = true ;
}
