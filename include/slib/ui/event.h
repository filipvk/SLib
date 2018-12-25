/*
 *   Copyright (c) 2008-2018 SLIBIO <https://github.com/SLIBIO>
 *
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *   THE SOFTWARE.
 */

#ifndef CHECKHEADER_SLIB_UI_EVENT
#define CHECKHEADER_SLIB_UI_EVENT

#include "definition.h"

#include "constants.h"
#include "gesture.h"

#include "../core/string.h"
#include "../core/time.h"
#include "../math/point.h"
#include "../math/size.h"
#include "../math/matrix3.h"

namespace slib
{

	class Window;
	class View;

	class SLIB_EXPORT TouchPoint
	{
	public:
		UIPointf point;
		sl_real pressure;
		TouchPhase phase;

	public:
		TouchPoint();

		TouchPoint(const TouchPoint& other);
		
		TouchPoint(const UIPointf& point);
		
		TouchPoint(const UIPointf& point, sl_real pressure);
		
		TouchPoint(const UIPointf& point, sl_real pressure, TouchPhase phase);
		
		TouchPoint(sl_ui_posf x, sl_ui_posf y);
		
		TouchPoint(sl_ui_posf x, sl_ui_posf y, sl_real pressure);
		
		TouchPoint(sl_ui_posf x, sl_ui_posf y, sl_real pressure, TouchPhase phase);
		
	public:
		TouchPoint& operator=(const TouchPoint& other);

	};

	template<>
	class Hash<Keycode>
	{
	public:
		constexpr sl_size operator()(const Keycode& code) const
		{
			return Rehash32((sl_uint32)code);
		}
		
	};

	class SLIB_EXPORT KeycodeAndModifiers
	{
	public:
		int value;
		SLIB_MEMBERS_OF_PRIMITIVE_WRAPPER(KeycodeAndModifiers, int, value)
		
	public:
		constexpr KeycodeAndModifiers() : value(0) {}
		
		constexpr KeycodeAndModifiers(Keycode keycode) : value((int)keycode) {}
		
		constexpr KeycodeAndModifiers(Keycode keycode, const Modifiers& modifiers) : value((int)keycode | modifiers) {}

	public:
		static KeycodeAndModifiers none();
		
		Keycode getKeycode() const;
		
		void setKeycode(Keycode keycode);
		
		Modifiers getModifiers() const;
		
		void setModifiers(const Modifiers& modifiers);
		
		void setShiftKey();
		
		void clearShiftKey();
		
		sl_bool isShiftKey() const;
		
		void setAltKey();
		
		void clearAltKey();
		
		sl_bool isAltKey() const;
		
		void setOptionKey();
		
		void clearOptionKey();
		
		sl_bool isOptionKey() const;
		
		void setControlKey();
		
		void clearControlKey();
		
		sl_bool isControlKey() const;
		
		void setWindowsKey();
		
		void clearWindowsKey();
		
		sl_bool isWindowsKey() const;
		
		void setCommandKey();
		
		void clearCommandKey();
		
		sl_bool isCommandKey() const;

		String toString() const;
		
		sl_bool parse(const String& str);
		
	public:
		KeycodeAndModifiers& operator|=(int modifiers);
		
		KeycodeAndModifiers operator|(int modifiers);
		
		friend KeycodeAndModifiers operator|(int modifiers, const KeycodeAndModifiers& km);
		
	};

	KeycodeAndModifiers operator|(Keycode keycode, int modifiers);

	KeycodeAndModifiers operator|(int modifiers, Keycode keycode);


	class SLIB_EXPORT UIEvent : public Referable
	{	
	protected:
		UIEvent();
		
		~UIEvent();
		
	public:
		static Ref<UIEvent> create(UIAction action);
		
		static Ref<UIEvent> createKeyEvent(UIAction action, Keycode keycode, sl_uint32 systemKeycode, const Time& time);
		
		static Ref<UIEvent> createMouseEvent(UIAction action, sl_ui_posf x, sl_ui_posf y, const Time& time);
		
		static Ref<UIEvent> createMouseWheelEvent(sl_ui_posf mouseX, sl_ui_posf mouseY, sl_real deltaX, sl_real deltaY, const Time& time);
		
		static Ref<UIEvent> createTouchEvent(UIAction action, const Array<TouchPoint>& points, const Time& time);
		
		static Ref<UIEvent> createTouchEvent(UIAction action, const TouchPoint& point, const Time& time);
		
		static Ref<UIEvent> createSetCursorEvent(sl_ui_posf x, sl_ui_posf y, const Time& time);
		
	public:
		UIAction getAction() const;
		
		void setAction(UIAction action);
		
		sl_bool isKeyEvent() const;
		
		sl_bool isMouseEvent() const;
		
		sl_bool isTouchEvent() const;
		
		// Relative to a absolute time or to the system startup
		Time getTime() const;
		
		// Relative to a absolute time or to the system startup
		void setTime(const Time& time);
		
		// key
		const KeycodeAndModifiers& getKeycodeAndModifiers() const;
		
		void setKeycodeAndModifiers(const KeycodeAndModifiers& km);
		
		Keycode getKeycode() const;
		
		void setKeycode(Keycode keycode);
		
		Modifiers getModifiers() const;
		
		void setModifiers(const Modifiers& modifiers);

		sl_uint32 getSystemKeycode() const;
		
		void setSystemKeycode(sl_uint32 keycode);
		
		// mouse, touch
		const UIPointf& getPoint() const;
		
		void setPoint(const UIPointf& pt);
		
		void setPoint(sl_ui_posf x, sl_ui_posf y);
		
		sl_ui_posf getX() const;
		
		void setX(sl_ui_posf x);
		
		sl_ui_posf getY() const;
		
		void setY(sl_ui_posf y);
		
		// mouse wheel
		sl_real getDelta() const;
		
		void setDelta(sl_real delta);
		
		sl_real getDeltaX() const;
		
		void setDeltaX(sl_real x);
		
		sl_real getDeltaY() const;
		
		void setDeltaY(sl_real y);
		
		// touch
		const TouchPoint& getTouchPoint() const;
		
		void setTouchPoint(const TouchPoint& pt);
		
		void setTouchPoint(const UIPointf& pt);
		
		void setTouchPoint(const UIPointf& pt, sl_real pressure);
		
		void setTouchPoint(sl_ui_posf x, sl_ui_posf y);
		
		void setTouchPoint(sl_ui_posf x, sl_ui_posf y, sl_real pressure);
		
		sl_real getPressure() const;
		
		void setPressure(sl_real pressure);
		
		Array<TouchPoint> getTouchPoints() const;
		
		sl_uint32 getTouchPointsCount() const;
		
		TouchPoint getTouchPoint(sl_uint32 index) const;
		
		void setTouchPoints(const Array<TouchPoint>& points);

		void transformPoints(const Matrix3f& mat);
		
		void transformPoints(const Matrix3lf& mat);
		
		// modifiers
		void setShiftKey();
		
		void clearShiftKey();
		
		sl_bool isShiftKey() const;
		
		void setAltKey();
		
		void clearAltKey();
		
		sl_bool isAltKey() const;
		
		void setOptionKey();
		
		void clearOptionKey();
		
		sl_bool isOptionKey() const;
		
		void setControlKey();
		
		void clearControlKey();
		
		sl_bool isControlKey() const;
		
		void setWindowsKey();
		
		void clearWindowsKey();
		
		sl_bool isWindowsKey() const;
		
		void setCommandKey();
		
		void clearCommandKey();
		
		sl_bool isCommandKey() const;
		
		// event management
		void resetStates();
		
		void preventDefault();
		
		sl_bool isPreventedDefault() const;
		
		void setPreventedDefault(sl_bool flag);
		
		void stopPropagation();
		
		sl_bool isStoppedPropagation() const;
		
		void setStoppedPropagation(sl_bool flag);
		
		void passToNext();
		
		sl_bool isPassedToNext();
		
		void setPassedToNext(sl_bool flag);
				
		Ref<UIEvent> duplicate();
		
		static sl_uint32 getSystemKeycode(Keycode key);
		
		static Keycode getKeycodeFromSystemKeycode(sl_uint32 systemKeycode);
		
		static String getKeyName(Keycode key, sl_bool flagShort = sl_false);
		
		static Keycode getKeycodeFromName(const String& keyName);
		
	protected:
		sl_uint32 m_flags;
		UIAction m_action;
		Time m_time;
		
		// keyboard
		KeycodeAndModifiers m_keycodeAndModifiers;
		sl_uint32 m_systemKeycode;
		
		// mouse, touch, mouse wheel
		TouchPoint m_point;
		
		// mouse wheel
		sl_real m_deltaX;
		sl_real m_deltaY;
		
		// touch
		Array<TouchPoint> m_points;
		
	};

}

#endif
