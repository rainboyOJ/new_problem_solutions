s = input().strip()

boy = sum(
    any(s[i + j] == "boy"[j] for j in range(3))
    for i in range(len(s) - 2)
)
girl = sum(
    any(s[i + j] == "girl"[j] for j in range(4))
    for i in range(len(s) - 3)
)

print(boy)
print(girl)
