#include "serial.h"

/*
 * 'open_port()' - Open serial port 1.
 *
 * Returns the file descriptor on success or -1 on error.
 */

struct termios oldtio, newtio; 

int open_port(void){

int fd; /* File descriptor for the port */



fd = open("/dev/ttyUSB_SC", O_RDWR | O_NOCTTY | O_NDELAY);

if (fd == -1) {
       /*
	* Could not open the port.
	*/

	perror("open_port: Unable to open /dev/ttyUSB_SC - ");
}
else{
  fcntl(fd, F_SETFL, 0);
  tcgetattr(fd,&oldtio);
  tcgetattr(fd,&newtio);
  newtio.c_cflag=B115200|CS8|CLOCAL|CREAD;

  tcflush(fd,TCIFLUSH);
  tcsetattr(fd,TCSANOW,&newtio);
}
return (fd);
}

void closePort(int fd)
{
	tcsetattr(fd, TCSANOW, &oldtio);
	close(fd);
}

