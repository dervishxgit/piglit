// [config]
// expect_result: pass
// glsl_version: 1.50
// check_link: false
// [end config]
//
// Tests that arrays (of matrices) can be inputs to the vertex shader
/*
* GLSLLangSpec.1.50.09 Inputs:
*
* Vertex shader inputs can only be float, floating-point
* vectors, matrices, signed and unsigned integers and integer vectors. 
* Vertex shader inputs can also form arrays of these types, but not 
* structures.
*
*/

#version 150

in mat2 a[2];		//2x2x2		8
in mat3 b[2];		//3x2x2		12
in mat4 c[2];		//4x2x2		16
//				=	36
//question for paul: neccessary to split test, given slot restrictions?

void main()
{
	gl_Position = vec4(
			a[0][0].x + a[0][1].x +
			a[1][0].x + a[1][1].x +
			b[0][0].x + b[0][1].x +
			b[1][0].x + b[1][1].x +
			c[0][0].x + c[0][1].x +
			c[1][0].x + c[1][1].x 
			);
}
