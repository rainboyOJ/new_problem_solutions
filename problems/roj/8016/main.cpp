/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 17:02
 * update_at: 2026-10-06 17:02
 */

#include <cstdio>
#include <string>
#include <stack>
using namespace std;

typedef long long ll;

const int MAXN = 105;   // 行数上限
const int MAXM = 205;   // 每行字符数上限

int n;                          // 地图行数
int len[MAXN];                  // len[i] 表示第 i 行实际存了几个字符
char grid[MAXN][MAXM];          // grid[i][j] 存地图字符，下标从 0 开始
bool vis[MAXN][MAXM];           // vis[i][j] 表示该字母格是否已被染过色

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

// 洪水填充：从 (r, c) 出发把整个家族的字母格都标记成已访问
// 用显式栈写成迭代 DFS，避免长链递归爆栈
void flood(int r, int c) {
    stack< pair<int, int> > st;
    st.push(make_pair(r, c));
    vis[r][c] = true;   // 入栈前先标记，防止重复入栈

    while (!st.empty()) {
        int x = st.top().first;
        int y = st.top().second;
        st.pop();

        // 枚举上下左右四个方向的字母格
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx < 0 || nx >= n || ny < 0 || ny >= len[nx]) continue; // 越界（各行长度不同）
            if (vis[nx][ny]) continue;
            if (grid[nx][ny] < 'a' || grid[nx][ny] > 'z') continue;     // 只走字母格
            vis[nx][ny] = true;
            st.push(make_pair(nx, ny));
        }
    }
}

int main() {
    scanf("%d", &n);
    // getchar 吃掉数字后面的换行
    getchar();
    for (int i = 0; i < n; ++i) {
        // 用 fgets 逐行读入，保留行首空格（大海）
        fgets(grid[i], MAXM, stdin);
        len[i] = 0;
        // fgets 可能把末尾换行读进来，统一截掉
        while (grid[i][len[i]] != '\0' && grid[i][len[i]] != '\n' && grid[i][len[i]] != '\r') {
            ++len[i];
        }
        grid[i][len[i]] = '\0';
    }

    int ans = 0; // 家族数：每发现一个未访问的字母格就 +1
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < len[i]; ++j) {
            if (!vis[i][j] && grid[i][j] >= 'a' && grid[i][j] <= 'z') {
                ++ans;
                flood(i, j);
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}
