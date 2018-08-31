#include "PID.h"
#include <limits>
#include <math.h>
#include <iostream>


using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	p_error = 0;
	i_error = 0;
	d_error = 0;
	p = { Kp, Ki, Kd };

	// Twiddle parameters
	dp = { 0.1 * Kp, 0.1 * Ki, 0.1 * Kd };
	it = 0; // times of iterations
	tol = 0.2; //tolerance of sum of dp.
	total_error = 0;
	best_error = std::numeric_limits<double>::max();
	it_converge = 100;	//iterations before it_converge will not be counted error in each twiddle loop.
	it_eval = 1000;	//it_eval iterations after it_converge will be counted error in each twiddle loop.
	index = 0; // index for extract elements from p and dp.
	flag_twiddle = true;
	flag_add = false;
	flag_subtract = false;
}

void PID::UpdateError(double cte) {
	if (it == 0) {
		p_error = cte;
	}
	d_error = cte - p_error;
	p_error = cte;
	i_error += cte;
	if (it % (it_eval + it_converge) > it_converge) {
		total_error += pow(cte, 2);
	}

	if (flag_twiddle & ((it % (it_eval + it_converge)) == 0)){
		if (!flag_add) {
			p[index] += dp[index];
			flag_add = true;
			it++;
			total_error = 0;
			cout << "added" << endl;
			return;
		}

		if (total_error < best_error) {
			best_error = total_error;
			dp[index] *= 1.1;
			cout << "updated (dp*1.1)" << endl;
		}
		else {
			if (!flag_subtract) {
				p[index] -= 2 * dp[index];
				flag_subtract = true;
				it++;
				total_error = 0;
				cout << "subtracted" << endl;
				return;
			}

			if (total_error < best_error) {
				best_error = total_error;
				dp[index] *= 1.1;
				cout << "updated (dp*1.1)" << endl;
			}
			else {
				p[index] += dp[index];
				dp[index] *= 0.9;
				cout << "updated (dp*0.9)" << endl;
			}
		}
		index = (index + 1) % 3;
		total_error = 0;
		flag_add = false;
		flag_subtract = false; 
		cout << "p = " << p[0]<< " " << p[1] << " " << p[2] << endl;
		cout << "dp = " << dp[0] << " " << dp[1] << " " << dp[2] << endl;

	}

	it++;
	//cout << "iteration: " << it << endl;
	return;
}

//double PID::TotalError() {
//}

