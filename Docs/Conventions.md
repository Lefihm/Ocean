# Ocean Conventions

## Naming

### Open Methods

An "open method" would be considered a function that is not within the scope of a class or object. So either static helper functions or general helper functions that are used.
Open methods should follow the naming convention of a lowercase 'o' as the prefix to the name.

**For example:**

```cpp
o___() { ... }

oDoSomething() { ... }

oConvertTo___() { ... }
```

### Classes, Structs, and Enums

Classes, structs, and enums should have no prefix, and should be Pascal case.
Names in pascal case start with a capital letter, and in names with multiple words, all words will start with a capital letter.

**For example:**

```cpp
enum Foo { ... };

struct Bar { ... };

class FooBar { ... };
```

A special case is when working with implementation specific versions of classes, or structs.

**For example:**

```cpp
/**
 * @brief General rendering class.
 */
class Renderer { ... };

/**
 * @brief OpenGL rendering class.
 */
class glRenderer { ... };

/**
 * @brief Vulkan rendering class.
 */
class vkRenderer { ... };
```

### Member Variables

### Class Data

Class variables should follow Pascal Case, but also should provide a prefix to the name. The prefix can be a single letter followed by a underscore, i.e. `m_...`, where `m` describes the variable as a member. Other prefixes may describe other features, such as a pointer may have `p_...`, or a constant may have `c_...`.

### Struct Data

As struct's are often data focused in use, the variable prefix is not as necessary. In the case of a struct, member variables should follow Camel Case. Where each word after the first begins with a capital letter, such as `fooBar`.

## Documentation

Documentation will be Doxygen compliant, using `/** */` (often refered to as JavaDoc or C-Style conventions).

**For example:**

```cpp
/**
 * @brief Function description
 *
 * @param p1 Parameter description
 * @param p2 Parameter description
 *
 * @return Return description
 */
void oFoo(i32 p1, i32 p2) { ... }
```

## Example Code

Below is a cohesive example code following the aformentioned conventions.

```cpp

/**
 * @brief A struct to track data and if they are active.
 */
struct Foo {
    /** @brief The ID of the data Foo is tracking. */
    u32 id;
    /** @brief Record's if the data is active or not. */
    b8 isActive;

};  // Foo

/**
 * @brief Translates the given Foo's id by a given distance.
 * 
 * @param f The Foo object to translate.
 * @param dist The distance to translate the id (forwards or backwards).
 */
void oTranslateFooID(Foo& f, i16 dist) { ... }

/**
 * @brief An enum of flags to control Bar.  
 */
enum BarFlags {
    /** @brief Flag to set verbose behavior. */
    BAR_VERBOSE = 0 << 1,
    /** @brief Flag to set ____. */
    BAR_____    = 0 << 2,

};  // BarFlags

/**
 * @brief A class that manages a set of data.
 */
class Bar {
public:
    /**
     * @brief Constructs a new Bar object.
     *
     * @param size The size of Bar data to create.
     * @param flags The BarFlags to use during construction. (OPTIONAL)
     */
    Bar(u32 size, const BarFlags flags = 0) { ... }
    ~Bar() = default;

    /**
     * @brief Description of DoSomething().
     * 
     * @returns i32 Returns the index of something.
     */
    i32 DoSomething() { ... }

private:
    /** @brief The list of Foo that is marked as active. */
    DynamicArray<Foo> m_ActiveData;
    /** @brief The list of Foo that is marked as indactive. */
    DynamicArray<Foo> m_InactiveData;

};  // Bar

```
