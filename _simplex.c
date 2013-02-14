// Copyright (c) 2008, Casey Duncan (casey dot duncan at gmail dot com)
// see LICENSE.txt for details
// $Id$

#include "Python.h"
#include <math.h>
#include "_noise.h"

// 2D simplex skew factors
#define F2 0.3660254037844386f  // 0.5 * (sqrt(3.0) - 1.0)
#define G2 0.21132486540518713f // (3.0 - sqrt(3.0)) / 6.0

float 
noise2(float x, float y) 
{
	int i1, j1, I, J, c;
	float s = (x + y) * F2;
	float i = floorf(x + s);
	float j = floorf(y + s);
	float t = (i + j) * G2;

	float xx[3], yy[3], f[3];
	float noise[3] = {0.0f, 0.0f, 0.0f};
	int g[3];

	xx[0] = x - (i - t);
	yy[0] = y - (j - t);

	i1 = xx[0] > yy[0];
	j1 = xx[0] <= yy[0];

	xx[2] = xx[0] + G2 * 2.0f - 1.0f;
	yy[2] = yy[0] + G2 * 2.0f - 1.0f;
	xx[1] = xx[0] - i1 + G2;
	yy[1] = yy[0] - j1 + G2;

	I = (int) i & 255;
	J = (int) j & 255;
	g[0] = PERM[I + PERM[J]] % 12;
	g[1] = PERM[I + i1 + PERM[J + j1]] % 12;
	g[2] = PERM[I + 1 + PERM[J + 1]] % 12;

	for (c = 0; c <= 2; c++)
		f[c] = 0.5f - xx[c]*xx[c] - yy[c]*yy[c];
	
	for (c = 0; c <= 2; c++)
		if (f[c] > 0)
			noise[c] = f[c]*f[c]*f[c]*f[c] * (GRAD3[g[c]][0]*xx[c] + GRAD3[g[c]][1]*yy[c]);
	
	return (noise[0] + noise[1] + noise[2]) * 70.0f;
}

static PyObject *
py_noise2(PyObject *self, PyObject *args, PyObject *kwargs)
{
	float x, y;
	int octaves = 1;
	float persistence = 0.5f;
	static char *kwlist[] = {"x", "y", "octaves", "persistence", NULL};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ff|if:snoise2", kwlist,
		&x, &y, &octaves, &persistence))
		return NULL;
	
	if (octaves == 1) {
		// Single octave, return simple noise
		return (PyObject *) PyFloat_FromDouble((double) noise2(x, y));
	} else if (octaves > 1) {
		int i;
		float freq = 1.0f;
		float amp = 1.0f;
		float max = 0.0f;
		float total = 0.0f;

		for (i = 0; i < octaves; i++) {
			total += noise2(x * freq, y * freq) * amp;
			max += amp;
			freq *= 2.0f;
			amp *= persistence;
		}
		return (PyObject *) PyFloat_FromDouble((double) (total / max));
	} else {
		PyErr_SetString(PyExc_ValueError, "Expected octaves value > 0");
		return NULL;
	}
}

#define dot3(v1, v2) ((v1)[0]*(v2)[0] + (v1)[1]*(v2)[1] + (v1)[2]*(v2)[2])

#define ASSIGN(a, v0, v1, v2) (a)[0] = v0; (a)[1] = v1; (a)[2] = v2;

#define F3 (1.0f / 3.0f)
#define G3 (1.0f / 6.0f)

float 
noise3(float x, float y, float z) 
{
	int c, o1[3], o2[3], g[4], I, J, K;
	float f[4], noise[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	float s = (x + y + z) * F3;
	float i = floorf(x + s);
	float j = floorf(y + s);
	float k = floorf(z + s);
	float t = (i + j + k) * G3;

	float pos[4][3];

	pos[0][0] = x - (i - t);
	pos[0][1] = y - (j - t);
	pos[0][2] = z - (k - t);

	if (pos[0][0] >= pos[0][1]) {
		if (pos[0][1] >= pos[0][2]) {
			ASSIGN(o1, 1, 0, 0);
			ASSIGN(o2, 1, 1, 0);
		} else if (pos[0][0] >= pos[0][2]) {
			ASSIGN(o1, 1, 0, 0);
			ASSIGN(o2, 1, 0, 1);
		} else {
			ASSIGN(o1, 0, 0, 1);
			ASSIGN(o2, 1, 0, 1);
		}
	} else {
		if (pos[0][1] < pos[0][2]) {
			ASSIGN(o1, 0, 0, 1);
			ASSIGN(o2, 0, 1, 1);
		} else if (pos[0][0] < pos[0][2]) {
			ASSIGN(o1, 0, 1, 0);
			ASSIGN(o2, 0, 1, 1);
		} else {
			ASSIGN(o1, 0, 1, 0);
			ASSIGN(o2, 1, 1, 0);
		}
	}
	
	for (c = 0; c <= 2; c++) {
		pos[3][c] = pos[0][c] - 1.0f + 3.0f * G3;
		pos[2][c] = pos[0][c] - o2[c] + 2.0f * G3;
		pos[1][c] = pos[0][c] - o1[c] + G3;
	}

	I = (int) i & 255; 
	J = (int) j & 255; 
	K = (int) k & 255;
	g[0] = PERM[I + PERM[J + PERM[K]]] % 12;
	g[1] = PERM[I + o1[0] + PERM[J + o1[1] + PERM[o1[2] + K]]] % 12;
	g[2] = PERM[I + o2[0] + PERM[J + o2[1] + PERM[o2[2] + K]]] % 12;
	g[3] = PERM[I + 1 + PERM[J + 1 + PERM[K + 1]]] % 12; 

	for (c = 0; c <= 3; c++) {
		f[c] = 0.6f - pos[c][0]*pos[c][0] - pos[c][1]*pos[c][1] - pos[c][2]*pos[c][2];
	}
	
	for (c = 0; c <= 3; c++) {
		if (f[c] > 0) {
			noise[c] = f[c]*f[c]*f[c]*f[c] * dot3(pos[c], GRAD3[g[c]]);
		}
	}
	
	return (noise[0] + noise[1] + noise[2] + noise[3]) * 32.0f;
}

static PyObject *
py_noise3(PyObject *self, PyObject *args, PyObject *kwargs)
{
	float x, y, z;
	int octaves = 1;
	float persistence = 0.5f;

	static char *kwlist[] = {"x", "y", "z", "octaves", "persistence", NULL};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "fff|if:snoise3", kwlist,
		&x, &y, &z, &octaves, &persistence))
		return NULL;
	
	if (octaves == 1) {
		// Single octave, return simple noise
		return (PyObject *) PyFloat_FromDouble((double) noise3(x, y, z));
	} else if (octaves > 1) {
		int i;
		float freq = 1.0f;
		float amp = 1.0f;
		float max = 0.0f;
		float total = 0.0f;

		for (i = 0; i < octaves; i++) {
			total += noise3(x * freq, y * freq, z * freq) * amp;
			freq *= 2.0f;
			max += amp;
			amp *= persistence;
		}
		return (PyObject *) PyFloat_FromDouble((double) (total / max));
	} else {
		PyErr_SetString(PyExc_ValueError, "Expected octaves value > 0");
		return NULL;
	}
}

#define F4 0.30901699437494745f # (sqrt(5.0) - 1.0) / 4.0
#define G4 0.1381966011250105f # (5.0 - sqrt(5.0)) / 20.0
/*
float
noise4(float x, float y, float z, float w) 
{
	float s = (x + y + z + w) * F4;
	int i = floorf(x + s);
	int j = floorf(y + s);
	int k = floorf(z + s);
	int m = floorf(w + s);

	float t = (i + j + K + m) * G4;
*/

static PyMethodDef simplex_functions[] = {
	{"noise2", (PyCFunction)py_noise2, METH_VARARGS | METH_KEYWORDS, 
		"noise2(x, y, octaves=1, persistence=0.5) return simplex noise value for specified "
		"coordinate.\n\n"
		"octaves -- specifies the number of passes, defaults to 1 (simple noise).\n\n"
		"persistence -- specifies the amplitude of each successive octave relative\n"
		"to the one below it. Defaults to 0.5 (each higher octave's amplitude\n"
		"is halved). Note the amplitude of the first pass is always 1.0."},
	{"noise3", (PyCFunction)py_noise3, METH_VARARGS | METH_KEYWORDS, 
		"noise3(x, y, z, octaves=1, persistence=0.5) return simplex noise value for "
		"specified coordinate\n\n"
		"octaves -- specifies the number of passes, defaults to 1 (simple noise).\n\n"
		"persistence -- specifies the amplitude of each successive octave relative\n"
		"to the one below it. Defaults to 0.5 (each higher octave's amplitude\n"
		"is halved). Note the amplitude of the first pass is always 1.0."},
	{NULL}
};

PyDoc_STRVAR(module_doc, "Native-code simplex noise functions");

#if PY_MAJOR_VERSION >= 3

static struct PyModuleDef moduledef = {
	PyModuleDef_HEAD_INIT,
	"_simplex",
	module_doc,
	-1,                 /* m_size */
	simplex_functions,  /* m_methods */
	NULL,               /* m_reload (unused) */
	NULL,               /* m_traverse */
	NULL,               /* m_clear */
	NULL                /* m_free */
};

PyObject *
PyInit__simplex(void)
{
    return PyModule_Create(&moduledef);
}

#else

void
init_simplex(void)
{
	Py_InitModule3("_simplex", simplex_functions, module_doc);
}

#endif
