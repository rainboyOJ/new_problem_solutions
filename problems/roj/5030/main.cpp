/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 19:45
 * update_at: 2026-10-08 19:45
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll TOTAL = 100;        // 百钱买百鸡：鸡共 100 只、钱共 100 文
const ll ROOSTER_PRICE = 5;  // 鸡翁一只值钱 5
const ll HEN_PRICE = 3;      // 鸡母一只值钱 3
const ll CHICK_PER_COIN = 3; // 鸡雏 3 只值钱 1，所以鸡雏数必须是 3 的倍数

// 枚举鸡翁数、鸡母数，由「百鸡」推出鸡雏数，再校验「百钱」。
// 鸡翁从小到大枚举，输出天然按鸡翁升序，符合题面「依次由小到大」。
void solve() {
    for (ll rooster = 0; rooster * ROOSTER_PRICE <= TOTAL; rooster++) {
        for (ll hen = 0; hen * HEN_PRICE <= TOTAL; hen++) {
            ll chick = TOTAL - rooster - hen;
            // 鸡雏按 3 只一组卖，不能整除就没有对应钱数，直接跳过
            if (chick < 0 || chick % CHICK_PER_COIN != 0) {
                continue;
            }
            ll cost = rooster * ROOSTER_PRICE + hen * HEN_PRICE + chick / CHICK_PER_COIN;
            if (cost == TOTAL) {
                cout << rooster << " " << hen << " " << chick << "\n";
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
