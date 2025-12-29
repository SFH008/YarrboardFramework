#ifndef GULPEDFILE_H
#define GULPEDFILE_H

#include <stdint.h>
#include <stddef.h>

struct GulpedFile {
    const uint8_t* data;      // Pointer to the file data array
    size_t length;            // Length of the data in bytes
    const char* sha256;       // SHA-256 hash as hex string
    const char* filename;     // Original filename (e.g., "logo.png")
    const char* mimetype;     // MIME type (e.g., "image/png")
};

#endif // GULPEDFILE_H
