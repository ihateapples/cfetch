set -e

REPO="https://github.com/ihateapples/cfetch"
TMP_DIR="/tmp/cfetch"

echo "[*] removing old temp install..."
rm -rf "$TMP_DIR"

echo "[*] cloning repository..."

git clone "$REPO" "$TMP_DIR"

cd "$TMP_DIR"

echo "[*] building cfetch..."
make

echo "[*] installing to /usr/local/bin..."

if [ ! -d "/usr/local/bin" ]; then
    echo "[!] creating /usr/local/bin..."
    sudo mkdir -p /usr/local/bin
fi

sudo install -m 755 cfetch /usr/local/bin/cfetch

echo "[*] cleaning up..."
cd /
rm -rf "$TMP_DIR"

echo "[✓] cfetch installed successfully!"
echo "[✓] run it with: cfetch"