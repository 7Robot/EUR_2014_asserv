#/usr/bin/python

from missions.mission import Mission
import logging

class Peintures(Mission):
    def __init__(self, robot, boardth):
        super(Peintures, self).__init__(robot, boardth)
        self.name = 'Peintures'

    def go(self, msg, state):
        logging.warn("starting mission %s" % self.name)
        if (state == 1 and msg.board == 'internal' and msg.name == 'beginmatch'):
            self.asserv.distRot(1, 0)
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

