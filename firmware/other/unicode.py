# -*- coding: utf-8 -*-

import sys

text = "МОЩНЫЙ"

s = text.decode('utf8')

for char in s:
    letter = ord(char) + 0xb0 - 0x410
    sys.stdout.write("\\x%x" % letter)
