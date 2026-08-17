/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXC = 128; // ASCII 字符范围
const int LOG = 31;   // 2^30 > 1e9，31 层足够覆盖最大变换次数

int next_char[MAXC];  // next_char[c] 表示字符 c 经过一次替换后的字符
int jump[LOG][MAXC];  // jump[j][c] 表示字符 c 经过 2^j 次替换后的字符

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 输入行形如 #Hello World#，需要整行读取
    string line;
    getline(cin, line);
    string initial = line.substr(1, line.size() - 2); // 去掉两侧的 # 得到初始字符串

    int n;
    cin >> n;
    getline(cin, line);
    // 未定义的字符替换为自身
    for (int i = 0; i < MAXC; i++) next_char[i] = i;
    for (int i = 0; i < n; i++) {
        getline(cin, line); // 形如 #a b# 或 #x y#
        next_char[(unsigned char)line[1]] = (unsigned char)line[2];
    }

    // 预处理跳转表：jump[j][c] = jump[j-1][ jump[j-1][c] ]
    for (int i = 0; i < MAXC; i++) jump[0][i] = next_char[i];
    for (int bit = 1; bit < LOG; bit++) {
        for (int i = 0; i < MAXC; i++) {
            jump[bit][i] = jump[bit - 1][jump[bit - 1][i]];
        }
    }

    int m;
    cin >> m;
    for (int query = 0; query < m; query++) {
        long long k;
        cin >> k;
        // 每个字符独立地完成 k 次替换：把 k 按二进制拆成若干 2^j 段
        string result;
        for (int i = 0; i < (int)initial.size(); i++) {
            int current = (unsigned char)initial[i];
            long long steps = k;
            int bit = 0;
            while (steps > 0) {
                if (steps & 1) current = jump[bit][current];
                steps >>= 1;
                bit++;
            }
            result.push_back((char)current);
        }
        cout << '#' << result << "#\n";
    }

    return 0;
}