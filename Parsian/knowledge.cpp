#include "stdafx.h"
#include "knowledge.h"
#include "base.h"

double ballPossession(const CWorldModel* _wm) {
    if (_wm->getBall().pos.x < 0) return 0;
    else return 1;
}

PID v[ROBOT_COUNT], w[ROBOT_COUNT];
void getRobotWheelPID(const CRobot& r, double _w, double vel_tan, double& right_wheel, double& left_wheel) {
	v[r.id].kp = 10; v[r.id].ki = 0; v[r.id].kd = 0.2;
	vel_tan += vel_tan / 10;
	v[r.id].run(vel_tan - (r.vel.th().isWithin(r.th + 10, r.th - 10) ? -1 : -1)*r.vel.length());

	w[r.id].kp = 1; w[r.id].ki = 0; w[r.id].kd = 0.2;
	_w += _w;
	w[r.id].run(_w - r.w);
	double w_o = (_w != 0 ) ? w[r.id].lastOut : 0;
	double v_o = (vel_tan != 0) ? v[r.id].lastOut : 0;
	getRobotWheel(w_o, v_o, right_wheel, left_wheel);
}

void getRobotWheel(double w, double vel_tan, double& right_wheel, double& left_wheel) {

	//solve vel_tan
	//wheel =  a*x
	double a{ 2.6952341387627644e+001 };
	double right_vel_tan{ a * vel_tan };
	double left_vel_tan{ a * vel_tan };
	//solve w
	//wheel = a*w
	double a1{ 1.8759045880902410 };
	double right_vel_w{ a1*w };
	double left_vel_w{ -a1 * w };
	right_wheel = right_vel_tan + right_vel_w;
	left_wheel = left_vel_tan + left_vel_w;
	if (right_wheel >= left_wheel && right_wheel > 150) {
		double k = 150 / right_wheel;
		right_wheel = 150;
		left_wheel *= k;
	}
	else if (right_wheel < left_wheel && left_wheel > 150) {
		double k = 150 / left_wheel;
		left_wheel = 150;
		right_wheel *= k;
	}
}
