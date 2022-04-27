#include "parseCommand.h"

ParseResult parse_command(InputBuffer *input_buffer, Statement *statement)
{
  if (input_buffer->buffer[0] == '.'){
      return parse_meta_command(input_buffer, statement);
  }
  if (strncmp(input_buffer->buffer, "insert", 6) == 0)
  {
    return parse_insert(input_buffer, statement);
  }
  if (strcmp(input_buffer->buffer, "select") == 0)
  {
    statement->type = STATEMENT_SELECT;
    return PARSE_SUCCESS;
  }

  return PARSE_UNRECOGNIZED_STATEMENT;
}

ParseResult parse_insert(InputBuffer *input_buffer, Statement *statement)
{
  statement->type = STATEMENT_INSERT;
  char *keyword = strtok(input_buffer->buffer, " ");
  char *id_string = strtok(NULL, " ");
  char *username = strtok(NULL, " ");
  char *email = strtok(NULL, " ");

  if (id_string == NULL || username == NULL || email == NULL)
  {
    return PARSE_SYNTAX_ERROR;
  }

  int id = atoi(id_string);
  if (id < 0)
  {
    return PARSE_NEGATIVE_ID;
  }
  if (strlen(username) > COLUMN_USERNAME_SIZE)
  {
    return PARSE_STRING_TOO_LONG;
  }
  if (strlen(email) > COLUMN_EMAIL_SIZE)
  {
    return PARSE_STRING_TOO_LONG;
  }

  statement->row_to_insert.id = id;
  strcpy(statement->row_to_insert.username, username);
  strcpy(statement->row_to_insert.email, email);
  return PARSE_SUCCESS;
}

ParseResult parse_meta_command(InputBuffer *input_buffer, Statement *statement){
  
    if (strcmp(input_buffer->buffer, ".exit") == 0)
    {
        statement->type = STATEMENT_EXIT;
        return PARSE_SUCCESS;
     
    }
    if(strcmp(input_buffer->buffer, ".tree") == 0)
    {
      statement->type = STATEMENT_PRINT_TREE;
      return PARSE_SUCCESS;
    }
    return PARSE_UNRECOGNIZED_STATEMENT;
}