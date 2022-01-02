import bpy
import time
import serial
import math

comport = '/dev/ttyUSB0'

ser = serial.Serial(comport, '115200')
time.sleep(5)

for x in range(500):
    ser.write(b'x\n')
    xrot = float(ser.readline())
    bpy.context.object.rotation_euler[0] = math.radians(xrot)

    ser.write(b'y\n')
    yrot = float(ser.readline())
    bpy.context.object.rotation_euler[1] = math.radians(yrot)

    ser.write(b'z\n')
    zrot = float(ser.readline())
    bpy.context.object.rotation_euler[2] = math.radians(zrot)

    bpy.ops.wm.redraw_timer(type='DRAW_WIN_SWAP', iterations=1)
    
ser.close()