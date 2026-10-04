/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:50
 * update_at: 2026-10-05 05:50
 */
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

// 当前(a,b)局面（a>=b）下，执子者是否必胜
// 商>=2 或整除时当前执子者可直接获胜；否则只能(a,b)->(b,a-b)，胜负翻转
bool current_wins(ll a, ll b) {
    bool mine = true; // true 表示起始先手在此局面执子
    while (a / b < 2 && a % b != 0) { // 商为1且不整除：唯一取法
        ll nb = a - b; // 取完后较少堆变为 a-b
        a = b;
        b = nb;
        mine = !mine; // 唯一取法后换人
    }
    return mine; // 比值>=2或整除：当前执子者获胜
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll a, b;
    while (cin >> a >> b) {
        if (a == 0 && b == 0) break;
        if (a < b) swap(a, b); // 保证 a 是较多堆
        cout << (current_wins(a, b) ? "win" : "lose") << "\n";
    }
    return 0;
}
