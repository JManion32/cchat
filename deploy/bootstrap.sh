#!/usr/bin/env bash
#
# One-time droplet setup.
# bash deploy/bootstrap.sh

set -euo pipefail

TCP_PORT="${TCP_PORT:-5000}"   # C++ server
WS_PORT="${WS_PORT:-8080}"     # gateway WebSocket, reached by browsers

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
[ "$(id -u)" -eq 0 ] && SUDO="" || SUDO="sudo"

$SUDO apt-get update
$SUDO apt-get install -y nginx nodejs

# nginx runs as www-data and must traverse this home to reach client_site.
# o+x allows traversal only, not listing or reading.
chmod o+x "$HOME"
mkdir -p "$HOME/client_site" "$HOME/gateway"
chmod o+rx "$HOME/client_site"

render() {
    sed -e "s|__HOME__|$HOME|g" \
        -e "s|__USER__|$(id -un)|g" \
        -e "s|__TCP_PORT__|$TCP_PORT|g" \
        -e "s|__WS_PORT__|$WS_PORT|g" \
        "$1"
}

render "$script_dir/cchat-server.service" \
    | $SUDO tee /etc/systemd/system/cchat-server.service > /dev/null
render "$script_dir/cchat-gateway.service" \
    | $SUDO tee /etc/systemd/system/cchat-gateway.service > /dev/null
$SUDO systemctl daemon-reload

render "$script_dir/cchat.nginx.conf" \
    | $SUDO tee /etc/nginx/sites-available/cchat > /dev/null
$SUDO ln -sfn /etc/nginx/sites-available/cchat /etc/nginx/sites-enabled/cchat
# Ships enabled and also claims default_server on :80, which collides with ours.
$SUDO rm -f /etc/nginx/sites-enabled/default
$SUDO nginx -t
$SUDO systemctl reload nginx

$SUDO systemctl enable cchat-server.service cchat-gateway.service

cat <<EOF

Bootstrap complete!

Now run:

systemctl start cchat-server

EOF