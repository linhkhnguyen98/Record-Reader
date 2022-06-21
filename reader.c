/*
 * CSE30 WI22 HW3
 * Username: cse30wi22jx (Fill in your username)
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
	/* Local Variables */
	int num_cols = 0;
	char **buf = NULL;
	int *obuf = NULL;
	char *readbuffer = NULL;
	int obuf_size = 0;
	size_t len = 0;
	int counter = 0;
	int max = 0;
	int lineCount = 0;



	int compare = strcmp(argv[1], "-c");
	if(compare != 0){
		num_cols = atoi(argv[1]);
		buf = malloc(num_cols * sizeof(char*));
		obuf_size = argc - 2;
		obuf = malloc(obuf_size * sizeof(int));
		for(int i = 0; i < obuf_size; i++){
			obuf[i] = atoi(argv[i+2]);
		}
	}
	else{
		num_cols = atoi(argv[2]);
		buf = malloc(num_cols * sizeof(char*));
		obuf_size = argc - 3;
		obuf = malloc(obuf_size * sizeof(int));
		for(int i = 0; i < obuf_size; i++){
			obuf[i] = atoi(argv[i+3]);
		}
	}

	/* process the input as described in the writeup */
	while(getline(&readbuffer, &len, stdin) > 0){

		//Read an array of char pointer readbuffer into buf
		//Place '\0' in the space or tab
		int buf_count = 0;
		for(size_t i = 0; i < strlen(readbuffer); i++){
			if(i == 0){
				buf[buf_count] = &readbuffer[i];
				buf_count++;
			}
			if(i > 0){
				if(readbuffer[i-1] == ' ' || readbuffer[i-1] == '\t'){
					buf[buf_count] = &readbuffer[i];
					buf_count++;
				}
			}
		}

		int readbufferLen = strlen(readbuffer);
		//printf("%d ", readbufferLen);
		for(int i = 1; i < readbufferLen; i++){
			if(readbuffer[i-1] == ' ' || readbuffer[i-1] == '\t'){
				readbuffer[i-1] = '\0';
			}
			else if(readbuffer[i] == '\n'){
				readbuffer[i] = '\0';
			}
		}
		
		for(int i = 0; i < readbufferLen; i++){
			if(readbuffer[i] != '\0'){
				counter++;
			}
			else{
				if(counter > max){
					max = counter;
					//index = i - max;
				}
				counter = 0;
			}
		}
		
		// if there's no -c
		if(compare != 0){
			//iterating through obuf[] to get the elements inside
			for(int i = 0; i < obuf_size; i++){
				// if the element in obuf[] is negative
				if(obuf[i] < 0){
					int shiftnum = 0;
					shiftnum = obuf[i] + num_cols;
					//if it's not the end of the list
					if(i != obuf_size - 1){
						printf("%s ", buf[shiftnum]);
					}
					else{
						printf("%s\n", buf[shiftnum]);
					}
				}
				// if the element in the obuf[] is pos
				else{
					if(i != obuf_size - 1){
						//printf("%d", obuf[i]);
						printf("%s ", buf[obuf[i]]);
					}
					else{
						//printf("%d", obuf[i]);
						printf("%s\n", buf[obuf[i]]);
					}
				}
				
			}
		}
		//if there's -c
		else{
			for(int i = 0; i < obuf_size; i++){
				// if the element in obuf[] is negative
				if(obuf[i] < 0){
					int shiftnum = 0;
					shiftnum = obuf[i] + num_cols;
					//if it's not the end of the list
					if(i != obuf_size - 1){
						printf("%s ", buf[shiftnum]);

					}
					else{
						printf("%s\n", buf[shiftnum]);
					}
				}
				else{
					if(i != obuf_size - 1){
						printf("%s ", buf[obuf[i]]);
					}
					else{
						printf("%s\n", buf[obuf[i]]);
					}
				}
			
			}

		}
	//free readbuffer
	if(readbuffer != NULL){
		free(readbuffer);
		readbuffer = NULL;
	}
	lineCount++;
	}
	//free buf
	if(buf != NULL){
		free(buf);
		buf = NULL;
	}
	if(obuf != NULL){
		free(obuf);
		obuf = NULL;
	}
	//free readbuffer
	if(readbuffer != NULL){
		free(readbuffer);
		readbuffer = NULL;
	}

	/* Format string for output to be printed when -c option is given

	   printf("Number of lines: %d\n"
	   "Longest field: %d characters\n",
	   insert your variable names here);
	*/
	if(compare == 0){
		printf("Number of lines: %d\n"
							"Longest field: %d characters\n", lineCount, max);
	}
	exit(0);
}
