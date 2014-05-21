#/usr/bin/python

from missions.mission import Mission
import logging

class Lances(Mission):
    def __init__(self, robot, boardth):
        super(Lances, self).__init__(robot, boardth)
        self.name = 'Lances'

    def go(self, msg, state):
        if (state == 1 and msg.board == 'internal' and msg.name == 'beginmatch'):
            logging.warn("starting mission %s" % self.name)
            self.asserv.distRot(0.70, 0)
            state = 2
        if state == 2:
            if (msg.board == 'internal' and msg.name == 'alert'):
                self.asserv.stop()
                #determiner la distance a l'objet
            elif (msg.board == 'asserv' and msg.name == 'freepath'):
                self.asserv.distRot(0,0)
                #envoyer la consigne a l'objet
            elif (msg.board == 'asserv' and msg.name == 'done'):
                state = 3

        return state

