/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 21:00
 * update_at: 2026-10-09 21:00
 */
// main.cpp：扩展域（种类）并查集 + 连通块二选一背包 DP。
//   回答 yes ⇔ 询问者与被询问者同类；回答 no ⇔ 异类。
//   并查集把每个人拆成「天神态 x」与「恶魔态 x+V」两个节点，合并关系后
//   每个连通块被分成互斥的两侧，一侧为天神；背包统计凑出 p1 个天神的方案数，
//   方案数恰为 1 才唯一确定，否则（0 无解 / ≥2 多解）输出 no。

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXV = 605; // p1, p2 < 300 ⇒ 人数 V ≤ 598，两个状态域共 2*V

int parent_node[MAXV * 2]; // 扩展域并查集父节点：1..V 为天神态，V+1..2V 为恶魔态

// 路径压缩查找。
int find_set(int x) {
    if (parent_node[x] == x)
        return x;
    return parent_node[x] = find_set(parent_node[x]);
}

// 合并两个状态节点。
void union_sets(int a, int b) {
    int root_a = find_set(a);
    int root_b = find_set(b);
    if (root_a != root_b) {
        parent_node[root_a] = root_b;
    }
}

int dp[MAXV][MAXV]; // dp[i][j]：前 i 个连通块中选 j 个人当天的方案数（≥2 一律截到 2，只关心「是否唯一」）

void solve() {
    // n, p1, p2, x, y 的取值都远小于 int 上限（n < 1000，p1/p2 < 300），
    // 用 int 即可，避免给数组下标引入类型不匹配。
    int n, p1, p2;
    while (cin >> n >> p1 >> p2 && (n != 0 || p1 != 0 || p2 != 0)) {
        int V = p1 + p2;
        if (V == 0) {
            // 题面保证 p1+p2 ≥ x ≥ 1，故 n > 0 时 V 不可能为 0。
            // 这里兜底：仍把本组 n 行询问读完，避免多组输入错位；
            // 此时必有 p1 = 0（p1 + p2 = 0），无人可判 ⇒ 走正常路径会输出 "end"。
            for (int i = 0; i < n; ++i) {
                int x, y;
                string ans;
                cin >> x >> y >> ans;
            }
            cout << "end\n";
            continue;
        }

        for (int i = 1; i <= 2 * V; ++i) {
            parent_node[i] = i;
        }

        for (int i = 0; i < n; ++i) {
            int x, y;
            string ans;
            cin >> x >> y >> ans;
            if (ans == "yes") {
                union_sets(x, y);         // 同类：天神态合并、恶魔态合并
                union_sets(x + V, y + V);
            } else {
                union_sets(x, y + V);     // 异类：一方的天神态与另一方的恶魔态合并
                union_sets(x + V, y);
            }
        }

        bool possible = true;
        for (int i = 1; i <= V; ++i) {
            if (find_set(i) == find_set(i + V)) { // 同一人既天神又恶魔 ⇒ 自相矛盾
                possible = false;
                break;
            }
        }

        if (!possible) {
            cout << "no\n";
            continue;
        }

        // 收集连通块：每个块取出「块内 1 号人的天神态根」和「恶魔态根」一对。
        vector<int> roots;
        int comp_id[MAXV * 2];
        for (int i = 1; i <= 2 * V; ++i) {
            comp_id[i] = -1;
        }

        for (int i = 1; i <= V; ++i) {
            int r = find_set(i);
            if (comp_id[r] == -1) {
                comp_id[r] = roots.size();
                roots.push_back(r);
                int r_op = find_set(i + V);
                comp_id[r_op] = roots.size();
                roots.push_back(r_op);
            }
        }

        int K = roots.size() / 2;
        vector<vector<int> > comp_members(roots.size()); // comp_members[2c]/[2c+1] 是第 c 块的两侧人员

        for (int i = 1; i <= V; ++i) {
            comp_members[comp_id[find_set(i)]].push_back(i);
        }

        // 滚动背包：dp[i][j] = dp[i-1][j-|c0|] + dp[i-1][j-|c1|]，结果截到 2。
        for (int i = 0; i <= K; ++i) {
            for (int j = 0; j <= p1; ++j) {
                dp[i][j] = 0;
            }
        }
        dp[0][0] = 1;

        for (int i = 1; i <= K; ++i) {
            int sz0 = comp_members[2 * (i - 1)].size();
            int sz1 = comp_members[2 * (i - 1) + 1].size();

            for (int j = 0; j <= p1; ++j) {
                if (j >= sz0 && dp[i - 1][j - sz0] > 0) {
                    dp[i][j] = min(2, dp[i][j] + dp[i - 1][j - sz0]);
                }
                if (j >= sz1 && dp[i - 1][j - sz1] > 0) {
                    dp[i][j] = min(2, dp[i][j] + dp[i - 1][j - sz1]);
                }
            }
        }

        if (dp[K][p1] != 1) {
            cout << "no\n"; // 0 = 无解，≥2 = 多解，都判不出唯一身份
        } else {
            // 沿唯一路径回溯：dp[i][cur]==1 时两侧不可能同时可行
            //（否则两条路的方案数会在 dp[i][cur] 处累加成 2）。
            int curr_j = p1;
            vector<int> ans;
            for (int i = K; i >= 1; --i) {
                int sz0 = comp_members[2 * (i - 1)].size();
                int sz1 = comp_members[2 * (i - 1) + 1].size();

                bool can0 = (curr_j >= sz0 && dp[i - 1][curr_j - sz0] == 1);

                if (can0) {
                    for (size_t k = 0; k < comp_members[2 * (i - 1)].size(); ++k) {
                        ans.push_back(comp_members[2 * (i - 1)][k]);
                    }
                    curr_j -= sz0;
                } else {
                    for (size_t k = 0; k < comp_members[2 * (i - 1) + 1].size(); ++k) {
                        ans.push_back(comp_members[2 * (i - 1) + 1][k]);
                    }
                    curr_j -= sz1;
                }
            }
            sort(ans.begin(), ans.end());
            for (size_t i = 0; i < ans.size(); ++i) {
                cout << ans[i] << "\n";
            }
            cout << "end\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
