# lexing-tool

A drop-in lexer for C


## Usage

```
$ gcc main.c src/lexer.c

$ ./a input.c
``` 
where input.c will be the file you want to be tokenized


## Example

```
// this is an example
int x = 10;
// output
-> ('int', 'INT')
-> ('x', 'IDENT')
-> ('=', 'ASSIGN')
-> ('10', 'NUM')
-> (';', 'SEMICOLON')
```
