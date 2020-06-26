# A UWP sample app using the ANGLE library

Requires ANGLE to be built locally. See <https://chromium.googlesource.com/angle/angle>

This is based off the UWP template in the old MS fork of ANGLE, and ported to C++/WinRT.
The template is still viewable at <https://github.com/microsoft/angle/tree/2017-lkg/templates/10/Windows/Universal/CoreWindowUniversal>.

To get the template code to compile, had to make similar changes to those in
<https://github.com/CartoDB/mobile-sdk/commit/e7c325f44c91350d0c2f68252f12d2b001ac733e>
(found after the fact searching for EGL_ANGLE_DISPLAY_ALLOW_RENDER_TO_BACK_BUFFER).

To build ANGLE, clone the repo as described in the ANGLE link above. Run `gn gen out/DebugUwp`
and then `gn args out/DebugUwp`, and set the build args to:

```text
target_os = "winuwp"
is_clang = false
```

Then build with `autoninja -C out/DebugUwp`.

_(TODO: Build fails if `is_clang` is not set. However appears to force MSVC to build
targeting UWP, and tries to use "CL.exe" with the wrong defaults. Figure this out
and either log a bug or fix it.)_

## C++ with WRL
This repo then has two projects. The one in the .\WRL directory can be built from
the command line with MSVC or Clang, and only uses the WRL libraries, not C++/WinRT
or C++/CX. This would work in most other environments the easiest. To use, just
CD into the WRL directory and run `build` or `build clang` followed by `build pack`.
This last step will also register the built AppX on your machine to run.

## C++/WinRT
The project in the root of the repo is a C++/WinRT Visual Studio 2019 project. After
building, copy the below 3 files to the `x64\Debug\CoreAppAngle\AppX` directory before deploying.

- libEGL.dll
- libGLESv2.dll
- zlib.dll

(_TODO: Figure out how to copy these at build time_)

If your ANGLE project is at a different location than `C:\src\angle`, then update
the paths in the .vcxproj file accordingly.
