#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
void prime(int rd){
	int first = 1;
	int base, num;
	int p[2];
	pipe(p);
	while(read(rd, &num, 4)){
		if(first == 1){
			first = 0;
			base = num;
			printf("prime %d\n",num);
			if(fork() == 0) {
				close(p[1]);
				prime(p[0]);
				close(p[0]);
			}
			else{
				close(p[0]);
			}
			
		}		
		else{
			if(num % base != 0)
				write(p[1],&num, 4);
		}
	}
	close(p[1]);
	wait(0);
}
int
main(int argc, char *argv[])
{

  if(argc >= 2){ 
    fprintf(2, "Usage: primes only\n");
    exit(1);
  }
  int p[2];
  pipe(p);
  if(fork() == 0){
	close(p[1]);
	prime(p[0]);
	close(p[0]);
  }
  else{
	close(p[0]);
	for(int i = 2; i <= 35; i ++){
		write(p[1], &i, 4);	
	}
	close(p[1]);
	wait(0);
  }
  exit(0);
}
