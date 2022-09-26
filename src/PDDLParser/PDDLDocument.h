#ifndef PPDDocument_HH_
#define PPDDocument_HH_

#include "domain.hh"
#include "problem.hh"

struct PDDLDocument {
public:
    Domain* domain;
    Problem* problem;

    PDDLDocument(Domain* domain, Problem* problem) : domain(domain), problem(problem) {}
};

#endif