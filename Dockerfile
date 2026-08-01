# syntax=docker/dockerfile:1.7

FROM node:22-bookworm-slim

WORKDIR /app

ENV NODE_ENV=production
ENV HOST=0.0.0.0
ENV PORT=3000

COPY package*.json ./
COPY scripts/install-git-hooks.js ./scripts/install-git-hooks.js
RUN --mount=type=cache,target=/root/.npm npm ci --omit=dev

COPY . .

EXPOSE 3000

CMD ["node", "./bin/www"]
