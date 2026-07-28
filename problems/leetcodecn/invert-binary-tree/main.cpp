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
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;
        swap(root->left, root->right);
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};

TreeNode* build(istream& in, int n) {
    if (!n) return nullptr;
    vector<TreeNode*> nodes(n);
    for (int i = 0, v; i < n; i++) { in >> v; if (v != -1) nodes[i] = new TreeNode(v); }
    for (int i = 0; i < n; i++) {
        if (!nodes[i]) continue;
        int l = 2 * i + 1, r = 2 * i + 2;
        if (l < n) nodes[i]->left = nodes[l];
        if (r < n) nodes[i]->right = nodes[r];
    }
    return nodes[0];
}

void print(TreeNode* r) {
    if (!r) return;
    queue<TreeNode*> q; q.push(r);
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        if (!p) { cout << "-1 "; continue; }
        cout << p->val << ' ';
        q.push(p->left); q.push(p->right);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    auto root = build(cin, n);
    root = Solution().invertTree(root);
    print(root);
    return 0;
}
