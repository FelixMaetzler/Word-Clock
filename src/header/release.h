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
#define SERPENTINES true
#define LINEBYLINE false
constexpr int rowcount = 10;
constexpr int colcount = 10;

// Takes care of the time change. Winter- summer time
#define MYTZ TZ_Europe_Berlin