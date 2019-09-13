/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is included that follows the "include" declaration
** in the input grammar file. */
#include <stdio.h>
#line 24 "/home/cian/Documents/GitHub/HEtest/hetest/cpp/baseline/heaan/server/debug/parser.y"


#include <cstdlib>
/* cassert is required by lemon */
#include <cassert>
#include <map>
#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>

#include "baseline/common/lex-global.h"

/* auto-generated header containing macros for Flex tokens */
#include "parser.h"

#include "baseline/heaan/server/struct-def.h"
#include "baseline/heaan/server/gates.h"
#include "common/logging.h"

std::vector<WirePtr>* wires;
std::map<std::string, GatePtr> gates;

#line 31 "/home/cian/Documents/GitHub/HEtest/hetest/cpp/baseline/heaan/server/debug/parser.c"
/* Next is all token values, in a form suitable for use by makeheaders.
** This section will be null unless lemon is run with the -m switch.
*/
/* 
** These constants (all generated automatically by the parser generator)
** specify the various kinds of tokens (terminals) that the parser
** understands. 
**
** Each symbol here is a terminal symbol in the grammar.
*/
/* Make sure the INTERFACE macro is defined.
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/* The next thing included is series of defines which control
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 terminals
**                       and nonterminals.  "int" is used otherwise.
**    YYNOCODE           is a number of type YYCODETYPE which corresponds
**                       to no legal terminal or nonterminal number.  This
**                       number is used to fill in empty slots of the hash 
**                       table.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       have fall-back values which should be used if the
**                       original value of the token will not parse.
**    YYACTIONTYPE       is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 rules and
**                       states combined.  "int" is used otherwise.
**    ParseTOKENTYPE     is the data type used for minor tokens given 
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is ParseTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    ParseARG_SDECL     A static variable declaration for the %extra_argument
**    ParseARG_PDECL     A parameter declaration for the %extra_argument
**    ParseARG_STORE     Code to store %extra_argument into yypParser
**    ParseARG_FETCH     Code to extract %extra_argument from yypParser
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
#define YYCODETYPE unsigned char
#define YYNOCODE 26
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE YYSTYPE
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  GateToken yy13;
  InputToken yy24;
  BitsToken yy46;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL ParserState* parser_state;
#define ParseARG_PDECL ,ParserState* parser_state
#define ParseARG_FETCH ParserState* parser_state = yypParser->parser_state
#define ParseARG_STORE yypParser->parser_state = parser_state
#define YYNSTATE 41
#define YYNRULE 17
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

/* The yyzerominor constant is used to initialize instances of
** YYMINORTYPE objects to zero. */
static const YYMINORTYPE yyzerominor = { 0 };

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
**
**   N == YYNSTATE+YYNRULE              A syntax error has occurred.
**
**   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
**
**   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as
**
**      yy_action[ yy_shift_ofst[S] + X ]
**
** If the index value yy_shift_ofst[S]+X is out of range or if the value
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
** is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
** and that yy_default[S] should be used instead.  
**
** The formula above is for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
*/
#define YY_ACTTAB_COUNT (56)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    23,   37,   41,   21,   19,   29,   28,   16,   59,   25,
 /*    10 */     1,   36,   26,   11,   30,   27,   29,   28,   24,   17,
 /*    20 */    14,    2,   33,   33,    8,   40,   38,    6,   13,   35,
 /*    30 */     4,   12,   34,   10,    3,   60,   24,    9,   31,   60,
 /*    40 */    32,   60,   60,   60,   60,    7,   22,   60,    5,   60,
 /*    50 */    20,   18,   60,   15,   60,   39,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     5,    3,    0,    8,    9,    1,    2,   12,   19,   20,
 /*    10 */    21,   13,   23,   22,   23,   24,    1,    2,    3,   11,
 /*    20 */    11,    4,   14,   14,    6,   24,    7,    6,   18,    7,
 /*    30 */     6,   18,    7,   10,    6,   25,    3,   10,    7,   25,
 /*    40 */    14,   25,   25,   25,   25,   16,   16,   25,   16,   25,
 /*    50 */    16,   16,   25,   16,   25,   17,
};
#define YY_SHIFT_USE_DFLT (-6)
#define YY_SHIFT_COUNT (25)
#define YY_SHIFT_MIN   (-5)
#define YY_SHIFT_MAX   (33)
static const signed char yy_shift_ofst[] = {
 /*     0 */     4,   15,   -5,   -2,   -2,   -2,   -2,   -2,   -2,   26,
 /*    10 */    26,   33,    9,    8,   31,   27,   28,   25,   23,   24,
 /*    20 */    22,   21,   19,   18,   17,    2,
};
#define YY_REDUCE_USE_DFLT (-12)
#define YY_REDUCE_COUNT (11)
#define YY_REDUCE_MIN   (-11)
#define YY_REDUCE_MAX   (38)
static const signed char yy_reduce_ofst[] = {
 /*     0 */   -11,   -9,   38,   37,   35,   34,   32,   30,   29,   13,
 /*    10 */    10,    1,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */    58,   58,   58,   58,   58,   58,   58,   58,   58,   58,
 /*    10 */    58,   42,   58,   58,   58,   58,   58,   58,   58,   58,
 /*    20 */    58,   58,   58,   58,   58,   58,   44,   48,   46,   45,
 /*    30 */    43,   53,   57,   56,   52,   51,   55,   54,   50,   49,
 /*    40 */    47,
};

/* The next table maps tokens into fallback tokens.  If a construct
** like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  int yyidx;                    /* Index of top element in stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyidxMax;                 /* Maximum value of yyidx */
#endif
  int yyerrcnt;                 /* Shifts left before out of the error */
  ParseARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void ParseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "NUM_INPUTS",    "LENGTH",        "LABEL",       
  "COLON",         "MUL",           "LPAREN",        "RPAREN",      
  "ADD",           "MULCONST",      "LBRACKET",      "RBRACKET",    
  "ADDCONST",      "WIRE",          "NUM",           "error",       
  "input",         "gate",          "bits",          "program",     
  "circuit",       "headers",       "gate_defs",     "header",      
  "gate_def",    
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "program ::= circuit",
 /*   1 */ "circuit ::= headers gate_defs",
 /*   2 */ "headers ::= headers header",
 /*   3 */ "headers ::= header",
 /*   4 */ "header ::= NUM_INPUTS",
 /*   5 */ "header ::= LENGTH",
 /*   6 */ "gate_defs ::= gate_defs gate_def",
 /*   7 */ "gate_defs ::= gate_def",
 /*   8 */ "gate_def ::= LABEL COLON gate",
 /*   9 */ "gate ::= MUL LPAREN input input RPAREN",
 /*  10 */ "gate ::= ADD LPAREN input input RPAREN",
 /*  11 */ "gate ::= MULCONST LPAREN input LBRACKET bits RBRACKET RPAREN",
 /*  12 */ "gate ::= ADDCONST LPAREN input LBRACKET bits RBRACKET RPAREN",
 /*  13 */ "input ::= LABEL",
 /*  14 */ "input ::= WIRE",
 /*  15 */ "bits ::= bits NUM",
 /*  16 */ "bits ::= NUM",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.
*/
static void yyGrowStack(yyParser *p){
  int newSize;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  if( pNew ){
    p->yystack = pNew;
    p->yystksz = newSize;
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows to %d entries!\n",
              yyTracePrompt, p->yystksz);
    }
#endif
  }
}
#endif

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to Parse and ParseFree.
*/
void *ParseAlloc(void *(*mallocProc)(size_t)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (size_t)sizeof(yyParser) );
  if( pParser ){
    pParser->yyidx = -1;
#ifdef YYTRACKMAXSTACKDEPTH
    pParser->yyidxMax = 0;
#endif
#if YYSTACKDEPTH<=0
    pParser->yystack = NULL;
    pParser->yystksz = 0;
    yyGrowStack(pParser);
#endif
  }
  return pParser;
}

/* The following function deletes the value associated with a
** symbol.  The symbol can be either a terminal or nonterminal.
** "yymajor" is the symbol code, and "yypminor" is a pointer to
** the value.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  ParseARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
**
** Return the major token number for the symbol popped.
*/
static int yy_pop_parser_stack(yyParser *pParser){
  YYCODETYPE yymajor;
  yyStackEntry *yytos = &pParser->yystack[pParser->yyidx];

  if( pParser->yyidx<0 ) return 0;
#ifndef NDEBUG
  if( yyTraceFILE && pParser->yyidx>=0 ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yymajor = yytos->major;
  yy_destructor(pParser, yymajor, &yytos->minor);
  pParser->yyidx--;
  return yymajor;
}

/* 
** Deallocate and destroy a parser.  Destructors are all called for
** all stack elements before shutting the parser down.
**
** Inputs:
** <ul>
** <li>  A pointer to the parser.  This should be a pointer
**       obtained from ParseAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
void ParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
  if( pParser==0 ) return;
  while( pParser->yyidx>=0 ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  free(pParser->yystack);
#endif
  (*freeProc)((void*)pParser);
}

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int ParseStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyidxMax;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;
 
  if( stateno>YY_SHIFT_COUNT
   || (i = yy_shift_ofst[stateno])==YY_SHIFT_USE_DFLT ){
    return yy_default[stateno];
  }
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    if( iLookAhead>0 ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        return yy_find_shift_action(pParser, iFallback);
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( 
#if YY_SHIFT_MIN+YYWILDCARD<0
          j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
          j<YY_ACTTAB_COUNT &&
#endif
          yy_lookahead[j]==YYWILDCARD
        ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
    }
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( i!=YY_REDUCE_USE_DFLT );
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser, YYMINORTYPE *yypMinor){
   ParseARG_FETCH;
   yypParser->yyidx--;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
   ParseARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer to the minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yyidx++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( yypParser->yyidx>yypParser->yyidxMax ){
    yypParser->yyidxMax = yypParser->yyidx;
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yyidx>=YYSTACKDEPTH ){
    yyStackOverflow(yypParser, yypMinor);
    return;
  }
#else
  if( yypParser->yyidx>=yypParser->yystksz ){
    yyGrowStack(yypParser);
    if( yypParser->yyidx>=yypParser->yystksz ){
      yyStackOverflow(yypParser, yypMinor);
      return;
    }
  }
#endif
  yytos = &yypParser->yystack[yypParser->yyidx];
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor = *yypMinor;
#ifndef NDEBUG
  if( yyTraceFILE && yypParser->yyidx>0 ){
    int i;
    fprintf(yyTraceFILE,"%sShift %d\n",yyTracePrompt,yyNewState);
    fprintf(yyTraceFILE,"%sStack:",yyTracePrompt);
    for(i=1; i<=yypParser->yyidx; i++)
      fprintf(yyTraceFILE," %s",yyTokenName[yypParser->yystack[i].major]);
    fprintf(yyTraceFILE,"\n");
  }
#endif
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 19, 1 },
  { 20, 2 },
  { 21, 2 },
  { 21, 1 },
  { 23, 1 },
  { 23, 1 },
  { 22, 2 },
  { 22, 1 },
  { 24, 3 },
  { 17, 5 },
  { 17, 5 },
  { 17, 7 },
  { 17, 7 },
  { 16, 1 },
  { 16, 1 },
  { 18, 2 },
  { 18, 1 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  int yyruleno                 /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  ParseARG_FETCH;
  yymsp = &yypParser->yystack[yypParser->yyidx];
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno>=0 
        && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    fprintf(yyTraceFILE, "%sReduce [%s].\n", yyTracePrompt,
      yyRuleName[yyruleno]);
  }
#endif /* NDEBUG */

  /* Silence complaints from purify about yygotominor being uninitialized
  ** in some cases when it is copied into the stack after the following
  ** switch.  yygotominor is uninitialized when a rule reduces that does
  ** not set the value of its left-hand side nonterminal.  Leaving the
  ** value of the nonterminal uninitialized is utterly harmless as long
  ** as the value is never used.  So really the only thing this code
  ** accomplishes is to quieten purify.  
  **
  ** 2007-01-16:  The wireshark project (www.wireshark.org) reports that
  ** without this code, their parser segfaults.  I'm not sure what there
  ** parser is doing to make this happen.  This is the second bug report
  ** from wireshark this week.  Clearly they are stressing Lemon in ways
  ** that it has not been previously stressed...  (SQLite ticket #2172)
  */
  /*memset(&yygotominor, 0, sizeof(yygotominor));*/
  yygotominor = yyzerominor;


  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
      case 4: /* header ::= NUM_INPUTS */
#line 62 "/home/cian/Documents/GitHub/HEtest/hetest/cpp/baseline/heaan/server/debug/parser.y"
{
   wires = new std::vector<WirePtr>();
   for (int i=0; i < yymsp[0].minor.yy0.int_val; ++i) {
      wires->push_back(boost::shared_ptr<Wire>(new Wire()));
   }
   parser_state->wires = wires;
}
#line 725 "/home/cian/Documents/GitHub/HEtest/hetest/cpp/baseline/heaan/server/debug/parser.c"
        break;
      case 5: /* header ::= LENGTH */
#line 71 "/home/cian/Documents/GitHub/HEtest/hetest/cpp/baseline/heaan/server/debug/parser.y"
{
  parser_state->length = yymsp[0].minor.yy0.int_val;
}
#line 732 "/home/cian/Documents/GitHub/HEtest/hetest/cpp/baseline/heaan/server/debug/parser.c"
        break;
      case 8: /* gate_def ::= LABEL COLON gate */
#line 78 "/home/cian/Documents/GitHub/HEtest/hetest/cpp/baseline/heaan/server/debug/parser.y"
{
  GatePtr gate(yymsp[0].minor.yy13.gate);
  gates[yymsp[-2].minor.yy0.str_val] = gate;
  free((void*)yymsp[-2].minor.yy0.str_val);
  parser_state->output_gate = gate;
}
#line 742 "/home/cian/Documents/GitHub/HEtest/hetest/cpp/baseline/heaan/server/debug/parser.c"
        break;
      case 9: /* gate ::= MUL LPAREN input input RPAREN */
#line 86 "/home/cian/Documents/GitHub/HEtest/hetest/cpp/baseline/heaan/server/debug/parser.y"
{
   Mul* gate = new Mul();
   if (yymsp[-2].minor.yy24.type == WIRE) {
     gate->AddLeftInput((*wires)[yymsp[-2].minor.yy24.int_val]);
   } else {
     gate->AddLeftInput(gates[yymsp[-2].minor.yy24.str_val]);
     free((void*)yymsp[-2].minor.yy24.str_val);
   }
   if (yymsp[-1].minor.yy24.type == WIRE) {
     gate->AddRightInput((*wires)[yymsp[-1].minor.yy24.int_val]);
   } else {
     gate->AddRightInput(gates[yymsp[-1].minor.yy24.str_val]);
     free((void*)yymsp[-1].minor.yy24.str_val);
   }
   yygotominor.yy13.gate = gate;
}
#line 762 "/home/cian/Documents/GitHub/HEtest/hetest/cpp/baseline/heaan/server/debug/parser.c"
        break;
      case 10: /* gate ::= ADD LPAREN input input RPAREN */
#line 104 "/home/cian/Documents/GitHub/HEtest/hetest/cpp/baseline/heaan/server/debug/parser.y"
{
   Add* gate = new Add();
   if (yymsp[-2].minor.yy24.type == WIRE) {
     gate->AddLeftInput((*wires)[yymsp[-2].minor.yy24.int_val]);
   } else {
     gate->AddLeftInput(gates[yymsp[-2].minor.yy24.str_val]);
     free((void*)yymsp[-2].minor.yy24.str_val);
   }
   if (yymsp[-1].minor.yy24.type == WIRE) {
     gate->AddRightInput((*wires)[yymsp[-1].minor.yy24.int_val]);
   } else {
     gate->AddRightInput(gates[yymsp[-1].minor.yy24.str_val]);
     free((void*)yymsp[-1].minor.yy24.str_val);
   }
   yygotominor.yy13.gate = gate;
}
#line 782 "/home/cian/Documents/GitHub/HEtest/hetest/cpp/baseline/heaan/server/debug/parser.c"
        break;
      case 11: /* gate ::= MULCONST LPAREN input LBRACKET bits RBRACKET RPAREN */
#line 123 "/home/cian/Documents/GitHub/HEtest/hetest/cpp/baseline/heaan/server/debug/parser.y"
{
   MulConst* gate = new MulConst();
   if (yymsp[-4].minor.yy24.type == WIRE) {
     gate->AddInput((*wires)[yymsp[-4].minor.yy24.int_val]);
   } else {
     gate->AddInput(gates[yymsp[-4].minor.yy24.str_val]);
     free((void*)yymsp[-4].minor.yy24.str_val);
   }
   gate->SetConstant(*yymsp[-2].minor.yy46.bits);
   delete yymsp[-2].minor.yy46.bits;
   yygotominor.yy13.gate = gate;
}
#line 798 "/home/cian/Documents/GitHub/HEtest/hetest/cpp/baseline/heaan/server/debug/parser.c"
        break;
      case 12: /* gate ::= ADDCONST LPAREN input LBRACKET bits RBRACKET RPAREN */
#line 138 "/home/cian/Documents/GitHub/HEtest/hetest/cpp/baseline/heaan/server/debug/parser.y"
{
   AddConst* gate = new AddConst();
   if (yymsp[-4].minor.yy24.type == WIRE) {
     gate->AddInput((*wires)[yymsp[-4].minor.yy24.int_val]);
   } else {
     gate->AddInput(gates[yymsp[-4].minor.yy24.str_val]);
     free((void*)yymsp[-4].minor.yy24.str_val);
   }
   gate->SetConstant(*yymsp[-2].minor.yy46.bits);
   delete yymsp[-2].minor.yy46.bits;
   yygotominor.yy13.gate = gate;
}
#line 814 "/home/cian/Documents/GitHub/HEtest/hetest/cpp/baseline/heaan/server/debug/parser.c"
        break;
      case 13: /* input ::= LABEL */
#line 151 "/home/cian/Documents/GitHub/HEtest/hetest/cpp/baseline/heaan/server/debug/parser.y"
{
  yygotominor.yy24.type = LABEL;
  yygotominor.yy24.str_val = yymsp[0].minor.yy0.str_val;
}
#line 822 "/home/cian/Documents/GitHub/HEtest/hetest/cpp/baseline/heaan/server/debug/parser.c"
        break;
      case 14: /* input ::= WIRE */
#line 156 "/home/cian/Documents/GitHub/HEtest/hetest/cpp/baseline/heaan/server/debug/parser.y"
{
  yygotominor.yy24.type = WIRE;
  yygotominor.yy24.int_val = yymsp[0].minor.yy0.int_val;
}
#line 830 "/home/cian/Documents/GitHub/HEtest/hetest/cpp/baseline/heaan/server/debug/parser.c"
        break;
      case 15: /* bits ::= bits NUM */
#line 161 "/home/cian/Documents/GitHub/HEtest/hetest/cpp/baseline/heaan/server/debug/parser.y"
{
   *yymsp[-1].minor.yy46.bits *= 10;
   *yymsp[-1].minor.yy46.bits += yymsp[0].minor.yy0.int_val;
   yygotominor.yy46.bits = yymsp[-1].minor.yy46.bits;
}
#line 839 "/home/cian/Documents/GitHub/HEtest/hetest/cpp/baseline/heaan/server/debug/parser.c"
        break;
      case 16: /* bits ::= NUM */
#line 167 "/home/cian/Documents/GitHub/HEtest/hetest/cpp/baseline/heaan/server/debug/parser.y"
{
   yygotominor.yy46.bits = new ConstantVal(yymsp[0].minor.yy0.int_val);
}
#line 846 "/home/cian/Documents/GitHub/HEtest/hetest/cpp/baseline/heaan/server/debug/parser.c"
        break;
      default:
      /* (0) program ::= circuit */ yytestcase(yyruleno==0);
      /* (1) circuit ::= headers gate_defs */ yytestcase(yyruleno==1);
      /* (2) headers ::= headers header */ yytestcase(yyruleno==2);
      /* (3) headers ::= header */ yytestcase(yyruleno==3);
      /* (6) gate_defs ::= gate_defs gate_def */ yytestcase(yyruleno==6);
      /* (7) gate_defs ::= gate_def */ yytestcase(yyruleno==7);
        break;
  };
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->yyidx -= yysize;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,(YYCODETYPE)yygoto);
  if( yyact < YYNSTATE ){
#ifdef NDEBUG
    /* If we are not debugging and the reduce action popped at least
    ** one element off the stack, then we can push the new element back
    ** onto the stack here, and skip the stack overflow test in yy_shift().
    ** That gives a significant speed improvement. */
    if( yysize ){
      yypParser->yyidx++;
      yymsp -= yysize-1;
      yymsp->stateno = (YYACTIONTYPE)yyact;
      yymsp->major = (YYCODETYPE)yygoto;
      yymsp->minor = yygotominor;
    }else
#endif
    {
      yy_shift(yypParser,yyact,yygoto,&yygotominor);
    }
  }else{
    assert( yyact == YYNSTATE + YYNRULE + 1 );
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  ParseARG_FETCH;
#define TOKEN (yyminor.yy0)
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ParseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ParseTOKENTYPE yyminor       /* The value for the token */
  ParseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  int yyact;            /* The parser action. */
  int yyendofinput;     /* True if we are at the end of input */
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  /* (re)initialize the parser, if necessary */
  yypParser = (yyParser*)yyp;
  if( yypParser->yyidx<0 ){
#if YYSTACKDEPTH<=0
    if( yypParser->yystksz <=0 ){
      /*memset(&yyminorunion, 0, sizeof(yyminorunion));*/
      yyminorunion = yyzerominor;
      yyStackOverflow(yypParser, &yyminorunion);
      return;
    }
#endif
    yypParser->yyidx = 0;
    yypParser->yyerrcnt = -1;
    yypParser->yystack[0].stateno = 0;
    yypParser->yystack[0].major = 0;
  }
  yyminorunion.yy0 = yyminor;
  yyendofinput = (yymajor==0);
  ParseARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput %s\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact<YYNSTATE ){
      assert( !yyendofinput );  /* Impossible to shift the $ token */
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->yyerrcnt--;
      yymajor = YYNOCODE;
    }else if( yyact < YYNSTATE + YYNRULE ){
      yy_reduce(yypParser,yyact-YYNSTATE);
    }else{
      assert( yyact == YY_ERROR_ACTION );
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yymx = yypParser->yystack[yypParser->yyidx].major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor,&yyminorunion);
        yymajor = YYNOCODE;
      }else{
         while(
          yypParser->yyidx >= 0 &&
          yymx != YYERRORSYMBOL &&
          (yyact = yy_find_reduce_action(
                        yypParser->yystack[yypParser->yyidx].stateno,
                        YYERRORSYMBOL)) >= YYNSTATE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yyidx < 0 || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          YYMINORTYPE u2;
          u2.YYERRSYMDT = 0;
          yy_shift(yypParser,yyact,YYERRORSYMBOL,&u2);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor,yyminorunion);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      yymajor = YYNOCODE;
      
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yyidx>=0 );
  return;
}
