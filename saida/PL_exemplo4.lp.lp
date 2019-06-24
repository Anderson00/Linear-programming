\ENCODING=ISO-8859-1
\Problem name: IloCplex

Minimize
 obj: 12 x1 + 10 x2 + 12 x3 + 13 x4 + 7 x5 + 11 x6 + 8 x7 + 14 x8 + 6 x9
      + 16 x10 + 11 x11 + 7 x12 + x13
Subject To
 c1: x1 + x2 + x3 + x4 <= 500
 c2: x5 + x6 + x7 + x8 <= 300
 c3: x9 + x10 + x11 + x12 <= 200
 c4: x1 + x5 + x9 >= 180
 c5: x2 + x6 + x10 >= 150
 c6: x3 + x7 + x11 >= 350
 c7: x4 + x8 + x12 >= 320
Bounds
      x13 = 0
End
