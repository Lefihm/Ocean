#include "Application.hpp"

#include "Ocean/Core/Logger.hpp"
#include "Ocean/Core/Assert.hpp"
#include "Ocean/Core/Macros.hpp"

#include "Ocean/Platform/Events/EventService.hpp"
#include "Ocean/Platform/Window/WindowService.hpp"

namespace Ocean {

    #define FixedTimestep 0.02f

    Application::Application(const ApplicationConfig& config) :
        m_LayerStack(),
        m_LastFrameTime(0.0f),
        m_Accumulator(0.0f),
        m_Running(false)
    {
        OASSERTM(!s_Instance, "Application already exists!");
        s_Instance = this;

        oprint(CONSOLE_TEXT_GREEN("Constructing Application\n"));

        RuntimeServiceRegistry::InitializeServices();

        EventService::AddEventCallback<EventCategory::APPLICATION>(OC_BIND_EVENT_FN(Application::OnEvent));
    }

    Application::~Application() {
        RuntimeServiceRegistry::ShutdownServices();

        oprint(CONSOLE_TEXT_GREEN("Deconstructing Applicaiton\n"));
    }

    void Application::Close() {
        oprint(CONSOLE_TEXT_GREEN("|- Application Close Call\n"));

        this->m_Running = false;
    }

    void Application::OnEvent(Event& e) {
        if (e.GetEventType() == EventType::APP_SHOULD_CLOSE)
            s_Instance->Close();

        
    }

    void Application::PushLayer(Layer* layer) {
        oprint(CONSOLE_TEXT_GREEN("|- Application Push Layer Call\n"));

        this->m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer) {
        oprint(CONSOLE_TEXT_GREEN("|- Application Push Overlay Call\n"));

        this->m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::Run() {
        oprint(CONSOLE_TEXT_GREEN("|- Application Run Call\n"));

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

            WindowService::PollEvents();
            EventService::DispatchEvents();

            FrameBegin();

            while (this->m_Accumulator.GetSeconds() >= FixedTimestep) {
                // TODO: Interpolation (For Physics Engine and Renderer)
                FixedUpdate(FixedTimestep);

                accumulatorCounter++;

                this->m_Accumulator -= FixedTimestep;
            }

            if (true) {
                VariableUpdate(timeStep);

                // TODO: Interpolation
                Render(f32());
            }
            FrameEnd();

            // this->m_Window->OnUpdate();

            frameCount++;
        }
    }

    void Application::FixedUpdate(Timestep delta) {
        // oprint(CONSOLE_TEXT_GREEN("\t|- Application FixedUpdate Call\n"));
    }
    void Application::VariableUpdate(Timestep delta) {
        // oprint(CONSOLE_TEXT_GREEN("\t|- Application VariableUpdate Call\n"));

        for (Layer* layer : this->m_LayerStack)
            layer->OnUpdate(delta);
    }
    
    void Application::FrameBegin() {
        // oprint(CONSOLE_TEXT_GREEN("\t|- Application FrameBegin Call\n"));
    }
    void Application::Render(f32 interpolation) {
        // oprint(CONSOLE_TEXT_GREEN("\t|- Application Render Call\n"));
    }
    void Application::FrameEnd() {
        // oprint(CONSOLE_TEXT_GREEN("\t|- Application FrameEnd Call\n"));
    }

    void Application::OnResize(u16 width, u16 height) {
        oprint(CONSOLE_TEXT_GREEN("|- Application OnResize Call\n"));
    }

}    // Ocean
