set(EXE_FILE "rpforest.exe")

file(GLOB_RECURSE ALL_SRC
    "*.h"
    "*.cpp"
    "*.H"
    "*.C"	
)

include_directories(utils)
include_directories(engine)
include_directories(engine/materials)
include_directories(rendering)
include_directories(rendering/ASky)
include_directories(generating)
include_directories(generating/configs)
include_directories(generating/lsystems)
include_directories(generating/lsystems/honda)
include_directories(generating/lsystems/ternary)
include_directories(generating/lsystems/family)

add_executable(${EXE_FILE} ${ALL_SRC})

set(embree_DIR /home/bartosz/Downloads/embree-3.6.1.x86_64.linux)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(embree 3.0 REQUIRED)

include_directories(${EMBREE_INCLUDE_DIRS})
include_directories(/usr/local/include/OpenEXR)


target_link_libraries(${EXE_FILE} GLEW ${OPENGL_gl_LIBRARY} glfw ${EMBREE_LIBRARY} IlmImf Imath Half Iex IexMath IlmThread /home/bartosz/UWR/RPForest/lib/libcommon.a stdc++fs)

