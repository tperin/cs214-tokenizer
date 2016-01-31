/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
	char *str;
	int pos;
};

typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 * 
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char * ts ) {
	TokenizerT *newTK = (TokenizerT*) malloc(sizeof(TokenizerT));
	newTK->str = ts;
	newTK->pos = 0;
	return newTK;
	return NULL;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken( TokenizerT * tk ) {
	int startpos = tk->pos;
	char *ptr = tk->str + (sizeof(char)*startpos);
//	printf("1: %c\n",*ptr);
	
	while (1) {
		if (*ptr == NULL) {
//			printf("2: %c\n",*ptr);
			break;
		}
		if (isalpha(*ptr)) {
			int xf = 0;
			while(isalnum(*ptr)) {
//				printf("%c ",*ptr);
				ptr++;
				xf++;
			}

			tk->pos = startpos + xf;
			char buff[xf+1];

			memcpy(buff,tk->str + (sizeof(char)*startpos),xf);
			buff[xf] = '\0';
	//		printf("%s\n",buff);
			return buff;
			
		}
		else if (isnumber(*ptr)) {
			int xf = 0;
//			int ishex = 0;
			
//			if (*ptr == '0') {
//				xf++;
//				ptr++;
//				if (*ptr == 'x' || *ptr == 'X') {
//					xf++;
//					ptr++;
//					if (isnumber(*ptr)) {
//						
//					}
//				}
//			}
			while (isnumber(*ptr) || *ptr == 'x' || *ptr == 'X') {
				xf++;
				ptr++;
			}
			tk->pos = startpos + xf;
			char buff[xf+1];
			memcpy(buff,tk->str + (sizeof(char)*startpos),xf);
			buff[xf] = '\0';
			return buff;

		}
		else if (*ptr == ' ' || *ptr == '\t' || *ptr == '\v' || *ptr == '\f' || *ptr == '\n' || *ptr == '\r') {
			startpos++;
			ptr++;
		}
		else {
			return NULL;
		}
	}
	return NULL;
}


char *determineType(char *val) {
	char *ptr = val;
	if (*ptr == '0') {
		ptr++;
		if (*ptr == 'x' || *ptr == 'X') {
			return "hexadecimal integer";
		}
		
		int ctr = 0;
		while (ctr < 3) {
			if (!isnumber(*ptr)) break;
			int num = *ptr - '0';
			if (num < 0 || num > 7) break;
			if (ctr == 2) return 'Octal';
		}
		ptr = val;
	}
	
	if (isnumber(*ptr)) {
		ptr++;
		if (*ptr == 'x' || *ptr == 'X') {
			ptr++;
			if (isnumber(*ptr)) {
				return "hexadecimal integer";
			}
			return "fuck";
		}
		if (*)
		return "decimal integer";
	}
}

/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {
	TokenizerT *t = NULL;
	
	if (argc <= 1) {
		t = TKCreate("test123g 234 0x540");
	}
	else {
		t = TKCreate(argv[1]);
	}

	while (1) {
		char *ayylmao = TKGetNextToken(t);
		if (ayylmao == NULL) {
			break;
		}
		else {
			printf("type: %s\n",ayylmao);
		}
	}
	return 0;
}