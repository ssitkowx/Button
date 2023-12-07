#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

namespace ButtonSpace
{
    enum class EState : uint8_t
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
        explicit Button (const ButtonSpace::Timeout vTimeout) : timeout (vTimeout) { }
        ~Button () = default;

        bool                IsTouched  (void) { return derivedType.IsTouched ();                                   }
        bool                IsHold     (void) { return (Event () == ButtonSpace::EState::Hold)     ? true : false; }
        bool                IsPressed  (void) { return (Event () == ButtonSpace::EState::Pressed)  ? true : false; }
        bool                IsReleased (void) { return (Event () == ButtonSpace::EState::Released) ? true : false; }
        ButtonSpace::EState Event      (void)
        {
            static ButtonSpace::EState state = ButtonSpace::EState::Untouched;
            static bool                isPressed;
            static uint8_t             timePressed;
            static uint8_t             timeReleased;

            if (IsTouched () == true)
            {
                if (isPressed == false)
                {
                    if (++timePressed == timeout.Hold)
                    {
                        isPressed   = true;
                        timePressed = ZERO;
                        state       = ButtonSpace::EState::Hold;
                    }
                    else { state = ButtonSpace::EState::Untouched; }
                }
                else { state = ButtonSpace::EState::Untouched; }

                timeReleased = ZERO;
            }
            else
            {
                if (timePressed >= timeout.Pressed && timePressed < timeout.Hold)
                {
                    isPressed   = true;
                    timePressed = ZERO;
                    timeReleased++;
                    return ButtonSpace::EState::Pressed;
                }

                if (isPressed == true)
                {
                    if (++timeReleased == timeout.Released)
                    {
                        isPressed    = false;
                        timeReleased = ZERO;
                        state        = ButtonSpace::EState::Released;
                    }
                    else { state = ButtonSpace::EState::Untouched; }
                }
                else { state = ButtonSpace::EState::Untouched; }

                timePressed = ZERO;
            }

            return state;
        }

    private:
        const ButtonSpace::Timeout timeout;
};
///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////