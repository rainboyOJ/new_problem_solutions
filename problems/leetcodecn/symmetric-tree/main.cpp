/**
 * Author by Rainboy
 */
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        function<bool(TreeNode*,TreeNode*)> dfs = [&](TreeNode* a, TreeNode* b) {
            if (!a && !b) return true;
            if (!a || !b) return false;
            return a->val == b->val && dfs(a->left, b->right) && dfs(a->right, b->left);
        };
        return dfs(root->left, root->right);
    }
};

TreeNode* build(istream& in, int n) {
    if (!n) return nullptr;
    vector<TreeNode*> nodes(n);
    for (int i = 0, v; i < n; i++) { in >> v; if (v != -1) nodes[i] = new TreeNode(v); }
    queue<TreeNode*> q; TreeNode* root = nodes[0];
    if (root) q.push(root);
    int idx = 1;
    while (!q.empty() && idx < n) {
        auto cur = q.front(); q.pop();
        if (idx < n) { cur->left = nodes[idx]; if (nodes[idx]) q.push(nodes[idx]); idx++; }
        if (idx < n) { cur->right = nodes[idx]; if (nodes[idx]) q.push(nodes[idx]); idx++; }
    }
    return root;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    auto root = build(cin, n);
    cout << Solution().isSymmetric(root) << '\n';
    return 0;
}
