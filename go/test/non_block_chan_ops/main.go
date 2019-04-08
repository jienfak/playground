package main

import "fmt"

func main(){
	msgs := make(chan string)
	signals := make(chan bool)

	select{
		case msg := <-msgs :
			fmt.Println("Received message: ", msg)
		default:
			fmt.Println("No message received.")
	}

	msg := "hi"
	select{
		case msgs <- msg :
			fmt.Println("Sent message: ", msg)
		default:
			fmt.Println("No message sent.")
	}

	select{
		case msg := <-msgs :
			fmt.Println("Received message: ", msg)
		case sig := <-signals :
			fmt.Println("Received signal: ", sig)
		default:
			fmt.Println("No activity.")
	}
}
