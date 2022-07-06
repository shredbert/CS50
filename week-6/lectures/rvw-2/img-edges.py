#!/usr/bin/python3

from PIL import Image, ImageFilter

before = Image.open("../assets/test.bmp")
after = before.filter(ImageFilter.FIND_EDGES())
after.save("../assets/edges.bmp")
