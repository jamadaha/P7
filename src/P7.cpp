#include <iostream>

#include "Config/Config.hh"
#include "CommonInterface/CommonInterface.hh"
#include "RunReport/RunReport.hh"
#include "RunReport/CompareReport.hh"

using namespace std;

int main(int argc, char** argv){
	std::vector<PDDLActionInstance*> actions;
    // predicates:
    // (on ?x ?y)
    // (ontable ?x)
    // (clear ?x)
    // (handempty)
    // (holding ?x)

    // example macro, not necessarily a good one
    // actions: pickup 0, stack 0 on 1, pickup 2
    PDDLAction _act1 = PDDLAction(
        "pickup",
        std::vector<std::string> {"?x"},
        // (clear ?x) (ontable ?x) (handempty)
        std::vector<PDDLLiteral> {PDDLLiteral(3, std::vector<unsigned int> {0}, true), PDDLLiteral(2, std::vector<unsigned int> {0}, true), PDDLLiteral(4, std::vector<unsigned int> {}, true)},
        // (not (ontable ?x)) (not (clear ?x)) (not (handempty)) (holding ?x)))
        std::vector<PDDLLiteral> {PDDLLiteral(2, std::vector<unsigned int> {0}, false), PDDLLiteral(3, std::vector<unsigned int> {0}, false), PDDLLiteral(4, std::vector<unsigned int> {}, false), PDDLLiteral(5, std::vector<unsigned int> {0}, true)}
    );
    PDDLAction _act2 = PDDLAction(
        "stack",
        std::vector<std::string> {"?x", "?y"},
        // (holding ?x) (clear ?y)
        std::vector<PDDLLiteral> {PDDLLiteral(5, std::vector<unsigned int> {0}, true), PDDLLiteral(3, std::vector<unsigned int> {1}, true)},
        // (not (holding ?x)) (not (clear ?y)) (clear ?x) (handempty) (on ?x ?y)))
        std::vector<PDDLLiteral> {PDDLLiteral(5, std::vector<unsigned int> {0}, false), PDDLLiteral(3, std::vector<unsigned int> {1}, false), PDDLLiteral(3, std::vector<unsigned int> {0}, true), PDDLLiteral(4, std::vector<unsigned int> {}, true), PDDLLiteral(1, std::vector<unsigned int> {0, 1}, true)}
    );
	PDDLAction _useless = PDDLAction(
		"putdown",
		std::vector<std::string> {"?x"},
		//:precondition (and (holding ?ob))
		std::vector<PDDLLiteral> {PDDLLiteral(5, std::vector<unsigned int> {0}, true)},
		//  :effect (and (clear ?ob) (arm-empty) (on-table ?ob) (not (holding ?ob))))
		std::vector<PDDLLiteral> {PDDLLiteral(1, std::vector<unsigned int> {0}, true), PDDLLiteral(3, std::vector<unsigned int> {1}, true), PDDLLiteral(4, std::vector<unsigned int> {1}, false)}
	);

    PDDLActionInstance act1     = PDDLActionInstance(&_act1, std::vector<unsigned int> {0});
    PDDLActionInstance act2     = PDDLActionInstance(&_act2, std::vector<unsigned int> {0, 1});
	PDDLActionInstance useless1 = PDDLActionInstance(&_act1, std::vector<unsigned int> {1});
	PDDLActionInstance useless2 = PDDLActionInstance(&_useless, std::vector<unsigned int> {1});
    PDDLActionInstance act3     = PDDLActionInstance(&_act1, std::vector<unsigned int> {2});

    actions.push_back(&act1);
    actions.push_back(&act2);
	actions.push_back(&useless1);
	actions.push_back(&useless2);
    actions.push_back(&act3);

    // Generate macro
    MacroGenerator macroGenerator = MacroGenerator();
    Macro m = macroGenerator.GenerateMacro(&actions);

	cout << "Name: " << m.name << endl;
	for (auto inst : m.path){
		for (auto obj : inst.objects){
			cout << "Object: " << obj << endl;
		}
	}
}