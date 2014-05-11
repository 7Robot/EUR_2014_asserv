#/usr/bin/python
import logging
from msg.msg import Msg

class Mission:
    def __init__(self, robot, boardth):
        self.robot = robot
        self.name = 'Mission Name not implemented'
        
        boards = boardth.channels
        for b in boards:
            setattr(self,b.lower(),boards[b])

    def create_send_event(self, board, name, args):
        m = Msg(board, name, args)
        self.robot.queue.put(m, True)
        
    def send_event(self, msg):
        self.robot.queue.put(msg, True)

    def go(self, msg, state):
        logging.warn('Mission not implemented')
        return state

