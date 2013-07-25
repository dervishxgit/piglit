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
 *Test IsSync()
 *
 *
 *Section 6.1.7(Sync Object Queries) of OpenGL 3.2 Core says:
 *"The command
 *	boolean IsSync( sync sync );
 * returns TRUE if sync is the name of a sync object. If sync is not the name of a sync
 * object, or if an error condition occurs, IsSync returns FALSE (note that zero is not
 * the name of a sync object)."
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

static GLsync test1, test2;

void
piglit_init(int argc, char **argv)
{
	bool pass = true;

	//Create valid sync object
	test1 = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);

	//Check if a valid name returns true
	pass = glIsSync(test1) && pass;

	//Check if invalid names return false
	pass = !glIsSync(test2) && pass;

	pass = !glIsSync(0) && pass;

	glDeleteSync(test1);

	piglit_report_result(pass ? PIGLIT_PASS : PIGLIT_FAIL);
}
