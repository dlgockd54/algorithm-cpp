#include <cstdio>
#include <cmath>

void ModularAddition(int A, int B, int M);
void ModularSubtraction(int A, int B, int M);
void ModularMultiple(int A, int B, int M);
void ModularDivide(int A, int B, int M);
void ModularSquare(int A, int B, int M);

int main()
{
    int A = 18;
    int B = 5;
    int M = 7;

    printf("[������ ������ ����]\n");
    ModularAddition(A, B, M);
    printf("\n");

    printf("[������ ������ ����]\n");
    ModularSubtraction(A, B, M);
    printf("\n");

    printf("[������ ������ ����]\n");
    ModularMultiple(A, B, M);
    printf("\n");

    printf("[�������� ������ ����]\n");
    //ModularOfDivide(A, B, M);
    printf("ERROR\n\n");

    printf("[������ ������ ����]\n");
    ModularSquare(A, B, M);

    return 0;
}

void ModularAddition(int A, int B, int M)
{
    int result[2] = { 0 };

    result[0] = (A + B) % M;
    result[1] = ((A % M) + (B % M)) % M;

    printf("(%d + %d) %% %d = %d\n", A, B, M, result[0]);
    printf("((%d %% %d) + (%d %% %d)) %% %d = %d\n", A, M, B, M, M, result[1]);
}

void ModularSubtraction(int A, int B, int M)
{
    int result[3] = { 0 };

    result[0] = (A - B) % M;
    result[1] = ((A % M) - (B % M)) % M;
    result[2] = ((A % M) - (B % M) + M) % M;

    printf("(%d - %d) %% %d = %d\n", A, B, M, result[0]);
    printf("((%d %% %d) - (%d %% %d)) %% %d = %d\n", A, M, B, M, M, result[1]);
    printf("((%d %% %d) - (%d %% %d) + %d) %% %d = %d\n", A, M, B, M, M, M, result[2]);
}

void ModularMultiple(int A, int B, int M)
{
    int result[2] = { 0 };

    result[0] = (A * B) % M;
    result[1] = ((A % M) * (B % M)) % M;

    printf("(%d * %d) %% %d = %d\n", A, B, M, result[0]);
    printf("((%d %% %d) * (%d %% %d)) %% %d = %d\n", A, M, B, M, M, result[1]);
}

void ModularDivide(int A, int B, int M)
{
    int result[2] = { 0 };

    result[0] = (A / B) % M;
    result[1] = ((A % M) / (B % M)) % M;

    printf("(%d / %d) %% %d = %d\n", A, B, M, result[0]);
    printf("((%d %% %d) / (%d %% %d)) %% %d = %d\n", A, M, B, M, M, result[1]);
}

void ModularSquare(int A, int B, int M)
{
    int result[2] = { 0 };

    result[0] = (int)pow((double)A, (double)B) % M;
    result[1] = (int)pow((double)(A % M), (double)B) % M;

    printf("(%d ^ %d) %% %d = %d\n", A, B, M, result[0]);
    printf("((%d %% %d) ^ %d) %% %d = %d\n", A, M, B, M, result[1]);
}
