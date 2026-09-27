# 本地构建与 systemd 原生部署

生产服务不使用 Docker 或 GitHub Actions 部署。本机验证并生成 release，通过
SSH 上传到 VPS，服务由 systemd 管理。

```text
干净的 master commit
  -> 本地完整验证
  -> 从 commit 导出 release
  -> 本地候选服务检查
  -> push origin/master
  -> rsync 上传 release
  -> VPS 候选服务检查
  -> 原子切换 current
  -> systemd 重启
  -> 本机与公网健康检查
  -> 失败时恢复上一 release
```

## 本机要求

本机需要 Node.js 22、npm、SSH、rsync、tar、zstd、curl 和 Python 3，并且能够通过
SSH alias `bohai` 登录 VPS。可通过环境变量覆盖主机和公网健康地址：

```bash
RBOOK_DEPLOY_HOST=example \
RBOOK_PUBLIC_HEALTH_URL=https://example.com/api/health/content \
./deploy.sh
```

先预览本次部署范围：

```bash
./deploy.sh --dry-run
```

确认后执行：

```bash
./deploy.sh
```

脚本要求当前分支为干净的 `master`，且没有落后或分叉于 `origin/master`。已经
push、但上次未成功激活的 commit 可以直接重试。

## VPS 要求

VPS 使用 systemd，并已安装系统级 Node.js 22、curl、tar、zstd、Python 3、rsync
和 util-linux。SSH 用户必须是 root，或者可以无交互执行 `sudo -n`。上传文件先
进入该 SSH 用户的 `~/.cache/problems-solution-deploy/`，激活脚本再以 root 执行。

首次部署会创建无登录权限的 `problems-solution` 用户，并建立以下目录：

```text
/opt/problems-solution/
├── current -> releases/<commit-sha>
├── releases/
├── dependencies/
├── bin/
├── deploy.env
└── deployments.log
```

生产配置保存在 `/opt/problems-solution/deploy.env`，权限为 `600`。首次迁移若能
读取旧容器，会自动继承 `CONTENT_HEALTH_TOKEN`；也可以提前手工创建配置：

```bash
install -d -m 755 /opt/problems-solution
printf '%s\n' 'CONTENT_HEALTH_TOKEN=replace-me' \
  > /opt/problems-solution/deploy.env
chmod 600 /opt/problems-solution/deploy.env
```

## Release 与依赖

release 只包含服务运行需要的已提交文件：应用入口、服务端模块、模板、静态资源、
`problems/` 和 `problem-sets/`。`.runtime/content-revision.json` 记录对应的完整
commit SHA。

生产依赖按 lockfile 哈希和运行平台缓存。部署机与 VPS 必须使用兼容的 Linux
架构和 Node ABI；平台不匹配时必须在兼容机器上构建依赖。

VPS 只保留当前和上一个 release。部署记录写入
`/opt/problems-solution/deployments.log`，不记录密钥。

## 健康检查与回滚

候选版本和正式版本必须同时满足：

- `/api/health/live` 可以响应；
- `/api/health/content` 的 `state` 为 `healthy`；
- `errorCount` 为 `0`；
- `activeRevision` 等于目标 commit。

部署前公网本来健康时，切换后公网检查失败也会触发回滚。若公网部署前已经不可用，
本机 `127.0.0.1:3300` 的检查作为最终依据。

查看服务和部署日志：

```bash
ssh bohai 'systemctl status problems-solution --no-pager'
ssh bohai 'journalctl -u problems-solution -n 100 --no-pager'
ssh bohai 'tail -20 /opt/problems-solution/deployments.log'
```

## 首次从 Docker 迁移

首次部署会先保持旧容器运行，在随机端口验证原生候选版本。候选通过后才停止旧
容器并启动 systemd 服务；如果新服务失败，会重新启动旧容器。原生服务通过本机
和公网检查后，旧容器会被删除。

确认服务稳定后，可以人工删除旧镜像并卸载 Docker。不要在首次切换前删除旧容器，
否则首次部署失败时无法恢复旧服务。

## GitHub

`.github/workflows/verify.yml` 只负责 Pull Request 验证。GitHub 不持有 VPS SSH
密钥，不构建或发布 GHCR 镜像。服务器也不需要 GitHub Deploy Key。
