/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:21
 * update_at: 2026-10-23 23:21
 */
// brute.cpp：小数据暴力解。
// 通过递归枚举所有合法的二叉树形态（即每次在当前中序区间 [l, r] 中枚举根节点 k），
// 不使用记忆化，直接递归计算每种划分方式的得分并求最大值，同时记录最优根以输出前序遍历。
// 搜索状态数对应卡特兰数 C_n，复杂度随 n 呈指数爆炸，仅适合验证小规模数据（如 n <= 8）。
#include <iostream>
#include <vector>
using namespace std;

int n;
long long a[35];

struct Result {
    long long score;
    vector<int> preorder;
};

// 纯暴力递归搜索，不使用 memo / dp
Result solve(int l, int r) {
    if (l > r) {
        return {1, {}};
    }
    if (l == r) {
        return {a[l], {l}};
    }

    Result best = {-1, {}};
    for (int k = l; k <= r; ++k) {
        Result left_res = solve(l, k - 1);
        Result right_res = solve(k + 1, r);
        long long current_score = left_res.score * right_res.score + a[k];

        if (current_score > best.score) {
            best.score = current_score;
            best.preorder.clear();
            best.preorder.push_back(k);
            best.preorder.insert(best.preorder.end(), left_res.preorder.begin(), left_res.preorder.end());
            best.preorder.insert(best.preorder.end(), right_res.preorder.begin(), right_res.preorder.end());
        }
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    Result ans = solve(1, n);
    cout << ans.score << "\n";
    for (size_t i = 0; i < ans.preorder.size(); ++i) {
        cout << ans.preorder[i] << (i + 1 == ans.preorder.size() ? "" : " ");
    }
    cout << "\n";

    return 0;
}
