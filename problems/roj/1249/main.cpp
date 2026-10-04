/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:55
 * update_at: 2026-10-05 06:55
 */
#include <cstdio>

typedef long long ll;

const int MAXN = 115;

char grid[MAXN][MAXN];    // grid[1..n][1..m]：'W' 有水、'.' 干燥；访问过的 'W' 就地改成 '.' 当访问标记
int stack_r[MAXN * MAXN]; // 洪泛栈的行坐标，每格最多入栈一次，容量 n*m 足够
int stack_c[MAXN * MAXN]; // 洪泛栈的列坐标

ll n, m;

int main() {
    scanf("%lld %lld", &n, &m);
    for (ll i = 1; i <= n; i++) {
        scanf("%s", grid[i] + 1);
    }

    ll ponds = 0;
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= m; j++) {
            if (grid[i][j] != 'W') {
                continue;
            }
            ponds++; // 遇到一个还没被洪泛吞掉的水格，就是一片新水洼
            // 迭代洪泛：栈里放待扩展的格子坐标
            ll top = 0;
            grid[i][j] = '.'; // 入栈前就标记，保证每个水格最多入栈一次
            stack_r[top] = i;
            stack_c[top] = j;
            top++;
            while (top > 0) {
                top--;
                ll r = stack_r[top];
                ll c = stack_c[top];
                // 八连通：行、列偏移各取 -1,0,1，排除 (0,0)
                for (ll dr = -1; dr <= 1; dr++) {
                    for (ll dc = -1; dc <= 1; dc++) {
                        if (dr == 0 && dc == 0) {
                            continue;
                        }
                        ll nr = r + dr;
                        ll nc = c + dc;
                        if (nr < 1 || nr > n || nc < 1 || nc > m) {
                            continue;
                        }
                        if (grid[nr][nc] != 'W') {
                            continue;
                        }
                        grid[nr][nc] = '.';
                        stack_r[top] = nr;
                        stack_c[top] = nc;
                        top++;
                    }
                }
            }
        }
    }

    printf("%lld\n", ponds);
    return 0;
}
