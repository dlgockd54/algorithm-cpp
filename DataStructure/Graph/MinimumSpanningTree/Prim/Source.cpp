#include <cstdio>
#include <vector>
#include <queue>

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

struct AdjListGraph
{
    int Infinity = std::numeric_limits<int>::max();

    vector<vector<pair<int, int>>> AdjList;
    vector<bool> IsVisited;

    size_t Size;
    bool IsDirected; // ���� �׷��� ����

    AdjListGraph(size_t size, bool isDirected)
    {
        AdjList.assign(size, vector<pair<int, int>>());
        IsVisited.assign(size, false);

        Size = size;
        IsDirected = isDirected;
    }

    void AddEdge(int u, int v, int w)
    {
        if (IsDirected)
        {
            // ���� �׷���
            // (u, v) = w
            AdjList[u].push_back(make_pair(v, w));
        }
        else
        {
            // ������ �׷���
            // <u, v>, <v, u> = w
            AdjList[u].push_back(make_pair(v, w));
            AdjList[v].push_back(make_pair(u, w));
        }
    }
};

struct Compare
{
    int first;

    Compare(int const& first) : first(first) { }

    bool operator() (pair<int, int> const& pair)
    {
        return (pair.first == first);
    }
};

// [Prim �˰���]
// - ���� ����ġ�� ���ٰ� ����
// - Dijkstra �˰���� ����
vector<int> Dijkstra_GreedyAlgorithm(AdjMaxtrixGraph& graph, int source); // O(N^2)
vector<int> Dijkstra_PriorityQueue(AdjListGraph& graph, int source); // O(M + NlogN)

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
        // u, v, w
        scanf("%d %d %d", &input[i][0], &input[i][1], &input[i][2]);
    }

    printf("[Prim] - Greedy Algorithm\n");
    {
        AdjMaxtrixGraph graph(V, false);

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
        auto parentVertex = Dijkstra_GreedyAlgorithm(graph, source);

        // Minimum Spanning Tree ���
        for (int i = 0; i < V; i++)
        {
            int vertex = parentVertex[i];

            if (vertex >= 0)
            {
                // 0�� �ƴ� 1�� �������� ������ ��� 1�� ����
                int u = vertex + 1;
                int v = i + 1;
                int w = graph.AdjMaxtrix[i][vertex];

                printf("%d -> %d : ", u, v);

                if (w != graph.Infinity)
                {
                    printf("%d\n", w);
                }
                else
                {
                    printf("INFINITY\n");
                }
            }
        }
    }

    printf("\n");

    printf("[Prim] - Priority Queue\n");
    {
        AdjListGraph graph(V, false);

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
        auto parentVertex = Dijkstra_PriorityQueue(graph, source);

        // Minimum Spanning Tree ���
        for (int i = 0; i < V; i++)
        {
            int vertex = parentVertex[i];

            if (vertex >= 0)
            {
                auto iterator = std::find_if(graph.AdjList[i].begin(), graph.AdjList[i].end(), Compare(vertex));

                // 0�� �ƴ� 1�� �������� ������ ��� 1�� ����
                int u = vertex + 1;
                int v = i + 1;

                printf("%d -> %d : ", u, v);

                if (iterator != graph.AdjList[i].end())
                {
                    int w = iterator->second;

                    printf("%d\n", w);
                }
                else
                {
                    printf("INFINITY\n");
                }
            }
        }
    }

    return 0;
}

vector<int> Dijkstra_GreedyAlgorithm(AdjMaxtrixGraph& graph, int source)
{
    vector<int64_t> distance(graph.Size, graph.Infinity);
    vector<int> parentVertex(graph.Size, -1);

    distance[source] = 0;

    for (int i = 0; i < graph.Size; i++)
    {
        int u = -1;
        int64_t minDistance = graph.Infinity;

        for (int v = 0; v < graph.Size; v++)
        {
            // �湮���� ���� ���� �߿� �ִ� �Ÿ�(������ �湮�� ����)
            if (!graph.IsVisited[v] && minDistance >= distance[v])
            {
                minDistance = distance[v];
                u = v;
            }
        }

        if (u >= 0)
        {
            // ������ �湮�� ����(Vertex)
            graph.IsVisited[u] = true;

            // �湮�� ������ ����� �������� ����ġ�� �������� �Ÿ� ����
            for (int v = 0; v < graph.Size; v++)
            {
                int64_t sumDistance = distance[u] + graph.AdjMaxtrix[u][v];

                // Minumum Distance
                if (!graph.IsVisited[v] && distance[v] > sumDistance)
                {
                    distance[v] = sumDistance;
                    parentVertex[v] = u;
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

    // ������������ �Ÿ��� �����Ͽ� �ִ� �Ÿ��� �������� ã�� (greater<Dijkstra>)
    typedef pair<int64_t, int> Dijkstra; // <distance, vertex>
    priority_queue<Dijkstra, vector<Dijkstra>, greater<Dijkstra>> queue;

    distance[source] = 0;

    queue.push(make_pair(0, source));

    while (!queue.empty())
    {
        auto top = queue.top();
        queue.pop();

        int64_t w = top.first;
        int u = top.second;

        graph.IsVisited[u] = true;

        // ���� ����(vertex)���� ª�� ��ΰ� ���� ���� Ȯ��
        if (distance[u] >= w)
        {
            for (auto v : graph.AdjList[u])
            {
                int vertex = v.first;
                int64_t weight = w + v.second;

                // �ִ� ��ΰ� ������, �������� ����ġ�� �������� �Ÿ� ����(�켱���� ť�� Push)
                if (!graph.IsVisited[vertex] && distance[vertex] > weight)
                {
                    distance[vertex] = weight;
                    parentVertex[vertex] = u;

                    queue.push(make_pair(weight, vertex));
                }
            }
        }
    }

    return parentVertex;
}
