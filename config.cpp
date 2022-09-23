#include "config.h"

int main(){
    Options o = {.search = Astar, .heuristic = Lmcut};
    Config c = Config ("./", o);
}