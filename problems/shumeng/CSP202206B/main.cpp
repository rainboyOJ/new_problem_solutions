/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:40
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n;          // 树的数量
long long limit; // 绿化图大小 L
int s;       // 藏宝图大小 S
pair<long long, long long> tree[MAXN]; // 每棵树的坐标 (x, y)
bool map_value[55][55]; // 藏宝图：map[dx][dy] 表示相对左下角的偏移位置是否有树
int tree_count;  // 藏宝图中 1 的总数
int answer;      // 匹配的左下角候选个数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> limit >> s;
    for (int i = 0; i < n; i++) {
        cin >> tree[i].first >> tree[i].second;
    }

    // 藏宝图按从下往上逐行读入，所以先读最上面一行，再填到 map[0..s][0..s]
    // 这里把输入的第 s 行放到 map 的第 s 行，保证 map[dx][dy] 与坐标偏移一致
    for (int row = s; row >= 0; row--) {
        for (int col = 0; col <= s; col++) {
            cin >> map_value[row][col];
            if (map_value[row][col]) tree_count++;
        }
    }

    // 枚举每个树作为藏宝图左下角，检查该窗口内的树是否与藏宝图一致
    for (int i = 0; i < n; i++) {
        long long x = tree[i].first, y = tree[i].second;
        if (x + s > limit || y + s > limit) continue; // 窗口越出绿化图边界

        bool valid = true;
        int inside = 0; // 落在窗口内的树的数量
        for (int j = 0; j < n; j++) {
            long long tx = tree[j].first, ty = tree[j].second;
            if (tx < x || tx > x + s || ty < y || ty > y + s) continue;
            inside++;
            if (!map_value[tx - x][ty - y]) { // 窗口内有树但藏宝图对应位置为 0
                valid = false;
                break;
            }
        }
        // 窗口内树的数量必须恰好等于藏宝图中 1 的数量，
        // 这样藏宝图为 1 的位置也都一定有树。
        if (valid && inside == tree_count) answer++;
    }

    cout << answer << '\n';
    return 0;
}