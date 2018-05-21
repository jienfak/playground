#!/usr/bin/node

var Person = function (name){
	/* -------------------------- */
	this.name = name;
	console.log("Object 'Person' with name '"+this.name+"' was created.");

	this.say = function(string){
		console.log(this.name+": "+string);
	}
}


var pers1 = new Person("sucker");
pers1.say("You will die");

