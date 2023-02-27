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

    struct TimeMax
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
        explicit Button (const ButtonSpace::TimeMax vTimeMax) : timeMax (vTimeMax) { }
        ~Button () = default;

        bool                IsPressed  (void) { return (Event () == ButtonSpace::EState::ePressed ) ? true : false; }
        bool                IsReleased (void) { return (Event () == ButtonSpace::EState::eReleased) ? true : false; }
        ButtonSpace::EState Event      (void)
        {
            static ButtonSpace::EState state     = ButtonSpace::EState::eUntouched;
            static bool                isPressed = false;
            static uint8_t             timePressed;
            static uint8_t             timeReleased;

            if (isTouched () == true)
            {
                if (isPressed == false)
                {
                    if (++timePressed == timeMax.Pressed)
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
                    if (++timeReleased == timeMax.Released)
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
        const ButtonSpace::TimeMax timeMax;

        bool isTouched  (void) { return derivedType.isTouched (); }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
