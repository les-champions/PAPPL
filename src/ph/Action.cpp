#include <iostream>
#include <boost/lexical_cast.hpp>
#include "Action.h"


Action::Action (ProcessPtr source_, ProcessPtr target_, ProcessPtr result_, const bool& infiniteRate_, const double& r_, const int& sa_)
    : result(result_), infiniteRate(infiniteRate_), r(r_), sa(sa_) {
    transitions = boost::make_shared<Transition>(source_,target_);
}


// getters
ProcessPtr Action::getSource() {
    return transitions->getSource();
}
ProcessPtr Action::getTarget() {
    return transitions->getTarget();
}
ProcessPtr Action::getResult() {
    return result;
}

// output for DOT file
string Action::toDotString (void) {
    string res;

    res += 				transitions->getSource()->getDotName()
                        + " -> " + 	transitions->getTarget()->getDotName()
                        + ";\n";
    res += 				transitions->getTarget()->getDotName()
                        + " -> " + 	result->getDotName()
                        + ";\n";

    return res;
}


// output for PH file
string Action::toString (void) {

    return 		transitions->getSource()->getSort()->getName()
                +	" "
                +	boost::lexical_cast<string>(transitions->getSource()->getNumber())
                + 	" -> "
                + 	transitions->getTarget()->getSort()->getName()
                +	" "
                +	 boost::lexical_cast<string>(transitions->getTarget()->getNumber())
                +	" "
                + 	 boost::lexical_cast<string>(result->getNumber())
                +	" @"
                +	(infiniteRate ?
                     "Inf"
                     :
                     (r == (int) r) ?
                     boost::lexical_cast<string>(r) + "."
                     :
                     boost::lexical_cast<string>(r)
                  )
                +	"~"
                +	 boost::lexical_cast<string>(sa)
                +	"\n"
                ;
}
