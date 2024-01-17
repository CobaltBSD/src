#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include <ctype.h>

#include <sys/syslimits.h>
#include <sys/param.h>
#include <sys/sysctl.h>

#define OS "CobaltBSD 1.0"

#define SECSPERHOUR	(60 * 60)
#define SECSPERDAY	(24 * 60 * 60)

const char *art[] = {
	"\x1b[38;5;22m########## ########## ##########\e[0m",
	"\x1b[38;5;22m########## ########## ##########\e[0m",
	"\x1b[38;5;23m########## ########## ##########\e[0m",
	"\x1b[38;5;23m########## ########## ##########\e[0m",
	"\x1b[38;5;24m########## ########## ##########\e[0m",
	"\x1b[38;5;24m########## ########## ##########\e[0m",
	"\x1b[38;5;25m########## ########## ##########\e[0m",
	"\x1b[38;5;25m########## ########## ##########\e[0m",
	"\x1b[38;5;26m########## ########## ##########\e[0m",
	"\x1b[38;5;26m########## ########## ##########\e[0m",
	"\x1b[38;5;26m########## ########## ##########\e[0m",
	"\x1b[38;5;27m########## ########## ##########\e[0m",
	"\x1b[38;5;27m########## ########## ##########\e[0m",
	"\x1b[38;5;27m########## ########## ##########\e[0m",
	"\x1b[38;5;27m########## ########## ##########\e[0m",
	NULL
};

int main(void) {
	char *lines[7];

	char hostname[HOST_NAME_MAX + 1] = {0};
	gethostname(hostname, HOST_NAME_MAX);

	char *ident_fmt = "%s@%s";
	int ident_len = snprintf(NULL, 0, ident_fmt, getlogin(), hostname);

	char ident[ident_len + 1];
	snprintf(ident, ident_len + 1, ident_fmt, getlogin(), hostname);

	printf("%s   ", art[0]);
	lines[0] = ident;
	puts(lines[0]);

	printf("%s   ", art[1]);
	lines[1] = "------------------------";
	puts(lines[1]);

	char *os_fmt = "OS: %s %s";
	int os_len = snprintf(NULL, 0, os_fmt, OS, MACHINE_ARCH);

	char os[os_len + 1];
	snprintf(os, os_len + 1, os_fmt, OS, MACHINE_ARCH);

	printf("%s   ", art[2]);
	lines[2] = os;
	puts(lines[2]);

	// Get vendor and product
	const int vendor[2] = {CTL_HW, HW_VENDOR};
	u_int vendor_sz = 2;

	size_t vendor_out_sz;
	sysctl(vendor, vendor_sz, NULL, &vendor_out_sz, NULL, 0);

	char vendor_out[vendor_out_sz];
	sysctl(vendor, vendor_sz, vendor_out, &vendor_out_sz, NULL, 0);

	const int product[2] = {CTL_HW, HW_PRODUCT};
	u_int product_sz = 2;

	size_t product_out_sz;
	sysctl(product, product_sz, NULL, &product_out_sz, NULL, 0);

	char product_out[product_out_sz];
	sysctl(product, product_sz, product_out, &product_out_sz, NULL, 0);

	char *host_fmt = "Host: %s %s";
	int host_len = snprintf(NULL, 0, host_fmt, vendor_out, product_out);

	char host[host_len + 1];
	snprintf(host, host_len + 1, host_fmt, vendor_out, product_out);

	printf("%s   ", art[3]);
	lines[3] = host;
	puts(lines[3]);

	// Get shell and version
	char *shell = basename(getenv("SHELL"));
	size_t shell_len = strlen(shell);

	char shell_upper[shell_len + 1];

	for (int i = 0; i < shell_len; ++i) {
		shell_upper[i] = toupper(shell[i]);
	}
	shell_upper[shell_len] = '\0';

	char *cmd_fmt = "echo 'echo $%s_VERSION' | %s -";
	int cmd_len = snprintf(NULL, 0, cmd_fmt, shell_upper, shell);

	char cmd[cmd_len + 1];
	snprintf(cmd, cmd_len + 1, cmd_fmt, shell_upper, shell);

	FILE *fp = popen(cmd, "re");
	char c;
	int version_string_sz = 1;
	char *version_string = NULL;

	do {
		fread(&c, 1, 1, fp);
		version_string = realloc(version_string, (version_string_sz + 1) * sizeof(char));
		version_string[version_string_sz - 1] = c;
		++version_string_sz;
	} while(c != '\n');
	version_string[version_string_sz - 2] = '\0'; // Also cut off the newline at the end

	char *shell_fmt = "Shell: %s %s";
	int shell_string_len = snprintf(NULL, 0, shell_fmt, shell, version_string);

	char shell_string[shell_len + 1];
	snprintf(shell_string, shell_string_len + 1, shell_fmt, shell, version_string);

	printf("%s   ", art[4]);
	lines[4] = shell_string;
	puts(lines[4]);

	// Print uptime
	// Derived from the code of `uptime`
	struct timespec boottime;
	time_t uptime;
	int days, hrs, mins;

	char *uptime_string = NULL;

	int buffer_sz = strlen("Uptime: ") + 1;
	uptime_string = realloc(uptime_string, sizeof(char) * buffer_sz);
	strlcpy(uptime_string, "Uptime: ", buffer_sz);

	if (clock_gettime(CLOCK_BOOTTIME, &boottime) != -1) {
		uptime = boottime.tv_sec;
		if (uptime > 59) {
			uptime += 30;
			days = uptime / SECSPERDAY;
			uptime %= SECSPERDAY;
			hrs = uptime / SECSPERHOUR;
			uptime %= SECSPERHOUR;
			mins = uptime / 60;
			if (days > 0) {
				char *day_string_fmt = "%d day%s%s";
				int day_string_len = snprintf(NULL, 0, day_string_fmt, days,
				    days > 1 ? "s" : "", hrs > 0 ? ", " : "");

				char day_string[day_string_len + 1];
				snprintf(day_string, day_string_len + 1, day_string_fmt, days,
				    days > 1 ? "s" : "", hrs > 0 ? ", " : "");

				buffer_sz += strlen(day_string);
			} if (hrs > 0) {
				char *hr_string_fmt = "%d hr%s%s";
				int hr_string_len = snprintf(NULL, 0, hr_string_fmt,
				    hrs, hrs > 1 ? "s" : "", mins > 0 || (days == 0 && hrs == 0) ? ", " : "");

				char hr_string[hr_string_len + 1];
				snprintf(hr_string, hr_string_len + 1, hr_string_fmt,
				    hrs, hrs > 1 ? "s" : "", mins > 0 || (days == 0 && hrs == 0) ? ", " : "");

				buffer_sz += strlen(hr_string);
				uptime_string = realloc(uptime_string, sizeof(char) * buffer_sz);
				strlcat(uptime_string, hr_string, buffer_sz);
			} if (mins > 0 || (days == 0 && hrs == 0)) {
				char *min_string_fmt = "%d min%s";
				int min_string_len = snprintf(NULL, 0, min_string_fmt,
				    mins, mins != 1 ? "s" : "");

				char min_string[min_string_len + 1];
				snprintf(min_string, min_string_len + 1, min_string_fmt,
				    mins, mins != 1 ? "s" : "");

				buffer_sz += strlen(min_string);
				uptime_string = realloc(uptime_string, sizeof(char) * buffer_sz);
				strlcat(uptime_string, min_string, buffer_sz);
			}
		} else {
			char *sec_string_fmt = "%d secs";
			int sec_string_len = snprintf(NULL, 0, sec_string_fmt, (int) uptime);

			char sec_string[sec_string_len + 1];
			snprintf(sec_string, sec_string_len, sec_string_fmt, (int) uptime);

			buffer_sz += strlen(sec_string);
			uptime_string = realloc(uptime_string, sizeof(char) * buffer_sz);
			strlcat(uptime_string, sec_string, buffer_sz);
		}
	}
	printf("%s   ", art[5]);
	lines[5] = uptime_string;
	puts(lines[5]);

	// Get CPU
	const int cpu[2] = {CTL_HW, HW_MODEL};
	u_int cpu_sz = 2;

	size_t cpu_out_sz;
	sysctl(cpu, cpu_sz, NULL, &cpu_out_sz, NULL, 0);

	char cpu_out[cpu_out_sz];
	sysctl(cpu, cpu_sz, cpu_out, &cpu_out_sz, NULL, 0);

	char *cpu_fmt = "CPU: %s";
	int cpu_len = snprintf(NULL, 0, "CPU: %s", cpu_out);

	char cpu_string[cpu_len + 1];
	snprintf(cpu_string, cpu_len + 1, cpu_fmt, cpu_out);

	printf("%s   ", art[6]);
	lines[6] = cpu_string;
	puts(lines[6]);

	for (int i = 7; art[i] != NULL; ++i) {
		puts(art[i]);
	}
	return 0;
}
