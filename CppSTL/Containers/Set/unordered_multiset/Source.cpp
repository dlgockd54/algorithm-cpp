#include <iostream>
#include <unordered_set>

using namespace std;

int main()
{
    // http://en.cppreference.com/w/cpp/container/unordered_multiset
    // http://www.cplusplus.com/reference/unordered_set/unordered_set/

    unordered_multiset<int> values; // Unordered Multise
     
    // [Modifiers]
    {
        // clear()
        values.clear();

        // insert(element)
        values.insert(1);
        values.insert(2);
        values.insert(3);

        auto result = values.insert(1); // set
        // result : key(1)�� iterator

        // erase(element)
        values.erase(2);
    }

    // [Capacity]
    {
        // empty()
        bool isEmpty = values.empty();
        cout << "isEmpty : " << isEmpty << '\n';

        // size()
        size_t size = values.size();
        cout << "size : " << size << '\n';
    }

    // [Operations]
    {
        // find(element)
        auto iterator = values.find(1);
        if (iterator != values.end())
        {
            cout << "element : " << *iterator << '\n';
        }

        // count(element)
        auto count = values.count(1);
        cout << "count : " << count << '\n';
    }

    // [Iterators]
    for (auto iter = values.begin(); iter != values.end(); ++iter)
    {
        cout << "value : " << *iter << '\n';
    }

    // [Iterators - Foreach]
    for (auto element : values)
    {
        cout << "value : " << element << "\n";
    }

    return 0;
}
