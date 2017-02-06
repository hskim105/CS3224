#include "types.h"
#include "user.h"
#include "stat.h"

char buf[512];
int lineCount(int fd){
	int i, n;
	int numLines = 0;
	while((n = read(fd, buf, sizeof(buf))) > 0){
		for(i = 0; i < n; i++){
			if(buf[i] == '\n'){
				numLines++;
			}
		}
	}
	return numLines;
}

void tail(int fd, char* name, int lineLimit, int numLines){
	int i, n;	
	int currentLine = 0;
	int startLine = numLines - lineLimit;

	//Print the last x lines
	while((n = read(fd, buf, sizeof(buf))) > 0){
		for(i = 0; i < n; i++){
			if(buf[i] == '\n'){
				currentLine++;
			}
			if(currentLine >= startLine){
				printf(1, "%c", buf[i]);
			}
			if(currentLine == numLines){
				exit();
			}
		}
	}

	if(n < 0){
		printf(1, "tail: read error\n");
		exit();
	}
}

int main(int argc, char* argv[]){
	int fd, i;
	int lineLimit = 10;
	int numLines;
	if(argc <= 1){
		numLines = lineCount(0);
		tail(0, "", lineLimit, numLines);
		exit();	
	}

	char* argLimit = argv[1];

	for(i = 1; i < argc; i++){
		if(argLimit[0] == '-'){
			lineLimit = atoi(++argLimit);
			i++;
		}
		if( (fd = open(argv[i], 0) ) < 0){
			printf(1, "tail: cannot open %s\n", argv[i]);
			exit();
		}

		numLines = lineCount(fd);
		close(fd);

		if((fd = open(argv[i],0)) < 0){
			printf(1, "tail: cannot open %s\n", argv[i]);
			exit();
		}

		tail(fd, argv[i], lineLimit, numLines);
		close(fd);
	}

	exit();
}
