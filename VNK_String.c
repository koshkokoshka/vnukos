#include "VNK_String.h"

reg VNK_StringLength(const char *str)
{
    const char *end = str;
    while (*++end != '\0');
    return end - str;
}
