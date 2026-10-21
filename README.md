# Black Salt Bus Mix Clone — Windows 10 / Studio One

This is an **original bus-mix processing plugin project inspired by a broad analog-style bus-compressor workflow**. It is not an official Black Salt Audio product and is not an exact copy of proprietary code, DSP, or interface.

## Important: source project, not a precompiled plugin
This ZIP contains C++ source and a build script. It does **not** contain a ready-to-load `.vst3` binary. A Windows VST3 must be compiled on Windows (or with a suitable Windows toolchain). The build script downloads JUCE from its official GitHub repository, so an internet connection is needed during the first build.

## Features
- Stereo bus compression: threshold, ratio, attack, release
- Makeup gain and dry/wet mix
- Low and high shelf tone controls
- Soft saturation / warmth control
- Dark interface with gold accents
- VST3 and standalone build targets

## Build on Windows 10
1. Install **Visual Studio 2022** with the *Desktop development with C++* workload.
2. Install **CMake 3.22+** and **Git**. Make sure `cmake` and `git` work in Command Prompt.
3. Extract this ZIP to a short path, e.g. `C:\\AudioDev\\BlackSaltBusMixClone`.
4. Open Command Prompt in the extracted folder and run:
   `build-windows.bat`
5. After a successful build, look in `build\\BlackSaltBusMixClone_artefacts\\Release\\VST3\\` for `BlackSalt Bus Mix Clone.vst3`.
6. Copy the `.vst3` bundle to:
   `C:\\Program Files\\Common Files\\VST3\\`
   (you may need administrator permission).
7. Restart Studio One, open **Options/Preferences → Locations → VST Plug-ins**, ensure the VST3 location is enabled, then rescan if needed.

## Build script
Run `build-windows.bat` from a Visual Studio 2022 Developer Command Prompt or a normal Command Prompt with CMake, Git, and the Visual Studio C++ build tools installed.

## Notes
- This is a starter implementation, not a mastering-certified processor. Use conservative settings and level-match when comparing bypass/on.
- Test on copies of sessions first. Keep peaks under control.
- The project has not been compiled or tested in this environment; the first Windows build may reveal compiler/API issues that need correction.
- This project is for personal experimentation. “Black Salt” is used descriptively to identify the requested style; this is not affiliated with or endorsed by Black Salt Audio.
