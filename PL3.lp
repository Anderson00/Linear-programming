\ENCODING=ISO-8859-1
\Problem name: IloCplex

Minimize
 obj: 8 x1 + 6 x2 + 10 x3 + 9 x4 + 9 x5 + 12 x6 + 13 x7 + 7 x8 + 14 x9 + 9 x10
      + 16 x11 + 5 x12 + x13
Subject To
 c1: x1 + x2 + x3 + x4 <= 30
 c2: x5 + x6 + x7 + x8 <= 50
 c3: x9 + x10 + x11 + x12 <= 40
 c4: x1 + x5 + x9 >= 45
 c5: x2 + x6 + x10 >= 20
 c6: x3 + x7 + x11 >= 30
 c7: x4 + x8 + x12 >= 30
Bounds
      x13 = 0
End
