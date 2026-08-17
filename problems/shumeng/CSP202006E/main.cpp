/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
const int MAXV = MAXN * 2 + 5;
const int MAXE = 500000;
const long long INF = (long long)4e18;

struct Edge {
    int to, next;
    long long flow;
};

int n, m, source, sink, edge_count = 1;
int head[MAXV], level[MAXV], current[MAXV];   // current 为当前弧优化指针
Edge edge[MAXE];

// 加一条 from -> to 容量为 flow 的边，并添加反向零容量边
void add_edge(int from, int to, long long flow) {
    edge[++edge_count] = {to, head[from], flow};
    head[from] = edge_count;
    edge[++edge_count] = {from, head[to], 0};
    head[to] = edge_count;
}

// BFS 分层，判断是否还有增广路
bool bfs() {
    queue<int> q;
    memset(level, -1, sizeof(level));
    level[source] = 0;
    q.push(source);
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int i = head[node]; i; i = edge[i].next) {
            if (edge[i].flow > 0 && level[edge[i].to] == -1) {
                level[edge[i].to] = level[node] + 1;
                q.push(edge[i].to);
            }
        }
    }
    return level[sink] != -1;
}

// DFS 沿分层图找增广路，limit 为当前允许通过的最大流量
long long dfs(int node, long long limit) {
    if (node == sink) return limit;
    for (int &i = current[node]; i; i = edge[i].next) {
        int to = edge[i].to;
        if (edge[i].flow == 0 || level[to] != level[node] + 1) continue;
        long long pushed = dfs(to, min(limit, edge[i].flow));
        if (pushed) {
            edge[i].flow -= pushed;
            edge[i ^ 1].flow += pushed;
            return pushed;
        }
    }
    return 0;
}

// 最大流 = 最小割
long long dinic() {
    long long result = 0, pushed;
    while (bfs()) {
        memcpy(current, head, sizeof(head));
        while ((pushed = dfs(source, INF)) != 0) result += pushed;
    }
    return result;
}

// 二次收益函数 a*x^2 + b*x + c
long long get_value(int a, int b, int c, long long x) {
    return 1LL * a * x * x + 1LL * b * x + c;
}

// 求开区间 (left, right) 内部整数点上的最大收益，对应"内部数量"选择
long long get_inner_best(int left, int right, int a, int b, int c) {
    long long answer = -(long long)4e18;
    long long candidates[4];
    candidates[0] = left + 1;
    candidates[1] = right - 1;
    candidates[2] = left + 1;
    candidates[3] = right - 1;
    if (a < 0) {
        // 开口向下时对称轴附近收益最大，检查对称轴两侧整数
        long long denominator = -2LL * a;
        long long numerator = b;
        long long floor_value = numerator >= 0 ? numerator / denominator : -((-numerator + denominator - 1) / denominator);
        candidates[2] = floor_value;
        candidates[3] = floor_value + 1;
    }
    for (int i = 0; i < 4; i++) {
        // 把候选点裁剪回开区间内部
        long long x = max((long long)left + 1, min((long long)right - 1, candidates[i]));
        answer = max(answer, get_value(a, b, c, x));
    }
    return answer;
}

// 给节点加权：正权点从源连入并累加总正权，负权点连向汇
void add_weight(int node, long long value, long long &sum) {
    if (value > 0) {
        add_edge(source, node, value);
        sum += value;
    } else if (value < 0) {
        add_edge(node, sink, -value);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    source = 2 * n + 1;
    sink = source + 1;
    long long positive_sum = 0;

    // 每种商品建两个节点：i 表示内部收益，i+n 表示切换到端点收益
    for (int i = 1; i <= n; i++) {
        int left, right, a, b, c;
        cin >> left >> right >> a >> b >> c;
        long long endpoint = max(get_value(a, b, c, left), get_value(a, b, c, right));
        long long inner = get_inner_best(left, right, a, b, c);
        add_weight(i, inner, positive_sum);
        add_weight(i + n, endpoint - inner, positive_sum);
        add_edge(i + n, i, INF);   // 强制：选端点必须连带选内部
    }

    // 依赖关系转成闭合图强制边
    for (int i = 1; i <= m; i++) {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 1) add_edge(y, x, INF);         // 买 y 必须先买 x
        else add_edge(y + n, x, INF);               // y 取端点时必须先买 x
    }

    // 最大权闭合子图答案 = 正权和 - 最小割
    cout << positive_sum - dinic() << '\n';

    return 0;
}