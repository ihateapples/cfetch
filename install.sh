set -e

echo "[*] Building cfetch..."

make

echo "[*] Installing to /usr/local/bin..."

# ensure target exists
if [ ! -d "/usr/local/bin" ]; then
    echo "[!] /usr/local/bin not found, creating it..."
    sudo mkdir -p /usr/local/bin
fi

sudo cp cfetch /usr/local/bin/cfetch
sudo chmod +x /usr/local/bin/cfetch

echo "[✓] Installed successfully!"
echo "[✓] Run it with: cfetch"