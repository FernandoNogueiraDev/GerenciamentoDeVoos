#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#define TAMANHO_FILA 5
#define TAMANHO_NOME 20


/*
=== CONEXÃO MYSQL E QUERIES ===
*/


    void conecta (MYSQL *conn){
    if (!mysql_real_connect(conn, "localhost", "root", "", NULL, 3306, NULL, 0))
    {
        fprintf(stderr, "Erro na conexão: Erro: %s\n",
              mysql_error(conn));
              mysql_close(conn);
              exit(1);
    }
    }

    void printaErro(MYSQL *conn, char *mensagemDeErro){
        fprintf(stderr, "%s: s%\n", mensagemDeErro, mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }




/*
===  LISTA LIGADA E OPERAÇÕES ===
*/

struct Passageiro {
  char nome[30];
  char cpf[20];
  struct Passageiro *proximo;
};

struct ListaLigada {
  struct Passageiro *elemento;
  int tamanho;
};

void inicializar(struct ListaLigada *lista) {
  lista->elemento = NULL;
  lista->tamanho = 0;
};

void inserir(struct ListaLigada *lista, const char *nome, const char *cpf) {
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

void remover(struct ListaLigada *lista, int posicao) {
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

void exibir(struct ListaLigada *lista) {
  printf("Lista de Passageiros:\n");
  struct Passageiro *atual = lista->elemento;
  while (atual != NULL) {
    printf("Nome: %s, CPF: %s\n", atual->nome, atual->cpf);
    atual = atual->proximo;
  }
}

int buscar(struct ListaLigada *lista, const char *nome) {
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

void selectionSort(struct ListaLigada *lista) {
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

void liberarLista(struct ListaLigada *lista) {
  struct Passageiro *atual = lista->elemento;
  while (atual != NULL) {
    struct Passageiro *proximo = atual->proximo;
    free(atual);
    atual = proximo;
  }

  lista->elemento = NULL;
  lista->tamanho = 0;
}

/*
===  FILA DINÂMICA E OPERAÇÕES ===
*/

struct Aviao {
  char RAB[5];
  char nome[30];
  char destino[20];
  struct Passageiro listaDePassageiros[100];
  struct Passageiro *proximo;
};

// Definição da estrutura de dados Item
typedef struct {
  char nome[TAMANHO_NOME];
} Item;

// Definição da estrutura opaca da fila
typedef struct {
  Item elementos[TAMANHO_FILA];
  int inicio, fim, tamanho;
} Fila;

// Assinaturas de funções
void inicializarFila(Fila *fila);
int filaVazia(Fila *fila);
void enqueue(Fila *fila, Item item);
Item dequeue(Fila *fila);
Item peek(Fila *fila);
int tamanhoFila(Fila *fila);
void reinicializarFila(Fila *fila);

void ListarVoos() {
  printf("=== Lista de Voos ===\n");
  printf("1. BH-RIO DE JANEIRO\n");
  printf("2. BH-SP\n");
  printf("3. SP-BRASILIA\n");
  printf("4. SP-SALVADOR\n");
  printf("5. SP-RIO DE JANEIRO\n");
}

int main() {
  // Declara uma variável do tipo Fila
  Fila minhaFila;
  // Inicializa a fila
  inicializarFila(&minhaFila);

  printf("Sistema de Gerenciamento de Voos\n");

  int opcao;
  int opcao2;
  do {
    // Exibe o menu
    printf("\nMenu:\n");
    printf("1. Novo voo\n");
    printf("2. Cancelar Voo\n");
    printf("3. Primeiro da fila\n");
    printf("4. Tamanho da fila\n");
    printf("5. Reinicializar fila\n");
    printf("6. Acessar voo\n");
    printf("7. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1: {
      char nome[TAMANHO_NOME];
      printf("Digite o destino do Voo a ser enfileirado:");
      scanf("%s", nome);
      Item Destino = {""};
      for (int i = 0; i < TAMANHO_NOME; i++) {
        Destino.nome[i] = nome[i];
      }
      enqueue(&minhaFila, Destino);
      break;
    }
    case 2: {
      if (!filaVazia(&minhaFila)) {
        Item pessoaRemovida = dequeue(&minhaFila);
        printf("Removendo Voo: %s\n", pessoaRemovida.nome);
      } else {
        printf("Erro: Fila vazia.\n");
      }
      break;
    }
    case 3: {
      if (!filaVazia(&minhaFila)) {
        Item inicioFila = peek(&minhaFila);
        printf("Voo no início da fila: %s\n", inicioFila.nome);
      } else {
        printf("Erro: Fila vazia.\n");
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
        int vooSelecionado;

        ListarVoos();

        printf("Digite o número do voo desejado: ");
        scanf("%d", &vooSelecionado);

        printf("\nOperações do Voo.\n");
        printf("1. Listar Dados do Voo.\n");
        printf("2. Listar os Passageiros.\n");
        printf("3. Novo pasageiro.\n");
        printf("4. Realizar Leilão de upgrade de classe\n");

        printf("Selecione uma opção: ");

        scanf("%d", &opcao2);

        switch (opcao2) {
        case 1: {
          // Função de listar dados do voo
          printf("Dados do Voo selecionado: \n");
          printf("Linha aérea: %s\n", "Cleberson Air Max");
          printf("Destino: %s\n", "Brasilia");
          printf("Data: %s\n", "12/05/2024");
          printf("Horário: %s\n", "19:00");
          printf("Número de passageiros: %d\n", 100);
          break;
        }
        case 2: {
          // Função de listar passageiros
          printf("Lista de Passageiros:\n");
          for (int i = 0; i < TAMANHO_FILA; i++){
            printf("Nome: %s, CPF: %s\n", minhaFila.elementos[i]);
          }
        }
        case 3: {
          // Função de novo Passageiro
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
          if(strcmp(simounao, "S") || strcmp(simounao, "SIM") || strcmp(simounao, "s") || strcmp(simounao, "sim"))
          {
          participaDoLeilao = 1;
          int piton = 1;
          while(piton){
          printf("(Lance Mínimo: R$ 1000)\n");
          printf("Qual o valor do lance do passageiro?\n");
          scanf("%f", &valorDoLance);
          if(valorDoLance >= 1000.0){
            piton = 0;
          } else {
            printf("Digite um valor maior que o lance mínimo\n");
          }

          }
          }
          //inserir(&minhaFila, nome, cpf);
          break;
        }
          case 4:{
            // Função de upgrade de classe();

            printf("Ganhadores do upgrade de classe\n");
            printf("1. %s\n", "Cleberson Air Max");
            printf("2. %s\n", "Cleberson Air Max");
            printf("3. %s\n", "Cleberson Air Max");
            printf("4. %s\n", "Cleberson Air Max");
            printf("5. %s\n", "Cleberson Air Max");
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

// Função para adicionar um elemento à fila
void enqueue(Fila *fila, Item item) {
  if (fila->tamanho < TAMANHO_FILA) {
    fila->fim = (fila->fim + 1) % TAMANHO_FILA;
    fila->elementos[fila->fim] = item;
    fila->tamanho++;
  } else {
    printf("Erro: Fila cheia.\n");
  }
}

// Função para remover um elemento da fila
Item dequeue(Fila *fila) {
  if (!filaVazia(fila)) {
    Item itemRemovido = fila->elementos[fila->inicio];
    fila->inicio = (fila->inicio + 1) % TAMANHO_FILA;
    fila->tamanho--;
    return itemRemovido;
  } else {
    printf("Erro: Fila vazia.\n");
    Item itemInvalido = {""};
    return itemInvalido;
  }
}

// Função para retornar o elemento no início da fila
Item peek(Fila *fila) {
  if (!filaVazia(fila)) {
    return fila->elementos[fila->inicio];
  } else {
    printf("Erro: Fila vazia.\n");
    Item itemInvalido = {""};
    return itemInvalido;
  }
}

// Função para inicializar a fila
void inicializarFila(Fila *fila) {
  fila->inicio = 0;
  fila->fim = -1;
  fila->tamanho = 0;
}

// Função para verificar se a fila está vazia
int filaVazia(Fila *fila) { return fila->tamanho == 0; }

// Função para retornar o tamanho da fila
int tamanhoFila(Fila *fila) { return fila->tamanho; }

// Função para reinicializar a fila
void reinicializarFila(Fila *fila) {
  fila->inicio = 0;
  fila->fim = -1;
  fila->tamanho = 0;
}
