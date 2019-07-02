#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> CountingElements_Vector(vector<int>& data);
map<int, int> CountingElements_Map(vector<int>& data);

int main()
{
    vector<int> data = { 1, 1, 2, 3, 3, 4, 5, 5 };

    printf("[Counting Elements] - Vector\n");
    {
        vector<int> result = CountingElements_Vector(data);

        for (size_t i = 0; i < result.size(); i++)
        {
            if (result[i] > 0)
            {
                printf("[%d] %d\n", i, result[i]);
            }
        }
    }

    printf("\n\n");

    printf("[Counting Elements] - Map\n");
    {
        map<int, int> result = CountingElements_Map(data);

        for (auto element : result)
        {
            printf("[%d] %d\n", element.first, element.second);
        }
    }

    return 0;
}

vector<int> CountingElements_Vector(vector<int>& data)
{
    // data�� ����(-)�� ���ԵǸ� vector�� ������ Ȯ���ؾ� ��
    // data�� ũ��(size)�� �ʹ� ũ�� vector �Ҵ��� �����

    vector<int> result;

    auto max = *std::max_element(data.begin(), data.end());

    result.assign(max + 1, 0);

    // N : data.size()
    // M : m(data�� ���� �� �ִ�)

    // Time Complexity : O(N + M)
    // Space Complexity : O(M)
    for (int element : data)
    {
        result[element]++;
    }

    return result;
}

map<int, int> CountingElements_Map(vector<int>& data)
{
    // ����(-) �� ���� �Ҵ翡 ���� ������ ������,
    // data�� Map���� ����� �ð� ���⵵�� ���� ŭ

    map<int, int> result;

    // Time Complexity : O(NlogN)
    // Space Complexity : O(N)
    for (int element : data)
    {
        result[element]++;
    }

    return result;
}
