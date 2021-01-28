cmake_minimum_required(VERSION 3.6)
project(stb)

set(HEADER_LIST
	"${PROJECT_SOURCE_DIR}/stb.h"
	"${PROJECT_SOURCE_DIR}/stb_c_lexer.h"
	"${PROJECT_SOURCE_DIR}/stb_connected_components.h"
	"${PROJECT_SOURCE_DIR}/stb_divide.h"
	"${PROJECT_SOURCE_DIR}/stb_ds.h"
	"${PROJECT_SOURCE_DIR}/stb_dxt.h"
	"${PROJECT_SOURCE_DIR}/stb_easy_font.h"
	"${PROJECT_SOURCE_DIR}/stb_herringbone_wang_tile.h"
	"${PROJECT_SOURCE_DIR}/stb_image.h"
	"${PROJECT_SOURCE_DIR}/stb_image_resize.h"
	"${PROJECT_SOURCE_DIR}/stb_image_write.h"
	"${PROJECT_SOURCE_DIR}/stb_include.h"
	"${PROJECT_SOURCE_DIR}/stb_leakcheck.h"
	"${PROJECT_SOURCE_DIR}/stb_perlin.h"
	"${PROJECT_SOURCE_DIR}/stb_rect_pack.h"
	"${PROJECT_SOURCE_DIR}/stb_sprintf.h"
	"${PROJECT_SOURCE_DIR}/stb_textedit.h"
	"${PROJECT_SOURCE_DIR}/stb_tilemap_editor.h"
	"${PROJECT_SOURCE_DIR}/stb_truetype.h"
	"${PROJECT_SOURCE_DIR}/stb_voxel_render.h"
	"${PROJECT_SOURCE_DIR}/stretchy_buffer.h")

add_library(stb STATIC
	stb_vorbis.c
	${HEADER_LIST})
