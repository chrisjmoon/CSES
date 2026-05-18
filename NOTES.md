# Containers

unordered_set
    average time complexity O(1)
    worst time complexity O(n)
    vulnerable to hash collision

set
    red-black tree (balanced BST)
    average time complexity O(log n)
    worst time complexity O(log n)
    stable performance consistency

multiset
    - associative container (elements referred to by keys, used to query membership, as opposed to indices)
    - set with duplicates
    - implemented using red-black tree
    - insertion, removal, search have logarithmic complexity
    - supports lower/upper_bound
        - cannot grab the index using ms.upper_bound(x) - ms.begin() | vectors use random-access iterators (like pointers); multiset and set use bidirectional iterators which support ++it and --it but not it2 - it1

# Methods

lower_bound
    - first index such that insertion will not violate sorted order
upper_bound
    - first index such that insertion will not violate sorted order after any instance of element

# Statistics

Given a set of numbers x[], argmin_t |x_i - t| is when t = median(x)


# Maximum Flow

**26.1.1** Denote $G$ the graph over $V$ and $E$. Let $V' = V \cup \{x\}$, $E' = E \setminus \{(u, v)\} \cup \{(u, x), (x, v)\}$, and $G'$ the graph over $V'$ and $E'$. Suppose $f: V \times V \rightarrow \mathbb{R}$ is a flow with maximal $|f|$ and $f': V' \times V' \rightarrow \mathbb{R}$ is a flow with maximal $|f'|$. We will show that $|f| = |f'|$. Note that $|f|$ is defined as the sum of the flow $f$ on all pairs $(s, w)$ such that $(s, w) \in E$ or in other words, $f = \sum_{w \in N_G(s)} f(s, w)$ where $N_G(s) = \{w \in V | (s, w) \in E\}$.

Suppose $s \neq u$. Then $|f'| = \sum_{w \in N_{G'}(s)} f'(s, w) = \sum_{w \in N_G(s)} f'(s, w) + f'(s, v) = \sum_{w \in N_G(s)} f'(s, w)$. By definition, since $f'$ is maximal over this sum, $|f'| = |f|$.

Suppose $s = u$ and define $f'': V \times V \rightarrow E$ such that $f'' = f'|_{V \setminus \{v\}}$ and $f''(s, v) = f'(s, x), f''(s, x) = 0$. In other words, we define a new flow that takes $f'$ and redirects all of its flow from $s$ to $x$ to $s$ to $v$. Such a flow satisfies constraints as $c''(s, v) = c'(s, x)$. Thus, $|f'| = \sum_{w \in N_{G'}(s)} f'(s, w) = \sum_{w \in N_G(s) \setminus \{v\}} f'(s, w) + f'(s, x) + f'(s, v) = \sum_{w \in N_G(s) \setminus \{v\}} f''(s, w) + f''(s, v) = \sum_{w \in N_G(s)} f''(s, w)$ where the second to last equality is derived from $f'' = f'|_{V \setminus \{v\}}$, $f'(s, v) = 0$, and $f''(s, v) = f'(s, x)$. Therefore, $|f'| = |f''|$ and because $f''$ is maximal over $N_G(s)$, $|f''| = |f|$ and thus, $|f'| = |f|$.

**26.1.2** Let $G$ be a multiple-source and multiple-sink network over vertices $V$ and edges $E$ with sources $S$ and sinks $T$. By convention, we are assuming that sources do not have incoming edges and sinks do not have outgoing edges. We similarly define a flow $f: V \times V \rightarrow \mathbb{R}$ that satisfy the properties $0 \leq f(u, v) \leq c(u, v)$ and $\sum_{v \in V} f(v, u) = \sum_{v \in V} f(u, v)$ for all $u$ in $V \setminus (S \cup T)$. We define the value of $f$ as $|f| = \sum_{s \in S} \sum_{v \in V} f(s, v)$ where $S$ is the set of sources.

Construct $G'$ from a multiple-source, multiple-sink network $G$ by adding a supersource $s'$ and supersink $t'$ such that $V' = V \cup \{s', t'\}$ and $E' = E \cup \{(s', s) | s \in S\} \cup \{(t, t') | t \in T\}$ with constraints $c'(s', s) = c'(t, t') = \infty$ for all $s \in S$ and $t \in T$.

For any flow $f'$ on $G'$, we construct a flow $f$ on $G$ such that $f = f'|_E$. Note that $f$ satisfies the constraints of the flow network automatically and that the inflow of $u$ is equal to the outflow of $u$ already for all $u \not \in S \cup T$. Further, we can see that any such $f'$ has $|f'| = |f|$ as $$|f'| = \sum_{s \in S} f'(s', s) = \sum_{s \in S} \sum_{v \in V'} f'(s, v)$$ by conservation of flow and $$\sum_{s \in S} \sum_{v \in V'} f'(s, v) = \sum_{s \in S} \sum_{v \in V} f'(s, v)$$ because $(s, s') \not \in E'$ for any $s \in S$ and $$\sum_{s \in S} \sum_{v \in V} f'(s, v) = \sum_{s \in S} \sum_{v \in V} f(s, v) = |f|$$ as $f'|_E = f$.

For any flow $f$ on $G$, we construct a flow $f'$ on $G'$ such that $f'|_E = f$ and $f'(s', s) = \sum_{v \in V} f(s, v)$ for all $s \in S$ and $f'(t, t') = \sum_{v \in V} f(v, t)$ for all $t \in T$. Note that $f'$ satisfies the constraints of the flow as $f'(s', s) < \infty$ for all $s \in S$, $f'(t, t') < \infty$ for all $t \in T$ and by construction, the outflow of $u$ is equal to the inflow of $u$ for all $u \in S \cup T$. Further, $$|f'| = \sum_{s \in S} f'(s', s) = \sum_{s \in S} \sum_{v \in V} f(s, v) = |f|$$ where the second equality is by definition of $f'$. Since the correspondence preserves flow value in both directions, we conclude that the maximum flow for $G$ is equal to the maximum flow for $G'$.

**26.1.3** **Lemma:** Let $G$ be a flow network over vertex set $V$ and edge set $E$. Let $Q, R$ partition $V$ such that $Q \cup R = V$ and $Q \cap R = \empty$ and define $f(Q, R) = \sum_{q \in Q, r \in R} f(q, r)$. Then $f(Q, R) = f(R, Q)$.

Proof: Let us induct on the size of $R$. Suppose the statement holds for $R$ and consider $w \in Q \setminus \{s, t\}$. We will show that $f(Q \setminus \{w\}, R \cup \{w\}) = f(R \cup \{w\}, Q \setminus \{w\})$. We have $f(Q \setminus \{w\}, R \cup \{w\}) = f(Q, R) - f(w, R) + f(Q, w)$ where $f(w, R)$ is defined as $f(\{w\}, R)$ and likewise $f(Q, w) = f(Q, \{w\})$. Further, $f(R \cup \{w\}, Q \setminus \{w\}) = f(R, Q) + f(w, Q) - f(R, w)$. It remains to see that $f(w, Q) - f(R, w) = f(Q, w) - f(w, R)$. By conservation of flow, the inflow of $w$ must equal its outflow, or in other words, $\sum_{v \in V} f(v, w) = \sum_{v \in Q} f(v, w) + \sum_{v \in R} f(v, w) = \sum_{v \in V} f(w, v) = \sum_{v \in Q} f(w, v) + \sum_{v \in R} f(w, v)$. That is, $f(Q, w) + f(R, w) = f(w, Q) + f(w, R)$ or $f(w, Q) - f(R, w) = f(Q, w) - f(w, R)$. Therefore, with the inductive hypothesis showing that $f(Q, R) = f(R, Q)$, we have $f(Q \setminus \{w\}, R \cup \{w\}) = f(Q, R) - f(w, R) + f(Q, w) = f(R, Q) + f(w, Q) - f(R, w) = f(R \cup \{w\}, Q \setminus \{w\})$.

If we assume $s \rightarrow t$, then $t \in Q$, so $t \notin R$. Since also $s \notin R$, every vertex in $R$ satisfies conservation of flow. Summing conservation over all vertices in $R$, we get
$$
f(Q,R)+f(R,R)=f(R,Q)+f(R,R).
$$
Thus, $f(Q,R)=f(R,Q)$. Since $f(Q,R)=0$, we also have $f(R,Q)=0$. Because flow values are nonnegative, this means every edge from $R$ to $Q$ carries zero flow.

We will use this fact to show that for a maximal flow $f$, the function $f'$ defined by
$$
f'(a,b)=
\begin{cases}
f(a,b), & a,b\in Q,\\
0, & \text{otherwise}
\end{cases}
$$
is a valid flow and satisfies $|f'|=|f|$. Equivalently, $f'$ agrees with $f$ on $Q\times Q$, and sets all flow involving vertices in $R$ to zero.

First, $f'$ satisfies the capacity constraints. Indeed, whenever $f'(a,b)=f(a,b)$, the capacity constraint follows from the capacity constraint for $f$. Whenever $f'(a,b)=0$, the capacity constraint is automatic.

Now we show that $f'$ satisfies conservation of flow. Let $q\in Q\setminus\{s,t\}$. Since there are no edges from $Q$ to $R$, we have $f(q,R)=0$. Also, as shown above, $f(R,Q)=0$, so in particular $f(R,q)=0$. Therefore,
$$
f(V,q)=f(Q,q)+f(R,q)=f(Q,q)
$$
and
$$
f(q,V)=f(q,Q)+f(q,R)=f(q,Q).
$$
By conservation for $f$, $f(V,q)=f(q,V)$, and hence $f(Q,q)=f(q,Q)$. By construction, $f'$ agrees with $f$ on $Q\times Q$ and is zero on all edges involving $R$, so $f'(V,q)=f'(Q,q)=f(Q,q)$ and $f'(q,V)=f'(q,Q)=f(q,Q)$. Therefore, $f'(V,q)=f'(q,V)$. So conservation holds for all ordinary vertices in $Q$.

Now let $r\in R$. By construction, all flow into and out of $r$ has been set to zero. Therefore, $f'(V,r)=0$ and $f'(r,V)=0$. Thus, $f'(V,r)=f'(r,V)$, so conservation also holds for all vertices in $R$. Therefore, $f'$ is a valid flow.

Finally, we show that $|f'|=|f|$. Since $s\in Q$ and there are no edges from $Q$ to $R$, we have $f(s,V)=f(s,Q)+f(s,R)=f(s,Q)$. Similarly, $f'(s,V)=f'(s,Q)+f'(s,R)=f'(s,Q)$. Because $f'$ agrees with $f$ on $Q\times Q$, we have $f'(s,Q)=f(s,Q)$. Therefore,
$$
|f'|=f'(s,V)=f'(s,Q)=f(s,Q)=f(s,V)=|f|.
$$

Thus, when $s\nrightarrow u$, we can zero out the unreachable region $R$ and obtain a valid flow $f'$ with the same value as $f$.

**26.1.7** To construct a corresponding network with vertex capacity, first construct a graph $G'$ such that for each edge $e = (u, v) \in E$, we construct a vertex $x_e$ with edges $(u, x_e), (x_e, v)$ replacing $(u, v)$. That is, $V' = V \cup \{x_e | e \in E\}$ and $E' = \cup_{e \in E} \{(u, x_e), (x_e, v)\}$. By 26.1.1, we can define an equivalent flow $f'$ on $G'$ from a flow $f$ on $G$. Now let us define a vertex capacity network $G''$ from $G'$ such that $l(x_e) = c(u, v)$ for all $e = (u, v) \in E$, $l(u) = min(\sum_{v \in V} c(v, u), \sum_{v \in V} c(u, v))$ for all $u \in V' \setminus \{s, t\}$. It remains to show that a flow $f'$ on $G'$ is in fact a flow on $G''$ by showing that $\sum_{v \in V'} f'(v, u) = \sum_{v \in V'} f'(u, v) \leq l(u)$ for all $u \in V \setminus \{s, t\}$. This is straightforward as $\sum_{v \in V'} f'(u, v) \leq \sum_{v \in V'} c(u, v)$ and $\sum_{v \in V'} f'(v, u) \leq \sum_{v \in V'} c(v, u)$, and through conservation of flow, $\sum_{v \in V'} f'(u, v) = \sum_{v \in V'} f'(v, u) \leq \min(\sum_{v \in V'} c(v, u), \sum_{v \in V'} c(u, v)) = l(u)$. For $x_e$ where $e = (u, v) \in E$, then $\sum_{w \in V'} f'(w, x_e) = f'(u, x_e) \leq c(u, x_e) = c(u, v) = l(u)$ and $\sum_{w \in V'} f'(x_e, w) = f'(x_e, v) \leq c(x_e, v) = c(u, v) = l(u)$. We conclude that $f'$ is a flow on the vertex capacity network of $G''$ and by 26.1.1, $|f'| = |f|$.

By construction, the vertex capacity equivalent network has $|V'| = |V| + |E|$ and $|E'| = 2|E|$.