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
        ePressed,
        eReleased,
        eUntouched
    };

    struct Timeout
    {
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

        bool                IsTouched  (void) { return derivedType.IsTouched ();                                    }
        bool                IsPressed  (void) { return (Event () == ButtonSpace::EState::ePressed ) ? true : false; }
        bool                IsReleased (void) { return (Event () == ButtonSpace::EState::eReleased) ? true : false; }
        ButtonSpace::EState Event      (void)
        {
            static ButtonSpace::EState state = ButtonSpace::EState::eUntouched;
            static bool                isPressed;
            static uint8_t             timePressed;
            static uint8_t             timeReleased;

            if (IsTouched () == true)
            {
                if (isPressed == false)
                {
                    if (++timePressed == timeout.Pressed)
                    {
                        isPressed   = true;
                        timePressed = ZERO;
                        state       = ButtonSpace::EState::ePressed;
                    }
                    else { state = ButtonSpace::EState::eUntouched; }
                }
                else { state = ButtonSpace::EState::eUntouched; }

                timeReleased = ZERO;
            }
            else
            {
                if (isPressed == true)
                {
                    if (++timeReleased == timeout.Released)
                    {
                        isPressed    = false;
                        timeReleased = ZERO;
                        state        = ButtonSpace::EState::eReleased;
                    }
                    else { state = ButtonSpace::EState::eUntouched; }
                }
                else { state = ButtonSpace::EState::eUntouched; }

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