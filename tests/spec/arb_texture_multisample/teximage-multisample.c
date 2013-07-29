/*
 * Copyright © 2013 Intel Corporation
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
 
/** @file teximage-multisample.c
 *
 * Section 3.8.4(TEXTURING) From GL spec 3.2 core:
 * Functions added 'glTexImage2DMultisample' and 'glTexImage3DMultisample'.
 *
 * For TexImage2DMultisample, target must be TEXTURE_2D_MULTISAMPLE or 
 * PROXY_TEXTURE_2D_MULTISAMPLE and for TexImage3DMultisample target must 
 * be TEXTURE_2D_MULTISAMPLE_ARRAY or PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY. 
 */

#include "piglit-util-gl-common.h"

PIGLIT_GL_TEST_CONFIG_BEGIN

	config.supports_gl_compat_version = 10;

PIGLIT_GL_TEST_CONFIG_END

// TexImage3DMultisample

static GLenum bindtarget2d[] = {
	GL_TEXTURE_2D_MULTISAMPLE,
	GL_TEXTURE_2D_MULTISAMPLE,
	GL_TEXTURE_2D
};

static GLenum targets2d[] = {
	GL_TEXTURE_2D_MULTISAMPLE,
	GL_PROXY_TEXTURE_2D_MULTISAMPLE,
	GL_TEXTURE_2D
};

static GLenum expectedError2d[] = {
	GL_NO_ERROR,
	GL_NO_ERROR,
	GL_INVALID_ENUM
};

// TexImage3DMultisample

static GLenum bindtarget3d[] = {
	GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
	GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
	GL_TEXTURE_2D
};

static GLenum targets3d[] = {
	GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
	GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY,
	GL_TEXTURE_2D
};

static GLenum expectedError3d[] = {
	GL_NO_ERROR,
	GL_NO_ERROR,
	GL_INVALID_ENUM
};

void
piglit_init(int argc, char **argv)
{
	int i;
	bool pass = true;
	GLuint textures2d[3];
	GLuint textures3d[3];
	
	glGenTextures(3, textures2d);
	glGenTextures(3, textures3d);
	
	// TexImage2DMultisample
	for(i = 0; i < sizeof(targets2d)/sizeof(GLenum); i++) {
		glBindTexture(bindtarget2d[i], textures2d[i]);
		
		glTexImage2DMultisample( targets2d[i], 4, GL_RGB,
					1024, 1024, GL_FALSE);
					
		pass = piglit_check_gl_error(expectedError2d[i]) && pass;
	}
	
	// TexImage3DMultisample
	for(i = 0; i < sizeof(targets3d)/sizeof(GLenum); i++) {
		glBindTexture(bindtarget3d[i], textures3d[i]);
		
		glTexImage3DMultisample( targets3d[i], 4, GL_RGB,
					1024, 1024, 4, GL_FALSE);

		pass = piglit_check_gl_error(expectedError3d[i]) && pass;
	}
		
	piglit_report_result(pass ? PIGLIT_PASS : PIGLIT_FAIL);
}
enum piglit_result
piglit_display(void)
{
	return PIGLIT_FAIL;
}
