#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int kthSmallest(TreeNode *root, int k) {
        stack<TreeNode *> st;
        auto cur = root;
        while (cur || !st.empty()) {
            while (cur) {
                st.push(cur);
                cur = cur->left;
            }
            cur = st.top();
            st.pop();
            if (--k == 0)
                return cur->val;
            cur = cur->right;
        }
        return -1;
    }
};

TreeNode *build(istream &in, int n) {
    if (!n)
        return nullptr;
    vector<TreeNode *> nodes(n);
    queue<TreeNode *> q;
    for (int i = 0, v; i < n; i++) {
        in >> v;
        if (v != -1)
            nodes[i] = new TreeNode(v);
    }
    TreeNode *root = nodes[0];
    if (root)
        q.push(root);
    int idx = 1;
    while (!q.empty() && idx < n) {
        auto cur = q.front();
        q.pop();
        if (idx < n) {
            cur->left = nodes[idx];
            if (nodes[idx])
                q.push(nodes[idx]);
            idx++;
        }
        if (idx < n) {
            cur->right = nodes[idx];
            if (nodes[idx])
                q.push(nodes[idx]);
            idx++;
        }
    }
    return root;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    auto r = build(cin, n);
    cout << Solution().kthSmallest(r, k) << '\n';
    return 0;
}
