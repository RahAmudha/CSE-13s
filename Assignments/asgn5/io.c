#include "io.h"

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct buffer {
    int fd;
    int offset;
    int num_remaining;
    uint8_t arr[BUFFER_SIZE];
};

Buffer *read_open(const char *filename) {
    if (open(filename, O_RDONLY) < 0) {
        return NULL;
    } else {
        Buffer *b = (Buffer *) malloc(sizeof(Buffer));
        for (int t = 0; t < BUFFER_SIZE; ++t) {
            b->arr[t] = 0;
        }
        b->fd = open(filename, O_RDONLY);
        b->offset = 0;
        b->num_remaining = 0;
        return b;
    }
}

void read_close(Buffer **pbuf) {
    close((*pbuf)->fd);
    free(*pbuf);
    *pbuf = NULL;
}

Buffer *write_open(const char *filename) {
    if (creat(filename, 0664) < 0) {
        return NULL;
    } else {
        Buffer *b = (Buffer *) malloc(sizeof(Buffer));
        for (int t = 0; t < BUFFER_SIZE; ++t) {
            b->arr[t] = 0;
        }
        b->fd = open(filename, O_WRONLY);
        b->offset = 0;
        b->num_remaining = 0;
        return b;
    }
}

void write_close(Buffer **pbuf) {
    if ((*pbuf)->offset > 0) {
        uint8_t *start = (*pbuf)->arr;
        int num_bytes = (*pbuf)->offset;
        do {
            ssize_t rc = write((*pbuf)->fd, start, num_bytes);
            if (rc < 0)
                perror("The error was: ");
            start += rc;
            num_bytes -= rc;
        } while (num_bytes > 0);
    }
    close((*pbuf)->fd);
    free(*pbuf);
    *pbuf = NULL;
}

bool read_uint8(Buffer *buf, uint8_t *x) {
    if (buf->num_remaining == 0) {
        ssize_t rc = read(buf->fd, buf->arr, sizeof(buf->arr));
        if (rc < 0)
            perror("The error was: \n");
        if (rc == 0)
            return false;
        buf->num_remaining = rc;
        buf->offset = 0;
    }
    buf->num_remaining--;
    *x = buf->arr[buf->offset];
    buf->offset++;
    return true;
}

bool read_uint16(Buffer *buf, uint16_t *x) {
    uint8_t b1;
    uint8_t b2;
    if (read_uint8(buf, &b1) && read_uint8(buf, &b2)) {
        *x = ((uint16_t) b2 << 8) | (uint16_t) b1;
        return true;
    }
    return false;
}

bool read_uint32(Buffer *buf, uint32_t *x) {
    uint16_t b1;
    uint16_t b2;
    if (read_uint16(buf, &b1) && read_uint16(buf, &b2)) {
        *x = ((uint32_t) b2 << 16) | (uint32_t) b1;
        return true;
    }
    return false;
}

void write_uint8(Buffer *buf, uint8_t x) {
    if (buf->offset == BUFFER_SIZE) {
        uint8_t *start = buf->arr;
        int num_bytes = buf->offset;
        do {
            ssize_t rc = write(buf->fd, start, num_bytes);
            if (rc < 0)
                perror("The error was: ");
            start += rc;
            num_bytes -= rc;
        } while (num_bytes > 0);
        buf->offset = 0;
    }
    buf->arr[buf->offset] = x;
    buf->offset++;
}

void write_uint16(Buffer *buf, uint16_t x) {
    write_uint8(buf, x);
    write_uint8(buf, x >> 8);
}

void write_uint32(Buffer *buf, uint32_t x) {
    write_uint16(buf, x);
    write_uint16(buf, x >> 16);
}
