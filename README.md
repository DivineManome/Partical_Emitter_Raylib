# Particle System

![C++](https://img.shields.io/badge/C%2B%2B-11-00599C?logo=c%2B%2B&logoColor=white)
![raylib](https://img.shields.io/badge/built%20with-raylib-black)

A small, interactive particle system written in C++ with [raylib](https://github.com/raysan5/raylib). Hold the left mouse button and a spray of colorful, fading circles pours out of the cursor. The project uses an **object pool**, so all particles are created once at startup and reused for the lifetime of the program.

<img width="780" height="703" alt="ParticleEmit2" src="https://github.com/user-attachments/assets/25262703-3d50-4536-a9d1-5b0c2888ba38" />


## Table of Contents

- [Features](#features)
- [Demo](#demo)
- [Controls](#controls)
- [How It Works](#how-it-works)
- [Getting Started](#getting-started)
- [Configuration](#configuration)
- [Troubleshooting](#troubleshooting)
- [Project Structure](#project-structure)
- [Ideas for Extending](#ideas-for-extending)
- [Feedback](#feedback)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## Features

- Spawns particles at the mouse position while the left button is held
- Every particle gets a random size, color, speed, and direction
- Particles grow slightly and fade out, then return to the pool
- Object pool of fixed size, so there is no memory allocation while the program runs
- Clean separation between the particle (`Particle`) and the system that manages them (`ParticleSystem`)

## Demo

<img width="395" height="394" alt="image" src="https://github.com/user-attachments/assets/9bd86fc5-295b-4d9c-b4cf-50732bbd617f" />

Every particle has a net downward motion, so the effect looks like a colorful spray falling from the cursor. Moving the mouse while holding the button paints a trail.

## Controls

| Input | Action |
| --- | --- |
| Hold `Left Mouse Button` | Spawn particles at the cursor |
| `Esc` | Quit |

## How It Works

### Object pool

The system creates `POOL_SIZE` particles (1000 by default) once, in `ParticleSystem::Start()`. Each particle has an `_active` flag. When the program needs a new particle, it looks for the first inactive one in the pool and activates it. When a particle finishes fading out, it is marked inactive and becomes available again.

If every particle in the pool is active, new spawn requests are skipped until some particles finish.

### Particle lifecycle

1. **Spawn:** while the left mouse button is held, 3 to 20 particles are activated each frame at the mouse position.
2. **Move:** each frame the particle moves along its direction at its own speed, and a constant downward drift (`_gravity`) is added.
3. **Change:** the radius grows by a small amount each frame and the alpha (opacity) drops.
4. **Recycle:** once the alpha runs out, the particle becomes inactive and returns to the pool.

With the default values, a particle lasts about 25 frames, which is roughly 0.4 seconds at 60 FPS.

### Randomized properties

Each particle is given these values when it is activated:

| Property | Range | Notes |
| --- | --- | --- |
| Radius | 5 to 50 pixels | Starting size |
| Speed | 2 to 8 pixels per frame | Speed along its direction |
| Angle | 0 to 360 degrees | Direction of travel |
| Color | Random red, green, and blue | Fully opaque when spawned |

### About the "gravity"

`_gravity` is a **constant downward drift** of 10 pixels per frame, not an acceleration that builds up over time. Because it is larger than the maximum particle speed (8), every particle ends up moving downward, even ones that start out aimed upward.

## Getting Started

### Requirements

- A C++ compiler with C++11 support (g++, clang, or MSVC)
- [raylib](https://github.com/raysan5/raylib) installed (see the raylib repository for installation instructions)

### Build

All source files need to be compiled together.

**Linux**

```bash
g++ main.cpp ParticleSystem.cpp Particle.cpp -o particles -std=c++11 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

**macOS**

```bash
g++ main.cpp ParticleSystem.cpp Particle.cpp -o particles -std=c++11 -lraylib -framework IOKit -framework Cocoa -framework OpenGL
```

**Windows (MinGW)**

```bash
g++ main.cpp ParticleSystem.cpp Particle.cpp -o particles.exe -std=c++11 -lraylib -lopengl32 -lgdi32 -lwinmm
```

**Windows (Visual Studio):** create a project from the raylib Visual Studio template and add all of the `.cpp` and `.h` files to it.

### Run

```bash
./particles
```

## Configuration

Most of the behavior can be changed by editing a few numbers.

| Setting | Location | Default | Effect |
| --- | --- | --- | --- |
| `POOL_SIZE` | `ParticleSystem.h` | `1000` | Maximum number of particles alive at once |
| Spawn rate | `GetRandomValue(3, 20)` in `ParticleSystem::Update` | 3 to 20 per frame | How many particles appear each frame while the button is held |
| Starting radius | `GetRandomValue(5, 50)` in `ParticleSystem::Update` | 5 to 50 | Size of new particles |
| Speed | `GetRandomValue(2, 8)` in `ParticleSystem::Update` | 2 to 8 | How fast particles travel along their direction |
| Direction | `GetRandomValue(0, 360)` in `ParticleSystem::Update` | 0 to 360 | Which way particles fly out |
| `_gravity` | `Particle.h` | `10` | Downward drift in pixels per frame |
| Growth | `_radius += 0.1` in `Particle::Update` | `0.1` | How much each particle grows per frame |
| Fade | `alpha -= 10` in `Particle::Update` | `10` | How fast particles fade. A bigger number gives a shorter life |
| Background | `ClearBackground(...)` in `ParticleSystem::Main` | `20, 20, 20` | Window background color |
| Window | `InitWindow(...)` in `ParticleSystem::Main` | `800 x 800` | Window size and title |

For example, lowering `_gravity` to `2` makes the particles spread out in all directions instead of falling, and lowering the fade value to `3` makes them last much longer.

## Troubleshooting

| Problem | Fix |
| --- | --- |
| Nothing appears | Hold the left mouse button while the cursor is over the window |
| Fewer particles than expected | The pool may be full. Increase `POOL_SIZE` in `ParticleSystem.h` |
| Particles disappear too quickly | Lower the fade value (`alpha -= 10`) in `Particle::Update` |
| Build fails with undefined references | Make sure all three `.cpp` files are in the build command |

## Project Structure

```
.
├── main.cpp              Entry point
├── ParticleSystem.h      Pool, game loop, and spawning (declaration)
├── ParticleSystem.cpp    Pool, game loop, and spawning (implementation)
├── Particle.h            A single particle (declaration)
├── Particle.cpp          A single particle (implementation)
├── README.md
├── LICENSE
└── docs/
    └── images/
        ├── demo.gif
        ├── screenshot.png
        ├── object-pool.png
        ├── lifecycle.png
        └── customization.png
```

| File | Responsibility |
| --- | --- |
| `main.cpp` | Creates a `ParticleSystem` and runs it |
| `ParticleSystem` | Owns the pool, opens the window, runs the main loop, and spawns particles |
| `Particle` | Holds the state of one particle and knows how to update and draw itself |

## Ideas for Extending

- Add a keyboard control to change gravity, spawn rate, or fade speed while running
- Make `_gravity` a real acceleration so particles speed up as they fall
- Add different particle shapes or textures
- Use a color gradient instead of fully random colors
- Add a second emitter, such as a fountain that spawns without the mouse

## Feedback

Issues and suggestions are welcome.

## Acknowledgments

- [raylib](https://github.com/raysan5/raylib), the library used for windowing, input, and drawing
