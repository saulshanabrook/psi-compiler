/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.

   dist.e - exported functions from dist.c	

*/

extern char *host_name;
extern int host;
extern int para_trace;
extern dist_t *distribution;
extern dist_assign(reduced_t *global, reduced_t *distributed,
	expr_t *res, dist_t *l_dist);
extern init_dist_arrays(dist_t *dist);
extern init_collect_arrays(dist_t *dist);
extern code_global_int(ident_t *ident);
extern dist_t *find_dist(ident_t *array);
