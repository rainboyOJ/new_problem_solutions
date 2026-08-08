# data_tool.py

位置：

```text
scripts/problem-analysis-tools/data_tool.py
```

作用：管理题目目录中的样例和本地测试数据。

## list

列出输入/答案配对、缺失答案和孤立答案：

```bash
python3 scripts/problem-analysis-tools/data_tool.py list problems/luogu/P1001
```

在题目目录中：

```bash
python3 ../../../scripts/problem-analysis-tools/data_tool.py list
```

## normalize

把已识别的数据文件从 CRLF/CR 统一为 LF：

```bash
python3 scripts/problem-analysis-tools/data_tool.py normalize problems/luogu/P1001
```

## add

把一组输入/答案复制到 `data/`：

```bash
python3 scripts/problem-analysis-tools/data_tool.py add problems/luogu/P1001 --input in3 --answer out3
```

指定保存名：

```bash
python3 scripts/problem-analysis-tools/data_tool.py add problems/luogu/P1001 \
  --input custom.in \
  --answer custom.out \
  --name hard-case
```

输出：

```text
data/hard-case.in
data/hard-case.out
```

## copy-samples-to-data

把根目录的 `in/out`、`in1/out1` 等样例复制到 `data/`：

```bash
python3 scripts/problem-analysis-tools/data_tool.py copy-samples-to-data problems/luogu/P1001
```

如需覆盖已有文件：

```bash
python3 scripts/problem-analysis-tools/data_tool.py copy-samples-to-data problems/luogu/P1001 --force
```

