/******************************************************************************
 *
 * File Name: p3-pub.c
 *	      (c) 2018 AED
 * Author:    Luis Miguel Silveira & AED Team
 * Revision:  16 Oct 2018
 *
 * NAME
 *     p3-pub.c - bignum operations
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *
 * DESCRIPTION
 *
 *
 * DIAGNOSTICS
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bignum.h"

/* this is arbitrary; using 2k for exemplification purposes */
#define MAX_STR 2048

#define DEBUG 1


int main(void)
{
  int ret;
  char *d1str, *d2str, *xstr, *ystr, *zstr;
  BigNum *x, *y, *z;

  /* please note that this code is for testing purposes only; in
   * reality it makes littles sense to use strings of fixed length since the
   * bignums, by definition can indeed have any length/size; but this is
   * only for testing purposes, so we try to simplify
   */
  d1str = (char*) calloc(1, MAX_STR*sizeof(char));
  d2str = (char*) calloc(1, MAX_STR*sizeof(char));

  /* let us create some bignums using intermediate string representations */
  if (scanf("%s %s", d1str, d2str) != 2) {
    fprintf(stderr, "could not read 2 long integers. exiting.\n");
    exit(1);
  }

  /* create bignum representation from binary string representation;
   * note that here we do not allocate a stirng of arbitrary length; the
   * string is allocated inside the bignum library function and has the
   * "right" size
   */
  x = bn_BNfromDecStr(d1str);
  y = bn_BNfromDecStr(d2str);
  z = bn_multby2(x);

  BigNum *a, *b, *c;
  char *astr, *bstr, *cstr;
  int i, j;
  a = bn_add(x,z);
  i = bn_compare(x,z);
  j = bn_compare(x,y);

#if DEBUG==1
  xstr = bn_DecStrfromBN(x);
  printf("%s is %s\n", d1str, xstr);
  ystr = bn_DecStrfromBN(y);
  printf("%s is %s\n", d2str, ystr);
  zstr = bn_DecStrfromBN(z);
  printf("%s is %s\n", d1str, zstr);

  astr = bn_DecStrfromBN(a);
  printf("%s\n",  astr);
  
  printf("compare %d\n",  i);
  
  printf("compare %d\n",  j);
#endif

  /* free the strings read from stdin and explicitly allocated above */
  free(d1str);
  free(d2str);
  /* free the three bignums created */
  bn_free(x);
  bn_free(y);
  bn_free(z);
  bn_free(a);
  //bn_free(b);
  //bn_free(c);
  /* free the three strings created in the bignum library function */
  free(xstr);
  free(ystr);
  free(zstr);
  free(astr);
  //free(bstr);
  //free(cstr);

  /* now do some operations with x and y */

  /* x+y?  x>y?  x*y?  ... */

  /* check if you need to free any more memory */

  return 0;
}

