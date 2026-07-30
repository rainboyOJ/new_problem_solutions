/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
int main(){
	int a,b,c;
	scanf("%d%d%d",&a,&b,&c);
	if( a+b > c && a+ c > b && b+c >a){
		printf("yes");
	}
	else
		printf("no");
	return 0;
}
