// Perform Linear Regression on time series and return slope

// Blake Leonard	2014

// Monitor Instruments


double linear_reg(double time_series[], int length, double delta_t );


double linear_reg(double time_series[], int length, double delta_t)
{
	double lin_slope;

	double sum_t = 0;

	double sum_y = 0;

	double sum_t_sq = 0;

	double sum_t_y = 0;
	
	int istep;

	for (istep = 0; istep < length; istep ++ )
	{

		sum_t += ( istep * delta_t );

		sum_y += time_series[istep];

		sum_t_sq += ( ( istep * delta_t ) * ( istep * delta_t ) );

		sum_t_y += ( time_series[istep] * ( istep * delta_t ) );

	}
	
	lin_slope = ( length * sum_t_y - sum_t * sum_y ) / ( length * sum_t_sq - sum_t * sum_t );

	return lin_slope;

}