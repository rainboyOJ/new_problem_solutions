/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:54
 * update_at: 2026-10-06 00:54
 */

#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

const int MOD = 1000000;

int n, m, K;
int fixed_row[6]; // 第 K 行的固定颜色，下标 1..m

// 一行的合法状态：用 1/2/3 表示颜色，相邻列不同
vector<vector<int>> rows; // rows[i][c] 第 i 个状态第 c 列的颜色

// compat[i] 表示能与 rows[i] 上下相邻的状态编号列表（逐列颜色都不同）
vector<vector<int>> compat;

// 生成所有合法行状态
void gen_rows(int dep) {
    static int cur[6];
    if (dep > m) {
        vector<int> tmp(m + 1);
        for (int c = 1; c <= m; ++c) tmp[c] = cur[c];
        rows.push_back(tmp);
        return;
    }
    for (int color = 1; color <= 3; ++color) {
        if (dep > 1 && color == cur[dep - 1]) continue; // 与左邻同色则跳过
        cur[dep] = color;
        gen_rows(dep + 1);
    }
}

// 建相容表
void build_compat() {
    int S = rows.size();
    compat.assign(S, vector<int>());
    for (int i = 0; i < S; ++i) {
        for (int j = 0; j < S; ++j) {
            bool ok = true;
            for (int c = 1; c <= m; ++c) {
                if (rows[i][c] == rows[j][c]) {
                    ok = false;
                    break;
                }
            }
            if (ok) compat[i].push_back(j);
        }
    }
}

// 行状态计数向量向下推 steps 行
vector<int> propagate(vector<int> vec, int steps) {
    int S = rows.size();
    for (int step = 0; step < steps; ++step) {
        vector<int> nxt(S, 0);
        for (int j = 0; j < S; ++j) {
            ll sum = 0;
            for (int idx = 0; idx < (int)compat[j].size(); ++idx) {
                sum += vec[compat[j][idx]];
            }
            nxt[j] = (int)(sum % MOD);
        }
        vec.swap(nxt);
    }
    return vec;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> K;
    for (int c = 1; c <= m; ++c) cin >> fixed_row[c];

    gen_rows(1);
    build_compat();

    // 查找固定行对应的状态编号
    int me = -1;
    for (int i = 0; i < (int)rows.size(); ++i) {
        bool same = true;
        for (int c = 1; c <= m; ++c) {
            if (rows[i][c] != fixed_row[c]) {
                same = false;
                break;
            }
        }
        if (same) {
            me = i;
            break;
        }
    }
    if (me == -1) { // 固定行自身相邻同色，不存在合法方案
        cout << 0 << "\n";
        return 0;
    }

    // 上半段：第 1 行任取合法状态，推到第 K-1 行，再要求贴住固定行
    int up = 1;
    if (K > 1) {
        vector<int> vec(rows.size(), 1); // 第一行每个合法状态各 1 种
        vec = propagate(vec, K - 2);     // 推到第 K-1 行
        ll sum = 0;
        for (int idx = 0; idx < (int)compat[me].size(); ++idx) {
            sum += vec[compat[me][idx]];
        }
        up = (int)(sum % MOD);
    }

    // 下半段：从固定行出发推到第 N 行，末行无约束全部求和
    int down = 1;
    if (K < n) {
        vector<int> vec(rows.size(), 0);
        vec[me] = 1; // 固定行状态为 1
        vec = propagate(vec, n - K);
        ll sum = 0;
        for (int i = 0; i < (int)vec.size(); ++i) sum += vec[i];
        down = (int)(sum % MOD);
    }

    cout << (ll)up * down % MOD << "\n";
    return 0;
}
