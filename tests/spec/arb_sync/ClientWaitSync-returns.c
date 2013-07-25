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
 *Test ClientWaitSync() returns correct values
 *
 *
 *Section 5.2.1(Waiting for Sync Objects) of OpenGL 3.2 Core says:
 *"ClientWaitSync returns one of four status values. A return value of
 * ALREADY_SIGNALED indicates that sync was signaled at the time 
 * ClientWaitSync was called. ALREADY_SIGNALED will always be   
 * returned if sync was signaled, even if the value of timeout is 
 * zero. A return value of TIMEOUT_EXPIRED indicates that the 
 * specified timeout period expired before sync was signaled. A re-
 * turn value of CONDITION_SATISFIED indicates that sync was signaled 
 * before the timeout expired. Finally, if an error occurs, in 
 * addition to generating a GL error as specified below, 
 * ClientWaitSync immediately returns WAIT_FAILED withoutblocking."
 *
 *
 * Note: This test sporadically fails for some reason...
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

#define ONE_SECOND 1000000

void
piglit_init(int argc, char **argv)
{
	bool pass = true;
	GLsync a, b;
	GLenum status1;

	//sync not set up yet so this should fail with both GL error and
	// respond GL_WAIT_FAILED
	status1 = glClientWaitSync(a, GL_SYNC_FLUSH_COMMANDS_BIT, 0);
	//check for proper GL error
	pass = piglit_check_gl_error(GL_INVALID_VALUE) && pass;
	//check return value
	if(status1 != GL_WAIT_FAILED) {
		printf("Expected GL_WAIT_FAILED but returned: %s\n",
			piglit_get_gl_enum_name(status1));
		pass = false;
	}

	//create syncs
	a = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);

	//sync <a> has not been signaled yet
	status1 = glClientWaitSync(a, GL_SYNC_FLUSH_COMMANDS_BIT, ONE_SECOND);
	if(status1 != GL_CONDITION_SATISFIED) {
		printf("Expected GL_CONDITION_SATISFIED but returned: %s\n",
			piglit_get_gl_enum_name(status1));
		pass = false;
	}

	//sync <a> has already been signaled
	status1 = glClientWaitSync(a, GL_SYNC_FLUSH_COMMANDS_BIT, ONE_SECOND);
	if(status1 != GL_ALREADY_SIGNALED) {
		printf("Expected GL_ALREADY_SIGNALED but returned: %s\n",
			piglit_get_gl_enum_name(status1));
		pass = false;
	}

	//sync <a> has already been signaled even though timeout is 0
	status1 = glClientWaitSync(a, GL_SYNC_FLUSH_COMMANDS_BIT, 0);
	if(status1 != GL_ALREADY_SIGNALED) {
		printf("Expected GL_ALREADY_SIGNALED with timeout but returned: %s\n",
			piglit_get_gl_enum_name(status1));
		pass = false;
	}

	//create new sync and call ClientWaitSync with a quick timeout
	b = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	
	//sync <b> will be checked after timeout expires
	status1 = glClientWaitSync(b, GL_SYNC_FLUSH_COMMANDS_BIT, 0);
	if(status1 != GL_TIMEOUT_EXPIRED) {
		printf("Expected GL_TIMEOUT_EXPIRED but returned: %s\n",
			piglit_get_gl_enum_name(status1));
		pass = false;
	}

	glDeleteSync(a);
	glDeleteSync(b);

	piglit_report_result(pass ? PIGLIT_PASS : PIGLIT_FAIL);
}
