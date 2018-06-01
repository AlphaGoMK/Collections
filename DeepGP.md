## Deep Gaussian Process Model

GP: to handle sparse dataset scenarios -> massively missing data  
deep GP: mean function(deep) + covariance function -- propagating uncertainly around network  
idea: automatically determine number of layer and hidden nodes to develop variants of Gaussian process for multiview learning  

## Further reading

Deep GP: deep belief networks(semantics) + priors in bayesian mmodels(experience)  
Non-parametric, continuous variables  
X -f-> H -f-> H -f-> Y  
#### Dynamics
t -- > H --> Y : Y form a multivariate time-series, then H also has to be one
dynamics encoded in covariance matrix __K__
