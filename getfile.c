#ifndef _INC_STDIO
#  include <stdio.h>
#endif
#ifndef _INC_STRING
#  include <stdlib.h>
#endif
#ifndef _WINDOWS_
#  include <windows.h>
#endif

TCHAR typeFilter[64] =
{
    "Text (txt, text)\0*.txt;*.text\0"
    "All (*)\0*.*\0"
};

FILE* 
GetFileDialog
(void)
{
    FILE *file;
    TCHAR fPath[MAX_PATH];

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = fPath;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = MAX_PATH - 1;
    ofn.lpstrFilter = typeFilter;
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn))
    {
        file = fopen(fPath, "r");
        if (file == NULL)
        {
            perror("Error: when opening a txt file\r\n");
            return NULL;
        }
    }
}