import numpy as np
import scipy.misc.pilutil as smp
import re
import sys

width = 41
height = 1

data = np.zeros( (width,height,3), dtype=np.uint8 )

reDone = re.compile(r".*Worker outputting: (\d+).*")

for line in sys.stdin:
    matchDone = reDone.match(line)
    if matchDone:
        print line
        num = int(matchDone.group(1))
        data[num,0] = [100,255,100]

img = smp.toimage( data )       # Create a PIL image

import pylab
pylab.imshow(img)
pylab.show()
