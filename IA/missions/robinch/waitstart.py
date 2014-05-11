#/usr/bin/python

from missions.mission import Mission
import logging

class WaitForSignal(Mission):
    def __init__(self, robot, boardth):
        super(WaitForSignal, self).__init__(robot, boardth)
        self.name = 'Wait for start'

    def go(self, msg, state):
        logging.warn("starting mission %s" % self.name)
        if (state == 0 and msg.board == 'asserv' and msg.name == 'start'):
            if msg.color == 0:
                state = 127
            elif msg.color == 1:
                state = 1

        return state
