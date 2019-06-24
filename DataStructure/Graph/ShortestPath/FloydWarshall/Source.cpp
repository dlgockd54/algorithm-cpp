#include <cstdio>
#include <vector>

using namespace std;

struct AdjMaxtrixGraph
{
    int Infinity = std::numeric_limits<int>::max();

    vector<vector<int>> AdjMaxtrix;
    vector<bool> IsVisited;

    size_t Size;
    bool IsDirected; // ���� �׷��� ����

    AdjMaxtrixGraph(size_t size, bool isDirected)
    {
        AdjMaxtrix.assign(size, vector<int>(size, Infinity));
        IsVisited.assign(size, false);

        Size = size;
        IsDirected = isDirected;

        // Graph �ʱ�ȭ
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (i == j)
                {
                    // ���� ������ Weight�� 0
                    AdjMaxtrix[i][j] = 0;
                }
            }
        }
    }

    void AddEdge(int u, int v, int w)
    {
        if (IsDirected)
        {
            // ���� �׷���
            // (u, v) = w
            AdjMaxtrix[u][v] = w;
        }
        else
        {
            // ������ �׷���
            // <u, v>, <v, u> = w
            AdjMaxtrix[u][v] = w;
            AdjMaxtrix[v][u] = w;
        }
    }
};

// [Floyd-Warshall �˰���]
// - ���� ����Ŭ ���ٰ� ����
vector<vector<int64_t>> FloydWarshall_GreedyAlgorithm(AdjMaxtrixGraph& graph, int source); // O(N^3)

int main()
{
    int V = 0; // Vertex ����
    int E = 0; // Edge ����
    int S = 0; // ���� Vertex ��ȣ

    // [input.txt]
    scanf("%d %d", &V, &E);
    scanf("%d", &S);

    vector<vector<int>> input(E, vector<int>(3, 0));

    for (int i = 0; i < E; i++)
    {
        scanf("%d %d %d", &input[i][0], &input[i][1], &input[i][2]);
    }

    printf("[Floyd-Warshall] - Greedy Algorithm\n");
    {
        AdjMaxtrixGraph graph(V, true);

        // Graph ���� ����
        for (int i = 0; i < E; i++)
        {
            int u = input[i][0] - 1;
            int v = input[i][1] - 1;
            int w = input[i][2];

            graph.AddEdge(u, v, w);
        }

        // 0�� �ƴ� 1�� �������� ������ ��� -1�� ����
        int source = S - 1;

        // Dijkstra Algorithm
        auto distance = FloydWarshall_GreedyAlgorithm(graph, source);

        // Shortest Path ���
        for (int i = 0; i < V; i++)
        {
            // 0�� �ƴ� 1�� �������� ������ ��� 1�� ����
            int destination = i + 1;

            printf("%d -> %d : ", S, destination);

            if (distance[source][i] != graph.Infinity)
            {
                printf("%lld\n", distance[source][i]);
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
                if (distance[i][j] == graph.Infinity)
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

    return 0;
}

vector<vector<int64_t>> FloydWarshall_GreedyAlgorithm(AdjMaxtrixGraph& graph, int source)
{
    vector<vector<int64_t>> distance(graph.Size, vector<int64_t>(graph.Size, graph.Infinity));

    // Distance �ʱ�ȭ
    for (int i = 0; i < graph.Size; i++)
    {
        for (int j = 0; j < graph.Size; j++)
        {
            distance[i][j] = graph.AdjMaxtrix[i][j];
        }
    }

    // Floyd-Warshall
    for (int k = 0; k < graph.Size; k++)
    {
        for (int i = 0; i < graph.Size; i++)
        {
            for (int j = 0; j < graph.Size; j++)
            {
                int64_t sum = distance[i][k] + distance[k][j];

                // Minumum Distance
                if (distance[i][j] > sum)
                {
                    distance[i][j] = sum;
                }
            }
        }
    }

    return distance;
}
