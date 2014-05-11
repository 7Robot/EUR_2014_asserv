#/usr/bin/python

class Msg:
    def __init__(self, board, name, args=None, info=None):
        self.board = board
        self.name = name
        self.args = args
        self.info = info

    def __getattr__(self, attr):
        return self.args[attr]

class InternalMsg(Msg):
    def __init__(self, name, args=None):
        super(Msg, self).__init__("internal", name, args)
