import pygetwindow
import time
from PIL import ImageGrab
import imagehash
import subprocess
import hashlib
import sys

#https://github.com/christopherpow/nes-test-roms/

proc = subprocess.Popen("./neslika " + sys.argv[1], shell=True)
time.sleep(1)

c = pygetwindow.getWindowGeometry("neslika")
img = ImageGrab.grab().crop((c[0] * 2, c[1] * 2, (c[2] + c[0]) * 2, (c[3] + c[1]) * 2))
print(imagehash.dhash(img))

proc.kill()