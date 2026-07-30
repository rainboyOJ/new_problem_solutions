/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>

int l,n,m;
int _min = 0x7f7f7f7f;

int a[50005];
void init(){
    scanf("%d%d%d",&l,&n,&m);
    int i;
    for (i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if( _min > a[i]-a[i-1])
             _min = a[i]-a[i-1];
    }
    if( l - a[n] < _min)
        _min = l - a[n];
    a[n+1] = l;
}

int cnt_remove(int num){
    int i,cnt = 0;
    int pre = 0;
    for(i=1;i<=n;i++){
        if( a[i] - a[pre] < num){
            cnt++;
        }
        else{
            pre = i;
        }
    }
    if( l-a[pre] < num)
        cnt++;
    return cnt;
}

//查找范围是[l,r), a[r] 永远 > key
template <typename T>
int first_g(T a[],int l,int r){
    int mid;
    while( l != r  ) //表示l和r没有重合
    {
        mid = (l+r) >>1; // 取中间位置
        if(cnt_remove(mid) <= m ) //表示 [m+1,r) 满足条件
            l = mid+1;
        else
            r = mid;
    }
    return l;
}

int main(){
    init();
    int ans = first_g(a,_min , l);
    printf("%d\n",ans-1);
    return 0;
}
