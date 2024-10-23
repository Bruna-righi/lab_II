#include <stdio.h>
#include <stdbool.h>
#include "bolsistas.h"

void menu(lista** lista_alunos, lista** lista_professores, lista** lista_projetos, lista** lista_vinculos);
void imprime_opcoes();
void insere_novos_dados(lista** lista_alunos, lista** lista_professores, lista** lista_projetos, lista** lista_vinculos);
void cria_vinculo(lista** lista_alunos, lista** lista_professores, lista** lista_projetos, lista** lista_vinculos);

//o menu em si:

void menu(lista** lista_alunos, lista** lista_professores, lista** lista_projetos, lista** lista_vinculos){
/*esta função recebe as listas existentes e dá as opções
de o que o programa pode fazer*/
    int opcao;
    bool menu_laco = true;
    while(menu_laco){

        //interação com o usuário
        imprime_opcoes();
        printf("Digite a opção escolhida:\n");
        printf(">>> ");
        scanf(" %d", &opcao);

        switch (opcao){

        //inserir dados
        case 1:
            insere_novos_dados(&lista_alunos, &lista_professores, &lista_projetos, &lista_vinculos);
            break;

        //criar um novo vinculo
        case 2:
            cria_vinculo(&lista_alunos, &lista_professores, &lista_projetos, &lista_vinculos);
            break;

        //excluir um vinculo já existente
        case 3:
            exclui(&lista_alunos, &lista_professores, &lista_projetos, &lista_vinculos);
            break;

        //imprimir a situação atual das listas existentes
        case 4:
            imprime_dados(&lista_alunos, &lista_professores, &lista_projetos, &lista_vinculos);
            break;

        //gerar o relatório final e encerrar o programa
        case 5:
            relatorio(&lista_alunos, &lista_professores, &lista_projetos, &lista_vinculos);
            menu_laco = false;
            break;

        //volta ao menu
        case 6:
            break;

        //nenhuma das àcima foi selecionada (fora do escopo)
        default:
            printf("Opção não existente! Tente outra.\n");
            break;
        }

        printf("\n");
    }
}

//opções do programa:

void imprime_opcoes(){
    printf("O programa pode realizar as seguintes ações:\n");
    printf("1 - inserir novos dados;\n");
    printf("2 - criar um vínculo;\n");
    printf("3 - excluir um vínculo;\n");
    printf("4 - imprimir os dados atuais;\n");
    printf("5 - gerar relatório e encerrar o programa;\n");
    printf("6 - voltar ao menu;\n");
}

void insere_novos_dados(lista** lista_alunos, lista** lista_professores, lista** lista_projetos, lista** lista_vinculos){
    int dado, quantidade;
    printf("Escolha o tipo de dado que deseja inserir:\n");
    printf("1 - inserir um aluno;\n");
    printf("2 - inserir um professor;\n");
    printf("3 - inserir um projeto;\n");
    printf(">>> ");
    scanf(" %d", &dado);
    printf("Digite quantos dados desse tipo deseja inserir:\n");
    printf(">>> ");
    scanf(" %d", &quantidade);
    if(quantidade <= 0){
        printf("Quantidade inválida, voltando ao menu...");
        return;
    }
    for(int i=0; i<quantidade; i++){
        switch(dado){
            case 1:
                alunos* novo_aluno = parametros_alunos();
                *lista_alunos = insere_novo_lista(novo_aluno, &lista_alunos);
                break;
            case 2:
                professores* novo_professor = parametros_professores();
                *lista_professores = insere_novo_lista(novo_professor, &lista_professores);
                break;
            case 3:
                projetos* novo_projeto = parametros_projetos();
                *lista_projetos = insere_novo_lista(novo_projeto, &lista_projetos);
                break;
            default:
                printf("Opção não disponível!\n");
                return;
        }
    }
}

void cria_vinculo(lista** lista_alunos, lista** lista_professores, lista** lista_projetos, lista** lista_vinculos){
    //essa parte precisa de alterações em outros locais do código
    //ou seja, não vou fazer agr
}

void exclui(lista** lista_alunos, lista** lista_professores, lista** lista_projetos, lista** lista_vinculos){
    *lista_vinculos = exclui_vinculo;
}
