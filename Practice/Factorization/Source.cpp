#include <cstdio>
#include <cmath>
#include <vector>
#include <set>

using namespace std;

// n�� ���� �� �ִ� ���� ���� �Ҽ�(Prime Number)
// �����佺�׳׽��� ü(Sieve Of Eratosthenes) Ȱ��
vector<int> SmallestFactors(int n);

// �μ�����(Factorization) : �Ҽ�(Prime Number)���� ��
multiset<int> Factorization(vector<int>& factors, int n);

int main()
{
    int n = 20;

    vector<int> factors = SmallestFactors(n);

    printf("[Smallest Factors] : %d\n", n);
    {
        for (int element : factors)
        {
            printf("%d ", element);
        }
    }

    printf("\n\n");

    printf("[Factorization] : %d\n", n);
    {
        multiset<int> result = Factorization(factors, n);

        for (int element : result)
        {
            printf("%d ", element);
        }
    }

    return 0;
}

vector<int> SmallestFactors(int n)
{
    vector<int> result(n + 1, 0);

    // Time Complexity : O(Nlog(log(N)))
    // Space Complexity : O(N)
    for (int i = 2; i < std::sqrt(n); i++)
    {
        if (result[i] == 0)
        {
            int j = i * i;

            while (j <= n)
            {
                if (result[j] == 0)
                {
                    // i : Smallest Prime Number
                    result[j] = i;
                }
                
                j += i;
            }
        }
    }

    // result(index >= 2)�� ���Ұ� 0�̸� �Ҽ�(Prime Number)

    return result;
}

multiset<int> Factorization(vector<int>& factors, int n)
{
    // Order : multiset<int>
    // Inorder : vector<int>
    multiset<int> result;

    int number = n;

    // Time Complexity : O(logN)
    // Space Complexity : O(N)
    while (factors[number] > 0)
    {
        result.insert(factors[number]);

        number /= factors[number];
    }

    result.insert(number);

    return result;
}
