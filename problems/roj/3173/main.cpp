/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 消除木块：区间 DP，先把同色相邻块压成颜色段
#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;

int seg_cnt;                 // 颜色段个数
vector<int> seg_size;        // 第 i 段里有几个木块
vector<vector<int> > earlier; // earlier[j]：第 j 段前面同色的段号，从近到远严格递减
vector<int> memo;            // f(i,j,k) 的记忆化表，-1 表示未算
int dim;                     // memo 每一维的大小（可用的 k 上界 + 2）

int idx(int i, int j, int k) {
    return (i * dim + j) * dim + k;
}

// 消掉颜色段 i..j 的最高分；段 j 这一次消除还会额外带上右边 k 个同色木块
int f(int i, int j, int k) {
    int& res = memo[idx(i, j, k)];
    if (res >= 0) {
        return res;
    }
    if (i == j) {
        int t = seg_size[j] + k;
        res = t * t;
        return res;
    }
    res = f(i, j - 1, 0) + (seg_size[j] + k) * (seg_size[j] + k); // 段 j 单独消
    for (int t = 0; t < (int)earlier[j].size(); t++) {
        int p = earlier[j][t];
        if (p < i) {
            break; // earlier[j] 递减，再往前都越界了
        }
        // 段 j 这次消除还包含左边的同色段 p：中间那截被夹住，接不到外面的木块
        int tail = (p == j - 1) ? 0 : f(p + 1, j - 1, 0);
        int cand = f(i, p, k + seg_size[j]) + tail;
        if (cand > res) {
            res = cand;
        }
    }
    return res;
}

// 一组数据的最高分
int score(vector<int>& colors) {
    seg_cnt = 0;
    seg_size.clear();
    earlier.clear();
    vector<vector<int> > seen; // 每个颜色已经出现过的段号，递增
    int previous = 0;          // 颜色 ∈ [1,n]，哨兵 0 保证第一块不并进上一段
    for (int t = 0; t < (int)colors.size(); t++) {
        int value = colors[t];
        if (previous == value) { // 与上一块同色：并进当前段
            seg_size[seg_cnt - 1]++;
            continue;
        }
        if ((int)seen.size() <= value) {
            seen.resize(value + 1);
        }
        vector<int> rev;
        for (int q = (int)seen[value].size() - 1; q >= 0; q--) {
            rev.push_back(seen[value][q]);
        }
        earlier.push_back(rev);
        seen[value].push_back(seg_cnt);
        seg_size.push_back(1);
        seg_cnt++;
        previous = value;
    }
    dim = (int)colors.size() + 2;
    memo.assign((seg_cnt + 1) * dim * dim, -1);
    return f(0, seg_cnt - 1, 0);
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) {
        return 0;
    }
    for (int tc = 1; tc <= T; tc++) {
        int n;
        scanf("%d", &n);
        vector<int> colors(n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &colors[i]);
        }
        printf("Case %d: %d\n", tc, score(colors));
    }
    return 0;
}
