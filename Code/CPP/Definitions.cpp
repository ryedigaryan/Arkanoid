//
// Created by ryedigaryan on 3/10/2018.
//

#include "Definitions.h"

void fail(const string& method)
{
    cout << "UNEXPECTED ERROR IN " << method << endl;
    exit(666666666);
}