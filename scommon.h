#ifndef TASK2_SCOMMON_H
#define TASK2_SCOMMON_H

#include "common.h"

// shared memory
#define DATACHANNEL_SHM_NAME "/task2-channel-data"


size_t initChannels(uint8_t* channels[1], int isReceiver) {

  size_t bufferSize = CHANNEL_BUFFER_PAGES * PAGESIZE;
  size_t channelSize = CHANNEL_INDICES * PAGESIZE;
  size_t totalSize = 2 * bufferSize + channelSize;

  int fd, retValue;
  char buffer[100];

  for (size_t i = 0; i < NUM_DATA_CHANNELS; i++) {
    sprintf(buffer, "%s-%zu", DATACHANNEL_SHM_NAME, channelIndex++);

    fd = shm_open(buffer, SHM_FLAGS, SHM_PROT);
    if (fd < 0) {
      error("File Descriptor bad %s", strerror(errno));
      exit(-1);
    }
    retValue = ftruncate(fd, totalSize); // 3 * sizeof int
    int tempint = sizeof(int);
    int tempr = 3 * sizeof(int);
    uint8_t* channelRaw = mmap( NULL, 3 * sizeof(int), MMAP_PROT, MMAP_FLAGS, fd, 0);

    /* mmap works in multiples of the page size on your system. 
    If you're doing this on i386/amd64 or actually most modern CPUs, this will be 4096.

    In the man page of mmap on my system it says: "offset must be a multiple of the page size as returned by sysconf(_SC_PAGE_SIZE).". 
    On some systems for historical reasons the length argument may be not a multiple of page size, 
    but mmap will round up to a full page in that case anyway. */

    printf("shm usage\n");

    for (int i = 0; i < 4096; i++){
      if(isReceiver == 0)
        printf("i:%d\n", i);
        channelRaw[i] = 1;
    }
    for (int i = 0; i < 17; i++){
      if(isReceiver == 1)
        printf("i:%d value: %d\n", i, channelRaw[i]);
    }

    // if(isReceiver == 0) {
    //   channelRaw[0] = 1;
    //   channelRaw[1] = 8;
    //   channelRaw[2] = 9;
    //   channelRaw[3] = 5;
    //   channelRaw[4] = 5;
    //   channelRaw[5] = 5;
    //   channelRaw[6] = 5;
    //   channelRaw[7] = 5;
    // }
    // else
    // {
    //   printf("%d\n", channelRaw[0]);
    //   printf("%d\n", channelRaw[1]);
    //   printf("%d\n", channelRaw[2]);
    //   printf("%d\n", channelRaw[3]);
    //   printf("%d\n", channelRaw[4]);
    //   printf("%d\n", channelRaw[5]);
    //   printf("%d\n", channelRaw[6]);
    //   printf("%d\n", channelRaw[7]);
    // }
    

    

    printf("channelRaw: %p\n", channelRaw);

  }
}


#endif // TASK2_SCOMMON_H