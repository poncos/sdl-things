# SDL Template - AI Coding Agent Instructions

## Project Overview
This is a C++ SDL2 (Simple DirectMedia Layer) graphics application template providing a reusable foundation for 2D rendering and event handling. The architecture follows an object-oriented encapsulation pattern where SDL lifecycle and operations are wrapped in the `SDLApp` class.

## Architecture & Code Organization

### Core Components
- **SDLApp class** ([../SDLApp.hpp](../SDLApp.hpp), [../SDLApp.cpp](../SDLApp.cpp)): Main SDL wrapper managing initialization, window/renderer creation, and main event loop
- **sdl_template.cpp**: Application entry point; instantiates SDLApp and calls lifecycle methods

### Design Pattern
The codebase uses **RAII (Resource Acquisition Is Initialization)**:
- Constructor initializes member pointers to NULL
- `init()` acquires SDL resources (window, renderer)
- `run()` executes the main game/render loop
- Destructor cleans up SDL resources (renderer, window)

## SDL Initialization & Lifecycle

**Critical initialization sequence** (see [../SDLApp.cpp](../SDLApp.cpp#L13-L39)):
1. `SDL_Init(SDL_INIT_VIDEO)` - initialize SDL video subsystem
2. `SDL_CreateWindow()` - create window (hardcoded 640x480)
3. `SDL_CreateRenderer()` - create accelerated renderer
4. Check all return values; report SDL errors via `SDL_GetError()`

**Main loop pattern** (see [../SDLApp.cpp](../SDLApp.cpp#L41-L59)):
- Poll events with `SDL_PollEvent()` (handle `SDL_QUIT` for window close)
- Clear renderer with white background (0xFF, 0xFF, 0xFF, 0xFF)
- Render custom content between clear and present
- Call `SDL_RenderPresent()` to display frame

## Development Patterns & Conventions

### Error Handling
- All initialization methods return `-1` on failure, `0` on success
- SDL errors logged to stderr via `std::cerr` with `SDL_GetError()` messages
- Example: `"SDL could not initialize! SDL_Error: " << SDL_GetError()`

### Memory Management
- Use NULL checks before destroying SDL objects
- Destructor pattern: check if pointer != NULL before calling destroy function
- No dynamic allocation currently; consider using unique_ptr for future SDL resource wrappers

### Method Naming
- `init()` - setup phase
- `run()` - main loop execution
- Follows snake_case for consistency

## Build & Compilation Notes
- SDL2 library dependency required (include: `-I/usr/include/SDL2`, link: `-lSDL2`)
- Ensure SDL2 headers are installed on system
- No build system configured (Makefile/CMake); manual compilation likely

## Known Issues & TODOs
- [../SDLApp.cpp](../SDLApp.cpp#L52): Comment "Render stuff here" marks placeholder for custom rendering logic
- [../sdl_template.cpp](../sdl_template.cpp#L10): Calls `.start()` method not defined in SDLApp class - likely should be `.run()`
- Missing includes: `<SDLh>` in [../SDLApp.hpp](../SDLApp.hpp#L3) appears malformed (should be `<SDL2/SDL.h>`)
- Method signatures in [../SDLApp.cpp](../SDLApp.cpp#L12) missing return types (`int` keyword)

## Extending the Codebase
When adding features:
1. Render custom content in the loop's render section (between clear/present)
2. Handle new SDL events in event polling section
3. Consider extracting render logic to separate methods for clarity
4. Add new resources (textures, audio) following RAII pattern
