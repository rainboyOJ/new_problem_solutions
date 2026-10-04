### 【题目描述】

小 s 和小 t 为了打发无聊的数学课经常传小纸条，但是由于小纸条内容往往是一个 secret，为了不让别人偷看到这个 secret，小 s 用了一种骗码方式。对于每个英文的大写字母都找到一个替代的字母。这样原来的 LOVE 可能 decode 之后就变成 BATE。这样传纸条的时候就不担心 secret 被 Captured~

### 【输入文件】

第一行，一个字符串，长度不超过 10000。只包含大写字母和空格。

第二行，一个长度为 26 的大写字符串，分别表示 A~Z 编码后变成什么大写字母。

### 【输出文件】

一行，一个字符串，表示输入文件的第一行字符串编码后的字符串。

### 【样例】

decode.in：

```
HPC PJVYMIY
BLMRGJIASOPZEFDCKWYHUNXQTV
```

decode.out：

```
ACM CONTEST
```

decode.in：

```
FDY GAI BG UKMY
KIMHOTSQYRLCUZPAGWJNBVDXEF
```

decode.out：

```
THE SKY IS BLUE
```
