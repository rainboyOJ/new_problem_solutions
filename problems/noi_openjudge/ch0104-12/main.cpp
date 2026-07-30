/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-30 22:57
 * update_at: 2026-07-30 22:57
 */
#include <cstdio>
int main(){
    int a,b;
    scanf("%d",&a);
    double walk_time = a / 1.2;
    double bike_time = a / 3.0;
    bike_time += 23;
    bike_time += 27;
    if( bike_time == walk_time)
        printf("All");
    else if ( bike_time > walk_time)
        printf("Walk");
    else {
        printf("Bike");
    }
    return 0;
}
