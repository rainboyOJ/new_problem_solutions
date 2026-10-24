/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:12
 * update_at: 2026-10-23 23:19
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 直接照“折叠的最后一步”递归：S[l..r] 折成 c，当且仅当存在规则 c -> xy 与分裂点 m，
// 使左半折成 x、右半折成 y。这里不做记忆化，重复子区间会被反复重算，
// 复杂度指数级，只适合 L <= 20 的小数据（正好对应 30% 部分分）。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXL = 205;   // L <= 200
const int MAXC = 4;     // 字母表只有 W I N G 四个

ll rule_cnt[MAXC];               // 每个字母的规则条数
vector<pair<int,int> > rule[MAXC]; // rule[c]：字母 c 的所有右部 (x, y)，元素是字母编号
char s[MAXL];                    // 1-indexed 的目标名字
ll n;                            // 名字长度 L

// 把字母映射到 0..3 的编号，顺序 W I N G
int to_id(char ch) {
    if (ch == 'W') return 0;
    if (ch == 'I') return 1;
    if (ch == 'N') return 2;
    return 3; // 'G'
}

char id_to_char[4] = {'W', 'I', 'N', 'G'};

// fold(c, l, r)：S[l..r] 能否折叠成单个字母 c
bool fold(int c, int l, int r) {
    if (l == r) {
        return s[l] == id_to_char[c];
    }
    for (auto &p : rule[c]) {           // 枚举最后一步替换 c -> x y
        int x = p.first;
        int y = p.second;
        for (int m = l; m < r; m++) {   // 枚举分裂点
            if (fold(x, l, m) && fold(y, m + 1, r)) {
                return true;
            }
        }
    }
    return false;
}

void read_data() {
    for (int c = 0; c < MAXC; c++) {
        cin >> rule_cnt[c];
    }
    for (int c = 0; c < MAXC; c++) {
        for (int k = 0; k < rule_cnt[c]; k++) {
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_data();

    string ans;
    for (int c = 0; c < MAXC; c++) {
        if (fold(c, 1, n)) ans.push_back(id_to_char[c]);
    }
    if (ans.empty()) cout << "The name is wrong!" << "\n";
    else cout << ans << "\n";

    return 0;
}
