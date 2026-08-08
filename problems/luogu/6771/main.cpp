#include <bits/stdc++.h>
using namespace std;

struct Block {
    int h, a, c;
    bool operator<(const Block& o) const {
        return a < o.a;                  // 按最大高度限制升序排列
    }
};

const int MAXH = 40005;

int N;
Block b[405];
// dp[j] 表示高度 j 是否可达。
bool dp[MAXH];
// used[j] 记录在处理当前类型方块时，达到高度 j 已经用了几个该方块。
int used[MAXH];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> b[i].h >> b[i].a >> b[i].c;
    }
    sort(b, b + N);                      // 先处理最大高度限制低的方块

    dp[0] = true;
    for (int i = 0; i < N; i++) {
        int h = b[i].h, a = b[i].a, c = b[i].c;
        fill(used, used + a + 1, 0);     // 每种方块重新计数
        // 多重背包可行性，用 used 数组限制每种的用量。
        for (int j = h; j <= a; j++) {
            if (!dp[j] && dp[j - h] && used[j - h] < c) {
                dp[j] = true;
                used[j] = used[j - h] + 1;
            }
        }
    }

    // 从最大高度向下找第一个可达高度。
    for (int j = b[N - 1].a; j >= 0; j--) {
        if (dp[j]) {
            cout << j << '\n';
            break;
        }
    }
    return 0;
}
