// [config]
// expect result: pass
// glsl_version: 1.50
// check_link: false
// [end config]
/*
* Section 4.3.8.1 (Input Layout Qualifiers) of the GLSL 1.50 spec says:
*  Fragment shaders can have an input layout only for redeclaring the
*  built-in variable gl_FragCoord (see section 7.2 Fragment Shader Special
*  Variables).
*
*  Redeclarations are done as follows
*      in vec4 gl_FragCoord; // redeclaration that changes nothing is allowed
*/

#version 150

in vec4 gl_FragCoord;

void main() {

     gl_FragColor(gl_FragCoord.x, gl_FragCoord.y,
     		  gl_FragCoord.z, gl_FragCoord.z);

}
