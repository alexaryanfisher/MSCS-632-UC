% Family Tree

% Family relationships using facts

% Parents
parent(rich, will).
parent(thim, will).
parent(sam, lex).
parent(kim, lex).
parent(sam, ash).
parent(kim, ash).
parent(will, hayd).
parent(will, my).
parent(will, syd).
parent(will, rj).
parent(lex, hayd).
parent(lex, my).
parent(lex, syd).
parent(lex, rj).
parent(ash, jay).
parent(ash, mani).
parent(ash, ej).

% Gender
male(rich).
male(sam).
male(will).
male(hayd).
male(my).
male(rj).
male(jay).
male(ej).

female(thim).
female(kim).
female(lex).
female(ash).
female(syd).
female(mani).

% Marriages
married(will, lex).
married(lex, will).
married(sam, kim).
married(kim, sam).
married(rich, thim).
married(thim, rich).

% Derive relationships using rules

% Grandparents (recursive)
grandparent(X, Y) :-
    parent(X, P), % X is a parent of P
    parent(P, Y). % P is a parent of Y

% Siblings
siblings(X, Y) :-
    parent(P, X), % X has parent of P
    parent(P, Y), % Y has parent of P
    X \= Y. % X and Y are not the same person

% Cousins
cousins(X, Y) :-
    parent(P1, X), % P1 is a parent of X
    parent(P2, Y), % P2 is a parent of Y
    siblings(P1, P2). % P1 and P2 are siblings.

% Descendants
descendant(X, Y) :-
    parent(Y, X). % Y is a parent of X
descendant(X, Y) :-
    parent(Z, X), % Z is a parent of X
    descendant(Z, Y). % Z is a descendant of Y

% Queries

% Children of a person
children(P, C) :-
    parent(P, C).

% All descendants of a person
descendants(P, D) :-
    descendant(D, P).

% Spouse of a person
spouse(X, Y) :-
    married(X, Y).