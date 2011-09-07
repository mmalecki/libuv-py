/*
 * Copyright (c) 2011, Ben Noordhuis <info@bnoordhuis.nl>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "Python.h"
#include "uv.h"

#include <stdlib.h>
#include <string.h>

static PyTypeObject tp_tcp;

static PyObject *tp_tcp_new(PyTypeObject* type, PyObject *a, PyObject *b);

static PyObject *do_run(PyObject *a, PyObject *b);

static PyMethodDef methods[] = {
  { "run", do_run, METH_NOARGS, NULL },
  { NULL, NULL, 0, NULL }
};


static PyObject *tp_tcp_new(PyTypeObject *type, PyObject *a, PyObject *b) {
  uv_tcp_t *handle;

  if ((handle = malloc(sizeof *handle)) == NULL)
    goto out;

  if (uv_tcp_init(handle)) {
    free(handle);
    goto out;
  }

out:
  return 0;
}


static PyObject *do_run(PyObject *a, PyObject *b) {
  int r;

  r = uv_run();

  return PyInt_FromLong(r);
}


PyMODINIT_FUNC init(void) {
  PyObject *module;

  module = Py_InitModule3("uv", methods, "libuv bindings");
  if (!module)
    return;

  tp_tcp.tp_new = tp_tcp_new;
}
