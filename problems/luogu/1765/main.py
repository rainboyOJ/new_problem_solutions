press_count = {}

for group in ["abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"]:
    for index, ch in enumerate(group):
        press_count[ch] = index + 1

press_count[" "] = 1

sentence = input().rstrip("\n")
answer = sum(press_count[ch] for ch in sentence)
print(answer)
