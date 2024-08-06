/*
 *  wc.l
 *
 *  Stefano Guerrini
 *  23/03/2012
 */

%option noyywrap

%{
    #include <stdio.h>

	/* counters */
	int nchars = 0;
	int nwords = 0;
	int nlines = 0;
%}

	/* newline */
NL	\n
	/* non-whitespace */
NWS	[^ \t\n]

%%

	/* newline: increase chars and lines */
{NL}		{
          nlines++;
          nchars++;
	        return 1;
        }

	/* word (a maximal sequence of non-whitespaces):
	 add the lenght of the word to chars and
	 increase words */
{NWS}+		nchars += yyleng; nwords++;

	/* whitespace: increase chars */
.         nchars++;

<<EOF>>   return 0;

%%

int main(int argc, char *argv[]) {
	/* start scanner */
	while (yylex() == 1);
	/* print results */
	printf("%8d%8d%8d\n", nlines, nwords, nchars);
  return EXIT_SUCCESS;
}
