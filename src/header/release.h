#ifndef RELEASE_H
#define RELEASE_H

/*
if you want the finished code without the Debuginformation,
you can set the relase to false
if you
*/
#define RELEASE false

#if !RELEASE
#define DEBUG_PRINT(x)     \
    do                     \
    {                      \
        Serial.println(x); \
    } while (0)
#else
#define DEBUG_PRINT(x)
#endif

#if !RELEASE
#define DEBUG(x) \
    do           \
    {            \
        x        \
    } while (0)
#else
#define DEBUG(x)
#endif

// for Matrix
/*
if the LEDs are connected like:
0 -- 1 -- 2 -- 3
               |
7 -- 6 -- 5 -- 4
|
8 -- 9 -- ...
*/
#define SERPENTINES true

/*
if the LEDs are connected like:
0 -- 1 -- 2 -- 3
              /
  ------------
/
4 -- 5 -- 6 -- 7
              /
  ------------
/
8 -- 9 -- ...
*/
#define LINEBYLINE false

/*defines the row count of the matrix*/
constexpr int rowcount = 10;
/*defines the coloum count of the matrix*/
constexpr int colcount = 10;

// Takes care of the time change. Winter- summer time
#define MYTZ TZ_Europe_Berlin

#endif