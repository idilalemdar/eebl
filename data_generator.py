#!/usr/bin/env python3

'''
Emergency brake after t = 5 s
'''
fd = open("brake_positions_1.txt", "w")

for i in range(1,51):
    fd.write("0\n")

for i in range(1,11): # brake position line's slope = 45 degrees
    fd.write(str(0.1 * i) + "\n")

for i in range(1,21):
    fd.write("1\n")

fd.close()


'''
Normal brake
'''
fd = open("brake_positions_2.txt", "w")

for i in range(1,51):
    fd.write("0\n")

for i in range(1,31): # brake position line's slope = 30 degrees
    if 1/15 * i < 0.5:
        fd.write(str(1/15 * i) + "\n")
    else:
        fd.write("0.5\n")

fd.close()

'''
Nonlinear emercengy brake curve, application takes the best fit
'''
fd = open("brake_positions_3.txt", "w")

for i in range(1,51):
    fd.write("0\n")

for i in range(1,41): # brake position line's slope = 30 degrees
    if 0.1 * i**2 < 1:
        fd.write(str(0.1 * i**2) + "\n")
    else:
        fd.write("1\n")

fd.close()