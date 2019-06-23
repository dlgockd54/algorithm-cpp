#include <cstdio>

#include "Array.h"
#include "Tree.h"

int main()
{
    FILE* pOutputFile = fopen("output.txt", "wt");

    string result = "";

    // [Array]
    {
        result = ConvertArray();
    }

    // [Tree]
    {
        int nodeNum = 19; // ��� ��ȣ�� �ִ�
        int rootNum = 1; // ��Ʈ ���� ��ȣ

        result = ConvertTree(nodeNum, rootNum);
    }

    fprintf(pOutputFile, "%s\n", result.c_str());

    fclose(pOutputFile);

    return 0;
}
