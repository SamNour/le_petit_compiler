$$

\begin{align}
    [\text{prog}] &\to [\text{stmt}]^*\\
    [\text{stmt}] &\to  
    \begin{cases}
    exit([\text{stmt}]) \\
    let \text{ident} = [\text{expr}]
    \end{cases}
    \\
    \text{expr} &\to \text{int\_literal}
\end{align}
$$
