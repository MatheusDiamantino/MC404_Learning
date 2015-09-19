#include <stdio.h>
#include "typeEnum.h"
#include <stdlib.h>

#include "typeEnum.h"

#ifndef reader.h
#define reader.h

type identifyType (char input[]);
bool containsChar (char input[], char c);
bool isLabel (char input[]);
bool isDirective (char input[]);
bool isComment (char input[]);

#endif
