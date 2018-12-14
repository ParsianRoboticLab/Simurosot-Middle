#ifndef _PID_HEADER_
#define _PID_HEADER_

class PID {
public:
    PID(double _kp = 0.0, double _ki = 0.0, double _kd = 0.0, double _maxSum = 10.0, double _minErr = 0.1) : kp(_kp), ki(_ki), kd(_kd), maxSum(_maxSum), minErr(_minErr) {
		sum = 0;
		last = 0;
    }

	~PID() {};

    double run(double err) {
        if(abs(err) < minErr) sum = 0;
        else if( sum <= maxSum || maxSum == 0) sum += err;
        else sum = maxSum;
        lastOut = (kp * err) + (ki * sum) + (kd * (err - last));
		last = err;
        return lastOut;
    }
    double lastOut;
	double kp, ki, kd;
private:

    double abs(double v) {return (v > 0) ? v : -v;}
    double sum;
    double last;
    const double maxSum, minErr;

};

#endif // _PID_HEADER_