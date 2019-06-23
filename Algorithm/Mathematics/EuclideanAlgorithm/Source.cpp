#include <cstdio>
#include <algorithm>

// [��Ŭ���� ȣ����(Euclidean Algorithm)]
int GCD(int n, int m); // GCD(Greatest Common Divisor)
int LCM(int n, int m); // LCM(Least Common Multiple)

int main()
{
    int a = 1071;
    int b = 1029;

    printf("A : %d, B : %d\n", a, b);

    printf("\n");

    printf("[�ִ� �����(GCD)]\n");
    {
        int result = GCD(a, b);

        printf("%d\n", result);
    }

    printf("\n");

    printf("[�ּ� �����(LCM)]\n");
    {
        int result = LCM(a, b);

        printf("%d\n", result);
    }

    return 0;
}

int GCD(int n, int m)
{
    while (m > 0)
    {
        int temp = 0;

        temp = n;
        n = m;
        m = temp % m;
    }

    return n;
}

int LCM(int n, int m)
{
    int result = (n * m) / GCD(n, m);

    return result;
}
