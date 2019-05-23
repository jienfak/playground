#!/usr/bin/env python3

import pygame
from pygame.locals import *

x_speed = 5
y_speed = 5


player_pos = {'x':100, 'y':100}
keys_list = ["w", "a", "s", "d"]
keys = {}
# Reset keys.
for key in keys_list :
	keys[key] = False


def set_keys(keys, event):
	# Sets keys if they are up or down now.
	if event.type == pygame.KEYDOWN :
		for key in keys_list :
			if event.key==eval("pygame.K_"+key) :
				keys[key] = True
	if event.type == pygame.KEYUP :
		for key in keys_list :
			if event.key==eval("pygame.K_"+key) :
				keys[key] = False

pygame.init()
width, height = 640, 480

screen = pygame.display.set_mode((width, height))

player = pygame.image.load("../resources/images/dude.png")
grass  = pygame.image.load("../resources/images/grass.png")
castle = pygame.image.load("../resources/images/castle.png")

while True :
	# Check for events.
	for event in pygame.event.get() :
		if event.type == pygame.QUIT :
			pygame.quit()
			exit()

	set_keys(keys, event)

	# Move player.
	if keys["w"] :
		player_pos['y'] += y_speed
	elif keys["s"] :
		player_pos['y'] -= y_speed
	if keys["a"] :
		player_pos['x'] -= x_speed
	elif keys["d"] :
		player_pos['x'] += x_speed

	

	# Fill all the screen with the black color.
	screen.fill(0)

	# Fill all the screen with grass texture.
	for x in range(width//grass.get_width()+1) :
		for y in range(height//grass.get_height()+1) :
			screen.blit(grass, (x*100, y*100))
	
	screen.blit(castle, (0, 30 ))
	screen.blit(castle, (0, 135))
	screen.blit(castle, (0, 240))
	screen.blit(castle, (0, 345))

	# Draw player.
	
	player_poss = [player_pos['x'], player_pos['y']]
	screen.blit(player, player_poss)
	pygame.display.flip()
