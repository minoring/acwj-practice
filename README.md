## BNF Grammar

```
primary_expression:
       identifier
     | T_INTLIT
     | T_STRLIT
     | '(' expression ')'
     ;

postfix_expression:
       primary_expression
     | postfix_expression '[' expression ']'
     | postfix_expression '(' expression ')'
     | postfix_expression '++'
     | postfix_expression '--'
     ;

prefix_expression:
       postfix_expression
     | '++' prefix_expression
     | '--' prefix_expression
     | prefix_operator prefix_expression
     ;

prefix_operator:
       '&'
     | '*'
     | '-'
     | '~'
     | '!'
     ;

expression: additive_expression
     ;

additive_expression:
       multiplicative_expression
     | additive_expression '+' multiplicative_expression
     | additive_expression '-' multiplicative_expression
     ;

multiplicative_expression:
       prefix_expression
     | multiplicative_expression '*' prefix_expression
     | multiplicative_expression '/' prefix_expression
     | multiplicative_expression '%' prefix_expression
     ;

expression_list:
       expression
     | expression ',' expression_list
     ;

number: T_INTLIT
     ;

statement: print_statement
     |     declaration
     |     assignment_statement
     |     if_statement
     |     while_statement
     |     for_statement
     |     return statement
     ;

print_statement: 'print' expression ';'
     ;

assignment_statement: opt_pointer identifier '=' expression ';'
     ;

if_statement: if_head
     |        if_head 'else' compound_statement
     ;

if_head: 'if' '(' true_false_expression ')' compound_statement
     ;

statements: statement
     |      statement statements
     ;

compound_statement: '{' '}' // empty, i.e. no statement
     |      '{' statements '}'
     ;

while_statement: 'while' '(' true_false_expression ')' compound_statement
     ;

for_statement: 'for' '(' preop_statement ';'
                         true_false_expression ';'
                         postop_statement ')' compound_statement
     ;

preop_statement: statement
     ;

postop_statement: statement
     ;

function_call: identifier '(' expression ')'
     ;

return_statement: 'return' '(' expression ')'
     ;

global_declarations: global_declarations
     | global_declaration global_declarations
     ;

global_declaration: function_declaration | var_declaration
     ;

function_declaration: type identifier '(' ')' compound_statement
     ;

var_declaration: type identifier_list ';'
     | type identifier '[' P_INTLIT ']' ';'
     ;

type: type_keyword opt_pointer
     ;

type_keyword: 'void' | 'char' | 'int' | 'long'
     ;

opt_pointer: <empty> | '*' opt_pointer
     ;

identifier_list: identifier | identifier ',' identifier_list
     ;

identifier: T_IDENT
     ;
```
