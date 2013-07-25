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
 *Test DeleteSync() returns correct error messages
 *
 *
 *Section 5.2(Sync Objects and Fences) on p243 of OpenGL 3.2 Core says:
 *"DeleteSync will silently ignore a sync value of zero. An INVALID_VALUE
 * error is generated if sync is neither zero nor the name of a sync object."
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

static GLsync test;
static GLenum ghost = GL_FRONT;

void
piglit_init(int argc, char **argv)
{
	bool pass = true;

	//****Test for successful function calls****
	glDeleteSync(0);
	pass = piglit_check_gl_error(GL_NO_ERROR) && pass;

	test = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	glDeleteSync(test);
	pass = piglit_check_gl_error(GL_NO_ERROR) && pass;

	//****Test for unsuccessful function calls****
	glDeleteSync(1);
	pass = piglit_check_gl_error(GL_INVALID_VALUE) && pass;
  
	glDeleteSync((GLsync)ghost);
	pass = piglit_check_gl_error(GL_INVALID_VALUE) && pass;

	piglit_report_result(pass ? PIGLIT_PASS : PIGLIT_FAIL);
}
