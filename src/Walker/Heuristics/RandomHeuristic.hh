#ifndef RandomHeuristic_HH
#define RandomHeuristic_HH

#include "BaseHeuristic.hh"

class RandomHeuristic : public BaseHeuristic {
public:
	RandomHeuristic() : BaseHeuristic(nullptr, nullptr){};

	inline PDDL::ActionInstance* NextChoice(PDDL::State * state, std::vector<PDDL::ActionInstance> *choices) override {
		return &choices->at(rand() % choices->size());
	}

	inline int Eval(const PDDL::State *state) const override {
		return rand();
	};
private:
	void Reset() override {}
};

#endif
