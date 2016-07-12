# study-no-2

The subset sum problem is a famous NP-complete decision problem, concerned with finding a non-empty subset from a set of numbers that sums to a target value. For example, we might ask whether a subset of the numbers in {-1, 2, -3, 4} sums to 0. The answer would be affirmative, given the subset {-1, -3, 4}.

NP-complete problems are those at the intersection of the NP and NP-hard complexity classes. The class NP contains all decision problems whose solutions are *verifiable* in polynomial time. The subclass P are those problems that are also known to be *solvable* in polynomial time on a *deterministic Turing machine* or classical computer. Polynomial time refers to algorithms whose run time is polynomial in the size of the problem, where size typically refers to the number of variables. Such problems are said to be *tractable*, having efficient solution algorithms. On the other hand, *intractable* problems are those whose algorithms require computation exponential in the size of the problem. The famous unresolved question of P vs. NP refers to whether all problems whose solution may be verified in polynomial time have (possibly undiscovered) polynomial-time algorithms (P = NP), or whether some are inherently intractable (P != NP). The latter is widely considered to be far more likely.

Note that NP does not stand for "non-polynomial" time (that would, ironically, be begging the question), but rather *non-deterministic polynomial time*, meaning algorithms that run in polynomial time on a *non-deterministic Turing machine* (NTM). A NTM is a hypothetical variant of Turing machine for which multiple instructions can be executed simultaneously. Such a machine would therefore be capable of checking all alternative solutions at the same time, rendering exponential solution spaces traversable in polynomial time. To illustrate, consider our subset sum example. An exhaustive search considers all possible inclusions and exclusions for the subset. This can be viewed as a binary tree,

<pre>
                with -1                                     without -1
            /               \                           /               \
        with 2              without 2               with 2              without 2
        /   \               /   \                   /   \               /   \
    w -3    w/o -3      w -3    w/o -3          w -3    w/o -3      w -3    w/o -3
    /   |   |   \       /   |   |   \           /   |   |   \       /   |   |   \
w 4  w/o 4 w 4 w/o 4 w 4  w/o 4 w 4 w/o 4   w 4  w/o 4 w 4 w/o 4 w 4  w/o 4 w 4 w/o 4
</pre>

A NTM would be capable of "guessing" each alternative simultaneously, traversing the tree and finding the solution in linear time. Thus, solving a problem on a NTM requires the same effort as *verifying* a solution on a determinstic Turing machine. Now it may be seen that NP is really just a formal way of talking about verification complexity.

As previously stated, NP-complete problems are both NP and NP-hard. As a member of NP, they are verifiable in polynomial time. NP-hard is the class of problems that are *at least as hard as the hardest NP problems*, i.e. NP-complete problems. More precisely, this means all problems in NP can be reduced in polynomial time to any NP-hard problem. Reducing one problem to another means to map the problems in such a way that one problem can be used to solve the other, in the form of an algorithm sub-routine or *oracle*. In sum, NP-complete problems are those NP-hard problems whose solutions may be verified efficiently. They are all within a polynomial-time reduction of each other, but it is not known if polynomial-time algorithms exist to solve them. Discovering an efficient algorithm for any one NP-complete problem would collapse the whole class, implying P = NP and the existence of efficient algorithms for all NP problems.

To prove the NP-completeness of a problem, it is necessary to,

1. Show it is in NP, by showing its solutions may be efficiently verified
2. Show it is NP-hard, by showing it can be efficiently reduced to another known NP-complete problem.

The first decision problem proved to be NP-complete is the boolean satisfiability problem or SAT (see the Cook-Levin theorem, 1971), which aims to find a combination of values for literals in a boolean expression such that the overall expression evaluates TRUE. The expression is taken to be in conjunctive normal form (a conjunction of disjunctions or an AND of ORs), for example,

<pre>
(X1 OR X2 OR ... OR XN) AND (NOT X1 OR ...) AND ...
</pre>

There are some special cases of SAT where computation is easy, for example if each variable features in exactly one clause, but in general, no efficient algorithm is known to exist. From a purely intuitive perspective, the task lends itself to an exponential runtime, as there are 2^N possible interpretations of the expression for N variables. Until P vs. NP is resolved, it is not known whether there is a reliable shortcut. Richard Karp used this result to find and categorise 21 NP-complete problems, beginning with the 3SAT problem, a variant of SAT in which all clauses contain three literals. It is easy to transform a CNF expression to the 3SAT form, with the introduction of dummy variables. The expression loses logical equivalency, but retains equisatisfiability, meaning that solutions in the 3SAT form are necessary and sufficient for solutions in the original form. The length of the expression triples, hence the reduction step is polynomial. Karp's 21 NP-complete problems further include problems from graph theory (such as clique selection) and integer programming.

Crescenzi and Kann (2011) provide a <a href="https://encrypted.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=1&cad=rja&uact=8&ved=0ahUKEwjMucHHm-rNAhXC7RQKHTzDA4QQFggdMAA&url=http%3A%2F%2Fcs.mcgill.ca%2F~lyepre%2Fpdf%2Fassignment2-solutions%2FsubsetSumNPCompleteness.pdf&usg=AFQjCNG_ffPUQEWs6E9HEYNQl9M4tPq55g&sig2=C4A9v-Xf_SFkM_dcn-if1A" target="_blank">proof of the NP-completeness of subset sum</a> by reducing it to 3SAT. The proof consists of showing that a set of numbers and target number may be generated to encode information about each of the clauses in a 3SAT expression. Solutions to the subset sum problem then provide solutions to the 3SAT problem (and vice versa), implying subset sum is NP-complete.

SubsetSum.cpp is a C++ implementation of a dynamic programming algorithm for solving the subset sum problem. The algorithm succeeds by creating a lookup table that solves partial subset sum problems for all numbers in a feasible range, i.e. between the minimum possible subset sum, denoted A, and the maximium, B. The complexity is O(N(B - A)), and can be said to run in *pseudo-polynomial* time, since it is polynomial in N, but A and B are exponential in the precision (number of bits) of the numbers. Recall, if it were really polynomial, we would have proven P = NP (unlikely).
