#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 29  // Tamanho da tabela hash (número primo para melhor distribuição)

// Estrutura que representa cada entrada da tabela hash
typedef struct {
    char key;      // A letra (chave)
    char *morse;   // O código Morse correspondente
} HashEntry;

// Função hash "mais complexa": multiplica o valor ASCII da chave por 7 (um número primo)
// e aplica o módulo TABLE_SIZE para obter um índice.
int hash(char key) {
    return (key * 7) % TABLE_SIZE;
}

// Função para inserir uma letra e seu código Morse na tabela hash utilizando linear probing
void insert(HashEntry table[], char key, char *morse) {
    int index = hash(key);
    // Se a posição já estiver ocupada, procura a próxima disponível (linear probing)
    while (table[index].key != '\0') {
        index = (index + 1) % TABLE_SIZE;
    }
    table[index].key = key;
    table[index].morse = morse;
}

// Função para buscar o código Morse correspondente a uma letra na tabela hash
char* lookup(HashEntry table[], char key) {
    int index = hash(key);
    int startIndex = index;  // Para detectar se demos uma volta completa na tabela
    while (table[index].key != '\0') {
        if (table[index].key == key) {
            return table[index].morse;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == startIndex) {  // Se percorremos toda a tabela, encerra a busca
            break;
        }
    }
    return NULL;  // Retorna NULL se a chave não for encontrada
}

int main() {
    // Inicializa a tabela hash com entradas vazias
    HashEntry hashTable[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i].key = '\0';
        hashTable[i].morse = NULL;
    }

    // Vetor com os códigos Morse para as letras de 'a' a 'z'
    char *morseCodes[26] = {
        ".-",   // a
        "-...", // b
        "-.-.", // c
        "-..",  // d
        ".",    // e
        "..-.",// f
        "--.", // g
        "....",// h
        "..",  // i
        ".---",// j
        "-.-", // k
        ".-..",// l
        "--",  // m
        "-.",  // n
        "---", // o
        ".--.",// p
        "--.-",// q
        ".-.", // r
        "...", // s
        "-",   // t
        "..-", // u
        "...-",// v
        ".--", // w
        "-..-",// x
        "-.--",// y
        "--.." // z
    };

    // Vetor com as letras correspondentes
    char letters[27] = "abcdefghijklmnopqrstuvwxyz";

    // Insere cada letra com seu código Morse na tabela hash
    for (int i = 0; i < 26; i++) {
        insert(hashTable, letters[i], morseCodes[i]);
    }

    char palavra[100];
    printf("Digite uma palavra (somente letras minúsculas): ");
    scanf("%s", palavra);

    printf("Código Morse: ");
    // Para cada caractere da palavra, busca seu código Morse na tabela hash e imprime
    for (int i = 0; i < strlen(palavra); i++) {
        char ch = palavra[i];
        char *codigo = lookup(hashTable, ch);
        if (codigo != NULL) {
            printf("%s ", codigo);
        }
    }
    printf("\n");

    return 0;
}
