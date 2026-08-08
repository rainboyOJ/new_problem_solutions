#!/usr/bin/env python3
import random


def main():
    random.seed()
    # TODO: generate input for this problem.


if __name__ == "__main__":
    main()
#!/usr/bin/env python3
import random

case_id = 1
T = 1
n = random.randint(2, 8)
k = random.randint(1, n - 1)

edges = []
for i in range(2, n + 1):
    p = random.randint(1, i - 1)
    edges.append((p, i))

keys = random.sample(range(1, n), k)

print(case_id, T)
print(n, k)
for u, v in edges:
    print(u, v)
print(*keys)
