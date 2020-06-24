A UWP sample app using the ANGLE library (https://chromium.googlesource.com/angle/angle)

To get the template code to compile, had to make similar changes to those in
https://github.com/CartoDB/mobile-sdk/commit/e7c325f44c91350d0c2f68252f12d2b001ac733e
(found after the fact searching for EGL_ANGLE_DISPLAY_ALLOW_RENDER_TO_BACK_BUFFER).

To build ANGLE, clone the repo as described in the ANGLE link above. Set the args.gn
to contain

```text
target_os = "winuwp"
is_clang = false
```

After building copy the below 3 files to the `x64\Debug\CoreAppAngle\AppX` directory
before deploying. (TODO: Figure out how to copy these at build time).

- libEDL.dll
- libGLESv2.dll
- zlib.dll

If your ANGLE project is at a different location than `C:\src\angle`, then update
the paths in the .vcxproj file accordingly.
