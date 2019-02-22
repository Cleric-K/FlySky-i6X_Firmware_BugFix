import struct
import array
import sys
import time
import datetime
import struct


# Script taken from https://github.com/qba667/FlyPlusI6X/blob/master/src/builid/fs-i6x.py
# and slightly modified
VERSION = (1, 0, 43, 1700)


def saveFile (name, data):  
	outFile = open(name, 'wb')
	outFile.write(data[0x4000:])
	outFile.close()
	

print('Reading {}, Writing {}'.format(*sys.argv[1:3]))


baseFile = sys.argv[1]
destFile = sys.argv[2]

dataFile = open(baseFile, 'rb')
data = bytearray(dataFile.read())
dataFile.close()


timeArray = bytearray(datetime.datetime.now().strftime("%H:%M:%S"), 'utf8')
dateArray = bytearray(datetime.datetime.now().strftime("%b %d %Y"), 'utf8')
dateVersionArray =  bytearray(datetime.datetime.now().strftime("1.0 %d-%b-%Y"), 'utf8')

timeArray.append(0)
dateArray.append(0)
dateVersionArray.append(0)

def patch(offset, pbytes):
    data[offset:offset+len(pbytes)] = pbytes


patch(0x11D6C, timeArray)
patch(0x11D50, dateArray)
patch(0x11D34, dateVersionArray)
patch(0x4500, struct.pack('<4H', *reversed(VERSION)))

saveFile(destFile, data)
