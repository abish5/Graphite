#pragma once
#include "Graphite/Input.h"

namespace Graphite {

	class WindowsInput : public Input
	{
	protected:
		WindowsInput();
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};

}

