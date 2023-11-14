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

TEST_F (ButtonFixture, CheckIfButtonIsShortPressedAndReleased)
{
    LOGW (MODULE, "CheckIfButtonIsShortPressed");

    Sequence seq;
    for (uint8_t pressedNum = ZERO; pressedNum < ButtonFixture::Timeout.Pressed.Short; pressedNum++)
    {
        EXPECT_CALL (oButtonHw, IsTouched ()).InSequence (seq).WillOnce (Return (true));
    }

    for (uint8_t releasedNum = ZERO; releasedNum < ButtonFixture::Timeout.Released; releasedNum++)
    {
        EXPECT_CALL (oButtonHw, IsTouched ()).InSequence (seq).WillOnce (Return (false));
    }

    ButtonSpace::EState state = ButtonSpace::EState::Untouched;
    for (uint8_t eventNum = ZERO; eventNum < ButtonFixture::Timeout.Pressed.Short; eventNum++)
    {
        state = oButtonHw.Event ();
        EXPECT_EQ (ButtonSpace::EState::Untouched, state);
    }

    state = ButtonSpace::EState::Untouched;
    for (uint8_t eventNum = ZERO; eventNum < ButtonFixture::Timeout.Released; eventNum++)
    {
        if (eventNum == ZERO) 
        {
            state = oButtonHw.Event ();
            EXPECT_EQ (ButtonSpace::EState::ShortPressed, state);
        }
        else if (eventNum ==(ButtonFixture::Timeout.Released - ONE))
        {
            state = oButtonHw.Event ();
            EXPECT_EQ (ButtonSpace::EState::Released, state);
        }
        else
        {
            state = oButtonHw.Event ();
            EXPECT_EQ (ButtonSpace::EState::Untouched, state);
        }
    }
}

TEST_F (ButtonFixture, CheckIfButtonIsLongPressedAndReleased)
{
    LOGW (MODULE, "CheckIfButtonIsLongPressedAndReleased");

    Sequence seq;
    for (uint8_t pressedNum = ZERO; pressedNum < ButtonFixture::Timeout.Pressed.Long; pressedNum++)
    {
        EXPECT_CALL (oButtonHw, IsTouched ()).InSequence (seq).WillOnce (Return (true));
    }

    for (uint8_t releasedNum = ZERO; releasedNum < ButtonFixture::Timeout.Released; releasedNum++)
    {
        EXPECT_CALL (oButtonHw, IsTouched ()).InSequence (seq).WillOnce (Return (false));
    }

    ButtonSpace::EState state = ButtonSpace::EState::Untouched;
    for (uint8_t eventNum = ZERO; eventNum < ButtonFixture::Timeout.Pressed.Long; eventNum++)
    {

        if (eventNum ==(ButtonFixture::Timeout.Released - ONE))
        {
            state = oButtonHw.Event ();
            EXPECT_EQ (ButtonSpace::EState::LongPressed, state);
        }
        else
        {
            state = oButtonHw.Event ();
            EXPECT_EQ (ButtonSpace::EState::Untouched, state);
        }
    }

    state = ButtonSpace::EState::Untouched;
    for (uint8_t eventNum = ZERO; eventNum < ButtonFixture::Timeout.Released; eventNum++)
    {
        if (eventNum ==(ButtonFixture::Timeout.Released - ONE))
        {
            state = oButtonHw.Event ();
            EXPECT_EQ (ButtonSpace::EState::Released, state);
        }
        else
        {
            state = oButtonHw.Event ();
            EXPECT_EQ (ButtonSpace::EState::Untouched, state);
        }
    }
}

TEST_F (ButtonFixture, CheckIfButtonIsReleased)
{
    LOGW (MODULE, "CheckIfButtonIsReleased");

    EXPECT_CALL (oButtonHw, IsTouched ()).WillRepeatedly (Return (true));

    Sequence seq;
    for (uint8_t pressedNum = ZERO; pressedNum < ButtonFixture::Timeout.Pressed.Long; pressedNum++)
    {
        EXPECT_CALL (oButtonHw, IsTouched ()).InSequence (seq).WillOnce (Return (true));
    }

    for (uint8_t releasedNum = ZERO; releasedNum < ButtonFixture::Timeout.Released; releasedNum++)
    {
        EXPECT_CALL (oButtonHw, IsTouched ()).InSequence (seq).WillOnce (Return (false));
    }

    ButtonSpace::EState state = ButtonSpace::EState::Untouched;
    for (uint8_t eventNum = ZERO; eventNum < ButtonFixture::Timeout.Pressed.Long; eventNum++)
    {
        ASSERT_EQ (ButtonSpace::EState::Untouched, state);
        state = oButtonHw.Event ();
    }

    ASSERT_EQ (ButtonSpace::EState::LongPressed, state);

    state = ButtonSpace::EState::Untouched;
    for (uint8_t eventNum = ZERO; eventNum < ButtonFixture::Timeout.Released; eventNum++)
    {
        ASSERT_EQ (ButtonSpace::EState::Untouched, state);
        state = oButtonHw.Event ();
    }

    ASSERT_EQ (ButtonSpace::EState::Released, state);
}

TEST_F (ButtonFixture, CheckIfButtonIsUntouchedAfterTooShortTimePressed)
{
    LOGW (MODULE, "CheckIfButtonIsUntouchedAfterTooShortTimePressed");

    EXPECT_CALL (oButtonHw, IsTouched ()).WillRepeatedly (Return (true));

    ButtonSpace::EState state = ButtonSpace::EState::Untouched;
    for (uint8_t eventNum = ZERO; eventNum < ButtonFixture::Timeout.Pressed.Long - ONE; eventNum++)
    {
        EXPECT_EQ (ButtonSpace::EState::Untouched, state);
        state = oButtonHw.Event ();
    }

    ASSERT_EQ (ButtonSpace::EState::Untouched, state);
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////