///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "LoggerHw.h"
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

TEST_F (ButtonFixture, CheckIfButtonIsReleased)
{
    LOGW (MODULE, "CheckIfButtonIsReleased");

    EXPECT_CALL (oButtonHw, isTouched ()).WillRepeatedly (Return (true));

    Sequence seq;
    for (uint8_t pressedNum = ZERO; pressedNum < ButtonFixture::TimeMax.Pressed; pressedNum++)
    {
        EXPECT_CALL (oButtonHw, isTouched ()).InSequence (seq).WillOnce (Return (true));
    }

    for (uint8_t releasedNum = ZERO; releasedNum < ButtonFixture::TimeMax.Released; releasedNum++)
    {
        EXPECT_CALL (oButtonHw, isTouched ()).InSequence (seq).WillOnce (Return (false));
    }

    ButtonSpace::EState state = ButtonSpace::EState::eUntouched;
    for (uint8_t eventNum = ZERO; eventNum < ButtonFixture::TimeMax.Pressed; eventNum++)
    {
        ASSERT_EQ (ButtonSpace::EState::eUntouched, state);
        state = oButtonHw.Event ();
    }

    ASSERT_EQ (ButtonSpace::EState::ePressed, state);

    state = ButtonSpace::EState::eUntouched;
    for (uint8_t eventNum = ZERO; eventNum < ButtonFixture::TimeMax.Released; eventNum++)
    {
        ASSERT_EQ (ButtonSpace::EState::eUntouched, state);
        state = oButtonHw.Event ();
    }

    ASSERT_EQ (ButtonSpace::EState::eReleased, state);
}

TEST_F (ButtonFixture, CheckIfButtonIsPressed)
{
    LOGW (MODULE, "CheckIfButtonIsPressed");

    EXPECT_CALL (oButtonHw, isTouched ()).WillRepeatedly (Return (true));

    ButtonSpace::EState state = ButtonSpace::EState::eUntouched;
    for (uint8_t eventNum = ZERO; eventNum < ButtonFixture::TimeMax.Pressed; eventNum++)
    {
        EXPECT_EQ (ButtonSpace::EState::eUntouched, state);
        state = oButtonHw.Event ();
    }

    ASSERT_EQ (ButtonSpace::EState::ePressed, state);
}

TEST_F (ButtonFixture, CheckIfButtonIsUntouchedAfterTooShortTimePressed)
{
    LOGW (MODULE, "CheckIfButtonIsUntouchedAfterTooShortTimePressed");

    EXPECT_CALL (oButtonHw, isTouched ()).WillRepeatedly (Return (true));

    ButtonSpace::EState state = ButtonSpace::EState::eUntouched;
    for (uint8_t eventNum = ZERO; eventNum < ButtonFixture::TimeMax.Pressed - ONE; eventNum++)
    {
        EXPECT_EQ (ButtonSpace::EState::eUntouched, state);
        state = oButtonHw.Event ();
    }

    ASSERT_EQ (ButtonSpace::EState::eUntouched, state);
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////