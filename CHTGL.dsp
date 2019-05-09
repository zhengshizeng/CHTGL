# Microsoft Developer Studio Project File - Name="CHTGL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CHTGL - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CHTGL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CHTGL.mak" CFG="CHTGL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CHTGL - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CHTGL - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CHTGL - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "CHTGL - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=CHTGL.bat
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "CHTGL - Win32 Release"
# Name "CHTGL - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AddCustomerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AddHTDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AddQWRDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AddSFKDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CHTGL.cpp
# End Source File
# Begin Source File

SOURCE=.\CHTGL.rc
# End Source File
# Begin Source File

SOURCE=.\CHTGLDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBtnChange.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTcglAddByHT.cpp
# End Source File
# Begin Source File

SOURCE=.\excel.cpp
# End Source File
# Begin Source File

SOURCE=.\Kpgl_Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MyExcelz.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectHTDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\SHTListDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SysSetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TcglDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\YuJingDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AddCustomerDlg.h
# End Source File
# Begin Source File

SOURCE=.\AddHTDlg.h
# End Source File
# Begin Source File

SOURCE=.\AddQWRDlg.h
# End Source File
# Begin Source File

SOURCE=.\AddSFKDlg.h
# End Source File
# Begin Source File

SOURCE=.\CHTGL.h
# End Source File
# Begin Source File

SOURCE=.\CHTGLDlg.h
# End Source File
# Begin Source File

SOURCE=.\CMFC5286D.H
# End Source File
# Begin Source File

SOURCE=.\DlgBtnChange.h
# End Source File
# Begin Source File

SOURCE=.\DlgTcglAddByHT.h
# End Source File
# Begin Source File

SOURCE=.\excel.h
# End Source File
# Begin Source File

SOURCE=.\Kpgl_Dlg.h
# End Source File
# Begin Source File

SOURCE=.\MyExcelz.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SelectHTDLG.h
# End Source File
# Begin Source File

SOURCE=.\SHTListDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SysSetDlg.h
# End Source File
# Begin Source File

SOURCE=.\TcglDlg.h
# End Source File
# Begin Source File

SOURCE=.\YuJingDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bk.bmp
# End Source File
# Begin Source File

SOURCE=.\res\btn_GYS.bmp
# End Source File
# Begin Source File

SOURCE=.\res\btn_HTGL_A.bmp
# End Source File
# Begin Source File

SOURCE=.\res\btn_HTGL_D.bmp
# End Source File
# Begin Source File

SOURCE=.\res\btn_HTGL_S.bmp
# End Source File
# Begin Source File

SOURCE=.\res\btn_KFGL.bmp
# End Source File
# Begin Source File

SOURCE=.\res\btn_QYR.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CHTGL.ico
# End Source File
# Begin Source File

SOURCE=.\res\CHTGL.rc2
# End Source File
# Begin Source File

SOURCE=.\res\htgl.bmp
# End Source File
# Begin Source File

SOURCE=.\res\jbsx.bmp
# End Source File
# Begin Source File

SOURCE=.\res\kpgl.bmp
# End Source File
# Begin Source File

SOURCE=.\res\qrcode.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tcgl.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wlgl.bmp
# End Source File
# Begin Source File

SOURCE=.\res\yjsx.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
