#include "Application.hpp"

#include "Ocean/Core/Assert.hpp"

namespace Ocean {

    #define FixedTimestep 0.02f

    Application::Application(OC_UNUSED const ApplicationConfig& config) :
        m_LayerStack(),
        m_LastFrameTime(0.0f),
        m_Accumulator(0.0f),
        m_Running(false)
    {
        OASSERTM(!s_Instance, "Application already exists!");
        s_Instance = this;
    }

    Application::~Application() {
    }

    void Application::Close() {
        this->m_Running = false;
    }

    void Application::PushLayer(Layer* layer) {
        this->m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer) {
        this->m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::Run() {
        this->m_Running = true;

        // Temporary
        Timestep time(0.0f);
        u32 accumulatorCounter = 0;
        u32 frameCount = 0;

        while (this->m_Running) {
            Timestep t(oTimeNow());
            Timestep timeStep(t - this->m_LastFrameTime);
            this->m_LastFrameTime = t;

            this->m_Accumulator += timeStep;
            time += timeStep;

            if (time.GetSeconds() >= 5.0f ) {
                time -= 5.0f;
                oprint("Frames per 5 seconds: %i (%f fps)\n", frameCount, frameCount / 5.0f);
                oprint("Fixed Updates per 5 seconds: %i (%f ups)\n", accumulatorCounter, accumulatorCounter / 5.0f);
                frameCount = accumulatorCounter = 0;
            }

            // // if (!this->m_Window->IsMinimized()) {
            // //     // p_Renderer->BeginFrame();
            // // }

            FrameBegin();

            while (this->m_Accumulator.GetSeconds() >= FixedTimestep) {
                // TODO: Interpolation (For Physics Engine and Renderer)
                FixedUpdate(FixedTimestep);

                accumulatorCounter++;

                this->m_Accumulator -= FixedTimestep;
            }

            if (true) {
                VariableUpdate(timeStep);

            //     // TODO: Interpolation
                Render(f32());
            }
            // // p_Renderer->EndFrame();

            FrameEnd();

            // this->m_Window->OnUpdate();

            frameCount++;

            if (frameCount >= 100)
                Close();
        }
    }

    void Application::FixedUpdate(OC_UNUSED Timestep delta) {

    }
    void Application::VariableUpdate(OC_UNUSED Timestep delta) {
        for (Layer* layer : this->m_LayerStack)
            layer->OnUpdate(delta);
    }
    
    void Application::FrameBegin() {
        
    }
    void Application::Render(OC_UNUSED f32 interpolation) {
        
    }
    void Application::FrameEnd() {
        
    }

    void Application::OnResize(u16 width, u16 height) {
        // Renderer::OnWindowResize(width, height);
    }

}    // Ocean
