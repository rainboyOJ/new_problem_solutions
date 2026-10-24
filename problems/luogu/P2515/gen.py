#!/usr/bin/env python3
import random

def main():
    n = random.randint(1, 8)
    m = random.randint(1, 20)
    w = [random.randint(1, 10) for _ in range(n)]
    v = [random.randint(1, 20) for _ in range(n)]
    
    # 依赖关系：0 到 n，但 d_i != i
    d = []
    for i in range(1, n + 1):
        candidates = [x for x in range(n + 1) if x != i]
        d.append(random.choice(candidates))
    
    print(f"{n} {m}")
    print(*(w))
    print(*(v))
    print(*(d))

if __name__ == '__main__':
    main()
