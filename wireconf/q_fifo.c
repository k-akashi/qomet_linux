/*
 * q_fifo.c		FIFO.
 *
 *		This program is free software; you can redistribute it and/or
 *		modify it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include "utils.h"
#include "tc_util.h"

#define usage() return(-1)

static int
fifo_parse_opt(qu, qp, n)
struct qdisc_util* qu;
struct qdisc_parameter* qp;
struct nlmsghdr* n;
{
//	int ok=0;
	struct tc_fifo_qopt opt;
	memset(&opt, 0, sizeof(opt));

	get_size(&opt.limit, "1000");

/*
	while (argc > 0) {
		if (strcmp(*argv, "limit") == 0) {
			NEXT_ARG();
			if (get_size(&opt.limit, *argv)) {
				fprintf(stderr, "Illegal \"limit\"\n");
				return -1;
			}
			ok++;
		} else if (strcmp(*argv, "help") == 0) {
			explain();
			return -1;
		} else {
			fprintf(stderr, "What is \"%s\"?\n", *argv);
			explain();
			return -1;
		}
		argc--; argv++;
	}
*/
	addattr_l(n, 1024, TCA_OPTIONS, &opt, sizeof(opt));

	return 0;
}

static int
fifo_print_opt(qu, f, opt)
struct qdisc_util* qu;
FILE* f;
struct rtattr* opt;
{
	struct tc_fifo_qopt *qopt;

	if(opt == NULL)
		return 0;

	if(RTA_PAYLOAD(opt) < sizeof(*qopt))
		return -1;

	qopt = RTA_DATA(opt);
	if(strcmp(qu->id, "bfifo") == 0) {
		SPRINT_BUF(b1);
		fprintf(f, "limit %s", sprint_size(qopt->limit, b1));
	} else
		fprintf(f, "limit %up", qopt->limit);

	return 0;
}


struct qdisc_util bfifo_qdisc_util = {
	.id = "bfifo",
	.parse_qopt = fifo_parse_opt,
	.print_qopt = fifo_print_opt,
};

struct qdisc_util pfifo_qdisc_util = {
	.id = "pfifo",
	.parse_qopt = fifo_parse_opt,
	.print_qopt = fifo_print_opt,
};

extern int prio_print_opt(struct qdisc_util* qu, FILE* f, struct rtattr* opt);
struct qdisc_util pfifo_fast_qdisc_util = {
	.id = "pfifo_fast",
	.print_qopt = prio_print_opt,
};
