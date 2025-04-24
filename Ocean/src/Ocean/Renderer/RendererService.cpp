#include "RendererService.hpp"

namespace Ocean {

    RendererService::RendererService() :
        RuntimeService()
    {
        if (!s_Instance)
            s_Instance = this;
    }

    RendererService::~RendererService()
    {
        
    }

    void RendererService::Init() {
        
    }

    void RendererService::Shutdown() {
        
    }



}   // Ocean
