/* include/llvm/Support/DataTypes.h. Generated from DataTypes.h.in by configure. */
2 /*===-- include/Support/DataTypes.h - Define fixed size types -----*- C -*-===*\
3 |* *|
4 |* The LLVM Compiler Infrastructure *|
5 |* *|
6 |* This file is distributed under the University of Illinois Open Source *|
7 |* License. See LICENSE.TXT for details. *|
8 |* *|
9 |*===----------------------------------------------------------------------===*|
10 |* *|
11 |* This file contains definitions to figure out the size of _HOST_ data types.*|
12 |* This file is important because different host OS's define different macros,*|
13 |* which makes portability tough. This file exports the following *|
14 |* definitions: *|
15 |* *|
16 |* [u]int(32|64)_t : typedefs for signed and unsigned 32/64 bit system types*|
17 |* [U]INT(8|16|32|64)_(MIN|MAX) : Constants for the min and max values. *|
18 |* *|
19 |* No library is required when using these functions. *|
20 |* *|
21 |*===----------------------------------------------------------------------===*/
22
23 /* Please leave this file C-compatible. */
24
25 /* Please keep this file in sync with DataTypes.h.cmake */
26
27 #ifndef SUPPORT_DATATYPES_H
28 #define SUPPORT_DATATYPES_H
29
30 #define HAVE_INTTYPES_H 1
31 #define HAVE_STDINT_H 1
32 #define HAVE_UINT64_T 1
33 /* #undef HAVE_U_INT64_T */
34
35 #ifdef __cplusplus
36 #include <cmath>
37 #else
38 #include <math.h>
39 #endif
40
41 #ifdef HAVE_INTTYPES_H
42 #include <inttypes.h>
43 #endif
44
45 #ifdef HAVE_STDINT_H
46 #include <stdint.h>
47 #else
48 #error "Compiler must provide an implementation of stdint.h"
49 #endif
50
51 #ifndef _MSC_VER
52
53 /* Note that this header's correct operation depends on __STDC_LIMIT_MACROS
54  being defined. We would define it here, but in order to prevent Bad Things
55  happening when system headers or C++ STL headers include stdint.h before we
56  define it here, we define it on the g++ command line (in Makefile.rules). */
57 #if !defined(__STDC_LIMIT_MACROS)
58 # error "Must #define __STDC_LIMIT_MACROS before #including Support/DataTypes.h"
59 #endif
60
61 #if !defined(__STDC_CONSTANT_MACROS)
62 # error "Must #define __STDC_CONSTANT_MACROS before " \
63  "#including Support/DataTypes.h"
64 #endif
65
66 /* Note that <inttypes.h> includes <stdint.h>, if this is a C99 system. */
67 #include <sys/types.h>
68
69 #ifdef _AIX
70 #include "llvm/Support/AIXDataTypesFix.h"
71 #endif
72
73 /* Handle incorrect definition of uint64_t as u_int64_t */
74 #ifndef HAVE_UINT64_T
75 #ifdef HAVE_U_INT64_T
76 typedef u_int64_t uint64_t;
77 #else
78 # error "Don't have a definition for uint64_t on this platform"
79 #endif
80 #endif
81
82 #else /* _MSC_VER */
83 #include <stdlib.h>
84 #include <stddef.h>
85 #include <sys/types.h>
86 #ifdef __cplusplus
87 #include <cmath>
88 #else
89 #include <math.h>
90 #endif
91
92 #if defined(_WIN64)
93 typedef signed __int64 ssize_t;
94 #else
95 typedef signed int ssize_t;
96 #endif /* _WIN64 */
97
98 #ifndef HAVE_INTTYPES_H
99 #define PRId64 "I64d"
100 #define PRIi64 "I64i"
101 #define PRIo64 "I64o"
102 #define PRIu64 "I64u"
103 #define PRIx64 "I64x"
104 #define PRIX64 "I64X"
105 #endif /* HAVE_INTTYPES_H */
106
107 #endif /* _MSC_VER */
108
109 /* Set defaults for constants which we cannot find. */
110 #if !defined(INT64_MAX)
111 # define INT64_MAX 9223372036854775807LL
112 #endif
113 #if !defined(INT64_MIN)
114 # define INT64_MIN((-INT64_MAX) - 1)
115 #endif
116 #if !defined(UINT64_MAX)
117 # define UINT64_MAX 0xffffffffffffffffULL
118 #endif
119
120 #if __GNUC__ > 3
121 #define END_WITH_NULL __attribute__((sentinel))
122 #else
123 #define END_WITH_NULL
124 #endif
125
126 #ifndef HUGE_VALF
127 #define HUGE_VALF(float)HUGE_VAL
128 #endif
129
130 #endif /* SUPPORT_DATATYPES_H */