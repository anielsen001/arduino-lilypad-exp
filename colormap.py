#!/usr/bin/python3
"""
create a colormap for loading into arduino program

write an output file that can be #included

"""

from matplotlib.pylab import *

# number of levels in the colormap
nLevels = 255

# set the scale range of output
scaleRange = 255 # max color value

a = cm.get_cmap('cubehelix',lut=nLevels)
ap = a(range(nLevels))

# open output file to write
with open('cmap.h','w') as f:
    f.write('#define N_CMAP_LEVELS %d\n\n'%nLevels)
    f.write('unsigned int CMAP[N_CMAP_LEVELS][3] = {\n')
    
    # loop over each level in the color map and print out
    for i,c in enumerate(ap):
        ic = c*scaleRange # create integers
        f.write('{ %d, %d, %d },\n'%(int(ic[0]),int(ic[1]),int(ic[2])))

    # done writing, finish the file
    f.write('};\n')

        
