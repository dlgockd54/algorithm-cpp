#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

void BinarySearch(vector<int>& data, int search);

int main()
{
    //vector<int> data = { 1, 2, 3, 4, 5 };
    vector<int> data = { 1, 5, 7, 15, 20, 21 };
    int search = 17; // ã������ ��

    // �ʿ信 ���� ����(Sort)
    std::sort(data.begin(), data.end());

    BinarySearch(data, search);

    return 0;
}

void BinarySearch(vector<int>& data, int search)
{
    int left = 0;
    int right = data.size() - 1;
    int middle = 0;

    do
    {
        middle = (left + right) / 2;

        if (data[middle] > search)
        {
            right = middle - 1;
        }
        else if (data[middle] < search)
        {
            left = middle + 1;
        }
        else // data[middle] == search
        {
            break;
        }
    } while (left <= right);

    if (left > right)
    {
        int leftDiff = search - data[right];
        int rightDiff = data[left] - search;

        printf("data�� %d�� �������� ����\n", search);
        printf("-> data[%d](%d)�� data[%d](%d) ���̿� ����\n", right, data[right], left, data[left]);

        if (leftDiff < rightDiff)
        {
            printf("-> data[%d](%d)�� �� ������ ��ġ\n", right, data[right]);
        }
        else if (leftDiff > rightDiff)
        {
            printf("-> data[%d](%d)�� �� ������ ��ġ\n", left, data[left]);
        }
        else
        {
            printf("-> ��Ȯ�� �߰��� ��ġ\n");
        }
    }
    else
    {
        printf("%d�� data[%d]�� ����\n", search, middle);
    }
}