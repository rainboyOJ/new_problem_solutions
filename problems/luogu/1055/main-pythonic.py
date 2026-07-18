s=input().strip()
digits=[int(ch) for ch in s if ch.isdigit()]
# last is check digit position may be X
body=s[:-1]
nums=[int(ch) for ch in body if ch.isdigit()]
total=sum(v*(i+1) for i,v in enumerate(nums))
check=total%11
expect='X' if check==10 else str(check)
print('Right' if s[-1]==expect else body+expect)
