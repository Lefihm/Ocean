# Core

This document describes the core components and architecture of the Ocean project.

## Application

The Application module is responsible for initializing, running, and shutting down the main program. It manages the lifecycle of the application and coordinates the interaction between different layers and services.

### Entry Point

The entry point is the main function where the application starts execution. It typically performs the following tasks:

1. Initializes `static services`
2. Create's an application with `CreateApplication`
3. Runs the application
4. Delete's the application
5. Shut's down the `static services`

### Layers

The application manages a stack of layers, allowing for flexible extension and separation of concerns. Each layer can override lifecycle methods such as `OnAttach`, `OnDetach`, `OnUpdate`, and `OnEvent`. An example separation of layers would be the active player view, and the UI existing on different layers to allow easy logic distinction.

**For Example:**

The following shows a minimal layer declaration that utilizes all of the available method overides.

```cpp
class ExampleLayer : public Ocean::Layer {
public:
    ExampleLayer() : Layer("ExampleLayer")
    { }
    virtual ~ExampleLayer()
    { }

    virtual void OnAttach() override {
        oprint("Attached layer: {%s}\n", this->GetName().cstr());
    }
    virtual void OnDetach() override { }

    virtual void OnUpdate(Timestep ts) override { }

    virtual void OnEvent(Ocean::Event& e) override { }

};  // ExampleLayer
```

For further reference, see [`Layer.hpp`](../Ocean/src/Ocean/Core/Layers/Layer.hpp).

## Services

Core services provide essential functionality to the application and its layers.

Services are categorized as either `static` or `runtime` services. This determines the lifetime of the service. Some example `static` services would be:

- `MemoryService`
- `LogService`

While `runtime` services can be:

- `RendererService`
- `AudioService`

**For Example:**

The following shows an example service declaration. This will automatically register the service for initialization in either the `static` or `runtime` registry.

```cpp
class FooService : public StaticService<FooService> {
public:
    FooService() = default;
    ~FooService() = default;

    AssignServiceName(FooService);
    AssignServicePriority(ServicePriority::DONT_CARE);

    virtual void Init() override { }
    virtual void Shutdown() override { }
};

class BooService : public RuntimeService<BooService> {
public:
    BooService() = default;
    ~BooService() = default;

    AssignServiceName(BooService);
    AssignServicePriority(ServicePriority::DONT_CARE);

    virtual void Init() override { }
    virtual void Shutdown() override { }
};
```

Overriding `Init` and `Shutdown` are optional, by default they do nothing.

`ServicePriority` simply provides a set of named priorities. `Services` are sorted from smallest to largest in terms of value, i.e. `DONT_CARE = 10`. Any value within the `u8` spec is valid.

For further reference, see [`Service.hpp`](../Ocean/src/Ocean/Core/Service.hpp).

### Memory

The `MemoryService` abstracts memory allocation and deallocation. It provides custom allocators, memory tracking, and debugging features to improve performance and detect leaks.

There are two defines to configure how the `MemoryService` or related allocators operate.

1. `OC_VERBOSE_MEMORY` -- Will output a log when any memory is allocated or deallocated through the `MemoryService`
2. `OC_VERBOSE` -- Will log the `MemoryStats` when the `MemoryService` shuts down

Both of these options are designed to help when debugging to find memory leaks, know that if using allocators that do not have a managed memory space then `MemoryStats` are unable to be recorded.

**For Example:**

```cpp
void* ptr = oalloca(128, oSystemAllocator); // Allocate 128 bytes

ptr = oallocat(Foo, oSystemAllocator); // Allocates the size of type Foo, now the original 128 bytes are lost

ofree(ptr, oSystemAllocator);               // Free the memory
```

### Logger

The Logger service handles logging of messages, warnings, and errors. It supports multiple log levels (info, warning, error, debug) and can output to various targets (console, file, etc.). Logging is essential for debugging and monitoring application behavior.

**For Example:**

```cpp
oprint("Hello, Ocean!\n");

oprintret("This is a message with a newline.");

oprints("This is a service log message. It must only be used within a valid service.");
```

### Scheduling

The `SchedulerService` handles tasks. It allows the application to schedule functions to run in a node-dependent order, supporting both synchronous and asynchronous execution.

**For Example:**

To schedule a single task, the following can be used to submit a task that will be completed at the earliest point in time.

```cpp
Ocean::Scheduler::SubmitTask([]() {
    oprint("Task executed asynchronously!\n");
});
```

To schedule multiple tasks that have dependent relationships. Create a `TaskPacket`, allowing the structuring of tasks. These tasks will run concurrently unless paths merge, then the child node will wait for the paths to be completed.

```cpp
// Create tasks
Ocean::Task taskA;
taskA.name = "TaskA";
taskA.action = []() { oprint("Running TaskA\n"); };

Ocean::Task taskB;
taskB.name = "TaskB";
taskB.action = []() { oprint("Running TaskB\n"); };

Ocean::Task taskC;
taskC.name = "TaskC";
taskC.action = []() { oprint("Running TaskC\n"); };

// Build dependency graph: TaskA -> TaskB -> TaskC
Ocean::DirectedGraph<Ocean::Task> graph;

auto nodeA = graph.AddNode(std::move(taskA));
auto nodeB = graph.AddNode(std::move(taskB));
auto nodeC = graph.AddNode(std::move(taskC));

graph.AddEdge(nodeA, nodeB); // TaskA must finish before TaskB
graph.AddEdge(nodeB, nodeC); // TaskB must finish before TaskC

// Create TaskPacket and submit
Ocean::TaskPacket packet(std::move(graph), "ExamplePacket");

Ocean::Scheduler::SubmitPacket(std::move(packet));
```

## Exceptions

The `Exceptions` defines custom exception types used throughout the core. It provides mechanisms for error reporting and handling, ensuring that errors are caught and managed appropriately. Each exception carries a related `Error`, providing better handling capabilities.

**For Example:**

```cpp
try {

    throw Ocean::Exception(Ocean::Error::OUT_OF_RANGE, "Index out of range!");

} catch (const Ocean::Exception& ex) {

    oprint("Caught Ocean exception: %s\n", ex.what());
    oprint("Error index: %i\n", ex.error());

}
```

## Asserts

Asserts are used to enforce invariants and catch programming errors during development. The assert macros check conditions at runtime and, if a condition fails, log an error and optionally halt execution (in debug builds).

**For Example:**

```cpp
OASSERT(ptr != nullptr);

OASSERTM(value > 0, "Value must be positive, got %d", value);

OASSERT_LENGTH(index, maxCount);
```

## Macros

Core macros provide utility functionality such as assertions, logging shortcuts, and platform/compiler-specific features. They help reduce boilerplate and noisy code.

**For Example:**

```cpp
// Mark a function parameter as unused
void foo(int used, OC_UNUSED int unused) { /* ... */ }

// Get the current file and line
oprint(CONSOLE_TEXT_RED("Location: %s\n"), OCEAN_FUNCTIONLINE("Here!"));
```
