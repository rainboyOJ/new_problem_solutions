import sys

# Increase recursion depth for DFS
sys.setrecursionlimit(200000)

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    n = int(input_data[0])
    m = int(input_data[1])
    k_val = int(input_data[2])
    mod = int(input_data[3])
    
    beat = []
    for i in range(m):
        beat.append(int(input_data[4 + i]))
    beat.sort()
    
    vis = set()
    ans = []
    
    def dfs(s_str, length):
        if s_str not in vis:
            vis.add(s_str)
            ans.append(s_str)
        else:
            return
        if length == n:
            return
        for i in range(n):
            if s_str[i] == '0':
                c = '0'
                for j in range(i):
                    if s_str[j] > c:
                        c = s_str[j]
                t = list(s_str)
                t[i] = chr(ord(c) + 1)
                dfs("".join(t), length + 1)

    start_s = "0" * n
    dfs(start_s, 0)
    
    S = []
    S.append("") # 1-based indexing
    ID = {}
    num = 0
    cnt = [0] * 120000
    
    for i in range(len(ans)):
        s_list = list(ans[i])
        c = '0'
        for j in range(n):
            if s_list[j] == '0':
                s_list[j] = chr(ord(c) + 1)
                c = chr(ord(c) + 1)
            else:
                if s_list[j] > c:
                    c = s_list[j]
        c_max = '0'
        for j in range(n):
            if s_list[j] > c_max:
                c_max = s_list[j]
        if ord(c_max) >= ord('0') + k_val:
            num += 1
            S.append(ans[i])
            ID[ans[i]] = num
            
    for i in range(1, num + 1):
        c_val = 0
        for j in range(n):
            if S[i][j] != '0':
                c_val |= (1 << j)
        cnt[i] = c_val
        
    fact = [1] * 550
    for i in range(1, 531):
        fact[i] = (fact[i - 1] * i) % mod
        
    C = [[0] * 550 for _ in range(550)]
    C[0][0] = 1
    for i in range(1, 531):
        for j in range(i + 1):
            if j == 0 or i == 1:
                C[i][j] = 1
            else:
                C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod

    dp = [[0] * (num + 1) for _ in range(m + 1)]
    dp[0][1] = 1
    
    for i in range(m):
        for j in range(1, num + 1):
            if dp[i][j] > 0:
                dp[i + 1][j] = (dp[i + 1][j] + dp[i][j]) % mod
                now = S[j]
                for l in range(n):
                    if now[l] == '0' and beat[i] >= (cnt[j] + (1 << l) + 1):
                        nxt = list(now)
                        c_char = '0'
                        for idx in range(l):
                            if nxt[idx] > c_char:
                                c_char = nxt[idx]
                        nxt[l] = chr(ord(c_char) + 1)
                        nxt_str = "".join(nxt)
                        next_id = ID.get(nxt_str, 0)
                        if next_id > 0:
                            ways = dp[i][j] * C[beat[i] - cnt[j] - 2][(1 << l) - 1] % mod
                            ways = ways * fact[1 << l] % mod
                            dp[i + 1][next_id] = (dp[i + 1][next_id] + ways) % mod
                            
    ans_val = 0
    full_mask = (1 << n) - 1
    for j in range(1, num + 1):
        if cnt[j] == full_mask:
            ans_val = (ans_val + dp[m][j]) % mod
            
    for i in range(1, n + 1):
        ans_val = (ans_val * 2) % mod
        
    print(ans_val)

if __name__ == '__main__':
    main()
