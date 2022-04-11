#include <PrecompiledHeader.h>

#include "GMaterial.h"

namespace GameWorld
{
	GMaterial::GMaterial(const std::string& name)
		: m_name(name)
	{

	}

	GMaterial::GMaterial(const std::string& name, MTransform& transform, MaterialConstant& constant)
		: m_name(name), m_transform(transform), m_constant(constant)
	{

	}

}