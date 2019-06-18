#pragma once

#include "Event.h"


namespace Noctis {

	class NOCTIS_API KeyEvent : public Event {
	public:
		inline int GetKeyCode() const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode) 
			: m_KeyCode(keycode) {}
		int m_KeyCode;
	};

	class NOCTIS_API KeyPressedEvent : public KeyEvent {
	public:
		//the class constructor uses a keycode and a repeat coounter
		KeyPressedEvent(int keycode, int repeatCount): KeyEvent(keycode), m_RepeatCount(repeatCount){}
		//repeat count getter
		inline int GetRepeatCount() const { return m_RepeatCount; }
		//return the string representation of the event 
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent:" << m_KeyCode << "(" << m_RepeatCount << ") repeats";
			return ss.str();
		}
		//macro used to get the event type
		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};	

	class NOCTIS_API KeyTypedEvent : public KeyEvent {
	public:
		//the class constructor uses a keycode and a repeat coounter
		KeyTypedEvent(int keycode) : KeyEvent(keycode) {}
		//repeat count getter
		//return the string representation of the event 
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyTypedEvent:" << m_KeyCode ;
			return ss.str();
		}
		//macro used to get the event type
		EVENT_CLASS_TYPE(KeyTyped)
	};

	class NOCTIS_API KeyReleasedEvent : public KeyEvent {
	public:
		//the class constructor uses a keycode 
		KeyReleasedEvent(int keycode ) : KeyEvent(keycode){}
		//return the string representation of the event 
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent:" << m_KeyCode ;
			return ss.str();
		}
		//macro used to get the event type
		EVENT_CLASS_TYPE(KeyReleased)
	};
}