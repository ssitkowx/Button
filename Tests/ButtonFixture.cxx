///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "LoggerHw.h"
#include "ButtonFixture.hxx"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

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
    for (uint8_t pressedNum = ZERO; pressedNum < ButtonFixture::Timeout.Pressed; pressedNum++)
    {
        EXPECT_CALL (oButtonHw, IsTouched ()).InSequence (seq).WillOnce (Return (true));
    }

    EXPECT_CALL (oButtonHw, IsTouched ()).InSequence (seq).WillOnce (Return (false));

    for (uint8_t pressedNum = ZERO; pressedNum < ButtonFixture::Timeout.Pressed; pressedNum++)
    {
        oButtonHw.Process ();
    }

    EXPECT_TRUE (oButtonHw.IsPressed ());

    oButtonHw.Process ();

    EXPECT_TRUE (oButtonHw.IsReleased ());
}

TEST_F (ButtonFixture, CheckIfButtonIsHoldAndReleased)
{
    LOGW (MODULE, "CheckIfButtonIsHoldAndReleased");

    Sequence seq;
    for (uint8_t holdNum = ZERO; holdNum < ButtonFixture::Timeout.Hold; holdNum++)
    {
        EXPECT_CALL (oButtonHw, IsTouched ()).InSequence (seq).WillOnce (Return (true));
    }

    EXPECT_CALL (oButtonHw, IsTouched ()).InSequence (seq).WillOnce (Return (false));

    for (uint8_t holdNum = ZERO; holdNum < ButtonFixture::Timeout.Hold; holdNum++)
    {
        oButtonHw.Process ();
    }

    EXPECT_TRUE (oButtonHw.IsHold ());

    oButtonHw.Process ();

    EXPECT_TRUE (oButtonHw.IsReleased ());
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////