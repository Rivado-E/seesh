#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUILTINS_LEN 6
const char *BUILTINS[] = {"cd", "exit", "echo", "pwd", "env", "set"};

typedef enum {
  Tok_If,
  Tok_Identifier,
  Tok_Keyword,
  Tok_Number,
  Tok_String,
  Tok_Operator,
  Tok_Separator,    // e.g., ;
  Tok_Redirect_In,  // e.g., >, <, >>
  Tok_Redirect_Out, // e.g., >, <, >>
  Tok_Pipe,         // e.g., |
  Tok_LParen,       // e.g., (, )
  Tok_RParen,       // e.g., (, )
  Tok_Quote,        // e.g., single or double quotes
  Tok_And,          // e.g., &&
  Tok_Or,           // e.g., ||
  Tok_Else,
  Tok_While,
  Tok_For,
  Tok_Background, // e.g., &
  Tok_Exit,
  Tok_Comment, // e.g., #
  Tok_Equal,   // e.g., =
  Tok_End,     // To mark the end of the tokens
  Tok_Builtin,
  Tok_Unknown,
} TokenKind;

typedef struct {
  TokenKind type;
  int start;
  int len;
} Token;

typedef struct {
  int cursor;
  int row;
  int col;
  char *content;
  int len;
} Lexer;

void consume_whitespace(Lexer *l) {
  while (isspace(l->content[l->cursor])) {
    if (l->content[l->cursor] == '\n') {
      l->row += 1;
      l->col = 0;
    } else {
      l->col += 1;
    }

    l->cursor += 1;
  }
}

void consume_string(Lexer *l, Token *t, char delimiter) {}
void consume_comment(Lexer *l, Token *t) {}

void consume_builtin(Lexer *l, Token *t, const char *builtin) {
  char *cursor = l->content + l->cursor;

  if (!strcmp(builtin, "echo")) {

    t->start = l->cursor;
    if (*(cursor) == '"') {

      t->start++;
      t->len = strchr(cursor+1, '"') - cursor;

    } else if (*(cursor) == '\'') {
      cursor ++; 
      t->start++;
      t->len = strchr(cursor+1, '\'') - cursor;

    } else {
      char *whitespace = strpbrk(cursor, " \t\n\r\f\v");
      if ((void *)whitespace != NULL) {
        t->len = strpbrk(cursor, " \t\n\r\f\v") - cursor;
      } else {
        t->len = l->len - l->cursor;
      }
    }

    char substring[t->len + 1];
    strncpy(substring, cursor, t->len);
    substring[t->len] =  '\0';
    printf("%s\n", substring);

  } else {
    printf("not implemented\n");
  }
}

void next_token(Lexer *l, Token *t) {
  int rest = l->len - l->cursor;
  int start = l->cursor;
  char *cursor = l->content + l->cursor;

  if (rest <= 0) {
    t->type = Tok_End;
    return;
  }

  if (isspace(l->content[l->cursor])) {
    consume_whitespace(l);
    start = l->cursor;
  }

  if ((void *)strstr(cursor, "&&") == cursor) {
    t->type = Tok_And;
  } else if ((void *)strstr(cursor, "||") == cursor) {
    t->type = Tok_Or;
  } else if ((void *)strstr(cursor, "for") == cursor) {
    t->type = Tok_For;
  } else if ((void *)strstr(cursor, "if") == cursor) {
    t->type = Tok_If;
  } else if ((void *)strstr(cursor, "while") == cursor) {
    t->type = Tok_While;
  } else if (*(cursor) == ';') {
    t->type = Tok_Separator;
  } else if (*(cursor) == '&') {
    t->type = Tok_Background;
  } else if (*(cursor) == '>') {
    t->type = Tok_Redirect_Out;
  } else if (*(cursor) == '<') {
    t->type = Tok_Redirect_In;
  } else if (*(cursor) == '#') {
    t->type = Tok_Redirect_In;
  } else if (*(cursor) == '"') {
    consume_string(l, t, '"');
  } else if (*(cursor) == '\'') {
    consume_string(l, t, '\'');
  } else {
    for (int i = 0; i < BUILTINS_LEN; i++) {
      // printf("debug %s\n", BUILTINS[i]);

      if ((void *)strstr(cursor, BUILTINS[i]) == cursor) {
        t->type = Tok_Builtin;
        l->cursor += 5;
        consume_builtin(l, t, "echo");
      }
    }
  }

  if (!t->type) {
    t->type = Tok_Unknown;
  }

  return;
}

void print_debug(Token *tokens) {}

int main(int argc, char **argv) {

  char *test = "'echo sam'";
  printf("test: %s\n", test);

  Lexer lexer = {0};
  Token token = {0};

  lexer.len = 9;
  lexer.content = "echo 'just because'";

  next_token(&lexer, &token);

  return 0;
}
