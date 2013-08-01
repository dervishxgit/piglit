// [config]
// expect result: fail
// glsl_version: 1.50
// check_link: false
// [end config]
/*
* Section 4.3.8.1 (Input Layout Qualifiers) of the GLSL 1.50 spec says:
*  Within any shader, the first redeclarations of gl_FragCoord must appear
*  before any use of gl_FragCoord.
*/

#version 150

vec2 a = gl_FragCoord.xy;

in vec4 gl_FragCoord; //redeclaration after use should be illegal

void main() {

     gl_FragColor(gl_FragCoord.x, gl_FragCoord.y,
     		  gl_FragCoord.z, gl_FragCoord.z);

}
