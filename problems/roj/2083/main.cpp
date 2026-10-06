/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 12:08
 * update_at: 2026-10-06 12:08
 */

// main.cpp：窗体面积。
// 用一个窗体栈（从底到顶）维护层级顺序；
// 查询 s(I) 时，用矩形切割法把目标窗体依次被上方窗体遮挡后的可见碎片保留下来。

#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

typedef long long ll;

const int MAXN = 70; // 同时存在的窗体最多 62 个（字母 + 数字），留点余量

// 一个窗体：标识符 + 对角坐标（保证 x1<x2, y1<y2）
struct Window {
    char id;
    ll x1, y1, x2, y2;
};

// 可见碎片矩形
struct Rect {
    ll x1, y1, x2, y2;
};

Window wins[MAXN]; // 窗体栈，wins[0] 最底，wins[top-1] 最顶
int top = 0;       // 栈中窗体个数

// 计算矩形面积
ll rect_area(const Rect &r) {
    return (r.x2 - r.x1) * (r.y2 - r.y1);
}

// 矩形切割：用遮挡矩形 cover 切割 rect，留下的碎片放入 out，返回碎片个数
// rect 与 cover 有交集时，交集被剔除，剩余部分分成至多 4 个互不相交的条带
int clip(const Rect &rect, const Rect &cover, Rect *out) {
    // 无交集：原矩形完整保留
    if (rect.x2 <= cover.x1 || rect.x1 >= cover.x2 ||
        rect.y2 <= cover.y1 || rect.y1 >= cover.y2) {
        out[0] = rect;
        return 1;
    }

    // 交集边界
    ll ix1 = std::max(rect.x1, cover.x1);
    ll iy1 = std::max(rect.y1, cover.y1);
    ll ix2 = std::min(rect.x2, cover.x2);
    ll iy2 = std::min(rect.y2, cover.y2);

    int cnt = 0;
    if (rect.y2 > iy2) { // 上方条带
        out[cnt].x1 = rect.x1; out[cnt].y1 = iy2;
        out[cnt].x2 = rect.x2; out[cnt].y2 = rect.y2;
        cnt++;
    }
    if (rect.y1 < iy1) { // 下方条带
        out[cnt].x1 = rect.x1; out[cnt].y1 = rect.y1;
        out[cnt].x2 = rect.x2; out[cnt].y2 = iy1;
        cnt++;
    }
    if (rect.x1 < ix1) { // 中间左侧条带
        out[cnt].x1 = rect.x1; out[cnt].y1 = iy1;
        out[cnt].x2 = ix1;     out[cnt].y2 = iy2;
        cnt++;
    }
    if (rect.x2 > ix2) { // 中间右侧条带
        out[cnt].x1 = ix2;     out[cnt].y1 = iy1;
        out[cnt].x2 = rect.x2; out[cnt].y2 = iy2;
        cnt++;
    }
    return cnt;
}

int main() {
    char line[256];
    std::vector<Rect> pieces; // 当前查询中还未被遮挡的可见碎片
    Rect tmp[8];              // clip 的临时碎片输出

    while (scanf("%255s", line) == 1) {
        std::string cmd = line;
        char op = cmd[0];
        // 逗号换成空格，方便 sscanf 按统一格式解析参数
        for (int i = 0; line[i] != '\0'; i++)
            if (line[i] == ',') line[i] = ' ';

        if (op == 'w') {
            // w(I,x,y,X,Y)：新建窗体，自动置顶
            char id;
            ll x1, y1, x2, y2;
            sscanf(line, " w ( %c %lld %lld %lld %lld )",
                   &id, &x1, &y1, &x2, &y2);
            if (x1 > x2) std::swap(x1, x2); // 对角点不保证左下在前后
            if (y1 > y2) std::swap(y1, y2);
            wins[top].id = id;
            wins[top].x1 = x1; wins[top].y1 = y1;
            wins[top].x2 = x2; wins[top].y2 = y2;
            top++;
        } else {
            // t/b/d/s 都是 t(I) 形式：先找到窗体在栈中的位置
            char id;
            sscanf(line, " %*c ( %c )", &id);
            int pos = -1;
            for (int i = 0; i < top; i++)
                if (wins[i].id == id) { pos = i; break; }

            if (op == 't') {
                // 置顶：取出后放到栈顶
                Window w = wins[pos];
                for (int i = pos; i < top - 1; i++) wins[i] = wins[i + 1];
                wins[top - 1] = w;
            } else if (op == 'b') {
                // 置底：取出后放到栈底
                Window w = wins[pos];
                for (int i = pos; i > 0; i--) wins[i] = wins[i - 1];
                wins[0] = w;
            } else if (op == 'd') {
                // 删除：从栈中移除
                for (int i = pos; i < top - 1; i++) wins[i] = wins[i + 1];
                top--;
            } else if (op == 's') {
                // 查询可见百分比：从栈顶往下直到目标窗体，依次切割
                pieces.clear();
                Rect all;
                all.x1 = wins[pos].x1; all.y1 = wins[pos].y1;
                all.x2 = wins[pos].x2; all.y2 = wins[pos].y2;
                pieces.push_back(all);

                for (int i = top - 1; i > pos && !pieces.empty(); i--) {
                    Rect cover;
                    cover.x1 = wins[i].x1; cover.y1 = wins[i].y1;
                    cover.x2 = wins[i].x2; cover.y2 = wins[i].y2;
                    std::vector<Rect> next_pieces;
                    for (int j = 0; j < (int)pieces.size(); j++) {
                        int cnt = clip(pieces[j], cover, tmp);
                        for (int k = 0; k < cnt; k++) next_pieces.push_back(tmp[k]);
                    }
                    pieces = next_pieces;
                }

                ll total = rect_area(all); // 窗体初始总面积，直接由坐标算出
                ll vis = 0; // 可见面积
                for (int j = 0; j < (int)pieces.size(); j++)
                    vis += rect_area(pieces[j]);
                // 乘 100 转百分比，四舍五入到 3 位小数
                printf("%.3f\n", (double)vis * 100.0 / (double)total);
            }
        }
    }
    return 0;
}
