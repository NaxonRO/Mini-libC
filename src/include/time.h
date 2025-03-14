// SPDX-License-Identifier: BSD-3-Clause

#ifndef __TIME_H__
#define __TIME_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef long time_t;

// Pentru liniile de sus am facut asemanator cum era si in celelalte file
// Structura am declarat-o cu time_t pt secunde si cu long pt nanosec
struct timespec {
    time_t tv_sec;
    long tv_nsec;
};

void nanosleep(struct timespec *rqtp, struct timespec *rmtp);

#ifdef __cplusplus
}
#endif

#endif
