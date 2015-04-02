/**
 * A quick implementation of stat.
 *
 * Copyright (c) 2015, Stephen A. Balaban, Lambda Labs, Inc.
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
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

void
usage() {
	fprintf(stderr, "Usage:\n\tstat filepaths...\n");
}

const char *
mode_to_device_string(struct stat *stat_buffer) {
	switch(stat_buffer->st_mode & S_IFMT) {
		case S_IFBLK: return "block device\n"; break;
		case S_IFCHR: return "character device\n"; break;
		case S_IFDIR: return "directory\n"; break;
		case S_IFIFO: return "FIFO/pipe\n"; break;
		case S_IFLNK: return "symlink\n"; break;
		case S_IFREG: return "regular file\n"; break;
		case S_IFSOCK: return "socket\n"; break;
		default: return "unknown?\n"; break;
	}
}

void
check_buff(void *buff, const char *error, int exitVal) {
	if (buff == NULL) {
		fprintf(stderr, "%s", error);
		exit(exitVal);
	}
}

char *
create_mode_to_perm_string(struct stat *stat_buffer) {
	mode_t mode = stat_buffer->st_mode;
	char *res = (char *) malloc(sizeof(char) * 11);
	check_buff(res, "Failed to allocate buffer for permisson string.", 2);
	res[0] = S_ISDIR(mode)  ? 'd' : '-';
	res[1] = mode & S_IRUSR ? 'r' : '-';
	res[2] = mode & S_IWUSR ? 'w' : '-';
	res[3] = mode & S_IXUSR ? 'x' : '-';
	res[4] = mode & S_IRGRP ? 'r' : '-';
	res[5] = mode & S_IWGRP ? 'w' : '-';
	res[6] = mode & S_IXGRP ? 'x' : '-';
	res[7] = mode & S_IROTH ? 'r' : '-';
	res[8] = mode & S_IWOTH ? 'w' : '-';
	res[9] = mode & S_IXOTH ? 'x' : '-';
	res[10] = '\0';
	return res;
}


char *
create_username_from_uid(uid_t uid) {
	size_t buf_len = sysconf(_SC_GETPW_R_SIZE_MAX) * sizeof(char);
	char *uname_buff = malloc(buf_len);
	check_buff(uname_buff, "Failed to allocate buffer for permisson string.", 2);

	struct passwd *pwdt = getpwuid(uid);
	strncpy(uname_buff, pwdt->pw_name, buf_len);
}

char *
create_groupname_from_gid(gid_t gid) {
	size_t buf_len = sysconf(_SC_GETGR_R_SIZE_MAX) * sizeof(char);
	char *uname_buff = malloc(buf_len);
	check_buff(uname_buff, "Failed to allocate buffer for permisson string.", 2);

	struct group *grp_st = getgrgid(gid);
	strncpy(uname_buff, grp_st->gr_name, buf_len);
}


void
statcmd(char *path) {
	// -rw-rw-r-- perm example
	char access[128], modify[128], change[128];
	const char *filetype, *name;
	char *perm, *owner, *group, *device;
	unsigned long mode, size, blocks, ioblock, inode, links, uid, gid;
	const char *fmtstring = (
	" File: ‘%s’\n"
	"  Size: %lu      	Blocks: %lu          IO Block: %d   %s\n"
	"Device: %s	Inode: %lu    Links: %lu\n"
	"Access: (%lo/%s)  Uid: ( %d/%s)   Gid: ( %d/%s)\n"
	"Access: %s\n"
	"Modify: %s\n"
	"Change: %s\n"
	" Birth: -\n");

	
	struct stat stat_buff;
	stat(path, &stat_buff);
	struct tm *access_time = localtime(&stat_buff.st_atime);
	struct tm *modify_time = localtime(&stat_buff.st_mtime);
	struct tm *change_time = localtime(&stat_buff.st_ctime);
	
	strftime(access, 128, "%F %T %z", access_time);
	strftime(modify, 128, "%F %T %z", modify_time);
	strftime(change, 128, "%F %T %z", change_time);
/*
	char *access = ctime(&stat_buff.st_atime);
	char *modify = ctime(&stat_buff.st_mtime);
	char *change = ctime(&stat_buff.st_ctime);
*/

	name = path;
	size = stat_buff.st_size;
	blocks = stat_buff.st_blocks;
	ioblock = stat_buff.st_blksize;
	inode = stat_buff.st_ino;
	links = stat_buff.st_nlink;
	uid = stat_buff.st_uid;
	gid = stat_buff.st_gid;
	mode = stat_buff.st_mode;
	filetype = mode_to_device_string(&stat_buff);
	owner = create_username_from_uid(uid);
	perm = create_mode_to_perm_string(&stat_buff);
	group = create_groupname_from_gid(gid);
	device = "";
	
	filetype = mode_to_device_string(&stat_buff);

	fprintf(stdout, fmtstring,
		name, size, blocks, ioblock, filetype, device, inode, links,
		mode & (S_IRWXU | S_IRWXG | S_IRWXO), perm, uid, owner, gid,
		group, access, modify, change);

	free(perm);
	free(owner);
	free(group);
}

int
main(int argc, char **argv)
{
	if (argc < 2) {
		usage();
		return EXIT_FAILURE;
	} else {
		int argIdx;
		for (argIdx = 1; argIdx < argc; argIdx++) {
			statcmd(argv[argIdx]);
		}
		return EXIT_SUCCESS;
	}
}
