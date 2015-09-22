#include <stdio.h>

#pragma once

typedef enum type {
  LABEL,
  INSTRUCTION,
  COMMENT,
  DIRECTIVE,
  ERROR
} inputType;
