# Untitled Logger - a scriptSQD's C++ logger library.

## Usage

**untitled-logger** has a pretty simple API: core members of the class are static, therefore you can invoke logger
without
having to create its instance first.

**SQD::Logger::Log** is a main method that uses internal class state to log (or not) to either stdout or file.

**SQD_LOG**, **SQD_WARN** and **SQD_ERR** are macros designed to allow developers to strip out logging entirely from
their
release builds by simply defining:

```c++
#define SQD_DISABLE_LOGGER 1
```

however is convenient for the end developer.

**untitled-logger** features 3 levels of logging: LOG, WARNING and ERROR. Each has appropriate colored output for stdout
and severity prefix for both stdout and file streams.

## CMake

The most convenient way to add the library is to do `add_subdirectory(...)` in your CMakeLists.txt.

**untitled-logger** sets `LOGGER_INCLUDES` and `LOGGER_LIBS` CMake variables and makes them visible for parent scope.
It's possible to do:

```cmake
target_include_directories(target PUBLIC ... ${LOGGER_INCLUDES} ...)
target_link_libraries(target PUBLIC ... ${LOGGER_LIBS} ...)
```

in your CMakeLists.txt and get up and running in no time at all.