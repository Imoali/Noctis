#pragma once

#include "Event.h"
#include <sstream>

namespace Noctis {

	class NOCTIS_API WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(unsigned int x, unsigned int y): m_Width(x), m_Height(y){}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();	
		}

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowResize)
	private:
		unsigned int m_Width, m_Height;
	};

	class NOCTIS_API WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowClose)
	};

	class NOCTIS_API AppTickEvent : public Event {
	public:
		AppTickEvent() {}
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(AppTick)
	};

	class NOCTIS_API AppUpdateEvent : public Event {
	public:
		AppUpdateEvent() {}
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
			EVENT_CLASS_TYPE(AppUpdate)
	};

	class NOCTIS_API AppRenderEvent : public Event {
	public:
		AppRenderEvent() {}
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
			EVENT_CLASS_TYPE(AppRender)
	};
}