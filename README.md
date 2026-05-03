# cfetch

a lightweight system info tool written in c

cfetch prints basic system information in a clean layout. 

---

## showcase

![cfetch](https://files.catbox.moe/193rbu.png)

---

## features

- cpu info from /proc/cpuinfo
- gpu detection via lspci (supports multiple gpus)
- ram usage
- uptime
- shell detection
- disk usage
---

## automatic install (adds cfetch command to path)

there’s an install script that builds and installs cfetch system-wide.

```bash
chmod +x install.sh
./install.sh
cfetch
{output}
```

## manual build (doesn't add to path)

```bash
make
```

# License
cFetch is licensed under MIT. 
