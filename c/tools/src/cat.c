/**
 * A quick implementation of cat. No flags.
 *
 * Copyright (c) 2014, Stephen A. Balaban, Lambda Labs, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

size_t const BUF_SIZE = 1024;
static const char *filename;

void
cat_fd(int fd)
{
	int stdoutfd = fileno(stdout);
	static char *buf = NULL;
	if ((buf = malloc(BUF_SIZE)) == NULL) {
		err(1, "malloc() failed!");
	}
	size_t nread = 0;
	size_t nwrite = 0;
	while ((nread = read(fd, buf, BUF_SIZE)) > 0) {
		if ((nwrite = write(stdoutfd, buf, nread)) < 0)
			err(1, "stdout fail!");
	}
}

int
main (int argc, char *argv[])
{
	int rval = EXIT_SUCCESS;
	argv++;

	int fd;
	filename = "stdin";
	fd = fileno(stdin);
	int i;
	if (argc == 1) {
		filename = "stdin";
		fd = fileno(stdin);
		cat_fd(fd);
	} else {
		for (i = 0; i < argc - 1; i++) {
			if (strcmp(*argv, "-") == 0) {
				filename = "stdin";
				fd = fileno(stdin);
				cat_fd(fd);
			} else if ((fd = open(*argv, O_RDONLY, 0)) < 0) {
				filename = *argv;
				warn("Error %s", filename);
				rval = EXIT_FAILURE;
			} else {
				filename = *argv;
				cat_fd(fd);
			}
			++argv;
			continue;
		}
	}
	return rval;
}
