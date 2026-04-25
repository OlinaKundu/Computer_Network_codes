#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	int fd1,fd2[2], pid, n;
	char msg1[512], msg2[512];
	fd1 = open("file.txt", O_RDONLY);
	n=read(fd1,msg1, sizeof(msg1));
	pipe(fd2);
	pid = fork();
	if(pid>0){
		close(fd2[0]);
		write(fd2[1], msg1,n);
		close(fd2[1]);
	}
	else if(pid==0){
		close(fd2[1]);
		n=read(fd2[0], msg2,sizeof(msg2));
		msg2[n]='\0';
		puts(msg2);
		close(fd2[0]);
	}
	else{
		printf("Error in fork");
		exit(0);
	}
	close(fd1);
	return 0;
}
 
