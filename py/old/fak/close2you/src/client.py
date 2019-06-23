import socket
import threading
import time

class Client:
    _parse_char = "~"
    _prefixes = {
            'message': '@',
            'join': '!',
            'exit': '#'
    }
    
    def __init__(self, name='user', port=11719):
        self.name = name;
        self.port = port
        #main sending socket binding
        self._ssock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self._ssock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

        #main listenning socket binding
        self._lsock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self._lsock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self._lsock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        self._lsock.bind( ('0.0.0.0',port) )

    #function sending to all Clients around
    def _send(self, prefix, nick, msg):
        self._ssock.sendto( (prefix+'~'+nick+'~'+msg).encode(), ("255.255.255.255", self.port) )

    def join(self):
        self._send( Client._prefixes['join'], self.name, '' )

    def exit(self):
        self._send( Client._prefixes['exit'], self.name, '' )

    def send_msg(self, msg):
        self._send( Client._prefixes['message'], self.name, msg)

    def _prompt(self):
        print('\n'+self.name+'>', end='')

    def _parseMsg(msg):
        return tuple( msg.split(Client._parse_char) )

    def startListening(self):
        #daemon, getting a messages from other peers
        listening = threading.Thread(target=self._listeningDaemon, args=())
        listening.daemon = True
        listening.start()

    #daemon thread getting messages from Clients around
    def _listeningDaemon(self):
        while True:
            msg = self._lsock.recv(1024).decode()
            prefix, nick, data = Client._parseMsg(msg)

            if nick!=self.name:
                print("["+time.ctime()+"]", end="")
                if prefix == Client._prefixes['message']:#default message
                    print('\r'+ nick+'>'+data) 

                elif prefix == Client._prefixes['join']:
                    print('\r'+nick+' has joined chat')

                elif prefix == Client._prefixes['exit']:
                    print('\r'+nick+' has left chat')

                else:
                    print('\nclose2you\t:got unright message')

                self._prompt()

