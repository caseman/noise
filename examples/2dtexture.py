"""Writes a 256x256 grayscale simplex noise texture file in pgm format
(see http://netpbm.sourceforge.net/doc/pgm.html)
"""
# $Id: 2dtexture.py 21 2008-05-21 07:52:29Z casey.duncan $

import sys
from noise import pnoise2

if len(sys.argv) not in (2, 3) or '--help' in sys.argv or '-h' in sys.argv:
	print >>sys.stderr, '2dtexture.py FILE [OCTAVES]'
	print >>sys.stderr
	print >>sys.stderr, __doc__
	raise SystemExit

f = open(sys.argv[1], 'wb')
if len(sys.argv) > 2:
	octaves = int(sys.argv[2])
else:
	octaves = 1
freq = 16.0 * octaves
print >>f, 'P2'
print >>f, '256 256'
print >>f, '255'
for y in range(256):
	for x in range(256):
		print >>f, int(pnoise2(x / freq, y / freq, octaves) * 127.0 + 128.0)
f.close()
