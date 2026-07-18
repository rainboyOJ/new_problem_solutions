s = input().strip()
boy = sum(any(s[i + k] == c for k, c in enumerate("boy")) for i in range(len(s) - 2))
girl = sum(any(s[i + k] == c for k, c in enumerate("girl")) for i in range(len(s) - 3))
print(boy, girl, sep="\n")
