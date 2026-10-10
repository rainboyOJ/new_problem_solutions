/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 婚礼：2-SAT（每对情侣选「开始段」或「结束段」），迭代式 Tarjan 求强连通分量
#include <cstdio>
#include <vector>
using namespace std;

const int START = 1; // 取值 1 = 仪式安排在婚礼开始时，0 = 安排在结束时

int size_v, timer, groups;
vector<vector<int> > g;
vector<int> index_, low, comp;
vector<char> on_stack;
vector<int> stk;

// 把 hh:mm 转成当天的分钟数
int to_minutes(const char* s) {
    int h = (s[0] - '0') * 10 + (s[1] - '0');
    int m = (s[3] - '0') * 10 + (s[4] - '0');
    return h * 60 + m;
}

// 迭代式 Tarjan：返回每个点的强连通分量编号（按出栈先后递增）
void tarjan() {
    index_.assign(size_v, 0);
    low.assign(size_v, 0);
    comp.assign(size_v, -1);
    on_stack.assign(size_v, 0);
    timer = 0;
    groups = 0;
    for (int root = 0; root < size_v; root++) {
        if (index_[root]) {
            continue;
        }
        vector<int> wn, wp; // (当前点, 下一个待访问的邻居下标)
        wn.push_back(root);
        wp.push_back(0);
        while (!wn.empty()) {
            int node = wn.back();
            int pos = wp.back();
            if (pos == 0) { // 第一次进入这个点
                timer++;
                index_[node] = low[node] = timer;
                stk.push_back(node);
                on_stack[node] = 1;
            }
            bool descended = false;
            while (pos < (int)g[node].size()) {
                int nx = g[node][pos];
                pos++;
                if (index_[nx] == 0) {
                    wp.back() = pos; // 记下进度，回来时从这个邻居继续
                    wn.push_back(nx);
                    wp.push_back(0);
                    descended = true;
                    break;
                }
                if (on_stack[nx] && index_[nx] < low[node]) {
                    low[node] = index_[nx];
                }
            }
            if (descended) {
                continue;
            }
            if (low[node] == index_[node]) { // 这个点是所在分量的根
                while (true) {
                    int top = stk.back();
                    stk.pop_back();
                    on_stack[top] = 0;
                    comp[top] = groups;
                    if (top == node) {
                        break;
                    }
                }
                groups++;
            }
            wn.pop_back();
            wp.pop_back();
            if (!wn.empty()) { // 回溯：子节点的 low 可以传回父节点
                int parent = wn.back();
                if (low[node] < low[parent]) {
                    low[parent] = low[node];
                }
            }
        }
    }
}

// 分钟数还原成 hh:mm（向下取整，与 Python 的 // 一致）
void print_stamp(int minute) {
    int h = minute / 60, m = minute % 60;
    if (m < 0) {
        m += 60;
        h -= 1;
    }
    printf("%02d:%02d", h, m);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return 0;
    }
    vector<int> bs(n), bt(n), bd(n); // 每对情侣的 S_i, T_i, D_i
    for (int i = 0; i < n; i++) {
        char s[16], t[16];
        int d;
        scanf("%15s %15s %d", s, t, &d);
        bs[i] = to_minutes(s);
        bt[i] = to_minutes(t);
        bd[i] = d;
    }
    // 取值 1：S_i ~ S_i+D_i；取值 0：T_i-D_i ~ T_i
    vector<int> ea(2 * n), eb(2 * n);
    for (int i = 0; i < n; i++) {
        ea[2 * i + START] = bs[i];
        eb[2 * i + START] = bs[i] + bd[i];
        ea[2 * i + 0] = bt[i] - bd[i];
        eb[2 * i + 0] = bt[i];
    }

    size_v = 2 * n;
    g.assign(size_v, vector<int>());
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int vi = 1; vi >= 0; vi--) {
                int a1 = ea[2 * i + vi], b1 = eb[2 * i + vi];
                for (int vj = 1; vj >= 0; vj--) {
                    int a2 = ea[2 * j + vj], b2 = eb[2 * j + vj];
                    if (a1 < b2 && a2 < b1) { // 两段仪式真的重叠，这组取值不允许
                        g[2 * i + vi].push_back(2 * j + 1 - vj);
                        g[2 * j + vj].push_back(2 * i + 1 - vi);
                    }
                }
            }
        }
    }

    tarjan();

    vector<int> outa, outb;
    bool ok = true;
    for (int i = 0; i < n; i++) {
        if (comp[2 * i] == comp[2 * i + 1]) { // x 与 ¬x 同分量：无解
            ok = false;
            break;
        }
        // 分量编号是弹栈顺序，编号小的一侧在缩点图里更靠后
        int chosen = (comp[2 * i + START] < comp[2 * i]) ? START : 0;
        outa.push_back(ea[2 * i + chosen]);
        outb.push_back(eb[2 * i + chosen]);
    }
    if (!ok) {
        printf("NO\n");
        return 0;
    }
    printf("YES\n");
    for (int i = 0; i < n; i++) {
        print_stamp(outa[i]);
        printf(" ");
        print_stamp(outb[i]);
        printf("\n");
    }
    return 0;
}
