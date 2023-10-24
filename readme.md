# A Compiler for English-Like Language+

## Steps to Run

```
$ chmod +x build.sh
$ ./build.sh
$ ./parser input.txt
```

- The shell script compiles the source code and outputs an executable `parser`
- `parser` then can be run against the stream of characters inside `input.txt`.

## Project Structure

### analyzer

- Contains `lexer.l` and `parser.y` files.
- The `parser.y` file contains the grammar in BNF notation where the given stream of characters in `input.txt` is verified against.
- The lexer returns the type of token in the input file to the parser.
- The parser and the lexer have a shared variable, `yylval` which holds the associated value of a particular token. It can be as simple as an integer or an index pointing to the symbol table.

### symbol_table

- Contains implementation of symbol table and its associated functions.
- The index in the symbol table for a particular token is determined by running the token's name through a hash function.
- Hash collisions are handled by linear probing.

### AST (Abstract Syntax Tree)

- Contains blueprints for different types of nodes (`VERB`, `NOUN`, `ADWORD`).
- Functions for constructing nodes to aid in building the AST.

### graph

- Implementation for drawing the AST.
- Given the root-node of the AST, a neat visualization of the AST is printed on the terminal.
- This is a modified version of the [source code](https://www.epaperpress.com/lexandyacc/calcg.html) by Frank Thomas Braun.

## What is happening?

- The lexer can recognize and return these 7 types of lexemes.
  1. `NOUNS` - Words starting with an uppercase letter and without numbers.
  2. `VERBS` - Words containing at least one number.
  3. `ADWORDS` - Lowercase alphabet words.
  4. `PUNCTUATIONS` - ., ?, !
  5. `NUMBERS` - Numerical characters only.
  6. `PREPOSITIONS` - Words starting with '@'.

- If a lexeme matches any of the above 7, it is put into the symbol table.

- The grammar recognized by the parser is 
  1. `NOUN VERB NOUN PUNCTUATION` - Second `NOUN` is optional.
  2. `ADWORD NOUN ADWORD VERB ADWORD NOUN PUNCTUATION` - All `ADWORDS` are optional.

- The parser generates an LALR parser, which tries to make sense of the stream of characters in the input file to match the grammar described in BNF form.

- There is an on-the-fly generation of syntax tree nodes, and if everything is correct, the root node is created finally.

- The root node is passed to the graph-code, which visualizes the structure of it by printing it on the terminal.

## Example

### input.txt

```
may The force b3e with You .
Good th1ng4 take Time !
why Bats m4ast3r wayne?
```

### output

```
$ ./parser input.txt

# AST 1


                  VERB(b3e)
                   |
          |------------------|
          |                  |
       ADWORD(force)        NOUN(You)
          |                  |
         |-                  |
         |                   |
        NOUN(The)          ADWORD(with)
         |
         |
         |
       ADWORD(may)

# AST 2


               VERB(th1ng4)
                  |
        |-----------------|
        |                 |
       NOUN(Good)        NOUN(Time)
                          |
                          |
                          |
                        ADWORD(take)

# AST 3


                VERB(m4ast3r)
                   |
         |------------------|
         |                  |
       NOUN(Bats)        ADWORD(wayne)
         |
         |
         |
       ADWORD(why)

# Symbol Table

+-----------------+-----------------+
| token_name      | lexeme          |
+-----------------+-----------------+
| NOUN            | Bats            |
| ADWORD          | with            |
| PUNCTUATION     | ?               |
| VERB            | b3e             |
| ADWORD          | wayne           |
| ADWORD          | force           |
| VERB            | m4ast3r         |
| VERB            | th1ng4          |
| NOUN            | You             |
| NOUN            | The             |
| PUNCTUATION     | !               |
| ADWORD          | why             |
| NOUN            | Good            |
| NOUN            | Time            |
| ADWORD          | take            |
| ADWORD          | may             |
| PUNCTUATION     | .               |
+-----------------+-----------------+
```

- As observed above the input can contain multiple space separated sentences and an AST is generated for each sentence.

## Example

### input.txt

```
may the force b3e with You .
```

### output

```
$ ./parser input.txt
Parse Failed
```

- This one contains two adwords together.

## Challenges Faced

- Writing the grammar was not hard, but it required prior knowledge of Lex and Yacc, handling all cases, and adequately including all the headers.
- Designing the AST node blueprints was challenging; structurally, the nodes in the AST are of all different sub-types linked together.
- The source code for drawing the graph was originally written for a different kind of node structure, so it took a lot of work to debug. It was hard to pinpoint precisely in which module there was a bug, so I had to test all the modules while switching off some. It also required fine-tuning some parameters to print a neatly spaced structure of the AST.