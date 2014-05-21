from missions.mission import Mission
import logging

class Forward(Mission):
    def __init__(self, robot, boardth):
        super(Forward, self).__init__(robot, boardth)
        self.name = 'Forward mission'
        self.target = None
        self.axe = None
        
    def walk(axe, target):
        if (axe == 'x'):
            self.asserv.reachX(target, 0.1, 0.1)
        elif (axe == 'y'):
            self.asserv.reachY(target, 0.1, 0.1)
        
    def go(self, msg, state):
        if (msg.board == "internal" and msg.name == 'forward'):
            self.target = msg.target
            self.axe = msg.axe  
            self.walk(msg.axe, msg.target)
            state = "forward"            
        
        elif (state == "forward"):
            if (msg.board == "internal" and msg.name == 'alert'):
                self.asserv.stop()
                state = "waiting"
            elif msg.board == "asserv" and msg.name == 'done'):
                self.target = None
                self.axe = None
                state = "done"
                
        elif (state == "waiting"):
            if (msg.board == 'asserv' and msg.name == 'freepath'):
                self.walk(self.axe, self.target)
                state = "forward"
                
        return state