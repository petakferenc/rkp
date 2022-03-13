#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if defined(linux) || defined(_linux) || defined(__linux__) || defined(__unix__)
#define OSTYPE 1
#elif defined(_WIN32) || defined(_WINDOWS) || defined(__WINDOWS__)
#define OSTYPE 2
#elif defined(MSDOS) || defined(_MSDOS) || defined(__MSDOS__)
#define OSTYPE 3
#elif (defined(__MACH__) && defined(__APPLE__))
#define OSTYPE 4
#else
#define OSTYPE 0
#endif

void determine_ostype(char *actual_filename);
void print_help();
void print_version();
void do_comm(char mode, char comm_type);
int find_argument(int argc, char *argv[], const char *argument);
void check_filename(const char *filename, char *actual_filename, const char *delimeter);

int main(int argc, char *argv[])
{
    char mode = 's';
    char comm_type = 'f';
    determine_ostype(argv[0]);

    if (argc == 2)
    {
        if (find_argument(argc, argv, "--version") == 0)
        {
            print_version();
        }
        else if ((find_argument(argc, argv, "--help") == 0))
        {
            print_help();
        }
    }
    if (find_argument(argc, argv, "--socket") == 0)
    {
        comm_type = 's';
    }
        if (find_argument(argc, argv, "--receive") == 0)
    {
        mode = 'r';
    }

    do_comm(mode, comm_type);

    return 0;
}

void determine_ostype(char *actual_filename)
{

    switch (OSTYPE)
    {
    case 1:
        printf("This is a Unix/Linux system.\n");
        check_filename("chart.out", actual_filename, "/");
        break;
    case 2:
        printf("This is a Windows system.\n");
        check_filename("chart.exe", actual_filename, "\\");
        break;
    case 3:
        printf("This is a MS-DOS system.\n");
        break;
    case 4:
        printf("This is an Apple/Machintos system.\n");
        break;
    default:
        printf("I don't know what kind of operating system is this.\n");
    }
}

void print_help()
{
    printf("Ha a ”--help” argumentummal indul a program, akkor adjontájékoztatást a felhasználónak a futtatás lehetséges opcióiról, a lehetséges parancssoriargumentumok jelentéséről!\n");
    printf("Ha a ”--version” parancssori argumentummal indítjuk el a programot, ennél az opciónál program verziószámát, elkészültének dátumát és a fejlesztő nevét!\n");
    printf("send\n");
    printf("receive\n");
    printf("file\n");
    printf("socket\n");
}
void print_version()
{
    printf("prints out version\n");
    printf("klek\n");
    printf("oemgalul\n");
}

void do_comm(char mode, char comm_type)
{
    if (comm_type == 'f' && mode == 's')
    {
        printf("sending to files");
    }
    else if (comm_type == 's' && mode == 's')
    {
        printf("sending to socket");
    }
    else if (comm_type == 's' && mode == 'r')
    {
        printf("receiving from socket");
    }
    else if (comm_type == 'f' && mode == 'r')
    {
        printf("receiving from file");
    }
    else
    {
        printf("unknown comm_type");
    }
}

int find_argument(int argc, char *argv[], const char *argument)
{
    for(int i = 1; i<argc; i++)
    {
        if (strcmp(argv[i], argument) == 0)
        {
            return 0;
        }
    }
    return 1;
}

void check_filename(const char *filename, char *actual_filename, const char *delimeter)
{
    char *path = strtok(actual_filename, delimeter);
    char *result;
   while (path != NULL) { 
     
      path = strtok(NULL, delimeter);
      if (path != NULL)
      {
          result = path;
      }
   }
   printf("%s\n", result);
   printf("%d", strcmp(filename, result));
    if (strcmp(filename, result) != 0)
    {
        printf("A futtatható állománynak nem az a neve hogy chart\n");
        exit(0);
    }
    printf("%s", filename);
    printf("%s", actual_filename);
}
