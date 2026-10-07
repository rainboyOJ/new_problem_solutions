/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:34
 * update_at: 2026-10-06 14:34
 */
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXM = 200005; // 选手数 2N 的上界，N <= 100000

ll n, r, q;            // 每边人数、轮数、询问名次
ll m;                  // 选手总数 2N
ll score[MAXM];        // score[i] 表示第 i 号选手当前总分（1-indexed）
ll power[MAXM];        // power[i] 表示第 i 号选手的实力值
ll order[MAXM];        // order[k] 表示当前第 k 名的选手编号
ll winner[MAXM];       // 本轮胜者组：按本轮赛前名次排列
ll loser[MAXM];        // 本轮负者组：与胜者组一一对应
ll nxt[MAXM];          // 归并两个有序组后的新排名

// 排名关键字：(总分降序，同分编号升序)
bool cmp_rank(ll a, ll b) {
    if (score[a] != score[b]) {
        return score[a] > score[b];
    }
    return a < b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> r >> q;
    m = 2 * n;
    for (ll i = 1; i <= m; i++) {
        cin >> score[i];
    }
    for (ll i = 1; i <= m; i++) {
        cin >> power[i];
    }

    for (ll i = 1; i <= m; i++) {
        order[i] = i;
    }
    sort(order + 1, order + m + 1, cmp_rank);

    for (ll rd = 1; rd <= r; rd++) {
        // 每轮按当前排名两两配对，实力高者获胜并加一分
        ll win_cnt = 0;
        ll lose_cnt = 0;
        for (ll k = 1; k <= m; k += 2) {
            ll a = order[k];
            ll b = order[k + 1];
            if (power[a] > power[b]) {
                score[a]++;
                winner[++win_cnt] = a;
                loser[++lose_cnt] = b;
            } else {
                score[b]++;
                winner[++win_cnt] = b;
                loser[++lose_cnt] = a;
            }
        }

        // 胜者组内部同时加一分、负者组内部不变，两组各自仍有序，归并即可
        ll i = 1;
        ll j = 1;
        ll idx = 0;
        while (i <= win_cnt && j <= lose_cnt) {
            if (cmp_rank(winner[i], loser[j])) {
                nxt[++idx] = winner[i++];
            } else {
                nxt[++idx] = loser[j++];
            }
        }
        while (i <= win_cnt) {
            nxt[++idx] = winner[i++];
        }
        while (j <= lose_cnt) {
            nxt[++idx] = loser[j++];
        }
        for (ll k = 1; k <= m; k++) {
            order[k] = nxt[k];
        }
    }

    cout << order[q] << '\n';
    return 0;
}
