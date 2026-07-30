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
	scanf("%d",&a);
	if(  a % 4 == 0){
		if( a % 100 ==0 && a % 400 != 0 )
			printf("N");
		else
			printf("Y");
	}
	else
		printf("N");
	return 0;
}
