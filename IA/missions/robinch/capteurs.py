#/usr/bin/python

from missions.mission import Mission
from logging

class Capteurs(Mission):
    def __init__(self, robot, boardth):
        super(Capteurs, self).__init__(robot, boardth)
        self.name = 'Capteurs'

    def go(self, msg, state):
        logging.warn("Starting mission %s" % self.name)
        if self.state == 'on':
            if (msg.board == 'asserv' and msg.name == 'sick'):
                if msg.id == 1:
                    self.create_send_internal('alert', {'id':1})
                elif msg.id == 2:
                    self.create_send_internal('alert', {'id':2})
                elif msg.id == 3:
                    self.create_send_internal('alert', {'id':3})
            elif (msg.board == 'asserv' and msg.name == 'freepath'):
                if msg.id == 1:
                    self.create_send_internal('freepath', {'id':1})
                elif msg.id == 2:
                    self.create_send_internal('freepath', {'id':2})
                elif msg.id == 3:
                    self.create_send_internal('freepath', {'id':3})
        elif self.state == 'off':
            self.state = 'on'
 
