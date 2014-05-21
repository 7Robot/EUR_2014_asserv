from missions.mission import Mission
import logging

class Turn(Mission):
    def __init__(self, robot, boardth):
        super(Turn, self).__init__(robot, boardth)
        self.name = 'Turning mission'
        
    def go(self, msg, state):
        if (msg.board == "internal" and msg.name == 'turn'):
            self.asserv.reachTheta(msg.target, 0.1, 0.1)
            state = "turning"

        elif (state == "turning"):
            if msg.board == "asserv" and msg.name == 'done'):
                self.target = None
                self.axe = None
                state = "done"