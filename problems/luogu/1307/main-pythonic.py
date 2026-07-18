s=input().strip()
sign='-' if s.startswith('-') else ''
body=s[len(sign):][::-1].lstrip('0') or '0'
print(sign+body)
