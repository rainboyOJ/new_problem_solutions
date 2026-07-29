#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int pathSum(TreeNode *root, int targetSum) {
        unordered_map<long, int> cnt;
        cnt[0] = 1;
        long ans = 0;
        function<void(TreeNode *, long)> dfs = [&](TreeNode *r, long sum) {
            if (!r)
                return;
            sum += r->val;
            // prefix - target 是能与当前前缀组成目标路径的祖先前缀和。
            ans += cnt[sum - targetSum];
            cnt[sum]++;
            dfs(r->left, sum);
            dfs(r->right, sum);
            // 回溯时移除当前前缀，避免影响其他分支。
            cnt[sum]--;
        };
        dfs(root, 0);
        return ans;
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
    int n, t;
    cin >> n >> t;
    auto r = build(cin, n);
    cout << Solution().pathSum(r, t) << '\n';
    return 0;
}
