/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:36
 * update_at: 2026-10-06 10:36
 */
// 解密牛语：逆向枚举一步加密的 (C, O, W) 三元组做记忆化搜索。
// 四重剪枝：字母守恒、首 C/末 W 固定、非标记段必为 T 的子串、邻接缺口 <= 3c。
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
typedef long long ll;

const std::string T = "Begin the Escape execution at the Break of Dawn"; // 目标原文
const int N = 47; // 目标原文长度

std::set<std::pair<char, char> > adj_pairs; // T 中所有相邻字母对
std::set<std::string> failed; // 记忆化：所有判定失败的密文状态

// 预处理 T 的相邻字母对集合，供邻接剪枝使用
void init_pairs() {
    for (int i = 0; i + 1 < N; i++)
        adj_pairs.insert(std::make_pair(T[i], T[i + 1]));
}

// 把串按 C/O/W 切开，检查每个极大非标记段是否都是 T 的连续子串。
// 依据：段内字母只会被整段搬运，永远连续，所以必须本来就是 T 的子串。
bool check_segments(const std::string &v) {
    std::string seg = "";
    for (int i = 0; i < (int)v.size(); i++) {
        if (v[i] == 'C' || v[i] == 'O' || v[i] == 'W') {
            if (!seg.empty() && T.find(seg) == std::string::npos) return false;
            seg = "";
        } else {
            seg += v[i];
        }
    }
    if (!seg.empty() && T.find(seg) == std::string::npos) return false;
    return true;
}

// 判断密文 v 能否解密成 T
bool dfs(const std::string &v) {
    if (v == T) return true; // 已经还原
    if (failed.count(v)) return false; // 之前判定过失败

    int c = 0, o = 0, w = 0;
    for (int i = 0; i < (int)v.size(); i++) {
        if (v[i] == 'C') c++;
        if (v[i] == 'O') o++;
        if (v[i] == 'W') w++;
    }
    // 守恒剪枝：每解密一次长度 -3、C/O/W 各减 1，其余字母不变
    if (c == 0 || (int)v.size() != N + 3 * c || o != c || w != c) {
        failed.insert(v);
        return false;
    }

    // 固定前后缀剪枝：交换够不到首个 C 之前与末个 W 之后的字符
    int p = v.find('C');          // 首个 C 的位置
    int q = v.rfind('W');         // 末个 W 的位置
    if (v.substr(0, p) != T.substr(0, p)) {
        failed.insert(v);
        return false;
    }
    if (v.substr(q + 1) != T.substr(N - ((int)v.size() - q - 1))) {
        failed.insert(v);
        return false;
    }

    // 连续段剪枝（最强）：每个非标记段必须是 T 的子串
    if (!check_segments(v)) {
        failed.insert(v);
        return false;
    }

    // 邻接缺口剪枝：删掉标记后，每一处「T 中不相邻」的相邻字母对
    // 至少要一次交换才能修复，而一次交换只改 3 个邻接位置
    std::string nm = "";
    for (int i = 0; i < (int)v.size(); i++)
        if (v[i] != 'C' && v[i] != 'O' && v[i] != 'W') nm += v[i];
    int gaps = 0;
    for (int i = 0; i + 1 < (int)nm.size(); i++)
        if (!adj_pairs.count(std::make_pair(nm[i], nm[i + 1]))) gaps++;
    if (gaps > 3 * c) {
        failed.insert(v);
        return false;
    }

    // 枚举一组 (C, O, W)：位置 i < j < k，逆着一步加密把两段换回去
    std::vector<int> cs, os, ws;
    for (int i = 0; i < (int)v.size(); i++) {
        if (v[i] == 'C') cs.push_back(i);
        if (v[i] == 'O') os.push_back(i);
        if (v[i] == 'W') ws.push_back(i);
    }
    for (int a = 0; a < (int)cs.size(); a++) {
        int i = cs[a];
        for (int b = 0; b < (int)os.size(); b++) {
            int j = os[b];
            if (j <= i) continue;
            for (int e = 0; e < (int)ws.size(); e++) {
                int k = ws[e];
                if (k <= j) continue;
                // 还原结果 = A + X + Y + Z（两段交换并删掉三个标记）
                std::string t = v.substr(0, i)             // A
                              + v.substr(j + 1, k - j - 1) // X（原 O~W 段换到前面）
                              + v.substr(i + 1, j - i - 1) // Y（原 C~O 段换到后面）
                              + v.substr(k + 1);           // Z
                if (dfs(t)) return true;
            }
        }
    }

    failed.insert(v); // 所有出路的失败，记忆化
    return false;
}

int main() {
    init_pairs();
    std::string s;
    std::getline(std::cin, s);
    // 去掉行尾可能混入的 \r 与空白
    while (!s.empty() && (s[s.size() - 1] == '\r' || s[s.size() - 1] == ' '))
        s.erase(s.size() - 1);

    // 其余字母的多重集是守恒量，先与目标比一次，能快速排除大部分输入
    std::string st = "";
    for (int i = 0; i < (int)s.size(); i++)
        if (s[i] != 'C' && s[i] != 'O' && s[i] != 'W') st += s[i];
    std::sort(st.begin(), st.end());
    std::string tt = T;
    std::sort(tt.begin(), tt.end());
    if (st != tt) {
        std::cout << "0 0" << std::endl;
        return 0;
    }

    if (dfs(s))
        std::cout << "1 " << std::count(s.begin(), s.end(), 'C') << std::endl;
    else
        std::cout << "0 0" << std::endl;
    return 0;
}
