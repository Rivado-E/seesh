#include "ctype.h"
#include "stdio.h"
#include "string.h"

typedef enum {
  Token_IF,
  Token_Identifier,
  Token_Keyword,
  Token_Number,
  Token_String,
  Token_Operator,
  Token_Separator,    // e.g., ;
  Token_Redirect_In,  // e.g., >, <, >>
  Token_Redirect_Out, // e.g., >, <, >>
  Token_Pipe,         // e.g., |
  Token_LParen,       // e.g., (, )
  Token_RParen,       // e.g., (, )
  Token_Quote,        // e.g., single or double quotes
  Token_LogicalAnd,   // e.g., &&
  Token_LogicalOr,    // e.g., ||
  Token_Else,
  Token_While,
  Token_For,
  Token_Background, // e.g., &
  Token_Exit,
  Token_Comment, // e.g., #
  Token_Equal,   // e.g., =
  Token_End,     // To mark the end of the tokens
  Token_Unknown
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

void next_token(Lexer *l, Token *t) {
  int rest = l->cursor >= l->len;
  int start = l->cursor;

  if (rest <= 0) {
    t->type = Token_End;
    return;
  }

  if (isspace(l->content[l->cursor])) {
    consume_whitespace(l);
    start = l->cursor;
  }

  if (rest >= 3) {
    if ((strncmp(l->content + l->cursor, "for", 3) == 0)) {
      t->type = Token_For;

    } else if ((strncmp(l->content + l->cursor, "for", 3) == 0)) {
      t->type = Token_For;

    } else if ((strncmp(l->content + l->cursor, "for", 3) == 0)) {
      t->type = Token_For;

    } else if ((strncmp(l->content + l->cursor, "for", 3) == 0)) {
      t->type = Token_For;
    }
  }

  if (!t->type && rest >= 2) {
    if ((strncmp(l->content + l->cursor, ">>", 2) == 0)) {
      t->type = Token_For;

    } else if ((strncmp(l->content + l->cursor, "<<", 2) == 0)) {
      t->type = Token_For;

    } else if ((strncmp(l->content + l->cursor, "||", 2) == 0)) {
      t->type = Token_For;

    } else if ((strncmp(l->content + l->cursor, "&&", 2) == 0)) {
      t->type = Token_For;
    }
  }

  if (!t->type && rest >= 1) {
    if (l->content[l->cursor] == '|') {
      t->type = Token_Pipe;

    } else if (l->content[l->cursor] == '&') {
      t->type = Token_For;

    } else if (l->content[l->cursor] == '(') {
      t->type = Token_For;

    } else if (l->content[l->cursor] == ')') {
      t->type = Token_For;

    } else if (l->content[l->cursor] == '<') {
      t->type = Token_For;

    } else if (l->content[l->cursor] == '>') {
      t->type = Token_For;

    } else if (l->content[l->cursor] == '=') {
      t->type = Token_For;

    } else if (l->content[l->cursor] == '#') {
      consume_comment(l, t);

    } else if (l->content[l->cursor] == '"') {
      consume_string(l, t, '\'');

    } else if (l->content[l->cursor] == '\'') {
      consume_string(l, t, '"');
    }
  }
  if (!t->type) {
    t->type = Token_Unknown;
  }

  return;
}

void print_debug(Token *tokens) {}

int main(int argc, char **argv) {

  char *test = "'echo sam'";
  printf("test: %s\n", test);

  return 0;
}
