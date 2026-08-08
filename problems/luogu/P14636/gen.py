#!/usr/bin/env python3
import random


def main():
    random.seed()
    # TODO: generate input for this problem.


if __name__ == "__main__":
    main()
#!/usr/bin/env python3
import random

n = random.randint(1, 9)
m = random.randint(1, 2 * n - 1)

values = []
for _ in range(n):
    values.append(random.randint(1, 25))

print(0, 1)
print(n, m)
print(*values)
