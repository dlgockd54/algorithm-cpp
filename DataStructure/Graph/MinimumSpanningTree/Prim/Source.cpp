#include <cstdio>
#include <vector>
#include <queue>

#define INFINITY 0x7FFFFFFF

using namespace std;

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
void Dijkstra_GreedyAlgorithm(int V, int E, int source, vector<vector<int>>& input); // O(N^2)
void Dijkstra_PriorityQueue(int V, int E, int source, vector<vector<int>>& input); // O(M + NlogN)

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

    printf("[Prim] - Greedy Algorithm\n");
    {
        Dijkstra_GreedyAlgorithm(countV, countE, source, input);
    }

    printf("\n");

    printf("[Prim] - Priority Queue\n");
    {
        Dijkstra_PriorityQueue(countV, countE, source, input);
    }

    return 0;
}

void Dijkstra_GreedyAlgorithm(int V, int E, int source, vector<vector<int>>& input)
{
    vector<vector<int>> adjMaxtrix;
    vector<int64_t> distance;
    vector<int> parentVertex;
    vector<bool> isVisited;

    int sourceIdx = source - 1; // 0�� �ƴ� 1�� �������� ������ ��� -1�� ����

    adjMaxtrix.resize(V, vector<int>(V, INFINITY));
    distance.resize(V, INFINITY);
    parentVertex.resize(V, -1);
    isVisited.resize(V, false);

    // Graph �ʱ�ȭ
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (i == j)
            {
                // ���� ������ Weight�� 0
                adjMaxtrix[i][j] = 0;
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
        //adjMaxtrix[u][v] = w;

        // ������ �׷��� <u, v>, <v, u> = w
        adjMaxtrix[u][v] = w;
        adjMaxtrix[v][u] = w;
    }

    // Dijkstra
    distance[sourceIdx] = 0;

    for (int i = 0; i < V; i++)
    {
        int u = -1;
        int64_t minDist = INFINITY;

        for (int v = 0; v < V; v++)
        {
            // �湮���� ���� ���� �߿� �ִ� �Ÿ�(������ �湮�� ����)
            if (!isVisited[v] && minDist >= distance[v])
            {
                minDist = distance[v];
                u = v;
            }
        }

        if (u >= 0)
        {
            // ������ �湮�� ����(Vertex)
            isVisited[u] = true;

            // �ִ� �Ÿ��� �ش��ϴ� ������ ����ġ�� �θ� ������ ����
            for (int v = 0; v < V; v++)
            {
                // Minumum
                if (!isVisited[v] && distance[v] > adjMaxtrix[u][v])
                {
                    distance[v] = adjMaxtrix[u][v];
                    parentVertex[v] = u;
                }
            }
        }
    }

    // Minimum Spanning Tree ���
    for (int i = 0; i < V; i++)
    {
        int vertex = parentVertex[i];

        if (vertex >= 0)
        {
            // 0�� �ƴ� 1�� �������� ������ ��� 1�� ����
            int u = vertex + 1;
            int v = i + 1;
            int w = adjMaxtrix[i][vertex];

            printf("%d -> %d : ", u, v);

            if (w != INFINITY)
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

void Dijkstra_PriorityQueue(int V, int E, int source, vector<vector<int>>& input)
{
    typedef pair<int64_t, int> Dijkstra;

    // ������������ �Ÿ��� �����Ͽ� �ִ� �Ÿ��� �������� ã�� (greater<Dijkstra>)
    priority_queue<Dijkstra, vector<Dijkstra>, greater<Dijkstra>> queue;

    vector<vector<pair<int, int>>> adjList(V);
    vector<int64_t> distance(V, INFINITY);

    vector<int> parentVertex(V, -1);
    vector<bool> isVisited(V, false);

    int sourceIdx = source - 1; // 0�� �ƴ� 1�� �������� ������ ��� -1�� ����

    // �׷��� ����
    for (int i = 0; i < E; i++)
    {
        int u = input[i][0] - 1;
        int v = input[i][1] - 1;
        int w = input[i][2];

        // ���� �׷��� (u, v) = w
        //adjList[u].push_back(make_pair(v, w));

        // ������ �׷��� <u, v>, <v, u> = w
        adjList[u].push_back(make_pair(v, w));
        adjList[v].push_back(make_pair(u, w));
    }

    // Dijkstra
    distance[sourceIdx] = 0;

    queue.push(make_pair(0, sourceIdx));

    while (!queue.empty())
    {
        int64_t w = queue.top().first;
        int u = queue.top().second;

        queue.pop();

        isVisited[u] = true;

        // ���� ����(vertex)���� ª�� ��ΰ� ���� ���� Ȯ��
        if (distance[u] >= w)
        {
            for (int v = 0; v < adjList[u].size(); v++)
            {
                int vertex = adjList[u][v].first;
                int64_t weight = w + adjList[u][v].second;

                // �ִ� ��ΰ� ������, �������� ����ġ�� �������� �Ÿ� ����(�켱���� ť�� Push)
                if (!isVisited[vertex] && distance[vertex] > weight)
                {
                    distance[vertex] = weight;
                    parentVertex[vertex] = u;

                    queue.push(make_pair(weight, vertex));
                }
            }
        }
    }

    // Minimum Spanning Tree ���
    for (int i = 0; i < V; i++)
    {
        int vertex = parentVertex[i];

        if (vertex >= 0)
        {
            auto iterator = find_if(adjList[i].begin(), adjList[i].end(), Compare(vertex));

            // 0�� �ƴ� 1�� �������� ������ ��� 1�� ����
            int u = vertex + 1;
            int v = i + 1;

            printf("%d -> %d : ", u, v);

            if (iterator != adjList[i].end())
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
