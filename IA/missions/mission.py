#/usr/bin/python

class Mission:
    def __init__(self, robot, boardth):
        self.robot = robot
        self.name = 'Mission Default Name'
        
        boards = boardth.channels
        for b in boards:
            setattr(self,b.lower(),boards[b])

    def mission(self):
        pass

