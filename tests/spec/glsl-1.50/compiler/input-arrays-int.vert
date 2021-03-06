// [config]
// expect_result: pass
// glsl_version: 1.50
// check_link: false
// [end config]
//
// Tests that arrays can be inputs to the vertex shader
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
			//slots
in int a[2]; 		//2
in ivec2 b[2];		//4
in ivec3 c[2];		//6
in ivec4 d[2];		//8

void main()
{
	gl_Position = vec4(a[0] + a[1] +
			b[0].x + b[1].x +
			c[0].x + c[1].x +
			d[0].x + d[1].x);
}
