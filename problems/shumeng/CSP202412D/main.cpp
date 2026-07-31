/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 02:19
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
int a[MAXN];
long long k[MAXN];
int distance_to[MAXN];
int next_unused[MAXN];

int find_next(int x) {
    int root = x;
    while (next_unused[root] != root) root = next_unused[root];
    while (next_unused[x] != x) {
        int next = next_unused[x];
        next_unused[x] = root;
        x = next;
    }
    return root;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> k[i];

    for (int i = 1; i <= n; i++) distance_to[i] = -1;
    for (int i = 2; i <= n + 1; i++) next_unused[i] = i;

    queue<int> states;
    distance_to[1] = 0;
    states.push(1);

    while (!states.empty()) {
        int current = states.front();
        states.pop();

        long long right = min((long long)n, current + k[current]);
        int landing = find_next(current + 1);
        while (landing <= right) {
            // 落点 landing 只保留第一次被某个最短路状态扫描的机会。
            next_unused[landing] = find_next(landing + 1);
            int next_state = landing - a[landing];
            if (distance_to[next_state] == -1) {
                distance_to[next_state] = distance_to[current] + 1;
                states.push(next_state);
            }
            landing = find_next(landing);
        }
    }

    cout << distance_to[n] << '\n';
    return 0;
}
