class PID {
public:
    PID(double _kp = 0.0, double _ki = 0.0, double _kd = 0.0, double _maxSum = 100.0, double _minErr = 1) : kp(_kp), ki(_ki), kd(_kd), maxSum(_maxSum), minErr(_minErr) {

    }

    ~PID();

    double run(double err) {
        if(abs(err) < minErr) sum = 0;
        else if( sum <= maxSum || maxSum == 0) sum += err;
        else sum = maxSum;
        lastOut = (kp * err) + (ki * sum) + (kd * (err - last));
        return lastOut;
    }
    double lastOut;

private:
    double abs(double v) {return (v > 0) ? v : -v;}

    double kp, ki, kd;
    double sum;
    double last;
    const double maxSum, minErr;

};