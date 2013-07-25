/* Copyright © 2013 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

/*
 *Test GetSynciv() returns correct error messages for invalid input
 *
 *
 *Section 6.1.7(Sync Object Queries) of OpenGL 3.2 Core says:
 * (For GetSynciv) "If sync is not the name of a sync object, an INVALID_VALUE error is generated.
 * If pname is not one of the values described above, an INVALID_ENUM error is
 * generated."
 *
 */

#include "piglit-util-gl-common.h"

PIGLIT_GL_TEST_CONFIG_BEGIN

config.supports_gl_compat_version = 10;

PIGLIT_GL_TEST_CONFIG_END

enum piglit_result
piglit_display(void)
{
	/* UNREACHED */
	return PIGLIT_FAIL;
}

void
piglit_init(int argc, char **argv)
{
	bool pass = true;
	GLsync a, b;
	GLint c;
	c = 20;

	GLsizei len;
	GLint val;

	a = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);

	//test that valid sync results in NO_ERROR
	glGetSynciv(a, GL_SYNC_STATUS, 1, &len, &val);
	pass = piglit_check_gl_error(GL_NO_ERROR) && pass;

	//test that invalid sync results in INVALID_VALUE
	glGetSynciv(b, GL_SYNC_STATUS, 1, &len, &val);
	pass = piglit_check_gl_error(GL_INVALID_VALUE) && pass;

	glGetSynciv(c, GL_SYNC_STATUS, 1, &len, &val);
	pass = piglit_check_gl_error(GL_INVALID_VALUE) && pass;

	//test valid pname values result in NO_ERROR
	glGetSynciv(a, GL_OBJECT_TYPE, 1, &len, &val);
	pass = piglit_check_gl_error(GL_NO_ERROR) && pass;

	glGetSynciv(a, GL_SYNC_STATUS, 1, &len, &val);
	pass = piglit_check_gl_error(GL_NO_ERROR) && pass;

	glGetSynciv(a, GL_SYNC_CONDITION, 1, &len, &val);
	pass = piglit_check_gl_error(GL_NO_ERROR) && pass;

	glGetSynciv(a, GL_SYNC_FLAGS, 1, &len, &val);
	pass = piglit_check_gl_error(GL_NO_ERROR) && pass;

	//test that invalid pname results in INVALID_ENUM
	glGetSynciv(a, GL_INVALID_VALUE, 1, &len, &val);
	pass = piglit_check_gl_error(GL_INVALID_ENUM) && pass;

	glDeleteSync(a);

	piglit_report_result(pass ? PIGLIT_PASS : PIGLIT_FAIL);
}
