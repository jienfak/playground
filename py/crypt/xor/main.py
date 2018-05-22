#!/usr/bin/python3

def crypt_xor(word, key):
    string = ''
    for charw in word:
        charbuff = charw
        for chark in key:
            charbuff = chr(ord(charbuff)^ord(chark))
        string += charbuff
    return string;

def uncrypt_xor(crypt, key):
    string = ''
    for charc in crypt:
        charbuff = charc
        for chark in reversed(key):
            charbuff = chr(ord(charbuff)^ord(chark))
        string +=charbuff
    return string

cry = crypt_xor('word', 'key')
print('"'+cry+'"')
uncry = uncrypt_xor(cry, 'key')
print('"'+uncry+'"')

