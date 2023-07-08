#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

struct Dados_arquivo{

   char Nome[30];
   float Bytes;
   float Blocos;
   int Bloco_inicio;
   int Bloco_final;

};

// sao 2048 Bytes divididos em blocos de 8
struct Dados_arquivo Disco[256];
struct Dados_arquivo Arquivo;

void criar_arquivo();
int verificar_existencia(struct Dados_arquivo Arquivo);
int gravar_disco(struct Dados_arquivo Arquivo);
void menu();

void criar_arquivo(){
   
   int Retorno_gravar_disco;
   printf("Como deseja nomear o arquivo? ");
   fgets(Arquivo.Nome, sizeof(Arquivo.Nome), stdin);
   if(verificar_existencia(Arquivo) == 1){
      criar_arquivo(Arquivo);
   }
   else{
      printf("Quantos Bytes o arquivo possui? ");
      scanf("%f", &Arquivo.Bytes);

      Arquivo.Blocos = ceil(Arquivo.Bytes/8);

      Retorno_gravar_disco = gravar_disco(Arquivo);
      if( Retorno_gravar_disco == 0){
         printf("Arquivo gravado com sucesso\n");
      } else {
         printf("Erro\n");
      }
   }
}

// verifica se ja existe um arquivo com o nome escolhido
int verificar_existencia(struct Dados_arquivo Arquivo){
   char op;
   for(int i = 0; i < 256; i++){

      if(strcmp(Arquivo.Nome, Disco[i].Nome) == 0){
         printf("Um arquivo com esse nome ja existe!\n");
         printf("Gostaria de tentar outro nome? s/n   ");
         scanf("%c", &op);
         getchar();
         if(op == 's' || op == 'S'){
            return 1;
         } else{
            menu();
         }
      }
   }
   return 0;
}
// grava os dados coletados em criar_arquivo no Disco
int gravar_disco(struct Dados_arquivo Arquivo){
   int auxiliar_bloco_final = 0;
   int auxiliar_bloco_inicio;
   int Bloco_final;
   for(int i = 0; i < 256; i++){
      if(Disco[i].Bytes == 0){
         
         if(auxiliar_bloco_final == 0){
            Bloco_final = i + Arquivo.Blocos;
            auxiliar_bloco_inicio = i + 1;
            auxiliar_bloco_final = 1; 
         }
         if(i == Bloco_final){
            return 0;
         } else {
            strcpy(Disco[i].Nome, Arquivo.Nome);
            Disco[i].Bytes = Arquivo.Bytes;
            Disco[i].Blocos = Arquivo.Blocos;
            Disco[i].Bloco_inicio = auxiliar_bloco_inicio;
            Disco[i].Bloco_final = Bloco_final;
         }
      }
   }
   return 1;
}

void remover_arquivo()
{
   printf("Digite o nome do arquivo que voce deseja remover\n");
   /* o fgets recebe o um ponteiro pro espaço de memoria onde sera armazenado a string, 
      o tamanho desse espaço de memoria e o locoal de onde a string sera coletada, 
      no caso do tecla por isso o stdin   */
   fgets(Arquivo.Nome, sizeof(Arquivo.Nome), stdin);
   int i;
   for(i = 0; i < 256; i++){
      if(strcmp(Disco[i].Nome, Arquivo.Nome) == 0){
         Disco[i].Blocos = 0;
         Disco[i].Bloco_inicio = 0;
         Disco[i].Bytes = 0;
         Disco[i].Bloco_final = 0;
         strcpy(Disco[i].Nome, "");
      }
   }
}

void desfragmentar(){
   
}

void exibir_info(){
   int i;
   for(i = 0; i < 256; i++){
      printf("%s\t", Disco[i].Nome);
      printf("%.f\t", Disco[i].Bytes);
      printf("%.f\t", Disco[i].Blocos);
      printf("%d\t", Disco[i].Bloco_inicio);
      printf("%d\n", Disco[i].Bloco_final);
   }
}

void menu(){

   int op;
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
            getchar();
            remover_arquivo();
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
      Disco[i].Bytes = 0;
   }
   printf("Bem vindo ao Emulador de disco 3000 :)\n");
   menu();

}
