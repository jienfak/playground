#!/usr/bin/node

const {exec} = require("child_process");

exec( "echo 'hello'", (err, stdout, stderr) => {
	if(err){
		return;
	}

	console.log(`stdout: ${stdout}`);
	console.log(`stderr: ${stderr}`);
});
