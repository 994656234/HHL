#include "command.h"

#include <string.h>
#include <stdio.h>

void printHexString(char *str);
void printHexStringBytes(char *str, int nbytes);

//private
void send_command_0(int fd, int command){

  char sendString[30];
  int n;

  sprintf(sendString,"!#%d\n", command);
  n=write(fd,sendString,strlen(sendString));

  if (n<0){
	fputs("write failed",stderr);
  }
}


void send_enter(int fd){

  char sendString[30];
  int n;

  sprintf(sendString,"\n");
  n=write(fd,sendString,strlen(sendString));

  if (n<0){
	fputs("write failed",stderr);
  }

}

commandReplyType getAnswer(int fd, char *buff){

	char buffer[255];  /* Input buffer */
        char *bufptr;      /* Current char in buffer */
        int  nbytes;       /* Number of bytes read */
	char errorStr[255];
	char errorStr2[255];

	/*receive val*/
        /* read characters into our string buffer until we get a CR or NL */
	 bufptr = buffer;
	 while ((nbytes = read(fd, bufptr, buffer + sizeof(buffer) - bufptr - 1)) > 0){
	   bufptr += nbytes;
	   if (bufptr[-1] == '\n' || bufptr[-1] == '\r'){
             break;
	   }
	 }

        /* nul terminate the string and see if we got an OK response */
	*bufptr = '\0';

///	printf("Full reply: %s\n",buffer);
///	printHexString(buffer);	


	strcpy(buff,buffer);	
	sprintf(errorStr,"\x001#200,01,BF\n");
	sprintf(errorStr2,"\x006\x001#200,01,BF\n");

	if (!strcmp(errorStr,buffer)){
///	  printf("NAK\n");
	  return NAK;
	}
	if (!strcmp(errorStr2,buffer)){
///	  printf("NAK2\n");
	  return NAK;
	}

	return stringType;
}

//private
void send_command_1(int fd, int command, int arg1){
  char sendString[30];
  int n;


  sprintf(sendString,"!#%d,%d\n", command,arg1);

  n=write(fd,sendString,strlen(sendString));

  if (n<0){
	fputs("write failed",stderr);
  }

}


void send_command_2(int fd, int command, int arg1, int arg2){
  char sendString[30];
  int n;


  sprintf(sendString,"!#%d,%d,%d\n", command,arg1,arg2);

  n=write(fd,sendString,strlen(sendString));

  if (n<0){
	fputs("write failed",stderr);
  }

}

void send_command_3(int fd, int command, int arg1, int arg2, int arg3){
  char sendString[30];
  int n;


  sprintf(sendString,"!#%d,%d,%d,%d\n", command,arg1,arg2,arg3);

  n=write(fd,sendString,strlen(sendString));

  if (n<0){
	fputs("write failed",stderr);
  }

}

void send_command_4(int fd, int command, int arg1, int arg2, int arg3, int arg4){
  char sendString[30];
  int n;


  sprintf(sendString,"!#%d,%d,%d,%d,%d\n", command,arg1,arg2,arg3,arg4);

  n=write(fd,sendString,strlen(sendString));

  if (n<0){
	fputs("write failed",stderr);
  }

}

//public
commandReplyType rcv_1_command_0(int fd, int command, char *arg1){

	commandReplyType rep;
	char rcv_str[255];
	
	char *result;
	char delims[]=",\r\n";


	send_command_0(fd, command);
	rep=getAnswer(fd,rcv_str);
	if (rep==stringType){
	  result=strtok(rcv_str,delims);
	  result=strtok(NULL,delims);
	  strcpy(arg1,result);
	}
	if (rep==NAK){
	  sleep(1);
	  send_enter(fd);
	  tcflush(fd,TCIFLUSH);
	  *arg1 = '\0';
	  return NAK;
        }
	return rep;	
}

commandReplyType rcv_2_command_0(int fd, int command, char *arg1, char *arg2){

	commandReplyType rep;
        char rcv_str[255];

        char *result;
        char delims[]=",\r\n";

        send_command_0(fd, command);
        rep=getAnswer(fd,rcv_str);
	if (rep==stringType){
          result=strtok(rcv_str,delims);
          result=strtok(NULL,delims);
          strcpy(arg1,result);
          result=strtok(NULL,delims);
          strcpy(arg2,result);
	}
	if (rep==NAK){
	  sleep(1);
	  send_enter(fd);
	  tcflush(fd,TCIFLUSH);
	  *arg1 = '\0';
          *arg2 = '\0';
	  return NAK;
        }

	return rep;
}

commandReplyType rcv_1_command_2(int fd ,int command, int arg1, int arg2, char *reply){

	commandReplyType rep;
	char rcv_str[255];
	
	char *result;
	char delims[]=",\r\n";

	send_command_2(fd, command, arg1, arg2);
	rep=getAnswer(fd,rcv_str);
	if (rep==stringType){
  	  result=strtok(rcv_str,delims);
	  result=strtok(NULL,delims);
	  strcpy(reply,result);
	}
	if (rep==NAK){
	  sleep(1);
	  send_enter(fd);
	  tcflush(fd,TCIFLUSH);
	  *reply = '\0';
	  return NAK;
        }

	return rep;
}

commandReplyType rcv_0_command_0(int fd ,int command){

	commandReplyType rep;
	char rcv_str[255];
	
	send_command_0(fd, command);
	rep=getAnswer(fd,rcv_str);

	if (rep==NAK){
	  sleep(1);
	  send_enter(fd);
	  tcflush(fd,TCIFLUSH);
	  return NAK;
        }
	return rep;
}

commandReplyType rcv_0_command_1(int fd ,int command, int arg1) {

	commandReplyType rep;
	char rcv_str[255];
	
	send_command_1(fd, command, arg1);
	rep=getAnswer(fd,rcv_str);

	if (rep==NAK){
	  sleep(1);
	  send_enter(fd);
	  tcflush(fd,TCIFLUSH);
	  return NAK;
        }
	return rep;
}

commandReplyType rcv_0_command_2(int fd ,int command, int arg1, int arg2){

	commandReplyType rep;
	char rcv_str[255];
	
	send_command_2(fd, command, arg1, arg2);
	rep=getAnswer(fd,rcv_str);

	if (rep==NAK){
	  sleep(1);
	  send_enter(fd);
	  tcflush(fd,TCIFLUSH);
	  return NAK;
        }
	return rep;
}

commandReplyType rcv_0_command_3(int fd ,int command, int arg1, int arg2, int arg3){

	commandReplyType rep;
	char rcv_str[255];
	
	send_command_3(fd, command, arg1, arg2, arg3);
	rep=getAnswer(fd,rcv_str);

	if (rep==NAK){
	  sleep(1);
	  send_enter(fd);
	  tcflush(fd,TCIFLUSH);
	  return NAK;
        }
	return rep;
}

commandReplyType rcv_0_command_4(int fd ,int command, int arg1, int arg2, int arg3, int arg4) {

	commandReplyType rep;
	char rcv_str[255];
	
	send_command_4(fd, command, arg1, arg2, arg3, arg4);
	rep=getAnswer(fd,rcv_str);

	if (rep==NAK){
	  sleep(1);
	  send_enter(fd);
	  tcflush(fd,TCIFLUSH);
	  return NAK;
        }
	return rep;
}

commandReplyType rcv_5_command_0(int fd, int command,char *arg1, char *arg2, char *arg3, char *arg4, char *arg5){
	commandReplyType rep;
        char rcv_str[255];

        char *result;
        char delims[]=",\r\n";

        send_command_0(fd, command);
        rep=getAnswer(fd,rcv_str);
	if (rep==stringType){
          result=strtok(rcv_str,delims);
          result=strtok(NULL,delims);
          strcpy(arg1,result);
          result=strtok(NULL,delims);
          strcpy(arg2,result);
          result=strtok(NULL,delims);
          strcpy(arg3,result);
          result=strtok(NULL,delims);
          strcpy(arg4,result);
          result=strtok(NULL,delims);
          strcpy(arg5,result);
	}
	if (rep==NAK){
	  sleep(1);
	  send_enter(fd);
	  tcflush(fd,TCIFLUSH);
	  *arg1 = '\0';
	  *arg2 = '\0';
	  *arg3 = '\0';
	  *arg4 = '\0';
	  *arg5 = '\0';
	  return NAK;
        }
	return rep;
}

void printHexString(char *str){
  int i;
  char errorChar;

  i=0;
  errorChar=1;
  while (errorChar != 0){
    errorChar=str[i];
    printf(" 0x%x",errorChar);	
    i++;
  }
  printf("\n");
}

void printHexStringBytes(char *str, int nbytes){
  int i;
  char errorChar;

  i=0;
  errorChar=1;
  while (i<nbytes){
    errorChar=str[i];
    printf(" 0x%x",errorChar);	
    i++;
  }
  printf("\n");
}
