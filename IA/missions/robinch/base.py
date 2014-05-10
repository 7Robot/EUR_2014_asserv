#/usr/bin/python

from missions.mission import Mission

class base(Mission):
    def __init__(self, robot, boardth):
        super(base, self).__init__(robot, boardth)
        self.name = 'base'

    def mission(self):
        logging.warn("starting mission base")
        pass
