#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

struct Dados_arquivo{

   char Nome[30];
   float Bits;
   float Blocos;
   int Bloco_inicio;

};

// sao 2048 bits divididos em blocos de 8
struct Dados_arquivo Disco[256];
struct Dados_arquivo Arquivo;

// grava os dados coletados em criar_arquivo no Disco
int gravar_disco(struct Dados_arquivo Arquivo){
   int Auxiliar_bloco_final = 0;
   int Bloco_final;
   for(int i = 0; i < 256; i++){
      if(Auxiliar_bloco_final == 0){
            Bloco_final = i + Arquivo.Blocos;
            Auxiliar_bloco_final = 1;
         }
      if(Disco[i].Bits == 0){
         if(i == Bloco_final){
            return 0;
         } else {
            strcpy(Disco[i].Nome, Arquivo.Nome);
            Disco[i].Bits = Arquivo.Bits;
            Disco[i].Blocos = Arquivo.Blocos;
            Disco[i].Bloco_inicio = Arquivo.Bloco_inicio;
         }
      }
   }
   return 1;
}

void criar_arquivo(){
   int i;
   printf("Como deseja nomear o arquivo? ");
   fgets(Arquivo.Nome, sizeof(Arquivo.Nome), stdin);
   printf("Quantos bits o arquivo possui? ");
   scanf("%f", &Arquivo.Bits);

   Arquivo.Blocos = ceil(Arquivo.Bits/8);

   i = gravar_disco(Arquivo);
   if(i == 0){
      printf("Arquivo salvo com sucesso!\n");
      printf("Seu arquivo ocupara %.f blocos do disco.\n", Arquivo.Blocos);
   } else{
      printf("ERRO!\n");
      printf("NAO HA MEMORIA SUFICIENTE DISPONIVEL\n");
   }

}

// verifica se ja existe um arquivo com o nome escolhido
void verificar_existencia(){
   char op;
   for(int i = 0; i < 256; i++){
      if(strcmp(Arquivo.Nome, Disco[i].Nome) == 0){
         printf("Um arquivo com esse nome ja existe!\n");
         printf("Gostaria de tentar outro nome? s/n");
         scanf("%c", &op);
         if(op == 's' || op == 'S'){
            criar_arquivo();
         } else{
            printf("Obrigado por usar nosso programa!");
            exit(1);
         }
      }
   }
}

void remover_arquivo(struct Dados_arquivo Arquivo)
{
   int i;
   for(i = 0; i < 256; i++){
      if(Disco[i].Nome == Arquivo.Nome){
         Disco[i].Bits = 0;
         strcpy(Disco[i].Nome, "");
      }
   }
}

void desfragmentar(){
}

void exibir_info(){

   for(int i = 0; i < 256; i++){
      printf("%s\t", Disco[i].Nome);
      printf("%.f\t", Disco[i].Bits);
      printf("%.f\t", Disco[i].Blocos);
      printf("%d\t", Disco[i].Bloco_inicio);
      printf("%.f\n", (Disco[i].Bloco_inicio + Disco[i].Blocos));
   }

}

void menu(){

   int op;
   printf("Bem vindo ao Emulador de disco 3000 :)\n");
   do{
      printf("\nPor favor selecione uma opção\n");
      printf("\t1 para criar um arquivo\n");
      printf("\t2 para excluir um arquivo\n");
      printf("\t3 para exibir uma lista do estado do disco\n");
      printf("\t4 para desfragmentar o disco\n");
      printf("\tAperte 5 para sair\n");
      scanf("%d", &op);

      switch(op){
         case 1:
            getchar();
            criar_arquivo();
            break;
         case 2:
            remover_arquivo(Arquivo);
            break;
         case 3:
            exibir_info();
            break;
         case 4:
            desfragmentar();
            break;
      }
   }while(op != 5);
   printf("Obrigo por usar o 'Emulador de disco 3000 :)', tenha uma boa vida.\n");
}



int main(){

   for(int i = 0; i < 256; i++){
      Disco[i].Bits = 0;
   }

   menu();

}
