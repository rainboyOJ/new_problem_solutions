/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-30 17:12
 * update_at: 2026-10-30 17:15
 */
// main2.cpp：P6648 解法二（备选），正/倒三角形 DAG 分解 + 引用计数即时释放。
// 与 main.cpp 的区别：一次性把边长 k 的整张表建出来，补空隙靠倒三角形，
// 代价是同时要持有好几张 O(n^2) 的表。k 很小时时间略优，但内存峰值高。
// 时间 O(n^2 log k)，空间 O(n^2)；n = 3000、k = 3000 时峰值约 242 MB。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXK = 3005;   // n、k 的上限
const int MAXNODE = 64;  // 用到的 (方向, 边长) 组合只有 O(log k) 个，64 够用

// 一个节点就是一张「指定方向、指定边长」的表。
// 正三角形和倒三角形的递推左右对称，所以用 type 区分方向，两套递推各写一份。
struct Node {
    int type;          // 0 正三角形，1 倒三角形
    int s;             // 边长
    int m;             // 坐标满足 x + y <= m，这一层共有 m + 1 行
    int p;             // 不超过 s 的最大 2 的幂
    int d;             // d = s - p
    int t;             // t = 2d - p - 1，中间补的倒三角形边长；<= 0 表示不需要
    int dep1;          // 同方向的较小块，边长 p
    int dep2;          // 中间补的反向块，边长 t；-1 表示没有
    int use_count;     // 还有几个父节点要用这张表，归零就可以释放内存
    vector<int> data;  // 这一层所有位置上的最大值
};

Node nodes[MAXNODE];  // 节点池，编号从 0 开始
int node_cnt;         // 已经建了几个节点

int down_id[MAXK];  // down_id[s]：边长 s 的正三角形的节点编号，-1 表示还没建
int up_id[MAXK];    // up_id[s]：边长 s 的倒三角形的节点编号

int n, k;  // 三角形大小、要求的子三角形边长；都不超过 3000，只当长度和下标用

// 边长 m + 1 的三角形一共有多少个位置
int triangle_size(int m) {
    return (m + 1) * (m + 2) / 2;
}

// 第 x 行第 0 个数在打包后的一维表里的起点
int row_start(int m, int x) {
    return x * (m + 1) - x * (x - 1) / 2;
}

// 不超过 x 的最大 2 的幂
int highest_power_less_than(int x) {
    int p = 1;
    while ((p << 1) < x) {
        p <<= 1;
    }
    return p;
}

// 建出 (方向 type, 边长 s) 这个节点，并递归建好它依赖的节点；已经建过就直接返回编号
int build_node(int type, int s) {
    int &slot = (type == 0 ? down_id[s] : up_id[s]);
    if (slot != -1) {
        return slot;
    }

    int id = node_cnt;
    node_cnt++;
    slot = id;

    nodes[id].type = type;
    nodes[id].s = s;
    nodes[id].m = (type == 0 ? n - s : n - 2 * s + 1);
    nodes[id].p = 0;
    nodes[id].d = 0;
    nodes[id].t = 0;
    nodes[id].dep1 = -1;
    nodes[id].dep2 = -1;
    nodes[id].use_count = 0;

    if (s == 1) {  // 边长 1 直接就是原始数据
        return id;
    }

    nodes[id].p = highest_power_less_than(s);
    nodes[id].d = s - nodes[id].p;
    nodes[id].t = 2 * nodes[id].d - nodes[id].p - 1;

    nodes[id].dep1 = build_node(type, nodes[id].p);
    nodes[nodes[id].dep1].use_count++;

    if (nodes[id].t > 0) {
        nodes[id].dep2 = build_node(type ^ 1, nodes[id].t);
        nodes[nodes[id].dep2].use_count++;
    }
    return id;
}

// 把节点的表清空，真正把内存还给系统
void release_node(int id) {
    nodes[id].data = vector<int>();
}

// 正三角形：3 个边长 p 的同向块盖住三个角，中间那块倒三角空隙用 dep2 补
void compute_down(int id) {
    Node &cur = nodes[id];
    Node &same = nodes[cur.dep1];
    const vector<int> &a = same.data;

    cur.data.assign(triangle_size(cur.m), 0);

    if (cur.dep2 == -1) {
        for (int x = 0; x <= cur.m; x++) {
            int len = cur.m - x + 1;
            int cur_row = row_start(cur.m, x);
            int row1 = row_start(same.m, x);
            int row2 = row_start(same.m, x + cur.d);
            for (int y = 0; y < len; y++) {
                int best = max(a[row1 + y], a[row2 + y]);
                best = max(best, a[row1 + y + cur.d]);
                cur.data[cur_row + y] = best;
            }
        }
        return;
    }

    Node &other = nodes[cur.dep2];
    const vector<int> &b = other.data;

    for (int x = 0; x <= cur.m; x++) {
        int len = cur.m - x + 1;
        int cur_row = row_start(cur.m, x);
        int row1 = row_start(same.m, x);
        int row2 = row_start(same.m, x + cur.d);
        int row4 = row_start(other.m, x + cur.d - cur.t);
        for (int y = 0; y < len; y++) {
            int best = max(a[row1 + y], a[row2 + y]);
            best = max(best, a[row1 + y + cur.d]);
            best = max(best, b[row4 + y + cur.d - cur.t]);
            cur.data[cur_row + y] = best;
        }
    }
}

// 倒三角形：和 compute_down 左右对称，只是三块的位置换成倒三角的三个角
void compute_up(int id) {
    Node &cur = nodes[id];
    Node &same = nodes[cur.dep1];
    const vector<int> &a = same.data;

    cur.data.assign(triangle_size(cur.m), 0);

    if (cur.dep2 == -1) {
        for (int x = 0; x <= cur.m; x++) {
            int len = cur.m - x + 1;
            int cur_row = row_start(cur.m, x);
            int row1 = row_start(same.m, x + cur.d);
            int row3 = row_start(same.m, x);
            for (int y = 0; y < len; y++) {
                int best = max(a[row1 + y + cur.d], a[row1 + y]);
                best = max(best, a[row3 + y + cur.d]);
                cur.data[cur_row + y] = best;
            }
        }
        return;
    }

    Node &other = nodes[cur.dep2];
    const vector<int> &b = other.data;

    for (int x = 0; x <= cur.m; x++) {
        int len = cur.m - x + 1;
        int cur_row = row_start(cur.m, x);
        int row1 = row_start(same.m, x + cur.d);
        int row3 = row_start(same.m, x);
        int row4 = row_start(other.m, x + cur.p);
        for (int y = 0; y < len; y++) {
            int best = max(a[row1 + y + cur.d], a[row1 + y]);
            best = max(best, a[row3 + y + cur.d]);
            best = max(best, b[row4 + y + cur.p]);
            cur.data[cur_row + y] = best;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(down_id, -1, sizeof(down_id));
    memset(up_id, -1, sizeof(up_id));

    cin >> n >> k;

    int base_m = n - 1;
    vector<int> base(triangle_size(base_m));  // 原始数据，按 (x, y) 坐标打包成一维

    // 读入时把「第 i 行第 j 个」转成两轴坐标：x = j - 1，y = i - j
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            cin >> base[row_start(base_m, j - 1) + (i - j)];
        }
    }

    int root_id = build_node(0, k);

    // 边长 1 的节点直接就是原始数据，两种方向都可能被用到
    if (down_id[1] != -1) {
        nodes[down_id[1]].data = base;
    }
    if (up_id[1] != -1) {
        nodes[up_id[1]].data = base;
    }
    base = vector<int>();

    // 按边长从小到大递推。p 和 t 都严格小于 s，所以这个顺序本身就是拓扑序，
    // 不需要再排序。
    for (int s = 2; s <= k; s++) {
        for (int type = 0; type <= 1; type++) {
            int id = (type == 0 ? down_id[s] : up_id[s]);
            if (id == -1) {
                continue;
            }

            if (type == 0) {
                compute_down(id);
            }
            else {
                compute_up(id);
            }

            // 两个子节点各少一个用户；归零说明以后不会再读，立刻释放
            int dep1 = nodes[id].dep1;
            if (dep1 != -1 && --nodes[dep1].use_count == 0) {
                release_node(dep1);
            }
            int dep2 = nodes[id].dep2;
            if (dep2 != -1 && --nodes[dep2].use_count == 0) {
                release_node(dep2);
            }
        }
    }

    // 根节点存的就是边长 k 的三角形在每个位置上的最大值
    ll answer = 0;
    for (int value : nodes[root_id].data) {
        answer += value;
    }
    cout << answer << '\n';
    return 0;
}
