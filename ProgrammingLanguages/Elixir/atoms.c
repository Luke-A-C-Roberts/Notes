#include <stdint.h>

// typedef unsigned long HashValue;

// typedef struct hash_bucket {
//     struct hash_bucket* next;	/* Next bucket */
//     HashValue hvalue;           /* Store hash value for get, rehash */
// } HashBucket;

// typedef struct index_slot  {
//     HashBucket bucket;
//     int index;
// } IndexSlot;

// typedef struct atom {
//     IndexSlot slot;       /* MUST BE LOCATED AT TOP OF STRUCT!!! */
//     int16_t len;          /* length of atom name (UTF-8 encoded) */
//     int16_t latin1_chars; /* 0-255 if atom can be encoded in latin1; otherwise, -1 */
//     int ord0;             /* ordinal value of first 3 bytes + 7 bits */
//     int8_t *name;         /* name of atom */
// } Atom;

// typedef struct atom {
//     struct {
//         struct {
//             void *next;
//             unsigned long hvalue;
//         } bucket;
//         int index;
//     } slot;
//     short len;
//     short latin1_chars;
//     int ord0;
//     char *name;
// } Atom;

typedef struct atom {
    void *next;
    unsigned long hvalue;
    int index;
    short len;
    short latin1_chars;
    int ord0;
    char *name;
} Atom;

// 64 + 64 + 32 + 16 + 16 + 64 = 4 * 64 (4 words) = 16 * 8 (16 bytes)

int main(void) {
    return 0;
}
