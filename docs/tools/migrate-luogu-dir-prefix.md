# migrate-luogu-dir-prefix.py

位置：

```text
scripts/migrate-luogu-dir-prefix.py
```

作用：将 `problems/luogu/` 下的纯数字一级目录批量改为 `P` 前缀目录。脚本只处理目录名，不修改题目内容；`B...`、`U...`、`CF...` 等非数字目录保持不动。

默认执行 dry-run：

```bash
python3 scripts/migrate-luogu-dir-prefix.py
```

确认没有冲突后执行：

```bash
python3 scripts/migrate-luogu-dir-prefix.py --apply
```

也可以用 `--root` 对临时目录做验证，`--verbose` 输出每一条迁移计划。脚本执行前会检查所有目标目录；如果任一 `P...` 目录已存在，会整体拒绝执行。
