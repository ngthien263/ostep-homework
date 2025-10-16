#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include <fcntl.h>
int main(){
	int fd = open("file.txt", O_CREAT | O_RDWR | O_APPEND, 0666);
	if (fd < 0)	return 0;
	pid_t pid = fork();
	if(pid < 0)	return 0;
	else if(pid == 0) {
		char text[] = "Child\n";
		write(fd, text, sizeof(text));
	} else {
		char text[] = "Parent\n";
                write(fd, text, sizeof(text));
	}
	close(fd);
	return 0;
}


/*
Note:
- After fork(), both parent and child share the same open file description in the kernel.
- Therefore, they both can access and write to the same file.
- When both process can access to the file at the same time, sometime the data can be written in unexpected order.
*/
