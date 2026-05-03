#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include "system.h"

#define CYAN  "\033[36m"
#define RESET "\033[0m"

int main() {

    const char *logo[] = {
        "       __     _       _     ",
        "      / _|   | |     | |    ",
        "  ___| |_ ___| |_ ___| |__  ",
        " / __|  _/ _ \\ __/ __| '_ \\ ",
        "| (__| ||  __/ || (__| | | |",
        " \\___|_| \\___|\\__\\___|_| |_|",
        "                            ",
        "                            "
    };

    char cpu[256] = {0};
    char gpu[1024] = {0};
    char ram[256] = {0};
    char up[128] = {0};
    char shell[128] = {0};
    char disk[256] = {0};
    char distro[128];

    struct utsname u;
    uname(&u);

    get_cpu(cpu);
    get_gpu(gpu);
    get_ram(ram);
    get_uptime(up);
    get_shell(shell);
    get_disk(disk);
    get_distro(distro);

    printf("%s   OS:      %s\n", logo[0], distro);
    printf("%s   Kernel:  %s\n", logo[1], u.release);
    printf("%s   CPU:     %s\n", logo[2], cpu);
    printf("%s   %s\n", logo[3], gpu);
    printf("%s   RAM:     %s\n", logo[4], ram);
    printf("%s   Uptime:  %s\n", logo[5], up);
    printf("%s   Shell:   %s\n", logo[6], shell);
    printf("%s   Disk:    %s\n", logo[7], disk);

    printf("\n");
    return 0;
}