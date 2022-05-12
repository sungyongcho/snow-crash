#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFF_SIZE 1024

int main(int argc, char **argv){
   char   buf[BUFF_SIZE];
   int    fd;
   int 	len;
   int i;

   if ( 0 < ( fd = open(argv[1], O_RDONLY))){
      len = read( fd, buf, sizeof(buf));
	  buf[len] = '\0';
      close(fd);
   } else {
      printf("file read error\n");
   }

	i = 0;
	while (buf[i] != '\0')
	{
		printf("%c", buf[i] - i);
		i++;
	}
	printf("\n");
	return 0;
}
