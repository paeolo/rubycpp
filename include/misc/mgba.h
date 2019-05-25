#ifndef MGBA_H
#define MGBA_H
#ifdef __cplusplus
extern "C" {
#endif

#define MGBA_LOG_FATAL 0
#define MGBA_LOG_ERROR 1
#define MGBA_LOG_WARN 2
#define MGBA_LOG_INFO 3
#define MGBA_LOG_DEBUG 4

void mgba_printf(const char* string, ...);

#ifdef __cplusplus
}
#endif
#endif