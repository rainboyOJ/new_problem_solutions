/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:33
 * update_at: 2026-10-06 09:33
 */
#include <iostream>
#include <set>
#include <utility>
#include <climits>
#include <algorithm>
using namespace std;

typedef long long ll;

const int BASE = 4;             // 固定 4 个矩形块

ll a[BASE][2];                  // 输入的 4 个矩形块边长
ll order[BASE];                 // 当前排列：order[i] 表示第 i 个图位放的原始矩形编号
ll orient[BASE];                // 当前方向：0 表示 a×b，1 表示 b×a
ll best_area;                   // 当前最小面积
set<pair<ll, ll> > ans;         // 取到最小面积的所有规范化边长 (p, q)

// 用当前排列和方向得到第 k 个图位矩形的宽 w[k]、高 h[k]
void get_rect(ll w[], ll h[]) {
    for (int i = 0; i < BASE; i++) {
        ll idx = order[i];
        if (orient[i] == 0) {
            w[i] = a[idx][0];
            h[i] = a[idx][1];
        } else {
            w[i] = a[idx][1];
            h[i] = a[idx][0];
        }
    }
}

// 尝试用 (宽, 高) 更新答案集合
void update(ll width, ll height) {
    ll area = width * height;
    ll p = min(width, height);
    ll q = max(width, height);
    if (area < best_area) {
        best_area = area;
        ans.clear();
        ans.insert(make_pair(p, q));
    } else if (area == best_area) {
        ans.insert(make_pair(p, q));
    }
}

// 计算 5 种基本铺放方案（方案 4、5 为同一拓扑）的封闭矩形并更新答案
void calc_all() {
    ll w[BASE], h[BASE];
    get_rect(w, h);

    ll w1 = w[0], h1 = h[0];
    ll w2 = w[1], h2 = h[1];
    ll w3 = w[2], h3 = h[2];
    ll w4 = w[3], h4 = h[3];

    // 方案 1：4 个矩形一字排开
    update(w1 + w2 + w3 + w4, max(max(h1, h2), max(h3, h4)));

    // 方案 2：下面并排 3 个，上面压 1 个
    update(max(w1 + w2 + w3, w4), max(max(h1, h2), h3) + h4);

    // 方案 3：左侧上下叠 2 个，右侧下方 1 个，右上方 1 个
    update(max(w1 + w2, w3) + w4, max(max(h1 + h3, h2 + h3), h4));

    // 方案 4/5：双柱加横梁
    update(w1 + max(w2, w4) + w3, max(max(h1, h3), h2 + h4));

    // 方案 6：风车形，按高度关系分 5 类求宽度
    ll width6;
    if (h3 >= h2 + h4) {
        width6 = max(max(w1, w2 + w3), w3 + w4);
    } else if (h3 > h4) {
        width6 = max(max(w1 + w2, w2 + w3), w3 + w4);
    } else if (h4 > h3) {
        width6 = max(max(w1 + w2, w1 + w4), w3 + w4);
    } else if (h4 >= h1 + h3) {
        width6 = max(max(w2, w1 + w4), w3 + w4);
    } else { // h3 == h4
        width6 = max(w1 + w2, w3 + w4);
    }
    update(width6, max(h1 + h3, h2 + h4));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for (int i = 0; i < BASE; i++) {
        cin >> a[i][0] >> a[i][1];
    }

    // 初始化排列为 0,1,2,3
    for (int i = 0; i < BASE; i++) {
        order[i] = i;
    }

    best_area = LLONG_MAX;
    ans.clear();

    // 枚举 4! 排列
    do {
        // 枚举 2^4 方向
        for (int mask = 0; mask < (1 << BASE); mask++) {
            for (int i = 0; i < BASE; i++) {
                orient[i] = (mask >> i) & 1;
            }
            calc_all();
        }
    } while (next_permutation(order, order + BASE));

    cout << best_area << "\n";
    for (set<pair<ll, ll> >::iterator it = ans.begin(); it != ans.end(); it++) {
        cout << it->first << " " << it->second << "\n";
    }

    return 0;
}
