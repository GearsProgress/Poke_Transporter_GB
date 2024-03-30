#ifndef PAYLOAD_H
#define PAYLOAD_H

#include <tonc.h>
#include "output.h"

#define PAYLOAD_SIZE 637
#define NUM_PAYLOADS 1

struct PAYLOAD
{
public:
    int language;
    int version;
    byte payload_array[PAYLOAD_SIZE];
};

#endif