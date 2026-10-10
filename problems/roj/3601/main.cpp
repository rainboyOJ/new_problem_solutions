/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){ ios::sync_with_stdio(false); cin.tie(nullptr); ll a,b; if(!(cin>>a>>b)) return 0; ll r0=a,r=b,s0=1,s=0; while(r){ ll q=r0/r; ll nr=r0-q*r; r0=r; r=nr; ll ns=s0-q*s; s0=s; s=ns; } cout << (s0%b+b)%b << '\n'; return 0; }
