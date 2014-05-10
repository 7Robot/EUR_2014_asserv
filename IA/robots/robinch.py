#/usr/bin/python

from mathutils.types import Vertex

class Robinch:
    def __init__(self):
        self.name = 'robinch'
        self.transmitter = 'arm'
        self.boards  = { "Asserv": 1301, "Turret": 1308 }
        self.semantic = '/home/ken/depots/EUR_2014_asserv/EUR_2014_asserv.X/semantic.py'
        self.host = 'localhost'

        #position et orientation initiale du robot
        self.pos = Vertex(-12000, -7000)
        self.rot = 0

        self.sensor_front = None 
        self.sensor_back = None
