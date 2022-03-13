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

// für Matrix
#define SERPENTINEN true
#define ZEILENWEISE false
#define ZEILENZAHL 10
#define SPALTENZAHL 10