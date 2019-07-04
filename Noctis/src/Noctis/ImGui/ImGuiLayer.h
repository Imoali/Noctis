#pragma once
#include "Noctis/Layer.h"

#include "Noctis/Events/ApplicationEvent.h"
#include "Noctis/Events/KeyEvent.h"
#include "Noctis/Events/MouseEvent.h"

namespace Noctis {

	class NOCTIS_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		
		void begin();
		void end();
	private:
		float m_Time = 0.0f;
	};

}