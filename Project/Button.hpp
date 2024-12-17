#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.hpp"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

namespace ButtonSpace
{
    enum class EEvent : uint8_t
    {
        Hold,
        Pressed,
        Released,
        Untouched
    };

    struct Timeout
    {
        uint8_t Hold;
        uint8_t Pressed;
        uint8_t Released;
    };
}

template <class DERIVED_TYPE>
class Button
{
    friend DERIVED_TYPE;
    DERIVED_TYPE & derivedType = static_cast <DERIVED_TYPE &>(*this);

    public:
        ButtonSpace::EEvent Event = ButtonSpace::EEvent::Untouched;
        
        explicit Button (const ButtonSpace::Timeout vTimeout) : timeout (vTimeout) { }
        ~Button () = default;

        bool IsTouched  (void) { return derivedType.IsTouched ();                                }
        bool IsHold     (void) { return (Event == ButtonSpace::EEvent::Hold)     ? true : false; }
        bool IsPressed  (void) { return (Event == ButtonSpace::EEvent::Pressed)  ? true : false; }
        bool IsReleased (void) { return (Event == ButtonSpace::EEvent::Released) ? true : false; }
        void Process    (void)
        {
            if (IsTouched () == true)
            {
                if (state.IsPressed == false || state.IsHold == false)
                {
                    if (++state.Time.Pressed == timeout.Pressed)
                    {
                        state.IsPressed = true;
                        Event           = ButtonSpace::EEvent::Pressed;
                    }
                    else if (state.Time.Pressed == timeout.Hold)
                    {
                        state.IsHold       = true;
                        state.Time.Pressed = ZERO;
                        Event              = ButtonSpace::EEvent::Hold;
                    }
                    else { Event = ButtonSpace::EEvent::Untouched; }
                }
                else { Event = ButtonSpace::EEvent::Untouched; }

                state.Time.Released = ZERO;
            }
            else
            {
                if (state.IsPressed == true || state.IsHold == true)
                {
                    if (++state.Time.Released == timeout.Released)
                    {
                        state.IsHold        = false;
                        state.IsPressed     = false;
                        state.Time.Released = ZERO;
                        Event               = ButtonSpace::EEvent::Released;
                    }
                    else { Event = ButtonSpace::EEvent::Untouched; }
                }
                else { Event = ButtonSpace::EEvent::Untouched; }

                state.Time.Pressed = ZERO;
            }
        }

    private:
        const ButtonSpace::Timeout timeout;

        struct
        {
            bool IsHold;
            bool IsPressed;

            struct
            {
                uint8_t Pressed;
                uint8_t Released;
            } Time;
        } state = {};
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
