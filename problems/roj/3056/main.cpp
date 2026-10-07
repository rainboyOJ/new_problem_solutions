/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:52
 * update_at: 2026-10-06 16:52
 */

// 对顶堆求第 p 小：大根堆 small 维护"当前最小的 p 个数"，堆顶即答案；
// 小根堆 big 装剩下的数，两堆合起来是全集。
// 注意 |A(i)| <= 2*10^9 超出 int 范围，题目数据用 ll。
#include <cstdio>
#include <queue>
#include <vector>
#include <functional>
using namespace std;

typedef long long ll;

const ll MAXM = 30005;

ll m, n;
ll a[MAXM]; // a[i] = 序列 A 的第 i 个加入元素（下标从 1 开始）
ll u[MAXM]; // u[p] = 第 p 次 GET 时盒内元素个数（下标从 1 开始）

priority_queue<ll> small; // 大根堆：装当前最小的若干个数，堆顶是第 p 小
priority_queue<ll, vector<ll>, greater<ll> > big; // 小根堆：装其余的数

// 读取输入
void read_input() {
    scanf("%lld %lld", &m, &n);
    for (ll i = 1; i <= m; i++) scanf("%lld", &a[i]);
    for (ll p = 1; p <= n; p++) scanf("%lld", &u[p]);
}

// 依次处理 N 次 GET
void solve() {
    ll p = 1; // 第 p 次 GET，small 的目标大小就是 p
    for (ll i = 1; i <= m; i++) {
        ll x = a[i];
        // 贪心：比左侧最大值还小的数进 small，否则进 big，保证 small 是最小的一段
        if (small.empty() || x < small.top())
            small.push(x);
        else
            big.push(x);

        // u[p] == i 说明第 p 个元素已加入，第 p 次 GET 发生在此刻之后
        while (p <= n && u[p] == i) {
            // 左借：small 不足 p 个，从 big 借最小值
            while ((ll)small.size() < p) {
                small.push(big.top());
                big.pop();
            }
            // 右还：small 超过 p 个，把左侧最大值还给 big
            while ((ll)small.size() > p) {
                big.push(small.top());
                small.pop();
            }
            printf("%lld\n", small.top()); // 堆顶即当前第 p 小
            p++;
        }
    }
}

int main() {
    read_input();
    solve();
    return 0;
}
