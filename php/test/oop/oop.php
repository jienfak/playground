<?php

class Human {
	public $fullname;
	private $nickname;
	protected $nick;

	function say(string $phrase){
		echo $this->$fullname.": ".$phrase;
	}

	function __construct(string $name){
		$this->$fullname = $name ;
	}
};

$proto = new Human ('Samuel') ;
$proto->say('fuck you!');

?>
