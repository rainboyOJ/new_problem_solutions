#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode *buildTree(vector<int> &pre, vector<int> &in) {
        unordered_map<int, int> pos;
        for (int i = 0; i < (int)in.size(); i++)
            pos[in[i]] = i;
        int idx = 0;
        // 中序区间 [l, r] 决定子树范围，前序指针依次给出每棵子树的根。
        function<TreeNode *(int, int)> build = [&](int l, int r) -> TreeNode * {
            if (l > r)
                return nullptr;
            int v = pre[idx++];
            int m = pos[v];
            TreeNode *root = new TreeNode(v);
            root->left = build(l, m - 1);
            root->right = build(m + 1, r);
            return root;
        };
        return build(0, in.size() - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> pre(n), in(n);
    for (int &x : pre)
        cin >> x;
    for (int &x : in)
        cin >> x;
    auto r = Solution().buildTree(pre, in);
    // 输出层序验证
    queue<TreeNode *> q;
    q.push(r);
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        if (!cur) {
            cout << "-1 ";
            continue;
        }
        cout << cur->val << ' ';
        q.push(cur->left);
        q.push(cur->right);
    }
    return 0;
}
