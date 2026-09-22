/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-22 20:35
 * update_at: 2026-09-22 20:35
 */
// main2.cpp：友好城市（子任务解法，N <= 5000，O(N^2)）。
//
// 同样先按南岸坐标从小到大排序，问题变成求北岸坐标序列 t[] 的最长严格
// 上升子序列(LIS)。这里用最直观的 O(N^2) DP：
//   dp[i] = 以第 i 对城市结尾时, 最多能批准多少条航道
//         = 1 + max{ dp[j] : j < i 且 t[j] < t[i] }   (没有可接的 j 时取 1)
//   ans   = max{ dp[i] }
// 瓶颈：对每个 i 都要回头扫描所有 j，一共 O(N^2) 次比较。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 5005; // 子任务 N <= 5000

int n;       // 友好城市的对数
int dp[maxn];// dp[i] = 以第 i 对城市结尾的最长合法链长度

struct Node{
    int s; // 南岸坐标
    int t; // 北岸坐标
} a[maxn];

// 按南岸坐标从小到大排序，让"南岸的先后顺序"成为序列的固定顺序。
bool cmp_south(const Node &x, const Node &y){
    return x.s < y.s;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> a[i].s >> a[i].t;
    }

    sort(a + 1, a + n + 1, cmp_south);

    int ans = 0;
    for(int i = 1; i <= n; ++i){
        dp[i] = 1; // 只选第 i 对城市, 长度至少是 1
        for(int j = 1; j < i; ++j){
            // 南岸顺序已经固定, 只要北岸坐标也更大, 就能接在第 j 对后面
            if(a[j].t < a[i].t){
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        ans = max(ans, dp[i]);
    }

    cout << ans << "\n";
    return 0;
}
