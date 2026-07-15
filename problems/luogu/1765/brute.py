groups = ["abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"]
press_count = {" ": 1}
for group in groups:
    for i, ch in enumerate(group, start=1):
        press_count[ch] = i

sentence = input().rstrip("\n")
print(sum(press_count[ch] for ch in sentence))
