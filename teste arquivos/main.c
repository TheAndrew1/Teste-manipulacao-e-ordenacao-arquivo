#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define num 3

void Organizar(FILE *arquivo, char nome_ref[], int *pontos_ref, int j)
{
    int pontos, i;
    char nome[4];
    int pos_i = ftell(arquivo);
    
    fseek(arquivo, 0, 0);
    for (i=0; i<j; i++)
    {
	fread(nome, sizeof(nome), 1, arquivo);
        fread(&pontos, sizeof(int), 1, arquivo);
        if(*pontos_ref >= pontos)
        {
        	fseek(arquivo, -(sizeof(int) + sizeof(nome)), 1);
        	fwrite(nome_ref, sizeof(nome), 1, arquivo);
        	fwrite(pontos_ref, sizeof(int), 1, arquivo);
        	*pontos_ref = pontos;
        	strcpy(nome_ref, nome);
		}
    }
    
    fseek(arquivo, pos_i - ftell(arquivo), 1);
}


int main()
{
    FILE *arquivo;
    int pontos, i;
    char nome[4];

    arquivo = fopen("teste", "w+b");
    if (arquivo == NULL)
    {
        printf ("Erro");
        return 0;
    }

    for (i=0; i<num; i++) //Escrever no arquivo
    {
    	printf("Digite o nome: ");
        fgets(nome, 4, stdin); //Pega nome
        fflush(stdin);
        printf("Digite a pontuacao: ");
        scanf("%d", &pontos); //Pega pontuação
        getchar();
        
        if(i != 0)
        	Organizar(arquivo, nome, &pontos, i);
    	
    	fwrite(nome, sizeof(nome), 1, arquivo); //Escreve nome
        fwrite(&pontos, sizeof(int), 1, arquivo); //Escreve pontos
    }
    system("cls");
    fclose(arquivo);

    arquivo = fopen("teste", "rb");
    for (i=0; i<num; i++) //Ler do arquivo
    {
        fread(nome, sizeof(nome), 1, arquivo);
        fread(&pontos, sizeof(int), 1, arquivo);
        printf("Nome: %s\t Pontuação: %d\n", nome, pontos);
    }
    fclose(arquivo);
    
    printf("Insira o nome: ");
    fgets(nome, 4, stdin); 
    fflush(stdin);
    printf("Insira pontuação: ");
    scanf("%d", &pontos);
    getchar();
    printf("\n\n");
    
	arquivo = fopen("teste", "r+b");
	Organizar(arquivo, nome, &pontos, num);
    
    for (i=0; i<num; i++) //Ler do arquivo
    {
        fread(nome, sizeof(nome), 1, arquivo);
        fread(&pontos, sizeof(int), 1, arquivo);
        printf("%do\t Nome: %s\t Pontuacao: %d\n", i+1, nome, pontos);
    }
    fclose(arquivo);
	
    return 0;
}
