#include <gtest/gtest.h>
#include <utility>

#include <CEngine/event/AbstractEvent.hh>

TEST( TestAbstractEvent, getEventTypeID ) {

    using namespace concussion::event;

    EventTypeID id = 3;
    AbstractEvent base( id );
    ASSERT_EQ( base.getEventTypeID(), id );
}

TEST( TestAbstractEvent, getTimeCreated ) {

    using namespace concussion::event;

    EventTimestamp time;
    EventTypeID id = 3;
    AbstractEvent base( id );
    ASSERT_EQ( base.getTimeCreated(), time );
}
