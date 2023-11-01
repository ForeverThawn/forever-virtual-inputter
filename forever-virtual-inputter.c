#ifndef _INC_STDIO
#  include <stdio.h>
#endif
#ifndef _INC_STRING
#  include <stdlib.h>
#endif
#ifndef _WINDOWS_
#  include <windows.h>
#endif
#ifndef _GCC_WRAP_STDINT_H
#  include <stdint.h>
#endif
#ifndef _FOREVER_VIRTUAL_INPUTTER
#  include "forever-virtual-inputter.h"
#endif


FILE *file;
int32_t c;
TCHAR *arg;
const TCHAR *version = "1.0";
extern DWORD offTime;
BOOL fFile = FALSE;
uint32_t optindex = 0;
extern TCHAR *fPath;

const TCHAR* help =
{
    "\r\n"
    "Forever Virtual Inputter\r\n"
    "\r\n"
    "Usage: fvi\r\n"
    "Usage: fvi [<switches>...] <archive_name>/<off_time>\r\n"
    "\r\n"
    "<Switches>\r\n"
    "  -h  :  Show this message\r\n"
    "  -f  :  Specify a text file\r\n"
    "  -t  :  Specify off time (default: 25)\r\n"
    "  -v  :  Check version\r\n"
    "\r\n"
    "Examples:\r\n"
    "  fvi -f test.txt\r\n"
    "  fvi -t 50 -f test.txt\r\n"
};

int32_t 
main
(int32_t argc, TCHAR** argv)
{
    MessageBoxA(NULL, help, "Forever Virtual Inputter Help", MB_OK); // A
    offTime = 25;
    if (argc == 1)
    {
        if (ONEXIT)
        {
            file = GetFileDialog();
            if (file == NULL)
            {
                fprintf(stderr, "Error: No file input!\r\n");
                return FileError;
            }
            if (!ParseCharacter(&file))
                return Normal;
            return Ok;
        }
    }
    else
    {
        if (ONEXIT)
        {
            while ((c = getopt(argc, argv, "hvt:f:", &arg)) && optindex < argc)
            {
                switch (c)
                {
                case 'h':
                    fprintf(stdout, "%s\r\n", help);
                    return Ok;

                case 'v':
                    fprintf(stdout, "%s\r\n", version);
                    return Ok;

                case 't':
                    if (EOF == sscanf(arg, "%u", &offTime))
                    {
                        perror("Error: Off time invalid!\r\n");
                        return TimeError;
                    }
                    break;

                case 'f':
                    fFile = TRUE;
                    fPath = arg;
                    break;

                default:
                    break;
                }
                optindex++;
            }
        }
        if (fFile)
        {
            file = fopen(fPath, "r");
            if (file == NULL)
            {
                fprintf(stderr, "Error: No file input!\r\n");
                return FileError;
            }
            if (ParseCharacter(&file))
                return Ok;
        }
        return Ok;
    }
}

BOOL 
CtrlHandler
(DWORD fdwctrltype)
{
    switch (fdwctrltype)
    {
    case CTRL_C_EVENT:
        Sleep(200);
        printf("\r\n\r\nUser Interrupt..\r\n");
        return FALSE;

    case CTRL_SHUTDOWN_EVENT:
    case CTRL_LOGOFF_EVENT:
    case CTRL_CLOSE_EVENT:
        Sleep(200);
        printf("\r\n\r\nConsole Terminated..\r\n");
        return FALSE;

    case CTRL_BREAK_EVENT:
        Sleep(200);
        return FALSE;

    default:
        return FALSE;
    }
}