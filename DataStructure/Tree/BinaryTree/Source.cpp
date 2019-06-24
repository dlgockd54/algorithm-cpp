#include <cstdio>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

struct Node
{
    int data;

    Node* left;
    Node* right;
};

struct NodeEx
{
    int data;

    int depth;      // ����� ����(�θ� ����� ��) [Root: 0]
    int level;      // ����� ����(Depth + 1) [Root: 1]

    int size;       // ����� ũ��((leftSize + rightSize) + 1)
    int leftSize;   // ���� �ڽ� ����� ũ��(����)
    int rightSize;  // ������ �ڽ� ����� ũ��(����)

    int column;         // ����� �� ��ȣ (Inorder Traversal)
    int perfectHeight;  // ��ȭ(Perfect) ���� Ʈ���� ���� �� �ִ� �ִ� ����

    NodeEx* parent;     // �θ� ���(nullptr: Root Node)

    NodeEx* left;     // ���� �ڽ� ���
    NodeEx* right;    // ������ �ڽ� ���

    // ��� N�� �θ� ��� : N / 2
    // ��� N�� ���� �ڽ� ��� : 2 * N
    // ��� N�� ������ �ڽ� ��� : (2 * N) + 1
    // ���� L���� ���� �� �ִ� �ִ� ��� ���� : pow(2, L - 1)
    // ����� ũ�Ⱑ N�� ���� ���� Ʈ���� ���� : log2(N + 1);
};

Node* CreateNode(int data, Node* left, Node* right);
void FreeNodes(vector<Node*>& tree);

NodeEx* CreateNodeEx(Node* node);
void FreeNodeEx(NodeEx* root);

NodeEx* InitializeTree_Recursion(Node* root, int depth, int& column);
NodeEx* InitializeTreeEx_Iteration(Node* root);

int UpdateTree_Recursion(NodeEx* root, NodeEx* parent, int depth, int& column);
void UpdateTree_Iteration(NodeEx* root);

Node* FindRootNode(vector<Node*>& raw); // ��Ʈ ��� ã��
NodeEx* FindNodeEx(NodeEx* root, int data); // ��� ã��

int GetHeightOfNode_recursion(NodeEx* node); // ����� ����(�ִ� ����)
int GetHeightOfNode_iteration(NodeEx* node); // ����� ����(�ִ� ����)
int GetSizeOfNode_recursion(NodeEx* node); // ����� ũ��(�ڱ� �ڽ� �� ��� �ڼ� ����� ��)
int GetSizeOfNode_iteration(NodeEx* node); // ����� ũ��(�ڱ� �ڽ� �� ��� �ڼ� ����� ��)

bool IsInternalNode(NodeEx* node); // ���� ��� Ȯ��
bool IsTerminalNode(NodeEx* node); // �ܸ� ��� Ȯ��
bool IsSiblingNode(NodeEx* node1, NodeEx* node2); // ���� ��� Ȯ��

// �ּ� ���� ����(LCA, Least Common Ancestor) ã��
NodeEx* FindLcaLode_Recursion(NodeEx* node, pair<NodeEx*, NodeEx*> child);
NodeEx* FindLcaNode_Iteration(int size, pair<NodeEx*, NodeEx*> child);

int main()
{
    vector<Node*> tree;

    int size = 0;

    // [input.txt]
    scanf("%d", &size);

    // ��尡 0�� ���� �����ϴ� ��� N + 1
    // ����� ��ȣ�� �������� ������ std::map<>�� ���
    tree.assign(size + 1, nullptr);

    for (int i = 0; i < size; i++)
    {
        int parent = 0;
        int left = 0;
        int right = 0;

        scanf("%d %d %d", &parent, &left, &right);

        if (tree[parent] == nullptr)
        {
            tree[parent] = CreateNode(parent, nullptr, nullptr);
        }

        if (left >= 0)
        {
            tree[left] = CreateNode(left, nullptr, nullptr);
            tree[parent]->left = tree[left];
        }

        if (right >= 0)
        {
            tree[right] = CreateNode(right, nullptr, nullptr);
            tree[parent]->right = tree[right];
        }
    }

    Node* root = FindRootNode(tree);

    //int column1 = 0;
    //int column2 = 0;

    //NodeEx* rootEx = InitializeTree_Recursion(root, 0, column1);
    NodeEx* rootEx = InitializeTreeEx_Iteration(root);

    //UpdateTree_Recursion(rootEx, nullptr, 0, column2);
    //UpdateTree_Iteration(rootEx);

    //int heightOfNode = GetHeightOfNode_Recursion(rootEx);
    int heightOfNode = GetHeightOfNode_iteration(rootEx);

    //int sizeOfNode = GetSizeOfNode_Recursion(rootEx);
    int sizeOfNode = GetSizeOfNode_iteration(rootEx);

    bool isTnternal = IsInternalNode(rootEx);
    bool isTerminal = IsTerminalNode(rootEx);
    bool isSibling = IsSiblingNode(rootEx->left, rootEx->right);

    // [LCA - �ּ� ���� ����]
    {
        NodeEx* node12 = FindNodeEx(rootEx, 12);
        NodeEx* node17 = FindNodeEx(rootEx, 17);
        // lca->data : 3

        //NodeEx* lca = FindLcaLode_Recursion(rootEx, make_pair(node12, node17));
        NodeEx* lca = FindLcaNode_Iteration(size, make_pair(node12, node17));
    }

    FreeNodeEx(rootEx);
    FreeNodes(tree);

    return 0;
}

Node* CreateNode(int data, Node* left, Node* right)
{
    Node* node = reinterpret_cast<Node*>(malloc(sizeof(Node)));

    node->data = data;

    node->left = left;
    node->right = right;

    return node;
}

void FreeNodes(vector<Node*>& tree)
{
    for (auto node : tree)
    {
        free(node);
    }

    tree.clear();
}

NodeEx* CreateNodeEx(Node* node)
{
    NodeEx* nodeEx = nullptr;

    if (node != nullptr)
    {
        nodeEx = reinterpret_cast<NodeEx*>(malloc(sizeof(NodeEx)));

        nodeEx->data = node->data;
        nodeEx->depth = 0;
        nodeEx->level = 0;

        nodeEx->size = 0;
        nodeEx->leftSize = 0;
        nodeEx->rightSize = 0;

        nodeEx->column = 0;
        nodeEx->perfectHeight = 0;

        nodeEx->parent = nullptr;

        nodeEx->left = nullptr;
        nodeEx->right = nullptr;
    }

    return nodeEx;
}

void FreeNodeEx(NodeEx* root)
{
    stack<NodeEx*> stack;

    stack.push(root);

    while (!stack.empty())
    {
        NodeEx* node = stack.top();
        stack.pop();

        if (node->right != nullptr)
        {
            stack.push(node->right);
        }
        if (node->left != nullptr)
        {
            stack.push(node->left);
        }

        free(node);
        node = nullptr;
    }
}

NodeEx* InitializeTree_Recursion(Node* root, int depth, int& column)
{
    NodeEx* rootEx = nullptr;

    if (root != nullptr)
    {
        int leftHeight = 0;
        int rightHeight = 0;

        // [Preorder Traversal]
        NodeEx* nodeEx = CreateNodeEx(root);

        // [Preorder Traversal]
        nodeEx->depth = depth; // Depth
        nodeEx->level = depth + 1; // Level

        // Left Subtree
        NodeEx* left = InitializeTree_Recursion(root->left, depth, column);
        if (left != nullptr)
        {
            nodeEx->left = left; // Left Node
            nodeEx->leftSize = left->size; // Left Size

            left->parent = nodeEx; // Parent Node
            leftHeight = left->perfectHeight;
        }

        // [Inorder Traversal]
        nodeEx->column = column; // Colmun
        column++;

        // Right Subtree
        NodeEx* right = InitializeTree_Recursion(root->right, depth, column);
        if (right != nullptr)
        {
            nodeEx->right = right; // Right Node
            nodeEx->rightSize = right->size; // Right Size

            right->parent = nodeEx; // Parent Node
            rightHeight = right->perfectHeight;
        }

        // [Postorder Traversal]
        nodeEx->size = (nodeEx->leftSize + nodeEx->rightSize) + 1; // Size
        nodeEx->perfectHeight = 1 + std::min(leftHeight, rightHeight); // Perfect Height

        rootEx = nodeEx; // �ڽ� ��� ����
    }

    return rootEx; // Root Node
}

// InitializeTree_Recursion()���� ��ü�� �� ����
int UpdateTree_Recursion(NodeEx* root, NodeEx* parent, int depth, int& column)
{
    int result = 0;

    if (root != nullptr)
    {
        // [Preorder Traversal]
        root->depth = depth; // Depth
        root->level = depth + 1; // Level

        root->parent = parent; // Parent Node

        // Left Subtree
        int leftSize = UpdateTree_Recursion(root->left, root, depth + 1, column);

        // [Inorder Traversal]
        root->column = column;
        column++;

        // Right Subtree
        int rightSize = UpdateTree_Recursion(root->right, root, depth + 1, column);

        // [Postorder Traversal]
        root->leftSize = leftSize;
        root->rightSize = rightSize;
        root->size = (root->leftSize + root->rightSize) + 1;

        result = root->size; // �ڽ� ��� ����
    }

    return result; // Size of Node
}

NodeEx* InitializeTreeEx_Iteration(Node* root)
{
    NodeEx* rootEx = nullptr;

    // [Postorder Traversal]
    // Depth(Level), Size, Parent Node
    {
        stack<Node*> nodeStack;
        stack<NodeEx*> nodeExStack;

        Node* node = root;
        Node* last = nullptr;

        // isLeftNode, ParentNode
        pair<bool, NodeEx*> parent(true, nullptr);

        int depth = 0;

        while (!nodeExStack.empty() || node != nullptr)
        {
            if (node != nullptr)
            {
                NodeEx* nodeEx = CreateNodeEx(node);

                // [Depth/Level]
                {
                    nodeEx->depth = depth; // Depth
                    nodeEx->level = depth + 1; // Level

                    depth++;
                }

                if (parent.second != nullptr)
                {
                    nodeEx->parent = parent.second; // Parent Node

                    if (parent.first) // Left Node
                    {
                        parent.second->left = nodeEx;
                    }
                    else // Right Node
                    {
                        parent.second->right = nodeEx;
                    }
                }

                nodeStack.push(node);
                nodeExStack.push(nodeEx);

                node = node->left;

                parent.first = true;
                parent.second = nodeEx;
            }
            else
            {
                Node* top = nodeStack.top();
                NodeEx* topEx = nodeExStack.top();

                if (top->right != nullptr && last != top->right)
                {
                    node = top->right;

                    parent.first = false;
                    parent.second = topEx;
                }
                else
                {
                    // [Size, Perfect Height, Parent]
                    {
                        NodeEx* left = topEx->left;
                        NodeEx* right = topEx->right;

                        int leftHeight = 0;
                        int rightHeight = 0;

                        if (left != nullptr)
                        {
                            topEx->leftSize = left->size; // Left Size
                            left->parent = topEx; // Parent Node

                            leftHeight = left->perfectHeight; // Left Height
                        }
                        if (right != nullptr)
                        {
                            topEx->rightSize = right->size; // Right Size

                            right->parent = topEx; // Parent Node
                            rightHeight = right->perfectHeight; // Right Height
                        }

                        topEx->size = (topEx->leftSize + topEx->rightSize) + 1; // Size
                        topEx->perfectHeight = 1 + std::min(leftHeight, rightHeight); // Perfect Height

                        depth--; // [Depth/Level]
                    }

                    last = top;
                    rootEx = topEx;

                    nodeStack.pop();
                    nodeExStack.pop();
                }
            }
        }
    }

    // [Inorder Traversal]
    // Column
    {
        stack<NodeEx*> stack;

        NodeEx* node = rootEx;
        int column = 1;

        while (!stack.empty() || node != nullptr)
        {
            if (node != nullptr)
            {
                stack.push(node);

                node = node->left;
            }
            else
            {
                node = stack.top();
                stack.pop();

                // [Column]
                {
                    node->column = column; // Column
                    column++;
                }

                node = node->right;
            }
        }
    }

    return rootEx;
}

// InitializeTree_Iteration()���� ��ü�� �� ����
void UpdateTree_Iteration(NodeEx* root)
{
    // [Postorder Traversal]
    // Depth(Level), Size, Parent Node
    {
        stack<NodeEx*> stack;

        NodeEx* node = root;
        NodeEx* last = nullptr;

        int depth = 0;

        while (!stack.empty() || node != nullptr)
        {
            if (node != nullptr)
            {
                // [Depth/Level]
                {
                    node->depth = depth; // Depth
                    node->level = depth + 1; // Level

                    depth++;
                }

                stack.push(node);

                node = node->left;
            }
            else
            {
                NodeEx* top = stack.top();

                if (top->right != nullptr &&
                    last != top->right)
                {
                    node = top->right;
                }
                else
                {
                    // [Size, Perfect Height, Parent]
                    {
                        NodeEx* left = top->left;
                        NodeEx* right = top->right;

                        int leftHeight = 0;
                        int rightHeight = 0;

                        if (left != nullptr)
                        {
                            top->leftSize = left->size; // Left Size
                            left->parent = top; // Parent Node

                            leftHeight = left->perfectHeight; // Left Height
                        }
                        if (right != nullptr)
                        {
                            top->rightSize = right->size; // Right Size

                            right->parent = top; // Parent Node
                            rightHeight = right->perfectHeight; // Right Height
                        }

                        top->size = (top->leftSize + top->rightSize) + 1; // Size
                        top->perfectHeight = 1 + std::min(leftHeight, rightHeight); // Perfect Height

                        depth--; // [Depth/Level]
                    }

                    last = top;
                    stack.pop();
                }
            }
        }
    }

    // [Inorder Traversal]
    // Column
    {
        stack<NodeEx*> stack;

        NodeEx* node = root;
        int column = 1;

        while (!stack.empty() || node != nullptr)
        {
            if (node != nullptr)
            {
                stack.push(node);

                node = node->left;
            }
            else
            {
                node = stack.top();
                stack.pop();

                // [Column]
                {
                    node->column = column; // Column
                    column++;
                }

                node = node->right;
            }
        }
    }
}

Node* FindRootNode(vector<Node*>& node)
{
    Node* result = nullptr;

    vector<bool> isRootNode(node.size(), true);

    // ��尡 0�� ���� �����ϴ� ���
    isRootNode[0] = false;

    for (size_t i = 0; i < node.size(); i++)
    {
        if (node[i] != nullptr)
        {
            Node* left = node[i]->left;
            Node* right = node[i]->right;

            if (left != nullptr)
            {
                isRootNode[left->data] = false;
            }

            if (right != nullptr)
            {
                isRootNode[right->data] = false;
            }
        }
    }

    for (size_t i = 0; i < isRootNode.size(); i++)
    {
        if (isRootNode[i])
        {
            result = node[i];
            break;
        }
    }

    return result;
}

NodeEx* FindNodeEx(NodeEx* root, int data)
{
    NodeEx* result = nullptr;

    stack<NodeEx*> stack;

    stack.push(root);

    // [Preorder Traversal]
    while (!stack.empty())
    {
        NodeEx* node = stack.top();
        stack.pop();

        if (node->data == data)
        {
            result = node;
            break;
        }

        if (node->right != nullptr)
        {
            stack.push(node->right);
        }
        if (node->left != nullptr)
        {
            stack.push(node->left);
        }
    }

    return result;
}

int GetHeightOfNode_recursion(NodeEx* node)
{
    int height = -1;

    if (node != nullptr)
    {
        int leftHeight = GetHeightOfNode_recursion(node->left);
        int rightHeight = GetHeightOfNode_recursion(node->right);

        // ����� ���� : �� ���� Ʈ���� ���� �� �ִ� + 1
        height = std::max(leftHeight, rightHeight) + 1;
    }

    return height;
}

int GetHeightOfNode_iteration(NodeEx* node)
{
    int height = -1;

    queue<NodeEx*> queue;

    queue.push(node);

    while (!queue.empty())
    {
        int size = queue.size();

        while (size > 0)
        {
            NodeEx* node = queue.front();
            queue.pop();

            if (node->left != nullptr)
            {
                queue.push(node->left);
            }

            if (node->right != nullptr)
            {
                queue.push(node->right);
            }

            size--;
        }

        height++;
    }

    return height;
}

int GetSizeOfNode_recursion(NodeEx* node)
{
    int size = 0;

    if (node != nullptr)
    {
        int leftSize = GetSizeOfNode_recursion(node->left);
        int rightSize = GetSizeOfNode_recursion(node->right);

        size = (leftSize + rightSize) + 1;
    }

    return size;
}

int GetSizeOfNode_iteration(NodeEx* node)
{
    int size = 0;

    queue<NodeEx*> queue;

    queue.push(node);
    size++;

    // [Preorder Traversal]
    while (!queue.empty())
    {
        NodeEx* node = queue.front();
        queue.pop();

        if (node->left != nullptr)
        {
            queue.push(node->left);
            size++;
        }

        if (node->right != nullptr)
        {
            queue.push(node->right);
            size++;
        }
    }

    return size;
}

bool IsSiblingNode(NodeEx* node1, NodeEx* node2)
{
    bool result = false;

    if (node1 != nullptr && node2 != nullptr)
    {
        if (node1->level == node2->level)
        {
            result = true;
        }
    }

    return result;
}

bool IsInternalNode(NodeEx* node)
{
    bool result = false;

    if (node != nullptr)
    {
        if (node->left != nullptr || node->right != nullptr)
        {
            result = true;
        }
    }

    return result;
}

bool IsTerminalNode(NodeEx* node)
{
    bool result = false;

    if (node != nullptr)
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            result = true;
        }
    }

    return result;
}

NodeEx* FindLcaLode_Recursion(NodeEx* node, pair<NodeEx*, NodeEx*> child)
{
    NodeEx* result = nullptr;

    if (node != nullptr)
    {
        if (node == child.first || node == child.second)
        {
            result = node;
        }
        else
        {
            NodeEx* left = FindLcaLode_Recursion(node->left, child);
            NodeEx* right = FindLcaLode_Recursion(node->right, child);

            if (left != nullptr && right != nullptr)
            {
                result = node;
            }
            else if (left != nullptr)
            {
                result = left;
            }
            else // (right != nullptr)
            {
                result = right;
            }
        }
    }

    return result;
}

NodeEx* FindLcaNode_Iteration(int size, pair<NodeEx*, NodeEx*> child)
{
    NodeEx* result = nullptr;

    NodeEx* child1 = child.first;
    NodeEx* child2 = child.second;

    vector<bool> isVisited(size + 1, false);
    // node->isVisited �Ǵ� Map<int(node->data), bool(isVisited)>�� ����

    while (child1 != nullptr)
    {
        isVisited[child1->data] = true;
        child1 = child1->parent;
    }

    while (child2 != nullptr)
    {
        if (isVisited[child2->data])
        {
            result = child2;
            break;
        }

        child2 = child2->parent;
    }

    return result;
}
