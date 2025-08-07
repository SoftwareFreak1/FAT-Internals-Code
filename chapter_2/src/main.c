#include <stdio.h>
#include <string.h>
#include "disk.h"
#define VOLUME_LABEL_ADDRESS 0x2B
#define VOLUME_LABEL_SIZE 11

void update_volume_label(Disk *disk);
void read_volume_label(Disk *disk);

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("./run.sh [disk file]\n");
        return -1;
    }

    
    Disk *disk = disk_open(argv[1]);
    if(disk == NULL) {
        printf("can't open disk file\n");
        return -1;
    }

    update_volume_label(disk);
    read_volume_label(disk);

    disk_close(disk);

    return 0;
}

void update_volume_label(Disk *disk) {
    // the new label must be padded with spaces when not exactly 11 characters long
    uint8_t buffer[VOLUME_LABEL_SIZE];
    memcpy(buffer, "NEW_LABEL  ", VOLUME_LABEL_SIZE);

    disk_write(disk, VOLUME_LABEL_ADDRESS, VOLUME_LABEL_SIZE, buffer);
}

void read_volume_label(Disk *disk) {
    uint8_t buffer[VOLUME_LABEL_SIZE];
    disk_read(disk, VOLUME_LABEL_ADDRESS, VOLUME_LABEL_SIZE, buffer);

    // null terminates volume label
    char volume_label[VOLUME_LABEL_SIZE + 1];
    strncpy(volume_label, (char*) buffer, VOLUME_LABEL_SIZE);
    volume_label[VOLUME_LABEL_SIZE] = '\0';

    printf("The volume label is '%s'\n", volume_label);
}
