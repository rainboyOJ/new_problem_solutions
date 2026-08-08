import sys

# Increase recursion depth just in case, though 25 is enough
sys.setrecursionlimit(2000)

def main():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return
    n = int(data[0])
    k = int(data[1])
    a = [int(x) for x in data[2:]]
    
    m = max(k, max(a))
    top_bit = m.bit_length() - 1 if m > 0 else 0
    
    # Trie lists: ch0[u], ch1[u], tag[u]. Root is 1.
    ch0 = [0, 0]
    ch1 = [0, 0]
    tag = [0, 0]
    cnt = 1
    
    for a_val in a:
        u = 1
        for bit in range(top_bit, -1, -1):
            k_bit = (k >> bit) & 1
            a_bit = (a_val >> bit) & 1
            if k_bit == 1:
                # 1. 严格小于分支: x_bit = a_bit
                x_bit_less = a_bit
                if x_bit_less == 0:
                    if not ch0[u]:
                        cnt += 1
                        ch0[u] = cnt
                        ch0.append(0)
                        ch1.append(0)
                        tag.append(0)
                    tag[ch0[u]] += 1
                else:
                    if not ch1[u]:
                        cnt += 1
                        ch1[u] = cnt
                        ch0.append(0)
                        ch1.append(0)
                        tag.append(0)
                    tag[ch1[u]] += 1
                
                # 2. 保持相等分支: x_bit = a_bit ^ 1
                x_bit_eq = a_bit ^ 1
                if x_bit_eq == 0:
                    if not ch0[u]:
                        cnt += 1
                        ch0[u] = cnt
                        ch0.append(0)
                        ch1.append(0)
                        tag.append(0)
                    u = ch0[u]
                else:
                    if not ch1[u]:
                        cnt += 1
                        ch1[u] = cnt
                        ch0.append(0)
                        ch1.append(0)
                        tag.append(0)
                    u = ch1[u]
            else:
                # 只能保持相等分支: x_bit = a_bit
                x_bit_eq = a_bit
                if x_bit_eq == 0:
                    if not ch0[u]:
                        cnt += 1
                        ch0[u] = cnt
                        ch0.append(0)
                        ch1.append(0)
                        tag.append(0)
                    u = ch0[u]
                else:
                    if not ch1[u]:
                        cnt += 1
                        ch1[u] = cnt
                        ch0.append(0)
                        ch1.append(0)
                        tag.append(0)
                    u = ch1[u]
        tag[u] += 1

    max_cola = 0
    
    # DFS traversal
    def dfs(u, current_sum):
        nonlocal max_cola
        if not u:
            return
        current_sum += tag[u]
        if not ch0[u] and not ch1[u]:
            if current_sum > max_cola:
                max_cola = current_sum
            return
        if ch0[u]:
            dfs(ch0[u], current_sum)
        if ch1[u]:
            dfs(ch1[u], current_sum)

    dfs(1, 0)
    print(max_cola)

if __name__ == '__main__':
    main()
