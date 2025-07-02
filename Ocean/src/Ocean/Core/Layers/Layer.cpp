#include "Layer.hpp"

namespace Ocean {

#ifdef OC_DEBUG

    Layer::Layer(const String& name) : m_Enabled(true), m_DebugName(name) { }

#else

    Layer::Layer(OC_UNUSED const String& name) : m_Enabled(true) { }

#endif

}   // Ocean
