/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:53
 * update_at: 2026-10-05 12:53
 */
#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;

typedef long long ll;

const int MAXN = 1005;

char key_s[MAXN];    // 密钥串，长度不超过 100
char cipher_s[MAXN]; // 密文串，长度不超过 1000
char plain_s[MAXN];  // 解出的明文

int main() {
    scanf("%s", key_s);
    scanf("%s", cipher_s);

    ll n = strlen(key_s);
    ll m = strlen(cipher_s);

    for (ll i = 0; i < m; i++) {
        // 密钥位统一按小写折算成 0..25 的偏移量，运算忽略大小写
        ll shift = tolower(key_s[i % n]) - 'a';
        // 明文大小写跟随密文：基准字符取 'a' 或 'A'
        char base = islower(cipher_s[i]) ? 'a' : 'A';
        // 解密为模 26 减法；C++ 的 % 会保留负号，所以再加一次 26 回绕
        ll idx = (cipher_s[i] - base - shift) % 26;
        if (idx < 0) {
            idx = idx + 26;
        }
        plain_s[i] = base + idx;
    }
    plain_s[m] = '\0';

    printf("%s\n", plain_s);
    return 0;
}
