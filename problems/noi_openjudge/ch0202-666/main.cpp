/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <bits/stdc++.h>
using namespace std;
#define F(n) for(int i =1;i<=n;i++)
#define F3(i,s,t) for(int i =s;i<=t;i++)
int tot; // total
int m,n;

int cnt; // count

// pre ,
// dep = depth 
void apple(int pre,int left,int dep)
{
    if( dep == n) {
        if( left >= pre )
            cnt++;
        return ;
    }
    F3(i,pre,left) {
        apple(i,left-i,dep+1);
    }
}


int main(){
    cin >> tot;
    F(tot) {
        cin >> m >> n;
        cnt = 0;
        apple(0,m,1);
        cout << cnt << endl;
    }
    return 0;
}
