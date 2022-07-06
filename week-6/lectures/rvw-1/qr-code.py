#!/usr/bin/python3

import qrcode
import os

img = qrcode.make("https://youtu.be/xvFZjo5PgG0")
img.save("../assets/qr-code.png", "PNG")
os.system("start_windows_process ../assets/qr-code.png")
