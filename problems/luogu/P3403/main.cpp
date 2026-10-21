/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-17 01:40
 * update_at: 2026-10-21 09:10
 */
// 跳楼机：从 1 楼出发，每次可向上跳 x/y/z 层，统计不超过 h 的可达楼层数。
// h 可达 2^63-1，逐层标记不可行；但三个步长都 <= 1e5，所以该压缩的维度是"楼层"。
// 取最小步长 base，把所有楼层按模 base 的余数分成 base 个等价类（商集 Z/baseZ）。
// 同一类里一旦能到 L，则 L+base、L+2base 也都能到——前提是 base 本身是合法步长。
// 所以每类只需知道最早可达楼层 dist[r]，其余全部由「加 base」生成。
// 把一步 s 作用到余数上是平移 r -> (r+s) mod base，它在 Z_base 里封闭，
// 于是整张图就是循环群关于生成集 {x mod base, y mod base, z mod base} 的 Cayley 图：
// 点 base 个、每点 3 条出边，与 h 的规模完全无关。在此基础上跑 Dijkstra 求 dist。
// 最后每类贡献 floor((h-dist[r])/base)+1 层；同余分类是划分，按类求和不会重复。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXB = 100000 + 5;  // base = min(x,y,z) <= 1e5

ll h;                 // 楼层上限，可达 2^63-1
int step[3];          // 三个步长 x, y, z
int base_len;         // base = min(step)，同时是余数类数量
ll dist_arr[MAXB];    // dist_arr[r]：模 base 余 r 这一类里的最早可达楼层

const ll INF = (1LL << 62);

void dijkstra() {
    for (int r = 0; r < base_len; r++) dist_arr[r] = INF;

    // 起点是 1 楼，不是 0：楼层从 1 开始，1 本身可达
    int start = 1 % base_len;
    dist_arr[start] = 1;

    // (楼层, 余数) 的小根堆
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> heap;
    heap.push({1, start});

    while (!heap.empty()) {
        ll current = heap.top().first;
        int residue = heap.top().second;
        heap.pop();

        if (current != dist_arr[residue]) continue;  // 堆里的过期记录

        for (int i = 0; i < 3; i++) {
            int s = step[i];
            int next_residue = (residue + s) % base_len;
            ll candidate = current + s;
            if (candidate < dist_arr[next_residue]) {
                dist_arr[next_residue] = candidate;
                heap.push({candidate, next_residue});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> h;
    for (int i = 0; i < 3; i++) cin >> step[i];

    base_len = min(step[0], min(step[1], step[2]));

    dijkstra();

    // 每个余数类独立贡献：最早可达楼层之后，每加一次 base 仍可达
    ll answer = 0;
    for (int r = 0; r < base_len; r++) {
        if (dist_arr[r] <= h) {
            answer += (h - dist_arr[r]) / base_len + 1;
        }
    }

    cout << answer << '\n';
    return 0;
}
