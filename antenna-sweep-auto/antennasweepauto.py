"""
antennasweepauto.py
Revised 6/14/2023
Colton Cox - ccox60@uco.edu
Nathan Wiley - nwiley@uco.edu
"""

#####################################################
# Imports

import os                                                          # Module for operating system related functionalities
import pynput                                                      # Module for controlling input devices like mouse and keyboard
import time                                                        # Module for adding delays
import pygetwindow as gw                                           # Module for window management
from pynput.mouse import Button, Controller as MouseController     # Specific classes from 'pynput.mouse'
from pynput.keyboard import Key, Controller as KeyboardController  # Specific classes from 'pynput.keyboard'
import serial                                                      # Module for serial communication


#####################################################
# Start-up

delay = 0.75 # Default delay time for sleep function used in export function

startTime = time.time()
# User input to define parameters here (?)

# Number of iterations (sweeps) to perform
default_iterations = 77
iterations = 8

# Physical rotation
motorcontrol = input("Use motor control? y/n: ") # User input prompt for using the motor control window

# Time between switching RF path
switch_delay_time = 30

# Serial parameters for interfacing with antennas
COM_PORT_ANT = 'COM19' # COM port used for communicating with antennas
ant_baudrate = 115200  # Baudrate for antennas
ant_timeout = 0.1
try:
	antennas = serial.Serial(port=COM_PORT_ANT, baudrate=ant_baudrate, timeout=ant_timeout) # Attempt to set up serial connection to antennas
except:
	print(f"Couldn't find Arduino on {COM_PORT_ANT} - Is it connected?") # If serial connection fails, print error to console

# Serial parameters for interfacing with control arm
COM_PORT_ARM = 'COM17' # COM port used for communicating with control arm
arm_baudrate = 115200  # Baudrate for control arm
arm_timeout = 1
try:
    arm = serial.Serial(port='COM17', baudrate=arm_baudrate, timeout=arm_timeout) # Attempt to set up serial connection to arm
except:
    print(f"Couldn't find BlackBox on {COM_PORT_ARM} - Is it connected? Ensure motor control program isn't connected.") # If serial connection fails, print error to console

def performTesting():
    cont = True  # Initialize the 'cont' variable to True
    while cont:
        code = input("Enter channel code to send to Arduino (q to quit): ")  # Prompt the user to enter a channel code
        if code == "q":
            cont = False  # Set 'cont' to False if the code is 'q'
            break         # Exit the loop
        else:
            antennas.write(bytes(str(code), 'utf-8'))  # Write the channel code to the antennas using serial communication
            print(f"Code: {code} sent")                # Print the code for console

if iterations == 0:
    performTesting()

mouse = MouseController()
keyboard = KeyboardController()

""" 
This bit of code opens the software in the correct position
win is MegiQ VNA
win2 is CONTROL 
"""
os.startfile("C:/Program Files (x86)/MegiQ/VNA/MiQVNA.exe")  # Start the MiQVNA.exe software
time.sleep(15)      # Pause for 15 seconds
gw.getAllTitles()   # Get all the window titles
gw.getAllWindows()  # Get all the windows
gw.getWindowsWithTitle('MegiQ VNA')  # Get the windows with the title 'MegiQ VNA'
gw.getActiveWindow()    # Get the active window
win = gw.getWindowsWithTitle('MegiQ VNA')[0]  # Get the first window with the title 'MegiQ VNA'
win.activate()          # Activate the window
win.moveTo(10, 10)      # Move the window to coordinates (10, 10)
win.resizeTo(727, 767)  # Resize the window to dimensions (727, 767)

# Minimize the command program
mouse.position = (1254, 15) # Set the mouse position for the minimize button
mouse.click(Button.left, 1) # Click the left mouse button once


#####################################################
# Function Definitions

# Initiates sweep in MegiQ
def sweep():
    mouse.position = (514, 553) # Set the mouse position for the sweep button
    mouse.click(Button.left, 1) # Click the left mouse button once
    time.sleep(1)               # Pause for 1 second

# Clicks save in MegiQ
def save():
    mouse.position = (699, 558) # Set the mouse position for the save button
    mouse.click(Button.left, 1) # Click the left mouse button once
    time.sleep(1)               # Pause for 1 second

# Saves data in MegiQ - Integer parameter used for loop
def file(filename):
    filename = str(filename)  # Convert filename from int to string for keyboard input
    for f in filename:        # Splits filename into individual digits for each key press
        keyboard.tap(f)       # Simulate pressing the corresponding key on the keyboard
        time.sleep(0.2)       # Pause for 0.2 seconds between key presses
    time.sleep(1)             # Pause for 1 second (outside of loop)

# Hits enter key
def ok():
    keyboard.tap(Key.enter)

# Initiates rotation in Control
def rotate():
    mouse.position = (1320, 236) # Set the mouse position for the rotation button
    mouse.click(Button.left, 1)  # Click the left mouse button once
    time.sleep(0.5)              # Pause for 0.5 seconds

# Sends g-code commands to the control arm
def sendGCode(gcode):
    arm.write(bytes(str(gcode + '\n'), 'utf-8'))   # Send g-code command as bytes
    print(f"Code: {gcode} sent")                   # Print sent g-code for debug console
    while True:
        response = arm.readline().decode().strip() # Read response from BlackBox
        if response == 'ok':                       # If response is 'ok'...
            break                                  # ...exit the loop
        elif response.startswith('error'):
            raise Exception(response)
        time.sleep(0.1)


def raiseToCompressor():
    sendGCode('$X')
    sendGCode('G10 P0 L20 Y0')
    sendGCode('$J=G91G21Y500F3600')
    time.sleep(10)
    sendGCode('G90\n G21\n G0 Y0')

# Changes signal path on switch to param
# Writes string number to arduino, parsed to function call for RF channel select (see switch_update.ino)
def switch(rf_path):
    rf_path = str(rf_path)                   # Convert the RF path to a string
    antennas.write(bytes(rf_path, 'utf-8'))  # Write the RF path to the antennas using serial communication
    time.sleep(3)                            # Pause for 3 seconds
    print(f"switching to rf path {rf_path}") # Print the RF path for console

#####################################################
# Start collection of data: sweep, save, title, repeat.
# For defined number of iterations (j and i), performs sweep measurement,
# and saves to file for each of the 4 antenna configurations
for j in range(iterations):
    raiseToCompressor()           # Bring the phantom up into the air compressor chamber and back down
    switch(j + 11)                # Change the signal path on the switch to the RF channel (j + 11)
    transmitting_antenna = j + 1; # Set the transmitting antenna number to (j + 1)
    for i in range(iterations):
        if (i + 1) is transmitting_antenna:
            pass              # Skip this iteration if i + 1 is the same as the transmitting antenna number
        else:
            switch(i + 1)     # Change the signal path on the switch to the RF channel (i + 1)
            time.sleep(0.25)  # Pause for 0.25 seconds
            sweep()           # Initiate sweep in MegiQ
            time.sleep(2.5)   # Pause for 2.5 seconds
            save()            # Click save in MegiQ
            time.sleep(0.25)  # Pause for 0.25 seconds
            file("Channel " + str(transmitting_antenna) + str(i + 1))  # Save data with a filename based on the transmitting and receiving antenna numbers
            ok()              # Press the Enter key

endTime = time.time()                               # Record end time for data collection
print(f"Total time: {endTime - startTime} seconds") # Print end time to console
antennas.close() # Close serial connect to antennas for safety...
arm.close()      # ...and also close connection to arm