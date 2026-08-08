press = {
    ch: i + 1
    for group in ["abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"]
    for i, ch in enumerate(group)
}
press[" "] = 1
print(sum(press[ch] for ch in input().rstrip("\n")))
