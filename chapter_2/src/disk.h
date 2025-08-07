#ifndef DISK_H
#define DISK_H
#include <stdint.h>

typedef struct Disk Disk;

Disk* disk_open(char* path);

void disk_read(
    Disk *disk,
    unsigned int address,
    unsigned int count,
    uint8_t *buffer
);

void disk_write(
    Disk *disk,
    unsigned int address,
    unsigned int count,
    uint8_t *buffer
);

void disk_close(Disk *disk);

#endif
