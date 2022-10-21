#pragma once

#include <sstream>
#include "Event.h"
#include <map>

class KeyEvent: public Event
{
public:
    inline int getKeyCode() const { return m_KeyCode; }

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
protected:
    KeyEvent(int keyCode)
        : m_KeyCode(keyCode)
    {
    }
    int m_KeyCode;

};

class KeyDownEvent : public KeyEvent
{
public:
    KeyDownEvent(int keyCode, bool repeated)
        : KeyEvent(keyCode), m_Repeated(repeated) {}
    inline bool getKeyRepeated(){ return m_Repeated; }

    std::string toString() const override
    {
        std::stringstream stringStream;
        stringStream << "KeyDown Event: " << m_KeyCode << ", repeated: " << m_Repeated;
        return stringStream.str();
    }

    EVENT_CLASS_TYPE(KeyPress)
private:
    bool m_Repeated;
};

class KeyUpEvent : public KeyEvent
{
public:
    KeyUpEvent(int keyCode)
        : KeyEvent(keyCode) {}

    std::string toString() const override
    {
        std::stringstream stringStream;
        stringStream << "KeyUp Event: " << m_KeyCode;
        return stringStream.str();
    }

    EVENT_CLASS_TYPE(KeyUp)
};


// Key codes modelled after mozilla html5/windows (US) codes
static int convertHtmlToWindowsKeyCode(std::string keyCode)
{
    std::map<std::string, int> keyCodesHtml;
    keyCodesHtml.insert(std::make_pair("Tab", 9));
    keyCodesHtml.insert(std::make_pair("Enter", 13));
    keyCodesHtml.insert(std::make_pair("ShiftLeft", 16));
    keyCodesHtml.insert(std::make_pair("ShiftRight", 16));
    keyCodesHtml.insert(std::make_pair("ControlLeft", 17));
    keyCodesHtml.insert(std::make_pair("ControlRight", 17));
    keyCodesHtml.insert(std::make_pair("AltLeft", 18));
    keyCodesHtml.insert(std::make_pair("AltRight", 18));
    keyCodesHtml.insert(std::make_pair("Escape", 27));
    keyCodesHtml.insert(std::make_pair("Space", 32));

    keyCodesHtml.insert(std::make_pair("ArrowLeft", 37));
    keyCodesHtml.insert(std::make_pair("ArrowUp", 38));
    keyCodesHtml.insert(std::make_pair("ArrowRight", 39));
    keyCodesHtml.insert(std::make_pair("ArrowDown", 40));

    keyCodesHtml.insert(std::make_pair("Digit0", 48));
    keyCodesHtml.insert(std::make_pair("Digit1", 49));
    keyCodesHtml.insert(std::make_pair("Digit2", 50));
    keyCodesHtml.insert(std::make_pair("Digit3", 51));
    keyCodesHtml.insert(std::make_pair("Digit4", 52));
    keyCodesHtml.insert(std::make_pair("Digit5", 53));
    keyCodesHtml.insert(std::make_pair("Digit6", 54));
    keyCodesHtml.insert(std::make_pair("Digit7", 55));
    keyCodesHtml.insert(std::make_pair("Digit8", 56));
    keyCodesHtml.insert(std::make_pair("Digit9", 57));

    keyCodesHtml.insert(std::make_pair("KeyA", 65));
    keyCodesHtml.insert(std::make_pair("KeyB", 66));
    keyCodesHtml.insert(std::make_pair("KeyC", 67));
    keyCodesHtml.insert(std::make_pair("KeyD", 68));
    keyCodesHtml.insert(std::make_pair("KeyE", 69));
    keyCodesHtml.insert(std::make_pair("KeyF", 70));
    keyCodesHtml.insert(std::make_pair("KeyG", 71));
    keyCodesHtml.insert(std::make_pair("KeyH", 72));
    keyCodesHtml.insert(std::make_pair("KeyI", 73));
    keyCodesHtml.insert(std::make_pair("KeyJ", 74));
    keyCodesHtml.insert(std::make_pair("KeyK", 75));
    keyCodesHtml.insert(std::make_pair("KeyL", 76));
    keyCodesHtml.insert(std::make_pair("KeyM", 77));
    keyCodesHtml.insert(std::make_pair("KeyN", 78));
    keyCodesHtml.insert(std::make_pair("KeyO", 79));
    keyCodesHtml.insert(std::make_pair("KeyP", 80));
    keyCodesHtml.insert(std::make_pair("KeyQ", 81));
    keyCodesHtml.insert(std::make_pair("KeyR", 82));
    keyCodesHtml.insert(std::make_pair("KeyS", 83));
    keyCodesHtml.insert(std::make_pair("KeyT", 84));
    keyCodesHtml.insert(std::make_pair("KeyU", 85));
    keyCodesHtml.insert(std::make_pair("KeyV", 86));
    keyCodesHtml.insert(std::make_pair("KeyW", 87));
    keyCodesHtml.insert(std::make_pair("KeyX", 88));
    keyCodesHtml.insert(std::make_pair("KeyY", 89));
    keyCodesHtml.insert(std::make_pair("KeyZ", 90));

    keyCodesHtml.insert(std::make_pair("Numpad0", 96));
    keyCodesHtml.insert(std::make_pair("Numpad1", 97));
    keyCodesHtml.insert(std::make_pair("Numpad2", 98));
    keyCodesHtml.insert(std::make_pair("Numpad3", 99));
    keyCodesHtml.insert(std::make_pair("Numpad4", 100));
    keyCodesHtml.insert(std::make_pair("Numpad5", 101));
    keyCodesHtml.insert(std::make_pair("Numpad6", 102));
    keyCodesHtml.insert(std::make_pair("Numpad7", 103));
    keyCodesHtml.insert(std::make_pair("Numpad8", 104));
    keyCodesHtml.insert(std::make_pair("Numpad9", 105));
    keyCodesHtml.insert(std::make_pair("NumpadAdd", 107));

    keyCodesHtml.insert(std::make_pair("Comma", 188));
    keyCodesHtml.insert(std::make_pair("Minus", 189));
    keyCodesHtml.insert(std::make_pair("Period", 190));

    return 0;
}
