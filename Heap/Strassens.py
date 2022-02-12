# Splits a given matrix into quarters of n/2 x n/2.
def Split(matrix):
	row, col = matrix.shape
	row2, col2 = row//2, col//2
	return matrix[:row2, :col2], matrix[:row2, col2:], matrix[row2:, :col2], matrix[row2:, col2:]


def multiply(a, b):
    for i=0 to N-1
        for j=0 to N-1
            c[i, j] = 0
            for k=0 to N
                c[i][j] += a[i, k]*b[k, j]
    return c


function multiply(x, y)
	// Base case when size of matrices is 1x1
	if Size(x) = 1
		return x * y

	// Splitting the matrices into 4 quadrants. 
	// This will be done recursively until the base case is reached.
	a, b, c, d = Split(x)
	e, f, g, h = Split(y)

    A = multiply(a)
    B = multiply(b)
    C = multiply(c)
    D = multiply(d)
    E = multiply(e)
    F = multiply(f)
    G = multiply(g)
	H = multiply(h)

	// Computing the values of the 4 quadrants of the output matrix c
	c11 = A*E + B*G
	c12 = A*F + B*H
	c21 = C*E + D*G
	c22 = C*F + D*H

	// Combining the 4 quadrants into a single output matrix.
	c = Combine(c11, c12, c21, c22)
	return c

def Strassen(x, y):

	# Base case when size of matrices is 1x1
	if Size(x) = 1:
		return x * y

	# Splitting the matrices into quadrants. This will be done recursively
	# until the base case is reached.
	a, b, c, d = Split(x)
	e, f, g, h = Split(y)

	# Computing the 7 products, recursively (p1, p2...p7)
	m1 = Strassen(a, f - h)
	m2 = Strassen(a + b, h)	
	m3 = Strassen(c + d, e)	
	m4 = Strassen(d, g - e)	
	m5 = Strassen(a + d, e + h)	
	m6 = Strassen(b - d, g + h)
	m7 = Strassen(a - c, e + f)

	# Computing the values of the 4 quadrants of the final matrix c
	c11 = m5 + m4 - m2 + m6
	c12 = m1 + m2		
	c21 = m3 + m4		
	c22 = m1 + m5 - m3 - m7

	# Combining the 4 quadrants into a single matrix by stacking horizontally and vertically.
	c = Combine(c11, c12, c21, c22)

	return c
