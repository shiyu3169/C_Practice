
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAXLINE 200 
#define MAXARGS 20
#define STDOUT 1
#define STDIN 0

static char * getword(char * begin, char **end_ptr) {
    char * end = begin;

    while ( *begin == ' ' )
        begin++; 
    end = begin;
    // After # are not commands, just comments
    while ( *end != '\0' && *end != '\n' && *end != ' ' && *end != '#')
        end++;  
    if ( end == begin )
        return NULL;  
    *end = '\0'; 
    *end_ptr = end;
    if (begin[0] == '$') {
        begin = getenv(begin+1);
	if (begin == NULL) {
	    perror("getenv");
	    begin = "UNDEFINED";
        }
    }
    return begin;
}


static void getargs(char cmd[], int *argcp, char *argv[])
{
    char *cmdp = cmd;
    char *end;
    int i = 0;

    if (fgets(cmd, MAXLINE, stdin) == NULL && feof(stdin)) {
        printf("Couldn't read from standard input. End of file? Exiting ...\n");
        exit(1); 
    }
    while ( (cmdp = getword(cmdp, &end)) != NULL ) { 
               argv[i++] = cmdp;
	cmdp = end + 1;
    }
    argv[i] = NULL;
    *argcp = i;
}

void interrupt_handler(int signum) {
    printf("");
}



static void executePIPE(int argc, char *argv[]) {
    int pipe_fd[2];      
    int fd;               
    pid_t child1, child2; 
    char * argvChild[2];

    printf("Executing \"ls | wc\";\n");
    printf("Number of files in curr dir is (first # is answer): ");
    fflush(stdout); 

    if ( -1 == pipe(pipe_fd) ) perror("pipe");
    child1 = fork();
    if (child1 > 0) child2 = fork();
    if (child1 == 0) { 
        if ( -1 == close(STDOUT) ) perror("close");  
        fd = dup(pipe_fd[1]); 
        if ( -1 == fd ) perror("dup");
        if ( fd != STDOUT) fprintf(stderr, "Pipe output not at STDOUT.\n");
        close(pipe_fd[0]); 
        close(pipe_fd[1]); 
        argvChild[0] = "ls"; argvChild[1] = NULL;
        if ( -1 == execvp(argvChild[0], argvChild) ) perror("execvp");
    } else if (child2 == 0) { 
        if ( -1 == close(STDIN) ) perror("close");
        fd = dup(pipe_fd[0]); 
        if ( -1 == fd ) perror("dup");
        if ( fd != STDIN) fprintf(stderr, "Pipe input not at STDIN.\n");
        close(pipe_fd[0]); 
        close(pipe_fd[1]); 
        argvChild[0] = "wc"; argvChild[1] = NULL;
        if ( -1 == execvp(argvChild[0], argvChild) ) perror("execvp");
    } else {
        int status;
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        if ( -1 == waitpid(child1, &status, 0) ) perror("waitpid");
        if (WIFEXITED(status) == 0)
            printf("child1 returned w/ error code %d\n", WEXITSTATUS(status));
        if ( -1 == waitpid(child2, &status, 0) ) perror("waitpid");
        if (WIFEXITED(status) == 0)
            printf("child2 returned w/ error code %d\n", WEXITSTATUS(status));
    }
    return;

}



static void executeIN(int argc, char *argv[]) {
    int background = 0;
    int fd;               
    pid_t childpid; 

    childpid = fork();
    if (childpid == -1) { 
        perror("fork"); 
        printf("  (failed to execute command)\n");
    }


    if (childpid == 0) { 
      int i;
      for (i = 0; i < argc; i++) {
         if (strcmp(argv[i], "<") == 0 ) {
             close(STDIN);
             if ((fd = open(argv[i+1], O_RDONLY)) == -1) {
                  perror("open<"); 
             }
             argc -= 2;
             argv[i] = argv[i+2];
             argv[i+1] = NULL;
             
      if (-1 == execvp(argv[0], argv)) {
           perror("execvp");
           printf("  (couldn't find command)\n");
      }
           close(fd);
         }

         if (strcmp(argv[i], ">") == 0 ) {
             close(STDOUT);
             if ((fd = open(argv[i+1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) == -1) {
                perror("open>");
             }
             argc -= 2;
             argv[i] = NULL;
             argv[i+1] = NULL;

      if (-1 == execvp(argv[0], argv)) {
           perror("execvp");
           printf("  (couldn't find command)\n");
      }
         close(fd);
         }

         if (strcmp(argv[i], "&") == 0) {
	     background = 1;
             argv[i] = NULL;
         }
      }

   if (!(strcmp(argv[0], "&") == 0)) {
	
      if (-1 == execvp(argv[0], argv)) {
           perror("execvp");
           printf("  (couldn't find command)\n");
      }
	}

      exit(1);
        
    } //Closes the child

    else {
        
        int q;
        for (q = 0; q < argc; q++) {
          
         if (strcmp(argv[q], "&") == 0) {
             background = 1;
		break;
         }
        }

	if (!background) {
            waitpid(childpid, NULL, 0);  /* wait until child process finishes */
        } 
	}  
    return;
}



int main(int argc, char *argv[])
{
    char cmd[MAXLINE];
    char *childargv[MAXARGS];
    int childargc;
    signal(SIGINT, interrupt_handler);

    // check if argc > 1, then execute script.myshell if argv[1]
    // is that file
    if ((argc > 1) && strcmp(argv[1], "script.myshell") == 0)
	freopen(argv[1], "r", stdin);

    while (1) {
        printf("%% "); /* printf uses %d, %s, %x, etc.  See 'man 3 printf' */
        fflush(stdout); /* flush from output buffer to terminal itself */
	getargs(cmd, &childargc, childargv); 

        char *cargv[childargc - 1];
        int j;
        for (j = 0; j < childargc - 1; j++)
            cargv[j] = childargv[j];

	if ( childargc > 0 && strcmp(childargv[0], "exit") == 0 )
            exit(0);
	else if ( childargc > 0 && strcmp(childargv[0], "logout") == 0 )
            exit(0);
	else if ( childargc > 1 && strcmp(childargv[1], "|") == 0 )
	    executePIPE(childargc, childargv);
        else
            executeIN(childargc, childargv);
    }
    /* NOT REACHED */
}
