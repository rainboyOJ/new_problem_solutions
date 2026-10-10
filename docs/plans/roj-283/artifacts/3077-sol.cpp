#include <cstdio>
#include <cstring>

const int N = 30;
int n;
char s[3][N];
int q[N], path[N];
bool st[N];

// 校验：从最低位往高位，只要某列三字母都已确定就检查
// t = 进入该列的进位；t == -1 表示进位未知（低位有未确定的列）
bool check() {
    for (int i = n - 1, t = 0; i >= 0; i--) {
        int a = path[s[0][i] - 'A'], b = path[s[1][i] - 'A'], c = path[s[2][i] - 'A'];
        if (a != -1 && b != -1 && c != -1) {
            if (t == -1) {
                // ★ 进位未知：进位 0 或 1 任一成立即可（原版只试 0 => 误杀合法状态）
                bool ok0 = ((a + b) % n == c);
                bool ok1 = ((a + b + 1) % n == c);
                if (!ok0 && !ok1) return false;
                // 最高位：不允许产生进位
                if (i == 0) {
                    if (!((a + b == c) || (a + b + 1 == c))) return false;
                }
            } else {
                if ((a + b + t) % n != c) return false;
                if (i == 0 && a + b + t >= n) return false;   // 最高位不能有进位
                t = (a + b + t) / n;
            }
        } else {
            t = -1;
        }
    }
    return true;
}

bool dfs(int u) {
    if (u == n) return true;
    for (int i = n - 1; i >= 0; i--) {
        if (!st[i]) {
            st[i] = true;
            path[q[u]] = i;
            if (check() && dfs(u + 1)) return true;
            st[i] = false;
            path[q[u]] = -1;
        }
    }
    return false;
}

int main() {
    if (scanf("%d", &n) != 1) return 0;
    memset(path, -1, sizeof path);
    for (int i = 0; i < 3; i++) scanf("%s", s[i]);
    int k = 0;
    bool seen[N]; memset(seen, 0, sizeof seen);
    for (int i = n - 1; i >= 0; i--)
        for (int j = 0; j < 3; j++) {
            int c = s[j][i] - 'A';
            if (!seen[c]) { seen[c] = true; q[k++] = c; }
        }
    memset(st, false, sizeof st);
    dfs(0);
    for (int i = 0; i < n; i++) printf("%d%c", path[i], " \n"[i == n - 1]);
    return 0;
}
