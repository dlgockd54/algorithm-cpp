#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

// [�賶 ����]
// �賶�� ���� �� �ִ� ������ �ִ��� ������ �ְ�,
// ���� ��ġ�� ���԰� �ִ� ������ �賶�� ���� ��,
// ��ġ�� ���� �ִ밡 �ǵ��� ���� ���� ���
int KnapsackProblem(vector<pair<int, int>> items, int w);

int main()
{
    int n = 0; // ���� ����
    int w = 0; // �賶�� ���� �� �ִ� ������ �ִ�
    vector<pair<int, int>> items; // ���� ����, ��ġ(����)

    // [input.txt]
    scanf("%d %d", &n, &w);

    for (int i = 0; i < n; i++)
    {
        int w = 0; // ���� ����
        int p = 0; // ���� ����

        scanf("%d %d", &w, &p);

        items.push_back(make_pair(w, p));
    }

    int result = KnapsackProblem(items, w);

    printf("%d\n", result);

    return 0;
}

int KnapsackProblem(vector<pair<int, int>> items, int w)
{
    int result = 0;

    // 0���� �ʱ�ȭ
    // �ִ� �����̹Ƿ� �ִ��� ���ؾ� ��
    vector<int> dp(w + 1, 0);

    for (auto element : items) // element = items[i]
    {
        int weight = element.first; // ����
        int value = element.second; // ��ġ

         // ���ѵ� ���԰� j�� ��� (w ~ weight)
        for (int j = w; j >= weight; j--)
        {
            int total = j - weight;

            // dp[j] : items[i]�� ���� ���ϴ� ��� (������ ��ġ)
            // dp[total] + value : items[i]�� �����ϴ� ��� (���ο� ��ġ)
            dp[j] = std::max(dp[j], dp[total] + value);
        }
    }

    result = dp[w];

    return result;
}
