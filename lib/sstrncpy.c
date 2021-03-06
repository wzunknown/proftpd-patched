/*
 * ProFTPD - FTP server daemon
 * Copyright (c) 1997, 1998 Public Flood Software
 * Copyright (c) 1999, 2000 MacGyver aka Habeeb J. Dihu <macgyver@tos.net>
 * Copyright (c) 2001-2015 The ProFTPD Project team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA 02110-1335, USA.
 *
 * As a special exemption, Public Flood Software/MacGyver aka Habeeb J. Dihu
 * and other respective copyright holders give permission to link this program
 * with OpenSSL, and distribute the resulting executable, without including
 * the source code for OpenSSL in the source distribution.
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#ifdef HAVE_STRING_H
# include <string.h>
#endif

#include "base.h"

/* "safe" strncpy, saves room for \0 at end of dest, and refuses to copy
 * more than "n" bytes.  Returns the number of bytes copied, or -1 if there
 * was an error.
 */
int sstrncpy(char *dst, const char *src, size_t n) {
  register char *d;
  int res = 0;

  if (dst == NULL) {
    errno = EINVAL;
    return -1;
  }

  if (src == NULL) {
    errno = EINVAL;
    return -1;
  }

  if (n == 0) {
    return 0;
  }

  /* Avoid attempts to overwrite memory with itself (Bug#4156). */
  if (dst == src) {
    return n;
  }

  d = dst;
  if (src && *src) {
    for (; *src && n > 1; n--) {
      *d++ = *src++;
      res++;
    }
  }

  *d = '\0';
  return res;
}
