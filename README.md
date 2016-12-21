Native-code and shader implementations of Perlin noise for Python

By Casey Duncan <casey dot duncan at gmail dot com>

This package is designed to give you simple to use, fast functions for
generating Perlin noise in your Python programs. Perlin noise is famously
called the "salt" of procedural generation, as it adds considerable flavor in
its application. Noise is commonly used for imparting realism in textures,
animation and other procedural content generation -- placement of hairs,
heights of mountains, density of forests, waving of a flag, etc. etc..

Ken Perlin invented the technique implemented in these algorithms following
his work on the CGI for the movie Tron. Over time Perlin noise has become
ubiquitous in CGI, and greatly contributed to the huge leap in realism that
followed.

An excellent "from the horse's mouth" overview of Perlin noise can be found
here: http://www.noisemachine.com/talk1/

An excellent discussion of simplex noise can be found here:
http://zach.in.tu-clausthal.de/teaching/cg2_08/literatur/simplexnoise.pdf

The noise library includes native-code implementations of Perlin "improved"
noise and Perlin simplex noise. It also includes a fast implementation of
Perlin noise in GLSL, for use in OpenGL shaders. The shader code and many of
the included examples require Pyglet (http://www.pyglet.org), the native-code
noise functions themselves do not, however.

The Perlin improved noise functions can also generate fBm (fractal Brownian
motion) noise by combining multiple octaves of Perlin noise. Functions for
convenient generation of turbulent noise in shaders are also included.

Installation uses the standard Python distutils regime:

python setup.py install

This will compile and install the noise package into your Python site
packages.

The functions and their signatures are documented in their respective
docstrings.  Use the Python help() function to read them.

>>> import noise 
>>> help(noise)

The examples directory contains sample programs using the noise functions.

I hope you find this package useful. Please send suggestions and bug reports
to my email above.

----

Blue planet texture used for atmosphere example courtesy NASA
