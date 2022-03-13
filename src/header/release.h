#define SERIAL_DEBUG true
#if SERIAL_DEBUG
#define DEBUG_PRINT(x) do {Serial.println(x);} while (0)
#else
#define DEBUG_PRINT(x)
#endif