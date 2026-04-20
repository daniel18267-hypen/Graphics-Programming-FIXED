#pragma once

#include "Structures.h"

namespace MeshLoader
{
	Mesh* Load(const char* path);
	Mesh* LoadTextured(const char* path);
	Mesh* LoadAdvanced(const char* path);
};