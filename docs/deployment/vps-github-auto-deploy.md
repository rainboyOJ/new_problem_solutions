# VPS + GitHub + Docker 自动部署教程

目标：每次 push 到 GitHub 的 `master` 分支后，GitHub Actions 自动区分应用变更与内容变更。应用变更构建镜像并重启服务；只修改 `problems/` 或 `problem-sets/` 时，VPS 更新 Git 后热刷新内容，不重建镜像、不重启容器。

最终链路：

```text
git push origin master
  -> GitHub Actions
  -> SSH 到 VPS
  -> /srv/rbook/scripts/deploy-vps.sh
  -> 内容变更: SIGUSR2 排空请求 -> git reset -> 写 revision -> SIGHUP
  -> 应用变更: build/push/pull image -> docker compose --force-recreate
  -> Actions 等待 /api/health/content 的 activeRevision
```

## 1. 准备本地项目

确认项目里有这些文件：

```text
Dockerfile
docker-compose.yml
.dockerignore
.github/workflows/deploy.yml
scripts/deploy-vps.sh
```

本地可以先检查：

```bash
npm test
```

服务直接从仓库内容构建内存目录。frontmatter 在启动或热刷新时扫描，Markdown 正文在首次请求时渲染，不需要预生成运行时索引文件。

Docker 镜像由 GitHub Actions 构建并推送到 GitHub Container Registry，即 `ghcr.io/rainboyoj/new_problem_solutions:master`。VPS 部署时会优先从 `ghcr.nju.edu.cn` 拉取，失败后依次 fallback 到 `gh-proxy.org` 和原始 `ghcr.io`，最终统一 tag 成本地镜像 `problems-solution:deploy` 给 Docker Compose 使用。镜像不包含运行时内容目录，部署时由 `docker-compose.yml` 把 VPS 仓库里的 `./problems` 和 `./problem-sets` 只读挂载到容器的 `/app/problems` 与 `/app/problem-sets`。这样可以避免把题目解析和题目单内容重复打进每个镜像层。

## 2. VPS 安装基础环境

SSH 登录 VPS：

```bash
ssh root@YOUR_VPS_IP
```

安装基础工具：

```bash
apt update
apt install -y git curl python3 nginx ca-certificates
```

安装 Docker Engine 和 Compose 插件。推荐使用 Docker 官方源：

```bash
install -m 0755 -d /etc/apt/keyrings
curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
chmod a+r /etc/apt/keyrings/docker.asc

echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" \
  > /etc/apt/sources.list.d/docker.list

apt update
apt install -y docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
docker --version
docker compose version
```

如果你的 VPS 不是 Ubuntu，请按 Docker 官方文档选择对应系统的安装方式。

## 3. 创建部署用户和项目目录

建议不要直接用 root 部署。

```bash
adduser --disabled-password --gecos "" rbook
usermod -aG docker rbook
mkdir -p /srv/rbook
chown -R rbook:rbook /srv/rbook
```

`rbook` 加入 `docker` 组后，需要重新登录该用户，组权限才会生效。

## 4. 在 VPS 上准备部署目录

切换到 `rbook` 用户：

```bash
su - rbook
```

确认目录权限：

```bash
mkdir -p /srv/rbook
cd /srv/rbook
```

## 5. Clone 项目到 VPS

仍然用 `rbook` 用户执行：

```bash
git clone https://gh-proxy.com/https://github.com/rainboyOJ/new_problem_solutions.git /srv/rbook
cd /srv/rbook
```

检查远端地址：

```bash
git remote -v
```

应该看到：

```text
origin  https://gh-proxy.com/https://github.com/rainboyOJ/new_problem_solutions.git (fetch)
origin  https://gh-proxy.com/https://github.com/rainboyOJ/new_problem_solutions.git (push)
```

后续 `scripts/deploy-vps.sh` 里的 `git fetch origin "$BRANCH"` 会继续使用这个 HTTPS 远端地址，不需要在 VPS 上额外配置 GitHub SSH deploy key。

注意：这个项目要独立部署，`problems/` 和 `problem-sets/` 都应该是仓库里的真实目录，而不是指向你本地电脑其它项目的软链接。Docker Compose 会把 `/srv/rbook/problems` 和 `/srv/rbook/problem-sets` 挂载到容器里。

检查：

```bash
ls -ld problems problem-sets
test -L problems && echo "problems is symlink" || echo "problems is real directory"
test -L problem-sets && echo "problem-sets is symlink" || echo "problem-sets is real directory"
```

如果输出任一目录是 symlink，请先把真实内容目录复制进仓库，再重新提交。

## 5.1 轻量部署规则

workflow 会根据本次 push 的变更路径决定是否重建镜像：

- 只有 `problems/` 和/或 `problem-sets/` 发生变化：
  跳过镜像构建与拉取。运行中的服务先拒绝新内容请求并排空已有请求，VPS 再更新 Git、写入目标 revision 并发送 `SIGHUP`；容器 ID 不变。
- 只要还有任何其它路径变化：
  重新构建并拉取镜像，然后用 Docker Compose 重建容器。

热刷新后，Actions 等待 `/api/health/content` 报告预期的 `activeRevision`。单个无效条目会被排除并使 workflow 失败；目录级错误会使内容路由返回 503，不会回滚 Git。

## 6. 准备 GHCR 镜像

首次部署前，先在 GitHub 页面手动运行一次 workflow，让 Actions 构建并推送镜像：

```text
GitHub 仓库 -> Actions -> Deploy to VPS -> Run workflow -> Branch: master
```

如果这是仓库第一次推送 GHCR 镜像，运行成功后打开：

```text
GitHub 仓库 -> Packages -> new_problem_solutions
```

建议把 package visibility 设置为 Public。公开镜像可以让 VPS 匿名 `docker pull`，手动排查时更省事。

如果 package 保持 Private，GitHub Actions 自动部署时会临时用 `GITHUB_TOKEN` 登录 GHCR。你手动在 VPS 上执行 `docker compose pull` 或 `bash scripts/deploy-vps.sh` 时，需要先登录 GHCR：

```bash
docker login ghcr.io -u YOUR_GITHUB_USERNAME
```

密码使用 GitHub Personal Access Token，至少需要 `read:packages` 权限。

部署脚本默认给每个 `docker pull` 候选地址设置 300 秒超时。这样 VPS 到某个镜像源网络卡住时，会自动尝试下一个候选地址；全部失败时旧容器会继续运行，GitHub Actions 会明确失败，便于排查。

## 7. 首次启动 Docker 服务

在 VPS 上用 `rbook` 用户执行：

```bash
cd /srv/rbook
bash scripts/deploy-vps.sh
docker compose ps
```

检查本机访问：

```bash
curl -fsS http://127.0.0.1:3300/api/problems?limit=1
```

查看日志：

```bash
docker compose logs -f problems-solution
```

确认题目目录和题目单目录都已挂载到容器：

```bash
docker compose exec problems-solution ls -ld /app/problems
docker compose exec problems-solution ls -ld /app/problem-sets
```

如果你之前按旧教程创建过 systemd 服务，需要先用 root 停掉旧服务，避免它占用 `3000` 端口：

```bash
systemctl disable --now problems-solution
```

## 8. 配置 Nginx 反向代理

退出到 root：

```bash
exit
```

创建 Nginx 配置：

```bash
cat > /etc/nginx/sites-available/problems-solution <<'EOF'
server {
    listen 80;
    server_name YOUR_DOMAIN_OR_IP;

    location / {
        proxy_pass http://127.0.0.1:3300;
        proxy_http_version 1.1;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;
    }
}
EOF

ln -sf /etc/nginx/sites-available/problems-solution /etc/nginx/sites-enabled/problems-solution
nginx -t
systemctl reload nginx
```

浏览器访问：

```text
http://YOUR_DOMAIN_OR_IP/
```

如果你有域名，后续可以用 certbot 配置 HTTPS。

## 9. 给 GitHub Actions 配置 SSH 登录 VPS

在你的本地电脑生成一把专门给 GitHub Actions 登录 VPS 的 key：

```bash
ssh-keygen -t ed25519 -C "github-actions-rbook" -f ./github_actions_rbook -N ""
```

把公钥复制到 VPS 的 `rbook` 用户：

```bash
ssh-copy-id -i ./github_actions_rbook.pub rbook@YOUR_VPS_IP
```

测试：

```bash
ssh -i ./github_actions_rbook rbook@YOUR_VPS_IP "cd /srv/rbook && docker compose ps"
```

然后打开 GitHub 仓库：

```text
Settings -> Secrets and variables -> Actions -> New repository secret
```

添加这些 secrets：

```text
VPS_HOST          = YOUR_VPS_IP
VPS_USER          = rbook
VPS_SSH_KEY       = github_actions_rbook 私钥全文
VPS_APP_DIR       = /srv/rbook
VPS_SERVICE_NAME  = problems-solution
CONTENT_HEALTH_TOKEN = 一段足够长的随机字符串
```

`VPS_APP_DIR` 和 `VPS_SERVICE_NAME` 可以不填，workflow 默认使用 `/srv/rbook` 和 `problems-solution`。镜像地址不需要配置 secret，workflow 会自动使用当前仓库生成 `ghcr.io/rainboyoj/new_problem_solutions:master`，并在部署时临时登录 GHCR 拉取镜像。如果你的 SSH 端口不是 22，需要在 `.github/workflows/deploy.yml` 的 `ssh` 命令里加 `-p YOUR_PORT`，并在 `ssh-keyscan` 里加 `-p YOUR_PORT`。

`VPS_SSH_KEY` 填私钥内容：

```bash
cat ./github_actions_rbook
```

复制完整输出，包括：

```text
-----BEGIN OPENSSH PRIVATE KEY-----
...
-----END OPENSSH PRIVATE KEY-----
```

## 10. 首次手动测试部署脚本

在 VPS 上用 `rbook` 用户执行：

```bash
ssh rbook@YOUR_VPS_IP
cd /srv/rbook
bash scripts/deploy-vps.sh
```

成功后应该看到：

```text
problems-solution ... Up
```

如果这里失败，先修 VPS 本地问题，再测试 GitHub Actions。

## 11. Push 触发自动部署

本地提交并 push：

```bash
git add .
git commit -m "Configure Docker based VPS auto deploy"
git push origin master
```

打开 GitHub 仓库：

```text
Actions -> Deploy to VPS
```

查看 workflow 日志。应用变更会构建并推送 GHCR 镜像，镜像拉取按 `ghcr.nju.edu.cn`、`gh-proxy.org`、`ghcr.io` 的顺序 fallback；内容变更只刷新挂载目录，不拉镜像。宿主机暴露端口是 `127.0.0.1:3300`。

## 12. 日常使用

以后只需要：

```bash
git push origin master
```

VPS 会自动更新。

查看服务状态：

```bash
ssh rbook@YOUR_VPS_IP
cd /srv/rbook
docker compose ps
```

查看日志：

```bash
docker compose logs -f problems-solution
```

手动部署：

```bash
cd /srv/rbook
bash scripts/deploy-vps.sh
```

## 13. 常见问题

### GitHub Actions 报 Permission denied

检查：

- `VPS_SSH_KEY` 是否是私钥，不是 `.pub` 公钥。
- VPS 用户名是否正确。
- 公钥是否已经写入 VPS 用户的 `~/.ssh/authorized_keys`。

### docker compose 权限失败

检查 `rbook` 是否在 `docker` 组：

```bash
id rbook
```

如果没有 `docker`：

```bash
usermod -aG docker rbook
```

然后重新登录 `rbook` 用户。

### 内容 revision 没更新

检查公开内容健康接口和容器日志：

```bash
cd /srv/rbook
curl -sS http://127.0.0.1:3300/api/health/content | python3 -m json.tool
docker compose logs --tail=100 problems-solution
```

详细错误接口需要部署时配置的 token：

```bash
curl -sS -H "Authorization: Bearer $CONTENT_HEALTH_TOKEN" \
  http://127.0.0.1:3300/api/health/content/details | python3 -m json.tool
```

### 服务启动失败

查看日志：

```bash
docker compose logs --tail=100 problems-solution
```

常见原因：

- VPS 仓库里的 `problems/` 不存在，或不是一个真实目录。
- VPS 无法从所有候选镜像源拉取 `ghcr.io/rainboyoj/new_problem_solutions:master`。
- `127.0.0.1:3300` 已被其它进程占用。
- Nginx 反向代理配置里的端口和 Compose 暴露端口不一致。

### VPS 拉取 GHCR 镜像失败

先检查 VPS 能否访问候选镜像源：

```bash
curl -I https://ghcr.io/v2/
curl -I https://ghcr.nju.edu.cn/v2/
docker pull ghcr.nju.edu.cn/rainboyoj/new_problem_solutions:master
docker pull gh-proxy.org/docker/ghcr.io/rainboyoj/new_problem_solutions:master
docker pull ghcr.io/rainboyoj/new_problem_solutions:master
```

如果 package 是 Private，需要先登录：

```bash
docker login ghcr.io -u YOUR_GITHUB_USERNAME
```

如果网络超时，说明 VPS 到 `ghcr.io` 的网络也不稳定。此时可以给 Docker 配代理，或者改用国内/自建 registry 镜像仓库。

### 想部署非 master 分支

修改 `.github/workflows/deploy.yml`：

```yaml
on:
  push:
    branches:
      - main
```

或者把 `master` 换成你实际使用的分支名。
