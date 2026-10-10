/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 22:30
 * update_at: 2026-10-10 00:05
 */
// main.cpp：卡片。
//   把 B 的边界拉直成一条总长 N*B 的线段，每隔 B 有一个向外的拐角。
//   Alice 每走完一条边长 A 要旋转一次，碰到 B 的拐角也要多旋转一次；
//   两种时刻重合时只算一次 ⇒ 旋转次数 = (0, X] 内「A 的倍数或 B 的倍数」的个数，
//   其中回到原位所需的总路程 X = lcm(A, N*B)。（由正多边形的旋转对称性，
//   只要 A 的整条边重新贴回起始边就算回到原位，故 A 的边数 M 不影响答案。）
//   容斥：ans = X/A + X/B - X/lcm(A,B)。这里把后两项合并成 (X/lcm(A,B))*(lcm(A,B)/B - 1)。
// 多组测试数据，while 读到 EOF，每组输出一行。
#include <iostream>
#include <numeric>

using namespace std;

typedef long long ll;

void solve() {
    ll a, m, b, n; // m 只读入、不参与计算：正多边形对称，A 的边数 M 与答案无关
    while (cin >> a >> m >> b >> n) {
        ll nb = n * b;
        ll x = a / std::gcd(a, nb) * nb; // x = lcm(a, n*b)，先除后乘避免中间乘积溢出
        ll c1 = x / a;                   // (0, x] 中 A 的倍数个数
        ll y = a / std::gcd(a, b) * b;   // y = lcm(a, b)
        ll c2 = x / y * (y / b - 1);     // (0, x] 中 B 的倍数个数去掉与 A 的倍数重合的部分
        cout << c1 + c2 << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
