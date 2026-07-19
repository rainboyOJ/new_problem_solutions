s = input().strip()
sign = '-' if s.startswith('-') else ''
print(sign + (s[len(sign):][::-1].lstrip('0') or '0'))
