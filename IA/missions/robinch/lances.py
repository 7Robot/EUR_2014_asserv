#/usr/bin/python

from missions.mission import Mission
import logging

class Lances(Mission):
    def __init__(self, robot, boardth):
        super(Lances, self).__init__(robot, boardth)
        self.name = 'Lances'
        self.balls = 0

    def go(self, msg):
        if (self.state = 'off' and msg.board == 'internal' and msg.name == 'beginlances'):
            self.state = 'on'
            self.create_send_internal('forward', {'target':0.62, 'axe':'x'})

<<<<<<< HEAD
        elif (self.state == 'on' and msg.board == 'internal' and msg.name == 'done'):
                self.asserv.odoBroadcastOn()
=======
        elif (self.state == 'on'):
            if (msg.board == 'internal' and msg.name == 'forward_done'):
>>>>>>> 69e8380b5d31401eacd8392b79887f943c569b2d
                self.asserv.speed(0.05, 0.1, 0.1)
                self.asserv.launchBalls(5)
                self.state = "speed_lances"

        elif (self.state == "speed_lances" and msg.board == 'asserv' and msg.name == 'doneLaunch'):
                self.asserv.stop()
                self.asserv.stopLaunch()
                self.asserv.odoBroadcastOff()
                self.state = 'off'

        elif (self.state = 'speed_lances' and msg.board == 'internal' and msg.name == 'alert'):
                self.asserv.stop()
                self.asserv.stopLaunch()
                self.state = 'alert'

        elif (self.state = 'alert' and msg.board == 'internal' and msg.name == 'freepath'): 
                self.asserv.getBalls()
                self.state = 'speed_lances_2'

        elif (self.state = 'speed_lances_2' and msg.board == 'asserv' and msg.name == 'balls'):
                self.balls = msg.amount
                self.state = 'speed_lances_2'

        elif (self.state = 'speed_lances_2' and msg.board == 'asserv' and msg.name == 'pos'):
                if abs(msg.x) > 0.90:
                    self.asserv.odoBroadcastOff()
                    self.asserv.stopLaunch()
                    self.state = 'off'
                elif abs(msg.x) < 0.90:
                    self.asserv.speed(0.05, 0.1, 0.1)
                    self.asserv.launchBalls(msg.amount)
                    self.state = 'speed_lances'


