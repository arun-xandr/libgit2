/*
 * Copyright (C) the libgit2 contributors. All rights reserved.
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */

#include "common.h"

#include "git2/sys/config.h"
#include "config.h"

typedef struct config_entry_list {
	struct config_entry_list *next;
	struct config_entry_list *last;
	git_config_entry *entry;
} config_entry_list;

typedef struct {
	git_atomic refcount;
	git_strmap *map;
	config_entry_list *list;
} diskfile_entries;

typedef struct git_config_file_iter {
	git_config_iterator parent;
	config_entry_list *head;
} git_config_file_iter;

int diskfile_entries_alloc(diskfile_entries **out);
void diskfile_entries_free(diskfile_entries *entries);
/* Add or append the new config option */
int diskfile_entries_append(diskfile_entries *entries, git_config_entry *entry);

void config_iterator_free(git_config_iterator* iter);
int config_iterator_next(git_config_entry **entry,
	git_config_iterator *iter);
