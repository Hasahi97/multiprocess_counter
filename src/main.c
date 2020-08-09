/* Contador de palavras
 *
 * Este programa recebera uma serie de caracteres representando palavras em sua
 * entrada. Ao receber um caractere fim de linha ('\n'), deve imprimir na tela o
 * numero de palavras separadas que recebeu e, apos, encerrar.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>
#define nArray 250

//Funcao para verificar caso seja primo
int vPrimo(int n)
{
  int i = 2;
  int nMetade;
  //Casos bases
  if(n == 0 ||n == 1)
  {
    return 0;
  }
  else
  {
     nMetade = n / 2;
     //Verifica caso o numero seja divisivel por algum outro alem dele mesmo
     for(i = 2; i <= nMetade; i++)
     {
       if(n % i == 0)
       {
         return 0;
         exit(0);
       }
     }
     return 1;
  }
}

int main()
{
  //Variaveis p/ o mmap
  int protec = PROT_READ | PROT_WRITE;
  int visibi = MAP_SHARED | MAP_ANON;
  //Vetor de ints que armazena a leitura da entrada
  int n[nArray];
  //Variaveis compartilhadas
  int *indice; //Sera responsavel por atribuir um indice a cada processo
  int *contComp; //Contador compartilhado
  int *f; //Flag para que seja exibido uma unica vez a saida
  pid_t pid;
  //mmap
  contComp = (int*)(mmap(NULL, sizeof(int), protec, visibi, 0, 0));
  f = (int*)(mmap(NULL, sizeof(int), protec, visibi, 0, 0));
  indice = (int*)(mmap(NULL, sizeof(int), protec, visibi, 0, 0));
  (*f) = (*contComp) = (*indice) = 0;
  //char que auxiliara a leitura
  char c = 'a';
  //Indice do array
  int i = 0;
  int j;

  //instanciando o vetor
  for(j = 0; j < nArray; j++)
  {
    n[j] = 0;
  }

  //Leitura da entrada
  while(c != '\n')
  {
    scanf("%d%c", &n[i], &c);
    i++;
  }
//Verifica os casos possiveis de acordo com o tamanho do vetor de entrada
  if(i == 1) ;
  else
  {
    if(i <= 2)
    {
      pid = fork();
    }
    else
    {
      if(i <= 4)
      {
        i = 4; //Corrige o valor
        pid = fork();
        pid = fork();
      }
      else
      {
        if(i <= 8)
        {
          i = 8; //Corrige o valor
          pid = fork();
          pid = fork();
          pid = fork();
        }
        else
        {
          if(i <= 16)
          {
            i = 16; //Corrige o valor
            pid = fork();
            pid = fork();
            pid = fork();
            pid = fork();
          }
        }
      }
    }
  }
  //Variaveis auxiliadoras a cada processo
  int ip, totalNProcesso;
  //Cada processo armazera um indice
  ip = (*indice);
  //Quando o indice é gravado o valor e incrementado para que nao haja duplicidade
  (*indice)++;
  //Verifica se o numero e primo
  if(vPrimo(n[ip]) == 1)
  {
    //Caso seja incrementa um contador compartilhado
    (*contComp)++;
  }
  else
  {
    (*f)++;
  }
  if((*f)+(*contComp) == i && (*f) != 0) //Apenas quando o ultimo processo por executado o valor sera exibido
  {
    printf("%d\n", (*contComp));
    (*f) = 17; //Numero fora do intervalo da quantidade de processos
  }
  while(1)
  {
    if(*f == 17)
    {
      return 0;
    }
  }
}