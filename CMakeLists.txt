cmake_minimum_required(VERSION 3.25)
project(
	ChromaRave
	VERSION 0.1.0
	LANGUAGES C
)

set(CMAKE_C_STANDARD          23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS        OFF)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CR_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")
set(CR_ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Assets")
set(CR_VENDOR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Vendor")

set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON  CACHE BOOL "" FORCE)
add_subdirectory(
	"${CR_VENDOR_DIR}/SDL"
	EXCLUDE_FROM_ALL SYSTEM
)

add_subdirectory(
	"${CR_VENDOR_DIR}/glad"
	EXCLUDE_FROM_ALL SYSTEM
)

set(CGLM_STATIC ON  CACHE BOOL "" FORCE)
set(CGLM_SHARED OFF CACHE BOOL "" FORCE)
add_subdirectory(
	"${CR_VENDOR_DIR}/cglm"
	EXCLUDE_FROM_ALL SYSTEM
)

add_executable(ChromaRave)
set_target_properties(
	ChromaRave PROPERTIES
	OUTPUT_NAME "ChromaRave"
)
file(
	GLOB_RECURSE ChromaRave_SOURCES
	CONFIGURE_DEPENDS
	"${CR_SOURCE_DIR}/*.c"
)
target_sources(
	ChromaRave PRIVATE
	${ChromaRave_SOURCES}
)
target_include_directories(
	ChromaRave PRIVATE
	${CR_SOURCE_DIR}
)
target_compile_options(
	ChromaRave PRIVATE
	"--embed-dir=${CR_ASSETS_DIR}"
)
target_link_libraries(
	ChromaRave PRIVATE
	SDL3::SDL3
	glad
	cglm
)
install(
	FILES
		$<TARGET_FILE:ChromaRave>
	DESTINATION
		"."
)

