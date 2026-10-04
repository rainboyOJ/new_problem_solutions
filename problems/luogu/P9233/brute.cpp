/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:07
 * update_at: 2026-10-03 11:07
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 做法：对每个结点 u，重新完整遍历一次子树 u，统计每种颜色出现几次，
// 再检查所有出现过的颜色点数是否相同。复杂度约为 O(n^2)，只适合小数据。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 200005;

int n;
int col[MAXN];              // col[i]：结点 i 的颜色
int fa[MAXN];               // fa[i]：结点 i 的父亲
vector<int> son_list[MAXN]; // 孩子列表

int bucket[MAXN];            // bucket[c]：本轮统计中颜色 c 的结点个数
int seen[MAXN];              // seen[1..seen_cnt]：本轮出现过的颜色，用来检查和清空桶
int seen_cnt;

ll ans;

// 把 u 及其所有后代的颜色扔进桶，返回这棵子树的结点个数。
int collect(int u) {
    if (bucket[col[u]] == 0) {
        seen_cnt++;
        seen[seen_cnt] = col[u];
    }
    bucket[col[u]]++;

    int total = 1;
    for (int i = 0; i < (int)son_list[u].size(); i++) {
        total += collect(son_list[u][i]);
    }
    return total;
}

// 对每个结点暴力统计它自己的子树。
void dfs_solve(int u) {
    seen_cnt = 0;
    collect(u);

    // 所有出现过的颜色，结点个数必须完全一样。
    bool ok = true;
    int first = bucket[seen[1]];
    for (int i = 2; i <= seen_cnt; i++) {
        if (bucket[seen[i]] != first) {
            ok = false;
            break;
        }
    }
    if (ok) {
        ans++;
    }

    // 还原桶，供后面的结点使用。
    for (int i = 1; i <= seen_cnt; i++) {
        bucket[seen[i]] = 0;
    }

    for (int i = 0; i < (int)son_list[u].size(); i++) {
        dfs_solve(son_list[u][i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> col[i] >> fa[i];
    }
    for (int i = 2; i <= n; i++) {
        son_list[fa[i]].push_back(i);
    }

    dfs_solve(1);
    cout << ans << "\n";

    return 0;
}
