#/usr/bin/python

from missions.mission import Mission
import logging

class Lances(Mission):
    def __init__(self, robot, boardth):
        super(Lances, self).__init__(robot, boardth)
        self.name = 'Lances'
        self.balls = 0

    def go(self, msg):
        if (msg.board == 'internal' and msg.name == 'beginlances'):
            self.state = 'on'
            self.create_send_internal('forward', {'target':0.62, 'axe':'x'})

        elif (self.state == 'on'):
            if (msg.board == 'internal' and msg.name == 'forward_done'):
                self.asserv.speed(0.05, 0.1, 0.1)
                self.asserv.launchBalls(5)
                self.state = "speed_lances"

        elif (self.state == "speed_lances"):
            if (msg.board == 'asserv' and msg.name == 'doneLaunch'):
                self.asserv.stop()
                self.asserv.stopLaunch()
                self.state = 'off'
            elif (msg.board == 'internal' and msg.name == 'alert'):
                self.asserv.stop()
                self.asserv.stopLaunch()
            elif (msg.board == 'internal' and msg.name == 'freepath'): 
                self.asserv.getBalls()
            elif (msg.board == 'asserv' and msg.name == 'balls'):
                self.balls = msg.amount
                self.asserv.getPos()
            elif (msg.board == 'asserv' and msg.name == 'pos'):
                if abs(msg.x) > 0.90:
                    self.state = 'off'
                elif abs(msg.x) < 0.90:
                    self.asserv.speed(0.05, 0.1, 0.1)
                    self.asserv.launchBalls(msg.amount)


