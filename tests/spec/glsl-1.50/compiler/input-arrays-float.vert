// [config]
// expect_result: pass
// glsl_version: 1.50
// check_link: false
// [end config]

#version 150

in float a[2];
in vec2 b[2];
in vec3 c[2]; 
in vec4 d[2]; 

void main()
{
	gl_Position = vec4(a[0] + a[1] + 
			b[0].x + b[1].x +
			c[0].x + c[1].x +
			d[0].x + d[1].x); 
}
