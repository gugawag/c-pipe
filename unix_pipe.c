/**
 * Example program demonstrating UNIX pipes.
 *
 * Figures 3.25 & 3.26
 *
 * @author Silberschatz, Galvin, and Gagne. Pequenas alterações feitas por Gustavo Wagner (gugawag@gmail.com)
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 25
#define READ_END	0
#define WRITE_END	1

int main(void)
{
	char write_msg[BUFFER_SIZE] = "Olá";
	char read_msg[BUFFER_SIZE];
	pid_t pid;
	int fd[2];

	/* cria um pipe */
	if (pipe(fd) == -1) {
		fprintf(stderr,"Pipe falhou");
		return 1;
	}

	/* cria um processo filho */
	pid = fork();

	if (pid < 0) {
		fprintf(stderr, "Fork falhou");
		return 1;
	}

	if (pid > 0) {  /* processo pai */
		printf("=== Pai ===\n");
		/* fecha o read_end do pipe, pois não será utilizado pelo pai */
		close(fd[READ_END]);

		printf("=== Escrevendo para meu filho: %s ===\n",write_msg);
		/* escreve no pipe */
		write(fd[WRITE_END], write_msg, strlen(write_msg)+1); 

		/* fecha o write_end do pipe */
		close(fd[WRITE_END]);
		printf("=== Fim Pai ===\n");
	}
	else { /* processo filho */
		printf("=== Filho ===\n");
		/* fecha o write_end do pipe, pois não será usado pelo filho */
		close(fd[WRITE_END]);

		/* lê do pioe */
		read(fd[READ_END], read_msg, BUFFER_SIZE);
		printf("Eu li: %s\n",read_msg);

		/* fecha o read_end do pipe */
		close(fd[READ_END]);
		printf("=== Fim Filho ===");
	}

	return 0;
}
