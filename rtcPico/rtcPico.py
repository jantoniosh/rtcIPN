from machine import Timer, Pin, I2C
from sh1106 import SH1106_I2C

WIDTH  = 128                                           
HEIGHT = 64                                             

i2c = I2C(0, scl=Pin(9), sda=Pin(8), freq=200000)      
print(i2c.scan())
print("I2C Address      : "+hex(i2c.scan()[0]).upper()) 
print("I2C Configuration: "+str(i2c))                   


oled = SH1106_I2C(WIDTH, HEIGHT, i2c)

oled.rotate(180)

count = 0

def counter(timer):
    global count
    # increment count
    oled.fill(0)
    oled.text("Contador:",5,5)
    oled.text(str(count),5,15)
    oled.show()
    print(count)
    count += 1

timer = Timer(-1)

timer.init(period=1000, mode=Timer.PERIODIC, callback=counter)