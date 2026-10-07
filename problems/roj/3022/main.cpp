/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:13
 * update_at: 2026-10-06 11:13
 */
#include <deque>
#include <iostream>
#include <string>
using namespace std;
typedef long long ll;

deque<ll> piles[14]; // piles[i]：第 i 堆牌，从上到下存点数（队首是堆顶）
ll up[14];           // up[v]：点数 v 被翻开并压入 v 号堆的次数，即正面朝上的 v 的张数

// 把牌面转成点数：A=1、2~9 为原值、0=10、J=11、Q=12、K=13
ll face_to_value(const string &face) {
    if (face == "A") return 1;
    if (face == "0") return 10;
    if (face == "J") return 11;
    if (face == "Q") return 12;
    if (face == "K") return 13;
    return face[0] - '0';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 读入 13 行，每行 4 张牌，行内顺序即从上到下
    for (ll i = 1; i <= 13; i++) {
        for (ll j = 1; j <= 4; j++) {
            string face;
            cin >> face;
            piles[i].push_back(face_to_value(face));
        }
    }

    // 4 条命：每条命先抽生命牌堆顶，再沿牌链走，直到抽到 K（点数 13）
    for (ll life = 1; life <= 4; life++) {
        ll value = piles[13].front(); // 生命牌堆最上面一张
        piles[13].pop_front();
        while (value != 13) {
            piles[value].push_front(value); // 正面朝上压到 value 号堆顶
            up[value]++;
            ll next_value = piles[value].back(); // 从该堆最下面抽一张
            piles[value].pop_back();
            value = next_value;
        }
    }

    ll answer = 0; // A~Q 中凑满 4 张正面朝上的点数个数（K 不计）
    for (ll v = 1; v <= 12; v++) {
        if (up[v] == 4) answer++;
    }
    cout << answer << '\n';
    return 0;
}
