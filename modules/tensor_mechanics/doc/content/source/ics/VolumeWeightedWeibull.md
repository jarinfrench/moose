# Volume Weighted Weibull

!syntax description /ICs/VolumeWeightedWeibull

The VolumeWeightedWeibull class generates a spatially randomized distribution of a variable following a Weibull distribution, but weighted by the element volume to account for the fact that larger volumes are more likely to contain defects, and would thus have a reduced strength. This class follows the approach documented in [!cite](strack_aleatory_2015), and using it to describe local strength for fracture models minimizes mesh size dependence.

The randomized value of a given variable $\eta$ used to characterize a strength can be expressed as:
\begin{equation}
\label{eqn:vww}
\eta=\bar{\eta}\biggl[\frac{\bar{V}\ln(R)}{V\ln(0.5)}\biggr]^{1/k}
\end{equation}
where $\bar{\eta}$ is the median value of the strength variable, $\bar{V}$ is the reference volume, which is the volume of a test specimen that has a median strength equal to $\bar{\eta}$, $R$ is a uniform random number on the interval from 0 to 1, and $k$ is the Weibull modulus.

This has two important differences from using the standard Weibull distribution, which can also be used to define a randomized strength in MOOSE using a combination of the WeibullDistribution object in the `stochastic_tools` module and the MOOSE [RandomIC](RandomIC.md) object:

 1. This Weibull distribution is defined by two parameters: the Weibull modulus, $k$, and the median value of the randomized variable, $\bar{\eta}$. This in contrast to the standard version, which has three parameters: the Weibull modulus, $k$, the shape parameter, $\lambda$, and the location parameter, $\theta$. The distribution generated by this Weibull distribution implicitly assumes that $\theta=0$. The value for $\lambda$ for the standard set of parameters in a Weibull distribution can be computed from $\bar{\eta}$ and $k$ as:
\begin{equation}
\lambda=\bar{\eta}\biggl[\frac{-1}{\ln(0.5)}\biggr]^{1/k}
\end{equation}

 2. The value of the samples from the standard Weibull distribution is scaled by the factor:
\begin{equation}
\biggl[\frac{\bar{V}}{V}\biggr]^{1/k}
\end{equation}
As a result of this scaling, elements larger than the reference volume typically have decreased strength, and elements smaller than the reference volume have increased strength (because $k$ is typically greater than 1).

!syntax parameters /ICs/VolumeWeightedWeibull

!syntax inputs /ICs/VolumeWeightedWeibull

!syntax children /ICs/VolumeWeightedWeibull

!bibtex bibliography
