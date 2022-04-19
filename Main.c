#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

void determine_ostype(char* actual_filename);
void print_help();
void print_version();
void do_comm(char mode, char comm_type);
int find_argument(int argc, char* argv[], const char* argument);
void check_filename(const char* filename, char* actual_filename, const char* delimeter);
int generate_mert_szam();
int Measurement(int** Values);
int max(int a, int b);
void BMPcreator(int *Values, int NumValues);
void printArray(int size, int* values);

int main(int argc, char* argv[])
{
    srand(time(NULL));
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
    int* values;
     int size = Measurement(& values);
     printArray(size, values);
    return 0;
}

void determine_ostype(char* actual_filename)
{

    switch (OSTYPE)
    {
    case 1:
       // printf("This is a Unix/Linux system.\n");
        check_filename("chart", actual_filename, "/");
        break;
    case 2:
       // printf("This is a Windows system.\n");
        check_filename("chart.exe", actual_filename, "\\");
        break;
    case 3:
        //printf("This is a MS-DOS system.\n");
        break;
    case 4:
       // printf("This is an Apple/Machintos system.\n");
        check_filename("chart", actual_filename, "/");
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
        printf("sending to files\n");
    }
    else if (comm_type == 's' && mode == 's')
    {
        printf("sending to socket\n");
    }
    else if (comm_type == 's' && mode == 'r')
    {
        printf("receiving from socket\n");
    }
    else if (comm_type == 'f' && mode == 'r')
    {
        printf("receiving from file\n");
    }
    else
    {
        printf("unknown comm_type\n");
    }
}

int find_argument(int argc, char* argv[], const char* argument)
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], argument) == 0)
        {
            return 0;
        }
    }
    return 1;
}

void check_filename(const char* filename, char* actual_filename, const char* delimeter)
{
    char* path = strtok(actual_filename, delimeter);
    char* result;
    while (path != NULL) {

        path = strtok(NULL, delimeter);
        if (path != NULL)
        {
            result = path;
        }
    }
    if (strcmp(filename, result) != 0)
    {
        printf("A futtatható állománynak nem az a neve hogy chart\n");
        exit(0);
    }
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int generate_mert_szam()
{
    time_t raw_time;
    struct tm* actual_local_time;
    time(&raw_time);
    actual_local_time = localtime(&raw_time);
    int seconds = (((*actual_local_time).tm_min % 15) * 60) + (*actual_local_time).tm_sec;
    return max(100,seconds);
}
int Measurement(int** Values)
{
    // 42,8571% size * 0,428571 =?x
  // 11/31   size * (11/31) =?y
  // rest    size - x - y
    int size = generate_mert_szam();
    int* values = (int*)calloc(size, sizeof(int));
    double firstG = size * 0.428571;
    double secondG = (size / 31) * 11;
    double thirdG = ceil((double)(size - firstG - secondG));
    
    for (int i = 1; i < size; i++)
    {
        int r = rand() % 3;
        while (1) {
           r = rand() % 3;
           if (r == 0 && firstG != 0)
           {
               break;

           }
           else if (r == 1 && secondG != 0)
           {
               break;
           }
           else if (r == 2 && thirdG != 0)
           {
               break;
           }
        }
       
       
        if (r == 0  )
        {
                values[i] = values[i - 1] + 1;
                firstG--;
            

        }else if(r == 1)
        {
            values[i] = values[i - 1] - 1;
            secondG--;
        }
        else if (r == 2)
        {
            values[i] = values[i - 1];
            thirdG--;
        }
    }
    


    (*Values) = values;

    return size;
}

void printArray(int size, int* values)
{
    for (int i = 0; i < size; i++) 
    {
        printf("%d=%d \n", i, values[i]);
    }
}


void BMPcreator(int * values, int size) {
    int WIDTH = size;
    int HEIGHT = size;
    unsigned int headers[13];
    FILE* outfile;
    int extrabytes;
    int paddedsize;
    int x; int y; int n;
    int red, green, blue;

    extrabytes = 4 - ((WIDTH * 3) % 4);                 // How many bytes of padding to add to each
                                                        // horizontal line - the size of which must
                                                        // be a multiple of 4 bytes.
    if (extrabytes == 4)
        extrabytes = 0;

    paddedsize = ((WIDTH * 3) + extrabytes) * 21;

    // Headers...
    // Note that the "BM" identifier in bytes 0 and 1 is NOT included in these "headers".

    headers[0] = paddedsize + size*2;      // bfSize (whole file size)
    headers[1] = 0;                    // bfReserved (both)
    headers[2] = 54;                   // bfOffbits
    headers[3] = 40;                   // biSize
    headers[4] = WIDTH;  // biWidth
    headers[5] = HEIGHT; // biHeight

    // Would have biPlanes and biBitCount in position 6, but they're shorts.
    // It's easier to write them out separately (see below) than pretend
    // they're a single int, especially with endian issues...

    headers[7] = 0;                    // biCompression
    headers[8] = paddedsize;           // biSizeImage
    headers[9] = 0;                    // biXPelsPerMeter
    headers[10] = 0;                    // biYPelsPerMeter
    headers[11] = 0;                    // biClrUsed
    headers[12] = 0;                    // biClrImportant

    outfile = fopen("chart.bmp", "wb");

    //
    // Headers begin...
    // When printing ints and shorts, we write out 1 character at a time to avoid endian issues.
    //

    fprintf(outfile, "BM");

    for (n = 0; n <= 5; n++)
    {
        fprintf(outfile, "%c", headers[n] & 0x000000FF);
        fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
        fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
        fprintf(outfile, "%c", (headers[n] & (unsigned int)0xFF000000) >> 24);
    }

    // These next 4 characters are for the biPlanes and biBitCount fields.

    fprintf(outfile, "%c", 1);
    fprintf(outfile, "%c", 0);
    fprintf(outfile, "%c", 24);
    fprintf(outfile, "%c", 0);

    for (n = 7; n <= 12; n++)
    {
        fprintf(outfile, "%c", headers[n] & 0x000000FF);
        fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
        fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
        fprintf(outfile, "%c", (headers[n] & (unsigned int)0xFF000000) >> 24);
    }

    //
    // Headers done, now write the data...
    //

    for (x = 0; x <= WIDTH - 1; x++)     // BMP image format is written from bottom to top...
    {
        for (y = HEIGHT-1 ; y >= 0; y--)
            
        {
        
             if (x == (HEIGHT / 2) + values[y]) {
                red = 255;
                green = 0;
                blue = 0;
            }
            else
            {
                red = 0;
                green = 0;
                blue = 255;
            }
        
         

            // Also, it's written in (b,g,r) format...

            fprintf(outfile, "%c", blue);
            fprintf(outfile, "%c", green);
            fprintf(outfile, "%c", red);
        }
        if (extrabytes)      // See above - BMP lines must be of lengths divisible by 4.
        {
            for (n = 1; n <= extrabytes; n++)
            {
                fprintf(outfile, "%c", 0);
            }
        }
    }

    fclose(outfile);
    return;

}
