/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

string s;
long long n;

int main() {
    cin >> s >> n;
    long long len = s.size();
    while (len < n) len *= 2;
    while (n > (int)s.size()) {
        long long half = len / 2;
        if (n == half + 1) n = half;
        else if (n > half + 1) n = n - half - 1;
        len = half;
    }
    cout << s[n - 1] << endl;
    return 0;
}
