@echo off

set compilerFlags=-O2 -Oi -GS-
set linkerFlags=/INCREMENTAL:NO /NOLOGO /STACK:0x100000,0x100000 /HEAP:0x100000,0x100000 /SUBSYSTEM:WINDOWS /NODEFAULTLIB
set warningExceptions=
set preprocessor=-D__DEV__=0 -D__WIN32__=1
set debugFlags=

IF NOT EXIST Build\ mkdir Build\
pushd Build\

::Win32::
cl %preprocessor% %compilerFlags% ..\src\Win32Main.c %debugFlags% kernel32.lib user32.lib /link %linkerFlags% /ENTRY:win32Start /OUT:FullscreenCursorLockEcks.exe 
::/Win32::

popd
@REM exit