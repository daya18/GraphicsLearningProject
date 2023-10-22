# CMakeList.txt : CMake project for GraphicsLearningProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.26)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("GraphicsLearningProject")

set ( CMAKE_CXX_STANDARD 20 )

set ( BUILD_SHARED_LIBS FALSE )

# Add ASSIMP
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "Build Assimp command line tools")
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Build Assimp tests")
set(ASSIMP_BUILD_TESTS_GLTF OFF CACHE BOOL "Build Assimp tests for glTF format")
set(ASSIMP_INSTALL OFF CACHE BOOL "Install Assimp")

add_subdirectory ( external/assimp )

# ----------

# Add GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory ( external/glfw-3.3.8 )
# --------

# Add GLM
add_subdirectory ( external/glm )
# -------

# Add Freetype
add_subdirectory ( external/freetype-2.13.2 )
# ------------


# Add source to this project's executable.
add_executable ( GraphicsLearningProject )

target_precompile_headers (GraphicsLearningProject PUBLIC
	source/PCH.hpp
)

set_source_files_properties (external/glad/src/glad.c PROPERTIES LANGUAGE CXX )

target_include_directories ( GraphicsLearningProject PUBLIC
	include
	external/glad/include
	external
)

target_sources ( GraphicsLearningProject PRIVATE
	external/glad/src/glad.c

	source/main.cpp
	source/Application.cpp
	"source/OpenGL/Shader.cpp" 
	"source/OpenGL/VertexBuffer.cpp" 
	"source/OpenGL/VertexArray.cpp" 
	 
	"source/Scene/Scene.cpp" 
	"source/SceneRenderer.cpp" 
	"source/OpenGL/IndexBuffer.cpp"
	"source/Scene/Camera.cpp" 
	"source/OpenGL/UniformBuffer.cpp" 
	"source/Scene/Mesh.cpp"  
	"source/Window.cpp" 
	"source/Scene/Material.cpp"  
	"source/OpenGL/Texture.cpp" 
	"source/DebugRenderer.cpp" 
	"source/Scene/Light.cpp"  
	"source/Scene/Node.cpp" 
	"source/Utility.cpp" 
	"source/TestScenes.cpp"
	"source/OpenGL/Cubemap.cpp"  
	"source/OpenGL/Context.cpp" 
	"source/CameraController.cpp" 
	"source/Profiler.cpp"  
	"source/BoundingBox.cpp"
 "source/OpenGL/ShadowMap.cpp")

target_link_libraries (GraphicsLearningProject PRIVATE
	glfw
	glm
	freetype
	assimp
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GraphicsLearningProject PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
