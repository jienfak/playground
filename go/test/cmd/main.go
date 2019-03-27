
package main

import (
	"fmt"
	"os"
	"strconv"
)

func main(){
	for i:=0 ; i<len(os.Args) ; i++ {
		fmt.Println("os.Args["+strconv.Itoa(i)+"] = \""+os.Args[i]+"\"")
	}
}
