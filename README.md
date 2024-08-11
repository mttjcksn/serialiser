# serialiser
A (de)serialiser lib for easily serialising primitive types, vectors, maps, unordered_maps, and custom objects.

## Build example
```
cmake --preset clang-debug
cd build/clang-debug
cmake --build .
```

## Runing tests
```ctest```
(From inside build folder)

## Using in a cmake project
```
include(FetchContent)

FetchContent_Declare(
  serialiser 
  GIT_REPOSITORY https://www.github.com/mttjcksn/serialiser
  GIT_TAG  main
)

FetchContent_MakeAvailable(serialiser)
```

And reference source files with:

```"${serialiser_SOURCE_DIR}/src"```