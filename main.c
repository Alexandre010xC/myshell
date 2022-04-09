#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

void cmd_input(char cmd[], char *params[]){
  char line[1024], *array[100], *pch;
  int count = 0, i = 0;

  int c;
  while((c = fgetc(stdin) != '\n')){
    line[count++] = (char) c;
  }

  if(count==1)
    return;
  
  pch = strtok(line, " \n");

  while(pch != NULL){
    array[i++] = strdup(pch);
    pch=strtok(NULL," \n");
  }

  strcpy(cmd, array[0]);

  for(int j=0;j<i;j++)
    params[j] = array[j];
  params[i] = NULL;
}

int main(void){

  char cmd[100], command[100], *parameters[20], *env[]={(char*) "PATH=/bin",0};
  int ch;
  
  system("clear");
  while(1){
    printf("myshell> ");

    cmd_input(command,parameters);

    while ((ch = getchar()) != '\n');

    if(strcmp(command,"exit")==0)
      break;

    if(fork()!=0){
      wait(NULL);
    }else{
      strcpy(cmd,"/bin/");
      strcat(cmd,command);
      execve(cmd,parameters,env);
    }
  }

  return 0;
}
