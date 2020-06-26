@SETLOCAL

SET INCLUDE=%INCLUDE%;C:\src\angle\include
SET LIB=%LIB%;C:\src\angle\out\DebugUwp

SET CL=/std:c++17 /Zi /EHsc /Od /MDd /permissive- /W3 /DWINAPI_FAMILY#WINAPI_FAMILY_APP /D_DEBUG
SET LINK=/SUBSYSTEM:WINDOWS /APPCONTAINER /DEBUG libEGL.dll.lib libGLESv2.dll.lib windowsapp.lib

SET SRC=app.cpp SimpleRenderer.cpp

if "%1" == "clean" del *.exe *.obj *.pdb *.ilk *.appx

if "%1" == "" cl.exe %SRC%

if "%1" == "clang" C:\src\angle\third_party\llvm-build\Release+Asserts\bin\clang-cl.exe %SRC% /clang:-fuse-ld=lld-link

if NOT "%1" == "pack" goto :EOF

:: Rebuild and pack the Appx package
rmdir /s /q .\appx
del .\CoreAppAngle.appx
mkdir .\appx
mkdir .\appx\Assets
copy /Y /B ".\Package.appxmanifest"                    ".\appx\AppxManifest.xml"
copy /Y /B "C:\src\angle\out\DebugUwp\libEGL.dll"      ".\appx\"
copy /Y /B "C:\src\angle\out\DebugUwp\libGLESv2.dll"   ".\appx\"
copy /Y /B "C:\src\angle\out\DebugUwp\zlib.dll"        ".\appx\"
copy /Y /B ".\app.exe"                                   ".\appx\"
copy /Y /B "..\Assets\StoreLogo.png"                   ".\appx\Assets\"
copy /Y /B "..\Assets\SplashScreen.scale-200.png"      ".\appx\Assets\"
copy /Y /B "..\Assets\Square150x150Logo.scale-200.png" ".\appx\Assets\"
copy /Y /B "..\Assets\Square44x44Logo.scale-200.png"   ".\appx\Assets\"

MakeAppx pack /d .\appx /p CoreAppAngle.appx
PowerShell -command "Add-AppxPackage -Register .\appx\AppxManifest.xml"
