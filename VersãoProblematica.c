#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include <locale.h>

//setlocale(LC_ALL, "Portuguese");


struct Dados_arquivo{
	char Nome[30];
	float Bytes;
	float Blocos;
	int Bloco_inicio;
	int Bloco_final;
};

// sao 2048 Bytes divididos em blocos de 8
struct Dados_arquivo Disco[257];
struct Dados_arquivo Arquivo;

// prototipos das funções
void criar_arquivo();
	int verificar_existencia(struct Dados_arquivo Arquivo);
	int verificar_armazenamento(struct Dados_arquivo Arquivo);
	void gravar_disco(struct Dados_arquivo Arquivo, int posicao);
void remover_arquivo();
void exibir_info();
int pesquisar_arquivo();
void desfragmentar();
	void reorganizar_posicao_blocos();

void criar_arquivo(){
	int verificacao;

	printf("Como deseja nomear o arquivo? ");
	fgets(Arquivo.Nome, sizeof(Arquivo.Nome), stdin);
	
   	if(verificar_existencia(Arquivo) == 1){
	printf("Quantos Bytes o arquivo possui? ");
	scanf("%f", &Arquivo.Bytes);
	
		Arquivo.Blocos = ceil(Arquivo.Bytes / 8);
		verificacao = verificar_armazenamento(Arquivo);
		if( verificacao != 0){
			gravar_disco(Arquivo, verificacao);
			printf("Arquivo gravado com sucesso\n");
		}
		else{
			printf("Erro\n");
		}
	}
}
/*	função auxiliar de criar_arquivo()
	verifica se ja existe um arquivo com o nome escolhido	*/
int verificar_existencia(struct Dados_arquivo Arquivo){
	int i;
	for(i = 1; i <= 256; i++){
		if(strcmp(Arquivo.Nome, Disco[i].Nome) == 0){
			printf("Um arquivo com esse nome ja existe!\n");
			return 0;
		}
	}
   return 1;
}
/*	função auxiliar de criar_arquivo()
	verifica se ha espaço suficiente no disco para gravar o arquivo	*/
int verificar_armazenamento(struct Dados_arquivo Arquivo){
	int i, j = 0;
	for (i = 1; i <= 256; i++){
		if(Disco[i].Blocos == 0){
			j++;
		}
		if(j == Arquivo.Blocos){
			return (i + 1) - j;
		}
		else if(Disco[i].Blocos != 0){
			j = 0;
		}
	}
	return 0;
}
/*	função auxiliar de criar_arquivo()
	grava os dados coletados em criar_arquivo no disco	*/
void gravar_disco(struct Dados_arquivo Arquivo, int posicao){
	int auxiliar_bloco_final = 0;
	int auxiliar_bloco_inicio;
	int Bloco_final;
	int i;

	for(i = posicao; i <= 256; i++){
		if(Disco[i].Blocos == 0){
			if(auxiliar_bloco_final == 0){
				Bloco_final = i + (Arquivo.Blocos - 1);
				auxiliar_bloco_final = 1;
				auxiliar_bloco_inicio = i;
			}
			if(i != Bloco_final){
				strcpy(Disco[i].Nome, Arquivo.Nome);
				Disco[i].Bytes = Arquivo.Bytes;
				Disco[i].Blocos = Arquivo.Blocos;
				Disco[i].Bloco_inicio = auxiliar_bloco_inicio;
				Disco[i].Bloco_final = Bloco_final;
			}
			else if(Bloco_final == i){
				strcpy(Disco[i].Nome, Arquivo.Nome);
				Disco[i].Bytes = Arquivo.Bytes;
				Disco[i].Blocos = Arquivo.Blocos;
				Disco[i].Bloco_inicio = auxiliar_bloco_inicio;
				Disco[i].Bloco_final = Bloco_final;
				//printf("%d\n", i);
				break;
			}
		}
	}
}
// remove o arquivo selecionado
void remover_arquivo(){
	printf("Digite o nome do arquivo que voce deseja remover\n");
	fgets(Arquivo.Nome, sizeof(Arquivo.Nome), stdin);
	int i;
	if(verificar_existencia(Arquivo) == 0){
		for(i = 1; i <= 256; i++){
			if(strcmp(Disco[i].Nome, Arquivo.Nome) == 0){
				Disco[i].Blocos = 0;
				Disco[i].Bloco_inicio = 0;
				Disco[i].Bloco_final = 0;
				Disco[i].Bytes = 0;
				strcpy(Disco[i].Nome, "");
			}
		}
		printf("Arquivo excluido com sucesso!");
	} else{
		printf("Arquivo inexistente");
	}
}
// exibe os estado de cada bloco do disco
void exibir_info(){
	int i;
	for(i = 1; i <= 256; i++){
		printf("%s\t", Disco[i].Nome);
		printf("%.f\t", Disco[i].Bytes);
		printf("%.f\t", Disco[i].Blocos);
		printf("%d\t", Disco[i].Bloco_inicio);
		printf("%d\n", Disco[i].Bloco_final);
	}
}
// exibe as informações do arquivo selecionado
int pesquisar_arquivo(){
	int i;
   	printf("Digite o nome do arquivo que voce deseja ver informacoes: ");
	fgets(Arquivo.Nome, sizeof(Arquivo.Nome), stdin);
	for(i = 1; i <= 256; i++){
      if(strcmp(Disco[i].Nome, Arquivo.Nome) == 0){
		   printf("\n\tNome do Arquivo: %s", Disco[i].Nome);
		   printf("\tEspaco em bytes: %.f\n", Disco[i].Bytes);
		   printf("\tEspaco em blocos: %.f\n", Disco[i].Blocos);
		   printf("\tPosicao do bloco inicial: %d\n", Disco[i].Bloco_inicio);
		   printf("\tPosicao do bloco final: %d\n", Disco[i].Bloco_final);
         return 0;
	   }
   }
   return 1;
}
// desfragmenta o disco
void desfragmentar(){
	int posicao_vazia = 1;
	int posicao_ocupada = 1;

	while(posicao_ocupada <= 256){
		// incrementa a variável posicao_vazia até encontrar uma posicao vazia no disco
		while(posicao_vazia <= 256 && Disco[posicao_vazia].Blocos != 0){
			posicao_vazia++;
		}
		if (posicao_vazia > 256){
			// Não há mais blocos vazios consecutivos, interromper a desfragmentação
			break;
		}
		posicao_ocupada = posicao_vazia + 1;

		// incrementa a variável posicao_ocupada até encontrar uma posicao ocupada no disco
		while (posicao_ocupada <= 256 && Disco[posicao_ocupada].Blocos == 0){
			posicao_ocupada++;
		}
		if (posicao_ocupada > 256){
			// Não há mais blocos ocupados consecutivos, interromper a desfragmentação
			break;
		}

		// Copiar o arquivo da posição ocupada para a posição vazia
		Disco[posicao_vazia] = Disco[posicao_ocupada];

		// Limpar a posição ocupada
		Disco[posicao_ocupada].Bytes = 0;
		strcpy(Disco[posicao_ocupada].Nome, "");
		Disco[posicao_ocupada].Blocos = 0;
		Disco[posicao_ocupada].Bloco_inicio = 0;
		Disco[posicao_ocupada].Bloco_final = 0;


		posicao_vazia++;
		posicao_ocupada++;
	}
}
/*	auxiliar da função desfragmenatar 
	corrige os dados dos blocos iniciais e finais de cada arquivo	*/
void reorganizar_posicao_blocos(){
	int l; // variavel responsavel por informar a posicao inicial de cada arquivo
	char nome_auxiliar[30]; // nome auxiliar que ira receber o nome do arquivo que estamos analisando
	int i;
	for (l = 1; l <= 256; l++){
		if (strcmp(Disco[l].Nome, "") != 0){ // verifica se o arquivo possui nome ou se é vazio, caso vazio nao entra
			strcpy(nome_auxiliar, Disco[l].Nome);
			int k = 0;
			// loop que comeca da posicao inicial do arquivo em analise
			for (i = l; i <= 256; i++){ 
				// conta quantos blocos possui o nome daquele arquivo, ao final o k armazena a quantidade de blocos
				if (strcmp(nome_auxiliar, Disco[i].Nome) == 0 && strcmp(nome_auxiliar, "") != 0){
					k++;
				}
				else{
					break;
				}
			}
			/* loop que começa do bloco inicial até o bloco final do arquivo
				e armazena em cada bloco os valores iniciais e finais dos blocos*/
			for (i = l; i <= l + k - 1; i++){
				Disco[i].Bloco_inicio = l;
				Disco[i].Bloco_final = l + k - 1;
			}
			// inicial atualiza para a posicao do proximo arquivo a ser analisado
			l += k - 1;
		}
	}
}

void menu(){

	int op;
	printf("Bem vindo ao Emulador de disco 3000 :)\n");
	do{
		printf("\nPor favor selecione uma opção:\n");
		printf("\t1 para criar um arquivo\n");
		printf("\t2 para excluir um arquivo\n");
		printf("\t3 para exibir uma lista do estado do disco\n");
		printf("\t4 para pesquisar um arquivo\n");
      	printf("\t5 para desfragmentar o disco\n");
		printf("\t6 para sair\n");
		printf("\tOpção:	");
		scanf("%d", &op);

		switch(op){
		case 1:
			getchar();
			criar_arquivo();
			break;
		case 2:
			getchar();
			remover_arquivo();
			break;
		case 3:
			exibir_info();
			break;
      	case 4:
			getchar();
			if(pesquisar_arquivo() == 1){
				printf("Não ha arquivo com esse nome\n");
			}
         	break;
		case 5:
			desfragmentar();
			reorganizar_posicao_blocos();
			break;
		default:
			printf("Opção invalida\n");
			break;
		}
	}
	while(op != 6);
	printf("Obrigado por usar o 'Emulador de disco 3000 :)', tenha uma boa vida.\n");
}
int main(){
	int i;
	for(i = 1; i <= 256; i++){
		Disco[i].Bytes = 0;
		strcpy(Disco[i].Nome, "");
		Disco[i].Blocos = 0;
	}
	menu();
}
