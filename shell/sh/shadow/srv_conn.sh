#!/usr/sbin/bash

# example how to connect #
ssh $(whoami)@192.168.0.2 -L4444:127.0.0.1:4444
ssh $(whoami)@192.168.0.2 -L7657:127.0.0.1:7657
