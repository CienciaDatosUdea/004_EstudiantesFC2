# Física Computacional II Project
This is the final project for the Física Computacional II class, teached by **Hernán Salinas**, FCEN Universidad de Antioquia, 2025-1, by **Sara Alejandra Carvajal** and **Laurent Hartwich**.


# Abstract

The goal of this project is to combine the 2D Ising model and a basic neural network in C++. The Ising model is implemented using a Monte Carlo simulation with the Metropolis criterion. The network is trained through supervised learning with clearly ordered and clearly unordered configurations in order to later predict whether an unknown configuration is ordered or unordered. Neural networks with different parameters are trained in order to compare how accuracy evolves during training. Finally, the critical temperature of the Ising magnet is determined by analyzing the predictions of the best network for configurations of a broad range of temperatures and determining the point of maximal confusion. This is compared to the analytical solution for the critical temperature.

Due to external circumstances, this project was not completed to its planned extent. The Ising part is fully implemented and functional, the ML part is developed to a point that clearly reflects the core idea of the project.

# 2D Ising Model

## General Description

The 2D Ising model is a prototypical system in statistical physics used to study phase transitions and collective behaviour in interacting spins.

It was originally proposed by Wilhelm Lenz in 1920 and analytically studied by his student Ernst Ising in 1925 as a way to understand phase transitions in ferromagnetic materials \[1.\]. While the 1D version does not exhibit a phase transition, the 2D model later solved by Lars Onsager revealed a critical temperature, making it a foundational tool in the study of critical phenomena \[1.\]. 

The Ising model consists of a lattice (usually square) of spins $S\_{i,j} = \pm 1$ where each spin interacts only with its four nearest neighbors (up, down, left, right), typically under periodic boundary conditions. Therefore, the total energy of the system corresponds to the sum over all nearest-neighbor interactions:

$$ H= - \sum\_{<i,j>} J S\_{i} S\_{j}$$

where the sum runs over all nearest neighbor pairs $<i,j>$ and $J$ is the interaction constant.

The total energy can be rewritten in a way that reflects the fact that the contribution of every spin depends only on its four nearest neighbors:

$$
\begin{align*}
    H &= - J \sum\_{<i,j>} S\_{i} S\_{j} \\
    &= - \frac{1}{2} \sum\_i \\, J \\, S\_i \sum\_{j\\,\in\\,\text{nn}(i)} S\_j \\
    &= \frac{1}{2} \sum\_i \\, E^{\text{local}}\_i
\end{align*}
$$

where $nn(i)$ denotes the set of nearest neighbors of spin i,

$$
E^{\text{local}}\_i := -J \ S\_i \sum\_{j \in \text{nn}(i)} {S}\_j
$$

corresponds to the contributions of the interactions of the $i$-th spin with its neighbors and the factor of $\frac{1}{2}$ is necessary because executing the sum over all indices without this adjustment would lead to counting every interaction twice (once from each spin's point of view).

From the total energy, we can derive thermodynamic properties of the system using the formalism of statistical mechanics \[1.\], such as:

* **Specific heat**:
$$C(T) = \frac{1}{T^2} \left( \langle H^2 \rangle - \langle H \rangle^2 \right)$$

* **Internal energy**:
$$U(T) = \langle H \rangle = \frac{1}{Z} \sum\_{S} H(S) e^{-H(S)/T}$$

where the average is taken over all configurations $S$.

In thermal equilibrium, the probability of encountering a given spin configuration $S$ is determined by the Boltzmann distribution:

$$P(S) = \frac{1}{Z} e^{-H(S)/T}$$

with the partition function
$$Z = \sum\_{\{ S \}} e^{-H(S)/T}$$

This expression plays a central role in Monte Carlo simulations, where it determines the likelihood of accepting or rejecting spin flips.

By analyzing the system's energy as a function of temperature, we can identify phase transitions through the behavior of thermodynamic observables such as the specific heat or magnetization.

In computational applications of the Ising model, the local energy plays a central role, especially in Monte Carlo simulations. These methods are widely used because they allow us to simulate large systems with many interacting spins, where computing the exact solution becomes intractable.

In particular, we apply the Metropolis algorithm, in which spins are flipped randomly, and each proposed change is accepted or rejected based on how it affects the system’s energy. This approach enables us to explore different configurations and find states close to thermal equilibrium by gradually favoring lower-energy configurations while still allowing some fluctuations.

Since the total energy of the Ising model depends only on the local interactions of every spin (nearest-neighbor-sums), only this local sum has to be computed and compared in order to evaluate the Metropolis probability of flipping a spin; it is not necessary to compute the total energy of the system every time. This is a significant factor regarding computational resources when computing a Markov Chain consisting of millions of individual steps. 

Beyond magnetism, the Ising model has been applied in diverse contexts such as biology, economics, statistics, and social analysis, thanks to its ability to capture collective behaviour emerging from simple local interactions \[2.\].

## Generation of Ising Configurations

In this project, we implement a simplified version of the two-dimensional Ising model in C++. The system consists of binary spins $S\_{i,j} = \pm1$ arranged on a square lattice, with nearest-neighbor interactions and periodic boundary conditions. We will not address large-scale phenomena—such as the explicit modeling of electrons or external magnetic fields—as the focus is on understanding the core dynamics through a minimal and controlled setting. 

Every configuration will be generated using the following structure: 

1. **Spin initialization:** We begin by generating random initial configurations, assigning each lattice site a spin value of $\pm 1$.

2. **Monte Carlo simulation based on the Metropolis algorithm**: To simulate the thermal behavior of the Ising system, we use the Metropolis algorithm—a stochastic sampling method that enables efficient exploration of the system's configuration space without evaluating every possible spin arrangement \[3\].

One single Monte Carlo step consists of the following routine:
* A random spin is selected
* The energy difference $\Delta E$ associated with flipping this spin (from $+1$ to $-1$ and viceversa) is calculated.
* If flipping the spin decreases the system’s energy ($\Delta E < 0$), the change is accepted.  
* Otherwise, the change is accepted with probability $e^ {-\Delta E / T}$, where $T$ is the temperature of the system.

One sweep refers to a full update cycle where we attempt to flip as many spins as there are in the lattice. Since the lattice has $L \times L$ spins, one sweep consists of $L^2$ Monte Carlo steps, each targeting a randomly selected spin. Repeating thousands of sweeps then allows the system to gradually evolve toward thermal equilibrium while sampling a wide range of configurations.

To build a diverse and uncorrelated dataset of configurations, this procedure is repeated multiple times, always starting from a newly randomized lattice and saving the end result to a binary file (including information about the associated temperature and the system size).

The analytical critical temperature for the 2D Ising magnet as derived by Lars Onsager is 

$$
\quad\quad\frac{2\\,J}{\ln(1+\sqrt{2})} \quad\quad\text{\[5\]}
$$

(assuming $k\_\text{B}$ = 1). Below this temperature, the configurations tend to be ordered, while above, they tend to be unordered.

# Machine Learning

> **This section is intended as a short recapitulation of well-established knowledge within the machine learning community and therefore does not quote extensively. Excellent introductory resources for approaching the subject in a more detailed way include [Grant Sandersons's video series](https://www.youtube.com/playlist?list=PLZHQObOWTQDNU6R1\_67000Dx\_ZCJB-3pi) with great visualizations and [Michael Nielsen's introductory book](https://neuralnetworksanddeeplearning.com/index.html) available online.**


## Application Idea

The approach described above will be used to first generate the configurations used as training data for our neural network model \[4.\], and later new configurations unknown to the network to assess its precision. The implemented neural network will take one Ising configuration as input (i.e. $L^2$ input neurons) and have two output neurons whose output should correspond to "probability the input spin configuration is ordered phase" and "probability this is a disordered phase". Therefore, our training data will consist of a set of configurations for one temperature that is well below the critical temperature and another temperature that is well above the critical temperature. Each sample will be labeled with the according target in order to apply supervised learning, during which the network should learn how statistical patterns in spin arrangements relate to "ordered-ness". The chosen targets are (1,0) for ordered configurations and (0,1) for unordered configurations. After training, the output of the network will be analyzed for configurations of a broad range of temperatures, which allows to interpret the point where the probabilities for "ordered" and "unordered" intersect as the critial temperature. This way, we hope to demonstrate that our implementation of the chosen approach is able to replicate the analytical critical temperature within a low margin of error. 

## Sigmoid neuron and basic feedforward network layout

The elementary structure of a neural network is a neuron. The neurons have an activation function, for which one popular choice is the sigmoid function given by

$$
\sigma(z) = \frac{1}{1+e^{-z}}
$$

with the derivative

$$
\sigma'(z) = \sigma(z) \cdot \left(1-\sigma(z)\right)
$$

The activation function modulates the output of a given neuron as a function of $z = \mathbf{w}\cdot\mathbf{x} + b$, where $\mathbf{x}$ is the vector of all outputs from the neurons of the layer before, $\mathbf{w}$ is the vector of all edge weights that this neuron applies to these outputs and $b$ is the bias that this neuron adds.

Let's examine this more carefully.

Every neuron of a given layer is connected to every neuron from the layer before. Therefore, from a single-neuron-perspective, every single neuron has one weight $w\_i$ *per output component of the last layer* and one single bias $b$. That corresponds to

$$
z\_\text{this specific neuron} = \mathbf{x}^\intercal\_\text{output from last layer}\mathbf{w}\_\text{this specific neuron} + b\_\text{this specific neuron}
$$

At last, the sigmoid activation function is applied to $z$ to modulate, or "activate", the output of the neuron.

Zooming out to the scope of one whole layer, these per-neuron-equations can be rewritten algebraically as

$$
\mathbf{z} = \mathbf{W}\\,\mathbf{x} + \mathbf{b} 
$$

where $\mathbf{W}$ is a matrix of dimension $(n\_\text{current layer} \times m\_\text{last layer})$ whose rows correspond to the edge weight vectors of the single neurons,

$$
\mathbf{W} = \begin{bmatrix}
    \quad       &  \mathbf{w}\_1  &     \quad    \\
                &  \mathbf{w}\_2  &              \\
                &  \vdots        &              \\
                &  \mathbf{w}\_\text{n}  &               \end{bmatrix}
$$

with the components of $\mathbf{b}$ corresponding to the biases of every neuron and the components of $\mathbf{z}$ therefore corresponding to the results for every neuron. Finally, applying the sigmoid function to every component of $\mathbf{z}$ yields the actual output of every neuron.

Without counting the input layer, a neural network with $N > 1$ layers (i.e. a network with hidden layers), the relationship between the initial input vector $\mathbf{x\_\text{in}}$ and the final output vector $\mathbf{x\_\text{out}}$ is the following:

$$
\begin{align*}
\mathbf{x\_\text{in}} =: \mathbf{x}\_0 &\rightarrow \mathbf{\sigma}\left(\mathbf{W}\_1\\,\mathbf{x}\_0 + \mathbf{b}\_1\right) =: \mathbf{x}\_1 \\
&\rightarrow \mathbf{\sigma}\left(\mathbf{W}\_2\\,\mathbf{x}\_1+ \mathbf{b}\_2\right) =: \mathbf{x}\_2 \\
&\rightarrow ... \\
&\rightarrow \mathbf{\sigma}\left(\mathbf{W}\_i\\,\mathbf{x}\_{i-1} + \mathbf{b}\_i\right) =: \mathbf{x}\_i \\
&\rightarrow ... \\
&\rightarrow \mathbf{\sigma}\left(\mathbf{W}\_{N}\\,\mathbf{x}\_{N-1} + \mathbf{b}\_{N}\right) =: \mathbf{x}\_{N} =: \mathbf{x\_\text{out}} 
\end{align*}
$$

where $\mathbf{\sigma}$ now refers to the component-wise application of the sigmoid function and $\mathbf{W}\_i$ and $\mathbf{b}\_i$ contain the edge weight vectors and biases of the i-th layer ("toward the (i-1)-th layer"). For neuron numbers $\\{n\_i : i \in 0, ..., N\\}$, this means that $\mathbf{x}\_{i-1} \in \mathbb{R}^{n\_{i-1}}$, $\mathbf{W}\_i \in \mathbb{R}^{n\_i\times n\_{i-1}}$ and $\mathbf{b}\_i \in \mathbb{R}^{n\_i}$ (where the latter two only exist for $i \geq 1$, respectively, since the input layer does not apply any weights or biases to the input vector in this way of thinking).

The flow chart above corresponds to a simple fully connected feedforward network, which means that every neuron is connected to every neuron from the layer before and the output vector is computed from the input vector one layer at a time without any cycles. Countless adaptations are possible.

## Supervised learning and backpropagation

### Output layer: output, target, cost function, error and learning rate

The learning process of a neural network is the phase in which training data is used to tune the weights and biases of the network until it (ideally) produces accurate outputs for previously unknown data.

There are different methods to train a network. The one used here is supervised learning, in which the training data is labeled with the expected answers. Other methods include unsupervised learning, in which the training data is not labeled in any way, and semi-supervised learning, which is a mixture of the two.

In the case of supervised learning, each input vector of the training dataset is labeled with the exact expected output vector (also called target). To take our intended use case as an example, if the input layer receives an array of spins that is considered by humans to represent an "ordered phase", and the output layer has two neurons whose outputs we want to correspond to "probability that this is an ordered phase" and "probability this is an unordered phase", then the expected output is $\mathbf{x\_\text{out}} = (1,0)$. Vice versa, for any input vector representing an unordered phase, the expected output is $\mathbf{x\_\text{out}} = (0,1)$. Then, the actual output of the neuron is compared to the expected output using a cost function, and the error is "propagated backwards" to adapt all weights and biases recursively – backpropagation.

Concretely, the weight and biases are tuned as follows.

First, all weights and biases are initialized as normally distributed real numbers (an example of a more sophisticated method would be the Xavier Glorot initialization). Then, the first input vector is passed to the network and the output $o\_k$ of every neuron is compared to its target value $t\_k$ through the quadratic cost function

$$
C = \tfrac{1}{2}\\,\sum\_k\left( t\_k - o\_k \right)^2
$$

which is a sum over all output neurons and can therefore be written vectorially,

$$
C = \tfrac{1}{2}\\,\| \mathbf{t} - \mathbf{o} \|^2
$$

 Intuitively, this function is to be minimized (as its global minimum lies where every output coincides exactly with its target\*), and the means to minimize it is to tune the weights and biases of the network (from which C implicitly depends, as these modulate the output $\mathbf{t}$ from a given input). We're therefore interested in how the cost function changes depending on each and every weight and bias, starting on the output layer. (\*Just as a side note: finding the actual global minimum in the highdimensional space of all weights and biases is not usually a feasible goal. Many local minima can also correspond to networks with good accuracy.) Let's first examine the weights. For the i-th neuron of the output layer, with output $o\_i$ and edge weights $w\_{ij}$,

$$
\frac{\partial C}{\partial w\_{ij}} = \frac{\partial C}{\partial o\_i} \\, \frac{\partial o\_i}{\partial z\_i} \\, \frac{\partial z\_i}{\partial w\_{ij}} := \delta\_i\\, \frac{\partial z\_i}{\partial w\_{ij}}
$$

while for the biases,

$$
\frac{\partial C}{\partial b\_{i}} = \frac{\partial C}{\partial o\_i} \\, \frac{\partial o\_i}{\partial z\_i} \\, \frac{\partial z\_i}{\partial b\_{i}} = \delta\_i\\, \frac{\partial z\_i}{\partial b\_{i}}$$

All of the partial derivatives are easily derived from the previous definitions:

$$
\begin{align*}
\frac{\partial C}{\partial o\_i} \\, &= o\_i - t\_i \\
\frac{\partial o\_i}{\partial z\_i} \\; &= \sigma'(z\_i) = \sigma(z\_i) \cdot (1 - \sigma(z\_i)) = o\_i \cdot (1 - o\_i) \\
\frac{\partial z\_i}{\partial w\_{ij}} &= x\_j \\
\frac{\partial z\_i}{\partial b\_{i}} &= 1 
\end{align*}
$$

(recall that the output of a neuron is simply $o\_i(z\_i) = \sigma(z\_i)$ and that $z\_i = \mathbf{x}^\intercal \mathbf{w}\_i + b\_i = \sum\_j x\_j w\_{ij} + b\_i$). Therefore, explicitly,

$$
\frac{\partial C}{\partial w\_{ij}} = (o\_i-t\_i)\\,o\_i\\,(1-o\_i)\\,x\_j = \delta\_i \\, x\_j
$$

and

$$
\frac{\partial C}{\partial b\_{i}} = (o\_i-t\_i)\\,o\_i\\,(1-o\_i) = \delta\_i
$$

Note that $\delta\_i$ does not depend on $j$, i.e. all derivatives $\frac{\partial C}{\partial w\_{ij}}$ for a given neuron depend on the same $\delta\_i$.

From here, the weights and biases are then adapted through "gradient descent", where every weight and bias is adjusted proportionally to its derivative of the cost function:

$$
\tilde{w}\_{ij} = w\_{ij} - \eta \\, \frac{\partial C}{\partial w\_{ij}} = w\_{ij} - \eta\\,\delta\_i\\,x\_j
$$
and
$$
\tilde b\_i = b\_i - \eta \\, \frac{\partial C}{\partial b\_{i}} = b\_i - \eta\\,\delta\_i
$$

To put it into words, the more changing some weight $w\_{ij}$ or bias $b\_i$ is expected to lower the cost function, the more it is changed. (The negative sign leads towards a minimum of C, as adding the partial derivative of $C$ on its own would lead toward a maximum.)

Moving again from the single-neuron scale to the scale of one whole layer (where the layer before has $m$ neurons and the output layer has $n$ neurons), this can be expressed again in vector/matrix form through

$$
\begin{align*}
\frac{\partial C}{\partial \mathbf{W}} &:= \begin{bmatrix}
    \quad\frac{\partial C}{\partial w\_{11}} & \frac{\partial C}{\partial w\_{12}}& ... & \frac{\partial C}{\partial w\_{1\text{m}}} \quad \\
\quad\vdots    & \vdots  & \vdots      & \vdots \quad \\
\quad\frac{\partial C}{\partial w\_{\text{n}1}} & \frac{\partial C}{\partial w\_{\text{n}2}}& ... & \frac{\partial C}{\partial w\_{\text{n}\text{m}}}\quad \end{bmatrix} \\
\frac{\partial C}{\partial\mathbf{b}} &:= \begin{bmatrix}
    \quad\frac{\partial C}{\partial b\_{1}}\quad \\
\vdots \\
\frac{\partial C}{\partial b\_{\text{n}}}\end{bmatrix}
\end{align*}
$$

where $b\_i$ is the bias of the i-th neuron of the output layer and $w\_{ij}$ is its weight with respect to the j-th neuron of the layer before.

Since, as mentioned, these partial derivatives consist in part of the errors $\delta\_i$ that are neuron-specific (i.e. constant within every row), these objects can be re-written as

$$
\begin{align*}
\frac{\partial C}{\partial \mathbf{W}} &= \mathbf{x} \\; \mathbf{\delta}^\intercal \\
\frac{\partial C}{\partial\mathbf{b}} &= \delta
\end{align*}
$$

where $\mathbf{\delta}$ is the vector whose i-th component $\mathbf{\delta}\_i := \frac{\partial C\_i}{\partial z\_i} = \frac{\partial C\_i}{\partial o\_i}\frac{\partial o\_i}{\partial z\_i}$ contains the whole information about the error of the i-th neuron of the output layer, and $\mathbf{x}^\intercal$ is the output from the layer before. Thus, finally, the edge weight matrix and the bias vector are adapted through element-wise substraction like

$$
\begin{align*}
\mathbf{\tilde W} &= \mathbf{W} - \eta \\; \frac{\partial C}{\partial W} = \mathbf{W} - \eta\\,\mathbf{x}\\,\delta^\intercal \\
\mathbf{\tilde b} &= \\;\\; \mathbf{b} - \eta \\, \frac{\partial C}{\partial \mathbf{b}}\\;\\; = \mathbf{b} - \eta \\; \mathbf{\delta}
\end{align*}
$$

Here, $\eta$ is the so-called learning rate, which can be constant, but also change as a function of the amount of the incorporated training data. The best choice for the learning rate has to be determined heuristically -- in the case of constant learning rates, low values can lead to very slow convergence, whereas overly big learning rates can lead to unstable behavior.

### Backpropagation

Now, how is the error from the output neurons propagated for all of the neurons before, for which there are no obvious "target values" defined by the label of the training data? The answer lies in the chain rule. As before, we want to compute $\delta^{\[i\]}\_{j} := \frac{\partial C}{\partial z^{\[i\]}\_{j}}$ for the j-th neuron of the i-th layer. For the n-th layer,

$$
\begin{align*}
\delta^{\[n-1\]}\_{j} = \frac{\partial C}{\partial z^{\[n-1\]}\_{j}} &= \sum\_i \frac{\partial C}{\partial o^{\[n\]}\_{i}}\frac{\partial o^{\[n\]}\_{i}}{\partial z^{\[n\]}\_{i}} \frac{\partial z^{\[n\]}\_{i}}{\partial x^{\[n-1\]}\_{j}}\frac{\partial x^{\[n-1\]}\_{j}}{\partial z^{\[n-1\]}\_{j}}
\end{align*}
$$

Remembering that

$$
\frac{\partial C}{\partial o^{\[n\]}\_{i}}\frac{\partial o^{\[n\]}\_{i}}{\partial z^{\[n\]}\_{i}} = \delta^{\[n\]}\_i
$$ 

and infering that

$$
z\_i^{\[n\]} = w^{\[n\]}\_{ij}\\,x^{\[n-1\]}\_j + b^{\[n\]}\_i \quad\Rightarrow\quad \frac{\partial z^{\[n\]}\_{i}}{\partial x^{\[n-1\]}\_{j}} = w^{\[n\]}\_{ij}
$$

and

$$
\frac{\partial x^{\[n-1\]}\_{j}}{\partial z^{\[n-1\]}\_{j}} = \sigma'\left(z\_j^{\[n-1\]}\right) = x^{\[n-1\]}\_{j} \\, \left(1 - x^{\[n-1\]}\_{j}\right)
$$

it follows that

$$
\delta^{\[n-1\]}\_{j} = \sum\_i \\, \delta^{\[n\]}\_i \\, w^{\[n\]}\_{ij} \\, x^{\[n-1\]}\_{j} \\, \left(1 - x^{\[n-1\]}\_{j}\right)
$$

which expresses any error of a former layer as a function of the errors of later layers.

This error can then again be used in the same way as before,

$$
\frac{\partial C}{\partial w\_{ij}^{\[n-1\]}} = \frac{\partial C}{\partial z\_{i}^{\[n-1\]}}\frac{\partial z\_i^{\[n-1\]}}{\partial w\_{ij}^{\[n-1\]}} = \delta^{\[n-1\]}\_j \\, x\_i^{\[n-2\]} \quad\rightarrow\quad \tilde w\_{ij}^{\[n-1\]} = w\_{ij}^{\[n-1\]} - \eta \\, \frac{\partial C}{\partial w\_{ij}^{\[n-1\]}}
$$

$$
\frac{\partial C}{\partial b\_{i}^{\[n-1\]}} = \frac{\partial C}{\partial z\_{i}^{\[n-1\]}}\frac{\partial z\_i^{\[n-1\]}}{\partial b\_{i}^{\[n-1\]}} = \delta^{\[n-1\]}\_j \quad\rightarrow\quad \tilde b\_{i}^{\[n-1\]} = b\_{i}^{\[n-1\]} - \eta \\, \delta\_i^{\[n-1\]}
$$

or, in matrix form,

$$
\frac{\partial C}{\partial \mathbf{W}^{\[n-1\]}} = \mathbf{x}^{\[n-2\]} \\, \delta^{\[n-1\]\\,\intercal} \quad\rightarrow\quad \mathbf{\tilde W}^{\[n-1\]} = \mathbf{W}^{\[n-1\]} - \eta \\, \frac{\partial C}{\partial \mathbf{W}^{\[n-1\]}}
$$

$$
\frac{\partial C}{\partial \mathbf{b}^{\[n-1\]}} = \delta^{\[n-1\]} \quad\rightarrow\quad \mathbf{\tilde b}^{\[n-1\]} = \mathbf{b}^{\[n-1\]} - \eta \\, \frac{\partial C}{\partial \mathbf{b}^{\[n-1\]}}
$$

To summarize one entire training loop: based on the current weights of the network, every input vector creates one output per neuron. The outputs of the final layer are compared to their target values, and backpropagation enables the errors of all former neurons to be calculated based on the errors of later neurons. Finally, all weights are adapted using the gradient of the cost function, since that function is what we want to minimize. This is called gradient descent.

## Learning: Epochs, mini-batches and online learning

Usually, "training a neural network with a training dataset" does not mean that every input vector from the training dataset is used for backpropagation just once. Instead, the whole training dataset is used several times. This is what the term "epoch" refers to: in every epoch, the neural network sees the whole training dataset exactly once. A network can then be trained with hundreds of epochs. It is, however, important to randomize the data newly for every epoch, so that the system does not get caught in any unforeseen loops.

Another aspect that has gone unmentioned sofar is the possibility of using mini-batches. Until now, the whole description of back-propagation implied doing it in every step, i.e. "pass an input vector $\rightarrow$ calculate cost function $\rightarrow$ backpropagate error and tune everything $\rightarrow$ do the same for all vectors". This is called online learning, as the neural network immediately reacts (i.e. backpropagates) after any new input. 

The alternative is averaging the cost function over batches of input vetors and then only updating the weights and biases once after every batch. The two  methods have nontrivial implications for the navigation through the highdimensional space of the cost function, but one doubtless advantage of using batches is computational speed, since not updating all weights and biases once for every input vector saves a lot of computations per epoch. Whether or not this actually leads to achieving a higher network accuracy for a given computation time still has to be determined heuristically, however.

Practically, where the cost of one input vector $\mathbf{x}$ with target $\mathbf{t}$ and produced output $\mathbf{o}$ was initially defined like

$$
C\_\mathbf{x} = \tfrac{1}{2}\\,\sum\_k\left( t\_k - o\_k \right)^2
$$

it is not averaged over a batch of $N$ input vectors

$$
\braket{C}\_\text{batch} = \tfrac{1}{N}\\,\sum\_\mathbf{x} C\_\mathbf{x}
$$

and the errors are propagated just once. Propagating the errors like this is possible because differentiation is a linear operation and the batch cost defined here is a simple average over the cost per input.

When training in batches, an additional computational speedup can be achieved when not passing all input vectors ony by one, but grouping them into one single matrix per batch, because this can be optimized to a higher degree. The operations per layer then go from

$$
\mathbf{z} = \mathbf{W}\\,\mathbf{x} + \mathbf{b} 
$$

for single vectors to

$$
\mathbf{Z} = \mathbf{W}\\,\mathbf{X} + \mathbf{b} 
$$

when passing the whole batch at once (where the i-th column of $\mathbf{X}$ is the i-th input vector, the i-th column of $\mathbf{Z}$ is the i-th output vector, and the vector $\mathbf{b}$ is added to every column of $\mathbf{WX}$).

--- 

# Implementation 

## Top Level Structure

On the highest level, the structure is separated into two parts (that will not interact with each other directly).

* The first part generates sets of Ising configurations (for a specified 2D array width L, temperature T, amount of metropolis sweeps and amount of configurations to generate) and saves them to a file.
* The second part implements the neural network that will load these files and use them as input data (training datasets for training, previously unknown datasets for success evaluation).

This setup is logical because while we will compare different approaches to training the neural network, there is no reason to generate new training data every time (for fixed parameters as described above). The size of the data is not significant (e.g. for memory usage) at our scales, but the time to generate it is. 

## Ising Code Structure

The project folder has the usual layout for using a Makefile: a /src/ folder for all .cpp files and an /include/ folder for all headfiles. For this part of the project, there is only one headfile, `ising\_public\_interface.h`. It contains the declarations for any class and function that will be used during the whole Ising script.

The ``Grid`` class is a flattened vector, i.e. a 1D vector containing the 2D grid with a defined `operator(int i, int j)` that allows calling the cells of the 2D system with intuitive 2D indices. Additionally, this operator allows the option to use periodic boundary conditions, i.e. calling it with indices that extend over the factual scope of the 2D system (activated per default). This spares implementing it as part of the ising class.

The `Ising` class contains the Grid containing the state of the 2D magnet, all methods needed to initialize and evolve it and getter functions for macroscopic attributes of the evolved system (energy, magnetization and specific heat).

Below, functions for diverse purposes are declared, such as the global rng and the functions for writing the data files.

The concrete .cpp files are structured as follows:
- ising\_main.cpp: contains main(), organizes the generation of all data and writing it to the output files
- ising\_methods.cpp: contains the definitions of all methods of the ising class
- grid.cpp: contains the definitions of all methods of the grid class
- file\_writer.cpp: contains the definitions of the methods used to write data to files
- range.cpp: contains a method for creating a vector similar to a range in python
- time.cpp: contains a method for creating the timestamps to keep track of the progress while executing the executable
- general\_methods.cpp: contains other methods such as the global rnb


## Neural Network Code Structure

The project folder has the usual layout for using a Makefile: a /src/ folder for all .cpp files and an /include/ folder for all headfiles. For this part of the project, there are several headfiles, `ml\_public\_interface.h`, `ml\_common\_types.h` and `ml\_error\_management.h`.

The public interface contains the declarations for the main `NeuralNetwork` class, structs associated with it and functions with diverse purposes, such as the flobal rng and the functions writing to files. The error management headfiles contains the declarations of the `ErrorManagement` class, the class whose methods are used to validate any action in the neural network (both input parameters and logic). The common types headfile only contains a minor redefinition.

The ``NeuralNetwork`` class describes the whole state of one neural network (e.g. amount of layers and neurons, weights, biases and bools keeping track of the current state of the network) as well as methods needed to load training (and validation) inputs and targets, train the network and validate its accuracy during and after training.

The concrete .cpp files are structured as follows:
- ml\_main.cpp: contains main(), organizes the reading of the datasets generated by the Ising part, training different networks, determining the best one, using the best one to get the outputs for the continuous temperature dataset and writing the corresponding files
- ml\_getter\_functions.cpp: contains the definitions of the getter functions of the NeuralNetwork class.
- ml\_constructors\_and\_data\_loading.cpp: contains the definitions of the constructor of the NeuralNetwork class and the methods used to load the validation data into the class (not to be confused with the methods loading the binary files - these methods here load the already reconstructed matrices into the class.)
- ml\_training.cpp: contains the definitions of the methods used during training the neural network
- ml\_random.cpp: contains the definitions of the global rng and other functions returning random numbers
- file\_writer.cpp, range.cpp, time.cpp: exact copies of the same files from the ising part
- ml\_error\_management.cpp: contains the definitions of all functions used to check parameters and execution logic

## Write-Read-Fidelity-Test Code Structure

Additionally, a project folder was created for testing the fidelity of data after writing and reading.

The project folder has the usual layout for using a Makefile: a /src/ folder for all .cpp files and an /include/ folder for all headfiles.

The files consist of those headfiles and .cpp files of the ising part that were needed to check that the functions writing data to binary files in the Ising script and reading it in again in the ML script are implemented in a way that the reconstructed data corresponds to the original data as expected. The files were shortened to only contain relevant functions.

## Plots

The notebook used to generate plots in python from the output data can be found in the "plots" folder. To re-run it, it is important that the used .txt files are inside the current working directory.

In the same folder, all finally used plots and graphics can also be found as .png.

## Compilation guide

As explained above, the project is split into two independent parts, the Ising part and the machine learning part.

It is assumed that `make` is installed.

First, make sure that the Eigen C++ library is installed. On Ubuntu, this can be achieved through `sudo apt update` $\rightarrow$ `sudo apt install libeigen-3 dev`. It is necessary that it be installed at the default location, `/usr/include/eigen3`. If it is installed elsewhere, the cxxflags in the makefiles have to be adapted to reflect the correct path.

From there, to compile any of the two parts of the project, it is only necessary to go to the respective main folder (`/Ising/` or `/ML/`) and enter `make` into the terminal. This will generate the respective object files to the .cpp files and link them to one executable.

To execute the whole project successfully (generating all data from scratch), it is necessary to first execute the Ising part, then copy the ``*\_bin`` files from ``Ising/data/ml\_datasets/`` to `ML/ml\_input\_datasets/` and then execute the ML part. In more detail, executing the Ising part will generate a variety of files. in `/data/basic\_visualization/`, for each respective temperature used to train the neural network, a small amount of spin configurations will be saved in the `*configs.txt` file and their respective energies, magnetizations and specific heats in the other ones. In the `/data/ml\_datasets/` folder, it will generate `*\_bin` files that contain the binary data of all configurations used by the ML part for training, validation and later determining the critical temperature. The .txt files contain the same macroscopic quantities as above for the training and validation dataset, which can be used to generate histograms of the macroscopic quantities of the datasets. This can be used for showing that even though the network is trained at only two temperatures (or ordered vs. unordered phases), there is a certain diversity within the configurations. It can also be used to analyze whether the validation dataset has a similar distribution to the (much) training dataset.

The ML part in its current state compiles and runs, but running it does not generate any files. If it were completed, it would generate one .txt file for every system configuration that contains its validation logs (tracking accuracy during training in order to compare how the different neural network evolve differently), and one .txt file tracking the outputs of the best network for the continuous temperature dataset (which would be used to determine the critical temperature, interpreted as the point of maximum confusion).

To compile the write-read fidelity test, simply go to the folder `write\_read\_test` and enter `make` into the terminal.

# Gratitude and thanks

We want to express our gratitude to our professor, Hernán Salinas, for his valuable input, guidance and understanding. We also want to thank professor Simon Trebst, whose Julia notebooks on the Ising model and training a neural model for digit recognition served as excellent entry points for a broader understanding of the subjects.


--- 
### Bibliography 

\[1.\] Pathria, R.K., & Beale, P.D. Statistical Mechanics (3rd ed.). Academic Press, 2011.

\[2.\] Macy, M. W., Szymanski, B. K., & Hołyst, J. A. (2024). The Ising model celebrates a century of interdisciplinary contributions. npj Complexity, 1(1), 10.

\[3.\] Newman, M. E., & Barkema, G. T. (1999). Monte Carlo methods in statistical physics. Clarendon Press.

\[4.\] Carrasquilla, J., & Melko, R. G. (2017). Machine learning phases of matter. Nature Physics, 13(5), 431-434.

\[5.\] Onsager, L. (1944). Crystal statistics. I. A two-dimensional model with an order-disorder transition. Physical review, 65(3-4), 117.