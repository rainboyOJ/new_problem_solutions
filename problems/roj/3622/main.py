import sys

def fall(g):
    for x in range(5):
        ptr = 0
        for y in range(7):
            if g[x][y] != 0:
                val = g[x][y]
                g[x][y] = 0
                g[x][ptr] = val
                ptr += 1

def clear_blocks(g):
    to_clear = [[False]*7 for _ in range(5)]
    any_clear = False
    for x in range(5):
        for y in range(7):
            c = g[x][y]
            if c != 0:
                if x + 2 < 5 and g[x+1][y] == c and g[x+2][y] == c:
                    to_clear[x][y] = to_clear[x+1][y] = to_clear[x+2][y] = True
                    any_clear = True
                if y + 2 < 7 and g[x][y+1] == c and g[x][y+2] == c:
                    to_clear[x][y] = to_clear[x][y+1] = to_clear[x][y+2] = True
                    any_clear = True
    if not any_clear:
        return False
    for x in range(5):
        for y in range(7):
            if to_clear[x][y]:
                g[x][y] = 0
    return True

def process(g):
    fall(g)
    while clear_blocks(g):
        fall(g)

def solve():
    sys.setrecursionlimit(200000)
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    n = int(input_data[0])
    g = [[0]*7 for _ in range(5)]
    idx = 1
    for x in range(5):
        y = 0
        while idx < len(input_data):
            val = int(input_data[idx])
            idx += 1
            if val == 0:
                break
            g[x][y] = val
            y += 1
            
    ans = []
    
    def dfs(step, current_g):
        if step == n:
            for x in range(5):
                if current_g[x][0] != 0:
                    return False
            return True
            
        cnt = [0] * 11
        for x in range(5):
            for y in range(7):
                if current_g[x][y] != 0:
                    cnt[current_g[x][y]] += 1
        for i in range(1, 11):
            if cnt[i] == 1 or cnt[i] == 2:
                return False
                
        for x in range(5):
            for y in range(7):
                if current_g[x][y] == 0:
                    continue
                    
                # Move right
                if x + 1 < 5 and current_g[x][y] != current_g[x+1][y]:
                    next_g = [col[:] for col in current_g]
                    next_g[x][y], next_g[x+1][y] = next_g[x+1][y], next_g[x][y]
                    process(next_g)
                    ans.append((x, y, 1))
                    if dfs(step + 1, next_g):
                        return True
                    ans.pop()
                    
                # Move left
                if x - 1 >= 0 and current_g[x-1][y] == 0:
                    next_g = [col[:] for col in current_g]
                    next_g[x][y], next_g[x-1][y] = next_g[x-1][y], next_g[x][y]
                    process(next_g)
                    ans.append((x, y, -1))
                    if dfs(step + 1, next_g):
                        return True
                    ans.pop()
                    
        return False
        
    if dfs(0, g):
        for move in ans:
            print(f"{move[0]} {move[1]} {move[2]}")
    else:
        print("-1")

if __name__ == '__main__':
    solve()
