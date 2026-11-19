# Switch 2.0 (Fritchii Edition)

Experimental, high-performance Nintendo Switch and Switch 2 emulator in C++, custom-tuned for **The Legend of Zelda: Ocarina of Time** and modern hardware.

---

## ⚡ Optimized for NVIDIA GeForce RTX 3050 (4GB VRAM) & 8GB RAM

This fork includes dedicated optimizations and stability fixes tailored specifically for 4GB VRAM GPUs (like the **NVIDIA GeForce RTX 3050 Laptop / Desktop**) and 8GB system RAM:

### 🛡️ Crash & Stability Fixes
- **Thread-Safe Descriptor Allocation**: Added synchronization and emergency fallback pools in `vk_descriptor_pool.cpp` to prevent `VK_ERROR_OUT_OF_POOL_MEMORY` crashes when opening menus, maps, and inventories.
- **Zero FPS Menu Freeze Fix**: Enabled `EDEN_NX2_ASYNC_DISCARD=1` and `EDEN_NX2_WARM_WHILE_PLAYING=1` so background pipelines compile without stalling the GPU thread.
- **Null Safety in Texture & LRU Cache**: Bounds-checked image eviction and view creation to prevent random crashes during map transitions and teleportation.

### 🚀 60 FPS Performance Tuning
- **Anti-Texture Thrashing Engine**: 
  - `EDEN_NX2_TC_MIN_AGE=120`: Protects recently used textures from premature eviction.
  - `EDEN_NX2_TC_EXPECTED_MIB=2800` & `EDEN_NX2_TC_CRITICAL_MIB=3300`: Prevents aggressive GC loops on 4GB VRAM cards.
  - `FRITCHII_TC_COLLECT_EVICTABLE=1`: Protects ASTC textures from wasteful eviction cycles.
  - `FRITCHII_LOST_WRITEBACK=4096`: Stops large framebuffer textures from being dropped without writeback.
- **Optimized Compute ASTC Decoding**: Eliminates real-time 440ms ASTC compute stalls.
- **Silenced High-Frequency Disk Logs**: Eliminated thousands of runtime logging calls per session to maximize CPU headroom.
- **High Refresh Frame Pacing**: Dynamic FPS unlocked with `frame_pacing_mode=0` (Auto) and `oot_high_refresh=true` for smooth 60 FPS gameplay.

---

## 💻 Tested Hardware Profile

- **GPU**: NVIDIA GeForce RTX 3050 Laptop (4 GB GDDR6)
- **CPU**: AMD Ryzen 7 5800H (8 Cores, 16 Threads)
- **RAM**: 8 GB DDR4 (Single Channel)
- **Target Game**: *The Legend of Zelda: Ocarina of Time* (NUP format, Title ID `0400486024DEC000`)
- **Performance**: Smooth 30 - 60 FPS native

---

## 🎮 Recommended Settings (4GB VRAM)

| Setting | Value | Reason |
|---|---|---|
| **Resolution** | 1x Native (720p/1080p) | Saves VRAM on 4GB cards |
| **GPU Accuracy** | Low | Maximum draw performance |
| **DMA Accuracy** | Unsafe | Highest transfer speed |
| **VRAM Usage Mode** | Conservative | Keeps memory under 4GB cap |
| **Scaling Filter** | Nearest Neighbor / Bilinear | Lightest GPU overhead |
| **Frame Pacing Mode** | Target_Auto | Smooth presentation at display refresh |
| **High Refresh** | Enabled (60Hz) | Unlocks smooth 60 FPS |

> **Tip**: In **Properties -> Add-Ons**, ensure **"Max Resolution (built-in)"** and **"Texture Pool x2 (built-in)"** are **unchecked** on 4GB VRAM GPUs to avoid VRAM overflow.

---

## 📦 Portable Standalone Run

To run without installation:
1. Place `fritchii.exe` and `nx2_switches.txt` in a folder.
2. Create a folder named `user` in the same directory (triggers portable mode).
3. Put your configs and keys in `user/config/` and `user/keys/`.
4. Run `fritchii.exe`.

---

## 🛠️ Building from Source

Requirements:
- Visual Studio 2022 (MSVC v143+) with C++20 support
- CMake 3.25+
- Ninja build system
- Vulkan SDK 1.3+

```cmd
git clone https://github.com/Helloflixofficial/switch2.0.git
cd switch2.0
mkdir build
cmake -B build -GNinja -DCMAKE_BUILD_TYPE=Release
ninja -C build yuzu -j 4
```

Output binary: `build\bin\fritchii.exe`.

---

## 📜 License

Fritchii is an experimental, modified version of GPL-licensed software. See [LICENSE.txt](LICENSE.txt) for license terms. Not affiliated with Nintendo.
