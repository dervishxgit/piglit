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
 *Test DeleteSync() can be called on a sync object with commands 
 * blocking it
 *
 *
 *Section 5.2(Sync Objects and Fences) of OpenGL 3.2 Core says:
 *"A sync object can be deleted by passing its name to the command
 * 	void DeleteSync( sync sync );
 * If the fence command corresponding to the specified sync object  
 * has completed, or if no ClientWaitSync or WaitSync commands are 
 * blocking on sync, the object is deleted immediately. Otherwise, 
 * sync is flagged for deletion and will be deleted when it is no 
 * longer associated with any fence command and is no longer
 * blocking any ClientWaitSync or WaitSync command. In either case, 
 * after returning from DeleteSync the sync name is invalid and can 
 * no longer be used to refer to the sync object."
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
static GLenum mess1;

void
piglit_init(int argc, char **argv)
{
	bool pass = true;

	test = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	//glFinish();
	mess1 = glClientWaitSync(test, GL_SYNC_FLUSH_COMMANDS_BIT, 1000);
	glDeleteSync(test);
	//printf("%s\n", piglit_get_gl_enum_name(mess1));

	pass = !glIsSync(test) && pass;

	piglit_report_result(pass ? PIGLIT_PASS : PIGLIT_FAIL);
}
