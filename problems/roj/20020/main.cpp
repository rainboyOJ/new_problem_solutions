/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 21:26
 * update_at: 2026-08-28 21:26
 */
// main.cpp：容斥 + 并查集。
// 枚举 T 的子集 S（2^15 种），对 S 中每一位 k，把所有第 k 位为 1 的数用并查集合并（强制同组），
// 每个连通块有 2 种去向（A 或 B），贡献 (-1)^{|S|} * 2^{连通块数}，求和即答案。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;   // n 的上界
const int MAXB = 15;    // 位数：0 <= a_i < 2^15
const int MOD = 998244353;

int n;
int a[MAXN];

// bitList[k][0..bitLen[k]-1]：第 k 位为 1 的所有元素下标
int bitList[MAXB][MAXN];
int bitLen[MAXB];

int father[MAXN];       // 并查集父节点
long long pow2[MAXN];   // pow2[c] = 2^c % MOD

// 并查集：找根（带路径压缩）
int find(int u) {
    if (father[u] == u) return u;
    return father[u] = find(father[u]);
}

void solve() {
    // T = 全部元素的或；只可能出现在 T 中的位才需要被“检查”
    int T = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        T |= a[i];
    }

    // 预处理：每一位的 1-数列表，省去后面每次重复扫描
    for (int k = 0; k < MAXB; k++)
        for (int i = 1; i <= n; i++)
            if (a[i] & (1 << k))
                bitList[k][bitLen[k]++] = i;

    pow2[0] = 1;
    for (int i = 1; i <= n; i++)
        pow2[i] = pow2[i - 1] * 2 % MOD;

    long long ans = 0;
    // 容斥：枚举 T 的子集 S，S 中每一位都被“强制”：该位为 1 的数同处一个集合
    for (int S = 0; S < (1 << MAXB); S++) {
        if ((T & S) != S) continue; // 只枚举 T 的子集

        for (int i = 1; i <= n; i++) father[i] = i; // 初始化并查集

        // 对 S 中每一位 k，把第 k 位为 1 的所有数合并成一个连通块
        for (int k = 0; k < MAXB; k++) {
            if (!(S & (1 << k))) continue;
            for (int i = 1; i < bitLen[k]; i++) {
                int u = find(bitList[k][0]);
                int v = find(bitList[k][i]);
                if (u != v) father[u] = v;
            }
        }

        // 统计连通块个数：每个块独立选择 A 或 B，共 2^cc 种
        int cc = 0;
        for (int i = 1; i <= n; i++)
            if (find(i) == i) cc++;

        if (__builtin_popcount(S) & 1)
            ans = (ans - pow2[cc] + MOD) % MOD; // 奇数个强制位取负号
        else
            ans = (ans + pow2[cc]) % MOD;
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
