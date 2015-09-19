#include <stdio.h>

#ifndef typeEnum.h
#define typeEnum.h

typedef enum type {
  LABEL,
  INSTRUCTION,
  COMMENT,
  DIRECTIVE,
  ERROR
} type;

#endif
