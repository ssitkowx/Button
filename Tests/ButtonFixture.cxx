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
    LOGW (MODULE, "CheckIfButtonIsPressedAndReleased");

    Sequence seq;
    bool     isTouched = true;

    for (uint8_t pressedNum = ZERO; pressedNum < ButtonFixture::Timeout.Pressed + ButtonFixture::Timeout.Released; pressedNum++)
    {
        if (pressedNum == ButtonFixture::Timeout.Pressed) { isTouched = false; }

        EXPECT_CALL (oButtonHw, IsTouched ()).InSequence (seq).WillOnce (Return (isTouched));
    }

    for (uint8_t pressedNum = ZERO; pressedNum < ButtonFixture::Timeout.Pressed; pressedNum++)
    {
        oButtonHw.Process ();
    }

    EXPECT_TRUE (oButtonHw.IsPressed ());

    for (uint8_t releasedNum = ZERO; releasedNum < ButtonFixture::Timeout.Released; releasedNum++)
    {
        oButtonHw.Process ();
    }

    EXPECT_TRUE (oButtonHw.IsReleased ());
}

TEST_F (ButtonFixture, CheckIfButtonIsHoldAndReleased)
{
    LOGW (MODULE, "CheckIfButtonIsHoldAndReleased");

    Sequence seq;
    bool     isTouched = true;

    for (uint8_t pressedNum = ZERO; pressedNum < ButtonFixture::Timeout.Hold + ButtonFixture::Timeout.Released; pressedNum++)
    {
        if (pressedNum == ButtonFixture::Timeout.Hold) { isTouched = false; }

        EXPECT_CALL (oButtonHw, IsTouched ()).InSequence (seq).WillOnce (Return (isTouched));
    }

    for (uint8_t holdNum = ZERO; holdNum < ButtonFixture::Timeout.Hold; holdNum++)
    {
        oButtonHw.Process ();
    }

    EXPECT_TRUE (oButtonHw.IsHold ());

    for (uint8_t releasedNum = ZERO; releasedNum < ButtonFixture::Timeout.Released; releasedNum++)
    {
        oButtonHw.Process ();
    }

    EXPECT_TRUE (oButtonHw.IsReleased ());
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
