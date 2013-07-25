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
 *Test FenceSync() returns correct error messages for invalid input
 *
 *
 *Section 5.2(Sync Objects and Fences) of OpenGL 3.2 Core says:
 *"An INVALID_ENUM error is generated if condition is not 
 * SYNC_GPU_COMMANDS_COMPLETE. If flags is not zero, an INVALID_VALUE
 * error is generated."
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

	//test that valid condition results in NO_ERROR
	GLsync a;
	a = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	pass = piglit_check_gl_error(GL_NO_ERROR) && pass;
	glDeleteSync(a);

	//test that invalid condition results in INVALID_ENUM
	GLsync b;
	b = glFenceSync(GL_NONE, 0);
	pass = piglit_check_gl_error(GL_INVALID_ENUM) && pass;
	glDeleteSync(b);

	//test that valid flag value results in NO_ERROR
	GLsync c;
	c = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	pass = piglit_check_gl_error(GL_NO_ERROR) && pass;
	glDeleteSync(c);

	//test that invalid flag value results in INVALID_VALUE
	GLsync d;
	d = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 1);
	pass = piglit_check_gl_error(GL_INVALID_VALUE) && pass;
	glDeleteSync(d);

	piglit_report_result(pass ? PIGLIT_PASS : PIGLIT_FAIL);
}
