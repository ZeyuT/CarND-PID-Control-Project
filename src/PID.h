#ifndef PID_H
#define PID_H
#include <vector>

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 
  std::vector<double> p;

  /*
  * Twiddling parameters
  */
  std::vector<double> dp;
  int it; // times of iterations
  double tol; //tolerance of sum of dp.
  double total_error;
  double best_error;
  int it_converge;	//iterations before it_converge will not be counted error in each twiddle loop.
  int it_eval;	//it_eval iterations after it_converge will be counted error in each twiddle loop.
  int index; // index for extract elements from p and dp.
  bool flag_twiddle;
  bool flag_add;
  bool flag_subtract;
  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  //double TotalError(double cte);
};

#endif /* PID_H */
