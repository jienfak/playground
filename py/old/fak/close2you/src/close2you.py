
import sys 
import client

name = input('Enter your nickname:')
user = client.Client(name)
user.join()
user.startListening()

while True:
    entered = input('\n'+name+'>')

    if entered and (entered[0]=='/'):
        argv = entered[1:].split(' ')

        if argv[0] == 'exit': 
            break

    elif entered:
        user.sendMsg(entered);

user.exit()
exit()
