/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:42
 * update_at: 2026-10-06 14:42
 */
#include <cstdio>
typedef long long ll;

const int MAXN = 200005;

ll S[MAXN]; // 第 i 组防具的起点
ll E[MAXN]; // 第 i 组防具的终点
ll D[MAXN]; // 第 i 组防具的步长，D=0 时归一为 1
int n;      // 当前测试数据的防具组数

// 位置 x 及左侧防具总数的奇偶性：1 表示破绽在 x 或其左侧
ll prefix_parity(ll x) {
    ll total = 0;
    for (int i = 1; i <= n; i++) {
        if (x < S[i]) {
            continue;
        }
        // 第 i 组在 [S_i, min(E_i, x)] 内的等差数列项数
        ll right = E[i] < x ? E[i] : x;
        total += (right - S[i]) / D[i] + 1;
    }
    return total & 1;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            ll s, e, d;
            scanf("%lld %lld %lld", &s, &e, &d);
            if (d == 0) {
                e = s; // 步长为 0 时等差数列退化成单点 S
                d = 1;
            }
            S[i] = s;
            E[i] = e;
            D[i] = d;
        }

        ll lo = S[1] - 1; // lo 左侧没有任何防具，前缀奇偶性必为 0
        ll hi = E[1];
        for (int i = 2; i <= n; i++) {
            if (S[i] - 1 < lo) {
                lo = S[i] - 1;
            }
            if (E[i] > hi) {
                hi = E[i];
            }
        }

        if (prefix_parity(hi) == 0) {
            printf("There's no weakness.\n"); // 总防具数为偶数，无破绽
            continue;
        }

        // 奇偶性在破绽处由 0 翻转为 1，二分找到第一个翻转位置
        while (hi - lo > 1) {
            ll mid = (lo + hi) / 2;
            if (prefix_parity(mid)) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        ll p = hi;

        // 每组等差数列至多在 p 处放一件，数出覆盖 p 的组数即为该处件数
        ll cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (S[i] <= p && p <= E[i] && (p - S[i]) % D[i] == 0) {
                cnt++;
            }
        }
        printf("%lld %lld\n", p, cnt);
    }
    return 0;
}
