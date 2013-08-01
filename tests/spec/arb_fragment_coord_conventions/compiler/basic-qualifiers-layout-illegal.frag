// [config]
// expect result: fail
// glsl_version: 1.50
// check_link: false
// [end config]
/*
* Section 4.3.8.1 (Input Layout Qualifiers) of the GLSL 1.50 spec says:
*  Fragment shaders can have an input layout only for redeclaring the
*  built-in variable gl_FragCoord (see section 7.2 Fragment Shader Special
*  Variables). The layout qualifier identifiers for gl_FragCoord are
*      layout-qualifier-id:
*          origin_upper_left
*          pixel_center_integer
*
* Test should fail because input layout should only apply to gl_FragCoord.
*/

#version 150

layout(origin_upper_left, pixel_center_integer) in vec2 gl_PointCoord;

layout(origin_upper_left, pixel_center_integer) in bool gl_FrontFacing;

void main() {

     gl_FragColor(gl_FragCoord.x, gl_FragCoord.y,
     		  gl_FragCoord.z, gl_FragCoord.z);

}