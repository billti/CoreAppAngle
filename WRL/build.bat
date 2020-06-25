@SETLOCAL

SET INCLUDE=%INCLUDE%;C:\src\angle\include
SET LIB=%LIB%;C:\src\angle\out\DebugUwp

SET CL=/std:c++17 /EHsc /Od /MDd /permissive- /W3 /DWINAPI_FAMILY#WINAPI_FAMILY_APP /D_DEBUG
SET LINK=/SUBSYSTEM:WINDOWS /APPCONTAINER libEGL.dll.lib libGLESv2.dll.lib windowsapp.lib

SET SRC=app.cpp SimpleRenderer.cpp

cl.exe %SRC%

copy /Y /B C:\src\angle\out\DebugUwp\libEGL.dll .\
copy /Y /B C:\src\angle\out\DebugUwp\libGLESv2.dll .\
copy /Y /B C:\src\angle\out\DebugUwp\zlib.dll .\
