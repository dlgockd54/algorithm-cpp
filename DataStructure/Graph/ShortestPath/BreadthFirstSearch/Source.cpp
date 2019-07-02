#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

struct AdjListGraph
{
    int Infinity = std::numeric_limits<int>::max();

    vector<vector<int>> AdjList; // <weight>
    vector<bool> IsVisited;

    size_t Size; // Vertex ����
    bool IsDirected; // ���� �׷��� ����

    AdjListGraph(size_t size, bool isDirected)
    {
        AdjList.assign(size, vector<int>());
        IsVisited.assign(size, false);

        Size = size;
        IsDirected = isDirected;
    }

    void AddEdge(int u, int v)
    {
        if (IsDirected)
        {
            // ���� �׷���
            // (u, v) w
            AdjList[u].push_back(v);
        }
        else
        {
            // ������ �׷���
            // <u, v>, <v, u> w
            AdjList[u].push_back(v);
            AdjList[v].push_back(u);
        }
    }
};

// [BFS : Breadth-First Search]
// ���� ����ġ�� ���ٰ� ����
vector<int64_t> BFS_Queue(AdjListGraph& graph, int source); // O(N)

int main()
{
    int V = 0; // Vertex ����
    int E = 0; // Edge ����
    int source = 0; // ���� Vertex ��ȣ

    // [input.txt]
    scanf("%d %d", &V, &E);
    scanf("%d", &source);

    vector<vector<int>> input(E, vector<int>(2, 0));

    for (int i = 0; i < E; i++)
    {
        // u, v
        scanf("%d %d", &input[i][0], &input[i][1]);
    }

    printf("\n");

    printf("[BFS : Breadth-First Search]\n");
    {
        AdjListGraph graph(V, false);

        // Graph ���� ����
        for (int i = 0; i < E; i++)
        {
            int u = input[i][0];
            int v = input[i][1];

            graph.AddEdge(u, v);
        }

        // Dijkstra Algorithm
        auto distance = BFS_Queue(graph, source);

        // Shortest Path ���
        for (int i = 0; i < V; i++)
        {
            int destination = i; // 0�� �ƴ� 1�� �������� ������ ��� 1�� ����

            printf("%d -> %d : ", source, destination);

            if (distance[i] != graph.Infinity)
            {
                printf("%lld\n", distance[i]);
            }
            else
            {
                printf("INFINITY\n");
            }
        }
    }

    return 0;
}

vector<int64_t> BFS_Queue(AdjListGraph& graph, int source)
{
    vector<int64_t> distance(graph.Size, graph.Infinity);

    queue<int> queue;
    int u = source;

    // [Source Vetex]
    {
        distance[u] = 0;

        graph.IsVisited[u] = true;
        queue.push(u);
    }

    while (!queue.empty())
    {
        u = queue.front();
        queue.pop();

        for (auto v : graph.AdjList[u])
        {
            // <u, v>           
            if (!graph.IsVisited[v])
            {
                distance[v] = distance[u] + 1;

                graph.IsVisited[v] = true;
                queue.push(v);
            }
        }
    }

    return distance;
}
