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
int main(){ios::sync_with_stdio(false); cin.tie(nullptr); int n; if(!(cin>>n)) return 0; ll prev=0,total=0; for(int i=0;i<n;i++){ll h;cin>>h; if(h>prev) total+=h-prev; prev=h;} cout<<total<<'\n'; return 0;}
