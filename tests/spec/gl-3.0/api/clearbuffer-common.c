/* Copyright © 2011 Intel Corporation
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

/**
 * \file clearbuffer-common.c
 * Common code and data for the basic glClearBuffer tests
 */
#include "piglit-util.h"

const float default_color[4] = { 0.2, 0.4, 0.6, 1.0 };
const float default_depth = 0.2;
const int default_stencil = 0x7a;

int piglit_width = 100, piglit_height = 100;
int piglit_window_mode = GLUT_RGB | GLUT_DOUBLE;

GLuint
generate_simple_fbo(bool color, bool stencil, bool depth, bool packed)
{
	GLuint fb;
	GLuint rb[3];
	GLenum status;

	glGenFramebuffers(1, &fb);
	glBindFramebuffer(GL_FRAMEBUFFER, fb);

	glGenRenderbuffers(3, rb);

	if (color) {
		glBindRenderbuffer(GL_RENDERBUFFER, rb[0]);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8,
				      piglit_width, piglit_height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER,
					  GL_COLOR_ATTACHMENT0,
					  GL_RENDERBUFFER,
					  rb[0]);
	} else {
		/* If GL_ARB_ES2_compatibility is not supported, the GL
		 * expects the draw buffer and read buffer be disabled if
		 * there is no color buffer (to read or draw).
		 */
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}

	if (stencil) {
		const GLenum format = (packed)
			? GL_DEPTH24_STENCIL8
			: GL_STENCIL_INDEX8;
		const GLenum attachment = (packed)
			? GL_DEPTH_STENCIL_ATTACHMENT
			: GL_STENCIL_ATTACHMENT;

		glBindRenderbuffer(GL_RENDERBUFFER, rb[1]);
		glRenderbufferStorage(GL_RENDERBUFFER, format,
				      piglit_width, piglit_height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER,
					  attachment,
					  GL_RENDERBUFFER,
					  rb[1]);
	}

	if (!packed && depth) {
		glBindRenderbuffer(GL_RENDERBUFFER, rb[2]);
		glRenderbufferStorage(GL_RENDERBUFFER,
				      GL_DEPTH_COMPONENT24,
				      piglit_width, piglit_height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER,
					  GL_DEPTH_ATTACHMENT,
					  GL_RENDERBUFFER,
					  rb[2]);
	}

	piglit_check_gl_error(GL_NO_ERROR, PIGLIT_FAIL);

	/* All of the possible combinations that we can generate are required
	 * to be supported by all OpenGL 3.0 implementations, with one
	 * exception.  As far as I can tell, implementations are not required
	 * to support separate depth and stencil.  That one option is handled
	 * specially.
	 */
	status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE
	    && !(status == GL_FRAMEBUFFER_UNSUPPORTED && stencil && !packed)) {
		fprintf(stderr,
			"Framebuffer %s color, %s stencil (%s) was not "
			"complete: 0x%04x\n",
			color ? "with" : "without",
			stencil ? "with" : "without",
			packed ? "packed" : "separate",
			status);
		piglit_report_result(PIGLIT_FAIL);
	}

	if (status == GL_FRAMEBUFFER_UNSUPPORTED) {
		glDeleteRenderbuffers(3, rb);
		glDeleteFramebuffers(1, &fb);
		return 0;
	}

	glClearColor(default_color[0],
		     default_color[1],
		     default_color[2],
		     default_color[3]);
	glClearDepth(default_depth);
	glClearStencil(default_stencil);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT
		| GL_STENCIL_BUFFER_BIT);
	glFinish();

	piglit_check_gl_error(GL_NO_ERROR, PIGLIT_FAIL);

	return fb;
}

bool
simple_probe(bool color, const float *color_value,
	     bool stencil, int stencil_value,
	     bool depth, float depth_value)
{
	bool pass = true;

	if (color) {
		if (!piglit_probe_rect_rgba(0, 0,
					    piglit_width, piglit_height,
					    color_value)) {
			fprintf(stderr, "Bad color value.\n");
			pass = false;
		}
	}

	if (stencil) {
		if (!piglit_probe_rect_stencil(0, 0,
					       piglit_width, piglit_height,
					       stencil_value)) {
			fprintf(stderr, "Bad stencil value.\n");
			pass = false;
		}
	}

	if (depth) {
		if (!piglit_probe_rect_depth(0, 0,
					     piglit_width, piglit_height,
					     depth_value)) {
			fprintf(stderr, "Bad depth value.\n");
			pass = false;
		}
	}

	piglit_check_gl_error(GL_NO_ERROR, PIGLIT_FAIL);
	return pass;
}

enum piglit_result
piglit_display(void)
{
	return PIGLIT_FAIL;
}