#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include "la.h"

/*
Design a Recursive Descent Parser for the following grammar:
Query -> select Parameters Fclause Wclause
Parameters -> id | id, Parameters
Fclause -> from Parameters
Wclause -> where Exp
Exp -> id='Character'
Sample input: select a from T1 where a='c'
*/


