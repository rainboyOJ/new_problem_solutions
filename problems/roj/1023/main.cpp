/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:44
 * update_at: 2026-10-04 22:44
 */
#include <iostream>

using namespace std;

typedef long long ll;

// 题面问 sizeof("Hello, World!")：13 个可见字符 + 末尾隐含的 '\0' = 14。
// 直接输出常量 14 即可。
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << sizeof("Hello, World!") << "\n";

    return 0;
}
