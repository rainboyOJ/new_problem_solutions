#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (!root || root == p || root == q)
            return root;
        auto l = lowestCommonAncestor(root->left, p, q);
        auto r = lowestCommonAncestor(root->right, p, q);
        if (l && r)
            return root;
        return l ? l : r;
    }
};

TreeNode *build(istream &in, int n) {
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
    int n, pv, qv;
    cin >> n >> pv >> qv;
    auto r = build(cin, n);
    // find p, q nodes by value
    TreeNode *p = nullptr, *q = nullptr;
    queue<TreeNode *> bfs;
    bfs.push(r);
    while (!bfs.empty()) {
        auto cur = bfs.front();
        bfs.pop();
        if (!cur)
            continue;
        if (cur->val == pv)
            p = cur;
        if (cur->val == qv)
            q = cur;
        bfs.push(cur->left);
        bfs.push(cur->right);
    }
    cout << Solution().lowestCommonAncestor(r, p, q)->val << '\n';
    return 0;
}
