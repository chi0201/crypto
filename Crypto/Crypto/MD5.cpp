//#include "MD5.h"
//
////Note: All variables are unsigned 32 bits and wrap modulo 2^32 when calculating
//var int[64] r, k
////r specifies the per-round shift amounts
//r[ 0..15] := {7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22}
//r[16..31] := {5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20}
//r[32..47] := {4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23}
//r[48..63] := {6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21}
////Use binary integer part of the sines of integers (Radians) as constants:
//for i from 0 to 63
//    k[i] := floor(abs(sin(i + 1)) � (2 pow 32))
////Initialize variables:
//var int h0 := 0x67452301
//var int h1 := 0xEFCDAB89
//var int h2 := 0x98BADCFE
//var int h3 := 0x10325476
////Pre-processing:
//append "1" bit to message
//append "0" bits until message length in bits = 448 (mod 512)
//append bit /* bit, not byte */ length of unpadded message as 64-bit little-endian integer to message
////Process the message in successive 512-bit chunks:
//for each 512-bit chunk of message
//    break chunk into sixteen 32-bit little-endian words w[j], 0 = j = 15
//    //Initialize hash value for this chunk:
//    var int a := h0
//    var int b := h1
//    var int c := h2
//    var int d := h3
//    //Main loop:
//    for i from 0 to 63
//        if 0 = i = 15 then
//            f := (b and c) or ((not b) and d)
//            g := i
//        else if 16 = i = 31
//            f := (d and b) or ((not d) and c)
//            g := (5�i + 1) mod 16
//        else if 32 = i = 47
//            f := b xor c xor d
//            g := (3�i + 5) mod 16
//        else if 48 = i = 63
//            f := c xor (b or (not d))
//            g := (7�i) mod 16
//        temp := d
//        d := c
//        c := b
//        b := b + leftrotate((a + f + k[i] + w[g]) , r[i])
//        a := temp
//    //Add this chunk's hash to result so far:
//    h0 := h0 + a
//    h1 := h1 + b
//    h2 := h2 + c
//    h3 := h3 + d
//var char digest[16] := h0 append h1 append h2 append h3 //(expressed as little-endian)
//  //leftrotate function definition
//  leftrotate (x, c)
//      return (x << c) or (x >> (32-c));
//Note: Instead of the formulation from the original RFC 1321 shown, the following may be used for improved efficiency (useful if assembly language is being used - otherwise, the compiler will generally optimize the above code. Since each computation is dependent on another in these formulations, this is often slower than the above method where the nand/and can be parallelised):
//(0  = i = 15): f := d xor (b and (c xor d))
//(16 = i = 31): f := c xor (d and (b xor c))