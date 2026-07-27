/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

int n;
string pic[2500];

int main() {
    cin >> n;
    pic[0] = " /\\ ";
    pic[1] = "/__\\";
    int h = 2;
    for (int k = 2; k <= n; k++) {
        string tmp[2500];
        for (int i = 0; i < h; i++) tmp[i] = pic[i];
        for (int i = 0; i < h; i++) pic[i] = string(h, ' ') + tmp[i] + string(h, ' ');
        for (int i = 0; i < h; i++) pic[i + h] = tmp[i] + tmp[i];
        h *= 2;
    }
    for (int i = 0; i < h; i++) {
        int pos = pic[i].find_last_not_of(' ');
        cout << pic[i].substr(0, pos + 1) << endl;
    }
    return 0;
}
