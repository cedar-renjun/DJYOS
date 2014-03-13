# Microsoft Developer Studio Project File - Name="djy_vc6" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=djy_vc6 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "djy_vc6.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "djy_vc6.mak" CFG="djy_vc6 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "djy_vc6 - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "djy_vc6 - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "djy_vc6 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "djy_vc6 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I ".\\" /I "..\src\user\include" /I "..\..\..\..\djysrc\bsp\cpu_peripheral\windows\include" /I "..\..\..\..\djysrc\djyos\djyfs\include" /I "..\..\..\..\djysrc\djyos\gui\include" /I "..\..\..\..\djysrc\djyos\include" /I "..\..\..\..\djysrc\bsp\board_peripheral\windows\include" /I "..\..\..\..\djysrc\bsp\arch\windows\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# SUBTRACT CPP /WX
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "djy_vc6 - Win32 Release"
# Name "djy_vc6 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "arch"

# PROP Default_Filter ""
# Begin Group "windows"

# PROP Default_Filter ""
# Begin Group "core"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\bsp\arch\windows\core\cpu.c
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\bsp\arch\windows\core\exception.c
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\bsp\arch\windows\core\int_hard.c
# End Source File
# End Group
# End Group
# Begin Group "cpu_peripheral"

# PROP Default_Filter ""
# Begin Group "src"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\bsp\cpu_peripheral\windows\src\command.c
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\bsp\cpu_peripheral\windows\src\cpu_peri_keyboard.c
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\bsp\cpu_peripheral\windows\src\cpu_peri_lcd_touch_mouse.c
# End Source File
# End Group
# End Group
# End Group
# Begin Group "djyos"

# PROP Default_Filter ""
# Begin Group "buffer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\buffer\line.c
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\buffer\ring.c
# End Source File
# End Group
# Begin Group "clock"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\clock\clock.c
# End Source File
# End Group
# Begin Group "djyfs"

# PROP Default_Filter ""
# Begin Group "flashfile"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\djyfs\flashfile\ddr.c
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\djyfs\flashfile\ecc256.c
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\djyfs\flashfile\fdt.c
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\djyfs\flashfile\flashfile.c
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\djyfs\flashfile\mdr.c
# End Source File
# End Group
# Begin Group "include No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\djyfs\include\ddr.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\djyfs\include\djyFAT32.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\djyfs\include\djyramfs.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\djyfs\include\djyramfs_ddr.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\djyfs\include\djyramfs_fdt.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\djyfs\include\djyramfs_mdr.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\djyfs\include\ecc256.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\djyfs\include\fdt.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\djyfs\include\file.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\djyfs\include\flashfile.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\djyfs\include\mdr.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\djyfs\file.c
# End Source File
# End Group
# Begin Group "core No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\core\djyos.c
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\core\endian.c
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\core\sys_init.c
# End Source File
# End Group
# Begin Group "driver"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\driver\driver.c
# End Source File
# End Group
# Begin Group "gui"

# PROP Default_Filter ""
# Begin Group "display"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\display\gk_display.c
# End Source File
# End Group
# Begin Group "encoding"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\encoding\ascii.c
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\encoding\ascii.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\encoding\encoding.c
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\encoding\encoding.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\encoding\gb2312.c
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\encoding\gb2312.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\encoding\loc_string.c
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\encoding\loc_string.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\encoding\nls.c
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\encoding\nls.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\encoding\utf8.c
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\encoding\utf8.h
# End Source File
# End Group
# Begin Group "font"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\font\ascii8x16.c
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\font\ascii8x16.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\font\ascii8x8.c
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\font\ascii8x8.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\font\font.c
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\font\font.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\font\gb2312_16.c
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\font\gb2312_16.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\font\textshow.c
# End Source File
# End Group
# Begin Group "gk_draw"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\gk_draw\gk_draw.c
# End Source File
# End Group
# Begin Group "include No. 2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\include\Ascii.h
# End Source File
# Begin Source File

SOURCE=".\..\..\..\..\djysrc\djyos\gui\include\config-gui.h"
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\include\gk_api.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\include\gk_clip.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\include\gk_display.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\include\gk_draw.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\include\gk_inc.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\include\gk_syscall.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\include\gk_usercall.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\include\gk_win.h
# End Source File
# End Group
# Begin Group "lib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\lib\gk_api.c
# End Source File
# End Group
# Begin Group "window"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\window\gk_clip.c
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\gui\window\gk_win.c
# End Source File
# End Group
# End Group
# Begin Group "include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\char_term.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\clock.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\critical.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\djyos.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\driver.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\endian.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\int.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\kernel.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\keyboard.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\line.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\lock.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\memb.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\memory.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\mems.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\msg.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\os_inc.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\pipe.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\ring.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\rsc.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\shell.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\shell_fs.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\stdin_dev.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\sys_init.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\Touch.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\version.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\include\wdt.h
# End Source File
# End Group
# Begin Group "int"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\int\int.c
# End Source File
# End Group
# Begin Group "lock"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\lock\lock.c
# End Source File
# End Group
# Begin Group "memory"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\memory\memb.c
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\memory\mems.c
# End Source File
# End Group
# Begin Group "pipe"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\pipe\pipe.c
# End Source File
# End Group
# Begin Group "rsc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\rsc\rsc.c
# End Source File
# End Group
# Begin Group "shell"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\shell\shell.c
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\shell\shell_fs.c
# End Source File
# End Group
# Begin Group "stdin"

# PROP Default_Filter ""
# Begin Group "char_term"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\stdin\char_term\char_term.c
# End Source File
# End Group
# Begin Group "keypad"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\stdin\keypad\keyboard.c
# End Source File
# End Group
# Begin Group "touch"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\stdin\touch\Touch.c
# End Source File
# End Group
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\stdin\stdin_dev.c
# End Source File
# End Group
# Begin Group "wdt"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\djysrc\djyos\wdt\wdt.c
# End Source File
# End Group
# End Group
# Begin Group "user"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\..\..\..\examples\djysim-vs2010+vc6\src\user\include\config-prj.h"
# End Source File
# Begin Source File

SOURCE=".\..\..\..\examples\djysim-vs2010+vc6\src\user\critical\critical.c"
# End Source File
# Begin Source File

SOURCE=".\..\..\..\examples\djysim-vs2010+vc6\src\user\config\font_songti_16x16.h"
# End Source File
# Begin Source File

SOURCE=".\..\..\..\examples\djysim-vs2010+vc6\src\user\src\main.c"
# End Source File
# Begin Source File

SOURCE=".\..\..\..\examples\djysim-vs2010+vc6\src\user\config\module_init.c"
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
