#include <stdio.h>
#include <stdlib.h>

#define FILENAME "data/config.txt"
#define MAXC 	 50


int read_config(int *num_filesystems, char filesystem_name[], char first_filesystem[]) {
	
	FILE *f = fopen(FILENAME, "r");
	char skip[MAXC];
	
	
	if (f == NULL) {
		printf("Error, el archivo no se ha podido encontrar o abrir %s\n", FILENAME);
		return 0;
	} else {

		while (!feof(f)) {
			fscanf(f, "%s", skip);	// titulo
			fscanf(f, "%d", num_filesystems);
			fscanf(f, "%s", skip);	// titulo
			fscanf(f, "%s", filesystem_name);
			fscanf(f, "%s", skip);	// titulo
			fscanf(f, "%s", first_filesystem);	
	
		}

	}
		fclose(f);
	

	return 1;
}


int main(void){

	int num_filesystems = 0;
	char filesystem_name[MAXC];
	char tmp_first_filesystem[MAXC];
	char first_filesystem;

	read_config(&num_filesystems, filesystem_name, tmp_first_filesystem);

	first_filesystem = tmp_first_filesystem[0];
	
	printf("%d \n", num_filesystems);
	printf("%s \n", filesystem_name);
	printf("%c \n", first_filesystem);

	return 1;

}
