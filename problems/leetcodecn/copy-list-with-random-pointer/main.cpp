/**
 * Author by Rainboy
 */
// main.cpp：哈希表映射，两遍遍历。
#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int val;
    Node *next;
    Node *random;

    Node(int _val) : val(_val), next(nullptr), random(nullptr) {}
};

class Solution {
public:
    Node *copyRandomList(Node *head) {
        if (!head)
            return nullptr;
        unordered_map<Node *, Node *> m;
        for (auto p = head; p; p = p->next)
            m[p] = new Node(p->val);
        for (auto p = head; p; p = p->next) {
            m[p]->next = m[p->next];
            m[p]->random = m[p->random];
        }
        return m[head];
    }
};

Node *build(istream &in, int n) {
    if (!n)
        return nullptr;
    vector<Node *> nodes(n);
    for (int i = 0, v; i < n; i++) {
        in >> v;
        nodes[i] = new Node(v);
    }
    for (int i = 0; i < n - 1; i++)
        nodes[i]->next = nodes[i + 1];
    return nodes[0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    auto head = build(cin, n);
    auto copied = Solution().copyRandomList(head);
    for (auto p = copied; p; p = p->next)
        cout << p->val << ' ';
    return 0;
}
