# 样例、对拍与官方数据

## 工具

工具位于 `scripts/problem-analysis-tools/`：`list_tags.py` 查询已有标签；`gen_random.py` 生成通用随机数据；`duipai.py` 非交互对拍；`duipai-human.py` 人工包装；`check_sample.py` 运行样例和 `data/*.in`；USACO 另有 `fetch_usaco_testdata.py`。

普通算法题可在输入格式清晰且暴力规模受控时补全 `gen.py`。生成器要服务于暴力规模，例如子集 `n <= 15`、排列 `n <= 8`，搜索限制节点/步数，数位或状态递归限制长度/状态数；不要生成满规模数据导致基线超时。

## 对拍

只有 `gen.py`、最终程序和可靠 `brute.cpp` 都存在且可运行，或用户明确要求时，才执行：

```bash
python3 scripts/problem-analysis-tools/duipai.py \
  --gen problems/<oj>/<problem_id>/gen.py \
  --user problems/<oj>/<problem_id>/main.cpp \
  --brute problems/<oj>/<problem_id>/brute.cpp -n 200
```

根据实际语言或文件名调整 `--user`。报告写入 `problem-analysis-workspace/duipai-report.md`；未运行或失败必须记录原因，不能暗示“已对拍”。

## USACO

USACO 优先使用官方数据：

```bash
python3 scripts/problem-analysis-tools/fetch_usaco_testdata.py problems/usaco/<cpid>
python3 scripts/problem-analysis-tools/check_sample.py problems/usaco/<cpid> --timeout 3 --memory-mb 256
```

下载后先阅读官方 `Solution` URL，再定稿代码。只有官方数据不可用、通过但边界/变换可疑、文章需要展示暴力到正解，或用户明确要求时才额外对拍。若检查工具因根目录 `in` 没有答案而报告 `NO_ANSWER`，但所有 `data/*.in` 通过且无失败，可接受；把命令和结果记入 `04-correctness-and-edge-cases.md`。

## 安全

测试是证据而非正确性证明。只报告实际执行的命令和结果；不声称代码已被 OJ 接受，不把不可靠暴力作为可信基线。
