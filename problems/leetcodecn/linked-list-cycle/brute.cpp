/**
 * Author by Rainboy
 */
// brute.cpp：哈希集合记录已访问节点。
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        unordered_set<ListNode *> s;
        for (auto p = head; p; p = p->next) {
            if (s.count(p))
                return true;
            s.insert(p);
        }
        return false;
    }
};

ListNode *build(istream &in, int n) {
    if (!n)
        return nullptr;
    auto head = new ListNode(0), cur = head;
    for (int i = 0, v; i < n; i++) {
        in >> v;
        cur->next = new ListNode(v);
        cur = cur->next;
    }
    return head->next;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    auto head = build(cin, n);
    cout << Solution().hasCycle(head) << '\n';
    return 0;
}
