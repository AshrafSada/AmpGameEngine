# AMP Game Engine

C/C++ 3D Game Engine currently using DirectX 11.

## Table of Contents

- [AMP Game Engine](#amp-game-engine)
  - [Table of Contents](#table-of-contents)
  - [Structure](#structure)
  - [Features](#features)
    - [Graphics Engine](#graphics-engine)
      - [Graphics APIs](#graphics-apis)
        - [Why Multiple Graphics APIs?](#why-multiple-graphics-apis)
      - [DirectX 11](#directx-11)
        - [Swap Chain](#swap-chain)
        - [Why DirectX 11 Not 12?](#why-directx-11-not-12)
    - [Game Engine](#game-engine)

## Structure

The engine utilizes DirectX 11 for rendering, and is written in C++.

This engine is designed to be cross-platform, but currently only supports Windows.

In the feature this engine will support Linux.

## Features

The engine has 2 main parts:

### Graphics Engine

The graphics engine is responsible for rendering the graphics using DirectX 11.

The graphics engine is designed to be cross-platform, but currently only supports Windows.

Basic tasks of the graphics engine:

1. Drawing Functions.
2. 2D/3D Models Loading.
3. Shaders Management.
4. Graphics APIs Management.

Technical functionality of the graphics engine must have at least the following:

1. Init function:
    - Initializes the graphics engine.
2. Release function:
    - Releases the graphics engine.
3. Singleton Get:
    - Returns the graphics engine instance globally across application.

#### Graphics APIs

The graphics engine supports multiple graphics APIs, but currently only supports DirectX 11.

##### Why Multiple Graphics APIs?

The main reason for supporting multiple graphics APIs is to support multiple platforms.

Examples of graphics APIs:

1. DirectX 11 (Windows).
2. DirectX 12 (Windows).
3. OpenGL (Windows, Linux, Mac).
4. Vulkan (Windows, Linux, Mac).
5. Metal (Mac).
6. WebGL (Web).
7. Mantle (Windows, Linux, Mac).

The reason for supporting multiple graphics APIs is to support multiple platforms.

We can later add support for other platforms like Linux and Mac.

#### DirectX 11

DirectX 11 is proven to be the best graphics API for Windows, despite that DirectX 12 is included in Windows 10, game developers still prefer DirectX 11.

The graphics engine is built on top of DirectX 11.

DirectX 11 has these main parts:

1. **DirectX Device**: Direct3D device is the rendering component of Direct3D.
2. **DirectX Context**: Direct3D device context is used to set pipeline state and generate rendering commands.
3. **DirectX Swap Chain**: a series of virtual framebuffers used by the graphics card and graphics API for frame rate stabilization, stutter reduction, and several other purposes.

##### Swap Chain

The swap chain is a collection of buffers that are used for rendering frames to the screen, using both system and video RAM.

In the general use case, the swap chain is a collection of two buffers, the front buffer and the back buffer.

The front buffer is the buffer that is currently being displayed on the screen, it utilizes the video RAM (GPU RAM), while the back buffer is the buffer that is currently being rendered to, and utilizes (GPU RAM + System RAM).

After the immediate context (device context) is done rendering to the back buffer, the swap chain presents the back buffer by swapping the two buffers.

This method of flipping the buffers is called **double buffering**.

It is called swap chain because it is a chain of buffers that are swapped, between the front buffer and the back buffer.

:bulb: ***Note***: The swap chain is very important rendering method, it should be loosely-coupled, from the device and device context.*

##### Understanding Device Context

The device context is the interface between the application and the GPU.

The GPU is a separate processor that is designed to handle graphics and image processing, which has 2 driver parts (Hardware Driver and Software Driver).

The device driver is designed to handle input/output operations, redirected to the GPU by the device context.

The device context is the interface between the application and the GPU, it is used to set pipeline state and ***generate rendering commands***.

Device context has 2 types:

1. **Immediate Context**: used for rendering commands.
2. **Deferred Context**: used for setting pipeline state.

Immediate context is used for:

1. Rendering commands list, or single command at a time.
2. Direct rendering to the GPU by it's driver (using driver sub-routines).
3. Immediate rendering to the back buffer.

Deferred context is used for:

1. Setting pipeline state.
2. Recording rendering commands to a command list.
3. Used for multi-threading.

:bulb: ***Note***: The graphics engine currently uses only Immediate Context.

##### Why DirectX 11 Not 12?

Common reasons why DirectX 11 is the best graphics API for Windows:

1. Frame rate is more stable than DirectX 12.
2. More games support DirectX 11 than DirectX 12.
3. DirectX 11 is not hardware demanding, it utilizes available GPU and CPU efficiently.
4. DirectX 11 is more close to Windows Operating System features which gives it better performance on Windows.
5. DirectX 11 is high-level API, while DX12 is low-level (more-complexity).

### Game Engine

The game engine is responsible for running the game.

It includes the Graphics Engine.
