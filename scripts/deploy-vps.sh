#!/usr/bin/env bash
set -euo pipefail

APP_DIR="${APP_DIR:-/srv/rbook}"
SERVICE_NAME="${SERVICE_NAME:-problems-solution}"
BRANCH="${BRANCH:-master}"
NODE_ENV="${NODE_ENV:-production}"
COMPOSE_PROJECT_NAME="${COMPOSE_PROJECT_NAME:-problems-solution}"
IMAGE_REF="${IMAGE_REF:-ghcr.io/rainboyoj/new_problem_solutions:master}"
GHCR_USERNAME="${GHCR_USERNAME:-}"
GHCR_TOKEN_B64="${GHCR_TOKEN_B64:-}"

cd "$APP_DIR"

echo "Deploying $(pwd) from branch $BRANCH"

git fetch origin "$BRANCH"
git reset --hard "origin/$BRANCH"

export SERVICE_NAME NODE_ENV COMPOSE_PROJECT_NAME IMAGE_REF

if docker compose version >/dev/null 2>&1; then
  compose=(docker compose)
elif command -v docker-compose >/dev/null 2>&1; then
  compose=(docker-compose)
else
  echo "Docker Compose is not installed. Install the Docker Compose plugin first." >&2
  exit 1
fi

if [[ -n "$GHCR_USERNAME" && -n "$GHCR_TOKEN_B64" ]]; then
  printf '%s' "$GHCR_TOKEN_B64" | base64 -d | docker login ghcr.io -u "$GHCR_USERNAME" --password-stdin
fi

"${compose[@]}" pull
"${compose[@]}" up -d --remove-orphans
"${compose[@]}" ps
