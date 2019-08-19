#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

void InfiniteCoin(); // ������ ���� ����
void FiniteCoin(); // ������ ���� ����(���� �Է�)

// [���� ��ȯ] ������ ����(����)
int InfiniteCoins_NumberOfCases(vector<int>& coins, int k);
int InfiniteCoins_NumberOfCoins(vector<int>& coins, int k);
int InfiniteCoins_NumberOfCoins_Greedy(vector<int>& coins, int k);

// [���� ��ȯ] ������ ����(����)
int FiniteCoin_NumberOfCases(vector<pair<int, int>>& coins, int k);
int FiniteCoin_NumberOfCoins(vector<pair<int, int>>& coins, int k);

int main()
{
    // ������ ������ ������ ���
    InfiniteCoin();

    // ������ ������ �־��� ���
    //FiniteCoin();

    return 0;
}

void InfiniteCoin()
{
    int n = 0; // ���� ������ ����
    int k = 0; // ������ �ݾ�
    vector<int> coins; // ���� ����

    // [input1.txt]
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++)
    {
        int coin = 0;

        scanf("%d", &coin);

        coins.push_back(coin);
    }

    //int cases = InfiniteCoins_NumberOfCoins_Iteration(coins, k);
    int numOfCases = InfiniteCoins_NumberOfCases(coins, k);
    int numOfCoins = InfiniteCoins_NumberOfCoins(coins, k);

    printf("[���� ��ȯ] - ������ ���� ����\n");
    printf("����� ��(�ּ�) : %d\n", numOfCases);
    printf("������ ��(�ּ�) : %d\n", numOfCoins);
}

void FiniteCoin()
{
    int n = 0; // ���� ������ ����
    int k = 0; // ������ �ݾ�
    vector<pair<int, int>> coins; // ���� ����, ����

    // [input2.txt]
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++)
    {
        pair<int, int> coin;

        scanf("%d %d", &coin.first, &coin.second);

        coins.push_back(coin);
    }

    int numOfCases = FiniteCoin_NumberOfCases(coins, k);
    int numOfCoins = FiniteCoin_NumberOfCoins(coins, k);

    printf("[���� ��ȯ] - ������ ���� ����\n");
    printf("����� ��(�ּ�) : %d\n", numOfCases);
    printf("������ ��(�ּ�) : %d\n", numOfCoins);
}

// https://www.acmicpc.net/problem/2293
// http://comganet.github.io/dp/2016/06/03/dp-1002
int InfiniteCoins_NumberOfCases(vector<int>& coins, int k)
{
    int result = 0;

    vector<int> dp(k + 1, 0); // 0���� �ʱ�ȭ

    dp[0] = 1;

    for (int element : coins) // element = conins[i]
    {
        // ������ �ݾ��� j�� ��� (coins[i] ~ k)
        for (int j = element; j <= k; j++)
        {
            int total = j - element;

            // dp[j] : coins[i]�� ���� ���ϴ� ��� (������ ����� ��)
            // dp[total] : coins[i]�� �����ϴ� ��� (���ο� ����� ��)
            dp[j] += dp[total];
        }
    }

    result = dp[k];

    return result;
}

// https://www.acmicpc.net/problem/2294
int InfiniteCoins_NumberOfCoins(vector<int>& coins, int k)
{
    int result = -1; // ����� ���� ������ -1

    // �ִ�(k + 1)���� �ʱ�ȭ
    // ����� �� �̹Ƿ� �ּڰ��� ���ؾ� ��
    vector<int> dp(k + 1, k + 1);

    dp[0] = 0;

    for (int element : coins) // element = conins[i]
    {
        // ������ �ݾ��� j�� ��� (coins[i] ~ k)
        for (int j = element; j <= k; j++)
        {
            int total = j - element;

            // dp[j] : coins[i]�� ���� ���ϴ� ��� (������ ����)
            // dp[total] + 1 : coins[i]�� �����ϴ� ��� (���ο� ����)
            dp[j] = std::min(dp[j], dp[total] + 1);
        }
    }

    if (dp[k] < k + 1)
    {
        result = dp[k];
    }

    return result;
}

// https://www.acmicpc.net/problem/11047
// �� ������ ������ ������, �ּڰ��� �ƴ� �� ���� (DP ���)
int InfiniteCoins_NumberOfCoins_Greedy(vector<int>& coins, int k)
{
    int result = 0;

    const int coinSize = coins.size();

    sort(coins.begin(), coins.end()); // ��������

    // k�� ���� �ſ� ū ��� (ex. 100,000,000)
    for (int i = coinSize - 1; i >= 0; i--)
    {
        if (k != 0)
        {
            result += k / coins[i];
            k %= coins[i];
        }
        else
        {
            break;
        }
    }

    return result;
}

// https://www.acmicpc.net/problem/2624
// http://comganet.github.io/dp/2016/06/03/dp-1005
int FiniteCoin_NumberOfCases(vector<pair<int, int>>& coins, int k)
{
    int result = 0;

    vector<int> dp(k + 1, 0); // 0���� �ʱ�ȭ

    dp[0] = 1;

    for (auto element : coins) // element = conins[i]
    {
        int coin = element.first;
        int number = element.second;

        // ������ �ݾ��� j�� ��� (coins[i] ~ k)
        for (int j = k; j >= 1; j--)
        {
            // ������ ������ n���� ��� (1 ~ number)
            for (int n = 1; n <= number; n++)
            {
                int total = j - (coin * n);

                if (total >= 0)
                {
                    // dp[j] : coins[i]�� ���� ���ϴ� ��� (������ ����� ��)
                    // dp[total] : coins[i]�� �����ϴ� ��� (���ο� ����� ��)
                    dp[j] += total;
                }
            }
        }
    }

    result = dp[k];

    return result;
}

int FiniteCoin_NumberOfCoins(vector<pair<int, int>>& coins, int k)
{
    int result = -1; // ����� ���� ������ -1

    vector<int> dp(k + 1, k + 1); // �ִ�(k + 1)���� �ʱ�ȭ

    dp[0] = 0;

    for (auto element : coins) // element = conins[i]
    {
        int coin = element.first;
        int count = element.second;

        // ������ �ݾ��� j�� ��� (coins[i] ~ 1)
        for (int j = k; j >= 1; j--)
        {
            // ������ ������ n���� ��� (1 ~ number)
            for (int n = 1; n <= count; n++)
            {
                int total = j - (coin * n);

                if (total >= 0)
                {
                    // dp[j] : coins[i]�� ���� ���ϴ� ��� (������ ����)
                    // dp[total] + 1 : coins[i]�� �����ϴ� ��� (���ο� ����)
                    dp[j] = std::min(dp[j], dp[total] + 1);
                }
            }
        }
    }

    if (dp[k] <= k)
    {
        result = dp[k];
    }
    else
    {
        // ����� ���� ������ -1
    }

    return result;
}
