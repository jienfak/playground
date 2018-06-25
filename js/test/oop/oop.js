#!/usr/bin/node

// Example of inheritance
var animal_proto = {
	eats: true
};

var human_proto = {
	is_stupid: true,
	name: "Samuel",
	say: function(string){
		console.log(this.name + ": " + string);
	},
	toString: function(){
		return this.name ;
	},
	String: this.toString
}

//Inheritance
Human.__proto__ = animal_proto ;

console.log("animal_proto.eats = " + animal_proto.eats);
console.log("animal_proto.is_stupid = " + animal_proto.is_stupid);

console.log("human_proto.eats = " + human_proto.eats);
console.log("human_proto.is_stupid = "+human_proto.is_stupid);

// we can use this to make classe just like this
function Human (name, is_stupid) {
	this.__proto__ = human_proto ; // default values of constructor

	//getting of propery by arguments
	this.name = name ;
	this.is_stupid = is_stupid ; 
}

// getting new object of class 'Human'
var samuel = new Human ('samuel', false) ;
samuel.say("You suck!");
console.log(samuel);
