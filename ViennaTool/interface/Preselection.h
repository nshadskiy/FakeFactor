#include "ViennaTool/interface/TNtupleAnalyzer.h"

#include <iostream>
#include <string>
#include "TString.h"


void compressFile(TString fname);
void createMergedTrees();

class SelectionClass
{
  public:
    TString filename;
    TString selection;
    int bitmask;

    SelectionClass(TString filename, TString selection, int bitmask)
    {
        this->filename = filename;
        this->selection = selection;
        this->bitmask = bitmask;
    }
};