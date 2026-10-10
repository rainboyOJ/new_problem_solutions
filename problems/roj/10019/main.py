#!/usr/bin/env python3
# Author: Antigravity
# Date: 2026-10-10 05:00
# 10019 扑克：预处理合法 5 张牌组 -> 按牌力排序 -> 三张子集反向索引 -> 二分找最弱稳赢组合。

import sys
import itertools

def solve() -> None:
    # ① 牌型表：同花顺 2 > 四条 3 > 葫芦 4 > 同花 5 > 顺子 6 > 三条 7
    #    f 是 5 个比较位，f[4] 最重要
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    d_val = tuple((x - 1) // 4 for x in range(53))
    hua_val = tuple((x - 1) % 4 for x in range(53))
    
    arr = []
    
    for p in itertools.combinations(range(1, 53), 5):
        p0, p1, p2, p3, p4 = p
        d0, d1, d2, d3, d4 = d_val[p0], d_val[p1], d_val[p2], d_val[p3], d_val[p4]
        t0, t1, t2, t3, t4 = hua_val[p0], hua_val[p1], hua_val[p2], hua_val[p3], hua_val[p4]
        
        is_flush = (t0 == t1 and t1 == t2 and t2 == t3 and t3 == t4)
        is_straight = (d0 + 1 == d1 and d1 + 1 == d2 and d2 + 1 == d3 and d3 + 1 == d4)
        
        tp = 0
        f = None
        
        if is_straight and is_flush:
            tp = 2
            f = (p0, p1, p2, p3, p4)
        elif d0 == d1 and d1 == d2 and d2 == d3:
            tp = 3
            f = (p4, p0, p1, p2, p3)
        elif d1 == d2 and d2 == d3 and d3 == d4:
            tp = 3
            f = (p0, p1, p2, p3, p4)
        elif d0 == d1 and d1 == d2 and d3 == d4:
            tp = 4
            f = (p3, p4, p0, p1, p2)
        elif d0 == d1 and d2 == d3 and d3 == d4:
            tp = 4
            f = (p0, p1, p2, p3, p4)
        elif is_flush:
            tp = 5
            f = (p0, p1, p2, p3, p4)
        elif is_straight:
            tp = 6
            f = (p0, p1, p2, p3, p4)
        elif d0 == d1 and d1 == d2:
            tp = 7
            f = (p3, p4, p0, p1, p2)
        elif d1 == d2 and d2 == d3:
            tp = 7
            f = (p0, p4, p1, p2, p3)
        elif d2 == d3 and d3 == d4:
            tp = 7
            f = (p0, p1, p2, p3, p4)
            
        if tp != 0:
            arr.append((tp, f, p))
            
    def sort_key(item):
        tp, f, _ = item
        return (
            tp,
            -d_val[f[4]], -d_val[f[3]], -d_val[f[2]], -d_val[f[1]], -d_val[f[0]],
            hua_val[f[4]], hua_val[f[3]], hua_val[f[2]], hua_val[f[1]], hua_val[f[0]]
        )
        
    arr.sort(key=sort_key)

    # ② 每组牌登记到 10 个三张子集桶里（桶内天然按牌力降序）
    a = [[] for _ in range(150005)]
    for idx, item in enumerate(arr):
        p = item[2]
        for c_comb in itertools.combinations(p, 3):
            h = c_comb[0] * 2809 + c_comb[1] * 53 + c_comb[2]
            a[h].append(idx)
            
    def parse_card(s):
        tt = {'S':1, 'H':2, 'C':3, 'D':4}[s[0]]
        if '2' <= s[1] <= '9': qq = int(s[1])
        elif s[1] == 'T': qq = 10
        elif s[1] == 'J': qq = 11
        elif s[1] == 'Q': qq = 12
        elif s[1] == 'K': qq = 13
        elif s[1] == 'A': qq = 14
        return (qq - 2) * 4 + tt
        
    def out_card(p):
        # 与官方 std.cpp 一致：每张牌后跟一个空格
        res = []
        for x in p:
            h = hua_val[x]
            dv = d_val[x]
            res.append("SHCD"[h] + "23456789TJQKA"[dv] + " ")
        return "".join(res)
        
    def cmp2_is_1(x_idx, y_idx):
        x_tp, x_f, _ = arr[x_idx]
        y_tp, y_f, _ = arr[y_idx]
        if x_tp != y_tp:
            return x_tp < y_tp
        for i in range(4, -1, -1):
            dx = d_val[x_f[i]]
            dy = d_val[y_f[i]]
            if dx != dy:
                return dx > dy
        return False

    idx_data = 0
    T = int(input_data[idx_data])
    idx_data += 1
    
    out_lines = []
    for _ in range(T):
        if idx_data + 6 > len(input_data):
            break
        s = input_data[idx_data:idx_data+6]
        idx_data += 6
        
        c_cocktail = [parse_card(x) for x in s[0:3]]
        c_chino = [parse_card(x) for x in s[3:6]]
        
        h_x = c_cocktail[0] * 2809 + c_cocktail[1] * 53 + c_cocktail[2]
        h_y = c_chino[0] * 2809 + c_chino[1] * 53 + c_chino[2]
        
        if not a[h_y]:
            out_lines.append("-1")
            continue
            
        y_max = a[h_y][0]
        if not a[h_x] or not cmp2_is_1(a[h_x][0], y_max):
            out_lines.append("-1")
            continue

        # ③ 倍增二分：求最后一个仍能赢的（牌力最弱）
        now = 0
        siz = len(a[h_x])
        for j in (4096, 2048, 1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1):
            if now + j < siz and cmp2_is_1(a[h_x][now + j], y_max):
                now += j
                
        best_p = arr[a[h_x][now]][2]
        out_lines.append(out_card(best_p))
        
    print('\n'.join(out_lines))

if __name__ == '__main__':
    solve()
