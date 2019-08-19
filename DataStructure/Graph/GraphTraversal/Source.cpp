#include <cstdio>
#include <stack>
#include <vector>
#include <queue>

using namespace std;

struct Graph
{
    vector<vector<int>> AdjList;
    vector<bool> IsVisited;

    size_t Size; // Vertex ����

    Graph(size_t size)
    {
        AdjList.assign(size, vector<int>());
        IsVisited.assign(size, false);

        Size = size;

        // [IsVisited]
        // White : �湮�� ���� ���� ���
        // Gray : �� ���̶� �湮�� ���
        // Black : �湮�� ������ ���
    }

    void AddEdge(int u, int v)
    {
        // ���� �׷���
        // G = (u, v)
        AdjList[u].push_back(v);
    }

    void ResetIsVisited()
    {
        std::fill(IsVisited.begin(), IsVisited.end(), false);
    }
};

void DFS_Recursion(Graph& graph, int source); // Recursion
void DFS_Stack(Graph& graph, int source); // Stack
void DFS_Stack2(Graph& graph, int source); // Stack
void BFS_Queue(Graph& graph, int source); // Queue

int main()
{
    int vertex = 8;
    Graph graph(vertex);

    // Case 1
    //graph.AddEdge(0, 2);
    //graph.AddEdge(0, 1);
    //graph.AddEdge(1, 4);
    //graph.AddEdge(1, 3);
    //graph.AddEdge(1, 0);
    //graph.AddEdge(2, 6);
    //graph.AddEdge(2, 5);
    //graph.AddEdge(2, 0);
    //graph.AddEdge(3, 7);
    //graph.AddEdge(3, 1);
    //graph.AddEdge(4, 7);
    //graph.AddEdge(4, 1);
    //graph.AddEdge(5, 7);
    //graph.AddEdge(5, 2);
    //graph.AddEdge(6, 7);
    //graph.AddEdge(6, 2);
    //graph.AddEdge(7, 6);
    //graph.AddEdge(7, 5);
    //graph.AddEdge(7, 4);
    //graph.AddEdge(7, 3);

    // Case 2
    graph.AddEdge(0, 1);
    graph.AddEdge(1, 0);
    graph.AddEdge(1, 2);
    graph.AddEdge(2, 1);
    graph.AddEdge(3, 1);
    graph.AddEdge(1, 3);
    graph.AddEdge(3, 5);
    graph.AddEdge(5, 3);
    graph.AddEdge(3, 6);
    graph.AddEdge(6, 3);
    graph.AddEdge(3, 4);
    graph.AddEdge(4, 3);
    graph.AddEdge(7, 5);
    graph.AddEdge(5, 7);

    //for (int i = 0; i < graph.size; i++)
    //{
    //    std::reverse(graph.adjList[i].begin(), graph.adjList[i].end());
    //}

    printf("[���� �켱 Ž��(DFS)] - Recursion\n");
    {
        graph.ResetIsVisited();
        DFS_Recursion(graph, 0);
    }

    printf("\n\n");

    printf("[���� �켱 Ž��(DFS)] - Stack\n");
    {
        graph.ResetIsVisited();
        DFS_Stack(graph, 0);
    }

    printf("\n\n");

    printf("[���� �켱 Ž��(DFS)] - Stack2\n");
    {
        graph.ResetIsVisited();
        DFS_Stack2(graph, 0);
    }

    printf("\n\n");

    printf("[�ʺ� �켱 Ž��(BFS)] - Queue\n");
    {
        graph.ResetIsVisited();
        BFS_Queue(graph, 0);
    }

    printf("\n");

    return 0;
}

void DFS_Recursion(Graph& graph, int source)
{
    int u = source;

    // [Source Vetex]
    {
        graph.IsVisited[u] = true; // Gray(1)

        printf("%d ", u);
    }

    // <u, v>
    for (auto v : graph.AdjList[u])
    {
        if (!graph.IsVisited[v]) // White(0)
        {
            DFS_Recursion(graph, v);
        }
    }

    //graph.IsVisited[v] = true; // Black(2)
}

void DFS_Stack(Graph& graph, int source)
{
    stack<int> stack;
    int u = source;

    // [Source Vetex]
    {
        stack.push(u);
    }

    while (!stack.empty())
    {
        bool isNextVisited = false;

        u = stack.top();

        if (!graph.IsVisited[u]) // White(0)
        {
            graph.IsVisited[u] = true; // Gray(1)
            printf("%d ", u);
        }

        // <u, v>
        for (auto v : graph.AdjList[u])
        {
            if (!graph.IsVisited[v]) // White(0)
            {
                stack.push(v);

                isNextVisited = true;
                break;
            }
        }

        if (!isNextVisited)
        {
            stack.pop();

            //graph.IsVisited[v] = true; // Black(2)
        }
    }
}

void DFS_Stack2(Graph& graph, int source)
{
    stack<int> stack;
    int u = source;

    // [Source Vetex]
    {
        stack.push(u);
    }

    while (!stack.empty())
    {
        u = stack.top();
        stack.pop();

        if (!graph.IsVisited[u])
        {
            graph.IsVisited[u] = true;
            printf("%d ", u);

            // <u, v>
            for (auto v : graph.AdjList[u])
            {
                if (!graph.IsVisited[v])
                {
                    stack.push(v);
                }
            }
        }
    }
}

void BFS_Queue(Graph& graph, int source)
{
    queue<int> queue;
    int u = source;

    // [Source Vetex]
    {
        printf("%d ", u);

        graph.IsVisited[u] = true; // Gray(1)
        queue.push(u);
    }

    while (!queue.empty())
    {
        u = queue.front();
        queue.pop();

        // <u, v>
        for (auto v : graph.AdjList[u])
        {
            if (!graph.IsVisited[v]) // White(0)
            {
                printf("%d ", v);

                graph.IsVisited[v] = true; // Gray(1)
                queue.push(v);
            }
        }

        //graph.IsVisited[v] = true; // Black(2)
    }
}
