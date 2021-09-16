#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char* readline(){
	char* buf = malloc(100);
	char* p = buf;
	while(read(0, p, 1) != 0){
		if(*p == '\n' || *p == 0){
			*p = 0;
			return buf;
		}
		p++;
	}
	if(p != buf){
		*p = 0; return buf;
	}
	return 0;// pay attention
}
int
main(int argc, char *argv[])
{

  if(argc < 2){ 
    fprintf(2, "Usage: xargs [command]\n");
    exit(1);
  }
  char* line;
  argv ++;
  char* newargv[32];
  char** p1 = argv;
  char** p2 = newargv;
  while(*p1){// copy previous arguments
	*p2 = *p1;
	p1 ++; p2 ++;
  }
  while((line = readline()) != 0){// add new arguments
	//printf("%s\n", line);
	int n = strlen(line);
	int i;
	int cur = argc - 1;
	char *buf = malloc(36);
	int j;
	for( i = 0, j = 0; i < n; i ++){
		if(line[i] == ' '){
			buf[j] = 0;
			newargv[cur++] = buf;
			buf = malloc(36);
			j = 0;
		}
		else{
			buf[j] = line[i];
			j ++;
		}
	}
	buf[j] = 0;
	newargv[cur++] = buf;
	newargv[cur] = 0;
	free(line);
	if(fork() == 0){
		exec(newargv[0], newargv);
	}
	else{
		wait(0);
	}
	//printf("exec ok\n");
  }
  exit(0);
}
