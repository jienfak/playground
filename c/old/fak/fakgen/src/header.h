/* macrosses */
	/* debugging */
	/* #define IS_DBG */

	/* boolean */
	#define FALSE 		0
	#define TRUE  		1	

	/* std descriptors */
	#define STDREAD		0
	#define STDOUT 		1
	#define STDERR 		2
	

	/* flags */
	#define VERSION_FLAG	(1<<0)
	#define HELP_FLAG	(1<<1)
	#define OUT_FLAG	(1<<2)
	#define NWORDS_FLAG	(1<<3)
	#define SEPS_FLAG	(1<<4)
	#define MAXREPS_FLAG	(1<<5)
	#define REVERSE_FLAG	(1<<6)

	/* arguments */
	#define OUTFILE		0
	#define NWORDS		1
	#define SEPS		2
	#define MAXREPS		3

	/* buffers */
	#define BUFF_SIZE 	1024
	#define PBUFF_SIZE 	1024
	
	/* information */
	#define VERSION 	"v0.94"
	#define PROGNAME 	"fakgen"

/* includes */
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

/* types */
typedef uint64_t	ul_t;
typedef uint8_t		us_t;

typedef unsigned (*hndl_f)(ul_t *flags, char **argv, int argc, int i, int bias, char **out_argv);

/* args */
	unsigned long	parseArgs(char **argv, int argc, int num_hndls, 
			char **long_handlers,
			char *shrt_handlers,
			hndl_f hndls[],
			char **out_argv,
			char **lost_argv
		);

/* handlers */
	unsigned versionHndl	(ul_t *, char **, int, int, int, char **);
	unsigned helpHndl	(ul_t *, char **, int, int, int, char **);
	unsigned outHndl	(ul_t *, char **, int, int, int, char **);
	unsigned nwordsHndl	(ul_t *, char **, int, int, int, char **);
	unsigned separatorsHndl	(ul_t *, char **, int, int, int, char **);
	unsigned maxrepsHndl	(ul_t *, char **, int, int, int, char **);
	unsigned reverseHndl	(ul_t *, char **, int, int, int, char **);

/* math */
	int		bitsEqTrue(ul_t);
	us_t 		maxRepsKws(char **, us_t, us_t);
	ul_t		powO(ul_t, us_t);

/* string */
	int		strSwitch(char **strarr, int arrlen, char *str);
	int		chrSwitch(char *str,	char chr);
	us_t		isNum(char *);
	us_t		isKw(char *);
	char		*strrev(char *dest, char *src);

/* passgen */
	/* genereates password by keywords and num of combination */
	char*		passGen( ul_t, char **, us_t, us_t, char *);
	/* has any repeats of words? */
	us_t 		isMv( ul_t, char **, us_t, us_t, us_t);
	/* copying array of pointer to chars */
	void 		grpCpyByBits( ul_t, char **, char**, ul_t);
	/* just like strlen only for pointer arrays */
	int		grpSize(char **);
