\ENCODING=ISO-8859-1
\Problem name: IloCplex

Maximize
 obj: 500 u1 + 180 v1 + 150 v2 + 350 v3 + 320 v4 + 300 u2 + 200 u3 + x8
Subject To
 c1:  u1 + v1 <= 12
 c2:  u1 + v2 <= 10
 c3:  u1 + v3 <= 12
 c4:  u1 + v4 <= 13
 c5:  v1 + u2 <= 7
 c6:  v2 + u2 <= 11
 c7:  v3 + u2 <= 8
 c8:  v4 + u2 <= 14
 c9:  v1 + u3 <= 6
 c10: v2 + u3 <= 16
 c11: v3 + u3 <= 11
 c12: v4 + u3 <= 7
Bounds
      x8 = 0
End
