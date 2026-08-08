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
n = random.randint(1, 8)

def rand01(length):
    return "".join(str(random.randint(0, 1)) for _ in range(length))

print(T)
print(n)
print(rand01(n))
print(rand01(n))
print(rand01(n))
print(rand01(n))
