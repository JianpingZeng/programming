#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include "node.h"

static void print_type_permission(mode_t mode);

static void print_user_group(uid_t uid, gid_t gid);

static void print_mtime(time_t mytime);

void display(Node* head);

#endif
