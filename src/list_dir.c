/*
 * "It's not a bug — it's an undocumented feature."
 *
 * Author: Leonardo Lopes Pereira
 * Email: lepereir@student.42.fr
 *
 * SPDX-License-Identifier: blessing
 */

#include "ft_ls.h"

#include <dirent.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *path_join(const char *dir, const char *name)
{
	char *path;
	size_t len;

	len = strlen(dir) + strlen(name) + 2;
	path = malloc(len);
	if (path == NULL)
		return (NULL);
	snprintf(path, len, "%s/%s", dir, name);
	return (path);
}

static int entry_fill(t_entry *entry, const char *path, const char *name)
{
	entry->name = strdup(name);
	entry->path = path_join(path, name);
	if (entry->name == NULL || entry->path == NULL)
		err(1, "malloc");
	if (lstat(entry->path, &entry->st) != 0)
	{
		warn("cannot access '%s'", entry->path);
		free(entry->name);
		free(entry->path);
		return (1);
	}
	return (0);
}

static void entry_push(t_dir *dir, const t_entry *entry)
{
	t_entry *grown;
	size_t capacity;

	if (dir->count == dir->capacity)
	{
		capacity = 64;
		if (dir->capacity != 0)
			capacity = dir->capacity * 2;
		grown = realloc(dir->entries, capacity * sizeof(t_entry));
		if (grown == NULL)
			err(1, "realloc");
		dir->entries = grown;
		dir->capacity = capacity;
	}
	dir->entries[dir->count] = *entry;
	dir->count++;
}

static void dir_read(const t_ft_ls *ls, t_dir *dir, DIR *dirp, const char *path)
{
	struct dirent *ent;
	t_entry entry;

	while (1)
	{
		ent = readdir(dirp);
		if (ent == NULL)
			break ;
		if (!ls->all && ent->d_name[0] == '.')
			continue ;
		if (entry_fill(&entry, path, ent->d_name) != 0)
			continue ;
		entry_push(dir, &entry);
	}
}

static int cmp_name(const void *a, const void *b)
{
	const t_entry *ea;
	const t_entry *eb;

	ea = a;
	eb = b;
	return (strcmp(ea->name, eb->name));
}

static int cmp_timespec(const struct timespec *a, const struct timespec *b)
{
	if (a->tv_sec > b->tv_sec)
		return (-1);
	if (a->tv_sec < b->tv_sec)
		return (1);
	if (a->tv_nsec > b->tv_nsec)
		return (-1);
	if (a->tv_nsec < b->tv_nsec)
		return (1);
	return (0);
}

static int cmp_mtime(const void *a, const void *b)
{
	const t_entry *ea;
	const t_entry *eb;
	int diff;

	ea = a;
	eb = b;
	diff = cmp_timespec(&ea->st.st_mtim, &eb->st.st_mtim);
	if (diff != 0)
		return (diff);
	return (cmp_name(a, b));
}

static int cmp_atime(const void *a, const void *b)
{
	const t_entry *ea;
	const t_entry *eb;
	int diff;

	ea = a;
	eb = b;
	diff = cmp_timespec(&ea->st.st_atim, &eb->st.st_atim);
	if (diff != 0)
		return (diff);
	return (cmp_name(a, b));
}

static void reverse_entries(t_dir *dir)
{
	t_entry tmp;
	size_t i;
	size_t j;

	i = 0;
	j = dir->count;
	while (i + 1 < j)
	{
		tmp = dir->entries[i];
		dir->entries[i] = dir->entries[j - 1];
		dir->entries[j - 1] = tmp;
		i++;
		j--;
	}
}

static void dir_sort(const t_ft_ls *ls, t_dir *dir)
{
	int (*cmp)(const void *, const void *);

	if (ls->no_sort || dir->count < 2)
		return ;
	if (!ls->sort_time)
		cmp = cmp_name;
	else if (ls->access_time)
		cmp = cmp_atime;
	else
		cmp = cmp_mtime;
	qsort(dir->entries, dir->count, sizeof(t_entry), cmp);
	if (ls->reverse)
		reverse_entries(dir);
}

static void dir_print(const t_dir *dir)
{
	size_t i;

	i = 0;
	while (i < dir->count)
	{
		printf("%s\n", dir->entries[i].name);
		i++;
	}
}

static void dir_free(t_dir *dir)
{
	size_t i;

	i = 0;
	while (i < dir->count)
	{
		free(dir->entries[i].name);
		free(dir->entries[i].path);
		i++;
	}
	free(dir->entries);
}

void list_dir(const t_ft_ls *ls, const char *path)
{
	struct stat st;
	t_dir dir;
	DIR *dirp;

	/* stat, not lstat: a symlink operand lists its target, like ls */
	if (stat(path, &st) != 0)
	{
		warn("cannot access '%s'", path);
		return ;
	}
	if (ls->self_only || !S_ISDIR(st.st_mode))
	{
		printf("%s\n", path);
		return ;
	}
	dirp = opendir(path);
	if (dirp == NULL)
	{
		warn("cannot open directory '%s'", path);
		return ;
	}
	dir = (t_dir){0};
	dir_read(ls, &dir, dirp, path);
	closedir(dirp);
	dir_sort(ls, &dir);
	dir_print(&dir);
	dir_free(&dir);
}
