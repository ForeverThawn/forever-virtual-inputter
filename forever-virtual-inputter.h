#ifndef _FOREVER_VIRTUAL_INPUTTER
#define _FOREVER_VIRTUAL_INPUTTER
#ifndef _INC_STDIO 
#  include <stdio.h>
#endif
#ifndef _INC_STRING
#  include <stdlib.h>
#endif
#ifndef _WINDOWS_
#  include <windows.h>
#endif
#define ONEXIT SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE)

BOOL CtrlHandler(DWORD fdwctrltype);
FILE* GetFileDialog(void);
int32_t getopt(const int argc, TCHAR** argv, const TCHAR* opts, TCHAR** optarg);
int32_t __cdecl required_shift(TCHAR ch);
int32_t ParseCharacter(FILE** file);
enum 
{
    FileError = -2,
    TimeError = -1,
    Ok = 0,
    Normal = 1,
    UserInterrupt = 2
};

#endif