///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "LoggerHw.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ButtonFixture.hxx"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// VARIABLES ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

using ::testing::Return;
using ::testing::Sequence;

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEST_F (ButtonFixture, CheckIfButtonIsPressedAndReleased)
{
    LOGW (Module, "CheckIfButtonIsPressedAndReleased");

    Sequence seq;
    bool     isTouched = true;

    for (uint8_t pressedNum = 0; pressedNum < ButtonFixture::Timeout.Pressed + ButtonFixture::Timeout.Released; pressedNum++)
    {
        if (pressedNum == ButtonFixture::Timeout.Pressed) { isTouched = false; }

        EXPECT_CALL (oButtonHw, IsTouched ()).InSequence (seq).WillOnce (Return (isTouched));
    }

    for (uint8_t pressedNum = 0; pressedNum < ButtonFixture::Timeout.Pressed; pressedNum++)
    {
        oButtonHw.Process ();
    }

    EXPECT_TRUE (oButtonHw.IsPressed ());

    for (uint8_t releasedNum = 0; releasedNum < ButtonFixture::Timeout.Released; releasedNum++)
    {
        oButtonHw.Process ();
    }

    EXPECT_TRUE (oButtonHw.IsReleased ());
}

TEST_F (ButtonFixture, CheckIfButtonIsHoldAndReleased)
{
    LOGW (Module, "CheckIfButtonIsHoldAndReleased");

    Sequence seq;
    bool     isTouched = true;

    for (uint8_t pressedNum = 0; pressedNum < ButtonFixture::Timeout.Hold + ButtonFixture::Timeout.Released; pressedNum++)
    {
        if (pressedNum == ButtonFixture::Timeout.Hold) { isTouched = false; }

        EXPECT_CALL (oButtonHw, IsTouched ()).InSequence (seq).WillOnce (Return (isTouched));
    }

    for (uint8_t holdNum = 0; holdNum < ButtonFixture::Timeout.Hold; holdNum++)
    {
        oButtonHw.Process ();
    }

    EXPECT_TRUE (oButtonHw.IsHold ());

    for (uint8_t releasedNum = 0; releasedNum < ButtonFixture::Timeout.Released; releasedNum++)
    {
        oButtonHw.Process ();
    }

    EXPECT_TRUE (oButtonHw.IsReleased ());
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
