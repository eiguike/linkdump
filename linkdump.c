// Link Dump 1.0v - eiguike 15/02/2014
//
// This program dump every hyperlink from a HTML file to a TXT file.
//
// Usage:
// linkdump <.html file> <.txt file>
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This weirdo function search the links and write to TXT file.
// First of all, this function try to search the href=", if find one,
// it will iterate to store the hyperlink in a variable until find another ".
int writeLink(char * whtml, FILE * ftxt, int size){
	int i, i2 = 0;
	int numLinks = 0;
	int flag = 0;
	char * link;
	for(i=0;i<size;i++){

		if(flag == 1){
			if(whtml[i] == '\"'){
				link = realloc(link, (i2+1) * sizeof(int));
				link[i2] = '\0';

				flag = 0;

				fprintf(ftxt,"%s\n",link);
				free(link);
				numLinks++;
			}else{
				link = realloc(link, (i2+2) * sizeof(int));
				link[i2] = whtml[i];
				i2++;
			}
		}else{
			if(whtml[i] == 'h'){
				if(whtml[i+1] == 'r'){
					if(whtml[i+2] == 'e'){
						if(whtml[i+3]== 'f'){
							if(whtml[i+4]== '='){
								if(whtml[i+5]=='\"'){
									flag = 1;
									i+=5;
									link = malloc(sizeof(char)*1);
									i2 = 0;
								}							
							}						
						}
					}
				}
			}
		}
	}
	printf("%d links has found!\n",numLinks);
	return 1;
}

// This function only show a message to how to use this program.
void printUsage(){
	printf("Usage:\n");
	printf("linkdump <.html file> <.txt file>\n");
	printf("Make sure these files really exists\n");	
}

// This function read the HTML file and pass all the source HTML to 
// a variable, after that, it is possible to find any links fastier
// than accessing the harddisk every time.
void printLink(char * html, char * txt){
	FILE * fhtml = fopen(html,"r");
	FILE * ftxt = fopen(txt,"w");

	if((fhtml == NULL) || (ftxt == NULL)){
		printUsage();
	}else{
		fseek(fhtml,1,SEEK_END);
		int size = ftell(fhtml);
		char * whtml = malloc(sizeof(char)*(size + 1));
		rewind(fhtml);
		if(whtml == NULL){
			return;
		}else{
			fread(whtml,1,size,fhtml);
			writeLink(whtml, ftxt, size);
			free(whtml);
		}		
	}
	fclose(fhtml);
	fclose(ftxt);
}

// Main function, nothing special.
int main(int argc, char * argv[]){
	if(argc != 3){
		printUsage();
		return -1;
	}else{
		printLink(argv[1], argv[2]);		
	}
		
}
