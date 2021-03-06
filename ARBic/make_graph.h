#ifndef _MAKE_GRAPH_H
#define _MAKE_GRAPH_H

#include "struct.h"

/* global data */
int col_width;
Edge **edge_list;
Edge *edge_ptr;

/* from cluster */
extern bits16 **profile;

/* global functions */
extern int cluster (FILE *fw, Edge **el, int n);

/* prototypes */
void seed_update (const discrete *s);
int str_intersect_r (const discrete *s1, const discrete *s2,char tag);
void seed_deduct (const discrete *s);
void make_graph (const char *fn);
static int edge_cmpr(void *a, void *b);
static void fh_insert_fixed(struct fibheap *a, Edge *i, Edge **cur_min);
static void fh_dump(struct fibheap *a, Edge **res);

/*get positive lcs of each seed,return the cosine similarity*/
extern int get_Genes_LCS(const discrete *s1, const discrete *s2,char *lcs_tg);
/*get the CSvalue of each seed*/
extern int get_Genes_LCS_R(const discrete *s1,const discrete *s2,char *lcs_ptrR);
extern int get_Genes_LCS_length(const discrete *s1, const discrete *s2);
int min_colsofbic(int rows);
#endif
