#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <mysql.h>
#define TAMANHO_FILA 5
#define TAMANHO_NOME 256
#define NUMERO_PASSAGEIROS 5

/*
=== CONEXÃO MYSQL E QUERIES ===
*/

/*
void conecta(MYSQL *conn){
    if (!mysql_real_connect(conn, "localhost", "root", "", NULL, 3306, NULL, 0))
    {
        printaErro(conn, "Erro na conexão: Erro: %s\n");
              mysql_close(conn);
              exit(1);
    }

    if (mysql_query(conn, "USE aeroporto;")) {
            printaErro(conn, "Erro na busca dos dados");
        }

}

void printaErro(MYSQL *conn, char *mensagemDeErro){
        fprintf(stderr, "%s: %s\n", mensagemDeErro, mysql_error(conn));
        mysql_close(conn);
        exit(1);
}

void listaVoos(MYSQL *conn){
        if (mysql_query(conn, "SELECT * FROM aviao;")) {
            printaErro(conn, "Erro na busca dos dados");
        }

        MYSQL_RES *resultado = mysql_use_result(conn);
        if (resultado == NULL) {
            printf("\n");
        }

        MYSQL_ROW linha;
        unsigned int num_campos;
        unsigned int i;

        num_campos = mysql_num_fields(resultado);
        while ((linha = mysql_fetch_row(resultado)))
         {
           unsigned long *tamanhos;
           tamanhos = mysql_fetch_lengths(resultado);
           for(i = 0; i < num_campos; i++)
           {
               printf("[%.*s] ", (int) tamanhos[i],
                      linha[i] ? linha[i] : "NULL");
           }
           printf("\n");
        }
}

void InsereVoo(MYSQL *conn, char *Destino, int *NumeroPassageiros){
    char textoTemporario[100000000];
    char *query = "INSERT INTO aviao (destino, número de usuários) VALUES ('";
    sprintf(textoTemporario, "%d", NumeroPassageiros);
    //if (mysql_query(conn, strcat("INSERT INTO aviao (destino, número de
usuários) VALUES ('",Destino))) {
     //       printaErro(conn, "Erro na busca dos dados");
     //   }

    printf(query);

}

void deletaVoo(MYSQL *conn, int idVoo){

    if (mysql_query(conn, strcat("DELETE FROM aviao WHERE idTeste = ;", idVoo)))
{ printaErro(conn, "Erro ao deletar voo");
        }

}
*/

/*
===  LISTA LIGADA E OPERAÇÕES ===
*/

struct Passageiro {
  char nome[30];
  char cpf[20];
  struct Passageiro *proximo;
};

struct ListaLigadaPassageiro {
  struct Passageiro *elemento;
  int tamanho;
};

void inicializarPassageiro(struct ListaLigadaPassageiro *lista) {
  lista->elemento = NULL;
  lista->tamanho = 0;
};

void inserirPassageiro(struct ListaLigadaPassageiro *lista, const char *nome,
                       const char *cpf) {
  struct Passageiro *novo =
      (struct Passageiro *)malloc(sizeof(struct Passageiro));
  if (novo == NULL) {
    printf("Erro na alocação de memória.\n");
    return;
  }

  strcpy(novo->nome, nome);
  strcpy(novo->cpf, cpf);
  novo->proximo = NULL;

  if (lista->elemento == NULL) {
    lista->elemento = novo;
  } else {
    struct Passageiro *atual = lista->elemento;
    while (atual->proximo != NULL) {
      atual = atual->proximo;
    }
    atual->proximo = novo;
  }

  lista->tamanho++;
}

void removerPassageiro(struct ListaLigadaPassageiro *lista, int posicao) {
  if (posicao < 0 || posicao >= lista->tamanho) {
    printf("Posição inválida.\n");
    return;
  }

  struct Passageiro *anterior = NULL;
  struct Passageiro *atual = lista->elemento;
  int contador = 0;

  while (atual != NULL && contador < posicao) {
    anterior = atual;
    atual = atual->proximo;
    contador++;
  }

  if (atual != NULL) {
    if (anterior == NULL) {
      lista->elemento = atual->proximo;
    } else {
      anterior->proximo = atual->proximo;
    }

    free(atual);
    lista->tamanho--;
  }
}

void exibirPassageiros(struct ListaLigadaPassageiro *lista) {
  printf("Lista de Passageiros:\n");
  struct Passageiro *atual = lista->elemento;
  while (atual != NULL) {
    printf("Nome: %s, CPF: %s\n", atual->nome, atual->cpf);
    atual = atual->proximo;
  }
}

int buscarPassageiro(struct ListaLigadaPassageiro *lista, const char *nome) {
  struct Passageiro *atual = lista->elemento;
  int posicao = 0;

  while (atual != NULL && strcmp(atual->nome, nome) != 0) {
    atual = atual->proximo;
    posicao++;
  }
  if (atual != NULL) {
    return posicao;
  } else {
    return -1;
  }
}

void selectionSortPassageiro(struct ListaLigadaPassageiro *lista) {
  struct Passageiro *atual, *menor, *proximo;
  char temp_nome[30], temp_cpf[20];

  atual = lista->elemento;
  while (atual != NULL) {
    menor = atual;
    proximo = atual->proximo;

    while (proximo != NULL) {
      if (strcmp(proximo->nome, menor->nome) < 0) {
        menor = proximo;
      }
      proximo = proximo->proximo;
    }

    // Troca os elementos
    strcpy(temp_nome, atual->nome);
    strcpy(temp_cpf, atual->cpf);
    strcpy(atual->nome, menor->nome);
    strcpy(atual->cpf, menor->cpf);
    strcpy(menor->nome, temp_nome);
    strcpy(menor->cpf, temp_cpf);

    atual = atual->proximo;
  }
}

void liberarLista(struct ListaLigadaPassageiro *lista) {
  struct Passageiro *atual = lista->elemento;
  while (atual != NULL) {
    struct Passageiro *proximo = atual->proximo;
    free(atual);
    atual = proximo;
  }

  lista->elemento = NULL;
  lista->tamanho = 0;
}

// =============
// === AVIÃO ===
// =============

struct Aviao {
  char destino[200];
  int numeroDePassageiros;
  struct ListaLigadaPassageiro listaDePassageiros;
  struct Aviao *proximo;
};

struct ListaLigadaAviao {
  struct Aviao *elemento;
  int tamanho;
};

void inicializarAviao(struct ListaLigadaAviao *lista) {
  lista->elemento = NULL;
  lista->tamanho = 0;
};

void inserirAviao(struct ListaLigadaAviao *lista, const char *nome,
                  int numero_de_passageiros) {
  struct Aviao *novo = (struct Aviao *)malloc(sizeof(struct Aviao));
  if (novo == NULL) {
    printf("Erro na alocação de memória.\n");
    return;
  }

  strcpy(novo->destino, nome);
  novo->numeroDePassageiros = numero_de_passageiros;
  novo->proximo = NULL;

  if (lista->elemento == NULL) {
    lista->elemento = novo;
  } else {
    struct Aviao *atual = lista->elemento;
    while (atual->proximo != NULL) {
      atual = atual->proximo;
    }
    atual->proximo = novo;
  }

  lista->tamanho++;
}

void removerAviao(struct ListaLigadaAviao *lista, int posicao) {
  if (posicao < 0 || posicao >= lista->tamanho) {
    printf("Posição inválida.\n");
    return;
  }

  struct Aviao *anterior = NULL;
  struct Aviao *atual = lista->elemento;
  int contador = 0;

  while (atual != NULL && contador < posicao) {
    anterior = atual;
    atual = atual->proximo;
    contador++;
  }

  if (atual != NULL) {
    if (anterior == NULL) {
      lista->elemento = atual->proximo;
    } else {
      anterior->proximo = atual->proximo;
    }

    free(atual);
    lista->tamanho--;
  }
}

void exibirAviao(struct ListaLigadaAviao *lista) {
  printf("Lista de Viagens:\n");
  struct Aviao *atual = lista->elemento;
  for (int i = 1; atual != NULL; i++) {
    printf("%d-Nome: %s, Numero de Passageiros: %d\n", i, atual->destino,
           atual->numeroDePassageiros);
    atual = atual->proximo;
  }
}

int buscarAviao(struct ListaLigadaAviao *lista, const char *nome) {
  struct Aviao *atual = lista->elemento;
  int posicao = 0;

  while (atual != NULL && strcmp(atual->destino, nome) != 0) {
    atual = atual->proximo;
    posicao++;
  }
  if (atual != NULL) {
    return posicao;
  } else {
    return -1;
  }
}

void selectionSortAviao(struct ListaLigadaAviao *lista) {
  struct Aviao *atual, *menor, *proximo;
  char temp_nome[30], temp_casa[20];

  atual = lista->elemento;
  while (atual != NULL) {
    menor = atual;
    proximo = atual->proximo;

    while (proximo != NULL) {
      if (strcmp(proximo->destino, menor->numeroDePassageiros) < 0) {
        menor = proximo;
      }
      proximo = proximo->proximo;
    }

    // Troca os elementos
    strcpy(temp_nome, atual->destino);
    strcpy(temp_casa, atual->numeroDePassageiros);
    strcpy(atual->destino, menor->destino);
    strcpy(atual->destino, menor->numeroDePassageiros);
    strcpy(menor->destino, temp_nome);
    strcpy(menor->numeroDePassageiros, temp_casa);

    atual = atual->proximo;
  }
}

void liberarListaAviao(struct ListaLigadaAviao *lista) {
  struct Aviao *atual = lista->elemento;
  while (atual != NULL) {
    struct Aviao *proximo = atual->proximo;
    free(atual);
    atual = proximo;
  }

  lista->elemento = NULL;
  lista->tamanho = 0;
}

/*
===  FILA DINÂMICA E OPERAÇÕES ===


*/

// Definição da estrutura de dados Item
typedef struct {
  char nome[TAMANHO_NOME];
  int numeroDePassageiros;
} Voo;

// Definição da estrutura opaca da fila
typedef struct {
  Voo *elementos;
  int inicio, fim, tamanho;
  int capacidade;
} Fila;

// Assinaturas de funções
int inicializarFila(Fila *fila);
int filaVazia(Fila *fila);
int redimensionarFila(Fila *fila);
void enqueue(Fila *fila, Voo item);
Voo dequeue(Fila *fila);
Voo peek(Fila *fila);
int tamanhoFila(Fila *fila);
void liberarFila(Fila *fila);
void reinicializarFila(Fila *fila);
Voo *filaParaArray(Fila *fila);
Fila *arrayParaFila(Voo *array, int tamanho);

void ListarVoos() {
  printf("=== Lista de Voos ===\n");
  printf("1. BH-RIO DE JANEIRO\n");
  printf("2. BH-SP\n");
  printf("3. SP-BRASILIA\n");
  printf("4. SP-SALVADOR\n");
  printf("5. SP-RIO DE JANEIRO\n");
}

int main() {

  // MYSQL *conn = mysql_init(NULL);

  // conecta(conn);

  // Declara uma variável do tipo FilaVoo
  Fila minhaFila;
  // Inicializa a fila
  inicializarFila(&minhaFila);

  struct ListaLigadaAviao minhaListaLigadaAviao;


  inicializarAviao(&minhaListaLigadaAviao);



  printf("Sistema de Gerenciamento de Voos\n");

  int opcao;
  int opcao2;
  do {
    // Exibe o menu
    printf("\nOperações:\n");
    printf("1. Novo voo.\n");
    printf("2. Cancelar Voo/Liberar decolagem.\n");
    printf("3. Primeiro da fila.\n");
    printf("4. Tamanho da fila.\n");
    printf("5. Reinicializar fila.\n");
    printf("6. Acessar voo.\n");
    printf("7. Sair.\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
    case 1: {
      // Antedeguemon
      char nome[TAMANHO_NOME];
      int passouDoTesteDeTamanho = 1;
      int deuCerto = 0;
      printf("Digite o destino do Voo: ");
      fgets(nome, TAMANHO_NOME, stdin);
      nome[strcspn(nome, "\n")] = '\0';

      // printf("deuCerto: %d, nome: %s", &deuCerto, nome);

      char numero[TAMANHO_NOME];
      printf("Digite a quantidade de Assentos: ");
      fgets(numero, TAMANHO_NOME, stdin);

      Voo Destino = {"", 0};
      // printf(nome);
      Destino.numeroDePassageiros = atoi(numero);
      // printf("NUMPAS %d", Destino.numeroDePassageiros);
      for (int i = 0; i < TAMANHO_NOME; i++) {
        Destino.nome[i] = nome[i];
      }

      printf("\nVoo a ser cadastrado: \nDestino: %s\nNumero De Assentos: "
             "%d \n",
             Destino.nome, Destino.numeroDePassageiros);
      int abc = 1;
      while (abc) {
        printf("Realizar o Cadastro do Voo? (S/n): ");
        char resposta[TAMANHO_NOME];
        scanf("%s", resposta);
        if (strcmp(resposta, "n") == 0 | strcmp(resposta, "N") == 0) {
          //printf("Para\n");
          abc = 2;
          break;
        } else if (strcmp(resposta, "s") == 0 | strcmp(resposta, "S") == 0) {
          abc = 0;
          //printf("Segue em frente\n");
        } else {
          printf("Entrada Inválida\n");
        }
      }
      if (abc == 2) {
        break;
      }

      enqueue(&minhaFila, Destino);

      inserirAviao(&minhaListaLigadaAviao, Destino.nome,
                   Destino.numeroDePassageiros);



      break;
    }
    case 2: {
      if (!filaVazia(&minhaFila)) {
        Voo pessoaRemovida = dequeue(&minhaFila);
        printf("Removendo Voo/Voo a decolar: %s\n", pessoaRemovida.nome);
      } else {
        printf("Fila vazia.\n");
      }
      break;
    }
    case 3: {
      if (!filaVazia(&minhaFila)) {
        Voo inicioFila = peek(&minhaFila);
        printf("Voo no início da fila: %s N.Assentos: %d\n", inicioFila.nome,
               inicioFila.numeroDePassageiros);
      } else {
        printf("Erro: Fila de decolagem vazia.\n");
      }
      break;
    }
    case 4: {
      printf("Tamanho da fila: %d\n", tamanhoFila(&minhaFila));
      break;
    }
    case 5: {
      reinicializarFila(&minhaFila);
      printf("Fila reinicializada.\n");
      break;
    }
    case 6: {
      do {
          if(minhaListaLigadaAviao.tamanho == 0){
            printf("Nenhum voo cadastrado\n");
            break;
          }
        int vooSelecionado = 1;
        int passou = 1;
        while(passou){
        printf("\n");

        exibirAviao(&minhaListaLigadaAviao);

        printf("\nDigite o número do voo desejado: ");
        scanf("%d", &vooSelecionado);

        if(vooSelecionado <= 0 || vooSelecionado >= (minhaListaLigadaAviao.tamanho + 1)){
            printf("\nEntrada Inválida\n");
        } else {
            passou = 0;
        }

        }

        vooSelecionado--;

        printf("\nOperações do Voo.\n");
        printf("1. Listar Dados do Voo.\n");
        printf("2. Novo pasageiro.\n");
        printf("3. Listar os Passageiros.\n");
        printf("4. Realizar Leilão de upgrade de classe.\n");
        printf("5. Voltar.\n");

        printf("Selecione uma opção: ");

        scanf("%d", &opcao2);

        switch (opcao2) {
        case 1: {
          // Função de listar dados do voo
          printf("Destino: %s \n Numero de Assentos: %d \n Numero de passageiros cadastrados: %d", minhaListaLigadaAviao.elemento[vooSelecionado].destino
                 ,minhaListaLigadaAviao.elemento[vooSelecionado].numeroDePassageiros,minhaListaLigadaAviao.elemento[vooSelecionado].listaDePassageiros.tamanho);
          break;
        }
        case 2: {
          // Função de novo Passageiro Atumalaca
          char nome[TAMANHO_NOME];
          char cpf[12];
          char simounao[123123];
          int participaDoLeilao = 0;
          float valorDoLance = 0;
          printf("Digite o nome do novo Passageiro: ");
          scanf("%s", nome);
          printf("Digite o CPF do novo Passageiro: ");
          scanf("%s", cpf);
          printf("Passageiro participa do leilão de upgrade de classe? (S/N)\n");
          scanf("%s", simounao);
          if (strcmp(simounao, "S") || strcmp(simounao, "SIM") ||
              strcmp(simounao, "s") || strcmp(simounao, "sim")) {
            participaDoLeilao = 1;
            int piton = 1;
            while (piton) {
              printf("(Lance Mínimo: R$ 1000)\n");
              printf("Qual o valor do lance do passageiro?\n");
              scanf("%f", &valorDoLance);
              if (valorDoLance >= 1000.0) {
                piton = 0;
              } else {
                printf("Digite um valor maior que o lance mínimo\n");
              }
            }
          }
          inserirPassageiro(&minhaListaLigadaAviao.elemento[vooSelecionado].listaDePassageiros, nome, cpf);
          break;
        }
        case 3: {
          // Função de listar passageiros
          printf("\nLista de Passageiros:\n");
          /*if (minhaListaLigadaAviao.tamanho > 0) {
            for (int i = 0; i < minhaListaLigadaAviao.elemento[vooSelecionado].listaDePassageiros.tamanho; i++) {
              printf("i equivale a : %d", i);
              printf("\nNome: %s, CPF: %s\n",
                     minhaListaLigadaAviao.elemento[vooSelecionado]
                         .listaDePassageiros.elemento[i].nome,
                     minhaListaLigadaAviao.elemento[vooSelecionado]
                         .listaDePassageiros.elemento[i].cpf);
            }
          }
           */
          exibirPassageiros(&minhaListaLigadaAviao.elemento[vooSelecionado].listaDePassageiros);

          break;
        }
        case 4: {
          // Função de upgrade de classe();
          printf("A fazer \n");
          /*
                    printf("Ganhadores do upgrade de classe\n");
                    printf("1. %s\n", "Cleberson Air Max");
                    printf("2. %s\n", "Cleberson Air Max");
                    printf("3. %s\n", "Cleberson Air Max");
                    printf("4. %s\n", "Cleberson Air Max");
                    printf("5. %s\n", "Cleberson Air Max");
            */
          break;
        }
        case 5: {
          break;
        }
        default: {
          printf("Opção inválida. Escolha uma opção válida.\n");
          break;
        }
        }

      } while (opcao2 != 5);

      break;
    }

    case 7: {
      printf("Encerrando o programa.\n");
      break;
    }

    default: {
      printf("Opção inválida. Escolha uma opção válida.\n");
      break;
    }
    }
  } while (opcao != 7);

  return 0;
}

// Função para inicializar a fila
int inicializarFila(Fila *fila) {
  fila->inicio = 0;
  fila->fim = -1;
  fila->tamanho = 0;
  fila->capacidade = 1; // Capacidade inicial
  fila->elementos = (Voo *)malloc(fila->capacidade * sizeof(Voo));
  if (fila->elementos == NULL) {
    printf("Erro de alocação de memória.\n");
    return -1;
  }
  return 0;
}

// Função para verificar se a fila está vazia
int filaVazia(Fila *fila) { return fila->tamanho == 0; }

// Função para redimensionar a capacidade da fila
int redimensionarFila(Fila *fila) {
  // Dobrar a capacidade
  int novaCapacidade = fila->capacidade * 2;
  Voo *novoArray =
      (Voo *)realloc(fila->elementos, novaCapacidade * sizeof(Voo));
  if (novoArray == NULL) {
    printf("Erro de realocação de memória.\n");
    return -1;
  }
  fila->elementos = novoArray;
  fila->capacidade = novaCapacidade;
  return 0;
}

// Função para adicionar um elemento à fila
void enqueue(Fila *fila, Voo item) {
  if (fila->tamanho == fila->capacidade) {
    redimensionarFila(fila);
  }
  fila->fim = (fila->fim + 1) % fila->capacidade;
  fila->elementos[fila->fim] = item;
  fila->tamanho++;
}
// Função para remover um elemento da fila
Voo dequeue(Fila *fila) {
  if (filaVazia(fila)) {
    printf("Erro: Fila vazia.\n");
    Voo itemInvalido = {-1, ""}; // Valor inválido para o item
    return itemInvalido;
  }
  Voo item = fila->elementos[fila->inicio];
  fila->inicio = (fila->inicio + 1) % fila->capacidade;
  fila->tamanho--;
  return item;
}

// Função para retornar o elemento no início da fila
Voo peek(Fila *fila) {
  if (filaVazia(fila)) {
    printf("Erro: Fila vazia.\n");
    Voo itemInvalido = {-1, ""}; // Valor inválido para o item
    return itemInvalido;
  }
  return fila->elementos[fila->inicio];
}

// Função para liberar a memória alocada para a fila
void liberarFila(Fila *fila) { free(fila->elementos); }

// Função para retornar o tamanho da fila
int tamanhoFila(Fila *fila) { return fila->tamanho; }

// Função para reinicializar a fila
void reinicializarFila(Fila *fila) {
  fila->inicio = 0;
  fila->fim = -1;
  fila->tamanho = 0;
}

// Função para converter a fila em um vetor de Item
Voo *filaParaArray(Fila *fila) {
  Voo *array = (Voo *)malloc(fila->tamanho * sizeof(Voo));
  if (array == NULL) {
    printf("Erro: Falha ao alocar memória para o vetor.\n");
    return NULL;
  }
  int j = fila->inicio;
  for (int i = 0; i < fila->tamanho; i++) {
    array[i] = fila->elementos[j];
    j = (j + 1) % fila->capacidade;
  }
  return array;
}

// Função para converter um vetor de item para a fila
Fila *arrayParaFila(Voo *array, int tamanho) {
  Fila *fila = (Fila *)malloc(sizeof(Fila));
  if (fila == NULL) {
    printf("Erro: Falha ao alocar memória para a fila.\n");
    return NULL;
  }
  fila->inicio = 0;
  fila->fim = tamanho - 1;
  fila->tamanho = tamanho;
  fila->capacidade = tamanho;
  fila->elementos = array;
  return fila;
}
