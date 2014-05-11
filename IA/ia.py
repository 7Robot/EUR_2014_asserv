#/usr/bin/python

import logging
import os
from classmanager import class_loader
from missions.mission import Mission

class IA:
    def __init__(self, robot, boardth):
        self.robot = robot
        self.boardth = boardth 
        self.logging = logging
        self.state = 0

        self._load_all_missions(robot.name)

    def _load_all_missions(self, prefix):
        path = os.path.join(os.getcwd(), "missions", prefix)
        missions = set(class_loader(path))
        self.missions = []
        for mission in missions:
            if mission.__name__ != "Mission" and issubclass(mission, Mission):
                m = mission(self.robot, self.boardth)
                self.missions += [m]
                self.logging.warn('mission %s loaded ...' % m.name)


    def get_msg(self):
        return self.robot.queue.get(True)


    def run(self):
        while True:
            try:
                m = self.get_msg()
                for mission in self.missions:
                    self.state = mission.go(m, self.state)
                    logging.warn("going to state %s" % self.state)

            except KeyboardInterrupt:
                break

