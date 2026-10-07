/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 02:11
 * update_at: 2026-10-06 02:11
 */

#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;

// 铺满长度为 len 的边需要多少块边长为 a 的石板：整数上取整
ll need(ll len, ll a) {
    return (len + a - 1) / a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m, a;
    cin >> n >> m >> a;

    // 长、宽两个方向分别上取整后相乘
    cout << need(n, a) * need(m, a) << "\n";
    return 0;
}
