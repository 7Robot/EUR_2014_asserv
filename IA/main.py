#!/usr/bin/python

import argparse, configparser
import sys
import socket

from atp.protos import load as load_protos
from atp.channel import Channel, print_packet


if __name__ == "__main__":

    configfile = '/etc/atp.conf'
    config = configparser.ConfigParser()
    config.read(configfile)

    #semantic_file = '/home/robot/EUR"
    if not semantic_file and 'atp' in config and 'semantic' in config['atp']:
        semantic_file = config['atp']['semantic']
    if not semantic_file:
        print("Error: can't find semantic file.", file=sys.stderr)
        sys.exit(1)
    protos = load_protos(semantic_file)

    board = args.board
    if not board and 'atp' in config and 'board' in config['atp']:
        board = config['atp']['board']
    if not board:
        print("Error: please specify board protocol to use.", file=sys.stderr)
        sys.exit(1)
    board = board.capitalize()

    if not board in protos:
        print("Error: unknow board protocol '%s' (available: %s)."
                %(board, ','.join(protos.keys())), file=sys.stderr)
        sys.exit(1)
    proto = protos[board]

    stream = sys.stdin.buffer

    host, port = ('localhost',1301)
   
    #transmitter = ''
    if not transmitter and 'atp' in config and 'transmitter' in config['atp']:
        transmitter = config['atp']['transmitter']

    callback = print_packet

    channel = Channel(stream, callback, board.lower(), proto,
            transmitter = transmitter, follow = args.follow)
    
    while True:
        try:
            robot = Robot()
            robot.run()

        except KeyboardInterrupt:
            break

class Robot:
    def __init__(self, channel):
        self.board = 'asserv'
        self.channel = channel

    def run(self):
        pass

