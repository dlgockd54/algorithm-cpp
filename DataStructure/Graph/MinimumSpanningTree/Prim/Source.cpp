#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

struct AdjMatrixGraph
{
    int Infinity = std::numeric_limits<int>::max();

    vector<vector<int64_t>> AdjMatrix;
    vector<bool> IsVisited;

    size_t Size; // Vertex ����
    bool IsDirected; // ���� �׷��� ����

    AdjMatrixGraph(size_t size, bool isDirected)
    {
        AdjMatrix.assign(size, vector<int64_t>(size, Infinity));
        IsVisited.assign(size, false);

        Size = size;
        IsDirected = isDirected;

        // Graph �ʱ�ȭ
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++)
            {
                if (i == j)
                {
                    // ���� ������ Weight�� 0
                    AdjMatrix[i][j] = 0;
                }
            }
        }
    }

    void AddEdge(int u, int v, int w)
    {
        if (IsDirected)
        {
            // ���� �׷���
            // (u, v) w
            AdjMatrix[u][v] = w;
        }
        else
        {
            // ������ �׷���
            // <u, v>, <v, u> w
            AdjMatrix[u][v] = w;
            AdjMatrix[v][u] = w;
        }
    }
};

struct AdjListGraph
{
    int Infinity = std::numeric_limits<int>::max();

    vector<vector<pair<int, int64_t>>> AdjList; // <vertex, weight>
    vector<bool> IsVisited;

    size_t Size; // Vertex ����
    bool IsDirected; // ���� �׷��� ����

    AdjListGraph(size_t size, bool isDirected)
    {
        AdjList.assign(size, vector<pair<int, int64_t>>());
        IsVisited.assign(size, false);

        Size = size;
        IsDirected = isDirected;
    }

    void AddEdge(int u, int v, int w)
    {
        if (IsDirected)
        {
            // ���� �׷���
            // (u, v) w
            AdjList[u].push_back(make_pair(v, w));
        }
        else
        {
            // ������ �׷���
            // <u, v>, <v, u> w
            AdjList[u].push_back(make_pair(v, w));
            AdjList[v].push_back(make_pair(u, w));
        }
    }
};

// [Prim �˰���]
// ���� ����ġ�� ���ٰ� ����
// Dijkstra �˰���� ����
vector<int> Dijkstra_GreedyAlgorithm(AdjMatrixGraph& graph, int source); // O(N^2)
vector<int> Dijkstra_PriorityQueue(AdjListGraph& graph, int source); // O(M + NlogN)

int main()
{
    int V = 0; // Vertex ����
    int E = 0; // Edge ����
    int source = 0; // ���� Vertex ��ȣ

    // [input.txt]
    scanf("%d %d", &V, &E);
    scanf("%d", &source);

    vector<vector<int>> input(E, vector<int>(3, 0));

    for (int i = 0; i < E; i++)
    {
        // u, v, w
        scanf("%d %d %d", &input[i][0], &input[i][1], &input[i][2]);
    }

    printf("[Prim] - Greedy Algorithm\n");
    {
        AdjMatrixGraph graph(V, false); // ������ �׷���
        int64_t sumWeight = 0;

        // Graph ���� ����
        for (int i = 0; i < E; i++)
        {
            int u = input[i][0];
            int v = input[i][1];
            int w = input[i][2];

            graph.AddEdge(u, v, w);
        }

        // Dijkstra Algorithm
        auto parentVertex = Dijkstra_GreedyAlgorithm(graph, source);

        // Minimum Spanning Tree ���
        for (int i = 0; i < V; i++)
        {
            int u = parentVertex[i];
            int v = i;

            if (u >= 0)
            {
                int64_t w = graph.AdjMatrix[i][u];

                printf("%d -> %d : ", u, v);

                if (w != graph.Infinity)
                {
                    sumWeight += w;

                    printf("%llu\n", w);
                }
                else
                {
                    printf("INFINITY\n");
                }
            }
        }

        printf("-> Total Weight : %llu\n", sumWeight);
    }

    printf("\n");

    printf("[Prim] - Priority Queue\n");
    {
        AdjListGraph graph(V, false); // ������ �׷���
        int64_t sumWeight = 0;

        // Graph ���� ����
        for (int i = 0; i < E; i++)
        {
            int u = input[i][0];
            int v = input[i][1];
            int w = input[i][2];

            graph.AddEdge(u, v, w);
        }

        // Dijkstra Algorithm
        auto parentVertex = Dijkstra_PriorityQueue(graph, source);

        // Minimum Spanning Tree ���
        for (int i = 0; i < V; i++)
        {
            int u = parentVertex[i];
            int v = i;

            if (u >= 0)
            {
                auto pred = [&u](pair<int, int64_t> const& vertex)
                {
                    return vertex.first == u;
                };
                auto iterator = std::find_if(graph.AdjList[v].begin(), graph.AdjList[v].end(), pred);

                printf("%d -> %d : ", u, v);

                if (iterator != graph.AdjList[v].end())
                {
                    int64_t w = iterator->second;
                    sumWeight += w;

                    printf("%llu\n", w);
                }
                else
                {
                    printf("INFINITY\n");
                }
            }
        }

        printf("-> Total Weight : %llu\n", sumWeight);
    }

    return 0;
}

vector<int> Dijkstra_GreedyAlgorithm(AdjMatrixGraph& graph, int source)
{
    vector<int64_t> distance(graph.Size, graph.Infinity);
    vector<int> parentVertex(graph.Size, -1);

    // [Source Vetex]
    {
        distance[source] = 0;
        parentVertex[source] = -1;
    }

    for (size_t i = 0; i < graph.Size - 1; i++)
    {
        int u = -1;
        int64_t minDistance = graph.Infinity;

        // �湮���� ���� ���� �߿� �ִ� �Ÿ�
        //for (int v 0; v < graph.Size; v++)
        for (int v = graph.Size - 1; v >= 0; v--)
        {
            if (!graph.IsVisited[v] && minDistance >= distance[v])
            {
                minDistance = distance[v];
                u = v; // ������ �湮�� ����
            }
        }

        if (u >= 0)
        {
            graph.IsVisited[u] = true;

            // <u, v>
            for (size_t v = 0; v < graph.Size; v++)
            {
                // graph.AdjMatrix[u][v] > 0 : ���� ����(Weight�� 0)�� �ƴ� ���
                if (graph.AdjMatrix[u][v] > 0 && distance[u] < graph.Infinity)
                {
                    // �湮�� ������ ����� �������� ����ġ�� �������� �Ÿ� ����
                    if (!graph.IsVisited[v] && distance[v] > graph.AdjMatrix[u][v])
                    {
                        distance[v] = graph.AdjMatrix[u][v];
                        parentVertex[v] = u;
                    }
                }
            }
        }
    }

    return parentVertex;
}

vector<int> Dijkstra_PriorityQueue(AdjListGraph& graph, int source)
{
    vector<int64_t> distance(graph.Size, graph.Infinity);
    vector<int> parentVertex(graph.Size, -1);

    // ��������(greater<Dijkstra>)���� �Ÿ��� �����Ͽ� �ִ� �Ÿ��� �������� ã��
    typedef pair<int64_t, int> Dijkstra; // <distance, vertex>
    priority_queue<Dijkstra, vector<Dijkstra>, greater<Dijkstra>> queue;

    // [Source Vetex]
    {
        distance[source] = 0;
        parentVertex[source] = -1;

        queue.push(make_pair(0, source));
    }

    while (!queue.empty())
    {
        auto top = queue.top();
        queue.pop();

        int u = top.second;
        int64_t w = top.first; // distance[u]

        graph.IsVisited[u] = true;

        // <u, v>
        for (auto vertex : graph.AdjList[u])
        {
            int v = vertex.first;
            int64_t weight = vertex.second;

            // �ִ� ��ΰ� ������ �������� ����ġ�� �������� �Ÿ� ����
            if (!graph.IsVisited[v] && distance[v] > weight)
            {
                distance[v] = weight;
                parentVertex[v] = u;

                queue.push(make_pair(distance[v], v));
            }
        }
    }

    return parentVertex;
}
