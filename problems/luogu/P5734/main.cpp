/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

char doc[100005]; // 文档字符串
int q;            // 操作次数

int main() {
    cin >> q >> doc;
    int op, a, b;
    char str[1005];
    for (int i = 1; i <= q; i++) {
        cin >> op;
        if (op == 1) { // 追加
            cin >> str;
            strcat(doc, str);
            cout << doc << "\n";
        } else if (op == 2) { // 截取子串
            cin >> a >> b;
            doc[a + b] = '\0'; // 在截取终点后截断
            // 将子串移到开头
            memmove(doc, doc + a, b + 1);
            cout << doc << "\n";
        } else if (op == 3) { // 插入
            cin >> a >> str;
            int len_doc = strlen(doc);
            int len_str = strlen(str);
            // 将后面的字符后移
            memmove(doc + a + len_str, doc + a, len_doc - a + 1);
            // 将 str 复制到插入位置
            memcpy(doc + a, str, len_str);
            cout << doc << "\n";
        } else { // 查找
            cin >> str;
            char *p = strstr(doc, str);
            if (p == NULL) cout << -1 << "\n";
            else cout << (p - doc) << "\n";
        }
    }
    return 0;
}
