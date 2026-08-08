/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m;

int main() {
    cin >> n >> m;
    ll sq = 0;
    for (ll side = 1; side <= min(n, m); side++)
        sq += (n - side + 1) * (m - side + 1);
    ll all = n * (n + 1) * m * (m + 1) / 4;
    ll rect = all - sq;
    cout << sq << " " << rect << endl;
    return 0;
}
