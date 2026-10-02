/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 08:57
 * update_at: 2026-10-02 08:57
 */
// main2.cpp：第二种解法。先把油价序列里“从 1 号站开始依次出现的新低站点”
//（严格下降子序列，允许跳过中间的站点）存进数组，再按相邻两个新低站之间的
// 距离算出每一段要买多少整升油。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, d;
int v[MAXN];              // v[i]：站点 i 到 i+1 的距离
int a[MAXN];              // a[i]：站点 i 的油价
long long pos[MAXN];      // pos[i]：站点 i 距离 1 号站的累计公里数（前缀和）

struct Low {
    int idx;              // 新低站点的编号
    long long at;         // 到这个站点为止的累计公里数
};

Low low[MAXN];            // low[1..cnt]：价格严格下降的新低站点序列
int cnt;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> d;
    for (int i = 1; i <= n - 1; i++) {
        cin >> v[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 距离前缀和，后面用它算任意两个站点之间的公里数。
    pos[1] = 0;
    for (int i = 1; i < n; i++) {
        pos[i + 1] = pos[i] + v[i];
    }

    // 找“新低”站点：价格严格低于之前所有站点才入数组。
    // 注意是子序列而不是连续下降段：中间价格回升不中断这个序列，
    // 只要后面出现更低的价格就继续记，否则会漏掉真正便宜的站点。
    cnt = 1;
    low[1].idx = 1;
    low[1].at = pos[1];
    int cur_min = a[1];
    for (int i = 2; i <= n; i++) {
        if (a[i] < cur_min) {
            cur_min = a[i];
            cnt++;
            low[cnt].idx = i;
            low[cnt].at = pos[i];
        }
    }

    // 贪心：只会在这几个新低站点加油——比它们贵的站点，油都能用更低价买在前面。
    // 从 low[i] 开到 low[i+1] 之间没有更便宜的站，所以缺口必须在 low[i] 用
    // a[low[i]] 这个价买够；整升购买向上取整，多出来的油带进后面（更便宜的）路段。
    long long ans = 0;
    long long tank = 0;    // 油箱里已有的油还能跑多少公里
    for (int i = 1; i <= cnt; i++) {
        long long seg = (i < cnt ? low[i + 1].at : pos[n]) - low[i].at; // 下一站/终点前的距离
        long long lack = seg - tank;
        if (lack > 0) {
            long long liter = (lack + d - 1) / d;   // 只能整升买，向上取整
            ans += liter * a[low[i].idx];
            tank += liter * d - seg;                // 剩余油量（公里数）
        } else {
            tank -= seg;                            // 现有油够用，一分钱不花
        }
    }

    cout << ans << '\n';

    return 0;
}
