package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main(){
	rand.Seed(time.Now().UnixNano())
	fmt.Println(string(rand.Intn(100)))
}
