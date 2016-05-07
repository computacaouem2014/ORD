#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRSIZE 64 

//definicao do header
struct header {
	short reg_num;
};

//nome bonito para o header
typedef struct header Header;

void set_seek(FILE *f, int position) {
	//coloca o ponteiro do arquivo na posicao passada
	fseek(f, position, SEEK_SET);
}

void inc_seek(FILE *f, int number) {
	//ALPHA
	fseek(f, number, SEEK_CUR);
}

void get_string(char *str) {
	//alternativa para o scanf
	fgets(str, STRSIZE, stdin);
	strtok(str, "\n");
}

void clean_buffer(char *buf) {
	//prenche o buffer com '\0'
	for(int i = 0; i < STRSIZE; i++)
		buf[i] = '\0';
}

void get_data(char *buf) {
	//pede e armazena os dados usando uma string auxiliar
	char temp[STRSIZE];
	printf("First name: ");
	get_string(buf);
	strcat(buf, "|");
	printf("Last name: ");
	get_string(temp);
	strcat(buf, temp);
	strcat(buf, "|");
	printf("Address: ");
	get_string(temp);
	strcat(buf, temp);
	strcat(buf, "|");
	printf("Country: ");
	get_string(temp);
	strcat(buf, temp);
	strcat(buf, "|");
}

void menu(int *num) {
	//printa o menu
	printf("Digite o que deseja fazer\n\t1. Inserir dados\n\t2. Buscar/Atualizar\n\t3. Sair\n>>");
	scanf("%d", num);
	getchar();
}

void insert(FILE *f, Header *h) {
	//cria o buffer e preenche com '\0'
	char buf[STRSIZE + 1];
	clean_buffer(buf);
	
	//scanea os dados e concatena no buffer
	get_data(buf);
	
	//avanca para posicao correta de escrita
	set_seek(f, h -> reg_num * STRSIZE);
	
	//escreve os dados no arquivo
	fwrite(buf, sizeof(buf), 1, f);

	//incrementa o numero de registros do header
	h -> reg_num += 1;

	//retorna para o inicio do arquivo e atualiza o numero de registros
	set_seek(f, 0);
	fwrite(&h -> reg_num, sizeof(Header), 1, f);
}

int main() {
	//cria um header novo
	Header *h = malloc(sizeof(Header));
	int opt = 0;

	//leitura do arquivo
	FILE *f = NULL;
	char file[STRSIZE];
	printf("Digite o nome do arquivo para abrir, caso o arquivo nao exista um novo arquivo sera criado: ");
	get_string(file);
	f = fopen(file, "r+");

	//se nao existir cria um arquivo com header = 0 (0 registros)
	if(f == NULL) {
		f = fopen(file, "w+");
		h -> reg_num = 0;
		fwrite(&h -> reg_num, sizeof(Header), 1, f);
	} else { 
		//se o arquivo ja existe pega o valor do header e armazena
		fread(h, sizeof(short), 1, f);
	}
	menu(&opt);
	switch(opt) {
		case 1: {
			//pede novos dados enquanto nao digitar 0 para sair
			int flag = 1;
			do {
				insert(f, h);
				printf("Digite 0 (ZERO) para sair ou 1 para continuar\n>>");
				scanf("%d", &flag);
				getchar();
			} while(flag);
		} break;
		
		case 2: {
		
		} break;

		case 3: {	
		} break;

		default: break;
	}	
	return 0;
}
