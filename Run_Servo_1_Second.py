#!/usr/bin/python3

import RPi.GPIO as GPIO
import time
import os
import smtplib, ssl

def sendEmail(mess):
    port = 465 # for SSL
    password = "raspiFeeder"
    sender = "pyfeeder@gmail.com"
    receiver = "lydia.nguyen9@gmail.com"
    message = mess

    #Create a secure SSL Context
    context = ssl.create_default_context()

    with smtplib.SMTP_SSL("smtp.gmail.com", port, context = context) as server:
        server.login("pyfeeder@gmail.com", password)
        server.sendmail(sender, receiver, message)

GPIO.setmode(GPIO.BOARD) #sets GPIO pins to board
GPIO.setup(11,GPIO.OUT)  #sets pin 11 to output
GPIO.setup(13,GPIO.OUT)  #sets pin 13 to output
GPIO.setup(15,GPIO.IN) #sets pin 15 as input
x = 100 * [0]
GPIO.output(13, GPIO.HIGH)
p=GPIO.PWM(11,50)        #sets var PWM as pin 11, 50Hz
p.start(7.3)
time.sleep(1)
p.ChangeDutyCycle(10)    #Runs Servo full speed
time.sleep(0.52)          #delays action
p.ChangeDutyCycle(7.3)   #changes servo speed to 0
GPIO.output(13, GPIO.LOW)
for ii in range(100):
    x[ii] = GPIO.input(15)
    time.sleep(0.01)
time.sleep(1)
p.stop()
time.sleep(1)
if (sum(x)>10):
    print(sum(x))
    sendEmail('Subject: Feeder notification - \n\n The stupid cats have been fed.')
else:
    print(sum(x))
    sendEmail('Subject: Feeder notification - \n\n The feeder might be empty, or not have gone off')
    







