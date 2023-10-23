if [ -d "temp" ]; then
  rm -r temp
fi
mkdir temp

flex -o temp/lex.yy.c analyzer/lexer.l
yacc -o temp/y.tab.c -d analyzer/parser.y
gcc temp/lex.yy.c temp/y.tab.c AST/AST.c symbol_table/symbol_table.c graph/graph.c -o parser

exit 0
