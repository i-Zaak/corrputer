/**
 * Statistical functions.
 */
#ifndef STATISTICS_H
#define	STATISTICS_H

#include "ValueStream.h"

/**
 * Returns the power sum average based on the blog post from
    Subliminal Messages.  Use the power sum average to help derive the running
    variance.
    sources: http://subluminal.wordpress.com/2008/07/31/running-standard-deviations/
 
    Keyword arguments:
    bar     --  current index or location of the value in the series
    series  --  list or tuple of data to average
    period  -- number of values to include in average
    pval    --  previous powersumavg (n - 1) of the series.
 * 
 * @param bar
 * @param series
 * @param period
 * @param pval
 * @return 
 */
float powersumavg(int bar, ValueStream* series, int period, float pval);

/**
 * Returns the running variance based on a given time period.
    sources: http://subluminal.wordpress.com/2008/07/31/running-standard-deviations/
 
    Keyword arguments:
    bar     --  current index or location of the value in the series
    series  --  list or tuple of data to average
    asma    --  current average of the given period
    apowsumavg -- current powersumavg of the given period
 * 
 * @param bar
 * @param series
 * @param period
 * @param asma
 * @param apowsumavg
 * @return 
 */
float running_var(int bar, ValueStream* series, int period, float asma, float apowsumavg);

/*
    Returns the cumulative or unweighted simple moving average.
    Avoids sum of series per call.
 
    Keyword arguments:
    bar     --  current index or location of the value in the series
    series  --  list or tuple of data to average
    prevma  --  previous average (n - 1) of the series.
*/
float cumulative_sma(int bar, ValueStream* series, float prevma);

/*
    Returns the running simple moving average - avoids sum of series per call.
 
    Keyword arguments:
    bar     --  current index or location of the value in the series
    series  --  list or tuple of data to average
    period  --  number of values to include in average
    prevma  --  previous simple moving average (n - 1) of the series
*/
float running_sma(int bar, ValueStream* series, int period, float prevma);

#endif	/* STATISTICS_H */

