# VPS + GitHub 自动部署教程

目标：每次 push 到 GitHub 的 `master` 分支后，GitHub Actions 自动 SSH 到 VPS，拉取最新代码，重新生成 `problems.json`，并重启 rbook 服务。

最终链路：

```text
git push origin master
  -> GitHub Actions
  -> SSH 到 VPS
  -> /srv/rbook/scripts/deploy-vps.sh
  -> git reset --hard origin/master
  -> npm ci --omit=dev
  -> npm run generate:problems
  -> systemctl restart rbook
```

## 1. 准备本地项目

确认项目里有这些文件：

```text
.github/workflows/deploy.yml
scripts/deploy-vps.sh
scripts/generate-problems-json.js
docs/deployment/vps-github-auto-deploy.md
```

确认 npm 命令可用：

```bash
npm test
npm run generate:problems
```

`generate:problems` 会扫描本项目的 `problems/` 目录，生成根目录的 `problems.json`。部署时会在 VPS 上重新执行这一步。

## 2. VPS 安装基础环境

SSH 登录 VPS：

```bash
ssh root@YOUR_VPS_IP
```

安装基础工具：

```bash
apt update
apt install -y git curl nginx
```

安装 Node.js。推荐使用 NodeSource 的 LTS 源：

```bash
curl -fsSL https://deb.nodesource.com/setup_lts.x | bash -
apt install -y nodejs
node -v
npm -v
```

## 3. 创建运行用户和项目目录

建议不要直接用 root 跑服务。

```bash
adduser --disabled-password --gecos "" rbook
mkdir -p /srv/rbook
chown -R rbook:rbook /srv/rbook
```

如果你已经有自己的部署用户，可以复用已有用户，把后续命令里的 `rbook` 用户替换掉。

## 4. 在 VPS 上配置 SSH 拉取 GitHub 仓库

切换到运行用户：

```bash
su - rbook
```

生成 VPS 用于拉取 GitHub 仓库的 SSH key：

```bash
ssh-keygen -t ed25519 -C "rbook-vps-deploy" -f ~/.ssh/rbook_github -N ""
cat ~/.ssh/rbook_github.pub
```

到 GitHub 仓库页面：

```text
Settings -> Deploy keys -> Add deploy key
```

填写：

- Title: `rbook-vps`
- Key: 粘贴刚才 `cat ~/.ssh/rbook_github.pub` 的输出
- Allow write access: 不勾选

在 VPS 上配置 SSH host：

```bash
cat > ~/.ssh/config <<'EOF'
Host github.com
  HostName github.com
  User git
  IdentityFile ~/.ssh/rbook_github
  IdentitiesOnly yes
EOF

chmod 600 ~/.ssh/config
ssh -T git@github.com
```

第一次会提示确认 GitHub host key，输入 `yes`。

## 5. Clone 项目到 VPS

仍然用 `rbook` 用户执行：

```bash
git clone git@github.com:YOUR_GITHUB_USER/YOUR_REPO.git /srv/rbook
cd /srv/rbook
npm ci --omit=dev
npm run generate:problems
```

注意：这个项目要独立部署，`problems/` 应该是仓库里的真实目录，而不是指向你本地电脑其它项目的软链接。

可以检查：

```bash
ls -ld problems
test -L problems && echo "problems is symlink" || echo "problems is real directory"
```

如果输出 `problems is symlink`，请先把真实题目目录复制进仓库，再重新提交。

## 6. 创建 systemd 服务

退出到 root：

```bash
exit
```

创建服务文件：

```bash
cat > /etc/systemd/system/rbook.service <<'EOF'
[Unit]
Description=rbook Fastify server
After=network.target

[Service]
Type=simple
User=rbook
Group=rbook
WorkingDirectory=/srv/rbook
Environment=NODE_ENV=production
Environment=PORT=3000
Environment=HOST=127.0.0.1
ExecStart=/usr/bin/npm start
Restart=always
RestartSec=3

[Install]
WantedBy=multi-user.target
EOF
```

启动并设置开机自启：

```bash
systemctl daemon-reload
systemctl enable rbook
systemctl start rbook
systemctl status rbook --no-pager --full
```

本机检查：

```bash
curl -fsS http://127.0.0.1:3000/api/problems?limit=1
```

## 7. 配置 Nginx 反向代理

创建 Nginx 配置：

```bash
cat > /etc/nginx/sites-available/rbook <<'EOF'
server {
    listen 80;
    server_name YOUR_DOMAIN_OR_IP;

    location / {
        proxy_pass http://127.0.0.1:3000;
        proxy_http_version 1.1;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;
    }
}
EOF

ln -sf /etc/nginx/sites-available/rbook /etc/nginx/sites-enabled/rbook
nginx -t
systemctl reload nginx
```

浏览器访问：

```text
http://YOUR_DOMAIN_OR_IP/
```

如果你有域名，后续可以用 certbot 配置 HTTPS。

## 8. 允许部署用户重启服务

GitHub Actions 会 SSH 到 VPS 执行 `scripts/deploy-vps.sh`。这个脚本最后会执行：

```bash
sudo systemctl restart rbook
```

所以需要允许部署用户免密码重启这个服务。

如果 GitHub Actions SSH 使用 `rbook` 用户：

```bash
cat > /etc/sudoers.d/rbook-deploy <<'EOF'
rbook ALL=(root) NOPASSWD: /bin/systemctl restart rbook, /bin/systemctl status rbook, /usr/bin/systemctl restart rbook, /usr/bin/systemctl status rbook
EOF

chmod 440 /etc/sudoers.d/rbook-deploy
visudo -c
```

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
ssh -i ./github_actions_rbook rbook@YOUR_VPS_IP "cd /srv/rbook && pwd"
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
VPS_SERVICE_NAME  = rbook
```

`VPS_APP_DIR` 和 `VPS_SERVICE_NAME` 可以不填，workflow 默认使用 `/srv/rbook` 和 `rbook`。如果你的 SSH 端口不是 22，需要在 `.github/workflows/deploy.yml` 的 `ssh` 命令里加 `-p YOUR_PORT`，并在 `ssh-keyscan` 里加 `-p YOUR_PORT`。

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

在 VPS 上用部署用户执行：

```bash
ssh rbook@YOUR_VPS_IP
cd /srv/rbook
bash scripts/deploy-vps.sh
```

成功后应该看到：

```text
Generated problems.json with ... problems.
Active: active (running)
```

如果这里失败，先修 VPS 本地问题，不要急着测试 GitHub Actions。

## 11. Push 触发自动部署

本地提交并 push：

```bash
git add .
git commit -m "Configure VPS auto deploy"
git push origin master
```

打开 GitHub 仓库：

```text
Actions -> Deploy to VPS
```

查看 workflow 日志。如果成功，VPS 会自动拉取最新代码、生成 `problems.json` 并重启服务。

## 12. 日常使用

以后只需要：

```bash
git push origin master
```

VPS 会自动更新。

查看服务状态：

```bash
ssh rbook@YOUR_VPS_IP
systemctl status rbook --no-pager --full
```

查看日志：

```bash
journalctl -u rbook -f
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

### deploy script 执行 sudo 失败

检查：

```bash
sudo -l
cat /etc/sudoers.d/rbook-deploy
visudo -c
```

确认允许执行 `systemctl restart rbook`。

### problems.json 没更新

检查 VPS 上是否有真实 `problems/` 目录：

```bash
cd /srv/rbook
ls -ld problems
npm run generate:problems
```

### 服务启动失败

查看日志：

```bash
journalctl -u rbook -n 100 --no-pager
```

常见原因：

- `problems/` 不存在。
- `npm ci --omit=dev` 没成功。
- `PORT` 已被其它进程占用。
- `systemd` 的 `WorkingDirectory` 路径不对。

### 想部署非 master 分支

修改 `.github/workflows/deploy.yml`：

```yaml
on:
  push:
    branches:
      - main
```

或者把 `master` 换成你实际使用的分支名。
