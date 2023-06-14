# antennasweepauto.py
# Revised 6/13/2023
# Colton Cox - ccox60@uco.edu
# Nathan Wiley - nwiley@uco.edu



import os
import pynput
import time
import pygetwindow as gw
from pynput.mouse import Button, Controller as MouseController
from pynput.keyboard import Key, Controller as KeyboardController
import serial



delay = 0.75

startTime = time.time()
# User input to define parameters here

# Number of iterations (sweeps) to perform
default_iterations = 77
iterations = 8

# Physical rotation
motorcontrol = input("Use motor control? y/n: ")

# Time between switching RF path
switch_delay_time = 30

# Serial parameters for interfacing with antennas
COM_PORT_ANT = 'COM19' # COM port used for communicating with antennas
baudrate = 115200
timeout = 0.1
try:
	antennas = serial.Serial(port=COM_PORT_ANT, baudrate=baudrate, timeout=timeout)
except:
	print(f"Couldn't find Arduino on {COM_PORT_ANT} - Is it connected?")

# Serial parameters for interfacing with control arm
COM_PORT_ARM = 'COM17' # COM port used for communicating with control arm
baudrate = 115200
timeout = 1
try:
	arm = serial.Serial(port=COM_PORT_ARM, baudrate=baudrate, timeout=timeout)
except:
	print(f"Couldn't find Arduino on {COM_PORT_ARM} - Is it connected?")

def performTesting():
    cont = True
    while cont:
        code = input("Enter channel code to send to Arduino (q to quit): ")
        if code == "q":
            cont = False
            break
        else:
            antennas.write(bytes(str(code), 'utf-8'))
            print(f"Code: {code} sent")

if iterations == 0:
    performTesting()

mouse = MouseController()
keyboard = KeyboardController()

""" 
This bit of code opens the software in the correct position
win1 is MegiQ VNA
win2 is CONTROL 
"""

os.startfile("C:/Program Files (x86)/MegiQ/VNA/MiQVNA.exe")
time.sleep(15)
gw.getAllTitles()
gw.getAllWindows()
gw.getWindowsWithTitle('MegiQ VNA')
gw.getActiveWindow()
win = gw.getWindowsWithTitle('MegiQ VNA')[0]
win.activate()
win.moveTo(10, 10)
win.resizeTo(727, 767)

# Only opens the Control window if it is being used
if motorcontrol.lower() == 'y':
    os.startfile("C:/Users/EngineeringAdmin/AppData/Local/Programs/OpenBuildsCONTROL/OpenBuildsCONTROL.exe")
    time.sleep(3)
    gw.getWindowsWithTitle('OpenBuilds CONTROL v1.0.344 / connected to COM17')
    win2 = gw.getWindowsWithTitle('OpenBuilds CONTROL v1.0.344 / connected to COM17')[0]
    win2.activate()
    win2.moveTo(755, 0)
    win2.resizeTo(767, 767)

# Allow time for software to boot
time.sleep(3)

# Minimize the command program
mouse.position = (1254, 15)
mouse.click(Button.left, 1)



#####################################################
# Function Definitions

# Initiates sweep in MegiQ
def sweep():
    mouse.position = (514, 553)
    mouse.click(Button.left, 1)
    time.sleep(1)


# Clicks save in MegiQ
def save():
    mouse.position = (699, 558)
    mouse.click(Button.left, 1)
    time.sleep(1)


# Saves data in MegiQ - Integer parameter used for loop
def file(filename):
    filename = str(filename)  # Convert filename from int to string for keyboard input
    for f in filename:        # Splits filename into individual digits for each key press
        keyboard.tap(f)
        time.sleep(0.2)
    time.sleep(1)


def ok():
    keyboard.tap(Key.enter)


# Initiates rotation in Control
def rotate():
    mouse.position = (1320, 236)
    mouse.click(Button.left, 1)
    time.sleep(0.5)


# Sends g-code commands to the control arm
def send_gcode(gcode):
    arm.write(bytes(str(gcode + '\n'), 'utf-8'))   # Send g-code command as string
    print(f"Code: {gcode} sent")                   # Print g-code for console
    while True:
        response = arm.readline().decode().strip() # Read Arduino response
        if response == 'ok':
            break
        elif response.startswith('error'):
            raise Exception(response)
        time.sleep(0.1)                            # Wait for the Arduino to process the command


def raise_to_compressor():
    send_gcode('G90 G21 Y100 F3600') # This y value is arbitrary. Will need to change when we know the measurement
    time.sleep(3)                    # Wait for compressor to fire
    send_gcode('G90 G21 Y0 F3600')   # Return to original position


# Changes signal path on switch to param
# Writes string number to arduino, parsed to function call for RF channel select (see switch_update.ino)
def switch(rf_path):
    rf_path = str(rf_path)
    antennas.write(bytes(rf_path, 'utf-8'))
    time.sleep(3)
    print(f"switching to rf path {rf_path}")


def set_transmitting_antenna(antenna_number):
    antenna_number += 10
    antenna_number = str(antenna_number)

    antennas.write(bytes(antenna_number, 'utf-8'))
    time.sleep(3)
    print(f"switching transmitting antenna to antenna number {int(antenna_number) - 10}")


def exportfile():
    time.sleep(delay)
    mouse.click(Button.left, 1)
    mouse.click(Button.right, 1)
    time.sleep(delay)
    mouse.position = (201, 311)
    time.sleep(delay)
    mouse.click(Button.left, 1)
    time.sleep(delay)
    mouse.position = (525, 398)
    time.sleep(delay)
    mouse.click(Button.left, 1)
    time.sleep(delay)
    mouse.position = (445, 492)
    time.sleep(delay)
    mouse.click(Button.left, 1)
    time.sleep(delay)
    mouse.position = (331, 379)
    time.sleep(delay)
    mouse.click(Button.left, 1)
    time.sleep(delay)
    mouse.position = (764, 496)
    time.sleep(delay)
    mouse.click(Button.left, 1)
    time.sleep(delay)
    ok()
    keyboard.tap(Key.tab)
    ok()



#####################################################
# start collection of data. sweep, save, title. repeat.

if motorcontrol.lower() == 'y':
    for i in range(iterations):
        sweep()
        time.sleep(0.25)
        save()
        time.sleep(0.25)
        file("Channel " + str(i + 1))
        ok()

        rotate()
        time.sleep(2) # Allow time for rotation between sweeps

else:
    # For defined number of iterations, performs sweep measurement,
    # and saves to file for each of the 4 antenna configurations
    for j in range(iterations):
        switch(j+11)
        transmitting_antenna = j+1;
        for i in range(iterations):
            if (i+1) is transmitting_antenna:
                pass
            else:
                switch(i+1)
                time.sleep(0.25)
                sweep()
                time.sleep(2.5)
                save()
                time.sleep(0.25)
                file("Channel " + str(transmitting_antenna) + str(i+1))
                ok()


endTime = time.time()
print(f"Total time: {endTime - startTime} seconds")
antennas.close()
arm.close()