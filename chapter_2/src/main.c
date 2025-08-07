#include <stdio.h>
#include <string.h>
#include "disk.h"
#define VOLUME_LABEL_ADDRESS 0x2B
#define VOLUME_LABEL_SIZE 11

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("./run.sh [disk file]\n");
        return -1;
    }

    uint8_t buffer[VOLUME_LABEL_SIZE];
    Disk *disk = disk_open(argv[1]);

    if(disk == NULL) {
        printf("can't open disk file\n");
        return -1;
    }

    disk_read(disk, VOLUME_LABEL_ADDRESS, VOLUME_LABEL_SIZE, buffer);
    disk_close(disk);

    // null terminates volume label
    char volume_label[VOLUME_LABEL_SIZE + 1];
    strncpy(volume_label, (char*) buffer, VOLUME_LABEL_SIZE);
    volume_label[VOLUME_LABEL_SIZE] = '\0';

    printf("The volume label is '%s'\n", volume_label);

    return 0;
}
