/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-12
 * update_at: 2026-10-12
 *
 * 暴力程序：枚举所有合并顺序，验证"先合并最小的两堆"最优
 * 只能跑很小的 n（合并顺序有 (2n-3)!! 种，n=7 就有 10395 种）
 */

#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 10;      // 暴力只能处理很少的堆数
const int MAXC = 100000;  // 最多记录这么多种合并顺序

ll a[MAXN];       // 一开始各堆的重量
ll all[MAXC];     // 所有合并顺序的总代价
int alln;         // 总代价的个数

// 枚举 cur[0..cnt-1] 这 cnt 堆的所有合并顺序
// cost 是已经花掉的体力
void dfs(ll cur[], int cnt, ll cost) {
    if (cnt == 1) {           // 只剩一堆，一种合并顺序走完了
        all[alln++] = cost;   // 记录这种顺序的总代价
        return;
    }
    int i, j, k;
    for (i = 0; i < cnt; ++i)        // 任选两堆 i,j 合并
        for (j = i + 1; j < cnt; ++j) {
            ll b[MAXN];               // 合并后的新集合
            int m = 0;
            for (k = 0; k < cnt; ++k)
                if (k != i && k != j) b[m++] = cur[k];
            b[m++] = cur[i] + cur[j]; // i,j 两堆合并成一堆
            dfs(b, m, cost + cur[i] + cur[j]);
        }
}

int main() {
    int n, i;
    cin >> n;
    for (i = 0; i < n; ++i) cin >> a[i];

    alln = 0;
    dfs(a, n, 0);
    sort(all, all + alln);    // 按总代价从小到大排

    cout << "合并顺序共 " << alln << " 种, 总代价从小到大: " << endl;
    for (i = 0; i < alln; ++i) cout << all[i] << " ";
    cout << endl;
    cout << "最小总代价 = " << all[0] << endl;
    return 0;
}
