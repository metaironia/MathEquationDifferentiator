#include "differentiator_func.h"

#include "tree/tree_func.h"

int main (const int argc, const char *argv[]) {

    Tree math_equation = {};
    TreeCtor (&math_equation);

    if (TreeMathEquationRead (&math_equation, argc, argv) == MATH_EQUATION_ERROR)   //this func non exist
        return -1;



    return 0;
}


