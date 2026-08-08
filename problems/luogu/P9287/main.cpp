#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;

int n, p;
int a[MAXN][MAXN];     // a[i][k] 表示在细胞 i 心中第 k 强的病毒编号
int rk[MAXN][MAXN];    // rk[i][v] 表示病毒 v 在细胞 i 心中的排名，1 表示最强
int best_pos[MAXN][MAXN]; // best_pos[j][x]：在细胞 x 心中比 x 强的病毒里，它们在细胞 j 心中的最靠后排名

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int k = 1; k <= n; k++) {
            cin >> a[i][k];
            rk[i][a[i][k]] = k;
        }
    }
    cin >> p;

    // 预处理 best_pos[j][x]。
    // 枚举“被消灭的病毒 x”，以及在细胞 x 心中比它更强的病毒 y，
    // 再看这些 y 在目标细胞 j 心中的最大排名是多少。
    for (int x = 1; x <= n; x++) {
        for (int pos = 1; pos < rk[x][x]; pos++) {
            int y = a[x][pos];
            for (int j = 1; j <= n; j++) {
                best_pos[j][x] = max(best_pos[j][x], rk[j][y]);
            }
        }
    }

    vector<int> ans;

    if (p == 1) {
        // 稳定病毒：自己在自己家里就是最强。
        for (int i = 1; i <= n; i++) {
            if (a[i][1] == i) {
                ans.push_back(i);
            }
        }
    } else {
        // 可行病毒：枚举病毒 i，再枚举它最终停留的细胞 j。
        for (int i = 1; i <= n; i++) {
            bool alive = false;

            for (int j = 1; j <= n && !alive; j++) {
                // 病毒 i 至少要有机会感染到细胞 j。
                if (rk[j][i] > rk[j][j]) {
                    continue;
                }

                int pos_i = rk[j][i];
                bool ok = true;

                // 在细胞 j 心中比 i 更强的每个病毒 x，都必须能够被某个“安全病毒”杀掉。
                for (int pos = 1; pos < pos_i; pos++) {
                    int x = a[j][pos];
                    if (best_pos[j][x] < pos_i) {
                        ok = false;
                        break;
                    }
                }

                if (ok) {
                    alive = true;
                }
            }

            if (alive) {
                ans.push_back(i);
            }
        }
    }

    cout << ans.size() << '\n';
    for (int idx = 0; idx < (int)ans.size(); idx++) {
        if (idx) {
            cout << ' ';
        }
        cout << ans[idx];
    }
    cout << '\n';

    return 0;
}
