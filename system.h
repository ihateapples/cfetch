#ifndef SYSTEM_H
#define SYSTEM_H

void get_cpu(char *out);
void get_gpu(char *out);
void get_ram(char *out);
void get_uptime(char *out);
void get_shell(char *out);
void get_disk(char *out);
void get_distro(char *out);

#endif