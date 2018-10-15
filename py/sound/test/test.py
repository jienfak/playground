#!/usr/bin/python3

import numpy   as np
import pyaudio as pa
import pygame

SAMPLE_RATE = 44100
S_16BIT     = 2**16

def generate_sample(freq, duration, volume):
    # Amplitude.
    amplitude = np.round(SAMPLE_RATE * volume)
    # Longness.
    total_samples = np.round(SAMPLE_RATE * duration)
    # Discretisation duration.
    w = 2.0 * np.pi * freq / SAMPLE_RATE

    k = np.arange(0, total_samples)
    return np.round(ampitude * np.sin(k*w))

freq_array = np.array([261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88])

def generate_tones(duration):
    tones = []
    for freq in freq_array:
        tone = np.array(generate_sample(freq, duration, 1.0), dtype=np.int16)
        tones.append(tone)
    return tones

# 
key_names = ['a', 's', 'd', 'f', 'g', 'h', 'j']
# 
key_list = list(map(lambda x: ord(x), key_names))
# 
key_dict = dict([(key, False) for key in key_list])

if __name__ == '__main__':
    # 
    p = pa.PyAudio()
    stream = p.open(format=p.get_format_from_width(width=2),
                    channels=2, rate=SAMPLE_RATE, output=True)
    window_size = 320, 240
    screen = pygame.display.set_mode(window_size)
    pygame.display.flip()
    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            if event.type == pygame.KEYDOWN:
                if event.key == ord('q'):
                    running = False
                for (index, key) in enumerate(key_list):
                    if event.key == key:
                        key_dict[key] = True
            if event.type == pygame.KEYUP:
                for (index, key) in enumerate(key_list):
                    if event.key == key:
                        key_dict[key] = False
        for (index, key) in enumerate(key_list):
            if key_dict[key] == True:
                stream.write(tones[index])
    pygame.quit()
    stream.stop_stream()
    stream.close()
    p.terminate()


