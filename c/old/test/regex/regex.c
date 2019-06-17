#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <sys/types.h>

#define MAX_MATCHES 16

int
main(int argc, char **argv)
{
	regex_t regex;
	regmatch_t matches[MAX_MATCHES];
	int reti;
	char msgbuf[64];
	 reti = regcomp(&regex, argv[1], REG_EXTENDED);
	 if (reti) {
	 	 fprintf(stderr, "Could not compile regex.\n");
	 	 exit(1);
	 }

	 reti = regexec(&regex, argv[2], 0, NULL, 0);
	 if (!reti) {
	 	 puts("Match!");
	 } else if (reti == REG_NOMATCH) {
	 	 puts("No match...");
	 } else {
		regerror(reti, &regex, msgbuf, sizeof(msgbuf));
		fprintf(stderr, "Regex match failed: '%s'.\n", msgbuf);
		exit(1);
	 }

	regfree(&regex);
	return 0;
}
