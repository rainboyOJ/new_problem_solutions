/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:49
 * update_at: 2026-10-06 01:49
 */
#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;

ll n, k;

// memo[rest][parts][low] 表示把 rest 拆成 parts 个非降正整数、且每段不小于 low 的方案数。
// n 最大约 200，k 最大约 7，low 最大约 n，用 -1 表示未计算。
ll memo[205][10][205];

// 返回方案数。
ll ways(ll rest, ll parts, ll low) {
    if (parts == 0) return rest == 0 ? 1 : 0;        // 恰好填满才合法
    if (parts == 1) return rest >= low ? 1 : 0;      // 只剩一段，和已固定
    ll &ans = memo[rest][parts][low];
    if (ans != -1) return ans;
    ans = 0;
    // head 的下界是非降约束 low；上界来自余下每段至少 head，即 head * parts <= rest。
    ll up = rest / parts;
    for (ll head = low; head <= up; ++head) {
        ans += ways(rest - head, parts - 1, head);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(memo, -1, sizeof(memo));
    cin >> n >> k;
    cout << ways(n, k, 1) << '\n';
    return 0;
}
