# -*- coding: utf-8 -*-
import smbus
import time
import random

bus = smbus.SMBus(1)
result_type = "none"
val = 0

while 1:
    with open('/tmp/output') as f:
        result_type = f.readlines()[-1].strip("\n")
    #print(result_type)
    #val=random.randint(0, 1)#产生随机数，范围0－25
    if(result_type == "turn_right" or result_type == "right"):
        val = 2
    elif(result_type == "turn_left" or result_type == "left"):
        val = 1
    elif(result_type == "stop" or result_type == "red_light"):
        val = 3
    elif(result_type == "backward"):
        val = 4
    elif(result_type == "forward" or result_type == "go" or result_type == "none"):
        val = 5
    else:
        val = 0
    print(val)
    bus.write_byte(0x08, val)#向地址8发送数
    time.sleep(0.05)#延时0.5
