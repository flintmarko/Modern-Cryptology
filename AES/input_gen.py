import numpy as np 
import random
import sympy as sp
from numpy.linalg import matrix_rank
np.set_printoptions(threshold=np.inf)
from pyfinite import ffield

#Dictionaries
dct = {'f' : [0,0,0,0],
 'g' : [0,0,0,1],
 'h' : [0,0,1,0],
 'i' : [0,0,1,1],
 'j' : [0,1,0,0],
 'k' : [0,1,0,1],
 'l' : [0,1,1,0],
 'm' : [0,1,1,1],
 'n' : [1,0,0,0],
 'o' : [1,0,0,1],
 'p' : [1,0,1,0],
 'q' : [1,0,1,1],
 'r' : [1,1,0,0],
 's' : [1,1,0,1],
 't' : [1,1,1,0],
 'u' : [1,1,1,1]}

inv_dict = { '0000': 'f',
 '0001': 'g',
 '0010': 'h',
 '0011': 'i',
 '0100': 'j',
 '0101': 'k',
 '0110': 'l',
 '0111': 'm',
 '1000': 'n',
 '1001': 'o',
 '1010': 'p',
 '1011': 'q',
 '1100': 'r',
 '1101': 's',
 '1110': 't',
 '1111': 'u'}

 #It converts byte to corresponding two charachters
def byte_str(b):
    binnum = '{:0>8}'.format(format(b,"b"))
    a = inv_dict[binnum[0:4]], inv_dict[binnum[4:8]]
    return a[0]+a[1]

#It maps set of two charachters(byte) to it's corresponding hex value
def map_to_str(st):
    char = chr(16*(ord(st[0]) - ord('f')) + ord(st[1]) - ord('f'))
    return char

#It takes full block of ip eg 'fffffffffffffffg' and outputs corresponding hex list
def block_to_byte(c):
    plainText = ""
    for i in range(0, len(c), 2):
        plainText += map_to_str(c[i:i+2])
    return plainText

#It contains all the required functions for reuse
#Add, Multiply,Expo, addVectors, scalarMultiplication, LinearTransformation
exp_store = [[-1]*128 for i in range(128)]
F = ffield.FField(7)

def Add (n1, n2):
    return int(n1) ^ int(n2)

def Multiply (n1, n2):
    return F.Multiply(n1, n2)

def Expo (no, pow):
    if exp_store[no][pow] != -1:
        return exp_store[no][pow]

    result = 0;
    if pow == 0:
        result = 1
    elif pow == 1:
        result = no
    elif pow%2 == 0:
        sqrt_no = Expo(no, pow>>1)
        result = Multiply(sqrt_no, sqrt_no)
    else:
        sqrt_no = Expo(no, pow>>1)
        result = Multiply(sqrt_no, sqrt_no)
        result = Multiply(no, result)

    exp_store[no][pow] = result
    return result

def addVectors (v1, v2):
    result = [0]*8
    for i, (e1, e2) in enumerate(zip(v1, v2)):
        result[i] = Add(e1, e2)
    return result

def scalarMultiplication (v, elem):
    result = [0]*8
    for i, e in enumerate(v):
        result[i] = Multiply(e, elem)
    return result

def LinearTransformation (mat, elist):
    result = [0]*8
    for row, elem in zip(mat, elist):
        result = addVectors(scalarMultiplication(row, elem), result)
    return result

#This list will consist of all possible exponents
poss_exp = [[] for i in range(8)]
#This list will consist of all possible diagonal values
poss_aii = [[[] for i in range(8)] for j in range(8)]
input_file = open("inputs_clean.txt", 'r')
output_file = open("outputs_clean.txt", 'r')
for ind, (iline, oline) in enumerate(zip(input_file.readlines(), output_file.readlines())):
    inpString = []
    outString = []
    #Converting each input to corresponding hex values
    for hexi in iline.strip().split(" "):
        #print(hexi)
        inpString.append(block_to_byte(hexi)[ind])
    for hexo in oline.strip().split(" "):
        outString.append(block_to_byte(hexo)[ind])
        
    for i in range(1, 127):
        for j in range(1, 128):
            flag = True
            for inps, outs in zip(inpString, outString):
                #We iterate over all possible values of ei and ajj to check if input maps to output
                if ord(outs) != Expo(Multiply(Expo(Multiply(Expo(ord(inps), i), j), i), j), i):
                    flag = False
                    break
            if flag:
                #If yes, then we append them to corresponding possible lists
                poss_exp[ind].append(i)
                poss_aii[ind][ind].append(j)

print(poss_aii)

print(poss_exp)


input_file = open("inputs_clean.txt", 'r')
output_file = open("outputs_clean.txt", 'r')
for ind, (iline, oline) in enumerate(zip(input_file.readlines(), output_file.readlines())):
    #Considering only first 6 pairs
    if ind > 6 :
        break
    inpString = []
    outString = []
    #Converting each input to corresponding hex values
    for hexi in iline.strip().split(" "):
        inpString.append(block_to_byte(hexi)[ind]) 
    for hexo in oline.strip().split(" "):
        outString.append(block_to_byte(hexo)[ind+1])
    for i in range(1, 128):
        #We iterate over all possible pairs of exponents and diagonal values
        for p1, e1 in zip(poss_exp[ind+1], poss_aii[ind+1][ind+1]):
            for p2, e2 in zip(poss_exp[ind], poss_aii[ind][ind]):
                flag = True
                for inp, outp in zip(inpString, outString):
                    #We substitute the pairs ad=nd iterate over all possible values of i
                    #We do this by forming virtual triangle (aii,aij,ajj)
                    if ord(outp) != Expo(Add(Multiply(Expo(Multiply(Expo(ord(inp), p2), e2), p2), i) ,Multiply(Expo(Multiply(Expo(ord(inp), p2), i), p1), e1)), p1):
                        flag = False
                        break
                if flag:
                    #If we find such value, then we can discard other possibilities and finalize the lists
                    poss_exp[ind+1] = [p1]
                    poss_aii[ind+1][ind+1] = [e1]
                    poss_exp[ind] = [p2]
                    poss_aii[ind][ind] = [e2]
                    poss_aii[ind][ind+1] = [i]

print()
print()

print(poss_aii)
print(poss_exp)

#This function mimics EAEAE
def EAEAE (plaintext, lin_mat, exp_mat):
    plaintext = [ord(c) for c in plaintext]
    Output = [[0 for j in range (8)] for i in range(8)]
    for ind, elem in enumerate(plaintext):
        Output[0][ind] = Expo(elem, exp_mat[ind])

    Output[1] = LinearTransformation(lin_mat, Output[0])

    for ind, elem in enumerate(Output[1]):
        Output[2][ind] = Expo(elem, exp_mat[ind])

    Output[3] = LinearTransformation(lin_mat, Output[2])

    for ind, elem in enumerate(Output[3]):
        Output[4][ind] = Expo(elem, exp_mat[ind])
    return Output[4]

for index in range(6):
    #As we have already found element next to diagonal thus skipping two elements every time
    of = index + 2
    
    exp_list = [e[0] for e in poss_exp]
    A = [[0 for i in range(8)] for j in range(8)]
  
    #We fill all the empty [] elements with 0
    for i in range(8):
        for j in range(8):
            A[i][j] = 0 if len(poss_aii[i][j]) == 0 else poss_aii[i][j][0]
    print(exp_list)
    print(A) 
    inp = open("inputs_clean.txt", 'r')
    out = open("outputs_clean.txt", 'r')
    for ind, (iline, oline) in enumerate(zip(inp.readlines(), out.readlines())):
        print(ind)
        print(iline)
        print(oline)
        if ind > (7-of):
            continue
        print(iline)
        inpString = [block_to_byte(msg) for msg in iline.strip().split(" ")]
        outString = [block_to_byte(msg) for msg in oline.strip().split(" ")]
        #We iterate over all possible values of ai,j to find which one satisfies EAEAE = Output
        for i in range(1, 128):
            A[ind][ind+of] = i
            flag = True
            for inps, outs in zip(inpString, outString):
                if EAEAE(inps, A, exp_list)[ind+of] != ord(outs[ind+of]):
                    flag = False
                    break
            if flag:
                poss_aii[ind][ind+of] = [i]
    inp.close();
    out.close();
#We fill all the empty [] elements with 0
A = [[0 for i in range(8)] for j in range(8)]
for i in range(8):
    for j in range(8):
        A[i][j] = 0 if len(poss_aii[i][j]) == 0 else poss_aii[i][j][0]

print()
print()
print(A)
print(exp_list)

LINEAR_MATRIX = [[84, 112, 19, 98, 110, 31, 2, 68], [0, 70, 30, 20, 62, 47, 123, 2], [0, 0, 43, 4, 1, 30, 9, 74], [0, 0, 0, 12, 118, 53, 103, 27], [0, 0, 0, 0, 112, 99, 29, 20], [0, 0, 0, 0, 0, 11, 92, 68], [0, 0, 0, 0, 0, 0, 27, 3], [0, 0, 0, 0, 0, 0, 0, 38]]
EXPONENT_MATRIX = [22, 113, 38, 73, 88, 48, 19, 26]

#Two halves of password
password_1 = "gskfgngjfumqjokp"
password_2 = "hllogkirjrlffufh"

#We iterate over all possible 128 byte values and perform EAEAE to check for which input the password (half) matches
def DecryptPassword(password):
    passw = block_to_byte(password)
    op = ""
    for ind in range(8):
        for ans in range(128):
            inp = op + byte_str(ans)+(16-len(op)-2)*'f'
            if ord(passw[ind]) == EAEAE(block_to_byte(inp), LINEAR_MATRIX, EXPONENT_MATRIX)[ind]:
                op += byte_str(ans)
                break
    return op


print((DecryptPassword(password_1))+(DecryptPassword(password_2)))


print(block_to_byte(DecryptPassword(password_1))+block_to_byte(DecryptPassword(password_2)))