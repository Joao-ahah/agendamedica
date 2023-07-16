#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do paciente
typedef struct Paciente {
    char nome[50];
    char dataConsulta[20];
    char data[20];
    char hora[20];
    char telefone[20];
    char cpf[20];
    struct Paciente* esquerda;
    struct Paciente* direita;
} Paciente;

// Função auxiliar para encontrar o paciente mínimo na subárvore direita
Paciente* pacienteMinimo(Paciente* node) {
    Paciente* atual = node;
    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

// Função para criar um novo nó da árvore
Paciente* criarNo(char nome[], char cpf[], char dataConsulta[], char telefone[], char data[], char hora[]) {
    Paciente* novo_paciente = (Paciente*)malloc(sizeof(Paciente));
    strcpy(novo_paciente->nome, nome);
    strcpy(novo_paciente->cpf, cpf);
    strcpy(novo_paciente->dataConsulta, dataConsulta);
    strcpy(novo_paciente->telefone, telefone);
    strcpy(novo_paciente->data, data);
    strcpy(novo_paciente->hora, hora);
    novo_paciente->esquerda = NULL;
    novo_paciente->direita = NULL;
    return novo_paciente;
}

// Função para inserir um paciente na árvore
Paciente* inserirPaciente(Paciente* raiz, char nome[], char cpf[], char dataConsulta[], char telefone[], char data[],  char hora[]) {
    if (raiz == NULL) {
        return criarNo(nome, cpf, dataConsulta, telefone, data, hora);
    }

    if (strcmp(nome, raiz->nome) < 0) {
        raiz->esquerda = inserirPaciente(raiz->esquerda, nome, cpf, dataConsulta, telefone, data, hora);
    } else if (strcmp(nome, raiz->nome) > 0) {
        raiz->direita = inserirPaciente(raiz->direita, nome, cpf, dataConsulta, telefone, data, hora);
    }

    return raiz;
}

// Função para agendar uma nova consulta
Paciente* agendarConsulta(Paciente* raiz) {
    char nome[50];
    char cpf[20];
    char dataConsulta[20];
    char data[20];
    char hora[20];
    char telefone[20];

    // Tratamento de erros
    printf("Nome do paciente: ");
    scanf("%s", nome);
    printf("CPF do paciente (xxx.xxx.xxx-xx): ");
    scanf("%s", cpf);
    while (strlen(cpf) != 14) {
        printf("\x1b[38;2;255;0;0m");
        printf("CPF inválido. Digite novamente (xxx.xxx.xxx-xx): ");
        printf("\x1b[0m");
        scanf("%s", cpf);
    }
    printf("Data de nascimento (dd/mm/aaaa): ");
    scanf("%s", data);
    while (strlen(data) != 10) {
        printf("\x1b[38;2;255;0;0m");
        printf("Data inválida. Digite novamente (dd/mm/aaaa): ");
        printf("\x1b[0m");
        scanf("%s", data);
    }
    // se o telefone for maior que 13 dígitos, retorna erro e digite novamente
    printf("Telefone do paciente: ");
    scanf("%s", telefone);
    while (strlen(telefone) > 13) {
        printf("\x1b[38;2;255;0;0m");
        printf("Telefone inválido. Digite novamente (xx-xxxxx-xxxx): ");
        printf("\x1b[0m");
        scanf("%s", telefone);
    }
    printf("Data da consulta (dd/mm/aaaa): ");
    scanf("%s", dataConsulta);
    while (strlen(dataConsulta) != 10) {
        printf("\x1b[38;2;255;0;0m");
        printf("Data inválida. Digite novamente (dd/mm/aaaa): ");
        printf("\x1b[0m");
        scanf("%s", dataConsulta);
    }
    
    // se a hora da consulta for maior que 24h, retorna erro e digite novamente
    printf("Hora da consulta (hh:mm): ");
    scanf("%s", hora);
    while (strlen(hora) > 24) {
        printf("\x1b[38;2;255;0;0m");
        printf("Hora inválida. Digite novamente (hh:mm): ");
        printf("\x1b[0m");
        scanf("%s", hora);
    }

    raiz = inserirPaciente(raiz, nome, cpf, dataConsulta, telefone, data, hora);
    printf("\x1b[38;2;0;255;0m");
    printf("AGENDAMENTO COM SUCESSO!\n");
    printf("\x1b[0m");

    return raiz;
}

// Função para exibir os pacientes em ordem alfabética
void exibirPacientes(Paciente* raiz) {
    if (raiz != NULL) {
        exibirPacientes(raiz->esquerda);
        printf("Nome: %s\n", raiz->nome);
        printf("CPF: %s\n", raiz->cpf);
        printf("Telefone: %s\n", raiz->telefone);
        printf("Data da Consulta: %s\n", raiz->dataConsulta);
        printf("Data: %s\n", raiz->data);
        printf("Consulta às:: %s\n", raiz->hora);
        printf("-----------------\n");
        exibirPacientes(raiz->direita);
    }
}
// Função para editar as informações na árvore pelo nome

Paciente* editarPaciente(Paciente* raiz, char nome[]) {
    if (raiz == NULL || strcmp(nome, raiz->nome) == 0) {
        return raiz;
    }

    if (strcmp(nome, raiz->nome) < 0) {
        return editarPaciente(raiz->esquerda, nome);
    } else {
        return editarPaciente(raiz->direita, nome);
    }
}


// Função para buscar um paciente na árvore pelo nome
Paciente* buscarPaciente(Paciente* raiz, char cpf[]) {
    if (raiz == NULL || strcmp(cpf, raiz->cpf) == 0) {
        return raiz;
    }

    if (strcmp(cpf, raiz->cpf) < 0) {
        return buscarPaciente(raiz->esquerda, cpf);
    } else {
        return buscarPaciente(raiz->direita, cpf);
    }
}

// Função para visualizar as consultas em ordem de nome
void visualizarConsultas(Paciente* raiz) {
    if (raiz != NULL) {
        visualizarConsultas(raiz->esquerda);
        printf("Nome: %s\n", raiz->nome);
        printf("CPF: %s\n", raiz->cpf);
        printf("Telefone: %s\n", raiz->telefone);
        printf("Data da Consulta: %s\n", raiz->dataConsulta);
        printf("Data: %s\n", raiz->data);
        printf("Consulta às: %s\n", raiz->hora);
        printf("-----------------\n");
        visualizarConsultas(raiz->direita);
    }
}
// Função auxiliar para encontrar o paciente máximo na subárvore esquerda
Paciente* pacienteMaximo(Paciente* node) {
    Paciente* atual = node;
    while (atual && atual->direita != NULL) {
        atual = atual->direita;
    }
    return atual;
}

// Função auxiliar para remover um paciente da árvore
Paciente* removerPaciente(Paciente* raiz, char cpf[]) {
    if (raiz == NULL) {
        return raiz;
    }

    if (strcmp(cpf, raiz->cpf) < 0) {
        raiz->esquerda = removerPaciente(raiz->esquerda, cpf);
    } else if (strcmp(cpf, raiz->cpf) > 0) {
        raiz->direita = removerPaciente(raiz->direita, cpf);
    } else {
        // Caso 1: O nó a ser removido não possui filhos
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            raiz = NULL;
        }
        // Caso 2: O nó a ser removido possui apenas um filho
        else if (raiz->esquerda == NULL) {
            Paciente* temp = raiz;
            raiz = raiz->direita;
            free(temp);
        } else if (raiz->direita == NULL) {
            Paciente* temp = raiz;
            raiz = raiz->esquerda;
            free(temp);
        }
        // Caso 3: O nó a ser removido possui dois filhos
        else {
            Paciente* temp = pacienteMinimo(raiz->direita);
            strcpy(raiz->nome, temp->nome);
            strcpy(raiz->cpf, temp->cpf);
            strcpy(raiz->telefone, temp->telefone);
            strcpy(raiz->dataConsulta, temp->dataConsulta);
            strcpy(raiz->data, temp->data);
            strcpy(raiz->hora, temp->hora);
            raiz->direita = removerPaciente(raiz->direita, temp->nome);
        }
    }

    return raiz;
}

// Função para remover uma consulta da árvore
Paciente* removerConsulta(Paciente* raiz) {
    char cpf[20];

    printf("CPF do paciente a ser removido: ");
    scanf("%s", cpf);

    raiz = removerPaciente(raiz, cpf);
    printf("\x1b[38;2;0;255;0m");
    printf("CONSULTA REMOVIDA COM SUCESSO!\n\n");
    printf("\x1b[0m");

    return raiz;
}



// Função para salvar a árvore em um arquivo de texto
void salvarArvoreEmArquivo(FILE* arquivo, Paciente* raiz) {
    if (raiz != NULL) {
        salvarArvoreEmArquivo(arquivo, raiz->esquerda);
        fprintf(arquivo, "Nome: %s\n", raiz->nome);
        fprintf(arquivo, "CPF: %s\n", raiz->cpf);
        fprintf(arquivo, "Telefone: %s\n", raiz->telefone);
        fprintf(arquivo, "Data: %s\n", raiz->data);
        fprintf(arquivo, "Data da Consulta: %s\n", raiz->dataConsulta);
        fprintf(arquivo, "Consulta às: %s\n", raiz->hora);
        fprintf(arquivo, "-----------------\n");
        salvarArvoreEmArquivo(arquivo, raiz->direita);
    }
}

void liberarArvore(Paciente* raiz) {

    if (raiz != NULL) {

        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

int main() {
Paciente* raiz = NULL;
int opcao;

do {
    printf("======== Sistema de Agendamento de Consultas ========\n\n");
    printf("1. Agendar consulta\n");
    printf("2. Visualizar todas as consultas agendadas\n");
    printf("3. Buscar paciente\n");
    printf("4. Remover consulta\n");
    printf("5. Salvar consultas em arquivo\n");
    printf("6. Editar dados do paciente\n");
    printf("7. Sair\n");
    printf("====================================================\n");
    printf("Digite a opção desejada:");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("================\n");
            printf("\033[34mAGENDAR CONSULTA\x1b[0m\n");
            printf("================\n");
            raiz = agendarConsulta(raiz);
            break;
        case 2:
            printf("====================\n");
            printf("\033[34mVISUALIZAR CONSULTAS\x1b[0m\n");
            printf("====================\n");
            printf("Consultas Agendadas:\n");
            exibirPacientes(raiz);
            break;
        case 3:
            {
                printf("========================\n");
                printf("\033[34mBUSCAR CONSULTA\x1b[0m\n");
                printf("========================\n");
                char cpf[20];
                printf("Digite o cpf do paciente: ");
                scanf("%s", cpf);
                Paciente* paciente = buscarPaciente(raiz, cpf);
                if (paciente != NULL) {
                    printf("\x1b[38;2;0;255;0m");
                    printf("PACIENTE ENCONTRADO:\n");
                    printf("\x1b[0m");
                    printf("Nome: %s\n", paciente->nome);
                    printf("CPF: %s\n", paciente->cpf);
                    printf("Data: %s\n", paciente->data);
                    printf("Data da Consulta: %s\n", paciente->dataConsulta);
                    printf("Consulta às: %sh\n", paciente->hora);
                    printf("Telefone: %s\n", paciente->telefone);
                } else {
                    printf("\x1b[38;2;255;0;0m");
                    printf("PACIENTE NÃO ENCONTRADO.\n");
                    printf("\x1b[0m");
                }
            }
            break;
        case 4:
            printf("================\n");
            printf("\033[34mREMOVER CONSULTA\x1b[0m\n");
            printf("================\n");
            raiz = removerConsulta(raiz);
            break;
        case 5:
            {
                printf("=======================\n");
                printf("\033[34mSALVAR DADOS NO ARQUIVO\x1b[0m\n");
                printf("=======================\n");
                FILE* arquivo = fopen("consultas.txt", "w");
                if (arquivo != NULL) {
                    salvarArvoreEmArquivo(arquivo, raiz);
                    printf("\x1b[38;2;0;255;0m");
                    printf("DADOS SALVOS EM ARQUIVO COM SUCESSO!\n");
                    printf("\x1b[0m");
                    fclose(arquivo);
                } else {
                    printf("Erro ao abrir o arquivo.\n");
                }
            
                break;
            }
        case 6:
        {   
            printf("===============\n");
            printf("\033[34mATUALIZAR DADOS\x1b[0m\n");
            printf("===============\n");
            // valida o cpf do paciente
            char cpf[20];
            printf("Digite o cpf do paciente: ");
            scanf("%s", cpf);
            Paciente* paciente = buscarPaciente(raiz, cpf);

            // alterar dados do paciente
            if (paciente != NULL) {
                printf("\x1b[38;2;0;255;0m");
                printf("PACIENTE ENCONTRADO:\n");
                printf("\x1b[0m");
                printf("Nome: %s\n", paciente->nome);
                printf("CPF: %s\n", paciente->cpf);
                printf("Data da Consulta: %s\n", paciente->dataConsulta);
                printf("Telefone: %s\n", paciente->telefone);
                printf("Data: %s\n", paciente->data);
                printf("Consulta às: %s\n", paciente->hora);
                printf("Novo NOME do paciente: ");
                scanf("%s", paciente->nome);
                printf("Novo CPF do paciente: ");
                scanf("%s", paciente->cpf);
                printf("Nova DATA DE NASCIMENTO do paciente: ");
                scanf("%s", paciente->data);
                printf("Nova DATA para consulta: ");
                scanf("%s", paciente->dataConsulta);
                printf("Nova HORA DA CONSULTA: ");
                scanf("%s", paciente->hora);
                printf("Novo TELEFONE do paciente: ");
                scanf("%s", paciente->telefone);
                printf("\x1b[38;2;0;255;0m");
                printf("DADOS ALTERADOS COM SUCESSO!\n\n");
                printf("\x1b[0m");
            } else {
                printf("\x1b[38;2;255;0;0m");
                printf("PACIENTE NÃO ENCONTRADO.\n");        
                printf("\x1b[0m");

            }
            break;
        }

        case 7:
        {
            printf("SAINDO...\n");
            liberarArvore(raiz);
            break;
        }
        default:
        {    
            printf("\x1b[38;2;255;0;0m");
            printf("Opção inválida. Tente novamente.\n");
            printf("\x1b[0m");
        }
    }
} while (opcao != 7);

return 0;
}