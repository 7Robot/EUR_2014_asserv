#!/usr/bin/python

import argparse, configparser
import sys
import socket

from atp.protos import load as load_protos
from atp.channel import Channel, print_packet

from robots import robinch
import boardThread

if __name__ == "__main__":
    while True:
        try:
            robot = robinch.Robinch()
            boardth = boardThread.BoardThread(robot)
            boardth.start()

        except KeyboardInterrupt:
            break

