#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <dialog.h>
#include <bsd_auth.h>
#include <err.h>
#include <syslog.h>

int main(void) {
	// Get username and password from dialog
	char *opts[] = {
		"Username", "1", "1", "", "1", "12", "32", "0", "0",
		"Password", "2", "1", "", "2", "12", "32", "0", "1",
	};
	init_dialog(stdin, stdout);
	dialog_vars.insecure = 1; // Show asterisks as characters are typed
	dialog_vars.input_menu = 1;
	int status = dialog_mixedform("Please login", "", 20, 50, 0, 2, opts);
	end_dialog();

	char *user = NULL;
	int i = 0;
	while (dialog_vars.input_result[i] != '\n') {
		user = realloc(user, sizeof(char) * i + 1);
		user[i] = dialog_vars.input_result[i];
		++i;
	}
	user = realloc(user, sizeof(char) * i + 1);
	user[i] = '\0';

	// Start authentication with provided username
	auth_session_t *as;
	char *challenge = NULL;

	if (!(as = auth_userchallenge(user, NULL, "auth-doas",
	    &challenge))) {
		warnx("Authentication failed");
		exit(EXIT_FAILURE);
	}
	
	char *pw = NULL;
	int j = 0;
	for (; j < strlen(dialog_vars.input_result) - i - 2; ++j) {
		pw = realloc(pw, sizeof(char) * j + 1);
		pw[j] = dialog_vars.input_result[i + j + 1];
	}
	pw = realloc(pw, sizeof(char) * j + 1);
	pw[j] = '\0';

	// Verify password
	if (!auth_userresponse(as, pw, 0)) {
		explicit_bzero(pw, sizeof(pw));
		syslog(LOG_AUTHPRIV | LOG_NOTICE,
		    "failed auth for %s", user);
		warnx("Authentication failed");
		exit(EXIT_FAILURE);
	}
	explicit_bzero(pw, sizeof(pw));

	// Get passwd entry
	struct passwd *ent = NULL;
	while ((ent = getpwent()) != NULL) {
		if (strcmp(user, ent->pw_name) == 0) {
			break;
		}
	}

	if (ent == NULL) {
		puts("Specified user was not found.");
		exit(EXIT_FAILURE);
	}

	// Open new shell if password is correct
	gid_t gid = ent->pw_gid;

	if (setgid(gid) != 0) {
		perror("setgid");
	}

	int ngroups = 0;
	getgrouplist(ent->pw_name, ent->pw_gid, NULL, &ngroups);
	gid_t t[ngroups];
	getgrouplist(ent->pw_name, ent->pw_gid, t, &ngroups);

	setgroups(ngroups, t);

	uid_t uid;
	uid_from_user(user, &uid);

	if (setuid(uid) != 0) {
		perror("setuid");
	}

	setenv("HOME", ent->pw_dir, 1);
	setenv("SHELL", ent->pw_shell, 1);
	setenv("USER", ent->pw_name, 1);

	char *argv[] = {"", 0};
	if (execv("/usr/bin/sh", argv) != 0) {
		puts("Unable to start shell");
		perror("");
	}
	return status;
}
