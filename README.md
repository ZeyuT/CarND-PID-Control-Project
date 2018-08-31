# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Purpose
The purpose of the project is to build PID controllers for the vehicle in the simulator. And tune the PID hyperparameters until the the vehicle is able to drive successfully around the track.
The simulator will provide the cross track error (CTE) and the velocity (mph) in order to compute the appropriate steering angle. And PID controllers will output the steering angle and throttle value, which will then be used to drive the vehicle in the track. 

## Reflection
* **Describe the effect each of the P, I, D components had in your implementation**

The P means proportional. It controls how intensely the vehicle responds to CTE. If the CTE is the same, the vehicle with smaller Kp will steer or deaccelerate slighter.

The I means integral. I error is the total error, and is actually the steady state error. I component in PID reduces the bias in the control input to the vehicle, which prevent the vehicle from driving along the center line. An example of the bias is steering drift.

The D means differential. D component reduces overshoot and oscillations.

* **Describe how the final hyperparameters were chosen**

_tuning the PID controller for steering angle_

I set the throttle value to 0.5. Then I manually modified hyperparameters in the PID controller until the vehicle could run roughly along the track without going outside the track. Then I used "twiddle" method to automatically optimize hyperparameters in the PID controller. Since I set the method to optimize one hyperparameters once every 1100 steps(100 steps to converge and 1000 steps to measure errors), which was pretty long distance, it was neccessary to manually modified the PID controller and let the vehicle be able to run along the track automatically. The initial value to be changed on Kp, Ki and Kd was one tenth of its own value. And I kept running the "twiddle" optimization until all of Kp, Kd and Ki did not change in continuous 9 loops, which means each of these hpyerparameters did not changes during the last 3 chances. The final {Kp, Ki, Kd} in the steering controller is:{0.151635, 0.000099, 6.6355}

_tuning the PID controller for throttle value_

After the PID controller for steering angle being fine tuned, I set a PD controller for throttle value. Since the total error did not matter much on the longitudinal speed control, the I component was abundoned. Besides, since the direction of CTE made no difference of letting the vehicle slow down, the input to the PD controller was the absolute value of CTE. Then I ran the same "twiddle" optimization and the same critiria to tune hyperparameters. The final {Kp, Ki, Kd} in the throttle controller is:{0.3597, 0, 0.1199}.

The method to tune the two PID controllers was not perfect but good enough to get appropriate hyperparameters. Because of the sequence of tuning the two controllers, the first controller to be tuned, which was for steering angle, took the major effect on driving the vehicle along the track. The controller for throttle value just made the vehicle run smoothly and made it possible to increase the reference speed. In this case, I set the reference throttle value to be 0.6.

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).

