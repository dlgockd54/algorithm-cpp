#include <cstdio>
#include <vector>

#define INFINITY 0x7FFFFFFF

using namespace std;

// [Floyd-Warshall �˰���]
// - ���� ����Ŭ ���ٰ� ����
void FloydWarshall_GreedyAlgorithm(int V, int E, int source, vector<vector<int>>& input); // O(N^3)

int main()
{
    int countV = 0;
    int countE = 0;
    int source = 0;
    vector<vector<int>> input;

    // [input.txt]
    scanf("%d %d", &countV, &countE);
    scanf("%d", &source);

    input.resize(countE, vector<int>(3, 0));

    for (int i = 0; i < countE; i++)
    {
        scanf("%d %d %d", &input[i][0], &input[i][1], &input[i][2]);
    }

    printf("[Floyd-Warshall] - Greedy Algorithm\n");
    {
        FloydWarshall_GreedyAlgorithm(countV, countE, source, input);
    }

    return 0;
}

void FloydWarshall_GreedyAlgorithm(int V, int E, int source, vector<vector<int>>& input)
{
    vector<vector<int>> adjMaxtrix;
    vector<vector<int64_t>> distance;

    int sourceIdx = source - 1; // 0�� �ƴ� 1�� �������� ������ ��� -1�� ����

    adjMaxtrix.resize(V, vector<int>(V, INFINITY));
    distance.resize(V, vector<int64_t>(V, INFINITY));

    // Graph �ʱ�ȭ
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (i == j)
            {
                // ���� ������ Weight�� 0
                adjMaxtrix[i][j] = 0;
                distance[i][j] = 0;
            }
        }
    }

    // Graph ����
    for (int i = 0; i < E; i++)
    {
        int u = input[i][0] - 1;
        int v = input[i][1] - 1;
        int w = input[i][2];

        // ���� �׷��� (u, v) = w
        adjMaxtrix[u][v] = w;

        // ������ �׷��� <u, v>, <v, u> = w
        //adjMaxtrix[u][v] = w;
        //adjMaxtrix[v][u] = w;
    }

    // Distance �ʱ�ȭ
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            distance[i][j] = adjMaxtrix[i][j];
        }
    }

    // Floyd-Warshall
    for (int k = 0; k < V; k++)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                int64_t sum = distance[i][k] + distance[k][j];

                // Minimum
                if (distance[i][j] > sum)
                {
                    distance[i][j] = sum;
                }
            }
        }
    }

    // Shortest Path ���
    for (int i = 0; i < V; i++)
    {
        // 0�� �ƴ� 1�� �������� ������ ��� 1�� ����
        int end = i + 1;

        printf("%d -> %d : ", source, end);

        if (distance[sourceIdx][i] != INFINITY)
        {
            printf("%lld\n", distance[sourceIdx][i]);
        }
        else
        {
            printf("INFINITY\n");
        }
    }

    printf("\n");

    // �ִ� �Ÿ� ���(���� ���)
    printf("�� ��ü �ִ� �Ÿ� (���� ���)\n");

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (distance[i][j] == INFINITY)
            {
                printf("%3s\n", "��");
            }
            else
            {
                printf("%3lld\n", distance[i][j]);
            }
        }
    }
}
