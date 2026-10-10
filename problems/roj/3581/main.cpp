/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int FA[20005];
int REL[20005];   // 节点与父节点的仇敌关系：0 同监狱，1 不同监狱

int find(int x) {
    if (FA[x] == x) return x;
    int root = find(FA[x]);
    REL[x] ^= REL[FA[x]];
    FA[x] = root;
    return root;
}

struct Edge { ll c; int a, b; };
Edge edges[100005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        edges[i].a = a; edges[i].b = b; edges[i].c = c;
    }
    sort(edges, edges + m, [](const Edge& x, const Edge& y) { return x.c > y.c; });

    for (int i = 1; i <= n; i++) { FA[i] = i; REL[i] = 0; }

    for (int i = 0; i < m; i++) {
        int a = edges[i].a, b = edges[i].b;
        ll c = edges[i].c;
        int ra = find(a), rb = find(b);
        if (ra == rb) {
            if ((REL[a] ^ REL[b]) == 0) {
                cout << c << "\n";
                return 0;
            }
        } else {
            FA[ra] = rb;
            REL[ra] = REL[a] ^ REL[b] ^ 1;
        }
    }
    cout << "0\n";
    return 0;
}
