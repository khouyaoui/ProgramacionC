#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //sleep
#define FILENAME "data/config.txt"
#define MAXC 	 50

typedef struct{
	char titulo[MAXC];
	long medida;
} Archivos;

typedef struct{
	char titulo[MAXC];
	int num_archivos;
} Carpetas;

int read_filesystem(char nom_filesystem[]) {
	FILE *f = fopen(nom_filesystem, "rb+");
	int num_carpetas, i, j, carpeta_option, archivo_option;
	Carpetas c;
	Archivos a;
	char nuevo_nombre[MAXC];
	
	if (f == NULL) {
		printf("Fichro no encontrado o error al intentar realiar la lectura.\n");
		return 0;
	} else {
		fread(&num_carpetas, sizeof(int), 1, f);
		//printf("Numero de carpetas: %d \n", num_carpetas);
		printf("¿Que número de carpeta? ");
		scanf("%d", &carpeta_option);
		for(i = 0; i < num_carpetas; i++){			
			if(i == (carpeta_option-1)){
				fread(&c, sizeof(Carpetas), 1, f);
				printf("Has entrado en la carpeta '%s'... \n", c.titulo);
				//printf("Numero de archivos: %d \n", c.num_archivos);
				if(c.num_archivos != 0){	
					printf("¿Que número de archivo? ");
					scanf("%d", &archivo_option);
					for(j = 0; j < c.num_archivos; j++){
						if(j == (archivo_option-1)){				
							fread(&a, sizeof(Archivos), 1, f);
							
							printf("Nuevo nombre para el archivo: '%s': ", a.titulo);
							//printf("Tamaño: %ld \n", a.medida);
							fseek(f, -sizeof(Archivos), SEEK_CUR);
							fflush( stdin );
							scanf("%s", nuevo_nombre);
							fwrite(nuevo_nombre, sizeof(char), sizeof(nuevo_nombre), f);
							printf("Guardando el nuevo nombre de archivo... \n");
							//sleep(3);
						}else{
							fread(&a, sizeof(Archivos), 1, f);
						}
					}
				}else{
					printf("Esta carpeta no tiene archivos... \n");
				}
				}else{
					fread(&c, sizeof(Carpetas), 1, f);
					for(j = 0; j < c.num_archivos; j++){
						fread(&a, sizeof(Archivos), 1, f);
					}
				}
			}
			
		fclose(f);
	}
	return 1;
}

int read_config(int *num_filesystems, char filesystem_name[], char first_filesystem[]) {
	
	FILE *f = fopen(FILENAME, "r");
	char skip[MAXC];
	if (f == NULL) {
		printf("Error, el archivo no se ha podido encontrar o abrir.\n");
		return 1;
	} else {
		while (!feof(f)) {
			fscanf(f, "%s", skip);
			fscanf(f, "%d", num_filesystems);
			fscanf(f, "%s", skip);
			fscanf(f, "%s", filesystem_name);
			fscanf(f, "%s", skip);
			fscanf(f, "%s", first_filesystem);	
		}
	}
		fclose(f);	

	return 0;
}

void info_program(){
	printf("##################################################################################\n");
	printf("# Programa para la gestión de ficheros binario,                                 #\n");
	printf("# a continuación le pediremos los datos necesarios para llevar a cabo la tarea  #\n");
	printf("##################################################################################\n");
}

void viewFilesystem (int *num_filesystems,char nom_filesystem [],char filesystem_name[],char first_filesystem[]){
	for(int i = 1; i < *num_filesystems+1; i++){
		sprintf(nom_filesystem, filesystem_name, first_filesystem[0] + i -1);
		printf("%d. %s \n", i, nom_filesystem+5);
	}
}

int main(void){

	int num_filesystems = 0;
	char filesystem_name[MAXC];
	char first_filesystem[MAXC];
	char nom_filesystem[MAXC];
	int filesystem_option;

	read_config(&num_filesystems, filesystem_name, first_filesystem);

	info_program();
	
	viewFilesystem(&num_filesystems,nom_filesystem,filesystem_name,first_filesystem);
		
	printf("Selecciona un filesystem: ");
	
	scanf("%d", &filesystem_option);
	
	sprintf(nom_filesystem, filesystem_name, first_filesystem[0] + (filesystem_option-1));
	
	read_filesystem(nom_filesystem);

	return 0;

}
