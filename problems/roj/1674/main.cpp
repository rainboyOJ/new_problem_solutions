/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:49
 * update_at: 2026-10-06 01:49
 */

#include <cstdio>
#include <queue>
using namespace std;

typedef long long ll;

const ll MAXN = 25;

ll m, n;               // m 个人围成圈，报数到 n 出局
ll sex[MAXN];          // sex[i] = 1 表示男生，0 表示女生
ll chances[MAXN];      // chances[i] 表示第 i 个人剩余的"数中机会"，男 1 女 2

// 循环队列模拟报数：队首永远是下一个报数的人
void solve() {
    queue<ll> q;
    for (ll i = 1; i <= m; ++i)
        q.push(i);

    ll counter = 0;    // 当前这一棒已经报到的数字
    while (q.size() > 1) {
        ll p = q.front();
        q.pop();
        counter++;
        if (counter < n) {
            q.push(p);         // 没数到 n，回到队尾继续报数
            continue;
        }
        counter = 0;           // 数到 n：下一个人从 1 重新报数
        chances[p]--;          // 用掉一次机会
        if (chances[p] > 0)
            q.push(p);         // 女生第 1 次数中不出局，站回队尾
        // 机会用完则不再入队，即出局
    }
    printf("%lld\n", q.front());
}

int main() {
    scanf("%lld", &m);
    for (ll i = 1; i <= m; ++i) {
        scanf("%lld", &sex[i]);
        chances[i] = (sex[i] == 0) ? 2 : 1; // 女生 2 次机会，男生 1 次
    }
    scanf("%lld", &n);
    solve();
    return 0;
}
