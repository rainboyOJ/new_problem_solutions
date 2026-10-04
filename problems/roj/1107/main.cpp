/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 01:40
 * update_at: 2026-10-05 01:40
 */

#include <algorithm>
#include <iostream>
typedef long long ll;
using namespace std;

const int MAXL = 10005;

// removed_tree[i] = 1 表示位置 i 上的树被移走
bool removed_tree[MAXL];

int main() {
    ll L, M; // L 马路长度，M 区域数目
    cin >> L >> M;
    for (int i = 1; i <= M; i++) {
        ll a, b;
        cin >> a >> b;
        if (a > b) swap(a, b); // 题目保证是两个不同整数，统一成左小右大
        for (ll j = a; j <= b; j++) removed_tree[j] = 1; // 区域内含端点的树全部移走
    }
    // 马路上共有 L+1 个整数点，统计没被移走的
    ll ans = 0;
    for (ll i = 0; i <= L; i++)
        if (!removed_tree[i]) ans++;
    cout << ans << endl;
    return 0;
}
