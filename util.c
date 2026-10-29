#include <string.h>
#include "util.h"

int inteiroPositivo(int numero)
{
    return numero > 0;
}

int numeroRealPositivo(float numero)
{
    return numero > 0;
}

int quantidadeValida(int quantidade)
{
    return quantidade >= 0;
}

int textoPreenchido(const char texto[])
{
    return strlen(texto) > 0;
}
