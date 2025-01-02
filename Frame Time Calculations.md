
$U$: update state time (s)
$R$: render call "draw" time (s)
$S$: simulation time (s)
$S = U + R$

$F$: frame time (s)
$\lambda$: fps ($s^{-1}$)
$F_{opt}$: optimal frame time (s)
$\lambda_{opt}$: optimal fps ($s^{-1}$)
$W$: wait time (s)

We want $F$ to ideally always be $F_{opt}$, so this means we need to alter $W$
$F_{opt} = F = S + W$
$W = F_{opt} - S$

so if $\lambda_{opt} = 60 \space \text{FPS}$, $F_{opt} = {1 \over 60} \space \text{s} = 0.1 \dot{6} \space \text{s}$
if $S = 0.001 \space \text{s}$, then $W = 0.01\dot{6}\space\text{s} - 0.001\space\text{s} = 0.015\dot{6}\space\text{s}$

However a problem is presented if $S > F_{opt}$, because this would mean $W < 0$. It is impossible to wait for a negative amount of time. To prevent this if $W < 0$, we must decrease $F$ temporarily until $W > 0$ again.

$\lambda_{max}$: the upper bound of $\lambda_{opt}$, ideal FPS.
$\lambda_{min}$: the lower bound of $\lambda_{opt}$. if $\lambda < \lambda_{opt} = \lambda_{min}$ then the simulation itself must be slowed rather than decreasing FPS.

$\lambda_{opt}$: an FPS between $\lambda_{min}$ and $\lambda_{max}$, stepped down depending on the actual simulation frame time $\lambda$.
$f_{opt} (W)$

```haskell
-- Typical waiting time calculation assuming W > 0
waitTime :: Float -> Float -> Float
waitTime sim_time opt_fps = sim_time - (1.0 / opt_fps)

-- Calculates the target FPS
optFPS :: Float -> Float -> Float -> Float
optFPS min_fps max_fps sim_time =
	max (min sim_fps max_fps) min_fps
	where sim_fps = 1.0 / sim_time

calcWait :: Float -> Float -> Float -> Float
calcWait min_fps max_fps sim_time = (waitTime sim_time) . optFPS
```
