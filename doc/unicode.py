#!/usr/bin/env python

import sys
import codecs

f = codecs.open(sys.argv[1], encoding='utf-8')
data = f.read()
for i in range(len(data)):
    ch = data[i]
    if(ch == u'\u202F'):
        print("char: %c, idx: %d"%(ch,i))
        str2 = repr(data[i-30:i+30])
        print("txt: %s" % (str2))