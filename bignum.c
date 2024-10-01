/******************************************************************************
 *
 * File Name: bignum.h
 *	      (c) 2024 AED
 * Author:    Luis Miguel Silveira & AED Team
 * Revision:  21 Set 2024
 *
 * NAME
 *     bignum.h - implementation library for handling bignums
 *
 * SYNOPSIS
 *     #include "bignum.h"
 *
 * DESCRIPTION
 *     Support function for bignum representation of unlimited size integers
 *
 * DIAGNOSTICS
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bignum.h"


typedef struct _digits {
  unsigned char digit ;
  struct _digits *ndig;
} Digits;

typedef struct _bignum {
  unsigned long size;
  unsigned char sign;
  Digits *digitList;
} BigNum;



/******************************************************************************
 * bn_BNfromDecStr()
 *
 * Arguments: pointer to BigNum structure
 * Returns: decstr - pointer to decimal number string
 * Side-Effects: allocates BigNum structure
 *
 * Description: creates a bignum representation for a number whose digits are
 *              stored in a string, the first character of which could be a
 *              '-' indicating the number is negative (otherwise it is
 *              positive).
 *
 *****************************************************************************/

BigNum *bn_BNfromDecStr(char *decstr) {
  BigNum *bn;
  Digits *nd, *aux = (Digits*)NULL;
  int i, st =0;

  /* let us allocate space for the bignum main structure */
  bn = (BigNum*) malloc(sizeof(BigNum));
  if (bn == ((BigNum*)NULL)) {
    fprintf(stderr, "error: cannot allocate bignum structure.  exiting.\n");

    exit(1);
  }
  /* now initialize */
  bn->sign = 0;
  bn->size = 0;
  bn->digitList = (Digits*) NULL;

  /* if number is negative, mark the sign and discard first char of string */
  if (decstr[0] == '-') {
      bn->sign = 1;
      st = 1;
  } else if (decstr[0] == '+') {
    /* less likely, but number can also be positive, so handle it he same way */
    st = 1;
  }
  /* let us go through the string, one digit at a time, from the right (end)
   * to the left (beginning)
   */
  for (i = strlen(decstr)-1; i >= st; i --) {
    /* allocate space for the digit */
    nd = (Digits*) malloc(sizeof(Digits));
    if (nd == ((Digits*)NULL)) {
      fprintf(stderr,
              "error: cannot allocate bignum bitb structure.  exiting.\n");
      exit(1);
    }
    /* assuming the digit is really a digit, we simply copy it as a digit,
    * se we really want to save the number, not the ascii code */
    if ((decstr[i] >= '0') && (decstr[i] <= '9'))
      nd->digit = (unsigned char) (decstr[i] - '0');
    else {
      fprintf(stderr, "error: found strange char in bit string.  exiting.\n");
      exit(1);
    }
    nd->ndig = (Digits*)NULL;
    /* if it is the first digit, it stays the head of the list */
    if (bn->digitList == (Digits *) NULL) {
      bn->digitList = nd;
    } else {
      /* just add it to the end of the list */
      aux->ndig = nd;
    }
    bn->size++;
    aux = nd;
  }
  /* after going through the entire string, we have the representation of
   * the bignum; return the pointer to the structure
   */

  return(bn);
}


/******************************************************************************
 * bn_DecStrfromBN()
 *
 * Arguments: pointer to BigNum structure
 * Returns: decstr - pointer to decimal number string
 * Side-Effects: allocates string for conversion
 *
 * Description: converts a bignum into a string of digits; useful for
 *              later visualization; first digit in bignum representation is
 *              least significative (LSD), so it needs to be stored at the
 *              "end" of the string to be visualized on the right. Since we
 *              do not know the number of digits the number has, we cannot do
 *              do that directly, so we store the digits on the string from
 *              position 0 (or 1 if negative) onwards.  Once this is completed
 *              we reverse the string digits in place (swap first with last,
 *              second with the one before last, etc).  In the end,
 *              the string is filled in the usual way and can be printed.
 *
 *****************************************************************************/

char *bn_DecStrfromBN(BigNum *bn) {
  Digits *nd;
  char *decstr, temp;
  int i, st = 0;

  /* string must hold bignum digits, plus sign digit plus terminator */
  decstr = (char*) malloc((bn->size+1+1) * sizeof(char));
  if (decstr == ((char*)NULL)) {
    fprintf(stderr,
            "error: cannot allocate binary string structure.  exiting.\n");
    exit(1);
  }
  /* if the sign is 1, it means it is a negative number, so the first
   * character of the string becomes '-' */
  if (bn->sign == 1) {
    decstr[0] = '-';
    st++;
  }

  /* recall the list of digits in the bignum representation starts with
   * the LSD, least significant digit; so when processing the list we
   * get a string that is visually backwards, i.e the number 39 will be
   * shown as "93" on the string because we handle the digit '9' first,
   * so we write to the string from the end back to the beginning
   */
  for (i = bn->size+st-1, nd = bn->digitList;
       nd != (Digits*)NULL && i >= st;
       nd = nd->ndig, i--) {
    /* now we want the character equivalent to the digit, not the number */
    decstr[i] = (char) (nd->digit + '0');
  }
  decstr[bn->size+st] = '\0';
  return(decstr);
}


/******************************************************************************
 * bn_copy()
 *
 * Arguments: bn - pointer to a bignum
 * Returns: pointer to the new bignum, copy
 * Side-Effects: allocates BigNum structure
 *
 * Description: returns a new bignum which is a copy of the one given.
 *
 *
 *****************************************************************************/

BigNum *bn_copy(BigNum *x) {
  BigNum *bn;
  Digits *ndx, *nd, *aux;

  /* let us allocate space for the bignum main structure */
  bn = (BigNum*) malloc(sizeof(BigNum));
  if (bn == ((BigNum*)NULL)) {
    fprintf(stderr, "error: cannot allocate bignum structure.  exiting.\n");
    exit(1);
  }
  /* now initialize */
  bn->size = x->size;
  bn->sign = x->sign;
  bn->digitList = (Digits*) NULL;

  for (ndx = x->digitList; ndx != NULL; ndx = ndx->ndig) {
    /* allocate space for the digit */
    nd = (Digits*) malloc(sizeof(Digits));
    if (nd == ((Digits*)NULL)) {
      fprintf(stderr,
              "error: cannot allocate bignum bitb structure.  exiting.\n");
      exit(1);
    }
    nd->digit = ndx->digit;
    nd->ndig = (Digits *) NULL;
    /* if it is the first digit, it stays the head of the list */
    if (bn->digitList == (Digits *) NULL) {
      bn->digitList = nd;
    } else {
      /* just add it to the end of the list */
      aux->ndig = nd;
    }
    aux = nd;
  }

  return(bn);
}


/******************************************************************************
 * bn_symmetric()
 *
 * Arguments: bn - pointer to a bignum
 * Returns: pointer to the new bignum, symmetric
 * Side-Effects: allocates BigNum structure
 *
 * Description: returns a new bignum which is the symmetric of the one given.
 *
 *
 *****************************************************************************/

BigNum *bn_symmetric(BigNum *x) {
  BigNum *bn;

  /* ... */

  return(bn);
}


/******************************************************************************
 * bn_isZero()
 *
 * Arguments: bn - pointer to a bignum
 * Returns: 1 if the bignum is zero, 0 otherwise
 * Side-Effects: (none)
 *
 * Description: determines if the bignum is zero; in this case it can only
 *              have one digit which must be the digit 0
 *
 *****************************************************************************/

int bn_isZero(BigNum *x) {
  Digits *nd = x->digitList;

  if ((nd->digit == 0) && (nd->ndig == (Digits*)NULL))
    return 1;
  else
    return 0;
}


/******************************************************************************
 * bn_compare()
 *
 * Arguments: x, y - pointers to two bignums
 * Returns: 1, 0 or -1 if respectively x>y, x==y or x<y
 * Side-Effects: (none)
 *
 * Description: compares two bignums and return an indication of which is
 *              bigger
 *
 *****************************************************************************/

int bn_compare(BigNum *x, BigNum *y) {
  Digits *ndx, *ndy;
  int result = 0; // Inicializar o resultado

  // Comparação de sinais
  if (x->sign == 1 && y->sign == 0) {
    result = -1; // x é negativo e y é positivo
  } else if (y->sign == 1 && x->sign == 0) {
    result = 1; // x é positivo e y é negativo
  } else {
    // Ambos têm o mesmo sinal
    if (x->sign == 1 && y->sign == 1) {
      // Ambos negativos
      if (x->size > y->size) {
        result = -1; // x é maior em tamanho, mas negativo (x < y)
      } else if (y->size > x->size) {
        result = 1; // y é maior em tamanho, mas negativo (x > y)
      }
    } else if (x->sign == 0 && y->sign == 0) {
      // Ambos positivos
      if (x->size > y->size) {
        result = 1; // x é maior em tamanho (x > y)
      } else if (y->size > x->size) {
        result = -1; // y é maior em tamanho (x < y)
      }
    }

    // Se os tamanhos são iguais, comparar dígito a dígito
    if (x->size == y->size) {
      ndx = x->digitList;
      ndy = y->digitList;

      while (ndx != NULL && ndy != NULL) {
        if (ndx->digit > ndy->digit) {
          result = (x->sign == 0) ? 1 : -1; // Positivos: x > y, Negativos: x < y
          break;
        } else if (ndx->digit < ndy->digit) {
          result = (x->sign == 0) ? -1 : 1; // Positivos: x < y, Negativos: x > y
          break;
        }
        // Continuar para o próximo dígito
        ndx = ndx->ndig;
        ndy = ndy->ndig;
      }
    }
  }

  // Se os números são exatamente iguais, result permanecerá 0
  return result;
}


/******************************************************************************
 * bn_add()
 *
 * Arguments: x, y - pointers to two bignums
 * Returns: bignum (x+y)
 * Side-Effects: allocates BigNum structure for result
 *
 * Description: computes sum of two bignums
 *
 *****************************************************************************/

BigNum *bn_add(BigNum *x, BigNum *y) {
  BigNum *bn;
  Digits *ndx, *ndy, *nd, *aux;
  char newn, carry;

  /* let us allocate space for the bignum main structure */
  bn = (BigNum*) malloc(sizeof(BigNum));
  if (bn == ((BigNum*)NULL)) {
    fprintf(stderr, "error: cannot allocate bignum structure.  exiting.\n");
    exit(1);
  }

  
  /* now initialize */
  bn->size = 0;
  bn->sign = 0;
  bn->digitList = (Digits*) NULL;
  ndx = x->digitList;  // Apontador para o primeiro dígito de x
  ndy = y->digitList;  // Apontador para o primeiro dígito de y

  carry = 0;
  aux = NULL;
  /* Laço para somar os dígitos de x e y */
  while (ndx != NULL || ndy != NULL || carry != 0) {
    newn = carry;  // Inicialmente, newn será o carry acumulado
    /* Somar o dígito de x, se existir */
    if (ndx != NULL) {
      newn += ndx->digit;
      ndx = ndx->ndig; // Ponteiro pro próximo
    }

    /* Somar o dígito de y, se existir */
    if (ndy != NULL) {
      newn += ndy->digit;
      ndy = ndy->ndig;
    }
    /* Se newn for maior que 9, haverá carry para o próximo dígito */
    if (newn >= 10) {
      newn -= 10;
      carry = 1;
    } else {
      carry = 0;
    }

    /* Criar novo dígito para o resultado */
    nd = (Digits*) malloc(sizeof(Digits));
    if (nd == ((Digits*)NULL)) {
      fprintf(stderr, "error: cannot allocate digit structure.  exiting.\n");
      exit(1);
    }
    nd->digit = newn;  // Armazena o novo dígito
    nd->ndig = NULL;   // O novo dígito não aponta para o próximo ainda


     /* Adicionar o novo dígito à lista do resultado */
    if (bn->digitList == NULL) {
      bn->digitList = nd;  // O primeiro dígito será a cabeça da lista
    } else {
      aux->ndig = nd;  // Conectar o novo dígito à lista
    }
    aux = nd;  // Atualiza o ponteiro auxiliar para o último dígito

    bn->size++;  // Incrementa o tamanho do BigNum
  /* ... */
  }
  return(bn);
}


/******************************************************************************
 * bn_multby2()
 *
 * Arguments: x - pointer to bignum
 * Returns: bignum
 * Side-Effects: allocates BigNum structure for result
 *
 * Description: creates a new bignum which is 2 * x
 *
 *****************************************************************************/

BigNum *bn_multby2(BigNum *x) {
  BigNum *bn;
  Digits *ndx, *nd, *aux;
  char newn, carry;

  /* let us allocate space for the bignum main structure */
  bn = (BigNum*) malloc(sizeof(BigNum));
  if (bn == ((BigNum*)NULL)) {
    fprintf(stderr, "error: cannot allocate bignum structure.  exiting.\n");
    exit(1);
  }
  /* now initialize */
  bn->size = x->size;
  bn->sign = x->sign;
  bn->digitList = (Digits*) NULL;

  carry = 0;
  for (ndx = x->digitList; ndx != NULL; ndx = ndx->ndig) {
    /* allocate space for the digit */
    nd = (Digits*) malloc(sizeof(Digits));
    if (nd == ((Digits*)NULL)) {
      fprintf(stderr,
              "error: cannot allocate bignum bitb structure.  exiting.\n");
      exit(1);
    }
    newn = ndx->digit * 2 + carry;
    if (newn >= 10) {
      newn = (newn % 10);
      carry = 1;
    } else {
      carry = 0;
    }
    nd->digit = newn;
    nd->ndig = (Digits *) NULL;
    /* if it is the first digit, it stays the head of the list */
    if (bn->digitList == (Digits *) NULL) {
      bn->digitList = nd;
    } else {
      /* just add it to the end of the list */
      aux->ndig = nd;
    }
    aux = nd;
  }
  /* if there was a carry, we have one more digit to add */
  if (carry == 1) {
    nd = (Digits*) malloc(sizeof(Digits));
    if (nd == ((Digits*)NULL)) {
      fprintf(stderr,
              "error: cannot allocate bignum bitb structure.  exiting.\n");
      exit(1);
    }
    bn->size++;
    nd->digit = carry;
    nd->ndig = (Digits *) NULL;
    aux->ndig = nd;
  }

  return(bn);
}


/******************************************************************************
 * bn_free()
 *
 * Arguments: x - pointer to bignum
 * Returns: void
 * Side-Effects: frees the memory associated with the bignum
 *
 * Description: given a bignum frees the memory for all list elements and
 *              also with the bignum header
 *
 *****************************************************************************/

void bn_free(BigNum *x) {
  Digits *ndx, *aux;

  /* go through all list elements and free them */
  for (ndx = x->digitList; ndx != NULL; ndx = aux) {
    aux = ndx->ndig;
    free(ndx);
  }
  /* free header */
  free(x);

  return;
}


/******************************************************************************
 * bn_oper()
 *
 * Arguments: x - pointer to bignum
 * Returns:
 * Side-Effects:
 *
 * Description: should do what is asked in the lab for problem 2.3
 *              may require changing the input arguments or the return value
 *
 *****************************************************************************/

BigNum *bn_oper(BigNum *x) {
  BigNum *bn;

  /* ... */

  return(bn);
}
