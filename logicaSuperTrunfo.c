#include <stdio.h>

typedef struct {
    char estado;
    char codigo[4];
    char nome[50];
    unsigned long int populacao;
    float area;
    float pib;
    int pontos_turisticos;

    float densidade;
    float pib_per_capita;
} Carta;

void calculaAtributos(Carta *c) {
    c->densidade = c->populacao / c->area;
    c->pib_per_capita = c->pib / c->populacao;
}

void imprimeCarta(const Carta *c) {
    printf("Carta: %s (%c) - %s\n", c->codigo, c->estado, c->nome);
    printf("Populacao: %lu\n", c->populacao);
    printf("Area: %.2f\n", c->area);
    printf("PIB: %.2f\n", c->pib);
    printf("Pontos Turisticos: %d\n", c->pontos_turisticos);
    printf("Densidade Populacional: %.2f\n", c->densidade);
    printf("PIB per Capita: %.2f\n", c->pib_per_capita);
    printf("\n");
}

int comparaAtributo(const Carta *c1, const Carta *c2, int atributo) {
    float v1, v2;

    switch (atributo) {
        case 1:
            return (c1->populacao > c2->populacao) ? 1 : (c1->populacao < c2->populacao) ? 0 : -1;
        case 2: 
            return (c1->area > c2->area) ? 1 : (c1->area < c2->area) ? 0 : -1;
        case 3: 
            return (c1->pib > c2->pib) ? 1 : (c1->pib < c2->pib) ? 0 : -1;
        case 4: 
            return (c1->pontos_turisticos > c2->pontos_turisticos) ? 1 : (c1->pontos_turisticos < c2->pontos_turisticos) ? 0 : -1;
        case 5: 
            return (c1->densidade < c2->densidade) ? 1 : (c1->densidade > c2->densidade) ? 0 : -1;
        case 6: 
            return (c1->pib_per_capita > c2->pib_per_capita) ? 1 : (c1->pib_per_capita < c2->pib_per_capita) ? 0 : -1;
        default:
            return -1;
    }
}

const char* nomeAtributo(int atributo) {
    switch (atributo) {
        case 1: return "Populacao";
        case 2: return "Area";
        case 3: return "PIB";
        case 4: return "Pontos Turisticos";
        case 5: return "Densidade Populacional";
        case 6: return "PIB per Capita";
        default: return "Desconhecido";
    }
}

float calculaSuperPoder(const Carta *c) {
    return (float)c->populacao + c->area + c->pib + (float)c->pontos_turisticos + (1.0f / c->densidade) + c->pib_per_capita;
}

int comparaDoisAtributos(const Carta *c1, const Carta *c2, int attr1, int attr2) {
    int r1 = comparaAtributo(c1, c2, attr1);
    int r2 = comparaAtributo(c1, c2, attr2);

    if (r1 == -1 && r2 == -1) return -1;
    if (r1 == r2) return r1;
    if (r1 == -1) return r2;
    if (r2 == -1) return r1;


    float sp1 = calculaSuperPoder(c1);
    float sp2 = calculaSuperPoder(c2);
    if (sp1 > sp2) return 1;
    else if (sp2 > sp1) return 0;
    else return -1;
}

int main() {
    Carta carta1, carta2;
    int attr1, attr2;
    
    printf("Cadastro da Carta 1:\n");
    printf("Estado (letra): ");
    scanf(" %c", &carta1.estado);
    printf("Codigo (ex: A01): ");
    scanf("%s", carta1.codigo);
    printf("Nome da cidade: ");
    scanf(" %[^\n]", carta1.nome);
    printf("Populacao: ");
    scanf("%lu", &carta1.populacao);
    printf("Area: ");
    scanf("%f", &carta1.area);
    printf("PIB: ");
    scanf("%f", &carta1.pib);
    printf("Numero de pontos turisticos: ");
    scanf("%d", &carta1.pontos_turisticos);

    printf("\nCadastro da Carta 2:\n");
    printf("Estado (letra): ");
    scanf(" %c", &carta2.estado);
    printf("Codigo (ex: A01): ");
    scanf("%s", carta2.codigo);
    printf("Nome da cidade: ");
    scanf(" %[^\n]", carta2.nome);
    printf("Populacao: ");
    scanf("%lu", &carta2.populacao);
    printf("Area: ");
    scanf("%f", &carta2.area);
    printf("PIB: ");
    scanf("%f", &carta2.pib);
    printf("Numero de pontos turisticos: ");
    scanf("%d", &carta2.pontos_turisticos);

    calculaAtributos(&carta1);
    calculaAtributos(&carta2);

    printf("\n=== Dados das Cartas ===\n");
    imprimeCarta(&carta1);
    imprimeCarta(&carta2);

    printf("Escolha o primeiro atributo para comparar:\n");
    printf("1 - Populacao\n2 - Area\n3 - PIB\n4 - Pontos Turisticos\n5 - Densidade Populacional\n6 - PIB per Capita\n");
    scanf("%d", &attr1);

    printf("Escolha o segundo atributo para comparar:\n");
    scanf("%d", &attr2);

    if (attr1 < 1 || attr1 > 6 || attr2 < 1 || attr2 > 6) {
        printf("Atributo(s) invalido(s). Finalizando.\n");
        return 1;
    }
    if (attr1 == attr2) {
        printf("Atributos devem ser diferentes. Finalizando.\n");
        return 1;
    }

    int resultado = comparaDoisAtributos(&carta1, &carta2, attr1, attr2);

    printf("\nResultado da comparacao entre as cartas usando os atributos \"%s\" e \"%s\":\n", nomeAtributo(attr1), nomeAtributo(attr2));

    if (resultado == 1)
        printf("Carta 1 (%s) venceu!\n", carta1.codigo);
    else if (resultado == 0)
        printf("Carta 2 (%s) venceu!\n", carta2.codigo);
    else
        printf("Empate!\n");

    return 0;
}
