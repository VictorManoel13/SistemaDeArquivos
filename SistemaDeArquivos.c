#include<stdio.h>
#include<string.h>
#include<stdlib.h>


struct Dados_arquivo{

   char Nome[30];
   float Bytes;
   float Blocos;
   int Bloco_inicio;

};

// sao 2048 Bytes divididos em blocos de 8
struct Dados_arquivo Disco[256];
struct Dados_arquivo Arquivo;

void criar_arquivo(){
   int gravar_disco(struct Dados_arquivo Arquivo);
   int x;
   printf("Como deseja nomear o arquivo?");
   scanf("%[^\n]", &Arquivo.Nome);
   printf("Quantos Bytes o arquivo possui?\n");
   scanf("%f", &Arquivo.Bytes);

   Arquivo.Blocos = ceil(Arquivo.Bytes/8);

   x = gravar_disco(Arquivo);
   if( x == 0){
      printf("Arquivo gravado com sucesso\n");
   } else {
      printf("Erro\n");
   }
   
}

// verifica se ja existe um arquivo com o nome escolhido
void verificar_existencia(){
   char op;
   for(int i = 0; i < 256; i++){
   {}
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
// grava os dados coletados em criar_arquivo no Disco
int gravar_disco(struct Dados_arquivo Arquivo){
   int auxiliar_bloco_final = 0;
   int Bloco_final;
   printf("%f   %f\n", Disco[0].Bytes, Arquivo.Blocos);

   for(int i = 0; i < 256; i++){
      if(Disco[i].Bytes == 0){
         
         if(auxiliar_bloco_final == 0){
            Bloco_final = i + Arquivo.Blocos;
            auxiliar_bloco_final = 1; 
         }
         if(i == Bloco_final){
            return 0;
         } else {
            strcpy(Disco[i].Nome, Arquivo.Nome);
            Disco[i].Bytes = Arquivo.Bytes;
            Disco[i].Blocos = Arquivo.Blocos;
            Disco[i].Bloco_inicio = Arquivo.Bloco_inicio;
         }
      }
   }
   return 1;
}
void remover_arquivo(struct Dados_arquivo Arquivo)
{
   int i;
   for(i = 0; i < 256; i++){
      if(Disco[i].Nome == Arquivo.Nome){
         Disco[i].Bytes = 0;
         strcpy(Disco[i].Nome, "");
      }
   }
}

void desfragmentar(){
   
}

void exibir_info(){
}



int main(){

   for(int i = 0; i < 256; i++){
      Disco[i].Bytes = 0;
   }

   criar_arquivo();

}
