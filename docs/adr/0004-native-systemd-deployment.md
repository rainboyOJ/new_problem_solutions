---
status: accepted
---

# Deploy immutable releases with SSH and systemd

生产部署由开发机生成与 Git commit 对应的不可变 release，通过 SSH 和 rsync
传到 VPS，再由 systemd 直接运行 Node.js 服务。GitHub Actions 只负责代码验证，
不构建容器镜像、不保存 VPS 密钥，也不触发生产部署。

release 必须通过 `git archive` 从目标 commit 生成，不能复制当前工作目录。这样
既能保证发布内容可以追溯，也能排除 `problems/` 下被 Git 忽略的分析工作区、
对拍产物和临时文件。

## Consequences

VPS 的 `/opt/problems-solution/current` 是指向当前 release 的符号链接。部署先在
随机端口以低权限用户启动候选版本；候选版本健康后再切换软链接并重启
`problems-solution.service`。本机端口或公网健康检查失败时，部署脚本恢复上一
release 并重新启动服务。

生产依赖按 `package-lock.json` 哈希、操作系统、CPU 架构和 Node ABI 缓存。只有
缓存不存在时才上传依赖包。服务器不需要访问 GitHub，也不需要 GitHub Deploy
Key 或 GHCR Token。

所有发布都通过重启服务激活，包括只修改 `problems/` 或 `problem-sets/` 的提交。
这取代 ADR 0002 中依赖 Docker bind mount 和运行中 Git worktree 的部署方式。
应用仍保留 `SIGHUP` 内容刷新能力，但原生发布流程不依赖它。

首次迁移允许脚本检测、停止并在失败时恢复旧的 `problems-solution` 容器。原生
服务通过全部检查后删除旧容器；后续部署路径不需要 Docker。
