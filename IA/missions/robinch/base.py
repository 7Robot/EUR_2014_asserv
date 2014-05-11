#/usr/bin/python

from missions.mission import Mission

class base(Mission):
    def __init__(self, robot, boardth):
        super(base, self).__init__(robot, boardth)
        self.name = 'base'

    def go(self, state):
        logging.warn("starting mission base")
        return state
