/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:36
 * update_at: 2026-10-06 10:36
 */
#include <cstdio>
#include <vector>
#include <map>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 105;   // 篱笆段数上限
const int MAXV = 205;   // 端点数量上限：每段篱笆两端，去重后不超过 2*N
const ll INF = (ll)1e18; // “走不到”的哨兵，篱笆总长远小于它

int n;                          // 篱笆段数
int m;                          // 去重后的端点数
int fence_u[MAXN];              // 第 i 段篱笆一端的端点编号
int fence_v[MAXN];              // 第 i 段篱笆另一端的端点编号
ll fence_len[MAXN];             // 第 i 段篱笆的长度
vector<int> adj[MAXV];          // adj[x] 存以 x 为一端的篱笆编号
map<vector<int>, int> vertex_id; // 端点身份（该端点上全部篱笆标号的有序集合）-> 端点编号

ll dist_arr[MAXV];              // Dijkstra 的距离表：dist_arr[x] 为当前起点到 x 的最短长度
bool used[MAXV];                // used[x] 表示 x 的最短路已确定

// 把端点身份映射成编号，没有见过就新建一个。
int get_vertex(const vector<int> &key) {
    map<vector<int>, int>::iterator it = vertex_id.find(key);
    if (it != vertex_id.end()) {
        return it->second;
    }
    vertex_id[key] = m;
    m = m + 1;
    return m - 1;
}

// 禁掉 banned 号篱笆后，从 start 沿至少一条篱笆走到 goal 的最短长度，走不到返回 INF。
// 起点先迈一条边再入堆，所以 start == goal（某段篱笆两端落在同一端点）时得到的是真实回路，而不是空路。
ll dijkstra(int start, int goal, int banned) {
    int i;
    for (i = 0; i < m; i++) {
        dist_arr[i] = INF;
        used[i] = false;
    }

    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > pq;
    for (i = 0; i < (int)adj[start].size(); i++) {
        int e = adj[start][i];
        if (e == banned) {
            continue;
        }
        int y = fence_u[e] + fence_v[e] - start; // 篱笆的另一端
        if (fence_len[e] < dist_arr[y]) {
            dist_arr[y] = fence_len[e];
            pq.push(make_pair(fence_len[e], y));
        }
    }

    while (!pq.empty()) {
        pair<ll, int> top = pq.top();
        pq.pop();
        ll d = top.first;
        int x = top.second;
        if (used[x]) {
            continue;
        }
        used[x] = true;
        if (x == goal) {
            return d;
        }
        for (i = 0; i < (int)adj[x].size(); i++) {
            int e = adj[x][i];
            if (e == banned) {
                continue;
            }
            int y = fence_u[e] + fence_v[e] - x; // 篱笆的另一端
            if (d + fence_len[e] < dist_arr[y]) {
                dist_arr[y] = d + fence_len[e];
                pq.push(make_pair(dist_arr[y], y));
            }
        }
    }
    return INF;
}

int main() {
    int i;
    int j;

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        int s;
        int length;
        int left_count;
        int right_count;
        scanf("%d %d %d %d", &s, &length, &left_count, &right_count);
        fence_len[i] = length;

        // 题面只给相接关系，不给坐标：把“该端点上全部篱笆的标号集合”当作端点身份。
        vector<int> left_key;
        left_key.push_back(s);
        for (j = 0; j < left_count; j++) {
            int label;
            scanf("%d", &label);
            left_key.push_back(label);
        }
        vector<int> right_key;
        right_key.push_back(s);
        for (j = 0; j < right_count; j++) {
            int label;
            scanf("%d", &label);
            right_key.push_back(label);
        }
        sort(left_key.begin(), left_key.end());
        sort(right_key.begin(), right_key.end());

        fence_u[i] = get_vertex(left_key);
        fence_v[i] = get_vertex(right_key);
        adj[fence_u[i]].push_back(i);
        adj[fence_v[i]].push_back(i);
    }

    // 每条篱笆轮流充当回路的一环：禁掉它，两端点之间的最短路就是回路剩下的部分。
    ll answer = INF;
    for (i = 1; i <= n; i++) {
        ll rest = dijkstra(fence_u[i], fence_v[i], i);
        if (rest < INF) {
            ll candidate = fence_len[i] + rest;
            if (candidate < answer) {
                answer = candidate;
            }
        }
    }
    printf("%lld\n", answer);
    return 0;
}
