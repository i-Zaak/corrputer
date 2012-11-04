#pragma once
#include "scope.h"

void readIG( FILE *file, IG_s *ig);
void readHG(FILE *file, HG_s *hg);
void readFG(FILE *file, FG_s *fg);
void readData(FILE *file, float* data, DATAindx length);
void printIG(IG_s *ig);
void printHG( HG_s *hg );
void printFG( FG_s *fg );

