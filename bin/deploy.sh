#!/bin/bash
set -e

echo "▶ Pulling latest changes..."
git pull

echo "▶ Restarting secure-chat server..."
sudo systemctl restart secure-chat

echo "▶ Restarting cchat-gateway..."
sudo systemctl restart cchat-gateway

# Always run from the frontend directory
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
FRONTEND_DIR="$SCRIPT_DIR/../../client_site"

echo "▶ Changing to frontend directory: $FRONTEND_DIR"
cd "$FRONTEND_DIR"

echo "▶ Building frontend..."
npm run build

echo "▶ Deploying frontend to /srv/chat-site..."
sudo rsync -av --delete dist/ /srv/chat-site/

echo "✅ Deployment complete"
