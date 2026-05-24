import sys

def solve():
    # 读取输入
    try:
        line = sys.stdin.read().split()
        if not line: return
        n = int(line[0])
        cases = []
        for i in range(n):
            cases.append((int(line[i*2+1]), int(line[i*2+2])))
    except EOFError:
        return

    # 定义 8 个方向：严格按字典序（列增量优先，行增量次之）
    # dx: 列(字母)位移, dy: 行(数字)位移
    directions = [(-2, -1), (-2, 1), (-1, -2), (-1, 2), 
                  (1, -2), (1, 2), (2, -1), (2, 1)]

    for i, (P, Q) in enumerate(cases, 1):
        visited = [[False] * Q for _ in range(P)]
        path = []

        def dfs(r, c):
            path.append(f"{chr(ord('A') + c)}{r + 1}")
            visited[r][c] = True
            
            if len(path) == P * Q:
                return True
            
            for dc, dr in directions:
                nc, nr = c + dc, r + dr
                if 0 <= nr < P and 0 <= nc < Q and not visited[nr][nc]:
                    if dfs(nr, nc):
                        return True
            
            # 回溯
            visited[r][c] = False
            path.pop()
            return False

        print(f"Scenario #{i}:")
        # 始终从 A1 (0, 0) 开始以保证字典序最小
        if dfs(0, 0):
            print("".join(path))
        else:
            print("impossible")
        print() # 每个 Case 后面的空行

if __name__ == "__main__":
    solve()
