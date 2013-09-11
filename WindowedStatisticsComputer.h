#ifndef WINDOWEDSTATISTICSCOMPUTER_H
#define	WINDOWEDSTATISTICSCOMPUTER_H
#include <queue>

class WindowedStatisticsComputer {
public:
    WindowedStatisticsComputer(int windowSize);
    WindowedStatisticsComputer(const WindowedStatisticsComputer& orig);
    virtual ~WindowedStatisticsComputer();
    
    void nextNumber(float value);
    float getMean();
    float getVariance();
    float getStDev();
    
private:
    int windowSize;
    
    int n;
    float sum;
    float mean;
    float variance;
    float M2;
    
    std::queue< float > *valueHistory;
    std::queue< float > *M2History;
};

#endif	/* WINDOWEDSTATISTICSCOMPUTER_H */

