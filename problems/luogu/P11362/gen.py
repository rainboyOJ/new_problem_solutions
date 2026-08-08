#!/usr/bin/env python3
import random


def main():
    random.seed()
    # TODO: generate input for this problem.


if __name__ == "__main__":
    main()
#!/usr/bin/env python3
import random

T = 1
n = random.randint(1, 4)
v = random.randint(2, 3)
m = random.randint(1, 6)

print(T)
print(n, m, v)
for _ in range(m):
    print(random.randint(1, n), random.randint(1, v))
