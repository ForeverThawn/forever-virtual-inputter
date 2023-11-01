#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#if !defined __STDC__ || !__STDC__
#ifndef const
#define const
#endif
#endif

#ifndef _WINDOWS_
#  include <windows.h>
#endif

#ifndef _INC_STDIO
#  include <stdio.h>
#endif

#ifndef _INC_STRING
#  include <string.h>
#endif

#ifdef __GNU_LIBRARY__
#  include <stdlib.h>
#endif

#ifndef _GCC_WRAP_STDINT_H
#  include <stdint.h>
#endif

#ifndef NULL
#define NULL (void*)0
#endif

int32_t opterr = 1;
int32_t optind = 1;
int32_t optopt;

int32_t 
getopt
(const int32_t argc, TCHAR** argv, const TCHAR* opts, TCHAR** optarg) 
{
    static int32_t sp = 1;
    int32_t c;
    char* cp;

    if (sp == 1) 
    {
        if (optind >= argc ||
            argv[optind][0] != '-' || argv[optind][1] == '\0')
            return EOF;
        else if (!strcmp(argv[optind], "--")) 
        {
            optind++;
            return EOF;
        }
    }
    optopt = c = argv[optind][sp];
    if (c == ':' || !(cp = strchr(opts, c)))
    {
        fprintf(stderr, "Error: illegal option -- %c\n", c);
        if (argv[optind][++sp] == '\0') 
        {
            optind++;
            sp = 1;
        }
        return '?';
    }
    if (*++cp == ':') 
    {
        if (argv[optind][sp + 1] != '\0')
            *optarg = &argv[optind++][sp + 1];
        else if (++optind >= argc) 
        {
            fprintf(stderr, "Error: option requires an argument -- %c\n", c);
            sp = 1;
            return '?';
        }
        else
            *optarg = argv[optind++];
        sp = 1;
    }
    else 
    {
        if (argv[optind][++sp] == '\0') 
        {
            sp = 1;
            optind++;
        }
        *optarg = NULL;
    }
    return c;
}


#ifdef DEBUG
int main(int argc, char** argv)
{
    char *optarg;
    int c;
    while (c = getopt(argc, argv, "vt:f:", &optarg))
    {
        switch (c)
        {
            case 'v':
                fprintf(stdout, "v\r\n");
                break;
            case 't':
                fprintf(stdout, "t\r\n");
                fprintf(stdout, "%s\r\n", optarg);
                break;
            case 'f':
                fprintf(stdout, "f\r\n");
                fprintf(stdout, "%s\r\n", optarg);
                break;
            default:
                return 0;
        }
    }
    return 0;
}
#endif