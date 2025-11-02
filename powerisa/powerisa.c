#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define SEGMENT_BITS 40
#define OFFSET_BITS  24

// Structure to represent a virtual address in SLS
typedef struct {
    uint64_t segment; // 40-bit segment ID
    uint32_t offset;  // 24-bit offset
} SLSAddress;

// Example "storage" for segments
#define SEGMENT_SIZE (1 << OFFSET_BITS) // 16 MB per segment
#define MAX_SEGMENTS 4                  // keep it small for demo

// Simulated QSECURITY level (10,20,30,40,50)
int security_level = 40; // default to 40

// Simple process structure with allowed segments
typedef struct {
    char name[16];
    int allowed_segments[MAX_SEGMENTS]; // 1 = allowed, 0 = denied
} Process;

Process current_process = {"DemoProc", {1, 1, 0, 0}}; // allowed segments: 0 and 1

uint8_t storage[MAX_SEGMENTS][1 << 12]; // pretend each segment is 4 KB

// ------------------------------------------------------------
// Address decoding
// ------------------------------------------------------------
SLSAddress decode_address(uint64_t vaddr) {
    SLSAddress addr;
    addr.segment = (vaddr >> OFFSET_BITS) & ((1ULL << SEGMENT_BITS) - 1);
    addr.offset  = vaddr & ((1ULL << OFFSET_BITS) - 1);
    return addr;
}

// ------------------------------------------------------------
// SLS store/load
// ------------------------------------------------------------
void sls_store(uint64_t vaddr, uint8_t value) {
    SLSAddress a = decode_address(vaddr);

    if (a.segment >= MAX_SEGMENTS) {
        printf("[SLS] Invalid segment %llu\n", (unsigned long long)a.segment);
        return;
    }

    if (security_level >= 50 && !current_process.allowed_segments[a.segment]) {
        printf("[SECURITY] Access denied: process '%s' cannot access segment %llu at level %d\n",
               current_process.name, (unsigned long long)a.segment, security_level);
        return;
    }

    if (a.offset < sizeof(storage[a.segment])) {
        storage[a.segment][a.offset] = value;
        printf("[SLS] Stored %u at segment %llu offset %u\n",
               value, (unsigned long long)a.segment, a.offset);
    } else {
        printf("[SLS] Invalid offset %u in segment %llu\n",
               a.offset, (unsigned long long)a.segment);
    }
}

uint8_t sls_load(uint64_t vaddr) {
    SLSAddress a = decode_address(vaddr);

    if (a.segment >= MAX_SEGMENTS) {
        printf("[SLS] Invalid segment %llu\n", (unsigned long long)a.segment);
        return 0;
    }

    if (security_level >= 50 && !current_process.allowed_segments[a.segment]) {
        printf("[SECURITY] Access denied: process '%s' cannot access segment %llu at level %d\n",
               current_process.name, (unsigned long long)a.segment, security_level);
        return 0;
    }

    if (a.offset < sizeof(storage[a.segment])) {
        uint8_t value = storage[a.segment][a.offset];
        printf("[SLS] Loaded %u from segment %llu offset %u\n",
               value, (unsigned long long)a.segment, a.offset);
        return value;
    } else {
        printf("[SLS] Invalid offset %u in segment %llu\n",
               a.offset, (unsigned long long)a.segment);
        return 0;
    }
}

// ------------------------------------------------------------
// IBM i style word sizes
// ------------------------------------------------------------
typedef uint8_t   BYTE;     // 8 bits
typedef uint16_t  HWORD;    // 16 bits
typedef uint32_t  WORD;     // 32 bits (instruction size)
typedef uint64_t  DWORD;    // 64 bits (register size)
typedef __uint128_t QWORD;  // 128 bits (thick pointer size)

// Define an "Object" type (MI works on objects, not raw memory)
typedef struct {
    char name[16];
    DWORD length;
    BYTE *data;
} MIObject;

// ------------------------------------------------------------
// MI safe memory access
// ------------------------------------------------------------
void MI_store(MIObject *obj, DWORD offset, BYTE value) {
    if (offset < obj->length) {
        obj->data[offset] = value;
        printf("[MI] Stored value %u at offset %llu in object '%s'\n",
               value, (unsigned long long)offset, obj->name);
    } else {
        printf("[MI] Memory safety violation prevented in object '%s'\n", obj->name);
    }
}

BYTE MI_load(MIObject *obj, DWORD offset) {
    if (offset < obj->length) {
        BYTE value = obj->data[offset];
        printf("[MI] Loaded value %u from offset %llu in object '%s'\n",
               value, (unsigned long long)offset, obj->name);
        return value;
    } else {
        printf("[MI] Memory safety violation prevented in object '%s'\n", obj->name);
        return 0;
    }
}

// ------------------------------------------------------------
// Raw memory access (unsafe)
// ------------------------------------------------------------
void raw_store(BYTE *mem, DWORD offset, BYTE value) {
    mem[offset] = value; // no safety checks
    printf("[RAW] Stored value %u at raw offset %llu\n",
           value, (unsigned long long)offset);
}

// ------------------------------------------------------------
// Bit printing helpers
// ------------------------------------------------------------
void print_bits_uint128(QWORD value) {
    for (int i = 127; i >= 0; i--) {
        putchar((value >> i) & 1 ? '1' : '0');
        if (i % 8 == 0) putchar(' ');
    }
    putchar('\n');
}

void print_bits64(uint64_t value, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        putchar((value >> i) & 1 ? '1' : '0');
        if (i % 8 == 0) putchar(' ');
    }
    putchar('\n');
}

// ------------------------------------------------------------
// Demo functions
// ------------------------------------------------------------
void demo_sls() {
    uint64_t vaddr = 0xb4d5391dff001122ULL;

    SLSAddress a = decode_address(vaddr);
    printf("Virtual Address: 0x%016llX\n", (unsigned long long)vaddr);
    printf("Segment: 0x%010llX\n", (unsigned long long)a.segment);
    printf("Offset:  0x%06X\n", a.offset);

    uint64_t demo_addr = (1ULL << OFFSET_BITS) * 1 + 0x10;
    sls_store(demo_addr, 42);
    sls_load(demo_addr);

    uint64_t bad_addr = (5ULL << OFFSET_BITS) + 0x20;
    sls_store(bad_addr, 99);
}

void demo_words() {
    HWORD h = 0xABCD;
    WORD  w = 0x12345678;
    DWORD d = 0x1122334455667788ULL;
    QWORD q = ((__uint128_t)0x1122334455667788ULL << 64) |
               0x99AABBCCDDEEFF00ULL;

    printf("HWORD (16 bits): 0x%04X\n", h);
    print_bits64(h, 16);

    printf("WORD  (32 bits): 0x%08X\n", w);
    print_bits64(w, 32);

    printf("DWORD (64 bits): 0x%016llX\n", (unsigned long long)d);
    print_bits64(d, 64);

    printf("QWORD (128 bits):\n");
    print_bits_uint128(q);
}

void demo_security_levels() {
    security_level = 40;
    printf("\n--- Security Level %d ---\n", security_level);
    uint64_t addr1 = (1ULL << OFFSET_BITS) * 1 + 0x10;
    sls_store(addr1, 77);
    sls_load(addr1);

    security_level = 50;
    printf("\n--- Security Level %d ---\n", security_level);
    uint64_t addr2 = (2ULL << OFFSET_BITS) + 0x20;
    sls_store(addr2, 99);
}

// ------------------------------------------------------------
// Memory dump utilities
// ------------------------------------------------------------
void print_segment_horizontal(int seg, int length) {
    printf("\n[Segment %d Horizontal Dump]\n", seg);
    for (int i = 0; i < length; i++) {
        if (i % 16 == 0) printf("%04X: ", i);
        printf("%02X ", storage[seg][i]);

        if ((i + 1) % 16 == 0) {
            printf(" | ");
            for (int j = i - 15; j <= i; j++) {
                uint8_t c = storage[seg][j];
                putchar((c >= 32 && c <= 126) ? c : '.');
            }
            printf("\n");
        }
    }
    printf("\n");
}

void print_segment_vertical(int seg, int length) {
    printf("\n[Segment %d Vertical Dump]\n", seg);
    for (int i = 0; i < length; i++) {
        uint8_t c = storage[seg][i];
        printf("Addr %04X | %02X | %c\n", i, c,
               (c >= 32 && c <= 126) ? c : '.');
    }
    printf("\n");
}

void print_memory_stats() {
    printf("\n[Memory Stats]\n");
    for (int seg = 0; seg < MAX_SEGMENTS; seg++) {
        int used = 0;
        int total = sizeof(storage[seg]);
        for (int i = 0; i < total; i++) {
            if (storage[seg][i] != 0) {
                used++;
            }
        }
        int free = total - used;
        double percent = (100.0 * used) / total;
        printf("Segment %d: used=%d bytes, free=%d bytes, usage=%.2f%%\n",
               seg, used, free, percent);
    }
    printf("\n");
}

// ------------------------------------------------------------
// Main
// ------------------------------------------------------------
int main() {
    // Create an MI object
    BYTE buffer[8] = {0};
    MIObject obj = {"CustomerRec", 8, buffer};

    // Safe MI operations
    MI_store(&obj, 2, 42);
    MI_load(&obj, 2);

    // Attempt out-of-bounds MI access
    MI_store(&obj, 20, 99);

    // Raw memory access (unsafe, no checks)
    raw_store(buffer, 20, 99); // This will corrupt memory!

    // Demo SLS
    demo_sls();

    // Fill some test data into segment 1
    for (int i = 0; i < 64; i++) {
        storage[1][i] = (i % 26) + 'A'; // letters A..Z repeating
    }

    // Print memory layouts
    print_segment_horizontal(1, 64);
    print_segment_vertical(1, 32);
    print_memory_stats();

    // Demo word sizes and bit printing
    demo_words();

    // Demo security levels
    demo_security_levels();

    return 0;
}

