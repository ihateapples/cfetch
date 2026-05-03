#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/statvfs.h>
#include "system.h"

/* ---------------- CPU ---------------- */
void get_cpu(char *out) {
    FILE *f = fopen("/proc/cpuinfo", "r");
    if (!f) {
        strcpy(out, "unknown");
        return;
    }

    char line[256];

    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "model name", 10) == 0) {
            strcpy(out, strchr(line, ':') + 2);
            out[strcspn(out, "\n")] = 0;
            fclose(f);
            return;
        }
    }

    fclose(f);
    strcpy(out, "unknown");
}

/* ---------------- GPU (MULTI) ---------------- */
void get_gpu(char *out) {
    FILE *f = popen("lspci | grep -Ei 'vga|3d|display'", "r");
    if (!f) {
        strcpy(out, "GPU 0: unknown");
        return;
    }

    char line[256];
    char buffer[1024] = {0};
    int i = 0;

    while (fgets(line, sizeof(line), f)) {

        line[strcspn(line, "\n")] = 0;

        // find SECOND colon (skip PCI address)
        char *first = strchr(line, ':');
        if (!first) continue;
        char *second = strchr(first + 1, ':');

        char *desc = second ? second + 2 : first + 2;

        // clean common prefixes
        if (strstr(desc, "VGA compatible controller"))
            desc = strstr(desc, "VGA compatible controller") + 25;

        if (strstr(desc, "3D controller"))
            desc = strstr(desc, "3D controller") + 14;

        char tmp[512];

        snprintf(tmp, sizeof(tmp), "GPU %d: %.200s\n", i++, desc);

        strcat(buffer, tmp);
    }

    pclose(f);

    if (i == 0) {
        strcpy(out, "GPU 0: unknown");
        return;
    }

    buffer[strlen(buffer) - 1] = 0;
    strcpy(out, buffer);
}

/* ---------------- RAM ---------------- */
void get_ram(char *out) {
    FILE *f = fopen("/proc/meminfo", "r");
    if (!f) {
        strcpy(out, "unknown");
        return;
    }

    char line[256];
    long total = 0, avail = 0;

    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "MemTotal", 8) == 0)
            sscanf(line, "MemTotal: %ld", &total);
        if (strncmp(line, "MemAvailable", 12) == 0)
            sscanf(line, "MemAvailable: %ld", &avail);
    }

    fclose(f);

    sprintf(out, "%ld MB / %ld MB",
            (total - avail) / 1024,
            total / 1024);
}

/* ---------------- UPTIME ---------------- */
void get_uptime(char *out) {
    FILE *f = fopen("/proc/uptime", "r");
    if (!f) {
        strcpy(out, "unknown");
        return;
    }

    double up;
    fscanf(f, "%lf", &up);
    fclose(f);

    int min = (int)up / 60;
    int hr = min / 60;
    min %= 60;

    sprintf(out, "%dh %dm", hr, min);
}

/* ---------------- SHELL ---------------- */
void get_shell(char *out) {
    char *s = getenv("SHELL");
    if (!s) s = "unknown";
    strcpy(out, s);
}

/* ---------------- DISK ---------------- */
void get_disk(char *out) {
    struct statvfs v;

    if (statvfs("/", &v) != 0) {
        strcpy(out, "unknown");
        return;
    }

    unsigned long total = v.f_blocks * v.f_frsize;
    unsigned long free = v.f_bfree * v.f_frsize;

    unsigned long used = (total - free) / (1024 * 1024);
    unsigned long total_mb = total / (1024 * 1024);

    sprintf(out, "%lu MB / %lu MB", used, total_mb);
}