#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

const int MAXN = 100005;
int dist[MAXN]; // 记录到达每个位置所需的最少时间

int bfs(int n, int k) {
    // 特殊情况：农夫在牛后面，只能往回走
    if (n >= k) return n - k;

    queue<int> q;
    memset(dist, -1, sizeof(dist)); // -1 表示尚未访问

    q.push(n);
    dist[n] = 0;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        // 尝试三种移动方式
        int next_moves[3] = {curr - 1, curr + 1, curr * 2};

        for (int i = 0; i < 3; ++i) {
            int next = next_moves[i];

            // 检查边界及是否访问过
            if (next >= 0 && next < MAXN && dist[next] == -1) {
                dist[next] = dist[curr] + 1;
                
                // 找到目标，直接返回
                if (next == k) return dist[next];
                
                q.push(next);
            }
        }
    }
    return 0;
}

int main() {
    int n, k;
    while (cin >> n >> k) {
        cout << bfs(n, k) << endl;
    }
    return 0;
}
