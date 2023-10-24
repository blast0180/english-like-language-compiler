# A Compiler for English-Like Language+

## Steps to Run

```
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
- The parser and the lexer have a shared variable `yylval` which holds the associated value of a particular token, it can be as simple as an integer or an index poining to the symbol table.

### symbol_table

- Contains implementation of symbol table and its associated functions.
- The index in the symbol table for a particular token is determined by running the name of the token through a hash function.
- Hash collisions are handled by linear probing.

### AST (Abstract Syntax Tree)

- Contains blueprints for different types of nodes (VERB, NOUN, ADWORD).
- Functions for constructing nodes to aid in building the AST.

### graph

- Implemetation for drawing the AST.
- Given the root-node of the AST, a neat visualization of the AST is printed on the terminal.
- This is a modifed version of the [source code](https://www.epaperpress.com/lexandyacc/calcg.html) by Frank Thomas Braun.

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