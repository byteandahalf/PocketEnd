#pragma once

#include "Dimension.h"

struct NormalDimension
: public Dimension
{
	NormalDimension(Level&);

	virtual void init();
	virtual const std::string getName() const;
};
