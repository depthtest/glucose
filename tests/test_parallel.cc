#include "parallel/MultiSolvers.h"
#include "mtl/Vec.h"
#include "core/SolverTypes.h"
#include <vector>
#include <cstdio>

template <typename Solver>
void addClause(Solver *solver, const std::vector<int>& clause) {
	Glucose::vec<Glucose::Lit> cl(clause.size());
	for (int i = 0; i < clause.size(); ++i) {
		cl[i] = clause[i] > 0 ? Glucose::mkLit(clause[i]-1, false) : Glucose::mkLit(-clause[i]-1, true);
		while (Glucose::var(cl[i]) >= solver->nVars()) {
			solver->newVar();
		}
	}
	solver->addClause(cl);
}

int main(int argc, char** argv) {
	Glucose::MultiSolvers solver;

	addClause(&solver, std::vector<int>({ 1,2,3 }));
	addClause(&solver, std::vector<int>({ -1,-2 }));
	addClause(&solver, std::vector<int>({ -1,-3 }));
	addClause(&solver, std::vector<int>({ -2,-3 }));

	auto is_SAT = solver.solve();
	printf("is SAT: %d\n", is_SAT==l_True);
	if (is_SAT==l_True) {
		for (int i = 0; i < solver.model.size(); ++i) {
			if (solver.model[i] != l_Undef) {
				auto is_F = toInt(solver.model[i]);
				printf("%d ", (1 - is_F) * (i + 1) + (is_F) * (-i - 1));
			}
		}
	}
	printf("\n");

	return 0;
}