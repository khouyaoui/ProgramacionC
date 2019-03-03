//libs
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

//Macros
#define FILENAME "data/config.txt"
#define dirName "data"
#define MAXC 	 50

typedef struct {	// aun sin usar
	char 	filesystem_name_format[MAXC];
	int 	num_filesystems;
	char	first_filesystem;
} dataConfig;

//Funciones
int listDir(){	//funcion para listarle los files a u
    struct dirent *de;
    DIR *dr = opendir(dirName); 
    if (dr == NULL) { 
        printf("No hemos podido abrir la carpeta indicada" ); 
        return 0; 
    }
    printf("------------------------------------------------\n");
    printf("Que filesystem desea seleccionar: \n");   
    while ((de = readdir(dr)) != NULL){ 
            if (!strcmp(de->d_name,"config.txt") == 0)
				printf("%s\n", de->d_name);
		}
	printf("------------------------------------------------\n"); 
    closedir(dr);     
    return 0; 
} 
/*
void show_filesystems(dataConfig d) {

	printf("FileSytems %c\n", d.filesystem_name_format);

	for (int i = 0; i < d.length; i++) {

	}
}*/
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
	return 0;
}

//Funcion main
int main(void){
	listDir();
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
