# $Id: setup.py 532 2009-01-29 04:32:33Z casey.duncan $

import sys
from distutils.core import setup, Extension

if sys.platform != 'win32':
	compile_args = ['-funroll-loops']
else:
	# XXX insert win32 flag to unroll loops here
	compile_args = []

setup(
	name='noise',
    version='1.0b3',
	description='Perlin noise for Python',
	long_description='''\
Perlin noise is ubiquitous in modern CGI. Used for procedural texturing,
animation, and enhancing realism, Perlin noise has been called the "salt" of
procedural content. Perlin noise is a type of gradient noise, smoothly
interpolating across a pseudo-random matrix of values.

The noise library includes native-code implementations of Perlin "improved"
noise and Perlin simplex noise. It also includes a fast implementation of
Perlin noise in GLSL, for use in OpenGL shaders. The shader code and many of
the included examples require Pyglet (http://www.pyglet.org), the native-code
noise functions themselves do not, however.

The Perlin improved noise functions can also generate fBm (fractal Brownian
motion) noise by combining multiple octaves of Perlin noise. Functions for
convenient generation of turbulent noise are also included.

Version 1.0b3 fixed problems compiling with Visual C++ on Windows.
Thanks to Stas Kounitski for fixing this issue!
''',
	author='Casey Duncan',
	author_email='casey.duncan@gmail.com',
	url='http://code.google.com/p/caseman',
    classifiers = [
        'Development Status :: 4 - Beta',
        'Topic :: Multimedia :: Graphics',
        'License :: OSI Approved :: MIT License',
        'Operating System :: MacOS :: MacOS X',
        'Operating System :: Microsoft :: Windows',
        'Operating System :: POSIX',
    ],

    package_dir={'noise': ''},
    packages=['noise'],
	ext_modules=[
		Extension('noise._simplex', ['_simplex.c'], 
			extra_compile_args=compile_args,
		),
		Extension('noise._perlin', ['_perlin.c'],
			extra_compile_args=compile_args,
		)
	],
)
