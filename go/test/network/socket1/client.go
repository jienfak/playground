
package main

import(
	"log"
	"net"
	"strconv"
	"strings"
)

const(
	msg = "Ping this shit"
	StopCharacter = "\r\n\r\n"
)

func SocketClient(ip string, port int){
	addr := strings.Join([]string{ip, strconv.Itoa(port)}, ":")
	conn, err := net.Dial("tcp", addr)

	defer conn.Close()

	if err != nil {
		log.Fatalln(err)
	}

	conn.Write([]byte(msg))
	conn.Write([]byte(StopCharacter))
	log.Printf("Send: %s", msg)

	buf := make([]byte, 1024)
	n, _:= conn.Read(buf)
	log.Printf("Receive: %s", buf[:n])
}

func main(){
	var(
		ip = "127.0.0.1"
		port = 3333
	)
	SocketClient(ip, port)
}
