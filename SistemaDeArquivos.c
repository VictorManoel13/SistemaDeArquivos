#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Dados_arquivo{

   char Nome[30];
   int Bits;
   int Blocos;
   int Bloco_inicio;

};

// sao 2048 bits divididos em blocos de 8
struct Dados_arquivo Disco[256];
struct Dados_arquivo Arquivo;

void criar_arquivo(){
   
   printf("Como deseja nomear o arquivo?");
   scanf("%[^\n]", &Arquivo.Nome);
   printf("Quantos bits o arquivo possui?\n");
   scanf("%d", &Arquivo.bits);

   Arquivo.Blocos = (Arquivo.Bits/8);
   gravar_disco(Arquivo);

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

   for(int i = 0; i < 256; i++){
      if(Disco[i].Bits == 0){
         int Bloco_final = i + Arquivo.Blocos;
         if(i == Bloco_final){
            return 0;
         } else {
            strcpi(Disco[i].Nome, Arquivo.Nome)
            Disco[i].Bits = Arquivo.Bits
            Disco[i].Blocos = Arquivo.Blocos
            Disco[i].Bloco_inicio = Arquivo.Bloco_inicio
         }
      }
   }
   return 1;
}
void remover_arquivo(){
}

void desfragmentar(){
}

void exibir_info(){
}



int main(){

   for(int i = 0; i < 256; i++){
      Disco[i].Bits = 0;
   }

   criar_arquivo();

}
