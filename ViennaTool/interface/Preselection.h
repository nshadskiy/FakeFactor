#include "ViennaTool/interface/TNtupleAnalyzer.h"

#include <iostream>
#include <string>


void compressFile(TString fname);

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