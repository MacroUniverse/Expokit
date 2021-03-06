#include "zhexpv.h"
#include "zgexpv.h"
#include "SLISC/disp.h"
using std::cout; using std::endl;

// vector classes
using slisc::VecDoub;
using slisc::VecComp;
using slisc::VecInt;
using slisc::linspace; // linearly spaced sequence
using slisc::norm_inf; // infinite norm
using slisc::disp; // print vectors

void test_EXPV()
{
	// === params ===========
	Int n = 40; // matrix size
	Int m = 20; // # krylov basis
	Doub t = 1; // time
	Doub tol = 0.; // error tol
	// ======================

	Int i;
	McooComp A;
	A.resize(n + 2*(n - 1) + 2*(n-5));
	A.resize(n, n);
	
	for (i = 0; i < n; ++i) {
		A.push(1., i, i);
	}
	for (i = 0; i < n - 1; ++i) {
		A.push(0.6, i, i + 1);
		A.push(0.6, i + 1, i);
	}
	for (i = 0; i < n - 5; ++i) {
		A.push(0.4, i, i + 5);
		A.push(0.4, i + 5, i);
	}

	VecComp v(n), w(n, 0.);
	linspace(v, 1, n);
	
	Doub anorm = norm_inf(A);

	Int lwsp = MAX(10, SQR(n*(m + 2) + 5 * (m + 2)) + 7);
	VecComp wsp(lwsp);
	Int liwsp = MAX(m + 2, 7);
	VecInt iwsp(liwsp);
	Int itrace = 1;
	Int iflag;
	ZHEXPV(n, m, t, v.ptr(), w.ptr(), tol, anorm,
		wsp.ptr(), lwsp, iwsp.ptr(), liwsp, A, itrace, iflag);
	disp(w, 16);
	w = 0.;
	ZGEXPV(n, m, t, v.ptr(), w.ptr(), tol, anorm,
		wsp.ptr(), lwsp, iwsp.ptr(), liwsp, A, itrace, iflag);
	disp(w, 16);
}

int main()
{
	test_EXPV();
}
