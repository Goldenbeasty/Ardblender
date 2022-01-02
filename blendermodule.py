import bpy
import time
import serial #using the pyserial library placed to blender/3.0/python/lib/python3.9/ or whatever your directory is for your blender install
import math

comport = '/dev/ttyUSB0' # com port on linux, on windows it can be 

def setup():
    global ser
    ser = serial.Serial(comport, '115200')
    time.sleep(3)

def getxrot():
    ser.write(b'x\n')
    xrot = math.radians(float(ser.readline()))
    return xrot

def getyrot():
    ser.write(b'y\n')
    yrot = math.radians(float(ser.readline()))
    return yrot

def getzrot():
    ser.write(b'z\n')
    zrot = math.radians(float(ser.readline()))
    return zrot

setup()

bpy.app.driver_namespace['getxrot'] = getxrot
bpy.app.driver_namespace['getyrot'] = getyrot
bpy.app.driver_namespace['getzrot'] = getzrot

def main():
    # for i in range(5):
        bpy.context.object.rotation_euler[0] = getxrot()
        bpy.context.object.rotation_euler[1] = getyrot()
        bpy.context.object.rotation_euler[2] = getzrot()
        # bpy.ops.wm.redraw_timer(type='DRAW_WIN_SWAP', iterations=1) #needed if you want to see live updates

    # ser.close() #currently left open because I have no idea how to autostart the script

if __name__ == "__main__":
    main()