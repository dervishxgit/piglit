// [config]
// expect_result: fail
// glsl_version: 1.10
//
// # NOTE: Config section was auto-generated from file
// # NOTE: 'glslparser.tests' at git revision
// # NOTE: 6cc17ae70b70d150aa1751f8e28db7b2a9bd50f0
// [end config]

/* FAIL
 * Without GLSL 1.40 or GL_ARB_shader_texture_lod, the "Lod" versions of the
 * texture lookup functions are not available in fragment shaders.
 */
uniform sampler1D s;
varying float coord;
varying float lod;

void main()
{
  gl_FragColor = texture1DLod(s, coord, lod);
}
