	return (digits > 0) ? 0 : -1;
		const char *scan = bufs[0].ptr;
		if (*scan != '@')
			return -1;

		if (read_next_int(&scan, &range.old_start) < 0)
			return -1;
		if (*scan == ',' && read_next_int(&scan, &range.old_lines) < 0)
			return -1;

		if (read_next_int(&scan, &range.new_start) < 0)
			return -1;
		if (*scan == ',' && read_next_int(&scan, &range.new_lines) < 0)
			return -1;

		if (range.old_start < 0 || range.new_start < 0)
			return -1;

		return info->hunk_cb(
			info->cb_data, info->delta, &range, bufs[0].ptr, bufs[0].size);

	if ((len == 2 || len == 3) && info->line_cb) {
		if (info->line_cb(
			info->cb_data, info->delta, origin, bufs[1].ptr, bufs[1].size) < 0)
			return -1;
		if (len == 3) {
			return info->line_cb(
	return 0;
static int update_file_is_binary_by_attr(git_repository *repo, git_diff_file *file)
	if (git_attr_get(repo, file->path, "diff", &value) < 0)
		return -1;


	return 0;
static void update_delta_is_binary(git_diff_delta *delta)
	if ((delta->old.flags & GIT_DIFF_FILE_BINARY) != 0 ||
		(delta->new.flags & GIT_DIFF_FILE_BINARY) != 0)
	else if ((delta->old.flags & GIT_DIFF_FILE_NOT_BINARY) != 0 ||
			 (delta->new.flags & GIT_DIFF_FILE_NOT_BINARY) != 0)
	int error = 0, mirror_new;
	if ((git_off_t)((size_t)delta->old.size) != delta->old.size ||
		(git_off_t)((size_t)delta->new.size) != delta->new.size)
		delta->old.flags |= GIT_DIFF_FILE_BINARY;
		delta->new.flags |= GIT_DIFF_FILE_BINARY;
		return 0;
		delta->old.flags |= GIT_DIFF_FILE_NOT_BINARY;
		delta->new.flags |= GIT_DIFF_FILE_NOT_BINARY;
		return 0;
	if (update_file_is_binary_by_attr(diff->repo, &delta->old) < 0)
		return -1;
	mirror_new = (delta->new.path == delta->old.path ||
				  strcmp(delta->new.path, delta->old.path) == 0);
		delta->new.flags &= (delta->old.flags & BINARY_DIFF_FLAGS);
		error = update_file_is_binary_by_attr(diff->repo, &delta->new);
	update_delta_is_binary(delta);
	if ((delta->old.flags & BINARY_DIFF_FLAGS) == 0) {
			delta->old.flags |= GIT_DIFF_FILE_BINARY;
			delta->old.flags |= GIT_DIFF_FILE_NOT_BINARY;
	if ((delta->new.flags & BINARY_DIFF_FLAGS) == 0) {
			delta->new.flags |= GIT_DIFF_FILE_BINARY;
			delta->new.flags |= GIT_DIFF_FILE_NOT_BINARY;
	update_delta_is_binary(delta);
	return 0;
		return 0;
	if (git_blob_lookup(blob, repo, oid) < 0)
		return -1;
	map->data = (void *)git_blob_rawcontent(*blob);
	map->len  = git_blob_rawsize(*blob);
	return 0;
	int error = 0;
	git_buf path = GIT_BUF_INIT;

	if (git_buf_joinpath(&path, git_repository_workdir(repo), file->path) < 0)
		return -1;
		ssize_t read_len;

		GITERR_CHECK_ALLOC(map->data);

		read_len = p_readlink(path.ptr, map->data, (size_t)file->size + 1);
		if (read_len != (ssize_t)file->size) {
			giterr_set(GITERR_OS, "Failed to read symlink '%s'", file->path);
			error = -1;
		} else
			map->len = read_len;
		error = git_futils_mmap_ro_file(map, path.ptr);
	git_buf_free(&path);
	int error = 0;
		if (delta->status == GIT_DELTA_UNMODIFIED &&
			(diff->opts.flags & GIT_DIFF_INCLUDE_UNMODIFIED) == 0)
		if ((error = file_is_binary_by_attr(diff, delta)) < 0)
				error = get_workdir_content(diff->repo, &delta->old, &old_data);
					diff->repo, &delta->old.oid, &old_data, &old_blob);
			if (error < 0)
			(hunk_cb || line_cb || git_oid_iszero(&delta->new.oid)) &&
				error = get_workdir_content(diff->repo, &delta->new, &new_data);
					diff->repo, &delta->new.oid, &new_data, &new_blob);
			if (error < 0)
			if ((delta->new.flags | GIT_DIFF_FILE_VALID_OID) == 0) {
					&delta->new.oid, new_data.data, new_data.len, GIT_OBJ_BLOB);
				if (error < 0)
				if (git_oid_cmp(&delta->old.oid, &delta->new.oid) == 0) {
					if ((diff->opts.flags & GIT_DIFF_INCLUDE_UNMODIFIED) == 0)
						goto cleanup;
			if (error < 0)
			if (error < 0)
		release_content(&delta->old, &old_data, old_blob);
		release_content(&delta->new, &new_data, new_blob);
		if (error < 0)
		return 0;
	old_suffix = pick_suffix(delta->old.mode);
	new_suffix = pick_suffix(delta->new.mode);
	if (delta->old.path != delta->new.path &&
		strcmp(delta->old.path,delta->new.path) != 0)
			delta->old.path, old_suffix, delta->new.path, new_suffix);
	else if (delta->old.mode != delta->new.mode &&
		delta->old.mode != 0 && delta->new.mode != 0)
			delta->old.path, new_suffix, delta->old.mode, delta->new.mode);
		git_buf_printf(pi->buf, "%c\t%s%c\n", code, delta->old.path, old_suffix);
		git_buf_printf(pi->buf, "%c\t%s\n", code, delta->old.path);
	if (git_buf_oom(pi->buf))
		return -1;
	git_oid_to_string(start_oid, sizeof(start_oid), &delta->old.oid);
	git_oid_to_string(end_oid, sizeof(end_oid), &delta->new.oid);
	if (delta->old.mode == delta->new.mode) {
			start_oid, end_oid, delta->old.mode);
		if (delta->old.mode == 0) {
			git_buf_printf(pi->buf, "new file mode %o\n", delta->new.mode);
		} else if (delta->new.mode == 0) {
			git_buf_printf(pi->buf, "deleted file mode %o\n", delta->old.mode);
			git_buf_printf(pi->buf, "old mode %o\n", delta->old.mode);
			git_buf_printf(pi->buf, "new mode %o\n", delta->new.mode);
	if (git_buf_oom(pi->buf))
		return -1;

	return 0;
	const char *oldpfx = pi->diff->opts.src_prefix;
	const char *oldpath = delta->old.path;
	const char *newpfx = pi->diff->opts.dst_prefix;
	const char *newpath = delta->new.path;
	git_buf_printf(pi->buf, "diff --git %s%s %s%s\n", oldpfx, delta->old.path, newpfx, delta->new.path);
	if (print_oid_range(pi, delta) < 0)
		return -1;

	if (git_oid_iszero(&delta->old.oid)) {
	if (git_oid_iszero(&delta->new.oid)) {
	if (git_buf_oom(pi->buf))
		return -1;
	if (pi->print_cb(pi->cb_data, GIT_DIFF_LINE_FILE_HDR, pi->buf->ptr) < 0 ||
		delta->binary != 1)
		return -1;
	if (git_buf_oom(pi->buf))
		return -1;
	if (git_buf_printf(pi->buf, "%.*s", (int)header_len, header) < 0)
		return -1;
	return pi->print_cb(pi->cb_data, GIT_DIFF_LINE_HUNK_HDR, pi->buf->ptr);
	if (git_buf_oom(pi->buf))
		return -1;
	mmfile_t old, new;
		old.ptr  = (char *)git_blob_rawcontent(old_blob);
		old.size = git_blob_rawsize(old_blob);
		old.ptr  = "";
		old.size = 0;
		new.ptr  = (char *)git_blob_rawcontent(new_blob);
		new.size = git_blob_rawsize(new_blob);
		new.ptr  = "";
		new.size = 0;
	delta.status = old.ptr ?
		(new.ptr ? GIT_DELTA_MODIFIED : GIT_DELTA_DELETED) :
		(new.ptr ? GIT_DELTA_ADDED : GIT_DELTA_UNTRACKED);
	delta.old.mode = 0100644; /* can't know the truth from a blob alone */
	delta.new.mode = 0100644;
	git_oid_cpy(&delta.old.oid, git_object_id((const git_object *)old_blob));
	git_oid_cpy(&delta.new.oid, git_object_id((const git_object *)new_blob));
	delta.old.path = NULL;
	delta.new.path = NULL;
	xdl_diff(&old, &new, &xdiff_params, &xdiff_config, &xdiff_callback);
	return 0;