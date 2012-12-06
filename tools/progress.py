import numpy as np
import scipy.misc.pilutil as smp
import re
import sys
import pylab

blocks = 41
streams = 41

width = 41
height = 1

prevProgress = 0
progress = 0

data = np.zeros( (width,height,3), dtype=np.uint8 )

reDone = re.compile(r".*\[N(\d+)\] Worker outputting: (\d+).*")
reBlocks = re.compile(r".*Number of blocks: (\d+).*")
reStreams = re.compile(r".*Number of streams: (\d+).*")

for line in sys.stdin:
    matchDone = reDone.match(line)
    matchBlocks = reBlocks.match(line)
    matchStreams = reStreams.match(line)
    if matchDone:
        who = int(matchDone.group(1)) - 2
        num = int(matchDone.group(2))
        data[num % streams, num / streams] = [50*who,255-(50*who),100+40*who]
        progress += 1
        newProgress = (progress * 100.0) / (blocks * 1.0)
        if (newProgress - prevProgress > 10.0):
            print "%02f%%" % newProgress
            prevProgress = newProgress
            img = smp.toimage( data )
            pylab.imshow(img)
            pylab.show()
    changed = False
    if matchBlocks:
        blocks = int(matchBlocks.group(1))
        changed = True
    if matchStreams:
        streams = int(matchStreams.group(1))
        changed = True
    if changed:
        width = streams
        height = blocks / streams
        data = np.zeros( (width,height,3), dtype=np.uint8 )


