#!/usr/bin/python3

import qrcode
import sys
from os import system

code = qrcode.make("https://youtu.be/xvFZjo5PgG0")
code.save("../assets/qr-code.png")
system("start_windows_process ../assets/qr.png")
