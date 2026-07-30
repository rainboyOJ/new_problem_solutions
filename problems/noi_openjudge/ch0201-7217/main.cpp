/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
int n;
bool check(int x,int dep){
	if( dep == n+1)
		return 1;
	if( x < n)
	    return 0;
	if( x % n == 1){
		if( check((x-1)-(x-1)/n,dep+1) ){
			return 1;
        }
    }
	return 0;
}
int main(){
	//printf("hello world");
    scanf("%d",&n);
	//printf("%d",n);
    int i;
	for(i=1;1;i++){
		if( check(i*n+1,1) ){
			printf("%d",i*n+1);
            return 0;
		}

	}
	return 0;
}
