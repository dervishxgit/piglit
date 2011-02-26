if (MSVC)
	add_definitions ( -D__WIN__ -D__MS__ )
ELSEIF (APPLE)
	add_definitions ( -D__AGL__ -D__UNIX__ )
	FIND_LIBRARY(CARBON_LIBRARY Carbon)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
	SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m32")
ELSE ()
	add_definitions ( -D__X11__ -D__UNIX__ )
ENDIF ()

include_directories(
	${OPENGL_INCLUDE_PATH}
	${TIFF_INCLUDE_DIR}
)

add_executable (glean
	codedid.cpp
	dsconfig.cpp
	dsfilt.cpp
	dsurf.cpp
	environ.cpp
	geomrend.cpp
	geomutil.cpp
	glutils.cpp
	main.cpp
	misc.cpp
	options.cpp
	rc.cpp
	tapi2.cpp
	tbasic.cpp
	tbasicperf.cpp
	tbinding.cpp
	tblend.cpp
	tbufferobject.cpp
	tchgperf.cpp
	tclipflat.cpp
	tdepthstencil.cpp
	test.cpp
	tfbo.cpp
	tfpexceptions.cpp
	tfragprog1.cpp
	tgetstr.cpp
	tglsl1.cpp
	tlogicop.cpp
	tmaskedclear.cpp
	tmultitest.cpp
	toccluqry.cpp
	torthpos.cpp
	tpaths.cpp
	tpbo.cpp
	tpgos.cpp
	tpixelformats.cpp
	tpointatten.cpp
	tpointsprite.cpp
	treadpix.cpp
	treadpixperf.cpp
	trgbtris.cpp
	tscissor.cpp
	tshaderapi.cpp
	tstencil2.cpp
	tteapot.cpp
	ttexcombine.cpp
	ttexcombine4.cpp
	ttexcube.cpp
	ttexenv.cpp
	ttexgen.cpp
	ttexrect.cpp
	ttexswizzle.cpp
	ttexture_srgb.cpp
	ttexunits.cpp
	tvertarraybgra.cpp
	tvertattrib.cpp
	tvertprog1.cpp
	tvtxperf.cpp
	winsys.cpp
	gl.cpp
	image_misc.cpp
	pack.cpp
	rdtiff.cpp
	reg.cpp
	unpack.cpp
	wrtiff.cpp
	basic.cpp
	lex.cpp
	timer.cpp
)

target_link_libraries (glean
	${OPENGL_gl_LIBRARY}
	${OPENGL_glu_LIBRARY}
	${GLUT_glut_LIBRARY}
	${X11_X11_LIB}
	${TIFF_LIBRARY}
	${CARBON_LIBRARY}
)