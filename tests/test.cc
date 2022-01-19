#include "simp/SimpSolver.h"
#include "mtl/Vec.h"
#include "core/SolverTypes.h"
#include <vector>
#include <cstdio>

void addClause(Glucose::Solver *solver, const std::vector<int>& clause) {
	Glucose::vec<Glucose::Lit> cl(clause.size());
	for (int i = 0; i < clause.size(); ++i) {
		cl[i] = clause[i] > 0 ? Glucose::mkLit(clause[i]-1, false) : Glucose::mkLit(-clause[i]-1, true);
		while (Glucose::var(cl[i]) >= solver->nVars()) {
			solver->newVar();
		}
	}
	solver->addClause(cl);
}

void getVecOfLits(Glucose::vec<Glucose::Lit> &cl, const std::vector<int>& clause) {
	cl.clear();
	cl.growTo(clause.size());
	for (int i = 0; i < clause.size(); ++i) {
		cl[i] = clause[i] > 0 ? Glucose::mkLit(clause[i] - 1, false) : Glucose::mkLit(-clause[i] - 1, true);
	}
}

int main(int argc, char** argv) {
	auto solver = Glucose::SimpSolver();

	addClause(&solver, std::vector<int>({ 1,2,3 }));
	addClause(&solver, std::vector<int>({ -1,-2 }));
	addClause(&solver, std::vector<int>({ -1,-3 }));
	addClause(&solver, std::vector<int>({ -2,-3 }));

	Glucose::vec<Glucose::Lit> cl;
	getVecOfLits(cl, std::vector<int>({ 1,2,3 }));

	auto is_SAT = solver.solve(cl);
	printf("is SAT: %d\n", int(is_SAT));
	if (is_SAT) {
		for (int i = 0; i < solver.model.size(); ++i) {
			if (solver.model[i] != l_Undef) {
				auto is_F = toInt(solver.model[i]);
				printf("%d ", (1 - is_F) * (i + 1) + (is_F) * (-i - 1));
			}
		}
	} else {
		for (int i = 0; i < solver.conflict.size(); ++i) {
			auto vv = (Glucose::var(solver.conflict[i]) + 1) * (int(Glucose::sign(solver.conflict[i])) * 2 - 1);
			printf("%d ", vv);
		}	
	}
	printf("\n");

	return 0;
}