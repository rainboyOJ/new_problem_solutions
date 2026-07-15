from collections import Counter


counter = Counter()

for _ in range(4):
    line = input()
    for ch in line:
        if "A" <= ch <= "Z":
            counter[ch] += 1

heights = [counter[chr(ord("A") + i)] for i in range(26)]
max_height = max(heights)

for level in range(max_height, 0, -1):
    row = []
    for height in heights:
        if height >= level:
            row.append("*")
        else:
            row.append(" ")
    print(" ".join(row).rstrip())

print(" ".join(chr(ord("A") + i) for i in range(26)))
