#!/usr/bin/python3

from PIL import Image, ImageFilter

before = Image.open("../assets/test.bmp")
after = before.filter(ImageFilter.BoxBlur(10))
after.save("../assets/out-blur.bmp")
