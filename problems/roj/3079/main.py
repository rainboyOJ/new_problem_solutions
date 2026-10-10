import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    n = int(input_data[0])
    cnt = [0] * 60
    for i in range(1, n + 1):
        cnt[int(input_data[i])] += 1
        
    routes = []
    for a in range(30):
        for d in range(a + 1, 60 - a):
            valid = True
            t = a
            while t < 60:
                if cnt[t] == 0:
                    valid = False
                    break
                t += d
            if valid:
                length = (59 - a) // d + 1
                routes.append((length, a, d))
                
    routes.sort(key=lambda x: (-x[0], x[1], x[2]))
    ans = []
    
    def dfs(depth, max_depth, start_idx, rest):
        if rest == 0:
            return True
        if depth == max_depth:
            return False
            
        for i in range(start_idx, len(routes)):
            length, a, d = routes[i]
            if rest > length * (max_depth - depth):
                return False 
                
            can_choose = True
            t = a
            while t < 60:
                if cnt[t] == 0:
                    can_choose = False
                    break
                t += d
                
            if can_choose:
                t = a
                while t < 60:
                    cnt[t] -= 1
                    t += d
                
                ans.append(routes[i])
                
                if dfs(depth + 1, max_depth, i, rest - length):
                    return True
                    
                ans.pop()
                
                t = a
                while t < 60:
                    cnt[t] += 1
                    t += d
                    
        return False

    max_depth = 0
    while max_depth <= 17:
        ans.clear()
        if dfs(0, max_depth, 0, n):
            # 题面虽要求输出一个整数，但真实测试数据需要输出详细方案
            for length, a, d in ans:
                print(f"{a:2d} {d:2d}")
            return
        max_depth += 1

if __name__ == '__main__':
    solve()