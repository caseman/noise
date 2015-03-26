import sys
try:
    from setuptools import setup, Extension
except ImportError:
    from distutils.core import setup, Extension

if sys.platform != 'win32':
    compile_args = ['-funroll-loops']
else:
    # XXX insert win32 flag to unroll loops here
    compile_args = []

setup(
    name='noise',
    version='1.2.2',
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
motion) noise by combining multiple octaves of Perlin noise. Shader functions
for convenient generation of turbulent noise are also included.

- 1.2.2 AppVeyor support for Windows builds (Thanks to Federico Tomassetti)

- 1.2.1 Fixes MSVC compatibility (Thanks to Christoph Gohlke)

- 1.2.0 adds 4D simplex noise, tiling for 2D simplex noise, 
  and parameterized lacunarity

See CHANGES.txt for more details
''',
    author='Casey Duncan',
    author_email='casey.duncan@gmail.com',
    url='https://github.com/caseman/noise',
    classifiers = [
        'Development Status :: 4 - Beta',
        'Topic :: Multimedia :: Graphics',
        'License :: OSI Approved :: MIT License',
        'Operating System :: MacOS :: MacOS X',
        'Operating System :: Microsoft :: Windows',
        'Operating System :: POSIX',
        'Programming Language :: C',
        'Programming Language :: Python :: 2',
        'Programming Language :: Python :: 3',
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
