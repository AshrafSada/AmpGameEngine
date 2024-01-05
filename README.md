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
