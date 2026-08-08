s = input().strip()
body, check = s[:-1], s[-1]
nums = [int(ch) for ch in body if ch.isdigit()]
mod = sum(v * (i + 1) for i, v in enumerate(nums)) % 11
expect = 'X' if mod == 10 else str(mod)
print('Right' if check == expect else body + expect)
