/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:12
 * update_at: 2026-10-23 23:19
 */
// 正解：区间 DP。can[l][r][c] 表示子串 S[l..r] 能否折叠成字母 c。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXL = 205;   // L <= 200
const int MAXC = 4;     // 字母表只有 W I N G 四个

ll len_limit[MAXC];            // 每个字母的规则条数
vector<pair<int,int> > rule[MAXC]; // rule[c]：字母 c 的所有右部 (x, y)，元素是字母编号
bool can[MAXL][MAXL][MAXC];    // can[l][r][c]：S[l..r] 能否折叠成字母 c
char s[MAXL];                  // 1-indexed 的目标名字
ll n;                          // 名字长度 L

// 把字母映射到 0..3 的编号，顺序与题目输出顺序一致：W I N G
int to_id(char ch) {
    if (ch == 'W') return 0;
    if (ch == 'I') return 1;
    if (ch == 'N') return 2;
    return 3; // 'G'
}

char id_to_char[4] = {'W', 'I', 'N', 'G'};

void read_data() {
    for (int c = 0; c < MAXC; c++) {
        cin >> len_limit[c];
    }
    for (int c = 0; c < MAXC; c++) {
        for (int k = 0; k < len_limit[c]; k++) {
            string t;
            cin >> t;
            rule[c].push_back(make_pair(to_id(t[0]), to_id(t[1])));
        }
    }
    string name;
    cin >> name;
    n = name.size();
    for (int i = 1; i <= n; i++) {
        s[i] = name[i - 1];
    }
}

void solve() {
    // 长度 1：不需要替换，只能是被折叠的那个字母本身
    for (int i = 1; i <= n; i++) {
        can[i][i][to_id(s[i])] = true;
    }

    // 按区间长度从小到大递推，保证用到的更短区间已经算好
    for (int len = 2; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            for (int m = l; m < r; m++) {   // 枚举分裂点：左半 S[l..m]，右半 S[m+1..r]
                for (int c = 0; c < MAXC; c++) {
                    if (can[l][r][c]) continue; // 已经能折成 c，跳过
                    for (auto &p : rule[c]) {
                        if (can[l][m][p.first] && can[m + 1][r][p.second]) {
                            can[l][r][c] = true;
                            break;
                        }
                    }
                }
            }
        }
    }
}

void print_answer() {
    string ans;
    for (int c = 0; c < MAXC; c++) {
        if (can[1][n][c]) ans.push_back(id_to_char[c]);
    }
    if (ans.empty()) cout << "The name is wrong!" << "\n";
    else cout << ans << "\n";
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0);
    read_data();
    solve();
    print_answer();
    return 0;
}
