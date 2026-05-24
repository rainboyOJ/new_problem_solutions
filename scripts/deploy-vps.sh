#!/usr/bin/env bash
set -euo pipefail

APP_DIR="${APP_DIR:-/srv/rbook}"
SERVICE_NAME="${SERVICE_NAME:-problems-solution}"
BRANCH="${BRANCH:-master}"
NODE_ENV="${NODE_ENV:-production}"
COMPOSE_PROJECT_NAME="${COMPOSE_PROJECT_NAME:-problems-solution}"

cd "$APP_DIR"

echo "Deploying $(pwd) from branch $BRANCH"

git fetch origin "$BRANCH"
git reset --hard "origin/$BRANCH"

export SERVICE_NAME NODE_ENV COMPOSE_PROJECT_NAME

if docker compose version >/dev/null 2>&1; then
  compose=(docker compose)
elif command -v docker-compose >/dev/null 2>&1; then
  compose=(docker-compose)
else
  echo "Docker Compose is not installed. Install the Docker Compose plugin first." >&2
  exit 1
fi

"${compose[@]}" up -d --build --remove-orphans
"${compose[@]}" ps
