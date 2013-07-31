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
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

//TODO: convert section to file name and spec quote

/**
 *  \fs-layout-qualifiers.c
 *
 * Test that layout qualifiers correctly change behavior of gl_FragCoord
 *
 * Section 4.3.4 (Inputs) of the GLSL 1.50 spec says:
 *  Fragment shaders can have an input layout only for redeclaring the
 *  built-in variable gl_FragCoord (see section 7.2 Fragment Shader Special
 *  Variables). The layout qualifier identifiers for gl_FragCoord are
 *      layout-qualifier-id
 *          origin_upper_left
 *          pixel_center_integer
 *  By default, gl_FragCoord assumes a lower-left origin for window coordinates
 *  and assumes pixel centers are located at half-pixel coordinates. For
 *  example, the (x, y) location (0.5, 0.5) is returned for the lower-left-most
 *  pixel in a window. The origin can be changed by redeclaring gl_FragCoord
 *  with the origin_upper_left identifier, moving the origin of gl_FragCoord to
 *  the upper left of the window, with y increasing in value toward the bottom
 *  of the window. The values returned can also be shifted by half a pixel in
 *  both x and y by pixel_center_integer so it appears the pixels are centered
 *  at whole number pixel offsets. This moves the (x, y) value returned by
 *  gl_FragCoord of (0.5, 0.5) by default, to (0.0, 0.0) with
 * pixel_center_integer. Redeclarations are done as follows
 *     in vec4 gl_FragCoord;    // redeclaration that changes nothing is allowed
 *     // All the following are allowed redeclaration that change behavior
 *         layout(origin_upper_left) in vec4 gl_FragCoord;
 *         layout(pixel_center_integer) in vec4 gl_FragCoord;
 *         layout(origin_upper_left, pixel_center_integer) in vec4 gl_FragCoord;
 * If gl_FragCoord is redeclared in any fragment shader in a program, it must be
 * redeclared in all the fragment shaders in that program that have a static use
 * gl_FragCoord. All redeclarations of gl_FragCoord in all fragment shaders in a
 * single program must have the same set of qualifiers. Within any shader, the
 * first redeclarations of gl_FragCoord must appear before any use of
 * gl_FragCoord. The built-in gl_FragCoord is only predeclared in fragment
 * shaders, so redeclaring it in any other shader language will be illegal.
 * Redeclaring gl_FragCoord with origin_upper_left and/or pixel_center_integer
 * qualifiers only affects gl_FragCoord.x and gl_FragCoord.y. It has no affect
 * on rasterization, transformation, or any other part of the OpenGL pipeline
 * or language features.
*/
