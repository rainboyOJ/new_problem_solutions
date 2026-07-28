/**
 * Author by Rainboy
 */
// brute.cpp：数组存值后双指针。
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        vector<int> v;
        for (auto p = head; p; p = p->next) v.push_back(p->val);
        for (int i = 0, j = (int)v.size() - 1; i < j; i++, j--)
            if (v[i] != v[j]) return false;
        return true;
    }
};

ListNode* build(istream& in, int n) {
    if (!n) return nullptr;
    auto head = new ListNode(0), cur = head;
    for (int i = 0, v; i < n; i++) { in >> v; cur->next = new ListNode(v); cur = cur->next; }
    return head->next;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    auto head = build(cin, n);
    cout << Solution().isPalindrome(head) << '\n';
    return 0;
}
