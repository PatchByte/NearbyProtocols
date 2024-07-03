#include "NearbyTests/Utils.hpp"
#include <stdio.h>

void print_bytes_as_hex(void* data, size_t length, int indent)
{
    unsigned char* p = (unsigned char*)data;

    for (int i = 0; i < indent; i++)
    {
        printf(" ");
    }

    if (length <= 0)
    {
        printf("No Data.\n");
        return;
    }

    for (int i = 0; i < length; ++i)
    {
        if (!(i % 16) && i)
        {
            printf("\n");
            for (int i = 0; i < indent; i++)
            {
                printf(" ");
            }
        }

        printf("0x%02x ", p[i]);
    }
    printf("\n");
}