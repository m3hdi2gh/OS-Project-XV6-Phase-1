#ifndef CUSTOM_LOGGER_H
#define CUSTOM_LOGGER_H

enum log_level { INFO = 0, WARN = 1, ERROR = 2 };

void log_message(enum log_level level, const char *msg);

#endif
