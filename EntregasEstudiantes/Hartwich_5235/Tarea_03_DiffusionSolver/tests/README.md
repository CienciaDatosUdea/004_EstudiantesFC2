The following tests have been conducted:

> "initial_state":

$\rightarrow$ the x values are calculated correctly by the Geometry class.

$\rightarrow$ t\_end = 0 is practically forbidden by error handling, but using one single very small step shows that the initial condition is plausibly integrated (gaussian symmetric in the mid point of the x range). 

> "final_state":

$\rightarrow$ For any physical parameters, a sufficiently long time will lead to the same result: the whole array will take on the value of the dirichlet boundary conditions, i.e. the whole 1D object will take on the temperature of its ends. Physically speaking, there's a temperature flow as long as the temperature is not constant, and, logically, the boundary conditions are the only constant value that the system can take on (since they are fixed and any point of the system taking on another value would imply that temperature is flowing and therefore not constant).

> "D_1_rest_const" and "D_2_rest_const"

$\rightarrow$ The comparison of these files shows that when the other parameters are the same, a larger D will lead to a faster thermal equalization.