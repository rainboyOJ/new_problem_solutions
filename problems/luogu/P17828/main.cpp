/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 18:55
 * update_at: 2026-10-31 20:00
 */
// main.cpp：答案等于「字符不同的对称位置对数」。
// 两侧的段指针同时向中间走，每段还剩多少直接记在 a[] 里（边走边减）；
// 两侧撞进同一段时，剩下的字符全都在这一段、字符必然相同，直接收工。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5 + 5;
int n;
ll a[maxn];    // 第 i 段的长度，跑的过程中会被减掉已经配掉的字符数
char c[maxn];  // 第 i 段全是字符 c[i]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    ll L = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> c[i];
        L += a[i];
    }

    ll half = L / 2;   // 一共要配几组，奇数长度时正中间的字符配给自己
    ll done = 0;       // 已经配好几组
    ll ans = 0;
    int li = 0, ri = n - 1;   // 左端当前段、右端当前段

    while (done < half) {
        if (li == ri) {
            // 两侧已经走进同一段：还没配的字符全在这段里，字符都一样，
            // 这些组一组都不用改，答案不会再变，直接结束。
            break;
        }
        // 两侧还在不同的段：各能提供多少个字符就吃多少，但别超过还差的组数
        ll take = min(min(a[li], a[ri]), half - done);
        if (c[li] != c[ri]) ans += take;   // 这一批 take 组对称位置全都要改
        a[li] -= take;
        a[ri] -= take;
        done += take;
        if (a[li] == 0) ++li;   // 这一段用完了，换成下一段
        if (a[ri] == 0) --ri;
    }

    cout << ans << '\n';
    return 0;
}
