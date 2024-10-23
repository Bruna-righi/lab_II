#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//o que ainda precisa ser feito:
/* 1- eu preciso modificar minha struct de projetos, pois o "professor" deve ser um ponteiro.
   2- eu preciso ajustar a forma como eu estou registrando projetos, pois
   não há verificações de erros ou inserções indevidas
   3- modificar minha função de busca para um único while e checar os tipos depois
   4 - eu preciso mudar minhas funções para que a cabeça da lista seja um 
   ponteiro de ponteiros*/

//para lembrar a mim mesma: fgets já coloca o '\0' no final da string, eu não preciso pôr!

#define PROJETOS 0
#define ALUNOS 1
#define PROFESSORES 2

typedef struct Lista lista;

void* cria_novo_lista();

typedef struct Lista{
    void* dados;
    lista* next;
}lista;

typedef struct Alunos{
    int matricula;
    char* nome;
    long int telefone;
}alunos;

typedef struct Projetos{
    
    int codigo;
    char* descricao;
    enum escolha {ensino=1, pesquisa, extensão};
    enum escolha tipo; 
    float orcamento_aprovado;
    float orcamento_disponivel;
    professores* prof_coordenador;
}projetos;

typedef struct Vinculos{
    alunos* aluno;
    projetos* projeto;
    float bolsa;
}vinculos;

typedef struct Professores{
    int codigo;
    char* nome;
    char* departamento;
}professores;

char* inicializa_nomes(){
    char* nome = (char*) malloc(sizeof(char)*110);
    return nome;
}

void* acha_ultimo(lista* minha_lista){
    lista* p = minha_lista;
    if(p!= NULL){
        while(p->next!=NULL) p = p->next;
    }
    return p;
}

void* acha_na_lista(lista* minha_lista, int n, int tipo){
    lista* p = minha_lista;
    if(tipo == 0){
        while(p != NULL){
            if(((projetos*)p->dados)->codigo == n){
                return p->dados;
            }
            p = p->next;
        }
    }
    if(tipo == 1){
        while(p != NULL){
            if(((alunos*)p->dados)->matricula == n){
                return p->dados;
            }
            p = p->next;
        }
    }
    if(tipo == 2){
        while(p != NULL){
            if(((professores*)p->dados)->codigo == n){
                return p->dados;
            }
            p = p->next;
        }
    }
    return NULL;
}

void* busca_e_remove_vinculo(lista* minha_lista, alunos* aluno, projetos* projeto){
    lista* p = minha_lista;
    lista* ant  = NULL;
    while(p != NULL){
        if(((vinculos*)p->dados)->aluno == aluno && ((vinculos*)p->dados)->projeto == projeto){
            if(ant == NULL) return p->next;
            if(p->next == NULL){
                p = NULL;
                free(p->next);
                return minha_lista;
            } 
            ant->next = p->next;
            free(p);
            return minha_lista;
        }
        ant = p;
        p = p->next;
    }
    return NULL;
}

alunos* parametros_alunos(){
    alunos* novo = (alunos*) malloc(sizeof(alunos));
    novo->nome = inicializa_nomes();
    printf("Digite o nome do aluno: ");
    fgets(novo->nome, sizeof(char)*110, stdin);
    novo->nome[strcspn(novo->nome, "\n")] = 0;
    printf("Digite a matricula do aluno: ");
    scanf(" %d", &novo->matricula);
    printf("Digite o número de telefone do aluno: ");
    scanf(" %ld", &novo->telefone);
    //printf("%d, %ld, %s", novo->matricula, novo->telefone, novo->nome);
    return novo;
}

professores* parametros_professores(){
    professores* novo = (professores*) malloc(sizeof(professores));
    printf("Digite o código do professor: ");
    scanf(" %d", &novo->codigo);
    novo->nome = inicializa_nomes();
    printf("Digite o nome do professor: ");
    fgets(novo->nome, sizeof(char)*110, stdin);
    novo->nome[strcspn(novo->nome, "\n")] = 0;
    novo->departamento = inicializa_nomes();
    printf("Digite o departamento de lotação do professor: ");
    fgets(novo->departamento, sizeof(char)*110, stdin);
    return novo;
}

projetos* parametros_projetos(){
    projetos* novo = (projetos*)malloc(sizeof(projetos));
    //código
    printf("Digite o código do projeto: ");
    scanf(" %d", &novo->codigo);
    //descrição
    novo->descricao = malloc(sizeof(char)*400);
    novo->prof_coordenador = inicializa_nomes();
    printf("Digite a descrição do projeto: ");
    fgets(novo->descricao, sizeof(char)*400, stdin);
    //tipo
    printf("Para o tipo de projeto:\n - Digite 1 se \"ensino\";\n - Digite 2 se \"pesquisa\";\n- Digite 3 se \"extensão\".\n");
    scanf(" %d", &novo->tipo);
    //orçamento
    printf("Digite o orçamento aprovado para o projeto: ");
    scanf(" %f", &novo->orcamento_aprovado);
    novo->orcamento_disponivel = novo->orcamento_aprovado;
    //nome professor
    printf("Digite o nome do professor coordenador: ");
    fgets(novo->prof_coordenador, sizeof(char)*110, stdin);
    return novo;
}

void* insere_no_final(void* parametro, lista* minha_lista){
    lista* p = acha_ultimo(minha_lista);
    lista* novo = (void*) malloc(sizeof(lista));
    novo->dados = parametro;
    novo->next = NULL;
    if(minha_lista == NULL){
        return novo;
    }
    p->next = novo;
    return minha_lista;
}

// a lista que eu passo como "minha_lista" deve ser diferente para cada tipo de dado
// ou seja, eu crio uma lista void para cada uma das minhas structs
void* insere_novo_lista(void* parametro, lista* minha_lista){ 
    lista* novo = (void*) malloc(sizeof(lista));
    novo->dados = parametro;
    novo->next = minha_lista;
    return novo;
}

void* cria_novo_lista(){
    return NULL;
}

lista* exclui_vinculo(lista* lista_vinculos, lista* lista_alunos, lista* lista_projetos){
    //lê os dados necessários
    int mat, cod, meses;
    printf("Digite o código do projeto do qual deseja remover o aluno: ");
    scanf(" %d", &cod);
    printf("Digite a matrícula do aluno que deseja remover do projeto: ");
    scanf(" %d", &mat);
    printf("Digite quantos meses de bolsa não serão mais pagos: ");
    scanf(" %d", &meses);
    //busca se há compabilidade nas listas
    alunos* aluno_remocao = (alunos*)acha_na_lista(lista_alunos, mat, ALUNOS);
    projetos* projeto_remocao = (projetos*) acha_na_lista(lista_projetos, cod, PROJETOS);
    vinculos* vinculo = (vinculos*) busca_e_remove_vinculo(lista_vinculos, aluno_remocao, projeto_remocao);
    if(vinculo == NULL){
        printf("Nada a remover!\n");
        return lista_vinculos;
    }
    return lista_vinculos;
}

vinculos* parametros_vinculos(lista* lista_alunos, lista* lista_projetos){
    float valor_bolsa;
    int projeto, matri;
    printf("Digite o código do projeto ao qual deseja vincular o aluno: ");
    scanf(" %d", &projeto);
    printf("Digite o valor mensal da bolsa do aluno: ");
    scanf(" %d", &valor_bolsa);
    projetos* temp = (projetos*) acha_na_lista(lista_projetos, projeto, PROJETOS);
    if(temp->orcamento_disponivel - (12*valor_bolsa) > 0){
        vinculos* novo = (vinculos*)malloc(sizeof(vinculos));
        printf("Digite a matrícula do aluno a ser vinculado: ");
        scanf(" %d", &matri);
        alunos* aux = (alunos*) acha_na_lista(lista_alunos, matri, ALUNOS);
        if(aux != NULL){
            novo->aluno = aux;
            novo->projeto = temp;
            novo->bolsa = valor_bolsa;
            temp->orcamento_disponivel -= 12*novo->bolsa;
            return novo;
        }else{
            printf("Aluno inexistente! Não foi possível criar o vínculo.\n");
            return NULL;
        }
    }else printf("Não foi possível vincular o aluno ao projeto, orçamento insuficente para a bolsa!\n");
    return NULL;
}

int main(){
    alunos* novo = parametros_alunos();
}
