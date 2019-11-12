#ifndef SERIAL_H
#define SERIAL_H

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

#ifdef __cplusplus
extern "C"
{
#endif

int open_port(void);

void closePort(int fd);

#ifdef __cplusplus
}
#endif

#endif
