/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:12
 * update_at: 2026-10-04 22:12
 */
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

typedef long long ll;

// 输入：高度 h、宽度 w、字符 c、标志 d（0 空心 / 1 实心）
ll h, w;
char ch;
ll d;

int main() {
    // 读取一行四参数
    scanf("%lld %lld %c %lld", &h, &w, &ch, &d);
    // border：上下两条边，也是实心的每一行；w 非负，隐式转 size_t 安全
    string border;
    border.append(w, ch);

    // middle：实心时整行字符；空心时左右各 1 个字符 + 中间 w-2 个空格
    string middle;
    if (d == 1) {
        middle = border;
    } else {
        middle.push_back(ch);
        middle.append(w - 2, ' ');
        middle.push_back(ch);
    }

    // 输出：border + middle 重复 (h-2) 次 + border，末尾空行
    // 行数 = h，先全部放到 vector 里一次性打印
    vector<string> rows;
    rows.push_back(border);
    for (ll i = 0; i < h - 2; ++i) {
        rows.push_back(middle);
    }
    rows.push_back(border);

    for (size_t i = 0; i < rows.size(); ++i) {
        printf("%s\n", rows[i].c_str());
    }
    // 与原题样例末尾空行一致，补一行空行
    printf("\n");
    return 0;
}
