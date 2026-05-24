#!/usr/bin/env bash
set -euo pipefail

APP_DIR="${APP_DIR:-/srv/rbook}"
SERVICE_NAME="${SERVICE_NAME:-problems-solution}"
BRANCH="${BRANCH:-master}"
NODE_ENV="${NODE_ENV:-production}"

cd "$APP_DIR"

echo "Deploying $(pwd) from branch $BRANCH"

git fetch origin "$BRANCH"
git reset --hard "origin/$BRANCH"

npm ci --omit=dev
npm run generate:problems

sudo systemctl restart "$SERVICE_NAME"
sudo systemctl --no-pager --full status "$SERVICE_NAME"
