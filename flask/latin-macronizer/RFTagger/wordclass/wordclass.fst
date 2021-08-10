
% lowercase vowels
$v$ = [aeiou���y���������������������]

% upperercase vowels
$V$ = [AEIOU���Y]

% lowercase consonants
$c$ = [bcdfghjklmnpqrstvwxz�]

% uppercase consonants
$C$ = [BCDFGHJKLMNPQRSTVWXZ]

% all lowercase letters
$l$ = [a-z�����������������������]

% all uppercase letters
$L$ = [A-Z�����]

% all letters
$x$ = $L$ | $l$

% other characters
$s$ = [$&'()*+\,./0-9:_`\%"\!\?&;()@=�\-]

% definition of the alphabet
ALPHABET = $L$ $l$ $s$

% You can modify the word class expressions below and
% add additional expressions. You can also modify the
% character class definitions above. See the SFST manual
% for information on the SFST syntax used here.

$T1$ = (\
  % numeric expressions
  [+\-]?[0-9][0-9,./:\-]* <1> |\
  % capitalized words
  $L$ .* <2> |\
  % lower-case words
  $l$ .* <3>)

$X1$ = $T1$

$X1$
