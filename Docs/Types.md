# Types

This document describes the core type definitions and utilities provided by the Ocean project. These types provide clarity, safety, and consistency throughout the codebase.

Most basic types follow the naming convention of a prefix, describing the type, and a postfix, representing the number of bits the type represents. Such as a `i32`, where `i` means `integer`, and `32` means `32 bits`.

The purpose of many alias's is for either laziness when typing. Or so that at a later time it is easier to replace types with a custom, Ocean specific implementation if needed.

## Bits

### Bix

The `Bix` family provides compact bit storage and manipulation for small sets of bits. For example, `Bix8` wraps an 8-bit value and allows for individual bit access, flipping, and masking.

**For Example:**

```cpp
Bix8 bits({ true, false, true, false, true, false, true, false });

bits.Flip(0); // Flip the first bit

bool isSet = bits[2]; // Access the third bit
```

For further reference, see [`Bix.hpp`](../Ocean/src/Ocean/Types/Bix.hpp).

### Bitrix

`Bitrix2D` is a bit-compressed 2D matrix, storing boolean values efficiently for use cases like grids or masks.

**For Example:**

```cpp
Bitrix2D grid(16, 16);

grid.Set(2, 3, true);

bool value = grid.Get(2, 3);
```

For further reference, see [`Bitrix.hpp`](../Ocean/src/Ocean/Types/Bitrix.hpp).

## Bools

Ocean defines boolean types for clarity and explicit sizing:

- `b8` -- 8-bit boolean (`typedef bool b8;`)
- `b32` -- 32-bit boolean (`typedef unsigned int b32;`)

For further reference, see [`Bool.hpp`](../Ocean/src/Ocean/Types/Bool.hpp).

## Integers

Explicit-width integer types are provided for portability and clarity:

|              | 8-bit | 16-bit | 32-bit | 64-bit  |
| ------------ | ----- | ------ | ------ | ------- |
| **Unsigned** | `u8`  | `u16`  | `u32`  | `u64`   |
| **Signed**   | `i8`  | `i16`  | `i32`  | `i64`   |

- `sizet` -- Alias for `size_t`

Maximum and minimum values for each type are also defined (e.g., `u32_max`, `i32_min`).

For further reference, see [`Integers.hpp`](../Ocean/src/Ocean/Types/Integers.hpp).

## Floats

Floating point types are defined for precision control:

- `f32` -- 32-bit floating point (`float`)
- `f64` -- 64-bit floating point (`double`)

For further reference, see [`FloatingPoints.hpp`](../Ocean/src/Ocean/Types/FloatingPoints.hpp).

## Strings

String types are provided for both C-style and C++-style strings:

- `cstring` -- Alias for `const char*`
- `String` -- Alias for `std::string`

For further reference, see [`Strings.hpp`](../Ocean/src/Ocean/Types/Strings.hpp).

## Smart Pointers

Ocean provides type aliases and factory functions for smart pointers:

- `Scope<T>` -- Alias for `std::unique_ptr<T>`
- `Ref<T>` -- Alias for `std::shared_ptr<T>`
- `MakeScope<T>(...)` -- Factory for `Scope`
- `MakeRef<T>(...)` -- Factory for `Ref`

**For Example:**

```cpp
// Creating a unique pointer (Scope)
Scope<MyClass> myScopedPtr = MakeScope<MyClass>(constructorArg1, constructorArg2);

// Creating a shared pointer (Ref)
Ref<MyClass> mySharedPtr = MakeRef<MyClass>(constructorArg1, constructorArg2);
```

For further reference, see [`SmartPtrs.hpp`](../Ocean/src/Ocean/Types/SmartPtrs.hpp).

## Iterators

Custom iterator templates are provided for input, output, forward, bidirectional, and random access iteration, following C++ iterator conventions.

**For Example:**

```cpp
int arr[] = {1, 2, 3, 4, 5};
InputIterator<int> begin(arr);
InputIterator<int> end(arr + 5);

for (auto it = begin; it != end; ++it) {
    int value = *it;
    // Use value...
}
```

For further reference, see [`Iterator.hpp`](../Ocean/src/Ocean/Types/Iterator.hpp).

## Timestep

The `Timestep` class wraps a floating-point value representing a time interval (in seconds), with utility methods for conversion and arithmetic.

**For Example:**

```cpp
Timestep ts(0.016f); // 16 milliseconds
float seconds = ts.GetSeconds();       // 0.016
float milliseconds = ts.GetMilliseconds(); // 16.0

Timestep ts2(0.010f);
Timestep sum = ts + ts2; // Uses operator overloading
```

For further reference, see [`Timestep.hpp`](../Ocean/src/Ocean/Types/Timestep.hpp).

## GLM Types

Ocean includes type aliases for common vector and matrix types from the [GLM](https://github.com/g-truc/glm) library, such as `glm::vec2`, `glm::mat4`, etc.

For further reference, see [`glmTypes.hpp`](../Ocean/src/Ocean/Types/glmTypes.hpp)
