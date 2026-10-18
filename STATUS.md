# monie visuals - honest status of this snapshot

**This is a work-in-progress source snapshot, NOT a finished plugin. No compiled VST3 is included.**

## Verified (Linux sandbox only: g++, Xvfb, Mesa software GL)
- Core logic unit tests pass (analyzer, engines, project JSON, text animation, ASR chunker, export plan).
- JUCE standalone target compiled and ran; all 7 GLSL shaders compiled; 30 scenes rendered distinct thumbnails (docs/screenshots/scene_contact_sheet_software_gl.png).

## Written but NOT visually/functionally verified
- Text layers, image/video layers, per-layer + global effect stack, text animations in GL, caption overlay.
- Plugin state save/load inside a host.

## Not built yet
- The premium UI (top bar, browser, inspector, layers/timeline, 12 tabs, themes). The editor is a temporary preview-only window.
- Caption worker (whisper.cpp process), manual lyrics/SRT/LRC UI, export job + progress UI, preset manager, shapes.
- Whisper recognition has never been run (no model available here).

## Never tested
- Windows build, FL Studio 26 loading, real-time performance on a real GPU.

## Build (Windows, you must do this)
Install Visual Studio 2022 (C++), CMake. JUCE 8.0.6 is fetched/placed per CMakeLists.txt. Then:
cmake -B build -G "Visual Studio 17 2022" -A x64 && cmake --build build --config Release --target MonieVisuals_VST3
Expect compile errors possible on Windows - it has not been tried.
