#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
	pid_t pid;
	int rv;
	switch( pid = fork() ){
		case -1:
			perror("fork");
			exit(1);
		case 0:
			printf("CHILD: pid=%d\n", pid);
			printf(" CHILD: Мой PID -- %d\n", getpid());
			printf(" CHILD: PID моего родителя -- %d\n",
			getppid());
			printf(" CHILD: Введите мой код возврата(как можно меньше):");
			scanf("%d", &rv);
			printf(" CHILD: Выход!\n");
			exit(rv);
		default:
			printf("PARENT: pid=%d\n", pid);
			printf("PARENT: Это процесс-родитель!\n");
			printf("PARENT: Мой PID -- %d\n", getpid());
			printf("PARENT: PID моего потомка %d\n",pid);
			printf("PARENT: Я жду, пока потомок не вызовет exit()...\n");
			printf("PARENT: Код возврата потомка:%d\n",
			WEXITSTATUS(rv));
			printf("PARENT: Выход!\n");
	}
	exit(0);
}
