//
// Created by Eddie Hoyle on 31/05/18.
//

#ifndef CONCUSSION_EVENTS_HH
#define CONCUSSION_EVENTS_HH

#include <CEngine/event/Event.hh>

struct KeyDownEvent : public concussion::event::Event< KeyDownEvent > {
    KeyDownEvent( int key ) : key( key ) {}
    int key;
};

struct KeyUpEvent : public concussion::event::Event< KeyUpEvent > {
    KeyUpEvent( int key ) : key( key ) {}
    int key;
};


#endif //CONCUSSION_EVENTS_HH
