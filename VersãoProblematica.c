#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

struct Dados_arquivo
{

	char Nome[30];
	float Bytes;
	float Blocos;
	int Bloco_inicio;
	int Bloco_final;

};

// sao 2048 Bytes divididos em blocos de 8
struct Dados_arquivo Disco[256];
struct Dados_arquivo Arquivo;


int verificar_existencia(struct Dados_arquivo Arquivo);
int verificar_armazenamento(struct Dados_arquivo Arquivo)
{
	int i, j = 0;
	for (i = 1; i <= 256; i++)
	{
		if(Disco[i].Blocos == 0)
		{
			j++;
		}
		if(j == Arquivo.Blocos)
		{
			return (i + 1) - j;
		}
		else if(Disco[i].Blocos != 0)
		{
			j = 0;
		}
	}
	return 0;
}

void criar_arquivo()
{
	void gravar_disco(struct Dados_arquivo Arquivo, int posicao);
	int verificacao;
	printf("Como deseja nomear o arquivo? ");
	gets(Arquivo.Nome);
	printf("Quantos Bytes o arquivo possui? ");
	scanf("%f", &Arquivo.Bytes);
	if(verificar_existencia(Arquivo) == 1)
	{
		Arquivo.Blocos = ceil(Arquivo.Bytes / 8);
		verificacao = verificar_armazenamento(Arquivo);
		printf("%d\n", verificacao);
		if( verificacao != 0)
		{
			gravar_disco(Arquivo, verificacao);
			printf("Arquivo gravado com sucesso\n");
		}
		else
		{
			printf("Erro\n");
		}
	}

}

// verifica se ja existe um arquivo com o nome escolhido
int verificar_existencia(struct Dados_arquivo Arquivo)
{
	char op;
	int i;
	for(i = 1; i <= 256; i++)
	{

		if(strcmp(Arquivo.Nome, Disco[i].Nome) == 0)
		{
			printf("Um arquivo com esse nome ja existe!\n");
			return 0;
		}
		else
		{
			return 1;
		}
	}
}
// grava os dados coletados em criar_arquivo no Disco
void gravar_disco(struct Dados_arquivo Arquivo, int posicao)
{
	int auxiliar_bloco_final = 0;
	int auxiliar_bloco_inicio;
	int Bloco_final;
	int i;

	for(i = posicao; i <= 256; i++)
	{
		if(Disco[i].Blocos == 0)
		{
			if(auxiliar_bloco_final == 0)
			{
				Bloco_final = i + (Arquivo.Blocos - 1);
				auxiliar_bloco_final = 1;
				auxiliar_bloco_inicio = i;
			}
			if(i != Bloco_final)
			{
				strcpy(Disco[i].Nome, Arquivo.Nome);
				Disco[i].Bytes = Arquivo.Bytes;
				Disco[i].Blocos = Arquivo.Blocos;
				Disco[i].Bloco_inicio = auxiliar_bloco_inicio;
				Disco[i].Bloco_final = Bloco_final;
			}
			else if(Bloco_final == i)
			{
				strcpy(Disco[i].Nome, Arquivo.Nome);
				Disco[i].Bytes = Arquivo.Bytes;
				Disco[i].Blocos = Arquivo.Blocos;
				Disco[i].Bloco_inicio = auxiliar_bloco_inicio;
				Disco[i].Bloco_final = Bloco_final;
				printf("%d\n", i);
				break;
			}
		}
	}

}

void remover_arquivo()
{
	printf("Digite o nome do arquivo que voce deseja remover\n");
	gets(Arquivo.Nome);
	int i;
	for(i = 1; i <= 256; i++)
	{
		if(strcmp(Disco[i].Nome, Arquivo.Nome) == 0)
		{
			Disco[i].Blocos = 0;
			Disco[i].Bloco_inicio = 0;
			Disco[i].Bloco_final = 0;
			Disco[i].Bytes = 0;
			strcpy(Disco[i].Nome, "");
		}
	}
}

void desfragmentar()
{
	int posicao_vazia = 1;
	int posicao_ocupada = 1;

	while (posicao_ocupada <= 256)
	{
		while (posicao_vazia <= 256 && Disco[posicao_vazia].Blocos != 0)
		{
			posicao_vazia++;
		}

		if (posicao_vazia > 256)
		{
			// Não há mais blocos vazios consecutivos, interromper a desfragmentação
			break;
		}

		posicao_ocupada = posicao_vazia + 1;

		while (posicao_ocupada <= 256 && Disco[posicao_ocupada].Blocos == 0)
		{
			posicao_ocupada++;
		}

		if (posicao_ocupada > 256)
		{
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

void reorganizar_posicao_blocos()
{
	int l = 1;
	char nome_auxiliar[30];
	int i;
	for (l = 1; l <= 256; l++)
	{
		if (strcmp(Disco[l].Nome, "") != 0)
		{
			strcpy(nome_auxiliar, Disco[l].Nome);
			int k = 0;
			for (i = l; i <= 256; i++)
			{
				if (strcmp(nome_auxiliar, Disco[i].Nome) == 0 && strcmp(nome_auxiliar, "") != 0)
				{
					k++;
				}
				else
				{
					break;
				}
			}
			for (i = l; i <= l + k - 1; i++)
			{
				Disco[i].Bloco_inicio = l;
				Disco[i].Bloco_final = l + k - 1;
			}
			l += k - 1;
		}
	}
}


void exibir_info()
{
	int i;
	for(i = 1; i <= 256; i++)
	{
		printf("%s\t", Disco[i].Nome);
		printf("%.f\t", Disco[i].Bytes);
		printf("%.f\t", Disco[i].Blocos);
		printf("%d\t", Disco[i].Bloco_inicio);
		printf("%d\n", Disco[i].Bloco_final);
	}
}

void menu()
{

	int op;
	printf("Bem vindo ao Emulador de disco 3000 :)\n");
	do
	{
		printf("\nPor favor selecione uma opção\n");
		printf("\t1 para criar um arquivo\n");
		printf("\t2 para excluir um arquivo\n");
		printf("\t3 para exibir uma lista do estado do disco\n");
		printf("\t4 para desfragmentar o disco\n");
		printf("\tAperte 5 para sair\n");
		scanf("%d", &op);

		switch(op)
		{
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
			desfragmentar(1);
			reorganizar_posicao_blocos();
			break;
		}
	}
	while(op != 5);
	printf("Obrigo por usar o 'Emulador de disco 3000 :)', tenha uma boa vida.\n");
}
int main()
{
	int i;
	for(i = 1; i <= 256; i++)
	{
		Disco[i].Bytes = 0;
		strcpy(Disco[i].Nome, "");
		Disco[i].Blocos = 0;
	}

	menu();

}
