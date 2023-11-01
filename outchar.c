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

DWORD offTime;
TCHAR *fPath;

int32_t __cdecl 
required_shift
(TCHAR ch)
{
    switch (ch)
    {
        case '~':
        case '!':
        case '@':
        case '#':
        case '$':
        case '%':
        case '^':
        case '&':
        case '*':
        case '(':
        case ')':
        case '{':
        case '}':
        case ':':
        case '"':
        case '<':
        case '>':
        case '?':
        case '|':
        case '_':
        case '+':
            return 1;
            
        default:
           return 0;
    }
}

int32_t 
ParseCharacter
(FILE** file)
{
    TCHAR ch;
    fprintf(stdout, "Task will be executed in 5 seconds\r\n\r\n");
    fprintf(stdout, "File Path : %s\r\n", fPath);
    fprintf(stdout, "Off Time  : %u ms\r\n\r\n", offTime);
    fprintf(stdout, "Waiting...\r\n");
    Sleep(5000);
    fprintf(stdout, "Task running...\r\n");

    fprintf(stdout, "\r\nCurrent character >> ");
    while ((ch = fgetc(*file)) != EOF)
    {
        if (isprint(ch))
        {
            fprintf(stdout, "\rCurrent character >> %c", ch);
            INPUT input;
            input.type = INPUT_KEYBOARD;
            input.ki.wScan = 0;
            input.ki.time = 0;
            input.ki.dwExtraInfo = 0;
            
            if (isupper(ch) || required_shift(ch))
            {
                input.ki.wVk = VK_SHIFT;
                input.ki.dwFlags = 0;
                SendInput(1, &input, sizeof(INPUT));
            }

            input.ki.wVk = VkKeyScan(ch);
                    
            input.ki.dwFlags = 0;
            SendInput(1, &input, sizeof(INPUT));

            input.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &input, sizeof(INPUT));
                    
            if (isupper(ch) || required_shift(ch))
            {
                input.ki.wVk = VK_SHIFT;
                input.ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(1, &input, sizeof(INPUT));
            }
        }
        else if (ch == '\n')
        {
            fprintf(stdout, "\rCurrent character >> \\n");
            INPUT enterInput[2];
            enterInput[0].type = INPUT_KEYBOARD;
            enterInput[0].ki.wVk = VK_RETURN;
            enterInput[0].ki.dwFlags = 0; // 模拟按下回车键
            enterInput[1] = enterInput[0]; 
            enterInput[1].ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(2, enterInput, sizeof(INPUT));
        }
        Sleep(offTime);
        fprintf(stdout, "\r                         ");
    }
    fprintf(stdout, "\r\nDone!\r\n");
    fclose(*file);
    return 0;
}