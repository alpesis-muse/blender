
# ---------------------------------------------------------------------------------------

# find all dependency libraries:
find_package(OpenMP)
if (NOT OPENMP_FOUND)
	message(WARNING "OpenMP is not found. Will be slow.")
else()
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()


find_package(JPEG)
if(JPEG_FOUND)
	include_directories(${JPEG_INCLUDE_DIR})
endif()

find_package(Eigen3 REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third-party/)

# ---------------------------------------------------------------------------------------

# find sources
file(GLOB SOURCES feature/*.cc blender/*.cc lib/*.cc)

# ---------------------------------------------------------------------------------------

add_library(openblender ${SOURCES})	# TODO shared?
target_link_libraries(openblender ${JPEG_LIBRARY} lodepng Eigen3::Eigen)

add_executable(tests tests.cc)
target_link_libraries(tests openblender)

add_executable(blender blender.cc)
target_link_libraries(blender openblender)

# ---------------------------------------------------------------------------------------

if (NOT JPEG_FOUND)
	target_compile_definitions(openblender PUBLIC DISABLE_JPEG)
	target_compile_definitions(blender PUBLIC DISABLE_JPEG)
endif()

find_package(PythonLibs)
if(PYTHONLIBS_FOUND AND BUILD_SHARED_LIBS)
	add_library(pyopenblender SHARED python/pybind.cc)
	target_link_libraries(pyopenblender openblender pybind11)
	target_include_directories(pyopenblender SYSTEM
		PRIVATE ${PYTHON_INCLUDE_DIRS}
	)
endif()
