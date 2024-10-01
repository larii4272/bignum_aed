/******************************************************************************
 *
 * File Name: bignum.h
 *	      (c) 2024 AED
 * Author:    Luis Miguel SIlveira & AED Team
 * Revision:  21 Set 2024
 *
 * NAME
 *     bignum.h - implementation library for handling bignums
 *
 * SYNOPSIS
 *     #include <stdio.h>
 *     #include <stdlib.h>
 *
 * DESCRIPTION
 *
 *
 * DIAGNOSTICS
 *
 *****************************************************************************/


#ifndef _BIGNUM_H
#define _BIGNUM_H

#include <stdio.h>
#include <stdlib.h>


typedef struct _bignum BigNum;

/* these are support functions for input/output conversion for visualization */
BigNum *bn_BNfromDecStr (char *decstr);
char *bn_DecStrfromBN (BigNum *bn);

/* operations on and with bignum's */
BigNum *bn_copy(BigNum*);

BigNum *bn_add (BigNum*, BigNum*);

BigNum *bn_symmetric (BigNum*);

int bn_compare (BigNum*, BigNum*);

int bn_isZero (BigNum*);

BigNum *bn_multby2 (BigNum*);

void bn_free(BigNum*);

BigNum *bn_oper (BigNum*);

#endif
