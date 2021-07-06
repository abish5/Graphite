#pragma once

#include "gppch.h"
#include "Layer.h"

namespace Graphite {

	Layer::Layer(const std::string& debugName)
		: m_DebugName(debugName)
	{}

	Layer::~Layer()
	{}
} 