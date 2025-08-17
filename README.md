# 🌐 WebServer (C++)

A lightweight, educational web server written in **C++**, designed to run on both **Linux** and **Windows**.  
This project demonstrates the fundamentals of socket programming, request parsing, and serving HTTP responses, while keeping the codebase clean and approachable.

---

## Features
- Cross-platform support (**Windows** & **Linux**)  
- Minimal dependencies (just the standard C library + [spdlog](https://github.com/gabime/spdlog) for logging)  
- Basic HTTP/1.1 request parsing (method, target, protocol, host)  
- Blocking socket model — Coming Soon: None blocking threaded model for handling multiple requests)
- Extendable foundation for building more advanced networking projects  

---

## Build Instructions

### Prerequisites
- **Linux**
  - GCC or Clang
  - `premake` (optional, if using provided premake5.lua file)
- **Windows**
  - Visual Studio (MSVC)
  - Windows SDK (for Winsock2 headers/libraries)

---

### Building on Linux

```bash
# Clone the repository (with submodules for spdlog)
git clone --recurse-submodules https://github.com/yourusername/webserver.git
cd webserver

# Build with premake5
premake5 gmake2
make config=debug/release

# Run the server
./build/webserver
```

### Building on Windows

```bash
# Clone the repository (with submodules for spdlog)
git clone --recurse-submodules https://github.com/yourusername/webserver.git
cd webserver

# Build with premake5
premake5 vs2022

# Open Visual Studio 2022 sln file
Webserver.sln (make sure ws2_32.lib is linked)
Build and Run (ctrl + F5)
```

---

## Usage

By default, the server listens to any local ip address on port 8080

Open your browser and navigate to any of the following:

```
http://localhost:8080

127.0.0.1:8080
```

---



