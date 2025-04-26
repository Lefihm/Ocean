#include "Event.hpp"

namespace Ocean {

    Event::Event(EventLevel level) :
        m_Level(level),
        m_IsHandled(false)
    {
        
    }

    Event::~Event()
    {
        
    }

}   // Ocean
