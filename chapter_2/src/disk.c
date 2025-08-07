#include "disk.h"
#include <stdio.h>
#include <stdlib.h>

struct Disk {
    FILE* file;
};

Disk* disk_open(char* path) {
    // opens the file for binary reading and writing
    FILE *file = fopen(path, "rb+");
    if (!file) return NULL;

    Disk *disk = malloc(sizeof(Disk));
    disk->file = file;
    return disk;
}

void disk_read(
    Disk *disk,
    unsigned int address,
    unsigned int count,
    uint8_t* buffer
) {
    fseek(disk->file, address, SEEK_SET);
    fread(buffer, count, 1, disk->file);
}

void disk_write(
    Disk *disk,
    unsigned int address,
    unsigned int count,
    uint8_t* buffer
) {
    fseek(disk->file, address, SEEK_SET);
    fwrite(buffer, count, 1, disk->file);
}

void disk_close(Disk *disk) {
    fclose(disk->file);
    free(disk);
}
