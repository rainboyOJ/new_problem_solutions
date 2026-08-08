from collections import Counter

counter = Counter(ch for _ in range(4) for ch in input() if "A" <= ch <= "Z")
letters = [chr(ord("A") + i) for i in range(26)]
heights = [counter[ch] for ch in letters]
for level in range(max(heights), 0, -1):
    print(" ".join("*" if h >= level else " " for h in heights).rstrip())
print(" ".join(letters))
