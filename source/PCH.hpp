#pragma once

#include <cstdlib>
#include <array>
#include <vector>
#include <iostream>
#include <string>
#include <initializer_list>
#include <fstream>
#include <sstream>
#include <memory>
#include <map>
#include <unordered_map>
#include <functional>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <filesystem>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <stb_image.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/camera.h>
#include <assimp/mesh.h>
#include <assimp/material.h>
#include <assimp/texture.h>