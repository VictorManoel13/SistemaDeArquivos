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



int verificar_armazenamento(struct Dados_arquivo Arquivo){
   int i, j = 0;
   for (i = 1; i <= 256; i++)
   {
      if(Disco[i].Blocos == 0){
         j++;
      }
      if(j == Arquivo.Blocos){
         return (i+1) - j;
      } else if(Disco[i].Blocos != 0){
         j = 0;
      }
   }
   return 0;
}

void criar_arquivo(){
   void gravar_disco(struct Dados_arquivo Arquivo, int posicao);
   int verificacao;
   printf("Como deseja nomear o arquivo? ");
   gets(Arquivo.Nome);
   printf("Quantos Bytes o arquivo possui? ");
   scanf("%f", &Arquivo.Bytes);

   Arquivo.Blocos = ceil(Arquivo.Bytes/8);
   verificacao = verificar_armazenamento(Arquivo);
   printf("%d\n", verificacao);
   if( verificacao != 0){
      gravar_disco(Arquivo, verificacao);
      printf("Arquivo gravado com sucesso\n");
   } else {
      printf("Erro\n");
   }
   
}

// verifica se ja existe um arquivo com o nome escolhido
void verificar_existencia(){
   char op;
   for(int i = 1; i <= 256; i++){

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
void gravar_disco(struct Dados_arquivo Arquivo, int posicao){
   int auxiliar_bloco_final = 0;
   int auxiliar_bloco_inicio;
   int Bloco_final;
   
   for(int i = posicao; i <= 256; i++){
      if(Disco[i].Blocos == 0){
         if(auxiliar_bloco_final == 0){
            Bloco_final = i + (Arquivo.Blocos-1);
            auxiliar_bloco_final = 1; 
            auxiliar_bloco_inicio = i;
         }
         if(i != Bloco_final){
            strcpy(Disco[i].Nome, Arquivo.Nome);
            Disco[i].Bytes = Arquivo.Bytes;
            Disco[i].Blocos = Arquivo.Blocos;
            Disco[i].Bloco_inicio = auxiliar_bloco_inicio;
            Disco[i].Bloco_final = Bloco_final;
         } else if(Bloco_final == i){
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
   for(i = 1; i <= 256; i++){
      if(strcmp(Disco[i].Nome, Arquivo.Nome) == 0){
         Disco[i].Blocos = 0;
         Disco[i].Bloco_inicio = 0;
         Disco[i].Bloco_final = 0;
         Disco[i].Bytes = 0;
         strcpy(Disco[i].Nome, "");
      }
   }
}

void desfragmentar(int Bloco_inicio_desfragmentacao){

   int i, j, k, l, posicoes_livres = 0, posicoes_ocupadas = 0;

   for (i = Bloco_inicio_desfragmentacao; i <= 256; i++)
   {
      if(Disco[i].Blocos == 0){
         for (j = i; j <=256; j++)
         {
            if(Disco[j].Blocos == 0){
               posicoes_livres++;
            } else{
               for (k = j; k <=256; k++){
                  if(Disco[k].Blocos != 0){
                     posicoes_ocupadas++;
                  }else{
                     break;
                  }
               }

               break;  
            }
         }
         break;
      }
   }
   // Copia os dados do arquivo (Nome, Bytes, Blocos) da posição ocupada para a posição livre correspondente.
   for(l = 0; l < posicoes_ocupadas; l++){
      strcpy(Disco[i+l].Nome,  Disco[i+posicoes_livres+l].Nome);
      Disco[i+l].Bytes = Disco[i+posicoes_livres+l].Bytes;
      Disco[i+l].Blocos = Disco[i+posicoes_livres+l].Blocos; 
   }

   /*Atualiza os campos Bloco_inicio e Bloco_final do arquivo na posição livre.
   Limpa os campos do arquivo na posição ocupada, atribuindo valores nulos ou zero.*/
   for(l = 0; l < posicoes_ocupadas; l++){
      strcpy(Disco[i+posicoes_livres+l].Nome, "");
      Disco[i+posicoes_livres+l].Bytes = 0;
      Disco[i+posicoes_livres+l].Blocos = 0; 
      Disco[i+posicoes_livres+l].Bloco_inicio = 0;
      Disco[i+posicoes_livres+l].Bloco_final = 0;
   }
   if (posicoes_livres == 0 || posicoes_ocupadas == 0) {
        // Condição de parada: não há mais posições livres e ocupadas consecutivas
        return;
    }
    desfragmentar(i + posicoes_ocupadas);
}

void reorganizar_posicao_blocos() {
    int l = 1;
    char nome_auxiliar[30];
    for (l = 1; l <= 256; l++) {
        if (strcmp(Disco[l].Nome, "") != 0) {
            strcpy(nome_auxiliar, Disco[l].Nome);
            int k = 0;
            for (int i = l; i <= 256; i++) {
                if (strcmp(nome_auxiliar, Disco[i].Nome) == 0 && strcmp(nome_auxiliar, "") != 0) {
                    k++;
                } else {
                    break;
                }
            }
            for (int i = l; i <= l + k - 1; i++) {
                Disco[i].Bloco_inicio = l;
                Disco[i].Bloco_final = l + k - 1;
            }
            l += k - 1;
        }
    }
}

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
   }while(op != 5);
   printf("Obrigo por usar o 'Emulador de disco 3000 :)', tenha uma boa vida.\n");
}
int main(){

   for(int i = 1; i <= 256; i++){
      Disco[i].Bytes = 0;
      strcpy(Disco[i].Nome, "");
      Disco[i].Blocos = 0;
   }

   menu();

}
