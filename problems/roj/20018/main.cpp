/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 21:26
 * update_at: 2026-08-28 21:26
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

string s;           // 压缩旋律串，只含小写字母和数字
long long c;        // 询问的第 c 个音符，从 0 开始编号
int m;              // 段的个数
char chs[MAXN];     // chs[i]：第 i 段的音符
long long cnts[MAXN]; // cnts[i]：第 i 段音符连续出现的次数
long long sum;      // 单周期总长度 L

// 把压缩串解析成 (音符, 次数) 段，并累加单周期长度。
void parse() {
    int n = (int)s.length();
    int i = 0;
    while (i < n) {
        chs[++m] = s[i]; // 当前位置一定是字母（音符）
        i++;
        long long cnt = 0;
        // 次数可能占多位数字，如 d10 表示 10 个 d，逐位拼出来。
        while (i < n && s[i] >= '0' && s[i] <= '9') {
            cnt = cnt * 10 + (s[i] - '0');
            i++;
        }
        cnts[m] = cnt;
        sum += cnt;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s >> c;

    parse();

    // 无限循环：第 c 个音符只取决于它在单周期内的位置 k = c mod L。
    c %= sum;

    // 前缀和定位：第 i 段覆盖区间 [pre, pre + cnts[i])，
    // 第一个 pre + cnts[i] > c 的段就是答案段。
    long long pre = 0;
    for (int i = 1; i <= m; i++) {
        if (pre + cnts[i] > c) {
            cout << chs[i] << '\n';
            return 0;
        }
        pre += cnts[i];
    }

    return 0;
}