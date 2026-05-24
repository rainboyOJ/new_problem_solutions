/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-22 10:19:49
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,m;
int a[maxn];
const int K = 24;
const int MAX_MASK = (1<<K);
int f[MAX_MASK];


int string2mask(const string &s)
{
    int t = 0;
    t |= 1 << (s[0] - 'a');
    t |= 1 << (s[1] - 'a');
    t |= 1 << (s[2] - 'a');
    return t;
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    std::cin >> n;
    string s;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> s;
        f[string2mask(s)]++; // 边界条件
    }
    
    // SOS DP
    // f[mask] 求单词为 mask的子集,子集的数量,也就是单词的数量
    for(int i =  0; i < K ;i++) {
        for(int mask = 0 ; mask < MAX_MASK ; ++ mask)
        {
            // 对应的位置是1
            if( mask & ( 1<< i))
            {
                f[mask] += f[mask ^(1<<i)];
            }
        }
    }

    int tot_xor = 0;
    int all_mask = MAX_MASK - 1;


    // 遍历问题,也就是假设的原因集合
    for(int v = 0 ; v< MAX_MASK; ++ v) {

        // 对应的补集
        int c = all_mask ^ v;

        // 正难则反: 
        int cnt = n - f[c];

        tot_xor ^= (cnt * cnt);

    }

    std::cout << tot_xor << "\n";
    
    return 0;
}
