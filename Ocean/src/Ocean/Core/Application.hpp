#pragma once

#include "Ocean/Types/Bool.hpp"
#include "Ocean/Types/Integers.hpp"
#include "Ocean/Types/Strings.hpp"
#include "Ocean/Types/Timestep.hpp"

#include "Ocean/Core/Macros.hpp"
#include "Ocean/Core/Memory.hpp"

#include "Ocean/Core/Layers/LayerStack.hpp"

#include "Ocean/Platform/Events/Event.hpp"

extern int main(int argc, char** argv);

/**
 * @brief The namespace of Ocean Engine. All primary Ocean functionality is within this namespace.
 */
namespace Ocean {

    /**
     * @brief A struct to configure the application at startup.
     */
    struct ApplicationConfig {
        /** @brief The name of the application. */
        cstring name;

        /** @brief The starting width of the application window. */
        u32 width;
        /** @brief The starting height of the application window. */
        u32 height;

        /** @brief If the application is fullscreen or not at startup. */
        b8 fullscreen;

        i32 argc;
        char** argv;

        /**
         * @brief Construct a new ApplicationConfig with the given parameters.
         * 
         * @param name The name of the Application.
         * @param w The initial width of the Application.
         * @param h The initial height of the Application.
         * @param fullscreen Set's the Application fullscreen at startup. (OPTIONAL)
         * @param argc (OPTIONAL)
         * @param argv (OPTIONAL)
         */
        ApplicationConfig(cstring name, u32 w, u32 h, b8 fullscreen = false, i32 argc = 0, char** argv = nullptr) :
            name(name),
            width(w),
            height(h),
            fullscreen(fullscreen),
            argc(argc),
            argv(argv)
        {

        }

    };    // ApplicationConfig

    /**
     * @brief The base Ocean application class.
     */
    class Application {
    public:
        /**
         * @brief Construct a new Application object.
         * 
         * @param config The ApplicationConfig to use when starting the application.
         */
        Application(const ApplicationConfig& config);
        virtual ~Application();

        /**
         * @brief Closes the application.
         */
        void Close();

        void OnEvent(Event& e);

        /**
         * @brief Pushes a layer onto the application's LayerStack.
         * 
         * @param layer The Layer to push.
         */
        void PushLayer(Layer* layer);
        /**
         * @brief Pushes a overlay onto the application's LayerStack. AKA it will be drawn over any layers.
         * 
         * @param layer The Layer to push.
         */
        void PushOverlay(Layer* layer);

        /**
         * @brief Call to resize the Application. AKA the main window and renderer.
         * 
         * @param width The new width.
         * @param height The new height.
         */
        void OnResize(u16 width, u16 height);

        /**
         * @brief Get's the Application instance.
         * 
         * @return Application* 
         */
        inline static Application* Get() { return s_Instance; }

        OC_NEW_OVERLOAD(oSystemAllocator);
        OC_DELETE_OVERLOAD(oSystemAllocator);

    protected:
        friend int ::main(int argc, char** argv);

    protected:
        /**
         * @brief The primary runtime of the application.
         */
        void Run();

        /**
         * @brief Update function for fixed timestep processes. AKA physics or state-machines.
         * 
         * @param delta The time since the last update, expected to be consistent by ~0.001 second.
         */
        void FixedUpdate(Timestep delta);
        /**
         * @brief Update function for variable timestep processes. AKA layer and runtime updates.
         * 
         * @param delta The time since the last update.
         */
        void VariableUpdate(Timestep delta);
        
        /**
         * @brief Runs at the beginning of each frame.
         */
        void FrameBegin();
        /**
         * @brief Runs after VariableUpdate is completed (at least while single threaded).
         * 
         * @param interpolation The interpolation since the last frame.
         */
        void Render(f32 interpolation);
        /**
         * @brief Runs at the end of each frame.
         */
        void FrameEnd();

    protected:
        /** @brief The instance of the Application, makes sure there is only one instance running. */
        inline static Application* s_Instance = nullptr;

        /** @brief The LayerStack of the application. */
        LayerStack m_LayerStack;

        /** @brief A Timestep of the last frame's runtime. */
        Timestep m_LastFrameTime;
        /** @brief A Timestep accumulating time until above the fixed timestep threshold. */
        Timestep m_Accumulator;

        /** @brief A b8 to record if the application is in runtime or not. */
        b8 m_Running;

    private:
        OC_NO_COPY(Application);

    };    // Application

    /**
     * @brief Create an Application object defined by the user.
     * 
     * @return Application* 
     */
    Application* CreateApplication(int argc, char** argv);

}    // Ocean
