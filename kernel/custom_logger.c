#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "custom_logger.h"

static char *level_str[] = { "INFO", "WARNING", "ERROR" };

void
log_message(enum log_level level, const char *msg)
{
  if(level < 0 || level > 2)
    level = INFO;
  printf("%s — %s\n", level_str[level], msg);
}
