/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:40
 * update_at: 2026-10-06 11:40
 */

// 星空题：星座 = 8 连通块；相似 = 经过 8 种 D4 变换后形状一致。
// 做法：洪填提取每个星座 -> 算规范指纹（8 种变换各自平移归一化后取字典序最小的点集）
// -> 指纹第一次出现领新字母，之后相似的星座复用同一个字母。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105;  // 天体图最大宽度和深度
const int MAXP = 165;  // 每个星座最多 160 颗星
const int MAXC = 505;  // 星座最多 500 个

int W, H;
char grid[MAXN][MAXN]; // 天体图，grid[行][列]，'1' 表示星星，最后被替换成字母
bool vis[MAXN][MAXN];  // 洪填时标记格子是否已经属于处理过的星座

ll star_r[MAXP], star_c[MAXP]; // 洪填收集到的当前星座的原始格子坐标
ll star_cnt;                   // 当前星座的星星数

ll norm_r[8][MAXP], norm_c[8][MAXP]; // 第 k 种 D4 变换平移归一化后的点集

pair<ll, ll> best_shape[MAXP]; // 当前星座的规范指纹：8 种形态里字典序最小的点集

// 已见指纹表：finger[i] = 第 i 个「新字母星座」的规范指纹
pair<ll, ll> finger[MAXC][MAXP];
ll finger_len[MAXC];
ll finger_cnt; // 已存指纹个数 = 已分配字母个数

// 检查 (r, c) 是否在天体图内。
bool in_map(ll r, ll c) {
    return r >= 0 && r < H && c >= 0 && c < W;
}

// 八方向 BFS 洪填：从 (sr, sc) 出发收集整个 8 连通块的原始坐标。
void flood_fill(ll sr, ll sc) {
    star_cnt = 0;
    ll qr[MAXN * MAXN], qc[MAXN * MAXN]; // BFS 队列（行、列）
    ll head = 0, tail = 0;
    qr[tail] = sr; qc[tail] = sc; tail++;
    vis[sr][sc] = true;

    while (head < tail) {
        ll r = qr[head], c = qc[head];
        head++;
        star_r[star_cnt] = r; star_c[star_cnt] = c; star_cnt++;
        for (ll dr = -1; dr <= 1; dr++) {
            for (ll dc = -1; dc <= 1; dc++) {
                if (dr == 0 && dc == 0) continue;
                ll nr = r + dr, nc = c + dc;
                if (!in_map(nr, nc)) continue;
                if (grid[nr][nc] != '1' || vis[nr][nc]) continue;
                vis[nr][nc] = true;
                qr[tail] = nr; qc[tail] = nc; tail++;
            }
        }
    }
}

// 生成第 k 种 D4 变换的平移归一化点集，存进 norm_r[k]/norm_c[k]。
// 8 种变换：(r,c) (r,-c) (-r,c) (-r,-c) (c,r) (c,-r) (-c,r) (-c,-r)。
void make_transform(ll k) {
    ll min_r = LLONG_MAX, min_c = LLONG_MAX;
    for (ll i = 0; i < star_cnt; i++) {
        ll r, c;
        if (k == 0)      { r = star_r[i];  c = star_c[i];  }
        else if (k == 1) { r = star_r[i];  c = -star_c[i]; }
        else if (k == 2) { r = -star_r[i]; c = star_c[i];  }
        else if (k == 3) { r = -star_r[i]; c = -star_c[i]; }
        else if (k == 4) { r = star_c[i];  c = star_r[i];  }
        else if (k == 5) { r = star_c[i];  c = -star_r[i]; }
        else if (k == 6) { r = -star_c[i]; c = star_r[i];  }
        else             { r = -star_c[i]; c = -star_r[i]; }
        norm_r[k][i] = r; norm_c[k][i] = c;
        if (r < min_r) min_r = r;
        if (c < min_c) min_c = c;
    }
    // 平移到最小行、最小列为 0，消除星座在天体图中的位置差异
    for (ll i = 0; i < star_cnt; i++) {
        norm_r[k][i] -= min_r;
        norm_c[k][i] -= min_c;
    }
}

// 计算当前星座的规范指纹：8 种形态各自排序后取字典序最小，结果存进 best_shape。
void compute_canonical() {
    for (ll i = 0; i < star_cnt; i++) {
        best_shape[i] = make_pair(norm_r[0][i], norm_c[0][i]);
    }
    sort(best_shape, best_shape + star_cnt);

    for (ll k = 1; k < 8; k++) {
        pair<ll, ll> cur[MAXP]; // 第 k 种变换排序后的点集
        for (ll i = 0; i < star_cnt; i++) {
            cur[i] = make_pair(norm_r[k][i], norm_c[k][i]);
        }
        sort(cur, cur + star_cnt);

        // 逐点比较，谁字典序小谁当新的规范形态
        for (ll i = 0; i < star_cnt; i++) {
            if (cur[i] == best_shape[i]) continue;
            if (cur[i] < best_shape[i]) {
                for (ll j = 0; j < star_cnt; j++) best_shape[j] = cur[j];
            }
            break;
        }
    }
}

int main() {
    scanf("%d %d", &W, &H);
    for (ll i = 0; i < H; i++) {
        scanf("%s", grid[i]);
    }

    for (ll i = 0; i < H; i++) {
        for (ll j = 0; j < W; j++) {
            if (grid[i][j] != '1' || vis[i][j]) continue;
            // 按扫描顺序遇到的连通块就是尚未标号的最左上角星座，字母按顺序分配
            flood_fill(i, j);

            // 先用原始坐标把字母写进图（后续变换只读副本，不动 star_r/star_c）
            for (ll t = 0; t < star_cnt; t++) {
                grid[star_r[t]][star_c[t]] = 'a' + finger_cnt;
            }

            // 生成 8 种平移归一化形态，算规范指纹
            for (ll k = 0; k < 8; k++) make_transform(k);
            compute_canonical();

            // 指纹查重：和之前所有「领过新字母」的星座逐一比较
            bool found = false;
            for (ll id = 0; id < finger_cnt; id++) {
                if (finger_len[id] != star_cnt) continue;
                bool same = true;
                for (ll t = 0; t < star_cnt; t++) {
                    if (finger[id][t] != best_shape[t]) { same = false; break; }
                }
                if (same) {
                    found = true;
                    // 相似星座复用第 id 个字母，把刚才写的字母改回去
                    for (ll t = 0; t < star_cnt; t++) {
                        grid[star_r[t]][star_c[t]] = 'a' + id;
                    }
                    break;
                }
            }
            if (!found) {
                // 新形状：保存指纹，字母保持 'a'+finger_cnt 不变
                finger_len[finger_cnt] = star_cnt;
                for (ll t = 0; t < star_cnt; t++) finger[finger_cnt][t] = best_shape[t];
                finger_cnt++;
            }
        }
    }

    for (ll i = 0; i < H; i++) {
        printf("%s\n", grid[i]);
    }
    return 0;
}
