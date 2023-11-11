// Copyright © 2023. GothicKit Contributors
// SPDX-License-Identifier: MIT
#pragma once
#include <stdint.h>

#ifdef __cplusplus
	#include <glm/vec2.hpp>
	#include <glm/vec3.hpp>
	#include <glm/vec4.hpp>
	#include <glm/ext/quaternion_float.hpp>
	#include <zenkit/Texture.hh>

using ZkVec2f = glm::vec2;
using ZkVec3f = glm::vec3;
using ZkVec4f = glm::vec4;
using ZkQuat = glm::quat;
using ZkColor = glm::u8vec4;
using ZkColorArgb = zenkit::ColorARGB;
#else

typedef struct {
	float x, y;
} ZkVec2f;

typedef struct {
	float x, y, z;
} ZkVec3f;

typedef struct {
	float x, y, z, w;
} ZkVec4f;

typedef struct {
	float x, y, z, w;
} ZkQuat;

typedef struct {
	uint8_t r, g, b, a;
} ZkColor;

typedef struct {
	uint8_t a, r, g, b;
} ZkColorArgb;

#endif