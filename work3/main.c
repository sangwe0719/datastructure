#include <stdio.h>
#include "match.h"
#include "postfix.h"

int main() {
    match_parentheses("((((a+b)*c+d-e)/(f+g)-(h+j)*(k-l))/(m-n))");
    printf("\n");
    match_parentheses("(a-b*c)+d-(e-(f-g)/h)/(i*j)-k");
    printf("\n");
    infix_to_postfix("a + b - c * d / e + f");
    infix_to_postfix("(a + b) * (c - d) / e + f"); 
    infix_to_postfix("a * b + c - d % e + f");
    infix_to_postfix("a + b - c + d - e + f");
    infix_to_postfix("((a + b) * c + d) / e - f");
    return 0;
}
