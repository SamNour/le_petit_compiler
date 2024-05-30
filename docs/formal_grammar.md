$$

\begin{align}
    [\text{prog}] &\to [\text{stmt}]^*\\
    [\text{stmt}] &\to  
    \begin{cases}
    \text{exit}([\text{expr}]) \\
    \exit{let} \space \text{ident} = [\text{expr}]
    \end{cases}
    \\
    \text{expr} &\to 
    \begin{cases}
    \text{int\_literal}\\ \space
    \text{ident}
    \end{cases}

\end{align}
$$
