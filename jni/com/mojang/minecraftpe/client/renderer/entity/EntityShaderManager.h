#pragma once

struct Color;
struct Entity;
#include "../MaterialPtr.h"

struct EntityShaderManager
{
	mce::MaterialPtr _materials[3];

	EntityShaderManager();

	virtual ~EntityShaderManager();
	virtual const Color _getOverlayColor(Entity&, float) const;
};
