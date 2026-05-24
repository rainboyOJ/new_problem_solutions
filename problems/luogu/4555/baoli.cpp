// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

constexpr int MAXN = 110000;            // 原始字符串最大长度
const int maxn = MAXN;

char s[maxn];

bool is_huiwen(int s,int len) {
    int start = 0;
    int end = len-1;

    while( start < len)
    {
        if( s[start] != s[end])
            return 0;
        start++;
        end--;
    }
    return 0;
}

bool max_hui_wen_end_at_pos(int pos) {

}

bool max_hui_wen_start_at_pos(int pos) {

}


int main() {
    scanf("%s",s+1);
    int len = strlen(s+1);
    int ans = 0;
    for(int i = 1 ;i < len;i++) {
        int t1 = max_hui_wen_start_at_pos(i);
        int t2 = max_hui_wen_start_at_pos(i+1);
        if( ans < t1 + t2) {
            ans = t1+t2;
        }
    }
    pr ans
    

    return 0;
}
