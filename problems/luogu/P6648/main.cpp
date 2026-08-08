#include <bits/stdc++.h>
using namespace std;

const int MAXK = 3005;
const int BUF_SIZE = 1 << 20;

struct FastIO {
    char buf[BUF_SIZE];
    int pos, len;

    FastIO() {
        pos = 0;
        len = 0;
    }

    inline int gc() {
        if (pos == len) {
            len = fread(buf, 1, BUF_SIZE, stdin);
            pos = 0;
            if (len == 0) {
                return EOF;
            }
        }
        return buf[pos++];
    }

    template <typename T>
    inline void read(T &x) {
        x = 0;
        int sign = 1;
        int c = gc();
        while (c != '-' && (c < '0' || c > '9')) {
            c = gc();
        }
        if (c == '-') {
            sign = -1;
            c = gc();
        }
        while (c >= '0' && c <= '9') {
            x = x * 10 + c - '0';
            c = gc();
        }
        x *= sign;
    }
} io;

struct Node {
    int type;           // 0: 正三角形, 1: 倒三角形
    int s;              // 当前三角形的边长
    int m;              // 可用坐标满足 x + y <= m
    int p, d, t;        // 递推参数
    int dep1;           // 同方向的较小三角形
    int dep2;           // 中间补的反向三角形，不存在时为 -1
    int use_count;      // 还有多少父状态会用到我
    int *data;          // 这一层所有位置的最大值
};

int n, k;
int down_id[MAXK];
int up_id[MAXK];
vector<Node> nodes;

inline int triangle_size(int m) {
    return (m + 1) * (m + 2) / 2;
}

inline int row_start(int m, int x) {
    return x * (m + 1) - x * (x - 1) / 2;
}

inline int highest_power_less_than(int x) {
    int p = 1;
    while ((p << 1) < x) {
        p <<= 1;
    }
    return p;
}

int build_node(int type, int s) {
    int &slot = (type == 0 ? down_id[s] : up_id[s]);
    if (slot != -1) {
        return slot;
    }

    Node node;
    node.type = type;
    node.s = s;
    node.m = (type == 0 ? n - s : n - 2 * s + 1);
    node.p = node.d = node.t = 0;
    node.dep1 = node.dep2 = -1;
    node.use_count = 0;
    node.data = nullptr;

    int id = (int)nodes.size();
    nodes.push_back(node);
    slot = id;

    if (s == 1) {
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

void build_base_layer(const vector<int> &base) {
    int base_id_down = down_id[1];
    if (base_id_down != -1) {
        int sz = triangle_size(n - 1);
        nodes[base_id_down].data = new int[sz];
        memcpy(nodes[base_id_down].data, &base[0], sizeof(int) * sz);
    }

    int base_id_up = up_id[1];
    if (base_id_up != -1) {
        int sz = triangle_size(n - 1);
        nodes[base_id_up].data = new int[sz];
        memcpy(nodes[base_id_up].data, &base[0], sizeof(int) * sz);
    }
}

void free_node_if_unused(int id, int root_id) {
    if (id == -1 || id == root_id) {
        return;
    }
    if (nodes[id].use_count == 0 && nodes[id].data != nullptr) {
        delete[] nodes[id].data;
        nodes[id].data = nullptr;
    }
}

void compute_down(int id) {
    Node &cur = nodes[id];
    Node &same = nodes[cur.dep1];
    int *a = same.data;

    int total = triangle_size(cur.m);
    cur.data = new int[total];

    if (cur.dep2 == -1) {
        for (int x = 0; x <= cur.m; x++) {
            int len = cur.m - x + 1;
            int cur_row = row_start(cur.m, x);
            int row1 = row_start(same.m, x);
            int row2 = row_start(same.m, x + cur.d);
            for (int y = 0; y < len; y++) {
                int v1 = a[row1 + y];
                int v2 = a[row2 + y];
                int v3 = a[row1 + y + cur.d];
                cur.data[cur_row + y] = max(v1, max(v2, v3));
            }
        }
        return;
    }

    Node &other = nodes[cur.dep2];
    int *b = other.data;

    for (int x = 0; x <= cur.m; x++) {
        int len = cur.m - x + 1;
        int cur_row = row_start(cur.m, x);
        int row1 = row_start(same.m, x);
        int row2 = row_start(same.m, x + cur.d);
        int row4 = row_start(other.m, x + cur.d - cur.t);
        for (int y = 0; y < len; y++) {
            int v1 = a[row1 + y];
            int v2 = a[row2 + y];
            int v3 = a[row1 + y + cur.d];
            int v4 = b[row4 + y + cur.d - cur.t];
            cur.data[cur_row + y] = max(max(v1, v2), max(v3, v4));
        }
    }
}

void compute_up(int id) {
    Node &cur = nodes[id];
    Node &same = nodes[cur.dep1];
    int *a = same.data;

    int total = triangle_size(cur.m);
    cur.data = new int[total];

    if (cur.dep2 == -1) {
        for (int x = 0; x <= cur.m; x++) {
            int len = cur.m - x + 1;
            int cur_row = row_start(cur.m, x);
            int row1 = row_start(same.m, x + cur.d);
            int row3 = row_start(same.m, x);
            for (int y = 0; y < len; y++) {
                int v1 = a[row1 + y + cur.d];
                int v2 = a[row1 + y];
                int v3 = a[row3 + y + cur.d];
                cur.data[cur_row + y] = max(v1, max(v2, v3));
            }
        }
        return;
    }

    Node &other = nodes[cur.dep2];
    int *b = other.data;

    for (int x = 0; x <= cur.m; x++) {
        int len = cur.m - x + 1;
        int cur_row = row_start(cur.m, x);
        int row1 = row_start(same.m, x + cur.d);
        int row3 = row_start(same.m, x);
        int row4 = row_start(other.m, x + cur.p);
        for (int y = 0; y < len; y++) {
            int v1 = a[row1 + y + cur.d];
            int v2 = a[row1 + y];
            int v3 = a[row3 + y + cur.d];
            int v4 = b[row4 + y + cur.p];
            cur.data[cur_row + y] = max(max(v1, v2), max(v3, v4));
        }
    }
}

int main() {
    memset(down_id, -1, sizeof(down_id));
    memset(up_id, -1, sizeof(up_id));

    io.read(n);
    io.read(k);

    int base_m = n - 1;
    vector<int> base(triangle_size(base_m));

    // 读入时把普通的“按行编号”转成两轴坐标 (x, y)。
    // 原三角形第 i 行第 j 个数，对应坐标：
    // x = j - 1, y = i - j
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            int x = j - 1;
            int y = i - j;
            int value;
            io.read(value);
            base[row_start(base_m, x) + y] = value;
        }
    }

    int root_id = build_node(0, k);
    build_base_layer(base);
    vector<int>().swap(base);

    vector<int> order;
    order.reserve(nodes.size());
    for (int i = 0; i < (int)nodes.size(); i++) {
        order.push_back(i);
    }
    sort(order.begin(), order.end(), [](int lhs, int rhs) {
        if (nodes[lhs].s != nodes[rhs].s) {
            return nodes[lhs].s < nodes[rhs].s;
        }
        return nodes[lhs].type < nodes[rhs].type;
    });

    for (int id : order) {
        if (nodes[id].s == 1) {
            continue;
        }

        if (nodes[id].type == 0) {
            compute_down(id);
        }
        else {
            compute_up(id);
        }

        nodes[nodes[id].dep1].use_count--;
        free_node_if_unused(nodes[id].dep1, root_id);

        if (nodes[id].dep2 != -1) {
            nodes[nodes[id].dep2].use_count--;
            free_node_if_unused(nodes[id].dep2, root_id);
        }
    }

    long long answer = 0;
    int total = triangle_size(nodes[root_id].m);
    for (int i = 0; i < total; i++) {
        answer += nodes[root_id].data[i];
    }

    printf("%lld\n", answer);

    for (int i = 0; i < (int)nodes.size(); i++) {
        if (nodes[i].data != nullptr) {
            delete[] nodes[i].data;
            nodes[i].data = nullptr;
        }
    }
    return 0;
}
