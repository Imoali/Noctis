#pragma once
#include "Noctis/Input.h"

namespace Noctis {
	class NOCTIS_API WindowsInput : public Input {
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual std::pair<float, float> GetMousePosImpl() override; 
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}