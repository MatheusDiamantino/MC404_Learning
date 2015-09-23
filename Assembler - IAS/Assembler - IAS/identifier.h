#include <stdio.h>
#include "typeEnum.h"
#include <stdlib.h>

#include "typeEnum.h"

#pragma once

void storeLabel(char input[]);
void identifyDirective(char input[]);
void identifyInstruction(char input[]);
void reader(char input[]);
inputType identifyType (char input[]);
bool containsChar (char input[], char c);
bool isLabel (char input[]);
bool isDirective (char input[]);
bool isComment (char input[]);
