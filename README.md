# findit
<div align="center">
  <img src="screenshots/screenshot.png" alt="findit voxel game screenshot" width="800"/>
</div>

**The station engine in C++** is a pilot project for studying station angles, rendering and optimization of visibility.

## What is it
Simple station sandbox with troughs 16x16x16. Generates random cubes, performs visibility checking (culling of hidden edges), renders via OpenGL. So far tech demo is the basis for a future game.

## Technologies used
- **C++17** - Engine Base
- **OpenGL 3.3+** - Cube rendering (VAO/VBO)
-**GLM** - vector mathematics, transformation
- **GLEW** - OpenGL functions loading
- **SDL** - window and input
-**Icon** - help from above

## Implementation Features
**Chanc 163 == 4096 stations**
**Generation of positions + color**                   
**Culling by neighbors (ivec3 hash)**  
**Custom matrices model**

## Management
-**WASD** - movement
- **Mouse** - overview
- **Esc** - exit

## Build (Linux)
`bash
git clone https://github.com/mental0-main/findit.git && cd findit
mkdir build && cd build
cmake .
make -j$(nproc)
./findit
`

**Status:** Project on pause. Base ready.
**Plans:** The world of plates, textures, lighting.

[! [GitHub](https://img.shields.io/badge/GitHub-@mewfl-black?logo=github)](https://github.com/mental0-main)
