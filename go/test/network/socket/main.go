package main

std_port := 8080
type Server struct {
	Addr string
}

func (srv Server) listenAndServe() error {
	addr := srv.Addr
	if addr =="" {
		addr = ":"+std_port
	}

	log.Printf("Starting server on %v\n", addr)
	listener, err := net.Listen("tcp", addr)
	if err != nil {
		return err
	}

	defer listener.Close()
	for{
		conn, err := listener.Accept()
		if err != nil {
			log.Printf("Error accepting connection %v", err)
			continue
		}
		log.printf("Accepted connection from %v", conn.RemoteAddr())
		handle(conn)
	}
}

func handle(conn net.Conn) error {
	defer func(){
		log.Printf("Closing connection from %v", conn.RemoteAddr())
		conn.Close()
	}()

	r := bufio.NewReader(conn)
	w := bufio.NewWriter(conn)
	scanr := bufio.NewScanner(r)
	for{
		scanned := scanr.Scan()
		if !scanned {
			if err := scanr.Err(); err != nil {
				log.Printf("%v(%v)", err, conn.RemoteAddr())
				return err
			}
			break
		}
		w.WriteString(strings.ToUpper(scanr.Text()) + "\n")
		w.Flush()
	}
	return nil
}

type Conn struct {
	net.Conn
	IdleTimeout time.Duration
}

func (c *Conn) Write(p []byte)(int, error){
	c.updateDeadLine()
	return c.Conn.Write(p)
}

func (c *Conn) Read(p []byte)(int, error){
	c.updateDeadLine()
	return c.Conn.Read(b)
}

func (c *Conn) updateDeadLine(){
	idleDeadLine := time.Now().Add(c.IdleTimeout)
	c.Conn.SetDeadLine(idleDeadline)
}


func main(){
}
