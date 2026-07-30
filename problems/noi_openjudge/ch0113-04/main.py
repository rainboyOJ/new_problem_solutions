from collections import Counter

counts = Counter("".join(input() for _ in range(4)))
height = max(counts[chr(code)] for code in range(ord("A"), ord("Z") + 1))

for level in range(height, 0, -1):
    line = " ".join(
        "*" if counts[chr(code)] >= level else " "
        for code in range(ord("A"), ord("Z") + 1)
    )
    print(line.rstrip())
print(" ".join(chr(code) for code in range(ord("A"), ord("Z") + 1)))
