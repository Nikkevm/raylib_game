@echo off

cl /Zi /DDEV main.c resources.c dev.c ui.c map.c entity.c enemy.c /Fobuild\ /Fdbuild\ /I"G:/sdks/include/raylib/" /link /MACHINE:X64 /out:"game_debug.exe" "G:/sdks/libs/raylib/raylib.lib" opengl32.lib kernel32.lib user32.lib shell32.lib gdi32.lib winmm.lib msvcrt.lib /NODEFAULTLIB:libcmt
