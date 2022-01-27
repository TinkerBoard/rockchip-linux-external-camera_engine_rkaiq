
/* Copyright (C) 1991-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */




/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */

/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */

/*
 * Copyright (c) 2019-2022 Rockchip Eletronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */



/*
 * moduleinfo_head.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */



// #define M4_STRUCT_DESC(ALIAS, SIZE, UI_MODULE)
// #define M4_NUMBER_DESC(ALIAS, TYPE, SIZE, RANGE, DEFAULT)
// #define M4_STRING_DESC(ALIAS, SIZE, RANGE, DEFAULT)
// #define M4_ENUM_DESC(ALIAS, ENUM, DEFAULT)

/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */





/* Copyright (C) 1998-2018 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

/*
 * ISO C Standard:  7.16  Boolean type and values  <stdbool.h>
 */
/* Signal that all the definitions are present.  */
/* Copyright (C) 1997-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/*
 *	ISO C99: 7.18 Integer types <stdint.h>
 */





/* Handle feature test macros at the start of a header.
   Copyright (C) 2016-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/* This header is internal to glibc and should not be included outside
   of glibc headers.  Headers including it must define
   __GLIBC_INTERNAL_STARTING_HEADER_IMPLEMENTATION first.  This header
   cannot have multiple include guards because ISO C feature test
   macros depend on the definition of the macro when an affected
   header is included, not when the first system header is
   included.  */







/* Copyright (C) 1991-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */




/* These are defined by the user (or the compiler)
   to specify the desired environment:

   __STRICT_ANSI__	ISO Standard C.
   _ISOC99_SOURCE	Extensions to ISO C89 from ISO C99.
   _ISOC11_SOURCE	Extensions to ISO C99 from ISO C11.
   __STDC_WANT_LIB_EXT2__
			Extensions to ISO C99 from TR 27431-2:2010.
   __STDC_WANT_IEC_60559_BFP_EXT__
			Extensions to ISO C11 from TS 18661-1:2014.
   __STDC_WANT_IEC_60559_FUNCS_EXT__
			Extensions to ISO C11 from TS 18661-4:2015.
   __STDC_WANT_IEC_60559_TYPES_EXT__
			Extensions to ISO C11 from TS 18661-3:2015.

   _POSIX_SOURCE	IEEE Std 1003.1.
   _POSIX_C_SOURCE	If ==1, like _POSIX_SOURCE; if >=2 add IEEE Std 1003.2;
			if >=199309L, add IEEE Std 1003.1b-1993;
			if >=199506L, add IEEE Std 1003.1c-1995;
			if >=200112L, all of IEEE 1003.1-2004
			if >=200809L, all of IEEE 1003.1-2008
   _XOPEN_SOURCE	Includes POSIX and XPG things.  Set to 500 if
			Single Unix conformance is wanted, to 600 for the
			sixth revision, to 700 for the seventh revision.
   _XOPEN_SOURCE_EXTENDED XPG things and X/Open Unix extensions.
   _LARGEFILE_SOURCE	Some more functions for correct standard I/O.
   _LARGEFILE64_SOURCE	Additional functionality from LFS for large files.
   _FILE_OFFSET_BITS=N	Select default filesystem interface.
   _ATFILE_SOURCE	Additional *at interfaces.
   _GNU_SOURCE		All of the above, plus GNU extensions.
   _DEFAULT_SOURCE	The default set of features (taking precedence over
			__STRICT_ANSI__).

   _FORTIFY_SOURCE	Add security hardening to many library functions.
			Set to 1 or 2; 2 performs stricter checks than 1.

   _REENTRANT, _THREAD_SAFE
			Obsolete; equivalent to _POSIX_C_SOURCE=199506L.

   The -ansi switch to the GNU C compiler, and standards conformance
   options such as -std=c99, define __STRICT_ANSI__.  If none of
   these are defined, or if _DEFAULT_SOURCE is defined, the default is
   to have _POSIX_SOURCE set to one and _POSIX_C_SOURCE set to
   200809L, as well as enabling miscellaneous functions from BSD and
   SVID.  If more than one of these are defined, they accumulate.  For
   example __STRICT_ANSI__, _POSIX_SOURCE and _POSIX_C_SOURCE together
   give you ISO C, 1003.1, and 1003.2, but nothing else.

   These are defined by this file and are used by the
   header files to decide what to declare or define:

   __GLIBC_USE (F)	Define things from feature set F.  This is defined
			to 1 or 0; the subsequent macros are either defined
			or undefined, and those tests should be moved to
			__GLIBC_USE.
   __USE_ISOC11		Define ISO C11 things.
   __USE_ISOC99		Define ISO C99 things.
   __USE_ISOC95		Define ISO C90 AMD1 (C95) things.
   __USE_ISOCXX11	Define ISO C++11 things.
   __USE_POSIX		Define IEEE Std 1003.1 things.
   __USE_POSIX2		Define IEEE Std 1003.2 things.
   __USE_POSIX199309	Define IEEE Std 1003.1, and .1b things.
   __USE_POSIX199506	Define IEEE Std 1003.1, .1b, .1c and .1i things.
   __USE_XOPEN		Define XPG things.
   __USE_XOPEN_EXTENDED	Define X/Open Unix things.
   __USE_UNIX98		Define Single Unix V2 things.
   __USE_XOPEN2K        Define XPG6 things.
   __USE_XOPEN2KXSI     Define XPG6 XSI things.
   __USE_XOPEN2K8       Define XPG7 things.
   __USE_XOPEN2K8XSI    Define XPG7 XSI things.
   __USE_LARGEFILE	Define correct standard I/O things.
   __USE_LARGEFILE64	Define LFS things with separate names.
   __USE_FILE_OFFSET64	Define 64bit interface as default.
   __USE_MISC		Define things from 4.3BSD or System V Unix.
   __USE_ATFILE		Define *at interfaces and AT_* constants for them.
   __USE_GNU		Define GNU extensions.
   __USE_FORTIFY_LEVEL	Additional security measures used, according to level.

   The macros __GNU_LIBRARY__, __GLIBC__, and __GLIBC_MINOR__ are
   defined by this file unconditionally.  __GNU_LIBRARY__ is provided
   only for compatibility.  All new code should use the other symbols
   to test for features.

   All macros listed above as possibly being defined by this file are
   explicitly undefined if they are not explicitly defined.
   Feature-test macros that are not defined by the user or compiler
   but are implied by the other feature-test macros defined (or by the
   lack of any definitions) are defined by the file.

   ISO C feature test macros depend on the definition of the macro
   when an affected header is included, not when the first system
   header is included, and so they are handled in
   <bits/libc-header-start.h>, which does not have a multiple include
   guard.  Feature test macros that can be handled from the first
   system header included are handled here.  */


/* Undefine everything, so we get a clean slate.  */
/* Suppress kernel-name space pollution unless user expressedly asks
   for it.  */




/* Convenience macro to test the version of gcc.
   Use like this:
   #if __GNUC_PREREQ (2,8)
   ... code requiring gcc 2.8 or later ...
   #endif
   Note: only works for GCC 2.0 and later, because __GNUC_MINOR__ was
   added in 2.0.  */







/* Similarly for clang.  Features added to GCC after version 4.2 may
   or may not also be available in clang, and clang's definitions of
   __GNUC(_MINOR)__ are fixed at 4 and 2 respectively.  Not all such
   features can be queried via __has_extension/__has_feature.  */







/* Whether to use feature set F.  */


/* _BSD_SOURCE and _SVID_SOURCE are deprecated aliases for
   _DEFAULT_SOURCE.  If _DEFAULT_SOURCE is present we do not
   issue a warning; the expectation is that the source is being
   transitioned to use the new macro.  */







/* If _GNU_SOURCE was defined by the user, turn on all the other features.  */
/* If nothing (other than _GNU_SOURCE and _DEFAULT_SOURCE) is defined,
   define _DEFAULT_SOURCE.  */
/* This is to enable the ISO C11 extension.  */





/* This is to enable the ISO C99 extension.  */





/* This is to enable the ISO C90 Amendment 1:1995 extension.  */
/* If none of the ANSI/POSIX macros are defined, or if _DEFAULT_SOURCE
   is defined, use POSIX.1-2008 (or another version depending on
   _XOPEN_SOURCE).  */
/* Some C libraries once required _REENTRANT and/or _THREAD_SAFE to be
   defined in all multithreaded code.  GNU libc has not required this
   for many years.  We now treat them as compatibility synonyms for
   _POSIX_C_SOURCE=199506L, which is the earliest level of POSIX with
   comprehensive support for multithreaded code.  Using them never
   lowers the selected level of POSIX conformance, only raises it.  */
/* The function 'gets' existed in C89, but is impossible to use
   safely.  It has been removed from ISO C11 and ISO C++14.  Note: for
   compatibility with various implementations of <cstdio>, this test
   must consider only the value of __cplusplus when compiling C++.  */






/* Get definitions of __STDC_* predefined macros, if the compiler has
   not preincluded this header automatically.  */
/* Copyright (C) 1991-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/* This macro indicates that the installed library is the GNU C Library.
   For historic reasons the value now is 6 and this will stay from now
   on.  The use of this variable is deprecated.  Use __GLIBC__ and
   __GLIBC_MINOR__ now (see below) when you want to test for a specific
   GNU C library version and use the values in <gnu/lib-names.h> to get
   the sonames of the shared libraries.  */



/* Major and minor version number of the GNU C library package.  Use
   these macros to test for features in specific releases.  */






/* This is here only because every header file already includes this one.  */


/* Copyright (C) 1992-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */




/* We are almost always included from features.h. */




/* The GNU libc does not support any K&R compilers or the traditional mode
   of ISO C compilers anymore.  Check for some of the combinations not
   anymore supported.  */




/* Some user header file might have defined this before.  */





/* All functions, except those with callbacks or those that
   synchronize memory, are leaf functions.  */
/* GCC can always grok prototypes.  For C++ programs we add throw()
   to help it optimize the function calls.  But this works only with
   gcc 2.8.x and egcs.  For gcc 3.2 and up we even mark C functions
   as non-throwing using a function attribute since programs can use
   the -fexceptions options for C code as well.  */
/* Compilers that are not clang may object to
       #if defined __clang__ && __has_extension(...)
   even though they do not need to evaluate the right-hand side of the &&.  */






/* These two macros are not used in glibc anymore.  They are kept here
   only because some other projects expect the macros to be defined.  */



/* For these things, GCC behaves the ANSI way normally,
   and the non-ANSI way under -traditional.  */




/* This is not a typedef so const __ptr_t does the right thing.  */



/* C++ needs to know that types and declarations are C, not C++.  */
/* Fortify support.  */
/* Support for flexible arrays.
   Headers that should use flexible arrays only if they're "real"
   (e.g. only if they won't affect sizeof()) should test
   #if __glibc_c99_flexarr_available.  */
/* __asm__ ("xyz") is used throughout the headers to rename functions
   at the assembly language level.  This is wrapped by the __REDIRECT
   macro, in order to support compilers that can do this some other
   way.  When compilers don't support asm-names at all, we have to do
   preprocessor tricks instead (which don't have exactly the right
   semantics, but it's the best we can do).

   Example:
   int __REDIRECT(setpgrp, (__pid_t pid, __pid_t pgrp), setpgid); */
/*

)
*/


/* GCC has various useful declarations that can be made with the
   __attribute__ syntax.  All of the ways we use this do fine if
   they are omitted for compilers that don't understand it. */




/* At some point during the gcc 2.96 development the malloc attribute
   for functions was introduced.  We don't want to use it unconditionally
   (although this would be possible) since it generates warnings.  */






/* Tell the compiler which arguments to an allocation function
   indicate the size of the allocation.  */







/* At some point during the gcc 2.96 development the pure attribute
   for functions was introduced.  We don't want to use it unconditionally
   (although this would be possible) since it generates warnings.  */






/* This declaration tells the compiler that the value is constant.  */






/* At some point during the gcc 3.1 development the used attribute
   for functions was introduced.  We don't want to use it unconditionally
   (although this would be possible) since it generates warnings.  */
/* Since version 3.2, gcc allows marking deprecated functions.  */






/* Since version 4.5, gcc also allows one to specify the message printed
   when a deprecated function is used.  clang claims to be gcc 4.2, but
   may also support this feature.  */
/* At some point during the gcc 2.8 development the format_arg attribute
   for functions was introduced.  We don't want to use it unconditionally
   (although this would be possible) since it generates warnings.
   If several format_arg attributes are given for the same function, in
   gcc-3.0 and older, all but the last one are ignored.  In newer gccs,
   all designated arguments are considered.  */






/* At some point during the gcc 2.97 development the strfmon format
   attribute for functions was introduced.  We don't want to use it
   unconditionally (although this would be possible) since it
   generates warnings.  */







/* The nonull function attribute allows to mark pointer parameters which
   must not be NULL.  */






/* If fortification mode, we warn about unused results of certain
   function calls which can lead to problems.  */
/* Forces a function to be always inlined.  */

/* The Linux kernel defines __always_inline in stddef.h (283d7573), and
   it conflicts with this definition.  Therefore undefine it first to
   allow either header to be included first.  */







/* Associate error messages with the source location of the call site rather
   than with the source location inside the function.  */






/* GCC 4.3 and above with -std=c99 or -std=gnu99 implements ISO C99
   inline semantics, unless -fgnu89-inline is used.  Using __GNUC_STDC_INLINE__
   or __GNUC_GNU_INLINE is not a good enough check for gcc because gcc versions
   older than 4.3 may define these macros and still not guarantee GNU inlining
   semantics.

   clang++ identifies itself as gcc-4.2, but has support for GNU inlining
   semantics, that can be checked fot by using the __GNUC_STDC_INLINE_ and
   __GNUC_GNU_INLINE__ macro definitions.  */
/* GCC 4.3 and above allow passing all anonymous arguments of an
   __extern_always_inline function to some other vararg function.  */





/* It is possible to compile containing GCC extensions even if GCC is
   run in pedantic mode if the uses are carefully marked using the
   __extension__ keyword.  But this is not generally available before
   version 2.8.  */




/* __restrict is known in EGCS 1.2 and above. */
/* ISO C99 also allows to declare arrays as non-overlapping.  The syntax is
     array_name[restrict]
   GCC 3.1 supports this.  */
/* Describes a char array whose address can safely be passed as the first
   argument to strncpy and strncat, as the char array is not necessarily
   a NUL-terminated string.  */
/* Copyright (C) 1999-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* Properties of long double type.
   Copyright (C) 2016-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License  published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/* This header is included by <sys/cdefs.h>.

   If long double is ABI-compatible with double, it should define
   __NO_LONG_DOUBLE_MATH to 1; otherwise, it should leave
   __NO_LONG_DOUBLE_MATH undefined.

   If this build of the GNU C Library supports both long double
   ABI-compatible with double and some other long double format not
   ABI-compatible with double, it should define
   __LONG_DOUBLE_MATH_OPTIONAL to 1; otherwise, it should leave
   __LONG_DOUBLE_MATH_OPTIONAL undefined.

   If __NO_LONG_DOUBLE_MATH is already defined, this header must not
   define anything; this is needed to work with the definition of
   __NO_LONG_DOUBLE_MATH in nldbl-compat.h.  */

/* In the default version of this header, long double is
   ABI-compatible with double.  */
/* __glibc_macro_warning (MESSAGE) issues warning MESSAGE.  This is
   intended for use in preprocessor macros.

   Note: MESSAGE must be a _single_ string; concatenation of string
   literals is not supported.  */
/* Generic selection (ISO C11) is a C-only feature, available in GCC
   since version 4.9.  Previous versions do not provide generic
   selection, even though they might set __STDC_VERSION__ to 201112L,
   when in -std=c11 mode.  Thus, we must check for !defined __GNUC__
   when testing __STDC_VERSION__ for generic selection support.
   On the other hand, Clang also defines __GNUC__, so a clang-specific
   check is required to enable the use of generic selection.  */


/* If we don't have __REDIRECT, prototypes will be missing if
   __USE_FILE_OFFSET64 but not __USE_LARGEFILE[64]. */







/* Decide whether we can define 'extern inline' functions in headers.  */







/* This is here only because every header file already includes this one.
   Get the definitions of all the appropriate __stub_FUNCTION symbols.
   <gnu/stubs.h> contains #define __stub_FUNCTION when FUNCTION is a stub
   that will always return failure (and set errno to ENOSYS).  */
/* This file is automatically generated.
   This file selects the right generated file of __stub_FUNCTION macros
   based on the architecture being compiled for.  */






/* This file is automatically generated.
   It defines a symbol __stub_FUNCTION for each function
   in the C library which is a stub, meaning it will fail
   every time called, usually setting errno to ENOSYS.  */

/* ISO/IEC TR 24731-2:2010 defines the __STDC_WANT_LIB_EXT2__
   macro.  */
/* ISO/IEC TS 18661-1:2014 defines the __STDC_WANT_IEC_60559_BFP_EXT__
   macro.  */







/* ISO/IEC TS 18661-4:2015 defines the
   __STDC_WANT_IEC_60559_FUNCS_EXT__ macro.  */







/* ISO/IEC TS 18661-3:2015 defines the
   __STDC_WANT_IEC_60559_TYPES_EXT__ macro.  */
/* bits/types.h -- definitions of __*_t types underlying *_t types.
   Copyright (C) 2002-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/*
 * Never include this file directly; use <sys/types.h> instead.
 */




/* Copyright (C) 1991-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* Copyright (C) 1999-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/* Convenience types.  */
typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;

/* Fixed-size types, underlying types depend on word size and compiler.  */
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;




__extension__ typedef signed long long int __int64_t;
__extension__ typedef unsigned long long int __uint64_t;


/* Smallest types with at least a given width.  */
typedef __int8_t __int_least8_t;
typedef __uint8_t __uint_least8_t;
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
typedef __int64_t __int_least64_t;
typedef __uint64_t __uint_least64_t;

/* quad_t is also 64 bits.  */




__extension__ typedef long long int __quad_t;
__extension__ typedef unsigned long long int __u_quad_t;


/* Largest integral types.  */




__extension__ typedef long long int __intmax_t;
__extension__ typedef unsigned long long int __uintmax_t;



/* The machine-dependent file <bits/typesizes.h> defines __*_T_TYPE
   macros for each of the OS types we define below.  The definitions
   of those macros must use the following macros for underlying types.
   We define __S<SIZE>_TYPE and __U<SIZE>_TYPE for the signed and unsigned
   variants of each of the following integer types on this machine.

	16		-- "natural" 16-bit type (always short)
	32		-- "natural" 32-bit type (always int)
	64		-- "natural" 64-bit type (long or long long)
	LONG32		-- 32-bit type, traditionally long
	QUAD		-- 64-bit type, always long long
	WORD		-- natural type of __WORDSIZE bits (int or long)
	LONGWORD	-- type of __WORDSIZE bits, traditionally long

   We distinguish WORD/LONGWORD, 32/LONG32, and 64/QUAD so that the
   conventional uses of long or long long type modifiers match the
   types we define, even when a less-adorned type would be the same size.
   This matters for (somewhat) portably writing printf/scanf formats for
   these types, where using the appropriate l or ll format modifiers can
   make the typedefs and the formats match up across all GNU platforms.  If
   we used long when it's 64 bits where long long is expected, then the
   compiler would warn about the formats not matching the argument types,
   and the programmer changing them to shut up the compiler would break the
   program's portability.

   Here we assume what is presently the case in all the GCC configurations
   we support: long long is always 64 bits, long is always word/address size,
   and int is always 32 bits.  */
/* We want __extension__ before typedef's that use nonstandard base types
   such as long long in C89 mode.  */
/* bits/typesizes.h -- underlying types for *_t.  Generic version.
   Copyright (C) 2002-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* See <bits/types.h> for the meaning of these macros.  This file exists so
   that <bits/types.h> need not vary across different GNU platforms.  */
/* Number of descriptors that can fit in an fd_set.  */


__extension__ typedef __u_quad_t __dev_t; /* Type of device numbers.  */
__extension__ typedef unsigned int __uid_t; /* Type of user identifications.  */
__extension__ typedef unsigned int __gid_t; /* Type of group identifications.  */
__extension__ typedef unsigned long int __ino_t; /* Type of file serial numbers.  */
__extension__ typedef __u_quad_t __ino64_t; /* Type of file serial numbers (LFS).*/
__extension__ typedef unsigned int __mode_t; /* Type of file attribute bitmasks.  */
__extension__ typedef unsigned int __nlink_t; /* Type of file link counts.  */
__extension__ typedef long int __off_t; /* Type of file sizes and offsets.  */
__extension__ typedef __quad_t __off64_t; /* Type of file sizes and offsets (LFS).  */
__extension__ typedef int __pid_t; /* Type of process identifications.  */
__extension__ typedef long int __clock_t; /* Type of CPU usage counts.  */
__extension__ typedef unsigned long int __rlim_t; /* Type for resource measurement.  */
__extension__ typedef __u_quad_t __rlim64_t; /* Type for resource measurement (LFS).  */
__extension__ typedef unsigned int __id_t; /* General type for IDs.  */
__extension__ typedef long int __time_t; /* Seconds since the Epoch.  */
__extension__ typedef unsigned int __useconds_t; /* Count of microseconds.  */
__extension__ typedef long int __suseconds_t; /* Signed count of microseconds.  */

__extension__ typedef int __daddr_t; /* The type of a disk address.  */
__extension__ typedef int __key_t; /* Type of an IPC key.  */

/* Clock ID used in clock and timer functions.  */
__extension__ typedef int __clockid_t;

/* Timer ID returned by timer_create.  */
__extension__ typedef void * __timer_t;

/* Type to represent block size.  */
__extension__ typedef long int __blksize_t;

/* Types from the Large File Support interface.  */

/* Type to count number of disk blocks.  */
__extension__ typedef long int __blkcnt_t;
__extension__ typedef __quad_t __blkcnt64_t;

/* Type to count file system blocks.  */
__extension__ typedef unsigned long int __fsblkcnt_t;
__extension__ typedef __u_quad_t __fsblkcnt64_t;

/* Type to count file system nodes.  */
__extension__ typedef unsigned long int __fsfilcnt_t;
__extension__ typedef __u_quad_t __fsfilcnt64_t;

/* Type of miscellaneous file system fields.  */
__extension__ typedef int __fsword_t;

__extension__ typedef int __ssize_t; /* Type of a byte count, or error.  */

/* Signed long type used in system calls.  */
__extension__ typedef long int __syscall_slong_t;
/* Unsigned long type used in system calls.  */
__extension__ typedef unsigned long int __syscall_ulong_t;

/* These few don't really vary by system, they always correspond
   to one of the other defined types.  */
typedef __off64_t __loff_t; /* Type of file sizes and offsets (LFS).  */
typedef char *__caddr_t;

/* Duplicates info from stdint.h but this is used in unistd.h.  */
__extension__ typedef int __intptr_t;

/* Duplicate info from sys/socket.h.  */
__extension__ typedef unsigned int __socklen_t;

/* C99: An integer type that can be accessed as an atomic entity,
   even in the presence of asynchronous interrupts.
   It is not currently necessary for this to be machine-specific.  */
typedef int __sig_atomic_t;
/* wchar_t type related definitions.
   Copyright (C) 2000-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */




/* The fallback definitions, for when __WCHAR_MAX__ or __WCHAR_MIN__
   are not defined, give the right value and type as long as both int
   and wchar_t are 32-bit types.  Adding L'\0' to a constant value
   ensures that the type is correct; it is necessary to use (L'\0' +
   0) rather than just L'\0' so that the type in C++ is the promoted
   version of wchar_t rather than the distinct wchar_t type itself.
   Because wchar_t in preprocessor #if expressions is treated as
   intmax_t or uintmax_t, the expression (L'\0' - 1) would have the
   wrong value for WCHAR_MAX in such expressions and so cannot be used
   to define __WCHAR_MAX in the unsigned case.  */
/* Copyright (C) 1999-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/* Exact integral types.  */

/* Signed.  */
/* Define intN_t types.
   Copyright (C) 2017-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */




/* bits/types.h -- definitions of __*_t types underlying *_t types.
   Copyright (C) 2002-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/*
 * Never include this file directly; use <sys/types.h> instead.
 */

typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;

/* Unsigned.  */
/* Define uintN_t types.
   Copyright (C) 2017-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */




/* bits/types.h -- definitions of __*_t types underlying *_t types.
   Copyright (C) 2002-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/*
 * Never include this file directly; use <sys/types.h> instead.
 */

typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;


/* Small types.  */

/* Signed.  */
typedef __int_least8_t int_least8_t;
typedef __int_least16_t int_least16_t;
typedef __int_least32_t int_least32_t;
typedef __int_least64_t int_least64_t;

/* Unsigned.  */
typedef __uint_least8_t uint_least8_t;
typedef __uint_least16_t uint_least16_t;
typedef __uint_least32_t uint_least32_t;
typedef __uint_least64_t uint_least64_t;


/* Fast types.  */

/* Signed.  */
typedef signed char int_fast8_t;





typedef int int_fast16_t;
typedef int int_fast32_t;
__extension__
typedef long long int int_fast64_t;


/* Unsigned.  */
typedef unsigned char uint_fast8_t;





typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
__extension__
typedef unsigned long long int uint_fast64_t;



/* Types for void * pointers.  */
typedef int intptr_t;


typedef unsigned int uintptr_t;



/* Largest integral types.  */
typedef __intmax_t intmax_t;
typedef __uintmax_t uintmax_t;
/* Limits of integral types.  */

/* Minimum of signed integral types.  */




/* Maximum of signed integral types.  */





/* Maximum of unsigned integral types.  */






/* Minimum of signed integral types having a minimum size.  */




/* Maximum of signed integral types having a minimum size.  */





/* Maximum of unsigned integral types having a minimum size.  */






/* Minimum of fast signed integral types having a minimum size.  */
/* Maximum of fast signed integral types having a minimum size.  */
/* Maximum of fast unsigned integral types having a minimum size.  */
/* Values to test for integral types holding void * pointer.  */
/* Minimum for largest signed integral type.  */

/* Maximum for largest signed integral type.  */


/* Maximum for largest unsigned integral type.  */



/* Limits of other integer types.  */

/* Limits of ptrdiff_t type.  */
/* Limits of sig_atomic_t.  */



/* Limit of size_t type.  */
/* Limits of wchar_t.  */

/* These constants might also be defined in <wchar.h>.  */




/* Limits of wint_t.  */



/* Signed.  */
/* Unsigned.  */
/* Maximal type.  */



typedef enum {
    BOOL_FALSE = 0,
    BOOL_TRUE = (!BOOL_FALSE)
} bool_t;

typedef int RESULT;

typedef enum RKAiqResult_e {
    RK_AIQ_RET_SUCCESS = 0, // this has to be 0, if clauses rely on it
    RK_AIQ_RET_FAILURE = 1, // process failure
    RK_AIQ_RET_INVALID_PARM = 2, // invalid parameter
    RK_AIQ_RET_WRONG_CONFIG = 3, // feature not supported
    RK_AIQ_RET_BUSY = 4, // there's already something going on...
    RK_AIQ_RET_CANCELED = 5, // operation canceled
    RK_AIQ_RET_OUTOFMEM = 6, // out of memory
    RK_AIQ_RET_OUTOFRANGE = 7, // parameter/value out of range
    RK_AIQ_RET_NULL_POINTER = 8, // the/one/all parameter(s) is a(are) NULL pointer(s)
    RK_AIQ_RET_DIVISION_BY_ZERO = 9, // a divisor equals ZERO
    RK_AIQ_RET_NO_INPUTIMAGE = 10 // no input image
} RKAiqResult_t;

typedef enum RKAiqState_e {
    RK_AIQ_STATE_INVALID = 0, /**< initialization value */
    RK_AIQ_STATE_INITIALIZED = 1, /**< instance is created, but not initialized */
    RK_AIQ_STATE_STOPPED = 2, /**< instance is confiured (ready to start) or stopped */
    RK_AIQ_STATE_RUNNING = 3, /**< instance is running (processes frames) */
    RK_AIQ_STATE_LOCKED = 4, /**< instance is locked (for taking snapshots) */
    RK_AIQ_STATE_MAX /**< max */
} RKAiqState_t;

typedef enum RKAiqOPMode_e {
    RK_AIQ_OP_MODE_INVALID = 0, /**< initialization value */
    RK_AIQ_OP_MODE_AUTO = 1, /**< instance is created, but not initialized */
    RK_AIQ_OP_MODE_MANUAL = 2, /**< instance is confiured (ready to start) or stopped */
    RK_AIQ_OP_MODE_MAX /**< max */
} RKAiqOPMode_t;
typedef unsigned int uint32_t;
typedef int sint32_t;
typedef char sint8_t;
typedef unsigned long long uint64t;


/******************************************************************************/
/**
 * @brief   A structure to represent a 5x5 matrix.
 *
 *          The 25 values are laid out as follows (zero based index):
 *
 *               | 00 01 02 03 04 | \n
 *               | 05 06 07 08 09 | \n
 *               | 10 11 12 13 14 | \n
 *               | 15 16 17 18 19 | \n
 *               | 20 21 22 23 24 | \n
 *
 * @note    The 25 values are represented as unsigned char numbers.
 *
 *****************************************************************************/
typedef struct Cam5x5UCharMatrix_s {
    uint8_t uCoeff[5 * 5]; /**< array of 5x5 unsigned char values */
} Cam5x5UCharMatrix_t;

typedef struct Cam15x15UCharMatrix_s {
    uint8_t uCoeff[15 * 15]; /**< array of 15x15 unsigned char values */
} Cam15x15UCharMatrix_t;


typedef struct Cam1x3IntMatrix_s
{
    // @desc: alias="Coeff", type="s32", size="[1, 3]", range="[-65535, 65535]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int Coeff[3];
} Cam1x3IntMatrix_t;

typedef struct Cam1x4IntMatrix_s
{
    int Coeff[4];
} Cam1x4IntMatrix_t;

typedef struct Cam1x6IntMatrix_s
{
    int Coeff[6];
} Cam1x6IntMatrix_t;

typedef struct Cam1x8IntMatrix_s
{
    int Coeff[8];
} Cam1x8IntMatrix_t;

typedef struct Cam1x9IntMatrix_s
{
    int Coeff[9];
} Cam1x9IntMatrix_t;

typedef struct Cam1x12IntMatrix_s
{
    int Coeff[12];
} Cam1x12IntMatrix_t;
typedef struct Cam1x17IntMatrix_s
{
    int Coeff[17];
} Cam1x17IntMatrix_t;

typedef struct Cam2x3IntMatrix_s
{
    int Coeff[2 * 3];
} Cam2x3IntMatrix_t;

typedef struct Cam3x3IntMatrix_s
{
    int Coeff[3 * 3];
} Cam3x3IntMatrix_t;

typedef struct Cam5x5IntMatrix_s
{
    int Coeff[5 * 5];
} Cam5x5IntMatrix_t;

/*****************************************************************************/
/**
 * @brief   Matrix coefficients
 *
 *          | 0 |
 *
 * @note    Coefficients are represented as float numbers
 */
/*****************************************************************************/
typedef struct Cam1x1FloatMatrix_s {
    float fCoeff[1];
} Cam1x1FloatMatrix_t;

/*****************************************************************************/
/**
 * @brief   Matrix coefficients
 *
 *          | 0 | 1 | 2 |
 *
 * @note    Coefficients are represented as float numbers
 */
/*****************************************************************************/
typedef struct Cam1x3FloatMatrix_s {
    // @desc: alias="fCoeff", type="f32", size="[1, 3]", range="[-65535, 65535]", default="0", digit="[6]", dynamic="0", hide="0", ro="0" 
    float fCoeff[3];
} Cam1x3FloatMatrix_t;

/*****************************************************************************/
/**
 * @brief   Matrix coefficients
 *
 *          | 0 | 1 | ... | 4 |
 *
 * @note    Coefficients are represented as float numbers
 */
/*****************************************************************************/
typedef struct Cam1x4FloatMatrix_s {
    // @desc: alias="fCoeff", type="f32", size="[1, 4]", range="[-65535, 65535]", default="0", digit="[6]", dynamic="0", hide="0", ro="0" 
    float fCoeff[4];
} Cam1x4FloatMatrix_t;

typedef struct Cam1x5FloatMatrix_s
{
    float fCoeff[5];
} Cam1x5FloatMatrix_t;

/*****************************************************************************/
/**
 * @brief   Matrix coefficients
 *
 *          | 0 | 1 | ... | 6 |
 *
 * @note    Coefficients are represented as float numbers
 */
/*****************************************************************************/
typedef struct Cam1x6FloatMatrix_s {
    float fCoeff[6];
} Cam1x6FloatMatrix_t;

typedef struct Cam1x8FloatMatrix_s
{
    float fCoeff[8];
} Cam1x8FloatMatrix_t;

typedef struct Cam1x9FloatMatrix_s
{
    float fCoeff[9];
} Cam1x9FloatMatrix_t;

/*****************************************************************************/
/**
 * @brief   Matrix coefficients
 *
 *          | 0 | 1 | ... | 15 |
 *
 * @note    Coefficients are represented as float numbers
 */
/*****************************************************************************/
typedef struct Cam1x16FloatMatrix_s {
    float fCoeff[16];
} Cam1x16FloatMatrix_t;

/*****************************************************************************/
/**
 * @brief   Matrix coefficients
 *
 *          | 0 | 1 |
 *
 * @note    Coefficients are represented as float numbers
 */
/*****************************************************************************/
typedef struct Cam2x1FloatMatrix {
    // @desc: alias="fCoeff", type="f32", size="[1, 2]", range="[-65535, 65535]", default="0", digit="[6]", dynamic="0", hide="0", ro="0" 
    float fCoeff[2];
} Cam2x1FloatMatrix_t;

/*****************************************************************************/
/**
 * @brief   Matrix coefficients
 *
 *          | 0 | 1 |
 *          | 2 | 3 |
 *
 * @note    Coefficients are represented as float numbers
 */
/*****************************************************************************/
typedef struct Cam2x2FloatMatrix {
    float fCoeff[4];
} Cam2x2FloatMatrix_t;

/*****************************************************************************/
/**
 * @brief   Matrix coefficients
 *
 *          | 0 | 1 |  2 |
 *
 * @note    Coefficients are represented as float numbers
 */
/*****************************************************************************/
typedef struct Cam3x1FloatMatrix {
    float fCoeff[3];
} Cam3x1FloatMatrix_t;

/*****************************************************************************/
/**
 * @brief   Matrix coefficients
 *
 *          | 0 | 1 |  2 |
 *          | 3 | 4 |  5 |
 *
 * @note    Coefficients are represented as float numbers
 */
/*****************************************************************************/
typedef struct Cam3x2FloatMatrix_s {
    float fCoeff[6];
} Cam3x2FloatMatrix_t;

/*****************************************************************************/
/**
 * @brief   Matrix coefficients
 *
 *          | 0 | 1 |  2 |
 *          | 3 | 4 |  5 |
 *          | 6 | 7 |  8 |
 *
 * @note    Coefficients are represented as float numbers
 */
/*****************************************************************************/
typedef struct Cam3x3FloatMatrix_s {
    float fCoeff[9];
} Cam3x3FloatMatrix_t;

/******************************************************************************/
/**
 * @brief   A structure to represent a 5x5 matrix.
 *
 *          The 25 values are laid out as follows (zero based index):
 *
 *               | 00 01 02 03 04 | \n
 *               | 05 06 07 08 09 | \n
 *               | 10 11 12 13 14 | \n
 *               | 15 16 17 18 19 | \n
 *               | 20 21 22 23 24 | \n
 *
 * @note    The 25 values are represented as float numbers.
 *
 *****************************************************************************/
typedef struct Cam5x5FloatMatrix_s {
    float fCoeff[25U]; /**< array of 5x5 float values */
} Cam5x5FloatMatrix_t;


/*****************************************************************************/
/**
 * @brief   Matrix coefficients
 *
 *          |   0 |   1 |   2 |   3 |   4 |   5 |   6 |   7 | ....
 *          |  17 |  18 |  19 |  20 |  21 |  22 |  23 |  24 | ....
 *          |  34 |  35 |  36 |  37 |  38 |  39 |  40 |  41 | ....
 *          ...
 *          ...
 *          ...
 *          | 271 | 272 | 273 | 274 | 275 | 276 | 277 | 278 | .... | 288 |
 *
 * @note    Coefficients are represented as short numbers
 */
/*****************************************************************************/
typedef struct Cam17x17FloatMatrix_s {
    float fCoeff[17 * 17];
} Cam17x17FloatMatrix_t;

/*****************************************************************************/
/**
 * @brief   Matrix coefficients
 *
 *          | 0 | 1 | 2 |
 *
 * @note    Coefficients are represented as short numbers
 */
/*****************************************************************************/
typedef struct Cam1x3ShortMatrix_s {
    // @desc: alias="fCoeff", type="s16", size="[1, 3]", range="[-65535, 65535]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int16_t Coeff[3];
} Cam1x3ShortMatrix_t;

/*****************************************************************************/
/**
 * @brief   Matrix coefficients
 *
 *          | 0 | 1 | 2 | ... | 4 |
 *
 * @note    Coefficients are represented as short numbers
 */
/*****************************************************************************/
typedef struct Cam1x4UShortMatrix_s {
    uint16_t uCoeff[4];
} Cam1x4UShortMatrix_t;

/*****************************************************************************/
/**
 * @brief   Matrix coefficients
 *
 *          | 0 | 1 | 2 | ... | 16 |
 *
 * @note    Coefficients are represented as short numbers
 */
/*****************************************************************************/
typedef struct Cam1x17UShortMatrix_s {
    uint16_t uCoeff[17];
} Cam1x17UShortMatrix_t;

/*****************************************************************************/
/**
 * @brief   Matrix coefficients
 *
 *          |   0 |   1 |   2 |   3 |   4 |   5 |   6 |   7 | ....
 *          |  17 |  18 |  19 |  20 |  21 |  22 |  23 |  24 | ....
 *          |  34 |  35 |  36 |  37 |  38 |  39 |  40 |  41 | ....
 *          ...
 *          ...
 *          ...
 *          | 271 | 272 | 273 | 274 | 275 | 276 | 277 | 278 | .... | 288 |
 *
 * @note    Coefficients are represented as short numbers
 */
/*****************************************************************************/
typedef struct Cam17x17UShortMatrix_s {
    // @desc: alias="uCoeff", type="u16", size="[17, 17]", range="[0, 10000]", default="1024", digit="[0]", dynamic="0", hide="0", ro="0" 
    uint16_t uCoeff[17 * 17];
} Cam17x17UShortMatrix_t;

typedef enum {
    RK_AIQ_WORKING_MODE_NORMAL,
    RK_AIQ_WORKING_MODE_ISP_HDR2 = 0x10,
    RK_AIQ_WORKING_MODE_ISP_HDR3 = 0x20,
//    RK_AIQ_WORKING_MODE_SENSOR_HDR = 10, // sensor built-in hdr mode
} rk_aiq_working_mode_t;

typedef enum {
    RK_AIQ_ISP_HDR_MODE_2_FRAME_HDR = RK_AIQ_WORKING_MODE_ISP_HDR2 + 1,
    RK_AIQ_ISP_HDR_MODE_2_LINE_HDR = RK_AIQ_WORKING_MODE_ISP_HDR2 + 2,
    RK_AIQ_ISP_HDR_MODE_3_FRAME_HDR = RK_AIQ_WORKING_MODE_ISP_HDR3 + 1,
    RK_AIQ_ISP_HDR_MODE_3_LINE_HDR = RK_AIQ_WORKING_MODE_ISP_HDR3 + 2,
} rk_aiq_isp_hdr_mode_t;

typedef enum {
    RK_AIQ_SENSOR_HDR_LINE_MODE_DCG, // 2frame: share the same exptime, use dual conversion gain; 3frame: DCG+VS, VS frame use individual gain & time
    RK_AIQ_SENSOR_HDR_LINE_MODE_STAGGER, // 2frame or 3frame
} rk_aiq_sensor_hdr_line_mode_t;



typedef enum {
    RK_AIQ_ISPP_STATIC_TNR_WORKING_MODE_2TO1,
    RK_AIQ_ISPP_STATIC_TNR_WORKING_MODE_3TO1,
} rk_aiq_ispp_static_tnr_working_mode_t;

typedef enum {
    RK_AIQ_ISPP_STATIC_FEC_WORKING_MODE_STABLIZATION,
    RK_AIQ_ISPP_STATIC_FEC_WORKING_MODE_FISHEYE,
} rk_aiq_ispp_static_fec_working_mode_t;

typedef enum {
    RK_MODULE_INVAL = 0,
    RK_MODULE_DPCC,
    RK_MODULE_BLS,
    RK_MODULE_LSC,
    RK_MODULE_AWB_GAIN,
    RK_MODULE_CTK,
    RK_MODULE_GOC,
    RK_MODULE_SHARP,
    RK_MODULE_AE,
    RK_MODULE_AWB,
    RK_MODULE_NR,//10
    RK_MODULE_GIC,
    RK_MODULE_3DLUT,
    RK_MODULE_LDCH,
    RK_MODULE_TNR,//14
    RK_MODULE_FEC,
    RK_MODULE_RAWNR,//16
    RK_MODULE_MAX
} rk_aiq_module_id_t;

typedef enum {
    RK_AIQ_UAPI_MODE_DEFAULT = 0,
    RK_AIQ_UAPI_MODE_SYNC,
    RK_AIQ_UAPI_MODE_ASYNC
} rk_aiq_uapi_mode_sync_e;

/*
 * @sync_mode (param in): flags for param update mode,
 *   @setAttrib:
 *     RK_AIQ_UAPI_MODE_DEFAULT:      default is sync mode.
 *     RK_AIQ_UAPI_MODE_SYNC:         sync mode.
 *     RK_AIQ_UAPI_MODE_ASYNC:        async mode.
 *   @getAttrib:
 *     RK_AIQ_UAPI_MODE_DEFAULT: default to get the attrib that was
 *       set(sync_mode == RK_AIQ_UAPI_MODE_ASYNC) last time, which
 *       may not be in effect yet.
 *     RK_AIQ_UAPI_MODE_SYNC:    get the attrib currently in use.
 *     RK_AIQ_UAPI_MODE_ASYNC:   the same as RK_AIQ_UAPI_MODE_DEFAULT.
 *
 * @done (parsm out): flags for param update status,
 *     true indicate param has been updated, false
 *     indicate param has not been updated.
 */
typedef struct rk_aiq_uapi_sync_s {
    rk_aiq_uapi_mode_sync_e sync_mode;
    
   _Bool 
                               done;
} rk_aiq_uapi_sync_t;

extern int g_rkaiq_isp_hw_ver;




typedef struct CalibDb_Sensor_Module_s {
    // @desc: alias="FNumber", type="f32", size="[1,1]", range="[1, 100]", default="1.6", digit="[2]", hide="0", ro="0" 
    float FNumber;
    // @desc: alias="EFL", type="f32", size="[1,1]", range="[0, 200]", default="3.5", digit="[2]", hide="0", ro="0" 
    float EFL;
    // @desc: alias="LensT", type="f32", size="[1,1]", range="[0, 100]", default="90", digit="[2]", hide="0", ro="0" 
    float LensT;
    // @desc: alias="IRCutT", type="f32", size="[1,1]", range="[0, 100]", default="90", digit="[2]", hide="0", ro="0" 
    float IRCutT;
} CalibDb_Sensor_Module_t;

typedef struct CalibDb_Module_ParaV2_s {
    // @desc: alias="SensorModule", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Sensor_Module_t sensor_module;
} CalibDb_Module_ParaV2_t;


/*
 * sensorinfo_head.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




// #define M4_STRUCT_DESC(ALIAS, SIZE, UI_MODULE)
// #define M4_NUMBER_DESC(ALIAS, TYPE, SIZE, RANGE, DEFAULT)
// #define M4_STRING_DESC(ALIAS, SIZE, RANGE, DEFAULT)
// #define M4_ENUM_DESC(ALIAS, ENUM, DEFAULT)

/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */



/*****************************************************************************/
/**
 * @brief   ISP2.0 SensorInfo enum Params
 */
/*****************************************************************************/
typedef enum _CalibDb_ExpGainModeV2_e {
    EXPGAIN_MODE_LINEAR = 0,
    EXPGAIN_MODE_NONLINEAR_DB = 1,
    EXPGAIN_MODE_MAX = 2
} CalibDb_ExpGainModeV2_t;

typedef enum _CalibDb_HdrFrmNumV2_e {
    HDR_TWO_FRAME = 0,
    HDR_THREE_FRAME = 1,
} CalibDb_HdrFrmNumV2_t;

/*****************************************************************************/
/**
 * @brief   ISP2.0 SensorInfo config Params
 */
/*****************************************************************************/
typedef struct CalibDb_AecGainRangeV2_s {
    // @desc: type="enum", alias="GainMode", enum_def="CalibDb_ExpGainModeV2_t", default="EXPGAIN_MODE_LINEAR", ro="0" 
    CalibDb_ExpGainModeV2_t GainMode;

    // @desc: alias="GainRange", type="f32", size="[1, 7]", range="[-65535, 65535]", default="0", digit="[4]", dynamic="2", hide="0", ro="0" 
    float* GainRange;//contains 7 params per line
    int GainRange_len;
} CalibDb_AecGainRangeV2_t;

typedef struct CalibDb_CISNormalTimeSetV2_s {
    // @desc: alias="TimeRegMin", type="u16", size="[1,1]", range="[1, 100]", default="1", digit="[0]", hide="0", ro="0" 
    uint16_t CISTimeRegMin;

    // @desc: alias="TimeRegMaxFac", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    Cam2x1FloatMatrix_t CISLinTimeRegMaxFac;

    // @desc: alias="TimeRegOdevity", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    Cam2x1FloatMatrix_t CISTimeRegOdevity;
} CalibDb_CISNormalTimeSetV2_t;

typedef struct CalibDb_CISHdrTimeSetV2_s {
    // @desc: type="enum", alias="name", enum_def="CalibDb_HdrFrmNumV2_t", default="HDR_TWO_FRAME", ro="0" 
    CalibDb_HdrFrmNumV2_t name;

    // @desc: type="bool", alias="CISTimeRegUnEqualEn", default="0", hide="0", ro="0" 
    
   _Bool 
                           CISTimeRegUnEqualEn;

    // @desc: alias="CISTimeRegMin", type="u16", size="[1,1]", range="[1, 100]", default="1", digit="[0]", hide="0", ro="0" 
    uint16_t CISTimeRegMin;

    // @desc: alias="CISHdrTimeRegSumFac", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    Cam2x1FloatMatrix_t CISHdrTimeRegSumFac;

    // @desc: alias="CISTimeRegMax", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    Cam1x3ShortMatrix_t CISTimeRegMax; //specially for Hdr that has limit on sframe/mframe, requiring max time line.value 0: no limit

    // @desc: alias="CISTimeRegOdevity", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    Cam2x1FloatMatrix_t CISTimeRegOdevity;
} CalibDb_CISHdrTimeSetV2_t;

typedef struct CalibDb_CISTimeSet_CombV2_s {
    // @desc: alias="Linear", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_CISNormalTimeSetV2_t Linear;

    // @desc: alias="Hdr", type="struct_list", size="[1, 2]", ui_module="normal_ui_style", ro="0" 
    CalibDb_CISHdrTimeSetV2_t Hdr[2];
} CalibDb_CISTimeSet_CombV2_t;

typedef struct CalibDb_AeRangeV2_s {
    // @desc: alias="Min", type="f32", size="[1,1]", range="[0, 65535]", default="0", digit="[3]", hide="0", ro="0" 
    float Min;

    // @desc: alias="Max", type="f32", size="[1,1]", range="[0, 65535]", default="0", digit="[3]", hide="0", ro="0" 
    float Max;
} CalibDb_AeRangeV2_t;

typedef struct CalibDb_CISGainSetV2_s {
    // @desc: alias="CISAgainRange", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_AeRangeV2_t CISAgainRange; //sensor Again or LCG range

    // @desc: alias="CISExtraAgainRange", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_AeRangeV2_t CISExtraAgainRange; //add for HDR-DCG MODE, HCG range

    // @desc: alias="CISDgainRange", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_AeRangeV2_t CISDgainRange; //sensor Dgain

    // @desc: alias="CISIspDgainRange", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_AeRangeV2_t CISIspDgainRange; //Isp Dgain

    // @desc: type="bool", alias="CISHdrGainIndSetEn", default="1", hide="0", ro="0" 
    
   _Bool 
                          CISHdrGainIndSetEn; //bit 0:use the same value; bit 1: support use different gain value
} CalibDb_CISGainSetV2_t;

typedef struct CalibDb_CISHdrSetV2_s {
    // @desc: type="bool", alias="hdr_en", default="0", hide="0", ro="0" 
    
   _Bool 
        hdr_en;

    // @desc: type="enum", alias="hdr_mode", enum_def="rk_aiq_isp_hdr_mode_t", default="RK_AIQ_ISP_HDR_MODE_2_LINE_HDR", ro="0" 
    rk_aiq_isp_hdr_mode_t hdr_mode;

    // @desc: type="enum", alias="line_mode", enum_def="rk_aiq_sensor_hdr_line_mode_t", default="RK_AIQ_SENSOR_HDR_LINE_MODE_STAGGER", ro="0" 
    rk_aiq_sensor_hdr_line_mode_t line_mode;
} CalibDb_CISHdrSetV2_t;

typedef struct CalibDb_Dcg_ParamsV2_s {
    // @desc: type="bool", alias="support_en", default="0", hide="0", ro="0" 
    
   _Bool 
                       support_en;

    // @desc: type="enum", alias="dcg_optype", enum_def="RKAiqOPMode_t", default="RK_AIQ_OP_MODE_AUTO", ro="0" 
    RKAiqOPMode_t dcg_optype;

    // @desc: alias="dcg_mode", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    Cam1x3IntMatrix_t dcg_mode;

    // @desc: alias="dcg_ratio", type="f32", size="[1,1]", range="[1, 100]", default="1", digit="[2]", hide="0", ro="0" 
    float dcg_ratio;

    // @desc: type="bool", alias="sync_switch", default="1", hide="0", ro="0" 
    
   _Bool 
                       sync_switch;

    // @desc: alias="lcg2hcg_gain_th", type="f32", size="[1,1]", range="[1, 4096]", default="32", digit="[2]", hide="0", ro="0" 
    float lcg2hcg_gain_th;

    // @desc: alias="hcg2lcg_gain_th", type="f32", size="[1,1]", range="[1, 4096]", default="16", digit="[2]", hide="0", ro="0" 
    float hcg2lcg_gain_th;
} CalibDb_Dcg_ParamsV2_t;

typedef struct CalibDb_DcgSetV2_s {
    // @desc: alias="Linear", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Dcg_ParamsV2_t Linear;

    // @desc: alias="Hdr", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Dcg_ParamsV2_t Hdr;
} CalibDb_DcgSetV2_t;

typedef struct CalibDb_ExpUpdateV2_s {
    // @desc: alias="time_update", type="s32", size="[1,1]", range="[0, 10]", default="2", digit="[0]", hide="0", ro="0" 
    int time_update;

    // @desc: alias="gain_update", type="s32", size="[1,1]", range="[0, 10]", default="2", digit="[0]", hide="0", ro="0" 
    int gain_update;

    // @desc: alias="dcg_update", type="s32", size="[1,1]", range="[0, 10]", default="2", digit="[0]", hide="0", ro="0" 
    int dcg_update;
} CalibDb_ExpUpdateV2_t;

typedef struct CalibDb_ExpUpdate_CombV2_s {
    // @desc: alias="Linear", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_ExpUpdateV2_t Linear;

    // @desc: alias="Hdr", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_ExpUpdateV2_t Hdr;
} CalibDb_ExpUpdate_CombV2_t;

typedef struct CalibDb_ResInfoV2_s {
    // @desc: alias="width", type="u16", size="[1,1]", range="[0, 65535]", default="0", digit="[0]", hide="0", ro="0" 
    uint16_t width;
    // @desc: alias="height", type="u16", size="[1,1]", range="[0, 65535]", default="0", digit="[0]", hide="0", ro="0" 
    uint16_t height;
} CalibDb_ResInfoV2_t;


typedef struct CalibDb_Sensor_ParaV2_s {
    // @desc: alias="Resolution", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_ResInfoV2_t resolution;

    // @desc: alias="Gain2Reg", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_AecGainRangeV2_t Gain2Reg;

    // @desc: alias="Time2Reg", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    Cam1x4FloatMatrix_t Time2Reg;

    // @desc: alias="CISGainSet", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_CISGainSetV2_t CISGainSet;

    // @desc: alias="CISTimeSet", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_CISTimeSet_CombV2_t CISTimeSet;

    // @desc: alias="CISHdrSet", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_CISHdrSetV2_t CISHdrSet;

    // @desc: alias="CISDcgSet", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_DcgSetV2_t CISDcgSet;

    // @desc: alias="CISExpUpdate", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_ExpUpdate_CombV2_t CISExpUpdate;

    // @desc: alias="CISMinFps", type="f32", size="[1,1]", range="[1, 100]", default="10", digit="[2]", hide="0", ro="0" 
    float CISMinFps;

    // @desc: alias="CISFlip", type="u8", size="[1,1]", range="[0, 3]", default="0", digit="[0]", hide="0", ro="0" 
    uint8_t CISFlip; // bit 0 : mirror, bit 1 : flip , range[0,3]
} CalibDb_Sensor_ParaV2_t;


/*
 * sys_static_cfg_head.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */



typedef enum EnableAlgoType_e {
    ENABLE_AE = 0x0,
    ENABLE_AWB,
    ENABLE_AF,
    ENABLE_ABLC,
    ENABLE_ADPCC,
    ENABLE_AMERGE,
    ENABLE_ATMO,
    ENABLE_ANR,
    ENABLE_ALSC,
    ENABLE_AGIC,
    ENABLE_ADEBAYER,
    ENABLE_ACCM,
    ENABLE_AGAMMA,
    ENABLE_AWDR,
    ENABLE_ADHAZ,
    ENABLE_A3DLUT,
    ENABLE_ALDCH,
    ENABLE_AR2Y,
    ENABLE_ACP,
    ENABLE_AIE,
    ENABLE_ASHARP,
    ENABLE_AORB,
    ENABLE_ACGC,
    ENABLE_ASD,
    ENABLE_ADRC,
    ENABLE_ADEGAMMA,

    ENABLE_ARAWNR,
    ENABLE_AMFNR,
    ENABLE_AYNR,
    ENABLE_ACNR,
    ENABLE_AEIS,
    ENABLE_AFEC,
    ENABLE_AMD,
    ENABLE_AGAIN
} EnableAlgoType_t;

typedef struct CalibDb_AlgoSwitch_s {
    // @desc: type="bool", alias="enable", default="0", hide="0", ro="0" 
    
   _Bool 
                       enable;

    // @desc: alias="EnableAlgos", type="string", size="[1, 1]", range="[0, 32]", default="ENABLE_AE", dynamic="1", hide="0", ro="0" 
    EnableAlgoType_t* enable_algos;
    int16_t enable_algos_len;
} CalibDb_AlgoSwitch_t;

typedef struct CalibDb_SysStaticCfg_ParaV2_s {
    // @desc: alias="AlgoSwitch", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_AlgoSwitch_t algoSwitch;
} CalibDb_SysStaticCfg_ParaV2_t;


/*
 * Copyright (c) 2019-2022 Rockchip Eletronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 * ablc_head.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */







/*****************************************************************************/
/**
 * @brief   ISP2.0 ABLC Config Params
 */
/*****************************************************************************/

typedef struct Blc_data_s {
    // @desc: alias="ISO", type="f32", size="[1, 100]", range="[0, 10000000]", default="50", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* ISO;
    int ISO_len;
    // @desc: alias="R_Channel", type="f32", size="[1, 100]", range="[0, 4095]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* R_Channel;
    int R_Channel_len;
    // @desc: alias="Gr_Channel", type="f32", size="[1, 100]", range="[0, 4095]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* Gr_Channel;
    int Gr_Channel_len;
    // @desc: alias="Gb_Channel", type="f32", size="[1, 100]", range="[0, 4095]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* Gb_Channel;
    int Gb_Channel_len;
    // @desc: alias="B_Channel", type="f32", size="[1, 100]", range="[0, 4095]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* B_Channel;
    int B_Channel_len;
} Blc_data_t;

typedef struct AblcParaV2_s {
    // @desc: type="bool", alias="enable", default="1", hide="0", ro="0" 
    
   _Bool 
        enable;
    // @desc: alias="BLC_Data", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    Blc_data_t BLC_Data;
} AblcParaV2_t;


typedef struct CalibDbV2_Ablc_s {
    // @desc: alias="BlcTuningPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    AblcParaV2_t BlcTuningPara;
    // @desc: alias="Blc1TuningPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    AblcParaV2_t Blc1TuningPara;
} CalibDbV2_Ablc_t;



/*
 * adegamma_head.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */





/*****************************************************************************/
/**
 * @brief   ISP2.0 Adegamma Config Params
 */
/*****************************************************************************/

typedef struct AdegmmaParaV2_s {
    // @desc: type="bool", alias="degamma_en", default="0", hide="0", ro="0" 
    
   _Bool 
        degamma_en;
    // @desc: alias="X_axis", type="u16", size="[1, 17]", range="[0, 4095]", default="[0 256 512 768 1024 1280 1536 1792 2048 2304 2560 2816 3072 3328 3584 3840 4096]", digit="[0]", dynamic="0", hide="0", ro="0" 
    int X_axis[17];
    // @desc: alias="curve_R", type="u16", size="[1, 17]", range="[0, 4095]", default="[0 256 512 768 1024 1280 1536 1792 2048 2304 2560 2816 3072 3328 3584 3840 4096]", digit="[0]", dynamic="0", hide="0", ro="0" 
    int curve_R[17];
    // @desc: alias="curve_G", type="u16", size="[1, 17]", range="[0, 4095]", default="[0 256 512 768 1024 1280 1536 1792 2048 2304 2560 2816 3072 3328 3584 3840 4096]", digit="[0]", dynamic="0", hide="0", ro="0" 
    int curve_G[17];
    // @desc: alias="curve_B", type="u16", size="[1, 17]", range="[0, 4095]", default="[0 256 512 768 1024 1280 1536 1792 2048 2304 2560 2816 3072 3328 3584 3840 4096]", digit="[0]", dynamic="0", hide="0", ro="0" 
    int curve_B[17];
} AdegmmaParaV2_t;

typedef struct CalibDbV2_Adegmma_s {
    // @desc: alias="DegammaTuningPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    AdegmmaParaV2_t DegammaTuningPara;
} CalibDbV2_Adegmma_t;



/*
 * adehaze_head.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */








typedef struct DehazeData_s {
    // @desc: alias="ISO", type="f32", size="[1, 100]", range="[0, 10000000]", default="50", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* ISO;
    int ISO_len;
    // @desc: alias="dc_min_th", type="f32", size="[1, 100]", range="[0, 255]", default="64", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* dc_min_th;
    int dc_min_th_len;
    // @desc: alias="dc_max_th", type="f32", size="[1, 100]", range="[0, 255]", default="192", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* dc_max_th;
    int dc_max_th_len;
    // @desc: alias="yhist_th", type="f32", size="[1, 100]", range="[0, 255]", default="249", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* yhist_th;
    int yhist_th_len;
    // @desc: alias="yblk_th", type="f32", size="[1, 100]", range="[0, 512]", default="0.002", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* yblk_th;
    int yblk_th_len;
    // @desc: alias="dark_th", type="f32", size="[1, 100]", range="[0, 255]", default="250", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* dark_th;
    int dark_th_len;
    // @desc: alias="bright_min", type="f32", size="[1, 100]", range="[0, 255]", default="180", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* bright_min;
    int bright_min_len;
    // @desc: alias="bright_max", type="f32", size="[1, 100]", range="[0, 255]", default="240", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* bright_max;
    int bright_max_len;
    // @desc: alias="wt_max", type="f32", size="[1, 100]", range="[0, 1]", default="0.9", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* wt_max;
    int wt_max_len;
    // @desc: alias="air_min", type="f32", size="[1, 100]", range="[0, 255]", default="200", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* air_min;
    int air_min_len;
    // @desc: alias="air_max", type="f32", size="[1, 100]", range="[0, 255]", default="250", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* air_max;
    int air_max_len;
    // @desc: alias="tmax_base", type="f32", size="[1, 100]", range="[0, 255]", default="125", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* tmax_base;
    int tmax_base_len;
    // @desc: alias="tmax_off", type="f32", size="[1, 100]", range="[0, 1]", default="0.1", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* tmax_off;
    int tmax_off_len;
    // @desc: alias="tmax_max", type="f32", size="[1, 100]", range="[0, 1]", default="0.8", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* tmax_max;
    int tmax_max_len;
    // @desc: alias="cfg_wt", type="f32", size="[1, 100]", range="[0, 1]", default="0.8", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* cfg_wt;
    int cfg_wt_len;
    // @desc: alias="cfg_air", type="f32", size="[1, 100]", range="[0, 255]", default="210", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* cfg_air;
    int cfg_air_len;
    // @desc: alias="cfg_tmax", type="f32", size="[1, 100]", range="[0, 1]", default="0.2", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* cfg_tmax;
    int cfg_tmax_len;
    // @desc: alias="dc_thed", type="f32", size="[1, 100]", range="[0, 255]", default="2", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* dc_thed;
    int dc_thed_len;
    // @desc: alias="dc_weitcur", type="f32", size="[1, 100]", range="[0, 1]", default="1", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* dc_weitcur;
    int dc_weitcur_len;
    // @desc: alias="air_thed", type="f32", size="[1, 100]", range="[0, 255]", default="2", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* air_thed;
    int air_thed_len;
    // @desc: alias="air_weitcur", type="f32", size="[1, 100]", range="[0, 1]", default="0.14", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* air_weitcur;
    int air_weitcur_len;
} DehazeData_t;

typedef struct Dehaze_Setting_V20_s {
    // @desc: type="bool", alias="en", default="1", hide="0", ro="0" 
    
   _Bool 
        en;
    // @desc: alias="stab_fnum", type="f32", size="[1,1]", range="[0, 31]", default="8.0", digit="[4]", hide="0", ro="0" 
    float stab_fnum;
    // @desc: alias="sigma", type="f32", size="[1,1]", range="[0, 255]", default="6.0", digit="[4]", hide="0", ro="0" 
    float sigma;
    // @desc: alias="wt_sigma", type="f32", size="[1,1]", range="[0, 256]", default="8.0", digit="[4]", hide="0", ro="0" 
    float wt_sigma;
    // @desc: alias="air_sigma", type="f32", size="[1,1]", range="[0, 255]", default="120.0", digit="[4]", hide="0", ro="0" 
    float air_sigma;
    // @desc: alias="tmax_sigma", type="f32", size="[1,1]", range="[0, 1]", default="0.0100", digit="[4]", hide="0", ro="0" 
    float tmax_sigma;
    // @desc: alias="DehazeData", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    DehazeData_t DehazeData;
} Dehaze_Setting_V20_t;

typedef struct EnhanceData_s {
    // @desc: alias="ISO", type="f32", size="[1, 100]", range="[0, 10000000]", default="50", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* ISO;
    int ISO_len;
    // @desc: alias="enhance_value", type="f32", size="[1, 100]", range="[0, 32]", default="1", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* enhance_value;
    int enhance_value_len;
} EnhanceData_t;

typedef struct Enhance_Setting_V20_s {
    // @desc: type="bool", alias="en", default="1", hide="0", ro="0" 
    
   _Bool 
        en;
    // @desc: alias="EnhanceData", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    EnhanceData_t EnhanceData;
} Enhance_Setting_V20_t;

typedef struct HistData_s {
    // @desc: alias="ISO", type="f32", size="[1, 100]", range="[0, 10000000]", default="50", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* ISO;
    int ISO_len;
    // @desc: alias="hist_gratio", type="f32", size="[1, 100]", range="[0, 32]", default="2", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* hist_gratio;
    int hist_gratio_len;
    // @desc: alias="hist_th_off", type="f32", size="[1, 100]", range="[0, 255]", default="64", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* hist_th_off;
    int hist_th_off_len;
    // @desc: alias="hist_k", type="f32", size="[1, 100]", range="[0, 8]", default="2", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* hist_k;
    int hist_k_len;
    // @desc: alias="hist_min", type="f32", size="[1, 100]", range="[0, 2]", default="0.016", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* hist_min;
    int hist_min_len;
    // @desc: alias="hist_scale", type="f32", size="[1, 100]", range="[0, 32]", default="0.09", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* hist_scale;
    int hist_scale_len;
    // @desc: alias="cfg_gratio", type="f32", size="[1, 100]", range="[0, 32]", default="2", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* cfg_gratio;
    int cfg_gratio_len;
} HistData_t;

typedef struct Hist_setting_V20_s {
    // @desc: type="bool", alias="en", default="1", hide="0", ro="0" 
    
   _Bool 
        en;
    // @desc: type="bool", alias="hist_para_en", default="1", hide="0", ro="0" 
    
   _Bool 
         hist_para_en;
    // @desc: type="bool", alias="hist_channel", default="1", hide="0", ro="0" 
    
   _Bool 
         hist_channel;
    // @desc: alias="HistData", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    HistData_t HistData;
} Hist_setting_V20_t;

typedef struct CalibDbDehazeV20_s {
    // @desc: type="bool", alias="Enable", default="1", hide="0", ro="0" 
    
   _Bool 
        Enable;
    // @desc: alias="cfg_alpha", type="f32", size="[1,1]", range="[0, 1]", default="1", digit="[4]", hide="0", ro="0" 
    float cfg_alpha;
    // @desc: alias="ByPassThr", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[4]", hide="0", ro="0" 
    float ByPassThr;
    // @desc: alias="dehaze_setting", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    Dehaze_Setting_V20_t dehaze_setting;
    // @desc: alias="enhance_setting", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    Enhance_Setting_V20_t enhance_setting;
    // @desc: alias="hist_setting", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    Hist_setting_V20_t hist_setting;
} CalibDbDehazeV20_t;

typedef struct CalibDbV2_dehaze_V20_s {
    // @desc: alias="DehazeTuningPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbDehazeV20_t DehazeTuningPara;
} CalibDbV2_dehaze_V20_t;

typedef struct DehazeDataV21_s {
    // @desc: alias="EnvLv", type="f32", size="[1, 100]", range="[0, 1]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* EnvLv;
    int EnvLv_len;
    // @desc: alias="dc_min_th", type="f32", size="[1, 100]", range="[0, 255]", default="64", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* dc_min_th;
    int dc_min_th_len;
    // @desc: alias="dc_max_th", type="f32", size="[1, 100]", range="[0, 255]", default="192", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* dc_max_th;
    int dc_max_th_len;
    // @desc: alias="yhist_th", type="f32", size="[1, 100]", range="[0, 255]", default="249", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* yhist_th;
    int yhist_th_len;
    // @desc: alias="yblk_th", type="f32", size="[1, 100]", range="[0, 512]", default="0.002", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* yblk_th;
    int yblk_th_len;
    // @desc: alias="dark_th", type="f32", size="[1, 100]", range="[0, 255]", default="250", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* dark_th;
    int dark_th_len;
    // @desc: alias="bright_min", type="f32", size="[1, 100]", range="[0, 255]", default="180", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* bright_min;
    int bright_min_len;
    // @desc: alias="bright_max", type="f32", size="[1, 100]", range="[0, 255]", default="240", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* bright_max;
    int bright_max_len;
    // @desc: alias="wt_max", type="f32", size="[1, 100]", range="[0, 1]", default="0.9", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* wt_max;
    int wt_max_len;
    // @desc: alias="air_min", type="f32", size="[1, 100]", range="[0, 255]", default="200", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* air_min;
    int air_min_len;
    // @desc: alias="air_max", type="f32", size="[1, 100]", range="[0, 255]", default="250", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* air_max;
    int air_max_len;
    // @desc: alias="tmax_base", type="f32", size="[1, 100]", range="[0, 255]", default="125", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* tmax_base;
    int tmax_base_len;
    // @desc: alias="tmax_off", type="f32", size="[1, 100]", range="[0, 1]", default="0.1", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* tmax_off;
    int tmax_off_len;
    // @desc: alias="tmax_max", type="f32", size="[1, 100]", range="[0, 1]", default="0.8", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* tmax_max;
    int tmax_max_len;
    // @desc: alias="cfg_wt", type="f32", size="[1, 100]", range="[0, 1]", default="0.8", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* cfg_wt;
    int cfg_wt_len;
    // @desc: alias="cfg_air", type="f32", size="[1, 100]", range="[0, 255]", default="210", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* cfg_air;
    int cfg_air_len;
    // @desc: alias="cfg_tmax", type="f32", size="[1, 100]", range="[0, 1]", default="0.2", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* cfg_tmax;
    int cfg_tmax_len;
    // @desc: alias="dc_weitcur", type="f32", size="[1, 100]", range="[0, 1]", default="1", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* dc_weitcur;
    int dc_weitcur_len;
    // @desc: alias="bf_weight", type="f32", size="[1, 100]", range="[0, 1]", default="0.5", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* bf_weight;
    int bf_weight_len;
    // @desc: alias="range_sigma", type="f32", size="[1, 100]", range="[0, 1]", default="0.04", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* range_sigma;
    int range_sigma_len;
    // @desc: alias="space_sigma_pre", type="f32", size="[1, 100]", range="[0, 1]", default="0.4", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* space_sigma_pre;
    int space_sigma_pre_len;
    // @desc: alias="space_sigma_cur", type="f32", size="[1, 100]", range="[0, 1]", default="0.8", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* space_sigma_cur;
    int space_sigma_cur_len;
} DehazeDataV21_t;

typedef struct Dehaze_Setting_V21_s {
    // @desc: type="bool", alias="en", default="1", hide="0", ro="0" 
    
   _Bool 
        en;
    // @desc: type="bool", alias="air_lc_en", default="1", hide="0", ro="0" 
    
   _Bool 
        air_lc_en;
    // @desc: alias="stab_fnum", type="f32", size="[1,1]", range="[0, 31]", default="8.0", digit="[4]", hide="0", ro="0" 
    float stab_fnum;
    // @desc: alias="sigma", type="f32", size="[1,1]", range="[0, 255]", default="6.0", digit="[4]", hide="0", ro="0" 
    float sigma;
    // @desc: alias="wt_sigma", type="f32", size="[1,1]", range="[0, 256]", default="8.0", digit="[4]", hide="0", ro="0" 
    float wt_sigma;
    // @desc: alias="air_sigma", type="f32", size="[1,1]", range="[0, 255]", default="120.0", digit="[4]", hide="0", ro="0" 
    float air_sigma;
    // @desc: alias="tmax_sigma", type="f32", size="[1,1]", range="[0, 1]", default="0.0100", digit="[4]", hide="0", ro="0" 
    float tmax_sigma;
    // @desc: alias="pre_wet", type="f32", size="[1,1]", range="[0, 1]", default="0.0100", digit="[4]", hide="0", ro="0" 
    float pre_wet;
    // @desc: alias="DehazeData", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    DehazeDataV21_t DehazeData;
} Dehaze_Setting_V21_t;

typedef struct EnhanceDataV21_s {
    // @desc: alias="EnvLv", type="f32", size="[1, 100]", range="[0, 1]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* EnvLv;
    int EnvLv_len;
    // @desc: alias="enhance_value", type="f32", size="[1, 100]", range="[0, 32]", default="1", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* enhance_value;
    int enhance_value_len;
    // @desc: alias="enhance_chroma", type="f32", size="[1, 100]", range="[0, 32]", default="1", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* enhance_chroma;
    int enhance_chroma_len;
} EnhanceDataV21_t;

typedef struct Enhance_Setting_V21_s {
    // @desc: type="bool", alias="en", default="1", hide="0", ro="0" 
    
   _Bool 
        en;
    // @desc: alias="enhance_curve", type="f32", size="[1, 17]", range="[0, 1024]", default="[0 64 128 192 256 320 384 448 512 576 640 704 768 832 896 960 1023]", digit="[0]", dynamic="0", hide="0", ro="0" 
    float enhance_curve[17];
    // @desc: alias="EnhanceData", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    EnhanceDataV21_t EnhanceData;
} Enhance_Setting_V21_t;

typedef struct HistDataV21_s {
    // @desc: alias="EnvLv", type="f32", size="[1, 100]", range="[0, 1]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* EnvLv;
    int EnvLv_len;
    // @desc: alias="hist_gratio", type="f32", size="[1, 100]", range="[0, 32]", default="2", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* hist_gratio;
    int hist_gratio_len;
    // @desc: alias="hist_th_off", type="f32", size="[1, 100]", range="[0, 255]", default="64", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* hist_th_off;
    int hist_th_off_len;
    // @desc: alias="hist_k", type="f32", size="[1, 100]", range="[0, 8]", default="2", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* hist_k;
    int hist_k_len;
    // @desc: alias="hist_min", type="f32", size="[1, 100]", range="[0, 2]", default="0.016", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* hist_min;
    int hist_min_len;
    // @desc: alias="hist_scale", type="f32", size="[1, 100]", range="[0, 32]", default="0.09", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* hist_scale;
    int hist_scale_len;
    // @desc: alias="cfg_gratio", type="f32", size="[1, 100]", range="[0, 32]", default="2", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* cfg_gratio;
    int cfg_gratio_len;
} HistDataV21_t;

typedef struct Hist_setting_V21_s {
    // @desc: type="bool", alias="en", default="1", hide="0", ro="0" 
    
   _Bool 
        en;
    // @desc: type="bool", alias="hist_para_en", default="1", hide="0", ro="0" 
    
   _Bool 
        hist_para_en;
    // @desc: alias="HistData", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    HistDataV21_t HistData;
} Hist_setting_V21_t;

typedef struct CalibDbDehazeV21_s {
    // @desc: type="bool", alias="en", default="1", hide="0", ro="0" 
    
   _Bool 
        Enable;
    // @desc: alias="cfg_alpha", type="f32", size="[1,1]", range="[0, 1]", default="1", digit="[4]", hide="0", ro="0" 
    float cfg_alpha;
    // @desc: alias="ByPassThr", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[4]", hide="0", ro="0" 
    float ByPassThr;
    // @desc: alias="dehaze_setting", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    Dehaze_Setting_V21_t dehaze_setting;
    // @desc: alias="enhance_setting", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    Enhance_Setting_V21_t enhance_setting;
    // @desc: alias="hist_setting", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    Hist_setting_V21_t hist_setting;
} CalibDbDehazeV21_t;

typedef struct CalibDbV2_dehaze_V21_s {
    // @desc: alias="DehazeTuningPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbDehazeV21_t DehazeTuningPara;
} CalibDbV2_dehaze_V21_t;

typedef struct CalibDbV2_dehaze_V30_s {
    // @desc: alias="DehazeTuningPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbDehazeV21_t DehazeTuningPara;
} CalibDbV2_dehaze_V30_t;



/*
 * adpcc_head.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */






typedef struct CalibDb_Dpcc_set_RK_V20_s {
    // @desc: alias="RK_enable", type="u8", size="[1, 13]", range="[0, 1]", default="[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char RK_enable[13];
    // @desc: alias="rb_sw_mindis", type="u8", size="[1, 13]", range="[0, 255]", default="[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char rb_sw_mindis[13];
    // @desc: alias="g_sw_mindis", type="u8", size="[1, 13]", range="[0, 255]", default="[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char g_sw_mindis[13];
    // @desc: alias="sw_dis_scale_min", type="u8", size="[1, 13]", range="[0, 63]", default="[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char sw_dis_scale_min[13];
    // @desc: alias="sw_dis_scale_max", type="u8", size="[1, 13]", range="[0, 63]", default="[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char sw_dis_scale_max[13];
} CalibDb_Dpcc_set_RK_V20_t;

typedef struct CalibDb_Dpcc_set_LC_V20_s {
    // @desc: alias="LC_enable", type="u8", size="[1, 13]", range="[0, 1]", default="[1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char LC_enable[13];
    // @desc: alias="rb_line_thr", type="u8", size="[1, 13]", range="[0, 255]", default="[8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char rb_line_thr[13];
    // @desc: alias="g_line_thr", type="u8", size="[1, 13]", range="[0, 255]", default="[8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char g_line_thr[13];
    // @desc: alias="rb_line_mad_fac", type="u8", size="[1, 13]", range="[0, 63]", default="[4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char rb_line_mad_fac[13];
    // @desc: alias="g_line_mad_fac", type="u8", size="[1, 13]", range="[0, 63]", default="[4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char g_line_mad_fac[13];
} CalibDb_Dpcc_set_LC_V20_t;

typedef struct CalibDb_Dpcc_set_PG_V20_s {
    // @desc: alias="PG_enable", type="u8", size="[1, 13]", range="[0, 1]", default="[1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char PG_enable[13];
    // @desc: alias="rb_pg_fac", type="u8", size="[1, 13]", range="[0, 63]", default="[4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char rb_pg_fac[13];
    // @desc: alias="g_pg_fac", type="u8", size="[1, 13]", range="[0, 63]", default="[3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char g_pg_fac[13];
} CalibDb_Dpcc_set_PG_V20_t;

typedef struct CalibDb_Dpcc_set_RND_V20_s {
    // @desc: alias="RND_enable", type="u8", size="[1, 13]", range="[0, 1]", default="[1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char RND_enable[13];
    // @desc: alias="rb_rnd_thr", type="u8", size="[1, 13]", range="[0, 255]", default="[8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char rb_rnd_thr[13];
    // @desc: alias="g_rnd_thr", type="u8", size="[1, 13]", range="[0, 255]", default="[8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char g_rnd_thr[13];
    // @desc: alias="rb_rnd_offs", type="u8", size="[1, 13]", range="[0, 3]", default="[3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char rb_rnd_offs[13];
    // @desc: alias="g_rnd_offs", type="u8", size="[1, 13]", range="[0, 3]", default="[3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char g_rnd_offs[13];
} CalibDb_Dpcc_set_RND_V20_t;

typedef struct CalibDb_Dpcc_set_RG_V20_s {
    // @desc: alias="RG_enable", type="u8", size="[1, 13]", range="[0, 1]", default="[1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char RG_enable[13];
    // @desc: alias="rb_rg_fac", type="u8", size="[1, 13]", range="[0, 63]", default="[8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char rb_rg_fac[13];
    // @desc: alias="g_rg_fac", type="u8", size="[1, 13]", range="[0, 63]", default="[8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char g_rg_fac[13];
} CalibDb_Dpcc_set_RG_V20_t;

typedef struct CalibDb_Dpcc_set_RO_V20_s {
    // @desc: alias="RO_enable", type="u8", size="[1, 13]", range="[0, 1]", default="[1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char RO_enable[13];
    // @desc: alias="rb_ro_lim", type="u8", size="[1, 13]", range="[0, 3]", default="[1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char rb_ro_lim[13];
    // @desc: alias="g_ro_lim", type="u8", size="[1, 13]", range="[0, 3]", default="[1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char g_ro_lim[13];
} CalibDb_Dpcc_set_RO_V20_t;

typedef struct CalibDb_Dpcc_set_V20_s {
    // @desc: alias="RK", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Dpcc_set_RK_V20_t RK;
    // @desc: alias="LC", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Dpcc_set_LC_V20_t LC;
    // @desc: alias="PG", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Dpcc_set_PG_V20_t PG;
    // @desc: alias="RND", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Dpcc_set_RND_V20_t RND;
    // @desc: alias="RG", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Dpcc_set_RG_V20_t RG;
    // @desc: alias="RO", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Dpcc_set_RO_V20_t RO;
} CalibDb_Dpcc_set_V20_t;

typedef struct FastData_s {
    // @desc: alias="ISO", type="f32", size="[1, 100]", range="[50, 10000000]", default="50", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* ISO;
    int ISO_len;
    // @desc: alias="Single_level", type="u32", size="[1, 100]", range="[1, 10]", default="1", digit="[0]", dynamic="1", hide="0", ro="0" 
    int* Single_level;
    int Single_level_len;
    // @desc: alias="Double_level", type="u32", size="[1, 100]", range="[1, 10]", default="1", digit="[0]", dynamic="1", hide="0", ro="0" 
    int* Double_level;
    int Double_level_len;
    // @desc: alias="Triple_level", type="u32", size="[1, 100]", range="[1, 10]", default="1", digit="[0]", dynamic="1", hide="0", ro="0" 
    int* Triple_level;
    int Triple_level_len;
} FastData_t;

typedef struct CalibDb_Dpcc_Fast_Mode_V20_s {
    // @desc: type="bool", alias="Fast_mode_en", default="1", hide="0", ro="0" 
    
   _Bool 
                 Fast_mode_en;
    // @desc: type="bool", alias="Single_enable", default="1", hide="0", ro="0" 
    
   _Bool 
        Single_enable;
    // @desc: type="bool", alias="Double_enable", default="1", hide="0", ro="0" 
    
   _Bool 
        Double_enable;
    // @desc: type="bool", alias="Triple_enable", default="1", hide="0", ro="0" 
    
   _Bool 
        Triple_enable;
    // @desc: alias="Fast_Data", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    FastData_t Fast_Data;
} CalibDb_Dpcc_Fast_Mode_V20_t;

typedef struct SetData_s {
    // @desc: alias="RK", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Dpcc_set_RK_V20_t RK;
    // @desc: alias="LC", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Dpcc_set_LC_V20_t LC;
    // @desc: alias="PG", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Dpcc_set_PG_V20_t PG;
    // @desc: alias="RND", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Dpcc_set_RND_V20_t RND;
    // @desc: alias="RG", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Dpcc_set_RG_V20_t RG;
    // @desc: alias="RO", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Dpcc_set_RO_V20_t RO;
} SetData_t;

typedef struct SetEnable_s {
    // @desc: alias="ISO", type="u32", size="[1, 13]", range="[50, 100000000]", default="[50 100 200 400 800 1600 3200 6400 12800 25600 51200 102400 204800]", digit="[4]", dynamic="0", hide="0", ro="0" 
    int ISO[13];
    // @desc: alias="fix_set", type="u16", size="[1, 13]", range="[0, 1]", default="[0 0 0 0 0 0 0 0 0 0 0 0 0]", digit="[0]", dynamic="0", hide="0", ro="0" 
    int fix_set[13];
    // @desc: alias="set1", type="u16", size="[1, 13]", range="[0, 1]", default="[0 0 0 0 0 0 0 0 0 0 0 0 0]", digit="[0]", dynamic="0", hide="0", ro="0" 
    int set1[13];
    // @desc: alias="set2", type="u16", size="[1, 13]", range="[0, 1]", default="[0 0 0 0 0 0 0 0 0 0 0 0 0]", digit="[0]", dynamic="0", hide="0", ro="0" 
    int set2[13];
    // @desc: alias="set3", type="u16", size="[1, 13]", range="[0, 1]", default="[0 0 0 0 0 0 0 0 0 0 0 0 0]", digit="[0]", dynamic="0", hide="0", ro="0" 
    int set3[13];
} SetEnable_t;

typedef struct CalibDb_Dpcc_Expert_Mode_V20_s {
    //@desc: type="bool", alias="stage1_Enable", default="1", hide="0", ro="0" 
    
   _Bool 
              stage1_Enable;
    // @desc: type="bool", alias="grayscale_mode", default="0", hide="0", ro="0" 
    
   _Bool 
              grayscale_mode;
    // @desc: type="bool", alias="dpcc_out_sel", default="1", hide="0", ro="0" 
    
   _Bool 
              dpcc_out_sel;
    // @desc: type="bool", alias="stage1_g_3x3", default="0", hide="0", ro="0" 
    
   _Bool 
               stage1_g_3x3;
    // @desc: type="bool", alias="stage1_rb_3x3", default="0", hide="0", ro="0" 
    
   _Bool 
               stage1_rb_3x3;
    // @desc: type="bool", alias="stage1_inc_rb_center", default="1", hide="0", ro="0" 
    
   _Bool 
           stage1_inc_rb_center;
    // @desc: type="bool", alias="stage1_inc_g_center", default="1", hide="0", ro="0" 
    
   _Bool 
           stage1_inc_g_center;
    // @desc: alias="rk_out_sel", type="u8", size="[1,1]", range="[0, 2]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned char rk_out_sel;
    // @desc: alias="SetEnable", type="struct", ui_module="array_table_ui", hide="0", ro="0" 
    SetEnable_t SetEnable;
    // @desc: alias="set1", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    SetData_t set1;
    // @desc: alias="set2", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    SetData_t set2;
    // @desc: alias="set3", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    SetData_t set3;
} CalibDb_Dpcc_Expert_Mode_V20_t;

typedef struct CalibDb_Dpcc_Pdaf_V20_s {
    // @desc: type="bool", alias="en", default="0", hide="0", ro="0" 
    
   _Bool 
        en;
    // @desc: alias="point_en", type="u16", size="[1, 16]", range="[1, 10]", default="[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char point_en[16];
    // @desc: alias="offsetx", type="u8", size="[1,1]", range="[0, 100]", default="0", digit="[0]", hide="0", ro="0" 
    int offsetx;
    // @desc: alias="offsety", type="u8", size="[1,1]", range="[0, 100]", default="0", digit="[0]", hide="0", ro="0" 
    int offsety;
    // @desc: alias="wrapx", type="u8", size="[1,1]", range="[0, 255]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned char wrapx;
    // @desc: alias="wrapy", type="u8", size="[1,1]", range="[0, 255]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned char wrapy;
    // @desc: alias="wrapx_num", type="u8", size="[1,1]", range="[0, 1023]", default="0", digit="[0]", hide="0", ro="0" 
    int wrapx_num;
    // @desc: alias="wrapy_num", type="u8", size="[1,1]", range="[0, 1023]", default="0", digit="[0]", hide="0", ro="0" 
    int wrapy_num;
    // @desc: alias="point_x", type="u16", size="[1, 16]", range="[1, 255]", default="[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]", digit="[0]", dynamic="0", ui_module="normal_ui_style", ro="0" 
    unsigned char point_x[16];
    // @desc: alias="point_y", type="u16", size="[1, 16]", range="[1, 255]", default="[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]", digit="[0]", dynamic="0", ui_module="normal_ui_style", ro="0" 
    unsigned char point_y[16];
    // @desc: alias="forward_med", type="u8", size="[1,1]", range="[0, 1]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned char forward_med;
} CalibDb_Dpcc_Pdaf_V20_t;

typedef struct SensorDpccData_s {
    // @desc: alias="ISO", type="f32", size="[1, 100]", range="[50, 10000000]", default="50", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* ISO;
    int ISO_len;
    // @desc: alias="level_single", type="u32", size="[1, 100]", range="[1, 10000000]", default="1", digit="[0]", dynamic="1", hide="0", ro="0" 
    int* level_single;
    int level_single_len;
    // @desc: alias="level_multiple", type="u32", size="[1, 100]", range="[1, 10000000]", default="1", digit="[0]", dynamic="1", hide="0", ro="0" 
    int* level_multiple;
    int level_multiple_len;
} SensorDpccData_t;

typedef struct CalibDb_Dpcc_Sensor_V20_s {
    // @desc: type="bool", alias="sensor_dpcc_auto_en", default="1", hide="0", ro="0" 
    
   _Bool 
        sensor_dpcc_auto_en;
    // @desc: alias="max_level", type="u8", size="[1,1]", range="[0, 100]", default="1", digit="[0]", hide="0", ro="0" 
    int max_level;
    // @desc: alias="SensorDpcc_Data", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    SensorDpccData_t SensorDpcc_Data;
} CalibDb_Dpcc_Sensor_V20_t;

typedef struct CalibDbDpccV20_s {
    // @desc: type="bool", alias="Enable", default="1", hide="0", ro="0" 
    
   _Bool 
                               Enable;
    // @desc: alias="Fast_Mode", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Dpcc_Fast_Mode_V20_t Fast_Mode;
    // @desc: alias="Expert_Mode", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Dpcc_Expert_Mode_V20_t Expert_Mode;
    // @desc: alias="CalibDb_Dpcc_Pdaf_V20_t", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Dpcc_Pdaf_V20_t Dpcc_pdaf;
    // @desc: alias="Sensor_dpcc", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Dpcc_Sensor_V20_t Sensor_dpcc;
} CalibDbDpccV20_t;

typedef struct CalibDbV2_Dpcc_s {
    // @desc: alias="DpccTuningPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbDpccV20_t DpccTuningPara;
} CalibDbV2_Dpcc_t;





typedef struct AdrcGain_s {
    // @desc: alias="EnvLv", type="f32", size="[1, 100]", range="[0, 1]", default="0", digit="[3]", dynamic="1", hide="0", ro="0" 
    float* EnvLv;
    int EnvLv_len;
    // @desc: alias="DrcGain", type="f32", size="[1, 100]", range="[1, 8]", default="4", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* DrcGain; //sw_drc_gain
    int DrcGain_len;
    // @desc: alias="Alpha", type="f32", size="[1, 100]", range="[0, 1]", default="0.2", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* Alpha;
    int Alpha_len;
    // @desc: alias="Clip", type="f32", size="[1, 100]", range="[0, 64]", default="16", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* Clip; //sw_drc_position, step: 1/255
    int Clip_len;
} AdrcGain_t;

typedef struct HighLight_s {
    // @desc: alias="EnvLv", type="f32", size="[1, 100]", range="[0, 1]", default="0", digit="[3]", dynamic="1", hide="0", ro="0" 
    float* EnvLv;
    int EnvLv_len;
    // @desc: alias="Strength", type="f32", size="[1, 100]", range="[0, 1]", default="1", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* Strength; //sw_drc_weig_maxl,  range[0,1], step 1/16
    int Strength_len;
} HighLight_t;

typedef struct LocalData_s
{
    // @desc: alias="EnvLv", type="f32", size="[1, 100]", range="[0, 1]", default="0", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* EnvLv;
    int EnvLv_len;
    // @desc: alias="LocalWeit", type="f32", size="[1, 100]", range="[0, 1]", default="1", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* LocalWeit; //sw_drc_weig_bilat, range[0 , 1], step: 1/16
    int LocalWeit_len;
    // @desc: alias="GlobalContrast", type="f32", size="[1, 100]", range="[0, 1]", default="0", digit="[3]", dynamic="1", hide="0", ro="0" 
    float* GlobalContrast; //sw_drc_lpdetail_ratio, setp 1/4096
    int GlobalContrast_len;
    // @desc: alias="LoLitContrast", type="f32", size="[1, 100]", range="[0, 1]", default="0", digit="[3]", dynamic="1", hide="0", ro="0" 
    float* LoLitContrast; //sw_drc_hpdetail_ratio, setp 1/4096
    int LoLitContrast_len;
} LocalData_t;

typedef struct local_s {
    // @desc: alias="LocalTMOData", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    LocalData_t LocalTMOData;
    // @desc: alias="curPixWeit", type="f32", size="[1,1]", range="[0, 1]", default="0.37", digit="[3]", hide="0", ro="0" 
    float curPixWeit; //sw_drc_weicur_pix,  range[0,1],step: 1/255
    // @desc: alias="preFrameWeit", type="f32", size="[1,1]", range="[0, 1]", default="1.0", digit="[3]", hide="0", ro="0" 
    float preFrameWeit;//sw_adrc_weipre_frame ,range[0,1],step: 1/255
    // @desc: alias="Range_force_sgm", type="f32", size="[1,1]", range="[0, 1]", default="0.0", digit="[4]", hide="0", ro="0" 
    float Range_force_sgm; //sw_drc_force_sgm_inv0 ,range[0,1], step 1/8191
    // @desc: alias="Range_sgm_cur", type="f32", size="[1,1]", range="[0, 1]", default="0.125", digit="[4]", hide="0", ro="0" 
    float Range_sgm_cur; //sw_drc_range_sgm_inv1, range[0,1], step 1/8191
    // @desc: alias="Range_sgm_pre", type="f32", size="[1,1]", range="[0, 1]", default="0.125", digit="[4]", hide="0", ro="0" 
    float Range_sgm_pre; //sw_drc_range_sgm_inv0,range[0,1], step 1/8191
    // @desc: alias="Space_sgm_cur", type="u16", size="[1,1]", range="[0, 4095]", default="4068", digit="[0]", hide="0", ro="0" 
    int Space_sgm_cur; //sw_drc_space_sgm_inv1
    // @desc: alias="Space_sgm_pre", type="u16", size="[1,1]", range="[0, 4095]", default="3968", digit="[0]", hide="0", ro="0" 
    int Space_sgm_pre; //sw_drc_space_sgm_inv0
} local_t;

typedef enum CompressMode_e {
    COMPRESS_AUTO = 0,
    COMPRESS_MANUAL = 1,
} CompressMode_t;

typedef struct Compress_s {
    // @desc: type="enum", alias="Mode", enum_def="CompressMode_t", default="COMPRESS_AUTO", ro="0" 
    CompressMode_t Mode;
    // @desc: alias="Manual_curve", type="u32", size="[1, 17]", range="[0, 8192]", default="[0 558 1087 1588 2063 2515 2944 3353 3744 4473 5139 5751 6316 6838 7322 7772 8192]", digit="[0]", dynamic="0", ui_module="curve_table", ro="0" 
    uint16_t Manual_curve[17];
} Compress_t;

typedef struct CalibDbV2_Adrc_s {
    // @desc: type="bool", alias="Enable", default="1", hide="0", ro="0" 
    
   _Bool 
        Enable;
    // @desc: alias="DrcGain", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    AdrcGain_t DrcGain;
    // @desc: alias="HiLight", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    HighLight_t HiLight;
    // @desc: alias="LocalTMOSetting", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    local_t LocalTMOSetting;
    // @desc: alias="CompressSetting", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    Compress_t CompressSetting;
    // @desc: alias="Scale_y", type="u16", size="[1, 17]", range="[0, 2048]", default="[0 2 20 76 193 381 631 772 919 1066 1211 1479 1700 1863 1968 2024 2048]", digit="[0]", dynamic="0", hide="0", ro="0" 
    int Scale_y[17];
    // @desc: alias="ByPassThr", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[4]", hide="0", ro="0" 
    float ByPassThr;
    // @desc: alias="Edge_Weit", type="f32", size="[1,1]", range="[0, 1]", default="1", digit="[3]", hide="0", ro="0" 
    float Edge_Weit; //sw_drc_edge_scl, range[0,1], step 1/255
    // @desc: type="bool", alias="OutPutLongFrame", default="0", hide="0", ro="0" 
    
   _Bool 
         OutPutLongFrame; //sw_drc_min_ogain
    // @desc: alias="IIR_frame", type="u8", size="[1,1]", range="[1, 1000]", default="16", digit="[0]", hide="0", ro="0" 
    int IIR_frame; //sw_drc_iir_frame, range [1, 1000]
    // @desc: alias="Tolerance", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[3]", hide="0", ro="0" 
    float Tolerance;
    // @desc: alias="damp", type="f32", size="[1,1]", range="[0, 1]", default="0.9", digit="[3]", hide="0", ro="0" 
    float damp;
} CalibDbV2_Adrc_t;

typedef struct CalibDbV2_drc_s {
    // @desc: alias="DrcTuningPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Adrc_t DrcTuningPara;
} CalibDbV2_drc_t;

typedef struct LocalDataV2_s
{
    // @desc: alias="EnvLv", type="f32", size="[1, 100]", range="[0, 1]", default="0", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* EnvLv;
    int EnvLv_len;
    // @desc: alias="LocalWeit", type="f32", size="[1, 100]", range="[0, 1]", default="1", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* LocalWeit; //sw_drc_weig_bilat, range[0 , 1], step: 1/16
    int LocalWeit_len;
    // @desc: alias="LocalAutoEnable", type="u8", size="[1, 100]", range="[0, 1]", default="1", digit="[0]", dynamic="1", hide="0", ro="0" 
    int* LocalAutoEnable; //sw_adrc_enable_soft_thd, range[0 , 1], step: 1
    int LocalAutoEnable_len;
    // @desc: alias="LocalAutoWeit", type="f32", size="[1, 100]", range="[0, 1]", default="0.037477", digit="[5]", dynamic="1", hide="0", ro="0" 
    float* LocalAutoWeit; //sw_adrc_bilat_soft_thd, range[0 , 1], step: 1/0x3fff
    int LocalAutoWeit_len;
    // @desc: alias="GlobalContrast", type="f32", size="[1, 100]", range="[0, 1]", default="0", digit="[3]", dynamic="1", hide="0", ro="0" 
    float* GlobalContrast; //sw_drc_lpdetail_ratio, setp 1/4096
    int GlobalContrast_len;
    // @desc: alias="LoLitContrast", type="f32", size="[1, 100]", range="[0, 1]", default="0", digit="[3]", dynamic="1", hide="0", ro="0" 
    float* LoLitContrast; //sw_drc_hpdetail_ratio, setp 1/4096
    int LoLitContrast_len;
} LocalDataV2_t;

typedef struct localV2_s {
    // @desc: alias="LocalData", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    LocalDataV2_t LocalData;
    // @desc: alias="curPixWeit", type="f32", size="[1,1]", range="[0, 1]", default="0.37", digit="[3]", hide="0", ro="0" 
    float curPixWeit; //sw_drc_weicur_pix,  range[0,1],step: 1/255
    // @desc: alias="preFrameWeit", type="f32", size="[1,1]", range="[0, 1]", default="1.0", digit="[3]", hide="0", ro="0" 
    float preFrameWeit;//sw_adrc_weipre_frame ,range[0,1],step: 1/255
    // @desc: alias="Range_force_sgm", type="f32", size="[1,1]", range="[0, 1]", default="0.0", digit="[4]", hide="0", ro="0" 
    float Range_force_sgm; //sw_drc_force_sgm_inv0 ,range[0,1], step 1/8191
    // @desc: alias="Range_sgm_cur", type="f32", size="[1,1]", range="[0, 1]", default="0.125", digit="[4]", hide="0", ro="0" 
    float Range_sgm_cur; //sw_drc_range_sgm_inv1, range[0,1], step 1/8191
    // @desc: alias="Range_sgm_pre", type="f32", size="[1,1]", range="[0, 1]", default="0.125", digit="[4]", hide="0", ro="0" 
    float Range_sgm_pre; //sw_drc_range_sgm_inv0,range[0,1], step 1/8191
    // @desc: alias="Space_sgm_cur", type="u16", size="[1,1]", range="[0, 4095]", default="4068", digit="[0]", hide="0", ro="0" 
    int Space_sgm_cur; //sw_drc_space_sgm_inv1
    // @desc: alias="Space_sgm_pre", type="u16", size="[1,1]", range="[0, 4095]", default="3968", digit="[0]", hide="0", ro="0" 
    int Space_sgm_pre; //sw_drc_space_sgm_inv0
} localV2_t;

typedef struct CalibDbV2_Adrc_V2_s {
    // @desc: type="bool", alias="Enable", default="1", hide="0", ro="0" 
    
   _Bool 
        Enable;
    // @desc: alias="DrcGain", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    AdrcGain_t DrcGain;
    // @desc: alias="HiLight", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    HighLight_t HiLight;
    // @desc: alias="LocalSetting", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    localV2_t LocalSetting;
    // @desc: alias="CompressSetting", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    Compress_t CompressSetting;
    // @desc: alias="Scale_y", type="u16", size="[1, 17]", range="[0, 2048]", default="[0 2 20 76 193 381 631 772 919 1066 1211 1479 1700 1863 1968 2024 2048]", digit="[0]", dynamic="0", hide="0", ro="0" 
    int Scale_y[17];
    // @desc: alias="ByPassThr", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[4]", hide="0", ro="0" 
    float ByPassThr;
    // @desc: alias="Edge_Weit", type="f32", size="[1,1]", range="[0, 1]", default="1", digit="[3]", hide="0", ro="0" 
    float Edge_Weit; //sw_drc_edge_scl, range[0,1], step 1/255
    // @desc: type="bool", alias="OutPutLongFrame", default="0", hide="0", ro="0" 
    
   _Bool 
         OutPutLongFrame; //sw_drc_min_ogain
    // @desc: alias="IIR_frame", type="u8", size="[1,1]", range="[1, 1000]", default="16", digit="[0]", hide="0", ro="0" 
    int IIR_frame; //sw_drc_iir_frame, range [1, 1000]
    // @desc: alias="Tolerance", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[3]", hide="0", ro="0" 
    float Tolerance;
    // @desc: alias="damp", type="f32", size="[1,1]", range="[0, 1]", default="0.9", digit="[3]", hide="0", ro="0" 
    float damp;
} CalibDbV2_Adrc_V2_t;

typedef struct CalibDbV2_drc_V2_s {
    // @desc: alias="DrcTuningPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Adrc_V2_t DrcTuningPara;
} CalibDbV2_drc_V2_t;


       
/*
 * aec_head.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */



// #define M4_STRUCT_DESC(ALIAS, SIZE, UI_MODULE)
// #define M4_NUMBER_DESC(ALIAS, TYPE, SIZE, RANGE, DEFAULT)
// #define M4_STRING_DESC(ALIAS, SIZE, RANGE, DEFAULT)
// #define M4_ENUM_DESC(ALIAS, ENUM, DEFAULT)

/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */





/*****************************************************************************/
/**
 * @brief   ISP2.0 AEC enum Params
 */
/*****************************************************************************/
typedef enum _CalibDb_HdrAeRatioTypeV2_e {
    AECV2_HDR_RATIOTYPE_MODE_AUTO,
    AECV2_HDR_RATIOTYPE_MODE_FIX,
} CalibDb_HdrAeRatioTypeV2_t;

typedef enum _CalibDb_AeStrategyModeV2_e {
    AECV2_STRATEGY_MODE_LOWLIGHT_PRIOR,
    AECV2_STRATEGY_MODE_HIGHLIGHT_PRIOR,
} CalibDb_AeStrategyModeV2_t;

typedef enum _CalibDb_AeHdrLongFrmModeV2_e {
    AECV2_HDR_LONGFRMMODE_NORMAL = 0,
    AECV2_HDR_LONGFRMMODE_AUTO_LONG_FRAME = 1,
    AECV2_HDR_LONGFRMMODE_LONG_FRAME = 2,
} CalibDb_AeHdrLongFrmModeV2_t;

typedef enum _CalibDb_AecMeasAreaModeV2_e {
    AECV2_MEASURE_AREA_AUTO = 0,
    AECV2_MEASURE_AREA_UP,
    AECV2_MEASURE_AREA_BOTTOM,
    AECV2_MEASURE_AREA_LEFT,
    AECV2_MEASURE_AREA_RIGHT,
    AECV2_MEASURE_AREA_CENTER,
} CalibDb_AecMeasAreaModeV2_t;

typedef enum _CalibDb_FlickerFreqV2_e {
    AECV2_FLICKER_FREQUENCY_OFF = 0,
    AECV2_FLICKER_FREQUENCY_50HZ = 1,
    AECV2_FLICKER_FREQUENCY_60HZ = 2,
} CalibDb_FlickerFreqV2_t;

typedef enum _CalibDb_AntiFlickerModeV2_e {
    AECV2_ANTIFLICKER_AUTO_MODE,
    AECV2_ANTIFLICKER_NORMAL_MODE,
} CalibDb_AntiFlickerModeV2_t;

typedef enum _CalibDb_IrisTypeV2_e {
    IRISV2_DC_TYPE = 0,
    IRISV2_P_TYPE = 1,
} CalibDb_IrisTypeV2_t;

typedef enum _CalibDb_CamYRangeModeV2_e {
    CAM_YRANGEV2_MODE_INVALID = 0, /**< invalid y range mode   */
    CAM_YRANGEV2_MODE_FULL, /**< Y = 0.299 * R + 0.587 * G + 0.114 * B,full range BT601*/
    CAM_YRANGEV2_MODE_LIMITED, /**< Y = 16 + 0.25R + 0.5G + 0.1094B,limited range*/
    CAM_YRANGEV2_MODE_MAX,
} CalibDb_CamYRangeModeV2_t;

typedef enum _CalibDb_CamRawStatsModeV2_e {
    CAM_RAWSTATSV2_MODE_INVALID = 0, /**< lower border (only for an internal evaluation) */
    CAM_RAWSTATSV2_MODE_R, /**< R channel */
    CAM_RAWSTATSV2_MODE_G, /**< G channel */
    CAM_RAWSTATSV2_MODE_B, /**< B channel */
    CAM_RAWSTATSV2_MODE_Y, /**< luminance channel */
    CAM_RAWSTATSV2_MODE_MAX, /**< upper border (only for an internal evaluation) */
} CalibDb_CamRawStatsModeV2_t;

typedef enum _CalibDb_CamHistStatsModeV2_e {
    CAM_HISTV2_MODE_INVALID = 0, /**< lower border (only for an internal evaluation) */
    CAM_HISTV2_MODE_RGB_COMBINED = 1, /**< RGB combined histogram, only available for SiHist */
    CAM_HISTV2_MODE_R = 2, /**< R histogram */
    CAM_HISTV2_MODE_G = 3, /**< G histogram */
    CAM_HISTV2_MODE_B = 4, /**< B histogram */
    CAM_HISTV2_MODE_Y = 5, /**< Y luminance histogram */
    CAM_HISTV2_MODE_MAX, /**< upper border (only for an internal evaluation) */
} CalibDb_CamHistStatsModeV2_t;

/*****************************************************************************/
/**
 * @brief   ISP2.0 AEC algo CommonCtrl Config Params
 */
/*****************************************************************************/
typedef struct CalibDb_AeDelayFrmNumV2_s {
    // @desc: alias="BlackDelay", type="u8", size="[1,1]", range="[0, 255]", default="0", digit="[0]", hide="0", ro="0" 
    uint8_t BlackDelay;

    // @desc: alias="WhiteDelay", type="u8", size="[1,1]", range="[0, 255]", default="0", digit="[0]", hide="0", ro="0" 
    uint8_t WhiteDelay;
} CalibDb_AeDelayFrmNumV2_t;

typedef struct CalibDb_AeSpeedV2_s {
    // @desc: type="bool", alias="SmoothEn", default="1", hide="0", ro="0" 
    
   _Bool 
                           SmoothEn;
    // @desc: type="bool", alias="DyDampEn", default="1", hide="0", ro="0" 
    
   _Bool 
                           DyDampEn;
    // @desc: alias="DampOver", type="f32", size="[1,1]", range="[0, 1.00]", default="0.15", digit="[2]", hide="0", ro="0" 
    float DampOver;

    // @desc: alias="DampUnder", type="f32", size="[1,1]", range="[0, 1.00]", default="0.45", digit="[2]", hide="0", ro="0" 
    float DampUnder;

    // @desc: alias="DampDark2Bright", type="f32", size="[1,1]", range="[0, 1.00]", default="0.15", digit="[2]", hide="0", ro="0" 
    float DampDark2Bright;

    // @desc: alias="DampBright2Dark", type="f32", size="[1,1]", range="[0, 1.00]", default="0.45", digit="[2]", hide="0", ro="0" 
    float DampBright2Dark;
} CalibDb_AeSpeedV2_t;

typedef struct CalibDb_AeFrmRateAttrV2_s {
    // @desc: type="bool", alias="isFpsFix", default="1", hide="0", ro="0" 
    
   _Bool 
                           isFpsFix;

    // @desc: alias="FpsValue", type="f32", size="[1,1]", range="[0, 200]", default="0", digit="[1]", hide="0", ro="0" 
    float FpsValue;
} CalibDb_AeFrmRateAttrV2_t;

typedef struct CalibDb_AntiFlickerAttrV2_s {
    // @desc: type="bool", alias="enable", default="1", hide="0", ro="0" 
    
   _Bool 
                                  enable;

    // @desc: type="enum", alias="Frequency", enum_def="CalibDb_FlickerFreqV2_t", default="AECV2_FLICKER_FREQUENCY_50HZ", ro="0" 
    CalibDb_FlickerFreqV2_t Frequency;

    // @desc: type="enum", alias="Mode", enum_def="CalibDb_AntiFlickerModeV2_t", default="AECV2_ANTIFLICKER_AUTO_MODE", ro="0" 
    CalibDb_AntiFlickerModeV2_t Mode;
} CalibDb_AntiFlickerAttrV2_t;

//manual exposure
typedef struct CalibDb_LinMeAttrV2_s {
    // @desc: type="bool", alias="ManualTimeEn", default="1", hide="0", ro="0" 
    
   _Bool 
                        ManualTimeEn;

    // @desc: type="bool", alias="ManualGainEn", default="1", hide="0", ro="0" 
    
   _Bool 
                        ManualGainEn;

    // @desc: type="bool", alias="ManualIspDgainEn", default="1", hide="0", ro="0" 
    
   _Bool 
                        ManualIspDgainEn;

    // @desc: alias="TimeValue", type="f32", size="[1,1]", range="[0, 1]", default="0.003", digit="[6]", hide="0", ro="0" 
    float TimeValue; //unit: s = 10^6 us

    // @desc: alias="GainValue", type="f32", size="[1,1]", range="[1, 4096]", default="1", digit="[3]", hide="0", ro="0" 
    float GainValue;

    // @desc: alias="IspDGainValue", type="f32", size="[1,1]", range="[1, 4096]", default="1", digit="[3]", hide="0", ro="0" 
    float IspDGainValue;
} CalibDb_LinMeAttrV2_t;

typedef struct CalibDb_HdrMeAttrV2_s {
    // @desc: type="bool", alias="ManualTimeEn", default="1", hide="0", ro="0" 
    
   _Bool 
                           ManualTimeEn;

    // @desc: type="bool", alias="ManualGainEn", default="1", hide="0", ro="0" 
    
   _Bool 
                           ManualGainEn;

    // @desc: type="bool", alias="ManualIspDgainEn", default="1", hide="0", ro="0" 
    
   _Bool 
                           ManualIspDgainEn;

    // @desc: alias="TimeValue", type="f32", size="[1, 3]", range="[0, 1]", default="0.003", digit="[6]", dynamic="0", hide="0", ro="0" 
    float TimeValue[(3)];

    // @desc: alias="GainValue", type="f32", size="[1, 3]", range="[1, 4096]", default="1.0", digit="[3]", dynamic="0", hide="0", ro="0" 
    float GainValue[(3)];

    // @desc: alias="IspDGainValue", type="f32", size="[1, 3]", range="[1, 4096]", default="1.0", digit="[3]", dynamic="0", hide="0", ro="0" 
    float IspDGainValue[(3)];
} CalibDb_HdrMeAttrV2_t;

typedef struct CalibDb_MeAttrV2_s {
    // @desc: alias="LinearAE", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_LinMeAttrV2_t LinearAE;

    // @desc: alias="HdrAE", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_HdrMeAttrV2_t HdrAE;
} CalibDb_MeAttrV2_t;

//win_scale = [h_off, v_off, h_size, v_size], range=[0,1]
typedef struct CalibDb_Aec_WinScale_s {
    // @desc: alias="h_offs", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[2]", hide="0", ro="0" 
    float h_offs;

    // @desc: alias="v_offs", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[2]", hide="0", ro="0" 
    float v_offs;

    // @desc: alias="h_size", type="f32", size="[1,1]", range="[0, 1]", default="1", digit="[2]", hide="0", ro="0" 
    float h_size;

    // @desc: alias="v_size", type="f32", size="[1,1]", range="[0, 1]", default="1", digit="[2]", hide="0", ro="0" 
    float v_size;
} CalibDb_Aec_WinScale_t;

typedef struct CalibDb_Aec_WinScaleV2_t {

    // @desc: alias="InRawWinScale", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Aec_WinScale_t InRawWinScale;

    // @desc: alias="TmoRawWinScale", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Aec_WinScale_t TmoRawWinScale;

    // @desc: alias="YuvWinScale", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Aec_WinScale_t YuvWinScale;
} CalibDb_Aec_WinScaleV2_t;

typedef struct CalibDb_AeEnvLvCalibV2_s {
    // @desc: alias="CalibFNumber", type="f32", size="[1,1]", range="[0, 256]", default="1.6", digit="[2]", hide="0", ro="0" 
    float CalibFNumber;

    // @desc: alias="CurveCoeff", type="f32", size="[1, 2]", range="[-1024, 1024]", default="1.0", digit="[5]", dynamic="0", hide="0", ro="0" 
    float CurveCoeff[2];//y=ax+b, Coeff=[a,b]
} CalibDb_AeEnvLvCalibV2_t;

typedef struct CalibDb_AecCommon_AttrV2_s {
    // @desc: type="bool", alias="Enable", default="1", hide="0", ro="0" 
    
   _Bool 
                                     Enable;

    // @desc: alias="AecRunInterval", type="u8", size="[1,1]", range="[0, 255]", default="0", digit="[0]", hide="0", ro="0" 
    uint8_t AecRunInterval;

    // @desc: type="enum", alias="AecOpType", enum_def="RKAiqOPMode_t", default="RK_AIQ_OP_MODE_AUTO", ro="0" 
    RKAiqOPMode_t AecOpType;

    // @desc: type="enum", alias="HistStatsMode", enum_def="CalibDb_CamHistStatsModeV2_t", default="CAM_HISTV2_MODE_G", ro="0" 
    CalibDb_CamHistStatsModeV2_t HistStatsMode;

    // @desc: type="enum", alias="RawStatsMode", enum_def="CalibDb_CamRawStatsModeV2_t", default="CAM_RAWSTATSV2_MODE_G", ro="0" 
    CalibDb_CamRawStatsModeV2_t RawStatsMode;

    // @desc: type="enum", alias="YRangeMode", enum_def="CalibDb_CamYRangeModeV2_t", default="CAM_YRANGEV2_MODE_FULL", ro="0" 
    CalibDb_CamYRangeModeV2_t YRangeMode;

    // @desc: alias="AecGridWeight", type="u8", size="[15, 15]", range="[0, 32]", default="1", digit="[0]", dynamic="0", hide="0", ro="0" 
    uint8_t AecGridWeight[(225)];

    // @desc: alias="AecManualCtrl", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_MeAttrV2_t AecManualCtrl;

    // @desc: alias="AecSpeed", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_AeSpeedV2_t AecSpeed;

    // @desc: alias="AecDelayFrmNum", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_AeDelayFrmNumV2_t AecDelayFrmNum;

    // @desc: alias="AecFrameRateMode", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_AeFrmRateAttrV2_t AecFrameRateMode;

    // @desc: alias="AecAntiFlicker", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_AntiFlickerAttrV2_t AecAntiFlicker;

    // @desc: alias="AecEnvLvCalib", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_AeEnvLvCalibV2_t AecEnvLvCalib;

    // @desc: alias="AecWinScale", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Aec_WinScaleV2_t AecWinScale;
} CalibDb_AecCommon_AttrV2_t;

/*****************************************************************************/
/**
 * @brief   ISP2.0 AEC algo LinAE Config Params
 */
/*****************************************************************************/
typedef struct CalibDb_LinExpInitExpV2_s {
    // @desc: alias="InitTimeValue", type="f32", size="[1,1]", range="[0, 1]", default="0.003", digit="[6]", hide="0", ro="0" 
    float InitTimeValue;

    // @desc: alias="InitGainValue", type="f32", size="[1,1]", range="[1, 4096]", default="1", digit="[3]", hide="0", ro="0" 
    float InitGainValue;

    // @desc: alias="InitIspDGainValue", type="f32", size="[1,1]", range="[1, 4096]", default="1", digit="[3]", hide="0", ro="0" 
    float InitIspDGainValue;

    // @desc: alias="InitPIrisGainValue", type="s32", size="[1,1]", range="[1, 4096]", default="1024", digit="[0]", hide="0", ro="0" 
    int InitPIrisGainValue;

    // @desc: alias="InitDCIrisDutyValue", type="s32", size="[1,1]", range="[0, 100]", default="100", digit="[0]", hide="0", ro="0" 
    int InitDCIrisDutyValue;
} CalibDb_LinExpInitExpV2_t;

typedef struct CalibDb_LinAeRoute_AttrV2_s {
    // @desc: alias="TimeDot", type="f32", size="[1, 6]", range="[0, 1]", default="0", digit="[6]", dynamic="1", hide="0", ro="0" 
    float* TimeDot;
    int TimeDot_len;
    // @desc: alias="GainDot", type="f32", size="[1, 6]", range="[1, 4096]", default="1", digit="[3]", dynamic="1", hide="0", ro="0" 
    float* GainDot;
    int GainDot_len;
    // @desc: alias="IspDGainDot", type="f32", size="[1, 6]", range="[1, 4096]", default="1", digit="[3]", dynamic="1", hide="0", ro="0" 
    float* IspDGainDot;
    int IspDGainDot_len;
    // @desc: alias="PIrisDot", type="s32", size="[1, 6]", range="[1, 4096]", default="1024", digit="[0]", dynamic="1", hide="0", ro="0" 
    int* PIrisDot;
    int PIrisDot_len;
} CalibDb_LinAeRoute_AttrV2_t;

typedef struct CalibDb_AecDynamicSetpointV2_s {
    // @desc: alias="ExpLevel", type="f32", size="[1, 6]", range="[0, 4096]", default="0", digit="[5]", dynamic="1", hide="0", ro="0" 
    float* ExpLevel;
    int ExpLevel_len;
    // @desc: alias="DySetpoint", type="f32", size="[1, 6]", range="[0, 255]", default="40", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* DySetpoint;
    int DySetpoint_len;
} CalibDb_AecDynamicSetpointV2_t;

typedef struct CalibDb_BacklitSetPointV2_s {
    // @desc: alias="ExpLevel", type="f32", size="[1, 6]", range="[0, 4096]", default="0", digit="[5]", dynamic="1", hide="0", ro="0" 
    float* ExpLevel;
    int ExpLevel_len;
    // @desc: alias="NonOEPdfTh", type="f32", size="[1, 6]", range="[0, 1]", default="0.4", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* NonOEPdfTh;
    int NonOEPdfTh_len;
    // @desc: alias="LowLightPdfTh", type="f32", size="[1, 6]", range="[0, 1]", default="0.2", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* LowLightPdfTh;
    int LowLightPdfTh_len;
    // @desc: alias="TargetLLLuma", type="f32", size="[1, 6]", range="[0, 255]", default="20", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* TargetLLLuma;
    int TargetLLLuma_len;
} CalibDb_BacklitSetPointV2_t;

typedef struct CalibDb_AecBacklightV2_s {
    // @desc: type="bool", alias="Enable", default="0", hide="0", ro="0" 
    
   _Bool 
                               Enable;

    // @desc: alias="StrBias", type="f32", size="[1,1]", range="[-500, 500]", default="0", digit="[2]", hide="1", ro="0" 
    float StrBias;//uint: %

    // @desc: type="enum", alias="MeasArea", enum_def="CalibDb_AecMeasAreaModeV2_t", default="AECV2_MEASURE_AREA_AUTO", ro="0" 
    CalibDb_AecMeasAreaModeV2_t MeasArea;

    // @desc: alias="OEROILowTh", type="f32", size="[1,1]", range="[0, 255]", default="150", digit="[2]", hide="0", ro="0" 
    float OEROILowTh;

    // @desc: alias="LumaDistTh", type="f32", size="[1,1]", range="[0, 100]", default="10", digit="[2]", hide="0", ro="0" 
    float LumaDistTh;//uint: %

    // @desc: alias="LvLowTh", type="f32", size="[1,1]", range="[0, 100]", default="7.5", digit="[4]", hide="0", ro="0" 
    float LvLowTh;

    // @desc: alias="LvHighTh", type="f32", size="[1,1]", range="[0, 100]", default="0.3125", digit="[4]", hide="0", ro="0" 
    float LvHighTh;

    // @desc: alias="BacklitSetPoint", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    CalibDb_BacklitSetPointV2_t BacklitSetPoint;
} CalibDb_AecBacklightV2_t;

typedef struct CalibDb_OverExpSetPointV2_s {
    // @desc: alias="OEpdf", type="f32", size="[1, 6]", range="[0, 1]", default="0", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* OEpdf;
    int OEpdf_len;
    // @desc: alias="LowLightWeight", type="f32", size="[1, 6]", range="[0, 20]", default="1", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* LowLightWeight;
    int LowLightWeight_len;
    // @desc: alias="HighLightWeight", type="f32", size="[1, 6]", range="[0, 20]", default="2", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* HighLightWeight;
    int HighLightWeight_len;
} CalibDb_OverExpSetPointV2_t;

typedef struct CalibDb_AecOverExpCtrlV2_s {
    // @desc: type="bool", alias="Enable", default="0", hide="0", ro="0" 
    
   _Bool 
                              Enable;

    // @desc: alias="StrBias", type="f32", size="[1,1]", range="[-500, 500]", default="0", digit="[2]", hide="1", ro="0" 
    float StrBias; //uint: %

    // @desc: alias="MaxWeight", type="f32", size="[1,1]", range="[0, 20]", default="8", digit="[2]", hide="0", ro="0" 
    float MaxWeight;

    // @desc: alias="HighLightTh", type="f32", size="[1,1]", range="[0, 255]", default="150", digit="[2]", hide="0", ro="0" 
    float HighLightTh;

    // @desc: alias="LowLightTh", type="f32", size="[1,1]", range="[0, 255]", default="30", digit="[2]", hide="0", ro="0" 
    float LowLightTh;

    // @desc: alias="OverExpSetPoint", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    CalibDb_OverExpSetPointV2_t OverExpSetPoint;
} CalibDb_AecOverExpCtrlV2_t;

typedef struct CalibDb_LinearAE_AttrV2_s {
    // @desc: type="bool", alias="RawStatsEn", default="1", hide="0", ro="0" 
    
   _Bool 
                                   RawStatsEn;

    // @desc: alias="ToleranceIn", type="f32", size="[1,1]", range="[0, 100]", default="10", digit="[2]", hide="0", ro="0" 
    float ToleranceIn;//uint: %

    // @desc: alias="ToleranceOut", type="f32", size="[1,1]", range="[0, 100]", default="15", digit="[2]", hide="0", ro="0" 
    float ToleranceOut;//uint: %

    // @desc: alias="Evbias", type="f32", size="[1,1]", range="[-500, 500]", default="0", digit="[2]", hide="1", ro="0" 
    float Evbias; //uint: %

    // @desc: type="enum", alias="StrategyMode", enum_def="CalibDb_AeStrategyModeV2_t", default="AECV2_STRATEGY_MODE_LOWLIGHT_PRIOR", ro="0" 
    CalibDb_AeStrategyModeV2_t StrategyMode;

    // @desc: alias="InitExp", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_LinExpInitExpV2_t InitExp;

    // @desc: alias="Route", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    CalibDb_LinAeRoute_AttrV2_t Route;

    // @desc: alias="DySetpoint", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    CalibDb_AecDynamicSetpointV2_t DySetpoint;

    // @desc: alias="BackLightCtrl", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_AecBacklightV2_t BackLightCtrl;

    // @desc: alias="OverExpCtrl", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_AecOverExpCtrlV2_t OverExpCtrl;
} CalibDb_LinearAE_AttrV2_t;

/*****************************************************************************/
/**
 * @brief   ISP2.0 AEC algo HdrAE Config Params
 */
/*****************************************************************************/
typedef struct CalibDb_HdrExpInitExpV2_s {
    // @desc: alias="InitTimeValue", type="f32", size="[1, 3]", range="[0, 1]", default="0.01", digit="[6]", dynamic="0", hide="0", ro="0" 
    float InitTimeValue[(3)];

    // @desc: alias="InitGainValue", type="f32", size="[1, 3]", range="[1, 4096]", default="1.0", digit="[3]", dynamic="0", hide="0", ro="0" 
    float InitGainValue[(3)];

    // @desc: alias="InitIspDGainValue", type="f32", size="[1, 3]", range="[1, 4096]", default="1.0", digit="[3]", dynamic="0", hide="0", ro="0" 
    float InitIspDGainValue[(3)];

    // @desc: alias="InitPIrisGainValue", type="s32", size="[1,1]", range="[1, 4096]", default="1024", digit="[0]", hide="0", ro="0" 
    int InitPIrisGainValue;

    // @desc: alias="InitDCIrisDutyValue", type="s32", size="[1,1]", range="[0, 100]", default="100", digit="[0]", hide="0", ro="0" 
    int InitDCIrisDutyValue;
} CalibDb_HdrExpInitExpV2_t;

typedef struct CalibDb_ExpRatioV2_s {
    // @desc: alias="RatioExpDot", type="f32", size="[1, 6]", range="[0, 1]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* RatioExpDot;
    int RatioExpDot_len;
    // @desc: alias="M2SRatioFix", type="f32", size="[1, 6]", range="[1, 256]", default="8", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* M2SRatioFix;
    int M2SRatioFix_len;
    // @desc: alias="L2MRatioFix", type="f32", size="[1, 6]", range="[1, 256]", default="8", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* L2MRatioFix;
    int L2MRatioFix_len;
    // @desc: alias="M2SRatioMax", type="f32", size="[1, 6]", range="[1, 256]", default="64", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* M2SRatioMax;
    int M2SRatioMax_len;
    // @desc: alias="L2MRatioMax", type="f32", size="[1, 6]", range="[1, 256]", default="64", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* L2MRatioMax;
    int L2MRatioMax_len;
} CalibDb_ExpRatioV2_t;

typedef struct CalibDb_ExpRatioCtrlV2_s {
    // @desc: type="enum", alias="ExpRatioType", enum_def="CalibDb_HdrAeRatioTypeV2_t", default="AECV2_HDR_RATIOTYPE_MODE_AUTO", ro="0" 
    CalibDb_HdrAeRatioTypeV2_t ExpRatioType;

    // @desc: alias="ExpRatio", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    CalibDb_ExpRatioV2_t ExpRatio;
} CalibDb_ExpRatioCtrlV2_t;

typedef struct CalibDb_HdrAeRoute_AttrV2_s {
    // @desc: alias="Frm0TimeDot", type="f32", size="[1, 6]", range="[0, 1]", default="0", digit="[6]", dynamic="1", hide="0", ro="0" 
    float* Frm0TimeDot;
    int Frm0TimeDot_len;
    // @desc: alias="Frm0GainDot", type="f32", size="[1, 6]", range="[1, 4096]", default="1", digit="[3]", dynamic="1", hide="0", ro="0" 
    float* Frm0GainDot;
    int Frm0GainDot_len;
    // @desc: alias="Frm0IspDGainDot", type="f32", size="[1, 6]", range="[1, 4096]", default="1", digit="[3]", dynamic="1", hide="0", ro="0" 
    float* Frm0IspDGainDot;
    int Frm0IspDGainDot_len;
    // @desc: alias="Frm1TimeDot", type="f32", size="[1, 6]", range="[0, 1]", default="0", digit="[6]", dynamic="1", hide="0", ro="0" 
    float* Frm1TimeDot;
    int Frm1TimeDot_len;
    // @desc: alias="Frm1GainDot", type="f32", size="[1, 6]", range="[1, 4096]", default="1", digit="[3]", dynamic="1", hide="0", ro="0" 
    float* Frm1GainDot;
    int Frm1GainDot_len;
    // @desc: alias="Frm1IspDGainDot", type="f32", size="[1, 6]", range="[1, 4096]", default="1", digit="[3]", dynamic="1", hide="0", ro="0" 
    float* Frm1IspDGainDot;
    int Frm1IspDGainDot_len;
    // @desc: alias="Frm2TimeDot", type="f32", size="[1, 6]", range="[0, 1]", default="0", digit="[6]", dynamic="1", hide="0", ro="0" 
    float* Frm2TimeDot;
    int Frm2TimeDot_len;
    // @desc: alias="Frm2GainDot", type="f32", size="[1, 6]", range="[1, 4096]", default="1", digit="[3]", dynamic="1", hide="0", ro="0" 
    float* Frm2GainDot;
    int Frm2GainDot_len;
    // @desc: alias="Frm2IspDGainDot", type="f32", size="[1, 6]", range="[1, 4096]", default="1", digit="[3]", dynamic="1", hide="0", ro="0" 
    float* Frm2IspDGainDot;
    int Frm2IspDGainDot_len;
    // @desc: alias="PIrisDot", type="s32", size="[1, 6]", range="[1, 4096]", default="1024", digit="[0]", dynamic="1", hide="0", ro="0" 
    int* PIrisDot;
    int PIrisDot_len;
} CalibDb_HdrAeRoute_AttrV2_t;

typedef struct CalibDb_LfrmSetPointV2_s
{
    // @desc: alias="LExpLevel", type="f32", size="[1, 6]", range="[0, 4096]", default="0", digit="[5]", dynamic="1", hide="0", ro="0" 
    float* LExpLevel;
    int LExpLevel_len;
    // @desc: alias="NonOEPdfTh", type="f32", size="[1, 6]", range="[0, 1]", default="0.4", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* NonOEPdfTh;
    int NonOEPdfTh_len;
    // @desc: alias="LowLightPdfTh", type="f32", size="[1, 6]", range="[0, 1]", default="0.2", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* LowLightPdfTh;
    int LowLightPdfTh_len;
    // @desc: alias="LSetPoint", type="f32", size="[1, 6]", range="[0, 255]", default="40", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* LSetPoint;
    int LSetPoint_len;
    // @desc: alias="TargetLLLuma", type="f32", size="[1, 6]", range="[0, 255]", default="20", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* TargetLLLuma;
    int TargetLLLuma_len;
} CalibDb_LfrmSetPointV2_t;

typedef struct CalibDb_LfrmCtrlV2_s
{
    // @desc: alias="OEROILowTh", type="f32", size="[1,1]", range="[0, 255]", default="150", digit="[2]", hide="0", ro="0" 
    float OEROILowTh;

    // @desc: alias="LvLowTh", type="f32", size="[1,1]", range="[0, 100]", default="7.5", digit="[4]", hide="0", ro="0" 
    float LvLowTh;

    // @desc: alias="LvHighTh", type="f32", size="[1,1]", range="[0, 100]", default="0.3125", digit="[4]", hide="0", ro="0" 
    float LvHighTh;

    // @desc: alias="LfrmSetPoint", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    CalibDb_LfrmSetPointV2_t LfrmSetPoint;
} CalibDb_LfrmCtrlV2_t;

typedef struct CalibDb_MfrmCtrlV2_s
{
    // @desc: alias="MExpLevel", type="f32", size="[1, 6]", range="[0, 4096]", default="0", digit="[5]", dynamic="1", hide="0", ro="0" 
    float* MExpLevel;
    int MExpLevel_len;
    // @desc: alias="MSetPoint", type="f32", size="[1, 6]", range="[0, 255]", default="40", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* MSetPoint;
    int MSetPoint_len;
} CalibDb_MfrmCtrlV2_t;

typedef struct CalibDb_SfrmSetPointV2_s
{
    // @desc: alias="SExpLevel", type="f32", size="[1, 6]", range="[0, 4096]", default="0", digit="[6]", dynamic="1", hide="0", ro="0" 
    float* SExpLevel;
    int SExpLevel_len;
    // @desc: alias="SSetPoint", type="f32", size="[1, 6]", range="[0, 255]", default="20", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* SSetPoint;
    int SSetPoint_len;
    // @desc: alias="TargetHLLuma", type="f32", size="[1, 6]", range="[0, 255]", default="150", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* TargetHLLuma;
    int TargetHLLuma_len;
} CalibDb_SfrmSetPointV2_t;

typedef struct CalibDb_SfrmCtrlV2_s
{
    // @desc: type="bool", alias="HLROIExpandEn", default="0", hide="0", ro="0" 
    
   _Bool 
                               HLROIExpandEn;

    // @desc: alias="HLLumaTolerance", type="f32", size="[1,1]", range="[0, 100]", default="12", digit="[2]", hide="0", ro="0" 
    float HLLumaTolerance;//unit:%

    // @desc: alias="SfrmSetPoint", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    CalibDb_SfrmSetPointV2_t SfrmSetPoint;
} CalibDb_SfrmCtrlV2_t;

typedef struct CalibDb_LongFrmCtrlV2_s {
    // @desc: type="enum", alias="mode", enum_def="CalibDb_AeHdrLongFrmModeV2_t", default="AECV2_HDR_LONGFRMMODE_NORMAL", ro="0" 
    CalibDb_AeHdrLongFrmModeV2_t mode;

    // @desc: alias="SfrmMinLine", type="u16", size="[1,1]", range="[0, 1024]", default="2", digit="[0]", hide="0", ro="0" 
    uint16_t SfrmMinLine;//uint:line

    // @desc: alias="LfrmModeExpTh", type="f32", size="[1,1]", range="[0, 100]", default="0.62", digit="[4]", hide="0", ro="0" 
    float LfrmModeExpTh;
} CalibDb_LongFrmCtrlV2_t;

typedef struct CalibDb_HdrAE_AttrV2_s {
    // @desc: alias="ToleranceIn", type="f32", size="[1,1]", range="[0, 100]", default="10", digit="[2]", hide="0", ro="0" 
    float ToleranceIn;//unit:%

    // @desc: alias="ToleranceOut", type="f32", size="[1,1]", range="[0, 100]", default="15", digit="[2]", hide="0", ro="0" 
    float ToleranceOut;//unit:%

    // @desc: alias="Evbias", type="f32", size="[1,1]", range="[-500, 500]", default="0", digit="[0]", hide="1", ro="0" 
    float Evbias;

    // @desc: type="enum", alias="StrategyMode", enum_def="CalibDb_AeStrategyModeV2_t", default="AECV2_STRATEGY_MODE_LOWLIGHT_PRIOR", ro="0" 
    CalibDb_AeStrategyModeV2_t StrategyMode;

    // @desc: alias="LumaDistTh", type="f32", size="[1,1]", range="[0, 100]", default="10", digit="[2]", hide="0", ro="0" 
    float LumaDistTh; //used for area-growing,unit:%

    // @desc: alias="InitExp", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_HdrExpInitExpV2_t InitExp;

    // @desc: alias="Route", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    CalibDb_HdrAeRoute_AttrV2_t Route;

    // @desc: alias="ExpRatioCtrl", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_ExpRatioCtrlV2_t ExpRatioCtrl;

    // @desc: alias="LongFrmMode", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_LongFrmCtrlV2_t LongFrmMode;

    // @desc: alias="LframeCtrl", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_LfrmCtrlV2_t LframeCtrl;

    // @desc: alias="MframeCtrl", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    CalibDb_MfrmCtrlV2_t MframeCtrl;

    // @desc: alias="SframeCtrl", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_SfrmCtrlV2_t SframeCtrl;
} CalibDb_HdrAE_AttrV2_t;

/*****************************************************************************/
/**
 * @brief   ISP2.0 AEC algo SyncTest Config Params
 */
/*****************************************************************************/
typedef struct CalibDb_LinAlterExpV2_s {
    // @desc: alias="TimeValue", type="f32", size="[1,1]", range="[0, 1]", default="0.01", digit="[6]", hide="0", ro="0" 
    float TimeValue;

    // @desc: alias="GainValue", type="f32", size="[1,1]", range="[1, 4096]", default="1", digit="[3]", hide="0", ro="0" 
    float GainValue;

    // @desc: alias="IspDGainValue", type="f32", size="[1,1]", range="[1, 4096]", default="1", digit="[3]", hide="0", ro="0" 
    float IspDGainValue;

    // @desc: alias="PIrisGainValue", type="s32", size="[1,1]", range="[1, 4096]", default="1024", digit="[0]", hide="0", ro="0" 
    int PIrisGainValue;

    // @desc: alias="DcgMode", type="s32", size="[1,1]", range="[-1, 1]", default="0", digit="[0]", hide="0", ro="0" 
    int DcgMode;
} CalibDb_LinAlterExpV2_t;

typedef struct CalibDb_HdrAlterExpV2_s {
    // @desc: alias="TimeValue", type="f32", size="[1, 3]", range="[0, 1]", default="0.01", digit="[6]", dynamic="0", hide="0", ro="0" 
    float TimeValue[(3)];

    // @desc: alias="GainValue", type="f32", size="[1, 3]", range="[1, 4096]", default="1.0", digit="[3]", dynamic="0", hide="0", ro="0" 
    float GainValue[(3)];

    // @desc: alias="IspDGainValue", type="f32", size="[1, 3]", range="[1, 4096]", default="1.0", digit="[3]", dynamic="0", hide="0", ro="0" 
    float IspDGainValue[(3)];

    // @desc: alias="PIrisGainValues", type="s32", size="[1,1]", range="[1, 4096]", default="1024", digit="[0]", hide="0", ro="0" 
    int PIrisGainValue;

    // @desc: alias="DcgMode", type="s32", size="[1, 3]", range="[-1, 1]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int DcgMode[(3)];
} CalibDb_HdrAlterExpV2_t;

typedef struct CalibDb_AlterExpV2_s {
    // @desc: alias="LinearAE", type="struct_list", size="dynamic", ui_module="normal_ui_style", ro="0" 
    CalibDb_LinAlterExpV2_t* LinearAE;
    int LinearAE_len;

    // @desc: alias="HdrAE", type="struct_list", size="dynamic", ui_module="normal_ui_style", ro="0" 
    CalibDb_HdrAlterExpV2_t* HdrAE;
    int HdrAE_len;
} CalibDb_AlterExpV2_t;

typedef struct CalibDb_AeSyncTestV2_s {
    // @desc: type="bool", alias="Enable", default="0", hide="0", ro="0" 
    
   _Bool 
                               Enable;

    // @desc: alias="IntervalFrm", type="s32", size="[1,1]", range="[0, 1024]", default="5", digit="[0]", hide="0", ro="0" 
    int IntervalFrm;

    // @desc: alias="AlterExp", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_AlterExpV2_t AlterExp;
} CalibDb_AeSyncTestV2_t;

/*****************************************************************************/
/**
 * @brief   ISP2.0 AEC algo IrisCtrl Config Params
 */
/*****************************************************************************/
typedef struct CalibDb_MIris_AttrV2_s {
    // @desc: alias="PIrisGainValue", type="s32", size="[1,1]", range="[1, 4096]", default="1024", digit="[0]", hide="0", ro="0" 
    int PIrisGainValue;

    // @desc: alias="DCIrisHoldValue", type="s32", size="[1,1]", range="[0, 100]", default="50", digit="[0]", hide="0", ro="0" 
    int DCIrisHoldValue;
} CalibDb_MIris_AttrV2_t;

typedef struct CalibDb_PIris_AttrV2_s {
    // @desc: alias="TotalStep", type="u16", size="[1,1]", range="[0, 1024]", default="81", digit="[0]", hide="0", ro="0" 
    uint16_t TotalStep;

    // @desc: alias="EffcStep", type="u16", size="[1,1]", range="[0, 1024]", default="64", digit="[0]", hide="0", ro="0" 
    uint16_t EffcStep;

    // @desc: type="bool", alias="ZeroIsMax", default="1", hide="0", ro="0" 
    
   _Bool 
                        ZeroIsMax;

    // @desc: alias="StepTable", type="u16", size="[1, 1024]", range="[1, 4096]", default="1024", digit="[0]", dynamic="0", hide="0", ro="0" 
    uint16_t StepTable[(1024)];
} CalibDb_PIris_AttrV2_t;

typedef struct CalibDb_DCIris_AttrV2_s {
    // @desc: alias="Kp", type="f32", size="[1,1]", range="[0, 10]", default="1", digit="[2]", hide="0", ro="0" 
    float Kp;
    // @desc: alias="Ki", type="f32", size="[1,1]", range="[0, 10]", default="0.2", digit="[2]", hide="0", ro="0" 
    float Ki;
    // @desc: alias="Kd", type="f32", size="[1,1]", range="[0, 10]", default="0.5", digit="[2]", hide="0", ro="0" 
    float Kd;
    // @desc: alias="MinPwmDuty", type="s32", size="[1,1]", range="[0, 100]", default="0", digit="[0]", hide="0", ro="0" 
    int MinPwmDuty;
    // @desc: alias="MaxPwmDuty", type="s32", size="[1,1]", range="[0, 100]", default="100", digit="[0]", hide="0", ro="0" 
    int MaxPwmDuty;
    // @desc: alias="OpenPwmDuty", type="s32", size="[1,1]", range="[0, 100]", default="50", digit="[0]", hide="0", ro="0" 
    int OpenPwmDuty;
    // @desc: alias="ClosePwmDuty", type="s32", size="[1,1]", range="[0, 100]", default="60", digit="[0]", hide="0", ro="0" 
    int ClosePwmDuty;
} CalibDb_DCIris_AttrV2_t;

typedef struct CalibDb_AecIrisCtrlV2_s {
    // @desc: type="bool", alias="Enable", default="0", hide="0", ro="0" 
    
   _Bool 
                                Enable;

    // @desc: type="enum", alias="IrisType", enum_def="CalibDb_IrisTypeV2_t", default="IRISV2_DC_TYPE", ro="0" 
    CalibDb_IrisTypeV2_t IrisType;

    // @desc: type="bool", alias="ManualEn", default="0", hide="0", ro="0" 
    
   _Bool 
                                ManualEn;

    // @desc: alias="ManualAttr", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_MIris_AttrV2_t ManualAttr;

    // @desc: alias="InitAttr", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_MIris_AttrV2_t InitAttr;

    // @desc: alias="PIrisAttr", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_PIris_AttrV2_t PIrisAttr;

    // @desc: alias="DCIrisAttr", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_DCIris_AttrV2_t DCIrisAttr;
} CalibDb_AecIrisCtrlV2_t;

/*****************************************************************************/
/**
 * @brief   Global AEC tuning structure of isp2.0
 */
/*****************************************************************************/
typedef struct CalibDb_Aec_ParaV2_s {
    // @desc: alias="CommCtrl", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_AecCommon_AttrV2_t CommCtrl;

    // @desc: alias="LinearAeCtrl", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_LinearAE_AttrV2_t LinearAeCtrl;

    // @desc: alias="HdrAeCtrl", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_HdrAE_AttrV2_t HdrAeCtrl;

    // @desc: alias="IrisCtrl", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_AecIrisCtrlV2_t IrisCtrl;

    // @desc: alias="SyncTest", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_AeSyncTestV2_t SyncTest; //special module for debug
} CalibDb_Aec_ParaV2_t;


/*
 * af_head.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */








typedef enum CalibDbV2_Af_SearchDir_s {
    CalibDbV2_CAM_AFM_POSITIVE_SEARCH = 0,
    CalibDbV2_CAM_AFM_NEGATIVE_SEARCH = 1,
    CalibDbV2_CAM_AFM_ADAPTIVE_SEARCH = 2
} CalibDbV2_Af_SearchDir_t;

typedef enum CalibDbV2_Af_SS_s {
    CalibDbV2_CAM_AFM_FSS_INVALID = 0,
    CalibDbV2_CAM_AFM_FSS_FULLRANGE = 1, /**< scan the full focus range to find the point of best focus */
    CalibDbV2_CAM_AFM_FSS_HILLCLIMBING = 2, /**< use hillclimbing search */
    CalibDbV2_CAM_AFM_FSS_ADAPTIVE_RANGE = 3, /**< similar to full range search, but with multiple subsequent scans
                                                       with decreasing range and step size will be performed. */
    CalibDbV2_CAM_AFM_FSS_MUTIWINDOW = 4, /**< search by muti-window statistics */
    CalibDbV2_CAM_AFM_FSS_MAX
} CalibDbV2_Af_SS_t;

typedef enum CalibDbV2_AF_MODE_s
{
    CalibDbV2_AF_MODE_NOT_SET = -1,
    CalibDbV2_AF_MODE_AUTO,
    CalibDbV2_AF_MODE_MACRO,
    CalibDbV2_AF_MODE_INFINITY,
    CalibDbV2_AF_MODE_FIXED,
    CalibDbV2_AF_MODE_EDOF,
    CalibDbV2_AF_MODE_CONTINUOUS_VIDEO,
    CalibDbV2_AF_MODE_CONTINUOUS_PICTURE,
    CalibDbV2_AF_MODE_ONESHOT_AFTER_ZOOM,
} CalibDbV2_AF_MODE_t;

typedef enum CalibDbV2_PDAF_DATA_DIR_s {
    CalibDbV2_PDAF_DIR_INVAL = 0,
    CalibDbV2_PDAF_DIR_LEFT = 1,
    CalibDbV2_PDAF_DIR_RIGHT = 2,
    CalibDbV2_PDAF_DIR_TOP = 3,
    CalibDbV2_PDAF_DIR_DOWN = 4
} CalibDbV2_PDAF_DATA_DIR_t;

typedef struct CalibDbV2_Af_ContrastZoom_s {
    // @desc: alias="QuickFoundThersZoomIdx", type="u16", size="[1, 32]", range="[0, 65535]", default="0", digit="[0]", dynamic="1", hide="0", ro="0" 
    unsigned short *QuickFoundThersZoomIdx;
    int QuickFoundThersZoomIdx_len;
    // @desc: alias="QuickFoundThers", type="f32", size="[1, 32]", range="[0, 1]", default="0", digit="[3]", dynamic="1", hide="0", ro="0" 
    float *QuickFoundThers;
    int QuickFoundThers_len;
    // @desc: alias="SearchStepZoomIdx", type="u16", size="[1, 32]", range="[0, 65535]", default="0", digit="[0]", dynamic="1", hide="0", ro="0" 
    unsigned short *SearchStepZoomIdx;
    int SearchStepZoomIdx_len;
    // @desc: alias="SearchStep", type="u16", size="[1, 32]", range="[0, 65535]", default="0", digit="[0]", dynamic="1", hide="0", ro="0" 
    unsigned short *SearchStep;
    int SearchStep_len;
    // @desc: alias="StopStepZoomIdx", type="u16", size="[1, 32]", range="[0, 65535]", default="0", digit="[0]", dynamic="1", hide="0", ro="0" 
    unsigned short *StopStepZoomIdx;
    int StopStepZoomIdx_len;
    // @desc: alias="StopStep", type="u16", size="[1, 32]", range="[0, 65535]", default="0", digit="[0]", dynamic="1", hide="0", ro="0" 
    unsigned short *StopStep;
    int StopStep_len;
    // @desc: alias="SkipHighPassZoomIdx", type="u16", size="[1,1]", range="[0, 65535]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short SkipHighPassZoomIdx;
    // @desc: alias="SkipHighPassGain", type="f32", size="[1,1]", range="[0, 1000]", default="0", digit="[3]", hide="0", ro="0" 
    float SkipHighPassGain;
    // @desc: alias="SwitchDirZoomIdx", type="u16", size="[1,1]", range="[0, 65535]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short SwitchDirZoomIdx;

    // @desc: alias="Spotlight HighlightRatio", type="f32", size="[1,1]", range="[0, 1]", default="0.014", digit="[3]", hide="0", ro="0" 
    float SpotlightHighlightRatio;
    // @desc: alias="Spotlight LumaRatio", type="f32", size="[1, 3]", range="[0, 1]", default="[0.3 0.5 0.8]", digit="[3]", dynamic="0", hide="0", ro="0" 
    float SpotlightLumaRatio[3];
    // @desc: alias="Spotlight BlkCnt", type="f32", size="[1, 3]", range="[0, 1]", default="[0.2 0.5 0.25]", digit="[3]", dynamic="0", hide="0", ro="0" 
    float SpotlightBlkCnt[3];
} CalibDbV2_Af_ContrastZoom_t;

typedef struct CalibDbV2_Af_Contrast_s {
    // @desc: type="bool", alias="enable", default="0", hide="0", ro="0" 
    
   _Bool 
        enable;
    // @desc: type="enum", alias="SearchStrategy", enum_def="CalibDbV2_Af_SS_t", default="CalibDbV2_CAM_AFM_FSS_ADAPTIVE_RANGE", ro="0" 
    CalibDbV2_Af_SS_t Afss; /**< enumeration type for search strategy */
    // @desc: type="enum", alias="FullDir", enum_def="CalibDbV2_Af_SearchDir_t", default="CalibDbV2_CAM_AFM_ADAPTIVE_SEARCH", ro="0" 
    CalibDbV2_Af_SearchDir_t FullDir;
    // @desc: alias="FullRangeTbl", type="u16", size="[1, 65]", range="[0, 64]", default="0", digit="[0]", dynamic="1", hide="0", ro="0" 
    unsigned short *FullRangeTbl; /**< full range search table*/
    int FullRangeTbl_len;
    // @desc: type="enum", alias="AdaptiveDir", enum_def="CalibDbV2_Af_SearchDir_t", default="CalibDbV2_CAM_AFM_ADAPTIVE_SEARCH", ro="0" 
    CalibDbV2_Af_SearchDir_t AdaptiveDir;
    // @desc: alias="AdaptRangeTbl", type="u16", size="[1, 65]", range="[0, 64]", default="0", digit="[0]", dynamic="1", hide="0", ro="0" 
    unsigned short *AdaptRangeTbl; /**< adaptive range search table*/
    int AdaptRangeTbl_len;
    // @desc: alias="TrigThers", type="f32", size="[1, 32]", range="[0, 1]", default="0", digit="[3]", dynamic="1", hide="0", ro="0" 
    float *TrigThers; /**< AF trigger threshold */
    int TrigThers_len;
    // @desc: alias="TrigThersFv", type="f32", size="[1, 32]", range="[0, 100000000000]", default="0", digit="[0]", dynamic="1", hide="0", ro="0" 
    float *TrigThersFv; /**< AF trigger threshold */
    int TrigThersFv_len;
    // @desc: alias="LumaTrigThers", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[3]", hide="0", ro="0" 
    float LumaTrigThers;
    // @desc: alias="ExpTrigThers", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[3]", hide="0", ro="0" 
    float ExpTrigThers;

    // @desc: alias="StableThers", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[3]", hide="0", ro="0" 
    float StableThers; /**< AF stable threshold */
    // @desc: alias="StableFrames", type="u16", size="[1,1]", range="[0, 65535]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short StableFrames; /**< AF stable  status must hold frames */
    // @desc: alias="StableTime", type="u16", size="[1,1]", range="[0, 65535]", default="0", digit="[3]", hide="0", ro="0" 
    unsigned short StableTime; /**< AF stable status must hold time */

    // @desc: alias="SceneDiffEnable", type="u8", size="[1,1]", range="[0, 1]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned char SceneDiffEnable;
    // @desc: alias="SceneDiffThers", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[3]", hide="0", ro="0" 
    float SceneDiffThers;
    // @desc: alias="SceneDiffBlkThers", type="u16", size="[1,1]", range="[0, 225]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short SceneDiffBlkThers;
    // @desc: alias="CenterSceneDiffThers", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[3]", hide="0", ro="0" 
    float CenterSceneDiffThers;

    // @desc: alias="ValidMaxMinRatio", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[3]", hide="0", ro="0" 
    float ValidMaxMinRatio;
    // @desc: alias="ValidValueThers", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[3]", hide="0", ro="0" 
    float ValidValueThers;

    // @desc: alias="OutFocusValue", type="f32", size="[1,1]", range="[0, 1000000]", default="0", digit="[3]", hide="0", ro="0" 
    float OutFocusValue; /**< out of focus vlaue*/
    // @desc: alias="OutFocusPos", type="u16", size="[1,1]", range="[0, 65]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short OutFocusPos; /**< out of focus position*/

    // @desc: alias="WeightEnable", type="u8", size="[1,1]", range="[0, 1]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned char WeightEnable;
    // @desc: alias="Weight", type="u16", size="[15, 15]", range="[0, 65535]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned short Weight[225]; /**< weight */

    // @desc: alias="SearchPauseLumaEnable", type="u8", size="[1,1]", range="[0, 1]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned char SearchPauseLumaEnable;
    // @desc: alias="SearchPauseLumaThers", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[3]", hide="0", ro="0" 
    float SearchPauseLumaThers;
    // @desc: alias="StableFrames", type="u16", size="[1,1]", range="[0, 65535]", default="0", digit="[3]", hide="0", ro="0" 
    unsigned short SearchLumaStableFrames;
    // @desc: alias="SearchLumaStableThers", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[3]", hide="0", ro="0" 
    float SearchLumaStableThers;

    // @desc: alias="Stage1QuickFoundThers", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[3]", hide="0", ro="0" 
    float Stage1QuickFoundThers;
    // @desc: alias="Stage2QuickFoundThers", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[3]", hide="0", ro="0" 
    float Stage2QuickFoundThers;

    // @desc: alias="FlatValue", type="f32", size="[1,1]", range="[0, 65535]", default="0", digit="[3]", hide="0", ro="0" 
    float FlatValue;

    // @desc: alias="PointLightLumaTh", type="u16", size="[1,1]", range="[0, 65535]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short PointLightLumaTh; /**< point light luma threshold */
    // @desc: alias="PointLightCntTh", type="u16", size="[1,1]", range="[0, 65535]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short PointLightCntTh; /**< point light count threshold */

    // @desc: alias="ZoomConfig", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Af_ContrastZoom_t ZoomCfg;
} CalibDbV2_Af_Contrast_t;

typedef struct CalibDbV2_Af_Laser_s {
    // @desc: type="bool", alias="enable", default="0", hide="0", ro="0" 
    
   _Bool 
        enable;
    // @desc: alias="vcmDot", type="f32", size="[1, 7]", range="[0, 64]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    float vcmDot[7];
    // @desc: alias="distanceDot", type="f32", size="[1, 7]", range="[0, 65535]", default="0", digit="[4]", dynamic="0", hide="0", ro="0" 
    float distanceDot[7];
} CalibDbV2_Af_Laser_t;

typedef struct CalibDbV2_Af_Pdaf_fineSearch_s {
    // @desc: alias="confidence", type="u32", size="[1,1]", range="[0, 1000]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned int confidence;
    // @desc: alias="range", type="s32", size="[1,1]", range="[0, 64]", default="0", digit="[0]", hide="0", ro="0" 
    int range;
    // @desc: alias="stepPos", type="s32", size="[1,1]", range="[1, 64]", default="1", digit="[0]", hide="0", ro="0" 
    int stepPos;
} CalibDbV2_Af_Pdaf_fineSearch_t;

typedef struct CalibDbV2_Af_PdafIsoPara_s {
    // @desc: alias="iso", type="u32", size="[1,1]", range="[0, 1000000]", default="0", digit="[0]", hide="0", ro="0" 
    int iso;
    // @desc: alias="pdNoiseFactor", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[3]", hide="0", ro="0" 
    float pdNoiseFactor;
    // @desc: alias="pdConfdRatio1", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[3]", hide="0", ro="0" 
    float pdConfdRatio1;
    // @desc: alias="pdConfdRatio2", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[3]", hide="0", ro="0" 
    float pdConfdRatio2;
    // @desc: alias="pdConfdRhresh", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[3]", hide="0", ro="0" 
    float pdConfdThresh;
    // @desc: alias="defocusPdThresh", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[3]", hide="0", ro="0" 
    float defocusPdThresh;
    // @desc: alias="stablePdRatio", type="f32", size="[1,1]", range="[0, 255]", default="0", digit="[3]", hide="0", ro="0" 
    float stablePdRatio;
    // @desc: alias="stablePdOffset", type="f32", size="[1,1]", range="[0, 255]", default="0", digit="[3]", hide="0", ro="0" 
    float stablePdOffset;
    // @desc: alias="stableCntRatio", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[3]", hide="0", ro="0" 
    float stableCntRatio;
    // @desc: alias="noconfCntThresh", type="u16", size="[1,1]", range="[0, 255]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short noconfCntThresh;
    // @desc: alias="fineSearchTbl", type="struct_list", size="[1, 10]", ui_module="normal_ui_style", ro="0" 
    CalibDbV2_Af_Pdaf_fineSearch_t* fineSearchTbl;
    int fineSearchTbl_len;
} CalibDbV2_Af_PdafIsoPara_t;

typedef struct CalibDbV2_Af_Pdaf_s {
    // @desc: type="bool", alias="enable", default="0", hide="0", ro="0" 
    
   _Bool 
        enable;
    // @desc: alias="pdVsCdDebug", type="u8", size="[1,1]", range="[0, 1]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned char pdVsCdDebug;
    // @desc: alias="pdDataBit", type="u16", size="[1,1]", range="[1, 16]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short pdDataBit;
    // @desc: alias="pdBlkLevel", type="u16", size="[1,1]", range="[1, 1023]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short pdBlkLevel;
    // @desc: alias="pdSearchRadius", type="u16", size="[1,1]", range="[0, 32]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short pdSearchRadius;
    // @desc: alias="pdMirrorInCalib", type="u8", size="[1,1]", range="[0, 1]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned char pdMirrorInCalib;
    // @desc: alias="pdWidth", type="u16", size="[1,1]", range="[0, 65535]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short pdWidth;
    // @desc: alias="pdHeight", type="u16", size="[1,1]", range="[0, 65535]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short pdHeight;
    // @desc: alias="pdIsoPara", type="struct_list", size="[1, 16]", ui_module="normal_ui_style", ro="0" 
    CalibDbV2_Af_PdafIsoPara_t* pdIsoPara;
    int pdIsoPara_len;
} CalibDbV2_Af_Pdaf_t;

typedef struct CalibDbV2_Af_VcmCfg_s {
    // @desc: alias="start current", type="s32", size="[1,1]", range="[-1, 2048]", default="-1", digit="[0]", hide="0", ro="0" 
    int start_current;
    // @desc: alias="rated current", type="s32", size="[1,1]", range="[-1, 2048]", default="-1", digit="[0]", hide="0", ro="0" 
    int rated_current;
    // @desc: alias="step mode", type="s32", size="[1,1]", range="[-1, 1000]", default="-1", digit="[0]", hide="0", ro="0" 
    int step_mode;
    // @desc: alias="extra delay", type="s32", size="[1,1]", range="[-10000, 10000]", default="0", digit="[0]", hide="0", ro="0" 
    int extra_delay;
    // @desc: alias="posture diff", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[3]", hide="0", ro="0" 
    float posture_diff;
} CalibDbV2_Af_VcmCfg_t;

typedef struct CalibDbV2_Af_MeasIsoCfg_s {
    // @desc: alias="iso", type="u32", size="[1,1]", range="[0, 1000000]", default="0", digit="[0]", hide="0", ro="0" 
    int iso;
    // @desc: alias="afmThres", type="u16", size="[1,1]", range="[0, 255]", default="4", digit="[0]", hide="0", ro="0" 
    unsigned short afmThres;
    // @desc: alias="Gamma_curve", type="u16", size="[1, 17]", range="[0, 1023]", default="[0 45 108 179 245 344 409 459 500 567 622 676 759 833 896 962 1023]", digit="[0]", dynamic="0", ui_module="curve_table", ro="0" 
    unsigned short gammaY[17];
    // @desc: alias="gaussWeight", type="u8", size="[1, 3]", range="[0, 128]", default="[16 14 14]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char gaussWeight[3];
} CalibDbV2_Af_MeasIsoCfg_t;

typedef struct CalibDbV2_Af_DefCode_s {
    // @desc: alias="code", type="u8", size="[1,1]", range="[0, 64]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned char code;
} CalibDbV2_Af_DefCode_t;

typedef struct CalibDbV2_Af_FocusCode_s {
    // @desc: alias="focus position", type="f32", size="[1,1]", range="[0, 1000000]", default="0", digit="[3]", hide="1", ro="0" 
    float pos;
    // @desc: alias="focus code", type="s16", size="[1, 5000]", range="[-32768, 32767]", default="0", digit="[0]", dynamic="1", hide="1", ro="0" 
    short *code;
    int code_len;
} CalibDbV2_Af_FocusCode_t;

typedef struct CalibDbV2_Af_ZoomFocusTbl_s {
    // @desc: alias="widemod deviate", type="u32", size="[1,1]", range="[0, 1000]", default="0", digit="[0]", hide="0", ro="0" 
    int widemod_deviate;
    // @desc: alias="telemod deviate", type="u32", size="[1,1]", range="[0, 1000]", default="0", digit="[0]", hide="0", ro="0" 
    int telemod_deviate;
    // @desc: alias="zoom move dot", type="u32", size="[1, 32]", range="[0, 1000000]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int *zoom_move_dot;
    int zoom_move_dot_len;
    // @desc: alias="zoom move step", type="u32", size="[1, 32]", range="[0, 1000000]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int *zoom_move_step;
    int zoom_move_step_len;
    // @desc: alias="focal length", type="f32", size="[1, 5000]", range="[0, 10000]", default="0", digit="[3]", dynamic="1", hide="1", ro="0" 
    float *focal_length;
    int focal_length_len;
    // @desc: alias="zoom code", type="s16", size="[1, 5000]", range="[-32768, 32767]", default="0", digit="[0]", dynamic="1", hide="1", ro="0" 
    short *zoomcode;
    int zoomcode_len;
    // @desc: alias="focus code", type="struct_list", size="dynamic", ui_module="normal_ui_style", ro="1" 
    CalibDbV2_Af_FocusCode_t *focuscode;
    int focuscode_len;

    // @desc: alias="zoom search table", type="s32", size="[1, 100]", range="[-32768, 32767]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int *ZoomSearchTbl;
    // @desc: alias="zoom search table number", type="u32", size="[1,1]", range="[0, 100]", default="0", digit="[0]", hide="0", ro="0" 
    int ZoomSearchTbl_len;
    // @desc: alias="zoom search reference curve", type="u32", size="[1,1]", range="[0, 32]", default="0", digit="[0]", hide="0", ro="0" 
    int ZoomSearchRefCurveIdx;
    // @desc: alias="zoom search margin", type="u32", size="[1,1]", range="[0, 100000]", default="0", digit="[0]", hide="0", ro="0" 
    int FocusSearchMargin;
    // @desc: alias="zoom search plus range", type="u32", size="[1, 100]", range="[0, 32767]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int *FocusSearchPlusRange;
    int FocusSearchPlusRange_len;
    // @desc: alias="focus stage1 step", type="u32", size="[1,1]", range="[0, 100]", default="0", digit="[0]", hide="0", ro="0" 
    int FocusStage1Step;
    // @desc: alias="quickFndRate", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[3]", hide="0", ro="0" 
    float QuickFndRate;
    // @desc: alias="quickFndMinFv", type="f32", size="[1,1]", range="[0, 2147483647]", default="0", digit="[0]", hide="0", ro="0" 
    float QuickFndMinFv;
    // @desc: alias="search zoom range", type="u32", size="[1,1]", range="[0, 100000]", default="0", digit="[0]", hide="0", ro="0" 
    int searchZoomRange;
    // @desc: alias="search focus range", type="u32", size="[1,1]", range="[0, 100000]", default="0", digit="[0]", hide="0", ro="0" 
    int searchFocusRange;
    // @desc: alias="search emax", type="f32", size="[1,1]", range="[0, 100000]", default="0", digit="[3]", hide="0", ro="0" 
    float searchEmax;
    // @desc: alias="search eavg", type="f32", size="[1,1]", range="[0, 100000]", default="0", digit="[3]", hide="0", ro="0" 
    float searchEavg;

    // @desc: alias="IsZoomFocusRec", type="u8", size="[1,1]", range="[0, 1]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned char IsZoomFocusRec;
    // @desc: alias="ZoomInfoDir", type="string", size="[1, 1]", range="[0, 64]", default="/data/", dynamic="0", hide="0", ro="0" 
    char *ZoomInfoDir;
} CalibDbV2_Af_ZoomFocusTbl_t;

typedef struct CalibDb_Af_LdgParam_s {
    // @desc: alias="enable", type="u8", size="[1,1]", range="[0, 1]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned char enable;
    // @desc: alias="ldg xl", type="u32", size="[1,1]", range="[0, 255]", default="0", digit="[0]", hide="0", ro="0" 
    int ldg_xl;
    // @desc: alias="ldg yl", type="u32", size="[1,1]", range="[0, 255]", default="0", digit="[0]", hide="0", ro="0" 
    int ldg_yl;
    // @desc: alias="ldg kl", type="u32", size="[1,1]", range="[0, 2147483647]", default="0", digit="[0]", hide="0", ro="0" 
    int ldg_kl;
    // @desc: alias="ldg xh", type="u32", size="[1,1]", range="[0, 255]", default="0", digit="[0]", hide="0", ro="0" 
    int ldg_xh;
    // @desc: alias="ldg yh", type="u32", size="[1,1]", range="[0, 255]", default="0", digit="[0]", hide="0", ro="0" 
    int ldg_yh;
    // @desc: alias="ldg kh", type="u32", size="[1,1]", range="[0, 2147483647]", default="0", digit="[0]", hide="0", ro="0" 
    int ldg_kh;
} CalibDbV2_Af_LdgParam_t;

typedef struct CalibDb_Af_HighLightParam_s {
    // @desc: alias="ther0", type="u32", size="[1,1]", range="[0, 255]", default="245", digit="[0]", hide="0", ro="0" 
    int ther0;
    // @desc: alias="ther1", type="u32", size="[1,1]", range="[0, 255]", default="200", digit="[0]", hide="0", ro="0" 
    int ther1;
} CalibDbV2_Af_HighLightParam_t;

typedef struct CalibDbV2_AF_Tuning_Para_s {
    // @desc: type="enum", alias="mode", enum_def="CalibDbV2_AF_MODE_t", default="CalibDbV2_AF_MODE_CONTINUOUS_PICTURE", ro="0" 
    CalibDbV2_AF_MODE_t af_mode;
    // @desc: alias="win_h_offs", type="u16", size="[1,1]", range="[0, 2000]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short win_h_offs;
    // @desc: alias="win_v_offs", type="u16", size="[1,1]", range="[0, 2000]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short win_v_offs;
    // @desc: alias="win_h_size", type="u16", size="[1,1]", range="[0, 2000]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short win_h_size;
    // @desc: alias="win_v_size", type="u16", size="[1,1]", range="[0, 2000]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short win_v_size;
    // @desc: alias="win_h_offs in video", type="u16", size="[1,1]", range="[0, 2000]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short video_win_h_offs;
    // @desc: alias="win_v_offs in video", type="u16", size="[1,1]", range="[0, 2000]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short video_win_v_offs;
    // @desc: alias="win_h_size in video", type="u16", size="[1,1]", range="[0, 2000]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short video_win_h_size;
    // @desc: alias="win_v_size in video", type="u16", size="[1,1]", range="[0, 2000]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short video_win_v_size;
    // @desc: alias="fixed mode", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Af_DefCode_t fixed_mode;
    // @desc: alias="macro mode", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Af_DefCode_t macro_mode;
    // @desc: alias="infinity mode", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Af_DefCode_t infinity_mode;
    // @desc: alias="ldg param", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Af_LdgParam_t ldg_param;
    // @desc: alias="high light", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Af_HighLightParam_t highlight;
    // @desc: alias="contrast af", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Af_Contrast_t contrast_af;
    // @desc: alias="video contrast af", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Af_Contrast_t video_contrast_af;
    // @desc: alias="laser af", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Af_Laser_t laser_af;
    // @desc: alias="pdaf", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Af_Pdaf_t pdaf;
    // @desc: alias="vcmcfg", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Af_VcmCfg_t vcmcfg;
    // @desc: alias="zoomfocus_tbl", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Af_ZoomFocusTbl_t zoomfocus_tbl;
    // @desc: alias="meas iso config", type="struct_list", size="[1, 13]", ui_module="normal_ui_style", ro="0" 
    CalibDbV2_Af_MeasIsoCfg_t measiso_cfg[13];
} CalibDbV2_AF_Tuning_Para_t;

typedef struct {
    // @desc: alias="TuningPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_AF_Tuning_Para_t TuningPara;
} CalibDbV2_AF_t;

typedef struct CalibDbV2_AfV30_MeasCfg_s {
    // @desc: alias="table index", type="u32", size="[1,1]", range="[0, 1000000]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned int tbl_idx;
    // @desc: alias="afmThres", type="u16", size="[1,1]", range="[0, 255]", default="4", digit="[0]", hide="0", ro="0" 
    unsigned short afmThres;
    // @desc: alias="Gamma Curve", type="u16", size="[1, 17]", range="[0, 1023]", default="[0 45 108 179 245 344 409 459 500 567 622 676 759 833 896 962 1023]", digit="[0]", dynamic="0", ui_module="curve_table", ro="0" 
    unsigned short gammaY[17];
    // @desc: alias="v1fv reliable", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[3]", hide="0", ro="0" 
    float v1fv_reliable;
    // @desc: alias="v2fv reliable", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[3]", hide="0", ro="0" 
    float v2fv_reliable;
    // @desc: alias="v1 fir sel", type="u8", size="[1,1]", range="[0, 1]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned char v1_fir_sel;
    // @desc: alias="v1 band", type="f32", size="[1, 2]", range="[0, 1]", default="0", digit="[3]", dynamic="0", hide="0", ro="0" 
    float v1_band[2];
    // @desc: alias="vertical first iir filter", type="s16", size="[1, 9]", range="[-255, 255]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    short v1_iir_coe[9];
    // @desc: alias="vertical first fir filter", type="s16", size="[1, 3]", range="[-2047, 2047]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    short v1_fir_coe[3];
    // @desc: alias="v2 band", type="f32", size="[1, 2]", range="[0, 1]", default="0", digit="[3]", dynamic="0", hide="0", ro="0" 
    float v2_band[2];
    // @desc: alias="vertical second iir filter", type="s16", size="[1, 3]", range="[-2047, 2047]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    short v2_iir_coe[3];
    // @desc: alias="vertical second fir filter", type="s16", size="[1, 3]", range="[-2047, 2047]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    short v2_fir_coe[3];
    // @desc: alias="h1 band", type="f32", size="[1, 2]", range="[0, 1]", default="0", digit="[3]", dynamic="0", hide="0", ro="0" 
    float h1_band[2];
    // @desc: alias="horizontal first iir1 filter", type="s16", size="[1, 6]", range="[-2047, 2047]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    short h1_iir1_coe[6];
    // @desc: alias="horizontal first iir2 filter", type="s16", size="[1, 6]", range="[-2047, 2047]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    short h1_iir2_coe[6];
    // @desc: alias="h2 band", type="f32", size="[1, 2]", range="[0, 1]", default="0", digit="[3]", dynamic="0", hide="0", ro="0" 
    float h2_band[2];
    // @desc: alias="horizontal second iir1 filter", type="s16", size="[1, 6]", range="[-2047, 2047]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    short h2_iir1_coe[6];
    // @desc: alias="horizontal second iir2 filter", type="s16", size="[1, 6]", range="[-2047, 2047]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    short h2_iir2_coe[6];
    // @desc: alias="ldg enable", type="u8", size="[1,1]", range="[0, 1]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned char ldg_en;
    // @desc: alias="vertical minluma thresh", type="u8", size="[1,1]", range="[0, 255]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned char ve_ldg_lumth_l;
    // @desc: alias="vertical gain for minluma", type="u8", size="[1,1]", range="[0, 255]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned char ve_ldg_gain_l;
    // @desc: alias="vertical slope low", type="u16", size="[1,1]", range="[0, 8191]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short ve_ldg_gslp_l;
    // @desc: alias="vertical maxluma thresh", type="u8", size="[1,1]", range="[0, 255]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned char ve_ldg_lumth_h;
    // @desc: alias="vertical gain for maxluma", type="u8", size="[1,1]", range="[0, 255]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned char ve_ldg_gain_h;
    // @desc: alias="vertical slope high", type="u16", size="[1,1]", range="[0, 8191]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short ve_ldg_gslp_h;
    // @desc: alias="horizontal minluma thresh", type="u8", size="[1,1]", range="[0, 255]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned char ho_ldg_lumth_l;
    // @desc: alias="horizontal gain for minluma", type="u8", size="[1,1]", range="[0, 255]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned char ho_ldg_gain_l;
    // @desc: alias="horizontal slope low", type="u16", size="[1,1]", range="[0, 8191]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short ho_ldg_gslp_l;
    // @desc: alias="horizontal maxluma thresh", type="u8", size="[1,1]", range="[0, 255]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned char ho_ldg_lumth_h;
    // @desc: alias="horizontal gain for maxluma", type="u8", size="[1,1]", range="[0, 255]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned char ho_ldg_gain_h;
    // @desc: alias="horizontal slope high", type="u16", size="[1,1]", range="[0, 8191]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short ho_ldg_gslp_h;
    // @desc: alias="vertical fv thresh", type="u16", size="[1,1]", range="[0, 4095]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short v_fv_thresh;
    // @desc: alias="horizontal fv thresh", type="u16", size="[1,1]", range="[0, 4095]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short h_fv_thresh;
    // @desc: alias="highlight thresh", type="u16", size="[1,1]", range="[0, 4095]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short highlit_thresh;
    // @desc: alias="vertical fv ratio", type="f32", size="[1,1]", range="[0, 1]", default="0.5", digit="[3]", hide="0", ro="0" 
    float v_fv_ratio;
} CalibDbV2_AfV30_MeasCfg_t;

typedef struct CalibDbV2_AfV30_IsoMeasCfg_s {
    // @desc: alias="iso", type="f32", range="[50, 204800]", default="50", digit="[1]", ui_module_param="index2", ro="0" 
    float iso;
    // @desc: alias="meas table index", type="u32", size="[1,1]", range="[0, 100]", default="0", digit="[0]", hide="0", ro="0" 
    int idx;
} CalibDbV2_AfV30_IsoMeasCfg_t;

typedef struct CalibDbV2_AfV30_ZoomMeas_s {
    // @desc: alias="zoom index", type="u32", range="[0, 100000]", default="0", digit="[0]", ui_module_param="index1", ro="0" 
    int zoom_idx;
    // @desc: alias="meas iso config", type="struct_list", size="[1, 13]", ui_module="double_index_list", ro="0" 
    CalibDbV2_AfV30_IsoMeasCfg_t measiso[13];
} CalibDbV2_AfV30_ZoomMeas_t;

typedef struct CalibDbV2_AFV30_Tuning_Para_s {
    // @desc: type="enum", alias="mode", enum_def="CalibDbV2_AF_MODE_t", default="CalibDbV2_AF_MODE_CONTINUOUS_PICTURE", ro="0" 
    CalibDbV2_AF_MODE_t af_mode;
    // @desc: alias="win_h_offs", type="u16", size="[1,1]", range="[0, 2000]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short win_h_offs;
    // @desc: alias="win_v_offs", type="u16", size="[1,1]", range="[0, 2000]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short win_v_offs;
    // @desc: alias="win_h_size", type="u16", size="[1,1]", range="[0, 2000]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short win_h_size;
    // @desc: alias="win_v_size", type="u16", size="[1,1]", range="[0, 2000]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short win_v_size;
    // @desc: alias="win_h_offs in video", type="u16", size="[1,1]", range="[0, 2000]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short video_win_h_offs;
    // @desc: alias="win_v_offs in video", type="u16", size="[1,1]", range="[0, 2000]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short video_win_v_offs;
    // @desc: alias="win_h_size in video", type="u16", size="[1,1]", range="[0, 2000]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short video_win_h_size;
    // @desc: alias="win_v_size in video", type="u16", size="[1,1]", range="[0, 2000]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned short video_win_v_size;
    // @desc: alias="fixed mode", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Af_DefCode_t fixed_mode;
    // @desc: alias="macro mode", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Af_DefCode_t macro_mode;
    // @desc: alias="infinity mode", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Af_DefCode_t infinity_mode;
    // @desc: alias="contrast af", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Af_Contrast_t contrast_af;
    // @desc: alias="video contrast af", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Af_Contrast_t video_contrast_af;
    // @desc: alias="laser af", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Af_Laser_t laser_af;
    // @desc: alias="pdaf", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Af_Pdaf_t pdaf;
    // @desc: alias="vcmcfg", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Af_VcmCfg_t vcmcfg;
    // @desc: alias="zoomfocus_tbl", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Af_ZoomFocusTbl_t zoomfocus_tbl;
    // @desc: alias="zoom meas", type="struct_list", size="dynamic", ui_module="double_index_list", ro="0" 
    CalibDbV2_AfV30_ZoomMeas_t *zoom_meas;
    int zoom_meas_len;
    // @desc: alias="meas config table", type="struct_list", size="dynamic", ui_module="normal_ui_style", ro="0" 
    CalibDbV2_AfV30_MeasCfg_t *meascfg_tbl;
    int meascfg_tbl_len;
} CalibDbV2_AFV30_Tuning_Para_t;

typedef struct {
    // @desc: alias="TuningPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_AFV30_Tuning_Para_t TuningPara;
} CalibDbV2_AFV30_t;


/*
 * agamma_head.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */






typedef enum GammaType_e {
    GAMMATYPE_LOG = 0,
    GAMMATYPE_EQU = 1,
} GammaType_t;

typedef struct CalibDbGammaV2_s {
    // @desc: type="bool", alias="Gamma_en", default="1", hide="0", ro="0" 
    
   _Bool 
        Gamma_en;
    // @desc: type="enum", alias="Gamma_out_segnum", enum_def="GammaType_t", default="GAMMATYPE_LOG", ro="0" 
    GammaType_t Gamma_out_segnum;
    // @desc: alias="Gamma_out_offset", type="u16", size="[1,1]", range="[0, 4095]", default="0", digit="[0]", hide="0", ro="0" 
    uint16_t Gamma_out_offset;
    // @desc: alias="Gamma_curve", type="u16", size="[1, 45]", range="[0, 4095]", default="[0 6 11 17 22 28 33 39 44 55 66 77 88 109 130 150 170 210 248 286 323 393 460 525 586 702 809 909 1002 1172 1325 1462 1588 1811 2004 2174 2327 2590 2813 3006 3177 3467 3708 3915 4095.0000]", digit="[4]", dynamic="0", ui_module="curve_table", ro="0" 
    uint16_t Gamma_curve[45];
} CalibDbGammaV2_t;

typedef struct CalibDbV2_gamma_s {
    // @desc: alias="GammaTuningPara", type="struct", ui_module="curve_ui_type_A", hide="0", ro="0" 
    CalibDbGammaV2_t GammaTuningPara;
} CalibDbV2_gamma_t;

typedef struct CalibDbGammaV30_s {
    // @desc: type="bool", alias="Gamma_en", default="1", hide="0", ro="0" 
    
   _Bool 
        Gamma_en;
    // @desc: alias="Gamma_out_offset", type="u16", size="[1,1]", range="[0, 4095]", default="0", digit="[0]", hide="0", ro="0" 
    uint16_t Gamma_out_offset;
    // @desc: alias="Gamma_curve", type="u16", size="[1, 49]", range="[0, 4095]", default="[0 93 128 154 175 194 211 226 240 266 289 310 329 365 396 425 451 499 543 582 618 684 744 798 848 938 1019 1093 1161 1285 1396 1498 1592 1761 1914 2052 2181 2414 2622 2813 2989 3153 3308 3454 4593 3727 3854 3977 4095]", digit="[0]", dynamic="0", ui_module="curve_table", ro="0" 
    uint16_t Gamma_curve[49];;
} CalibDbGammaV30_t;

typedef struct CalibDbV2_gamma_V30_s {
    // @desc: alias="GammaTuningPara", type="struct", ui_module="curve_ui_type_A", hide="0", ro="0" 
    CalibDbGammaV30_t GammaTuningPara;
} CalibDbV2_gamma_V30_t;



/*
 * agic_head.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */



typedef struct Gic_setting_v20_s {
    // @desc: alias="ISO", type="f32", size="[1, 100]", range="[0, 10000000]", default="50", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* ISO;
    int ISO_len;
    // @desc: alias="min_busy_thre", type="f32", size="[1, 100]", range="[0, 1023]", default="160", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* min_busy_thre;
    int min_busy_thre_len;
    // @desc: alias="min_grad_thr1", type="f32", size="[1, 100]", range="[0, 1023]", default="32", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* min_grad_thr1;
    int min_grad_thr1_len;
    // @desc: alias="min_grad_thr2", type="f32", size="[1, 100]", range="[0, 1023]", default="32", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* min_grad_thr2;
    int min_grad_thr2_len;
    // @desc: alias="k_grad1", type="f32", size="[1, 100]", range="[0, 15]", default="5", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* k_grad1;
    int k_grad1_len;
    // @desc: alias="k_grad1", type="f32", size="[1, 100]", range="[0, 15]", default="1", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* k_grad2;
    int k_grad2_len;
    // @desc: alias="gb_thre", type="f32", size="[1, 100]", range="[0, 15]", default="7", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* gb_thre;
    int gb_thre_len;
    // @desc: alias="maxCorV", type="f32", size="[1, 100]", range="[0, 1023]", default="40", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* maxCorV;
    int maxCorV_len;
    // @desc: alias="maxCorVboth", type="f32", size="[1, 100]", range="[0, 1023]", default="8", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* maxCorVboth;
    int maxCorVboth_len;
    // @desc: alias="dark_thre", type="f32", size="[1, 100]", range="[0, 2047]", default="120", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* dark_thre;
    int dark_thre_len;
    // @desc: alias="dark_threHi", type="f32", size="[1, 100]", range="[0, 2047]", default="240", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* dark_threHi;
    int dark_threHi_len;
    // @desc: alias="k_grad1_dark", type="f32", size="[1, 100]", range="[0, 15]", default="6", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* k_grad1_dark;
    int k_grad1_dark_len;
    // @desc: alias="k_grad2_dark", type="f32", size="[1, 100]", range="[0, 15]", default="1", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* k_grad2_dark;
    int k_grad2_dark_len;
    // @desc: alias="min_grad_thr_dark1", type="f32", size="[1, 100]", range="[0, 1023]", default="64", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* min_grad_thr_dark1;
    int min_grad_thr_dark1_len;
    // @desc: alias="min_grad_thr_dark2", type="f32", size="[1, 100]", range="[0, 1023]", default="32", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* min_grad_thr_dark2;
    int min_grad_thr_dark2_len;
    // @desc: alias="noiseCurve_0", type="f32", size="[1, 100]", range="[0, 1023]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* noiseCurve_0;
    int noiseCurve_0_len;
    // @desc: alias="noiseCurve_1", type="f32", size="[1, 100]", range="[0, 1023]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* noiseCurve_1;
    int noiseCurve_1_len;
    // @desc: alias="GValueLimitLo", type="f32", size="[1, 100]", range="[0, 4095]", default="1280", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* GValueLimitLo;
    int GValueLimitLo_len;
    // @desc: alias="GValueLimitHi", type="f32", size="[1, 100]", range="[0, 4095]", default="1760", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* GValueLimitHi;
    int GValueLimitHi_len;
    // @desc: alias="textureStrength", type="f32", size="[1, 100]", range="[0, 2]", default="1", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* textureStrength;
    int textureStrength_len;
    // @desc: alias="ScaleLo", type="f32", size="[1, 100]", range="[0, 1023]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* ScaleLo;
    int ScaleLo_len;
    // @desc: alias="ScaleHi", type="f32", size="[1, 100]", range="[0, 1023]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* ScaleHi;
    int ScaleHi_len;
    // @desc: alias="globalStrength", type="f32", size="[1, 100]", range="[0, 2]", default="1", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* globalStrength;
    int globalStrength_len;
    // @desc: alias="noise_coea", type="f32", size="[1, 100]", range="[0, 1023]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* noise_coea;
    int noise_coea_len;
    // @desc: alias="noise_coeb", type="f32", size="[1, 100]", range="[0, 1023]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* noise_coeb;
    int noise_coeb_len;
    // @desc: alias="diff_clip", type="f32", size="[1, 100]", range="[0, 1023]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* diff_clip;
    int diff_clip_len;
} Gic_setting_v20_t;

typedef struct Gic_setting_v21_s {
    // @desc: alias="ISO", type="f32", size="[1, 100]", range="[0, 10000000]", default="50", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* ISO;
    int ISO_len;
    // @desc: alias="min_busy_thre", type="f32", size="[1, 100]", range="[0, 1023]", default="160", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* min_busy_thre;
    int min_busy_thre_len;
    // @desc: alias="min_grad_thr1", type="f32", size="[1, 100]", range="[0, 1023]", default="32", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* min_grad_thr1;
    int min_grad_thr1_len;
    // @desc: alias="min_grad_thr2", type="f32", size="[1, 100]", range="[0, 1023]", default="32", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* min_grad_thr2;
    int min_grad_thr2_len;
    // @desc: alias="k_grad1", type="f32", size="[1, 100]", range="[0, 15]", default="5", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* k_grad1;
    int k_grad1_len;
    // @desc: alias="k_grad1", type="f32", size="[1, 100]", range="[0, 15]", default="1", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* k_grad2;
    int k_grad2_len;
    // @desc: alias="gb_thre", type="f32", size="[1, 100]", range="[0, 15]", default="7", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* gb_thre;
    int gb_thre_len;
    // @desc: alias="maxCorV", type="f32", size="[1, 100]", range="[0, 1023]", default="40", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* maxCorV;
    int maxCorV_len;
    // @desc: alias="maxCorVboth", type="f32", size="[1, 100]", range="[0, 1023]", default="8", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* maxCorVboth;
    int maxCorVboth_len;
    // @desc: alias="dark_thre", type="f32", size="[1, 100]", range="[0, 2047]", default="120", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* dark_thre;
    int dark_thre_len;
    // @desc: alias="dark_threHi", type="f32", size="[1, 100]", range="[0, 2047]", default="240", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* dark_threHi;
    int dark_threHi_len;
    // @desc: alias="k_grad1_dark", type="f32", size="[1, 100]", range="[0, 15]", default="6", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* k_grad1_dark;
    int k_grad1_dark_len;
    // @desc: alias="k_grad2_dark", type="f32", size="[1, 100]", range="[0, 15]", default="1", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* k_grad2_dark;
    int k_grad2_dark_len;
    // @desc: alias="min_grad_thr_dark1", type="f32", size="[1, 100]", range="[0, 1023]", default="64", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* min_grad_thr_dark1;
    int min_grad_thr_dark1_len;
    // @desc: alias="min_grad_thr_dark2", type="f32", size="[1, 100]", range="[0, 1023]", default="32", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* min_grad_thr_dark2;
    int min_grad_thr_dark2_len;
    // @desc: alias="noiseCurve_0", type="f32", size="[1, 100]", range="[0, 1023]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* noiseCurve_0;
    int noiseCurve_0_len;
    // @desc: alias="noiseCurve_1", type="f32", size="[1, 100]", range="[0, 1023]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* noiseCurve_1;
    int noiseCurve_1_len;
    // @desc: alias="NoiseScale", type="f32", size="[1, 100]", range="[0, 1023]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* NoiseScale;
    int NoiseScale_len;
    // @desc: alias="NoiseBase", type="f32", size="[1, 100]", range="[0, 1023]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* NoiseBase;
    int NoiseBase_len;
    // @desc: alias="globalStrength", type="f32", size="[1, 100]", range="[0, 2]", default="1", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* globalStrength;
    int globalStrength_len;
    // @desc: alias="diff_clip", type="f32", size="[1, 100]", range="[0, 1023]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* diff_clip;
    int diff_clip_len;
} Gic_setting_v21_t;

typedef struct CalibDbGicV20_s {
    // @desc: type="bool", alias="enable", default="0", hide="0", ro="0" 
    
   _Bool 
                       enable;
    // @desc: type="bool", alias="edge_en", default="0", hide="0", ro="0" 
    
   _Bool 
                       edge_en;
    // @desc: type="bool", alias="noise_cut_en", default="0", hide="0", ro="0" 
    
   _Bool 
                       noise_cut_en;
    // @desc: alias="gr_ration", type="u8", size="[1,1]", range="[0, 3]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned char gr_ration;
    // @desc: alias="GicData", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    Gic_setting_v20_t GicData;
} CalibDbGicV20_t;

typedef struct CalibDbV2_Gic_V20_s {
    // @desc: alias="GicTuningPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbGicV20_t GicTuningPara;
} CalibDbV2_Gic_V20_t;

typedef struct CalibDbGicV21_s {
    // @desc: type="bool", alias="enable", default="0", hide="0", ro="0" 
    
   _Bool 
                       enable;
    // @desc: alias="gr_ration", type="u8", size="[1,1]", range="[0, 3]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned char gr_ration;
    // @desc: alias="GicData", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    Gic_setting_v21_t GicData;
} CalibDbGicV21_t;

typedef struct CalibDbV2_Gic_V21_s {
    // @desc: alias="GicTuningPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbGicV21_t GicTuningPara;
} CalibDbV2_Gic_V21_t;



/*
 * aie_head.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */



// #define M4_BOOL_DESC(ALIAS, DEFAULT, HIDE)

// #define M4_ARRAY_DESC(ALIAS, TYPE, SIZE, RANGE, DEFAULT,DIGIT,DYNAMIC, HIDE)

// #define M4_NUMBER_DESC(ALIAS, TYPE, RANGE, DEFAULT,DIGIT, HIDE)

typedef struct __ie_param {
    // @desc: type="bool", alias="enable", default="1", hide="0", ro="0" 
    
   _Bool 
        enable;
    // @desc: alias="mode", type="u8", size="[1,1]", range="[0, 6]", default="0", digit="[0]", hide="0", ro="0" 
    unsigned char mode;
}IE_Param_t;

typedef struct __ie {
    // @desc: alias="IETuningPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    IE_Param_t param;
} CalibDbV2_IE_t;


/*
 * alsc_head.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
/*
 *rk_aiq_types_alsc_hw.h
 *
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


//MEMO: rkisp2-config.h/rkisp3-config.h -> ISP2X_LSC_DATA_TBL_SIZE is 290


/**
 * @brief LSC config table to be set to hardware.
 * Remember, 4 channel data array must be in the head of struct,
 * and with the order of (r, gr, gb, b)!
*/
typedef struct rk_aiq_lsc_cfg_s {
    unsigned short r_data_tbl[289];
    unsigned short gr_data_tbl[289];
    unsigned short gb_data_tbl[289];
    unsigned short b_data_tbl[289];

    unsigned short x_grad_tbl[16];
    unsigned short y_grad_tbl[16];
    unsigned short x_size_tbl[16];
    unsigned short y_size_tbl[16];
    
   _Bool 
        lsc_en;
} rk_aiq_lsc_cfg_t;




typedef struct lsc_name_s {
    // @desc: alias="name", type="string", size="[1, 1]", range="[0, 32]", default="default", dynamic="0", hide="0", ro="0" 
    char name[( 32U )];
} lsc_name_t;

typedef struct resolution_s {
    char name[( 32U )];
    uint32_t width;
    uint32_t height;
} resolution_t;

/**
 * @brief illumination case in different <using case>, <resolution>, <color temperature>
*/
typedef struct CalibDbV2_AlscCof_ill_s {
    // @desc: alias="usedForCase", type="u32", size="[1,1]", range="[0, 100]", default="0", digit="[0]", hide="0", ro="0" 
    uint32_t usedForCase;
    // @desc: alias="name", type="string", size="[1, 1]", range="[0, 32]", default="default", dynamic="0", hide="0", ro="0" 
    char name[( 32U )];
    // @desc: alias="wbGain", type="f32", size="[1, 2]", range="[0, 10000]", default="0", digit="[4]", dynamic="0", hide="0", ro="0" 
    float wbGain[2];
    // @desc: alias="tableUsed", type="struct_list", size="dynamic", ui_module="normal_ui_style", ro="0" 
    lsc_name_t* tableUsed;
    int tableUsed_len;
    // @desc: alias="gains", type="f32", size="[1, 100]", range="[0, 10000]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* gains;
    int gains_len;
    // @desc: alias="vig", type="f32", size="[1, 100]", range="[0, 100]", default="0", digit="[2]", dynamic="1", hide="0", ro="0" 
    float* vig;
    int vig_len;
} CalibDbV2_AlscCof_ill_t;

typedef struct CalibDbV2_Lsc_Resolution_s {
    // @desc: alias="name", type="string", size="[1, 1]", range="[0, 32]", default="default", dynamic="0", hide="0", ro="0" 
    char name[( 32U )];





    // @desc: alias="lsc_sect_size_x", type="u16", size="[1, 16]", range="[0, 10000]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 



    uint16_t lsc_sect_size_x[16];





    // @desc: alias="lsc_sect_size_y", type="u16", size="[1, 16]", range="[0, 10000]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 



    uint16_t lsc_sect_size_y[16];
} CalibDbV2_Lsc_Resolution_t;

typedef struct CalibDbV2_Lsc_Common_s {
    // @desc: type="bool", alias="enable", default="1", hide="0", ro="0" 
    
   _Bool 
                                   enable;
    // @desc: alias="resolutionAll", type="struct_list", size="dynamic", ui_module="normal_ui_style", ro="0" 
    CalibDbV2_Lsc_Resolution_t* resolutionAll;
    int resolutionAll_len;
} CalibDbV2_Lsc_Common_t;

typedef struct CalibDbV2_AlscCof_s {
    // @desc: type="bool", alias="damp_enable", default="1", hide="0", ro="0" 
    
   _Bool 
                                   damp_enable;
    // @desc: alias="illAll", type="struct_list", size="dynamic", ui_module="normal_ui_style", ro="0" 
    CalibDbV2_AlscCof_ill_t* illAll;
    int illAll_len;
} CalibDbV2_AlscCof_t;

//represent a cell of tableAll in xml/json
typedef struct CalibDbV2_LscTableProfile_s {
    // @desc: alias="name", type="string", size="[1, 1]", range="[0, 32]", default="default", dynamic="0", hide="0", ro="0" 
    char name[( 32U )];
    // @desc: alias="resolution", type="string", size="[1, 1]", range="[0, 32]", default="default", dynamic="0", hide="0", ro="0" 
    char resolution[( 32U )];
    // @desc: alias="illumination", type="string", size="[1, 1]", range="[0, 32]", default="default", dynamic="0", hide="0", ro="0" 
    char illumination[( 32U )];
    // @desc: alias="vignetting", type="f32", size="[1,1]", range="[0, 100]", default="100", digit="[0]", hide="0", ro="0" 
    float vignetting;

    // @desc: alias="lsc_samples_red", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    Cam17x17UShortMatrix_t lsc_samples_red;
    // @desc: alias="lsc_samples_greenR", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    Cam17x17UShortMatrix_t lsc_samples_greenR;
    // @desc: alias="lsc_samples_greenB", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    Cam17x17UShortMatrix_t lsc_samples_greenB;
    // @desc: alias="lsc_samples_blue", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    Cam17x17UShortMatrix_t lsc_samples_blue;
} CalibDbV2_LscTableProfile_t;

typedef struct CalibDbV2_LscTable {
    // @desc: alias="tableAll", type="struct_list", size="dynamic", ui_module="normal_ui_style", ro="0" 
    CalibDbV2_LscTableProfile_t* tableAll;
    int tableAll_len;
} CalibDbV2_LscTable_t;

typedef struct CalibDb_LscV2_s {
    // @desc: alias="common", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Lsc_Common_t common;
    // @desc: alias="alscCoef", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_AlscCof_t alscCoef;
    // @desc: alias="table_list", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_LscTable_t tbl;
} CalibDbV2_LSC_t;


/*
 * amerge_head.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */



typedef struct MergeOECurveV20_s {
    // @desc: alias="EnvLv", type="f32", size="[1, 100]", range="[0, 1]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* EnvLv;
    int EnvLv_len;
    // @desc: alias="Smooth", type="f32", size="[1, 100]", range="[0, 1]", default="0.4", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* Smooth;
    int Smooth_len;
    // @desc: alias="Offset", type="f32", size="[1, 100]", range="[108, 300]", default="210", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* Offset;
    int Offset_len;
} MergeOECurveV20_t;

typedef struct MergeMDCurveV20_s {
    // @desc: alias="MoveCoef", type="f32", size="[1, 100]", range="[0, 1]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* MoveCoef;
    int MoveCoef_len;
    // @desc: alias="LM_smooth", type="f32", size="[1, 100]", range="[0, 1]", default="0.4", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* LM_smooth;
    int LM_smooth_len;
    // @desc: alias="LM_offset", type="f32", size="[1, 100]", range="[0, 1]", default="0.38", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* LM_offset;
    int LM_offset_len;
    // @desc: alias="MS_smooth", type="f32", size="[1, 100]", range="[0, 1]", default="0.4", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* MS_smooth;
    int MS_smooth_len;
    // @desc: alias="MS_offset", type="f32", size="[1, 100]", range="[0, 1]", default="0.38", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* MS_offset;
    int MS_offset_len;
} MergeMDCurveV20_t;

typedef struct MergeV20_s {
    // @desc: alias="OECurve", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    MergeOECurveV20_t OECurve;
    // @desc: alias="MDCurve", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    MergeMDCurveV20_t MDCurve;
    // @desc: alias="ByPassThr", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[4]", hide="0", ro="0" 
    float ByPassThr;
    // @desc: alias="OECurve_damp", type="f32", size="[1,1]", range="[0, 1]", default="0.9", digit="[4]", hide="0", ro="0" 
    float OECurve_damp;
    // @desc: alias="MDCurveLM_damp", type="f32", size="[1,1]", range="[0, 1]", default="0.9", digit="[4]", hide="0", ro="0" 
    float MDCurveLM_damp;
    // @desc: alias="MDCurveMS_damp", type="f32", size="[1,1]", range="[0, 1]", default="0.9", digit="[4]", hide="0", ro="0" 
    float MDCurveMS_damp;
} MergeV20_t;

typedef struct CalibDbV2_merge_s {
    // @desc: alias="MergeTuningPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    MergeV20_t MergeTuningPara;
} CalibDbV2_merge_t;

typedef enum MergeBaseFrame_e {
    BASEFRAME_LONG = 0,
    BASEFRAME_SHORT = 1,
} MergeBaseFrame_t;

typedef struct LongFrameModeData_s {
    // @desc: alias="OECurve", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    MergeOECurveV20_t OECurve;
    // @desc: alias="MDCurve", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    MergeMDCurveV20_t MDCurve;
    // @desc: alias="OECurve_damp", type="f32", size="[1,1]", range="[0, 1]", default="0.9", digit="[4]", hide="0", ro="0" 
    float OECurve_damp;
    // @desc: alias="MDCurveLM_damp", type="f32", size="[1,1]", range="[0, 1]", default="0.9", digit="[4]", hide="0", ro="0" 
    float MDCurveLM_damp;
    // @desc: alias="MDCurveMS_damp", type="f32", size="[1,1]", range="[0, 1]", default="0.9", digit="[4]", hide="0", ro="0" 
    float MDCurveMS_damp;
} LongFrameModeData_t;

typedef struct MergeMDCurveV21Short_s {
    // @desc: alias="MoveCoef", type="f32", size="[1, 100]", range="[0, 1]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* MoveCoef;
    int MoveCoef_len;
    // @desc: alias="Coef", type="f32", size="[1, 100]", range="[0, 1]", default="0.05", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* Coef;
    int Coef_len;
    // @desc: alias="ms_thd0", type="f32", size="[1, 100]", range="[0, 1]", default="0", digit="[1]", dynamic="1", hide="0", ro="0" 
    float* ms_thd0;
    int ms_thd0_len;
    // @desc: alias="lm_thd0", type="f32", size="[1, 100]", range="[0, 1]", default="0", digit="[1]", dynamic="1", hide="0", ro="0" 
    float* lm_thd0;
    int lm_thd0_len;
} MergeMDCurveV21Short_t;

typedef struct ShortFrameModeData_s {
    // @desc: alias="OECurve", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    MergeOECurveV20_t OECurve;
    // @desc: alias="MDCurve", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    MergeMDCurveV21Short_t MDCurve;
    // @desc: alias="OECurve_damp", type="f32", size="[1,1]", range="[0, 1]", default="0.9", digit="[4]", hide="0", ro="0" 
    float OECurve_damp;
    // @desc: alias="MDCurve_damp", type="f32", size="[1,1]", range="[0, 1]", default="0.9", digit="[4]", hide="0", ro="0" 
    float MDCurve_damp;
} ShortFrameModeData_t;

typedef struct MergeV21_s {
    // @desc: type="enum", alias="BaseFrm", enum_def="MergeBaseFrame_t", default="BASEFRAME_LONG", ro="0" 
    MergeBaseFrame_t BaseFrm;
    // @desc: alias="ByPassThr", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[4]", hide="0", ro="0" 
    float ByPassThr;
    // @desc: alias="LongFrmModeData", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    LongFrameModeData_t LongFrmModeData;
    // @desc: alias="ShortFrmModeData", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    ShortFrameModeData_t ShortFrmModeData;
} MergeV21_t;

typedef struct CalibDbV2_merge_V2_s {
    // @desc: alias="MergeTuningPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    MergeV21_t MergeTuningPara;
} CalibDbV2_merge_V2_t;



/*
 * atmo_head.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */



typedef enum GlobalLumaMode_e {
    GLOBALLUMAMODE_ENVLV = 0,
    GLOBALLUMAMODE_ISO = 1,
} GlobalLumaMode_t;

typedef struct GlobalLumaData_s
{
    // @desc: alias="EnvLv", type="f32", size="[1, 100]", range="[0, 1]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* EnvLv;
    int EnvLv_len;
    // @desc: alias="ISO", type="f32", size="[1, 100]", range="[0, 10000000]", default="50", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* ISO;
    int ISO_len;
    // @desc: alias="Strength", type="f32", size="[1, 100]", range="[0, 1]", default="0.25", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* Strength;
    int Strength_len;
} GlobalLumaData_t;

typedef struct CalibDbGlobalLuma_s
{
    // @desc: type="enum", alias="Mode", enum_def="GlobalLumaMode_t", default="GLOBALLUMAMODE_ENVLV", ro="0" 
    GlobalLumaMode_t Mode;
    // @desc: alias="GlobalLumaData", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    GlobalLumaData_t GlobalLumaData;
    // @desc: alias="Tolerance", type="f32", size="[1,1]", range="[0, 0.2]", default="0", digit="[4]", hide="0", ro="0" 
    float Tolerance;
} CalibDbGlobalLuma_t;

typedef enum DetailsHighLightMode_e {
    DETAILSHIGHLIGHTMODE_OEPDF = 0,
    DETAILSHIGHLIGHTMODE_ENVLV = 1,
} DetailsHighLightMode_t;

typedef struct HighLightData_s
{
    // @desc: alias="OEPdf", type="f32", size="[1, 100]", range="[0, 1]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* OEPdf;
    int OEPdf_len;
    // @desc: alias="EnvLv", type="f32", size="[1, 100]", range="[0, 1]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* EnvLv;
    int EnvLv_len;
    // @desc: alias="Strength", type="f32", size="[1, 100]", range="[0, 1]", default="0.5", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* Strength;
    int Strength_len;
} HighLightData_t;

typedef struct CalibDbDetailsHighLight_s
{
    // @desc: type="enum", alias="Mode", enum_def="DetailsHighLightMode_t", default="DETAILSHIGHLIGHTMODE_ENVLV", ro="0" 
    DetailsHighLightMode_t Mode;
    // @desc: alias="HighLightData", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    HighLightData_t HighLightData;
    // @desc: alias="Tolerance", type="f32", size="[1,1]", range="[0, 0.2]", default="0", digit="[4]", hide="0", ro="0" 
    float Tolerance;
} CalibDbDetailsHighLight_t;

typedef enum DetailsLowLightMode_e {
    DETAILSLOWLIGHTMODE_FOCUSLUMA = 0,
    DETAILSLOWLIGHTMODE_DARKPDF = 1,
    DETAILSLOWLIGHTMODE_ISO = 2,
} DetailsLowLightMode_t;

typedef struct LowLightData_s
{
    // @desc: alias="FocusLuma", type="f32", size="[1, 100]", range="[0, 100]", default="1", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* FocusLuma;
    int FocusLuma_len;
    // @desc: alias="DarkPdf", type="f32", size="[1, 100]", range="[0, 1]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* DarkPdf;
    int DarkPdf_len;
    // @desc: alias="ISO", type="f32", size="[1, 100]", range="[0, 10000000]", default="50", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* ISO;
    int ISO_len;
    // @desc: alias="Strength", type="f32", size="[1, 100]", range="[1, 4]", default="1", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* Strength;
    int Strength_len;
} LowLightData_t;

typedef struct CalibDbDetailsLowLight_s
{
    // @desc: type="enum", alias="Mode", enum_def="DetailsLowLightMode_t", default="DETAILSLOWLIGHTMODE_ISO", ro="0" 
    DetailsLowLightMode_t Mode;
    // @desc: alias="LowLightData", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    LowLightData_t LowLightData;
    // @desc: alias="Tolerance", type="f32", size="[1,1]", range="[0, 0.2]", default="0", digit="[4]", hide="0", ro="0" 
    float Tolerance;
} CalibDbDetailsLowLight_t;

typedef enum TmoTypeMode_e {
    TMOTYPEMODE_DYNAMICRANGE = 0,
    TMOTYPEMODE_ENVLV = 1,
} TmoTypeMode_t;

typedef struct TmoData_s
{
    // @desc: alias="DynamicRange", type="f32", size="[1, 100]", range="[1, 84]", default="1", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* DynamicRange;
    int DynamicRange_len;
    // @desc: alias="EnvLv", type="f32", size="[1, 100]", range="[0, 1]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* EnvLv;
    int EnvLv_len;
    // @desc: alias="Strength", type="f32", size="[1, 100]", range="[0, 1]", default="0.5", digit="[4]", dynamic="1", hide="0", ro="0" 
    float* Strength;
    int Strength_len;
} TmoData_t;

typedef struct CalibDbLocalTMO_s
{
    // @desc: type="enum", alias="Mode", enum_def="TmoTypeMode_t", default="TMOTYPEMODE_DYNAMICRANGE", ro="0" 
    TmoTypeMode_t Mode;
    // @desc: alias="LocalTmoData", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    TmoData_t LocalTmoData;
    // @desc: alias="Tolerance", type="f32", size="[1,1]", range="[0, 0.2]", default="0", digit="[4]", hide="0", ro="0" 
    float Tolerance;
} CalibDbLocalTMO_t;

typedef struct CalibDbGlobaTMO_s
{
    // @desc: type="bool", alias="Enable", default="1", hide="0", ro="0" 
    
   _Bool 
                Enable;
    // @desc: alias="IIR", type="f32", size="[1,1]", range="[1, 1000]", default="64", digit="[0]", hide="0", ro="0" 
    float IIR;
    // @desc: type="enum", alias="Mode", enum_def="TmoTypeMode_t", default="TMOTYPEMODE_DYNAMICRANGE", ro="0" 
    TmoTypeMode_t Mode;
    // @desc: alias="GlobalTmoData", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    TmoData_t GlobalTmoData;
    // @desc: alias="Tolerance", type="f32", size="[1,1]", range="[0, 0.2]", default="0", digit="[4]", hide="0", ro="0" 
    float Tolerance;
} CalibDbGlobaTMO_t;

typedef struct CalibDbTmoV20_s
{
    // @desc: type="bool", alias="Enable", default="1", hide="0", ro="0" 
    
   _Bool 
                Enable;
    // @desc: alias="GlobalLuma", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbGlobalLuma_t GlobalLuma;
    // @desc: alias="DetailsHighLight", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbDetailsHighLight_t DetailsHighLight;
    // @desc: alias="DetailsLowLight", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbDetailsLowLight_t DetailsLowLight;
    // @desc: alias="LocalTMO", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbLocalTMO_t LocalTMO;
    // @desc: alias="GlobaTMO", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbGlobaTMO_t GlobaTMO;
    // @desc: alias="damp", type="f32", size="[1,1]", range="[0, 1]", default="0.9", digit="[4]", hide="0", ro="0" 
    float damp;
} CalibDbTmoV20_t;

typedef struct CalibDbV2_tmo_s
{
    // @desc: alias="TmoTuningPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbTmoV20_t TmoTuningPara;
} CalibDbV2_tmo_t;



/*
 * awb_head.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */









typedef enum CalibDbV2_Awb_Down_Scale_Mode_e {
  CALIB_AWB_DS_4X4 = 0,
  CALIB_AWB_DS_8X8 = 1,
} CalibDbV2_Awb_Down_Scale_Mode_t;

typedef enum CalibDbV2_Awb_Blk_Stat_Mode_V21_e {
  CALIB_AWB_BLK_STAT_MODE_ALL_V201 = 0,
  CALIB_AWB_BLK_STAT_MODE_REALWP_V201 = 1,
} CalibDbV2_Awb_Blk_Stat_Mode_V21_t;

typedef enum CalibDbV2_Awb_Blk_Stat_Mode_V20_e {
  CALIB_AWB_BLK_STAT_MODE_ALL_V200 = 1,
  CALIB_AWB_BLK_STAT_MODE_UVWP_V200 = 2,
  CALIB_AWB_BLK_STAT_MODE_XYWP_V200 = 3,
} CalibDbV2_Awb_Blk_Stat_Mode_V20_t;


typedef enum CalibDbV2_Awb_Ext_Range_Domain_e {
  CALIB_AWB_EXTRA_RANGE_DOMAIN_UV = 0,
  CALIB_AWB_EXTRA_RANGE_DOMAIN_XY = 1
} CalibDbV2_Awb_Ext_Range_Domain_t;

typedef enum CalibDbV2_Awb_Ext_Range_Mode_s {
  CALIB_AWB_EXCLUDE_WP_MODE = 1,
  CALIB_AWB_EXTTRA_LIGHT_SOURCES_MODE = 3,
} CalibDbV2_Awb_Ext_Range_Mode_t;

typedef struct CalibDbV2_ExtRange_s {
  // @desc: type="enum", alias="domain", enum_def="CalibDbV2_Awb_Ext_Range_Domain_t", default="CALIB_AWB_EXTRA_RANGE_DOMAIN_UV", ro="0" 
  CalibDbV2_Awb_Ext_Range_Domain_t domain;/*0uv domain,1 xy domain*/
  // @desc: type="enum", alias="mode", enum_def="CalibDbV2_Awb_Ext_Range_Mode_t", default="CALIB_AWB_EXCLUDE_WP_MODE", ro="0" 
  CalibDbV2_Awb_Ext_Range_Mode_t mode;
  // @desc: alias="region", type="s32", size="[1, 4]", range="[-8192, 8191]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
  int region[4];
} CalibDbV2_ExtRange_t;

typedef struct CalibDbV2_Yuv3D_Range_Ill_s {
  // @desc: alias="b_uv", type="s32", size="[1,1]", range="[-65536, 65535]", default="0", digit="[0]", hide="1", ro="0" 
  int b_uv; //17+0 s
  // @desc: alias="slope_inv_neg_uv", type="s32", size="[1,1]", range="[-262144, 262143]", default="0", digit="[0]", hide="0", ro="0" 
  int slope_inv_neg_uv; //9+10s //-1/k
  // @desc: alias="slope_factor_uv", type="s32", size="[1,1]", range="[-16384, 16383]", default="0", digit="[0]", hide="1", ro="0" 
  int slope_factor_uv; //1+14s // 1/(-1/k+k)
  // @desc: alias="slope_ydis", type="s32", size="[1,1]", range="[-262144, 262143]", default="0", digit="[0]", hide="1", ro="0" 
  int slope_ydis; //9+10s //k
  // @desc: alias="b_ydis", type="s32", size="[1,1]", range="[-65536, 65535]", default="0", digit="[0]", hide="1", ro="0" 
  int b_ydis; //17+0s
  // @desc: alias="ref_v", type="u8", size="[1,1]", range="[0, 255]", default="0", digit="[0]", hide="1", ro="0" 
  unsigned char ref_v;//8u
  // @desc: alias="dis", type="u16", size="[1, 6]", range="[0, 4095]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
  unsigned short dis[6];//8+4 u
  // @desc: alias="th", type="u8", size="[1, 6]", range="[0, 255]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
  unsigned char th[6]; //8u
} CalibDbV2_Yuv3D_Range_Ill_t;

typedef struct CalibDbV2_Yuv3D_2_Range_Ill_s {
  // @desc: alias="thcurve_u", type="f32", size="[1, 6]", range="[0, 255]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
  float thcurve_u[6];
  // @desc: alias="thcure_th", type="f32", size="[1, 6]", range="[0, 8]", default="0", digit="[4]", dynamic="0", hide="0", ro="0" 
  float thcure_th[6];
  // @desc: alias="lineVector", type="f32", size="[1, 6]", range="[0, 255]", default="0", digit="[4]", dynamic="0", hide="1", ro="0" 
  float lineVector[6];
  // @desc: alias="disP1P2", type="u8", size="[1,1]", range="[0, 255]", default="0", digit="[0]", hide="1", ro="0" 
  unsigned char disP1P2;
} CalibDbV2_Yuv3D_2_Range_Ill_t;

typedef struct CalibDbV2_Tcs_Range_Ill_s {
  // @desc: alias="normal", type="f32", size="[1, 4]", range="[-8, 8]", default="0", digit="[4]", dynamic="0", hide="0", ro="0" 
  float normal[4];
  // @desc: alias="big", type="f32", size="[1, 4]", range="[-8, 8]", default="0", digit="[4]", dynamic="0", hide="0", ro="0" 
  float big[4];
  // @desc: alias="small", type="f32", size="[1, 4]", range="[-8, 8]", default="0", digit="[4]", dynamic="0", hide="0", ro="0" 
  float small[4];
} CalibDbV2_Tcs_Range_Ill_t;

typedef struct CalibDbV2_Tcs_Range_Ill2_s {
  // @desc: alias="normal", type="f32", size="[1, 4]", range="[-8, 8]", default="0", digit="[4]", dynamic="0", hide="0", ro="0" 
  float normal[4];
  // @desc: alias="big", type="f32", size="[1, 4]", range="[-8, 8]", default="0", digit="[4]", dynamic="0", hide="0", ro="0" 
  float big[4];
} CalibDbV2_Tcs_Range_Ill2_t;

typedef struct CalibDbV2_Uv_Range_Ill_s {
  // @desc: alias="u", type="f32", size="[1, 4]", range="[0, 255]", default="0", digit="[1]", dynamic="0", hide="0", ro="0" 
  float u[4];
  // @desc: alias="v", type="f32", size="[1, 4]", range="[0, 255]", default="0", digit="[1]", dynamic="0", hide="0", ro="0" 
  float v[4];
} CalibDbV2_Uv_Range_Ill_t;

typedef enum CalibDbV2_Awb_DoorType_e {
  CALIB_AWB_DOOR_TYPE_INDOOR = 1,
  CALIB_AWB_DOOR_TYPE_AMBIGUITY = 2,
  CALIB_AWB_DOOR_TYPE_OUTDOOR = 3,
} CalibDbV2_Awb_DoorType_t;

typedef struct CalibDbV2_Awb_Light_V20_s {
  // @desc: alias="name", type="string", size="[1, 1]", range="[0, 16]", default="default", dynamic="0", hide="0", ro="0" 
  char* name;
  // @desc: type="enum", alias="doorType", enum_def="CalibDbV2_Awb_DoorType_t", default="CALIB_AWB_DOOR_TYPE_AMBIGUITY", ro="0" 
  CalibDbV2_Awb_DoorType_t doorType;
  // @desc: alias="standardGainValue", type="f32", size="[1, 4]", range="[0, 4]", default="1.0", digit="[4]", dynamic="0", hide="0", ro="0" 
  float standardGainValue[4];
  // @desc: alias="uvRegion", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
  CalibDbV2_Uv_Range_Ill_t uvRegion;
  // @desc: alias="xyRegion", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
  CalibDbV2_Tcs_Range_Ill_t xyRegion;
  // @desc: alias="yuvRegion", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Yuv3D_Range_Ill_t yuvRegion;
  // @desc: alias="staWeight", type="u8", size="[1, 16]", range="[0, 100]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
  unsigned char staWeight[16];
  // @desc: alias="dayGainLvThSet", type="u32", size="[1, 2]", range="[0, 255000]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
  unsigned int dayGainLvThSet[2];
  // @desc: alias="defaultDayGainLow", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
  float defaultDayGainLow[4];//spatial gain
  // @desc: alias="defaultDayGainHigh", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
  float defaultDayGainHigh[4];
  // @desc: type="bool", alias="xyType2Enable", default="1", hide="1", ro="0" 
  
 _Bool 
       xyType2Enable;
} CalibDbV2_Awb_Light_V20_t;

typedef enum CalibDb_Window_Mode_e {
  CALIB_AWB_WINDOW_CFG_AUTO = 0,
  CALIB_AWB_WINDOW_CFG_FIXED,
} CalibDb_Window_Mode_t;

typedef struct CalibDbV2_StatWindow_s {
  // @desc: type="enum", alias="mode", enum_def="CALIB_AWB_WINDOW_CFG_AUTO", default="CALIB_AWB_WINDOW_CFG_AUTO", ro="0" 
  CalibDb_Window_Mode_t mode;
  // @desc: alias="window", type="f32", size="[1, 4]", range="[0, 100]", default="[0 0 1 1]", digit="[2]", dynamic="0", hide="0", ro="0" 
  float window[4];//percent 100% ,between[0,100]
} CalibDbV2_StatWindow_t;

typedef struct CalibDbV2_Awb_Cct_Clip_Cfg_s {
  // @desc: type="bool", alias="enable", default="0", hide="0", ro="0" 
  
 _Bool 
      enable;
  // @desc: alias="cct", type="f32", size="[1, 5]", range="[0, 10000]", default="0", digit="[0]", dynamic="1", hide="0", ro="0" 
  float* cct;
  int cct_len;
  // @desc: alias="cri_bound_up", type="f32", size="[1, 5]", range="[0, 1]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
  float* cri_bound_up;
  int cri_bound_up_len;
  // @desc: alias="cri_bound_low", type="f32", size="[1, 5]", range="[0, 1]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
  float* cri_bound_low;
  int cri_bound_low_len;
} CalibDbV2_Awb_Cct_Clip_Cfg_t;

typedef struct CalibDbV2_Awb_Cct_DaylightClip_Cfg_s {
  // @desc: type="bool", alias="enable", default="0", hide="0", ro="0" 
  
 _Bool 
       enable;
  // @desc: alias="outdoor_cct_min", type="f32", size="[1,1]", range="[0, 10000]", default="5000", digit="[0]", hide="0", ro="0" 
  float outdoor_cct_min;
} CalibDbV2_Awb_Cct_DaylightClip_Cfg_t;

typedef struct CalibDbV2_Awb_Limit_Range_s {
  // @desc: alias="lumaValue", type="f32", size="[1, 5]", range="[0, 255000]", default="0", digit="[1]", dynamic="1", hide="0", ro="0" 
  float *lumaValue;
  int lumaValue_len;
  // @desc: alias="maxR", type="u16", size="[1, 5]", range="[0, 255]", default="230", digit="[0]", dynamic="1", hide="0", ro="0" 
  unsigned short *maxR;
  int maxR_len;
  // @desc: alias="minR", type="u16", size="[1, 5]", range="[0, 255]", default="3", digit="[0]", dynamic="1", hide="0", ro="0" 
  unsigned short *minR;
  int minR_len;
  // @desc: alias="maxG", type="u16", size="[1, 5]", range="[0, 255]", default="230", digit="[0]", dynamic="1", hide="0", ro="0" 
  unsigned short *maxG;
  int maxG_len;
  // @desc: alias="minG", type="u16", size="[1, 5]", range="[0, 255]", default="3", digit="[0]", dynamic="1", hide="0", ro="0" 
  unsigned short *minG;
  int minG_len;
  // @desc: alias="maxB", type="u16", size="[1, 5]", range="[0, 255]", default="230", digit="[0]", dynamic="1", hide="0", ro="0" 
  unsigned short *maxB;
  int maxB_len;
  // @desc: alias="minB", type="u16", size="[1, 5]", range="[0, 255]", default="3", digit="[0]", dynamic="1", hide="0", ro="0" 
  unsigned short *minB;
  int minB_len;
  // @desc: alias="maxY", type="u16", size="[1, 5]", range="[0, 255]", default="230", digit="[0]", dynamic="1", hide="0", ro="0" 
  unsigned short *maxY;
  int maxY_len;
  // @desc: alias="minY", type="u16", size="[1, 5]", range="[0, 255]", default="3", digit="[0]", dynamic="1", hide="0", ro="0" 
  unsigned short *minY;
  int minY_len;
} CalibDbV2_Awb_Limit_Range_t;

typedef struct CalibDbV2_Rgb2Tcs_s {
  // @desc: alias="pseudoLuminanceWeight", type="f32", size="[1, 3]", range="[0, 1]", default="0.3", digit="[6]", dynamic="0", hide="0", ro="0" 
  float pseudoLuminanceWeight[3];
  // @desc: alias="rotationMat", type="f32", size="[3, 3]", range="[0, 1]", default="0.3", digit="[6]", dynamic="0", hide="0", ro="0" 
  float rotationMat[9];
} CalibDbV2_Rgb2Tcs_t;

typedef struct CalibDbV2_Awb_Sgc_Cblk_s {
  // @desc: alias="index", type="u16", size="[1,1]", range="[1, 24]", default="1", digit="[0]", hide="0", ro="0" 
  unsigned short index;
  // @desc: alias="meanC", type="f32", size="[1,1]", range="[0, 255]", default="0", digit="[6]", hide="0", ro="0" 
  float meanC;
  // @desc: alias="meanH", type="f32", size="[1,1]", range="[-180, 180]", default="0", digit="[6]", hide="0", ro="0" 
  float meanH;
} CalibDbV2_Awb_Sgc_Cblk_t;

typedef struct CalibDbV2_Awb_Sgc_Ls_s {
  // @desc: alias="name", type="string", size="[1, 1]", range="[0, 16]", default="default", dynamic="0", hide="0", ro="0" 
  char* name;
  // @desc: alias="RGain", type="f32", size="[1,1]", range="[0, 8]", default="1", digit="[6]", hide="0", ro="0" 
  float RGain;
  // @desc: alias="BGain", type="f32", size="[1,1]", range="[0, 8]", default="1", digit="[6]", hide="0", ro="0" 
  float BGain;
} CalibDbV2_Awb_Sgc_Ls_t;

typedef struct CalibDbV2_Awb_Sgc_s {
  // @desc: type="bool", alias="enable", default="0", hide="0", ro="0" 
  
 _Bool 
      enable;
  // @desc: alias="colorBlock", type="struct_list", size="[1, 24]", ui_module="normal_ui_style", ro="0" 
  CalibDbV2_Awb_Sgc_Cblk_t *colorBlock;
  int colorBlock_len;
  // @desc: alias="lsUsedForEstimation", type="struct_list", size="[1, 7]", ui_module="normal_ui_style", ro="0" 
  CalibDbV2_Awb_Sgc_Ls_t *lsUsedForEstimation;
  int lsUsedForEstimation_len;
  // @desc: alias="alpha", type="f32", size="[1,1]", range="[0, 1]", default="1", digit="[4]", hide="0", ro="0" 
  float alpha;
} CalibDbV2_Awb_Sgc_t;

typedef enum CalibDbV2_Awb_Hdr_Fr_Ch_Mode_e {
  CALIB_AWB_HDR_FRAME_CHOOSE_MODE_MANUAL = 0,
  CALIB_AWB_HDR_FRAME_CHOOSE_MODE_AUTO
} CalibDbV2_Awb_Hdr_Fr_Ch_Mode_t;

typedef struct CalibDbV2_Awb_Hdr_Fr_Ch_s {
  // @desc: type="enum", alias="frameChooseMode", enum_def="CalibDbV2_Awb_Hdr_Fr_Ch_Mode_t", default="CALIB_AWB_HDR_FRAME_CHOOSE_MODE_AUTO", ro="0" 
  CalibDbV2_Awb_Hdr_Fr_Ch_Mode_t frameChooseMode;
  // @desc: alias="frameChoose", type="u8", size="[1,1]", range="[0, 2]", default="1", digit="[0]", hide="0", ro="0" 
  unsigned char frameChoose;
} CalibDbV2_Awb_Hdr_Fr_Ch_t;

typedef enum CalibDbV2_Awb_Mul_Win_Mode_e {
  CALIB_AWB_WIN_USELESS = 0,
  CALIB_AWB_WIN_EXTRAWP = 1,
  CALIB_AWB_WIN_WEIGHTWP = 2,
} CalibDbV2_Awb_Mul_Win_Mode_t;

typedef struct CalibDbV2_Awb_Mul_Win_s {
  // @desc: type="bool", alias="enable", default="1", hide="0", ro="0" 
  
 _Bool 
       enable;
  // @desc: type="enum", alias="multiwindowMode", enum_def="CalibDbV2_Awb_Mul_Win_Mode_t", default="CALIB_AWB_WIN_USELESS", ro="0" 
  CalibDbV2_Awb_Mul_Win_Mode_t multiwindowMode;
  // @desc: alias="window", type="u16", size="[8, 4]", range="[0, 8191]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
  float window[8][4];//8  windows in pixel domain ,hOffset,vOffser,hSize,vSize;
  // @desc: alias="weight", type="u16", size="[8, 4]", range="[0, 10]", default="0", digit="[4]", dynamic="0", hide="0", ro="0" 
  float weight;//weight for 8  windows;
} CalibDbV2_Awb_Mul_Win_t;

typedef struct CalibDbV2_Wb_Awb_Div_WpTh_s{
  //  @desc: alias="lumaValue", type="f32", size="[1, 5]", range="[0, 255000]", default="0", digit="[1]", dynamic="1", hide="0", ro="0" 
  float *lumaValue;
  int lumaValue_len;
  // @desc: alias="low", type="f32", size="[1, 5]", range="[0, 100000]", default="0", digit="[0]", dynamic="1", hide="0", ro="0" 
  float *low;
  int low_len;
  // @desc: alias="high", type="f32", size="[1, 5]", range="[0, 100000]", default="0", digit="[0]", dynamic="1", hide="0", ro="0" 
  float *high;
  int high_len;
}CalibDbV2_Wb_Awb_Div_WpTh_t;

typedef struct CalibDbV2_Wb_Awb_Div_s {
  // @desc: alias="lumaValThLow", type="u32", size="[1,1]", range="[0, 255000]", default="0", digit="[0]", hide="0", ro="0" 
  unsigned int lumaValThLow;
  // @desc: alias="lumaValThLow2", type="u32", size="[1,1]", range="[0, 255000]", default="0", digit="[0]", hide="0", ro="0" 
  unsigned int lumaValThLow2;
  // @desc: alias="lumaValThHigh", type="u32", size="[1,1]", range="[0, 255000]", default="0", digit="[0]", hide="0", ro="0" 
  unsigned int lumaValThHigh;
  // @desc: alias="lumaValThHigh2", type="u32", size="[1,1]", range="[0, 255000]", default="0", digit="[0]", hide="0", ro="0" 
  unsigned int lumaValThHigh2;
  // @desc: alias="wpNumTh", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
  CalibDbV2_Wb_Awb_Div_WpTh_t wpNumTh;
} CalibDbV2_Wb_Awb_Div_t;

typedef struct CalibDbV2_Wb_Awb_Caga_s {
  // @desc: type="bool", alias="enable", default="1", hide="0", ro="0" 
  
 _Bool 
      enable;
  // @desc: alias="targetGain", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
  float targetGain[4];//cagaTargetGain
  // @desc: alias="laCalcFactor", type="f32", size="[1,1]", range="[0, 255]", default="0", digit="[4]", hide="0", ro="0" 
  float laCalcFactor;
} CalibDbV2_Wb_Awb_Caga_t;

typedef struct CalibDbV2_Wb_Awb_Prob_Calc_Dis_s {
  // @desc: alias="proDis_THH", type="f32", size="[1,1]", range="[0, 8]", default="0", digit="[4]", hide="0", ro="0" 
  float proDis_THH; //threshold for distance probality calculation// rename to do
  // @desc: alias="proDis_THL", type="f32", size="[1,1]", range="[0, 8]", default="0", digit="[4]", hide="0", ro="0" 
  float proDis_THL;
} CalibDbV2_Wb_Awb_Prob_Calc_Dis_t;

typedef struct CalibDbV2_Wb_Awb_Prob_Calc_Lv_s {
  // @desc: alias="outdoorLumaValThLow", type="u32", size="[1,1]", range="[0, 255000]", default="0", digit="[0]", hide="0", ro="0" 
  unsigned int outdoorLumaValThLow;
  // @desc: alias="outdoorLumaValThHigh", type="u32", size="[1,1]", range="[0, 255000]", default="0", digit="[0]", hide="0", ro="0" 
  unsigned int outdoorLumaValThHigh;// threshold for luminance probality calculation
} CalibDbV2_Wb_Awb_Prob_Calc_Lv_t;

typedef struct CalibDbV2_Wb_Awb_Prob_Calc_Wp_s {
  // @desc: alias="wpNumPercTh", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[6]", hide="0", ro="0" 
  float wpNumPercTh;
  // @desc: alias="wpNumPercTh2", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[6]", hide="0", ro="0" 
  float wpNumPercTh2;
} CalibDbV2_Wb_Awb_Prob_Calc_Wp_t;

typedef struct CalibDbV2_Wb_Awb_Convg_s {
  // @desc: alias="varThforUnDamp", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[4]", hide="0", ro="0" 
  float varThforUnDamp;
  // @desc: alias="varThforDamp", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[4]", hide="0", ro="0" 
  float varThforDamp;
} CalibDbV2_Wb_Awb_Convg_t;

typedef struct CalibDbV2_Awb_Tolerance_s {
  // @desc: alias="lumaValue", type="f32", size="[1, 4]", range="[0, 255000]", default="0", digit="[0]", dynamic="1", hide="0", ro="0" 
  float* lumaValue;
  int lumaValue_len;
  // @desc: alias="toleranceValue", type="f32", size="[1, 4]", range="[0, 1]", default="0", digit="[4]", dynamic="1", hide="0", ro="0" 
  float* toleranceValue;
  int toleranceValue_len;
} CalibDbV2_Awb_Tolerance_t;

typedef struct CalibDbV2_Awb_runinterval_s {
  // @desc: alias="lumaValue", type="f32", size="[1, 4]", range="[0, 255000]", default="0", digit="[0]", dynamic="1", hide="0", ro="0" 
  float *lumaValue;
  int lumaValue_len;
  // @desc: alias="intervalValue", type="f32", size="[1, 4]", range="[0, 255]", default="0", digit="[0]", dynamic="1", hide="0", ro="0" 
  float *intervalValue;
  int intervalValue_len;
} CalibDbV2_Awb_runinterval_t;

typedef struct CalibDbV2_Awb_DampFactor_s {
  // @desc: alias="dFStep", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[4]", hide="0", ro="0" 
  float dFStep;
  // @desc: alias="dFMin", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[4]", hide="0", ro="0" 
  float dFMin;
  // @desc: alias="dFMax", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[4]", hide="0", ro="0" 
  float dFMax;
  // @desc: alias="lvIIRsize", type="u32", size="[1,1]", range="[0, 128]", default="0", digit="[0]", hide="0", ro="0" 
  int lvIIRsize;
  // @desc: alias="lvVarTh", type="f32", size="[1,1]", range="[0, 100]", default="0", digit="[4]", hide="0", ro="0" 
  float lvVarTh;
} CalibDbV2_Awb_DampFactor_t;

typedef struct CalibDbV2_Awb_Cct_Lut_Cfg_Lv_s {
  // @desc: alias="lumaValue", type="f32", size="[1,1]", range="[0, 255000]", default="0", digit="[0]", hide="0", ro="0" 
  float lumaValue;
  // @desc: alias="ct_grid_num", type="s32", size="[1,1]", range="[0, 32]", default="0", digit="[0]", hide="0", ro="0" 
  int ct_grid_num;
  // @desc: alias="cri_grid_num", type="s32", size="[1,1]", range="[0, 32]", default="0", digit="[0]", hide="0", ro="0" 
  int cri_grid_num;
  // @desc: alias="ct_in_range", type="f32", size="[1, 2]", range="[0, 10000]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
  float ct_in_range[2];//min,max, equal distance sapmle
  // @desc: alias="cri_in_range", type="f32", size="[1, 2]", range="[-2, 2]", default="0", digit="[4]", dynamic="0", hide="0", ro="0" 
  float cri_in_range[2];//min,max
  // @desc: alias="ct_lut_out", type="f32", size="[9, 7]", range="[0, 10000]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
  float *ct_lut_out;
  int ct_lut_out_len;
  // @desc: alias="cri_lut_out", type="f32", size="[9, 7]", range="[-2, 2]", default="0", digit="[4]", dynamic="0", hide="0", ro="0" 
  float *cri_lut_out;
  int cri_lut_out_len;
} CalibDbV2_Awb_Cct_Lut_Cfg_Lv_t;

typedef struct CalibDbV2_Awb_GainAdjust_s {
  // @desc: type="bool", alias="enable", default="1", hide="0", ro="0" 
  
 _Bool 
      enable;
  // @desc: alias="lutAll", type="struct_list", size="[1, 8]", ui_module="normal_ui_style", ro="0" 
  CalibDbV2_Awb_Cct_Lut_Cfg_Lv_t *lutAll;
  int lutAll_len;
} CalibDbV2_Awb_GainAdjust_t;

typedef struct CalibDbV2_Awb_Remosaic_Para_s {
  // @desc: type="bool", alias="enable", default="1", hide="0", ro="0" 
  
 _Bool 
      enable;
  // @desc: type="bool", alias="applyInvWbGainEnable", default="1", hide="0", ro="0" 
  
 _Bool 
      applyInvWbGainEnable;
  // @desc: alias="sensorWbGain", type="f32", size="[1, 4]", range="[0, 4]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
  float sensorWbGain[4];
} CalibDbV2_Awb_Remosaic_Para_t;

typedef struct CalibDbV2_Awb_xyRegion_stable_WpTh_s {
    // @desc: alias="lumaValue", type="f32", size="[1, 5]", range="[0, 255000]", default="0", digit="[1]", dynamic="1", hide="0", ro="0" 
    float *lumaValue;
    int lumaValue_len;
    // @desc: alias="forBigType", type="f32", size="[1, 5]", range="[0, 100000]", default="0", digit="[0]", dynamic="1", hide="0", ro="0" 
    float *forBigType;
    int forBigType_len;
    // @desc: alias="forExtraType", type="f32", size="[1, 5]", range="[0, 100000]", default="0", digit="[0]", dynamic="1", hide="0", ro="0" 
    float *forExtraType;
    int forExtraType_len;
} CalibDbV2_Awb_xyRegion_stable_WpTh_t;

typedef struct CalibDbV2_Awb_xyRegion_stable_s {
  // @desc: type="bool", alias="enable", default="1", hide="0", ro="0" 
  
 _Bool 
      enable;
  //  @desc: alias="wpNumTh", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
  CalibDbV2_Awb_xyRegion_stable_WpTh_t wpNumTh;
  // @desc: alias="xyTypeListSize", type="s32", size="[1,1]", range="[0, 65535]", default="0", digit="[0]", hide="0", ro="0" 
  int xyTypeListSize;// xyTypeListSize ==0 will disable this function
  // @desc: alias="varianceLumaTh", type="f32", size="[1,1]", range="[0, 100]", default="0", digit="[4]", hide="0", ro="0" 
  float varianceLumaTh;
} CalibDbV2_Awb_xyRegion_stable_t;

typedef struct CalibDbV2_Awb_gain_offset_cfg_s{
  // @desc: type="bool", alias="enable", default="1", hide="0", ro="0" 
  
 _Bool 
      enable;
  // @desc: alias="offset", type="f32", size="[1, 4]", range="[-8, 8]", default="0", digit="[4]", dynamic="0", hide="0", ro="0" 
  float offset[4];//rggb
}CalibDbV2_Awb_gain_offset_cfg_t;

typedef struct CalibDbV2_Wb_Awb_Ext_Com_Para_t{
  // @desc: alias="lightSourceForFirstFrame", type="string", size="[1, 1]", range="[-128, 127]", default="default", dynamic="0", hide="0", ro="0" 
  char *lightSourceForFirstFrame;
  // @desc: alias="tolerance", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
  CalibDbV2_Awb_Tolerance_t tolerance;//wb gain diff th for awb gain update, set 0 to disable this function
  // @desc: alias="runInterval", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
  CalibDbV2_Awb_runinterval_t runInterval;
  // @desc: alias="dampFactor", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Awb_DampFactor_t dampFactor;
  // @desc: alias="wbGainAdjust", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Awb_GainAdjust_t wbGainAdjust;
  // @desc: alias="wbGainDaylightClip", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Awb_Cct_DaylightClip_Cfg_t wbGainDaylightClip;
  // @desc: alias="wbGainClip", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Awb_Cct_Clip_Cfg_t wbGainClip;
  // @desc: alias="division", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Wb_Awb_Div_t division;
  // @desc: alias="defaultNightGain", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
  float defaultNightGain[4];
  // @desc: alias="lumaValueMatrix", type="u32", size="[1, 16]", range="[0, 255000]", default="1", digit="[0]", dynamic="0", hide="0", ro="0" 
  unsigned int lumaValueMatrix[16];
  // @desc: alias="defaultNightGainWeight", type="u8", size="[1, 16]", range="[0, 100]", default="1", digit="[0]", dynamic="0", hide="0", ro="0" 
  unsigned char defaultNightGainWeight[16];
  // @desc: alias="probCalcDis", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Wb_Awb_Prob_Calc_Dis_t probCalcDis;
  // @desc: alias="probCalcLv", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Wb_Awb_Prob_Calc_Lv_t probCalcLv;
  // @desc: alias="probCalcWp", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Wb_Awb_Prob_Calc_Wp_t probCalcWp;
  // @desc: alias="converged", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Wb_Awb_Convg_t converged;
  // @desc: alias="xyRegionStableSelection", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Awb_xyRegion_stable_t xyRegionStableSelection;
  // @desc: alias="weightForNightGainCalc", type="u8", size="[1, 16]", range="[0, 100]", default="1", digit="[0]", dynamic="1", hide="0", ro="0" 
  unsigned char *weightForNightGainCalc;
  int weightForNightGainCalc_len;
  // @desc: alias="singleColorProces", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Awb_Sgc_t singleColorProces;
  // @desc: alias="lineRgBg", type="f32", size="[1, 3]", range="[-2147483648, 2147483647]", default="1", digit="[4]", dynamic="0", hide="1", ro="0" 
  float lineRgBg[3];
  // @desc: alias="lineRgProjCCT", type="f32", size="[1, 3]", range="[-2147483648, 2147483647]", default="1", digit="[4]", dynamic="0", hide="1", ro="0" 
  float lineRgProjCCT[3];
  // @desc: alias="chrAdpttAdj", type="struct", ui_module="normal_ui_style", hide="1", ro="0" 
  CalibDbV2_Wb_Awb_Caga_t chrAdpttAdj;
  // @desc: alias="remosaicCfg", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Awb_Remosaic_Para_t remosaicCfg;
  // @desc: alias="wbGainOffset", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Awb_gain_offset_cfg_t wbGainOffset;
} CalibDbV2_Wb_Awb_Ext_Com_Para_t;


typedef struct CalibDbV2_Wb_Awb_Para_V20_t {
  // @desc: alias="hdrPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Awb_Hdr_Fr_Ch_t hdrPara;
  // @desc: type="bool", alias="lscBypassEnable", default="0", hide="0", ro="0" ;
  
 _Bool 
                     lscBypassEnable;
  // @desc: type="bool", alias="uvDetectionEnable", default="1", hide="0", ro="0" ;
  
 _Bool 
                     uvDetectionEnable;
  // @desc: type="bool", alias="xyDetectionEnable", default="1", hide="0", ro="0" ;
  
 _Bool 
                     xyDetectionEnable;
  // @desc: type="bool", alias="yuvDetectionEnable", default="1", hide="0", ro="0" ;
  
 _Bool 
                     yuvDetectionEnable;
  // CXF CHECK
  // @desc: alias="lsUsedForYuvDet", type="string", size="[1, 7]", range="[-128, 127]", default="light", dynamic="1", hide="1", ro="0" ;
  char** lsUsedForYuvDet;
  int lsUsedForYuvDet_len;
  // @desc: alias="yuvDetRef_u", type="u8", size="[1,1]", range="[0, 255]", default="0", digit="[0]", hide="1", ro="0" 
  unsigned char yuvDetRef_u; //8u //cxf3333
  // @desc: type="enum", alias="downScaleMode", enum_def="CalibDbV2_Awb_Down_Scale_Mode_t", default="CALIB_AWB_DS_4X4", ro="0" ;
  CalibDbV2_Awb_Down_Scale_Mode_t downScaleMode;
  // @desc: type="enum", alias="blkMeasureMode", enum_def="CalibDbV2_Awb_Blk_Stat_Mode_V20_t", default="CALIB_AWB_BLK_STAT_MODE_ALL_V200", ro="0" ;
  CalibDbV2_Awb_Blk_Stat_Mode_V20_t blkMeasureMode;
  // @desc: alias="mainWindow", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_StatWindow_t mainWindow;
  // @desc: alias="limitRange", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
  CalibDbV2_Awb_Limit_Range_t limitRange;
  // @desc: alias="rgb2TcsPara", type="struct", ui_module="normal_ui_style", hide="1", ro="0" 
  CalibDbV2_Rgb2Tcs_t rgb2TcsPara;
  // @desc: alias="multiWindow", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Awb_Mul_Win_t multiWindow;
  // @desc: alias="extraWpRange", type="struct_list", size="[1, 7]", ui_module="normal_ui_style", ro="0" 
  CalibDbV2_ExtRange_t extraWpRange[7];
  // @desc: alias="lightSources", type="struct_list", size="[1, 7]", ui_module="normal_ui_style", ro="0" 
  CalibDbV2_Awb_Light_V20_t* lightSources;
  int lightSources_len;
} CalibDbV2_Wb_Awb_Para_V20_t;

typedef struct CalibDbV2_Awb_Luma_Weight_Enable_Th_s {
  // @desc: alias="wpDiffWeiNoTh", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[4]", hide="0", ro="0" 
  float wpDiffWeiNoTh;
  // @desc: alias="wpDiffWeiLvValueTh", type="u32", size="[1,1]", range="[0, 255000]", default="0", digit="[0]", hide="0", ro="0" 
  unsigned int wpDiffWeiLvValueTh;
} CalibDbV2_Awb_Luma_Weight_Enable_Th_t;

typedef struct CalibDbV2_Awb_Luma_Weight_Lv_Ratio_s {
  // @desc: alias="ratioValue", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[4]", hide="0", ro="0" 
  float ratioValue;
  // @desc: alias="weight", type="f32", size="[1, 9]", range="[0, 1]", default="0", digit="[4]", dynamic="0", hide="0", ro="0" 
  float weight[9] ;
} CalibDbV2_Awb_Luma_Weight_Lv_Ratio_t;

typedef struct CalibDbV2_Awb_Luma_Weight_Lv_s {
  // @desc: alias="LvValue", type="f32", size="[1,1]", range="[0, 255000]", default="0", digit="[0]", hide="0", ro="0" 
  float LvValue;
  // @desc: alias="ratioSet", type="struct_list", size="[1, 4]", ui_module="normal_ui_style", ro="0" 
  CalibDbV2_Awb_Luma_Weight_Lv_Ratio_t* ratioSet;
  int ratioSet_len;
} CalibDbV2_Awb_Luma_Weight_Lv_t;

typedef struct CalibDbV2_Awb_Luma_Weight_s {
  //with differernt luma ,the different weight in WP sum
  // @desc: type="bool", alias="enable", default="0", hide="0", ro="0" ;
  
 _Bool 
      enable;
  // @desc: alias="wpDiffWeiEnableTh", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Awb_Luma_Weight_Enable_Th_t wpDiffWeiEnableTh;
  // @desc: alias="wpDiffwei_y", type="u8", size="[1, 9]", range="[0, 255]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
  unsigned char wpDiffwei_y[9];
  // @desc: alias="perfectBin", type="u8", size="[1, 8]", range="[0, 1]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
  unsigned char perfectBin[8];// true means the luma is appropriate
  // @desc: alias="wpDiffWeightLvSet", type="struct_list", size="[1, 4]", ui_module="normal_ui_style", ro="0" 
  CalibDbV2_Awb_Luma_Weight_Lv_t* wpDiffWeightLvSet;
  int wpDiffWeightLvSet_len;
} CalibDbV2_Awb_Luma_Weight_t;

typedef struct CalibDbV2_Awb_Light_V21_s {
  // @desc: alias="name", type="string", size="[1, 1]", range="[0, 32]", default="default", dynamic="0", hide="0", ro="0" 
  char* name;
  // @desc: type="enum", alias="doorType", enum_def="CalibDbV2_Awb_DoorType_t", default="CALIB_AWB_DOOR_TYPE_AMBIGUITY", ro="0" 
  CalibDbV2_Awb_DoorType_t doorType;
  // @desc: alias="standardGainValue", type="f32", size="[1, 4]", range="[0, 8]", default="0", digit="[4]", dynamic="0", hide="0", ro="0" 
  float standardGainValue[4];
  // @desc: alias="uvRegion", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
  CalibDbV2_Uv_Range_Ill_t uvRegion;
  // @desc: alias="xyRegion", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
  CalibDbV2_Tcs_Range_Ill2_t xyRegion;
  // @desc: alias="rtYuvRegion", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Yuv3D_2_Range_Ill_t rtYuvRegion;
  // @desc: alias="staWeight", type="u8", size="[1, 16]", range="[0, 100]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
  unsigned char staWeight[16];
  // @desc: alias="dayGainLvThSet", type="u8", size="[1, 2]", range="[0, 255000]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
  unsigned int dayGainLvThSet[2];
  // @desc: alias="defaultDayGainLow", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
  float defaultDayGainLow[4];//spatial gain
  // @desc: alias="defaultDayGainHigh", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
  float defaultDayGainHigh[4];
  // @desc: alias="xyType2Enable", type="u8", size="[1,1]", range="[0, 1]", default="1", digit="[0]", hide="1", ro="0" 
  unsigned char xyType2Enable;
} CalibDbV2_Awb_Light_V21_t;

typedef struct CalibDbV2_Wb_Awb_Para_V21_t {
  // @desc: alias="hdrPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Awb_Hdr_Fr_Ch_t hdrPara;//hdrFrameChoose;
  // @desc: type="bool", alias="lscBypassEnable", default="0", hide="0", ro="0" ;
  
 _Bool 
                     lscBypassEnable;
  // @desc: type="bool", alias="uvDetectionEnable", default="0", hide="0", ro="0" ;
  
 _Bool 
                     uvDetectionEnable;
  // @desc: type="bool", alias="xyDetectionEnable", default="0", hide="0", ro="0" ;
  
 _Bool 
                     xyDetectionEnable;
  // @desc: type="bool", alias="yuvDetectionEnable", default="0", hide="0", ro="0" ;
  
 _Bool 
                     yuvDetectionEnable;
  // @desc: alias="lsUsedForYuvDet", type="string", size="[1, 7]", range="[0, 16]", default="default", dynamic="1", hide="1", ro="0" 
  char** lsUsedForYuvDet;
  int lsUsedForYuvDet_len;
  // @desc: type="bool", alias="blkStatisticsEnable", default="0", hide="0", ro="0" ;
  
 _Bool 
                     blkStatisticsEnable;
  // @desc: type="enum", alias="downScaleMode", enum_def="CalibDbV2_Awb_Down_Scale_Mode_t", default="CALIB_AWB_DS_8X8", ro="0" 
  CalibDbV2_Awb_Down_Scale_Mode_t downScaleMode;
  // @desc: type="enum", alias="blkMeasureMode", enum_def="CalibDbV2_Awb_Blk_Stat_Mode_V21_t", default="CALIB_AWB_BLK_STAT_MODE_REALWP_V201", ro="0" 
  CalibDbV2_Awb_Blk_Stat_Mode_V21_t blkMeasureMode;
  // @desc: alias="mainWindow", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_StatWindow_t mainWindow;
  // @desc: alias="limitRange", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
  CalibDbV2_Awb_Limit_Range_t limitRange;
  // @desc: alias="rgb2TcsPara", type="struct", ui_module="normal_ui_style", hide="1", ro="0" 
  CalibDbV2_Rgb2Tcs_t rgb2TcsPara;
  // @desc: alias="rgb2RotationYuvMat", type="f32", size="[4, 4]", range="[-255, 255]", default="0", digit="[6]", dynamic="0", hide="1", ro="0" 
  float rgb2RotationYuvMat[16];
  //several winow in uv or xy domain
  // @desc: alias="extraWpRange", type="struct_list", size="[1, 7]", ui_module="normal_ui_style", ro="0" 
  CalibDbV2_ExtRange_t extraWpRange[7];
  // @desc: alias="wpDiffLumaWeight", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Awb_Luma_Weight_t wpDiffLumaWeight;
  // @desc: type="bool", alias="wpDiffBlkWeiEnable", default="0", hide="0", ro="0" ;
  
 _Bool 
                wpDiffBlkWeiEnable;
  // @desc: alias="wpDiffBlkWeight", type="u16", size="[15, 15]", range="[0, 63]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
  unsigned short wpDiffBlkWeight[225];
  // @desc: alias="lightSources", type="struct_list", size="[1, 7]", ui_module="normal_ui_style", ro="0" 
  CalibDbV2_Awb_Light_V21_t* lightSources;
  int lightSources_len;
} CalibDbV2_Wb_Awb_Para_V21_t;

typedef enum CalibDbV2_Wb_Mwb_Mode_e {
  CALIB_MWB_MODE_CCT = 1, /**< run manual white balance by cct*/
  CALIB_MWB_MODE_WBGAIN = 2, /**< run manual white balance by wbgain*/
  CALIB_MWB_MODE_SCENE = 3, /**< run manual white balance by scene selection*/
} CalibDbV2_Wb_Mwb_Mode_t;

typedef enum CalibDbV2_Wb_Mwb_Scene_e {
  CALIB_WB_SCENE_INCANDESCENT = 0,
  CALIB_WB_SCENE_FLUORESCENT,
  CALIB_WB_SCENE_WARM_FLUORESCENT,
  CALIB_WB_SCENE_DAYLIGHT,
  CALIB_WB_SCENE_CLOUDY_DAYLIGHT,
  CALIB_WB_SCENE_TWILIGHT,
  CALIB_WB_SCENE_SHADE
} CalibDbV2_Wb_Mwb_Scene_t;

typedef struct CalibDbV2_Awb_Cct_s {
  // @desc: alias="CCT", type="f32", size="[1,1]", range="[0, 10000]", default="5000", digit="[0]", hide="0", ro="0" 
  float CCT;
  // CXF CHECK
  // @desc: alias="CCRI", type="f32", size="[1,1]", range="[-2, 2]", default="0", digit="[3]", hide="0", ro="0" 
  float CCRI;
} CalibDbV2_Awb_Cct_t;
typedef struct CalibDbV2_Wb_Mwb_Cfg_Para_s{
  // @desc: alias="mwbGain", type="f32", size="[1, 4]", range="[0, 8]", default="1.0", digit="[4]", dynamic="0", hide="0", ro="0" 
  float mwbGain[4];
  // @desc: type="enum", alias="scene", enum_def="CalibDbV2_Wb_Mwb_Scene_t", default="CALIB_WB_SCENE_DAYLIGHT", ro="0" ;
  CalibDbV2_Wb_Mwb_Scene_t scene;
  // @desc: alias="cct", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Awb_Cct_t cct;
}CalibDbV2_Wb_Mwb_Cfg_Para_t;

typedef struct CalibDbV2_Wb_Mwb_Para_s {
  // @desc: type="enum", alias="mode", enum_def="CalibDbV2_Wb_Mwb_Mode_t", default="CALIB_MWB_MODE_WBGAIN", ro="0" ;
  CalibDbV2_Wb_Mwb_Mode_t mode;
  // @desc: alias="cfg", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Wb_Mwb_Cfg_Para_t cfg;
} CalibDbV2_Wb_Mwb_Para_t;

typedef enum CalibDbV2_Wb_Op_Mode_e {
  CALIB_WB_MODE_MANUAL = 0, /**< run manual white balance */
  CALIB_WB_MODE_AUTO = 1, /**< run auto white balance */
} CalibDbV2_Wb_Op_Mode_t;

typedef struct CalibDbV2_Wb_Para_t {
  // @desc: type="bool", alias="byPass", default="0", hide="0", ro="0" ;
  
 _Bool 
      byPass;
  // @desc: type="enum", alias="mode", enum_def="CalibDbV2_Wb_Op_Mode_t", default="CALIB_WB_MODE_AUTO", ro="0" ;
  CalibDbV2_Wb_Op_Mode_t mode;//replace awbEnable
} CalibDbV2_Wb_Para_t;

typedef struct CalibDbV2_Wb_Para_V20_s {
  // @desc: alias="control", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Wb_Para_t control;
  // @desc: alias="manualPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Wb_Mwb_Para_t manualPara;
  // @desc: alias="autoPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Wb_Awb_Para_V20_t autoPara;
  // @desc: alias="autoExtPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Wb_Awb_Ext_Com_Para_t autoExtPara;
} CalibDbV2_Wb_Para_V20_t;

typedef struct CalibDbV2_Wb_Para_V21_s {
  // @desc: alias="control", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Wb_Para_t control;
  // @desc: alias="manualPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Wb_Mwb_Para_t manualPara;
  // @desc: alias="autoPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Wb_Awb_Para_V21_t autoPara;
  // @desc: alias="autoExtPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
  CalibDbV2_Wb_Awb_Ext_Com_Para_t autoExtPara;
} CalibDbV2_Wb_Para_V21_t;


/*
 * bayernr_head_v1.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */



////////////////////////bayernr V2//////////////////////////////////////
typedef struct CalibDbV2_Bayer2dnr_V2_CalibPara_Setting_ISO_s {
    // @desc: alias="iso", type="f32", range="[50, 204800]", default="50", digit="[1]", ui_module_param="index2", ro="0" 
    float iso;

    // @desc: alias="lumapoint", type="s32", size="[1, 16]", range="[0, 65535]", default="0.0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int lumapoint[16];

    // @desc: alias="sigma", type="s32", size="[1, 16]", range="[0, 65535]", default="0.0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int sigma[16];

} CalibDbV2_Bayer2dnr_V2_CalibPara_Setting_ISO_t;

typedef struct CalibDbV2_Bayer2dnr_V2_CalibPara_Setting_s {
    // @desc: alias="SNR_Mode", type="string", size="[1, 1]", range="[0, 64]", default="LSNR", dynamic="0", ui_module_param="index1", ro="0" 
    char *SNR_Mode;
    // @desc: alias="Sensor_Mode", type="string", size="[1, 1]", range="[0, 64]", default="lcg", dynamic="0", hide="0", ro="0" 
    char *Sensor_Mode;
    // @desc: alias="Calib_ISO", type="struct_list", size="dynamic", ui_module="double_index_list", ro="0" 
    CalibDbV2_Bayer2dnr_V2_CalibPara_Setting_ISO_t *Calib_ISO;
    int Calib_ISO_len;

} CalibDbV2_Bayer2dnr_V2_CalibPara_Setting_t;

typedef struct CalibDbV2_Bayer2dnr_V2_CalibPara_s {
    // @desc: alias="Setting", type="struct_list", size="dynamic", ui_module="double_index_list", ro="0" 
    CalibDbV2_Bayer2dnr_V2_CalibPara_Setting_t *Setting;
    int Setting_len;
} CalibDbV2_Bayer2dnr_V2_CalibPara_t;

typedef struct CalibDbV2_Bayer2dnr_V2_TuningPara_Setting_ISO_s {
    // @desc: alias="iso", type="f32", range="[50, 204800]", default="50", digit="[1]", ui_module_param="index2", ro="0" 
    float iso;

    // @desc: type="bool", alias="gauss_guide", default="1", hide="0", ro="0" 
    
   _Bool 
        gauss_guide;

    // @desc: alias="filter_strength", type="f32", size="[1,1]", range="[0, 16]", default="0.5", digit="[2]", hide="0", ro="0" 
    float filter_strength;

    // @desc: alias="edgesofts", type="f32", size="[1,1]", range="[0, 16.0]", default="1.0", digit="[2]", hide="0", ro="0" 
    float edgesofts;

    // @desc: alias="ratio", type="f32", size="[1,1]", range="[0, 1.0]", default="0.2", digit="[2]", hide="0", ro="0" 
    float ratio;

    // @desc: alias="weight", type="f32", size="[1,1]", range="[0, 1.0]", default="1.0", digit="[2]", hide="0", ro="0" 
    float weight;

} CalibDbV2_Bayer2dnr_V2_TuningPara_Setting_ISO_t;

typedef struct CalibDbV2_Bayer2dnr_V2_TuningPara_Setting_s {
    // @desc: alias="SNR_Mode", type="string", size="[1, 1]", range="[0, 64]", default="LSNR", dynamic="0", ui_module_param="index1", ro="0" 
    char *SNR_Mode;
    // @desc: alias="Sensor_Mode", type="string", size="[1, 1]", range="[0, 64]", default="lcg", dynamic="0", hide="0", ro="0" 
    char *Sensor_Mode;
    // @desc: alias="Tuning_ISO", type="struct_list", size="dynamic", ui_module="double_index_list", ro="0" 
    CalibDbV2_Bayer2dnr_V2_TuningPara_Setting_ISO_t *Tuning_ISO;
    int Tuning_ISO_len;
} CalibDbV2_Bayer2dnr_V2_TuningPara_Setting_t;

typedef struct CalibDbV2_Bayer2dnr_V2_TuningPara_s {
    // @desc: type="bool", alias="enable", default="1", hide="0", ro="0" 
    
   _Bool 
        enable;
    // @desc: alias="Setting", type="struct_list", size="dynamic", ui_module="double_index_list", ro="0" 
    CalibDbV2_Bayer2dnr_V2_TuningPara_Setting_t *Setting;
    int Setting_len;
} CalibDbV2_Bayer2dnr_V2_TuningPara_t;



typedef struct CalibDbV2_Bayer2dnr_V2_s {
    // @desc: alias="Version", type="string", size="[1, 1]", range="[0, 64]", default="V2", dynamic="0", hide="0", ro="0" 
    char *Version;
    // @desc: alias="CalibPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Bayer2dnr_V2_CalibPara_t CalibPara;
    // @desc: alias="Bayernr2D", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Bayer2dnr_V2_TuningPara_t TuningPara;
    // @desc: alias="Bayernr3D", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
} CalibDbV2_Bayer2dnr_V2_t;


/*
 * bayernr_head_v1.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */



////////////////////////bayernr V2//////////////////////////////////////
typedef struct CalibDbV2_BayerTnr_V2_CalibPara_Setting_ISO_s {
    // @desc: alias="iso", type="f32", range="[50, 204800]", default="50", digit="[1]", ui_module_param="index2", ro="0" 
    float iso;

    // @desc: alias="lumapoint", type="s32", size="[1, 16]", range="[0, 65535]", default="0.0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int lumapoint[16];

    // @desc: alias="sigma", type="s32", size="[1, 16]", range="[0, 65535]", default="0.0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int sigma[16];

    // @desc: alias="lumapoint2", type="s32", size="[1, 16]", range="[0, 65535]", default="0.0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int lumapoint2[16];

    // @desc: alias="lo_sigma", type="s32", size="[1, 16]", range="[0, 65535]", default="0.0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int lo_sigma[16];

    // @desc: alias="hi_sigma", type="s32", size="[1, 16]", range="[0, 65535]", default="0.0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int hi_sigma[16];

} CalibDbV2_BayerTnr_V2_CalibPara_Setting_ISO_t;

typedef struct CalibDbV2_BayerTnr_V2_CalibPara_Setting_s {
    // @desc: alias="SNR_Mode", type="string", size="[1, 1]", range="[0, 64]", default="LSNR", dynamic="0", ui_module_param="index1", ro="0" 
    char *SNR_Mode;
    // @desc: alias="Sensor_Mode", type="string", size="[1, 1]", range="[0, 64]", default="lcg", dynamic="0", hide="0", ro="0" 
    char *Sensor_Mode;
    // @desc: alias="Calib_ISO", type="struct_list", size="dynamic", ui_module="double_index_list", ro="0" 
    CalibDbV2_BayerTnr_V2_CalibPara_Setting_ISO_t *Calib_ISO;
    int Calib_ISO_len;

} CalibDbV2_BayerTnr_V2_CalibPara_Setting_t;

typedef struct CalibDbV2_BayerTnr_V2_CalibPara_s {
    // @desc: alias="Setting", type="struct_list", size="dynamic", ui_module="double_index_list", ro="0" 
    CalibDbV2_BayerTnr_V2_CalibPara_Setting_t *Setting;
    int Setting_len;
} CalibDbV2_BayerTnr_V2_CalibPara_t;


typedef struct CalibDbV2_BayerTnr_V2_TuningPara_Setting_ISO_s {
    // @desc: alias="iso", type="f32", range="[50, 204800]", default="50", digit="[1]", ui_module_param="index2", ro="0" 
    float iso;

    // @desc: alias="thumbds", type="f32", size="[1,1]", range="[0, 8]", default="8", digit="[2]", hide="0", ro="0" 
    float thumbds;

    // @desc: type="bool", alias="lo_enable", default="1", hide="0", ro="0" 
    float lo_enable;

    // @desc: type="bool", alias="hi_enable", default="1", hide="0", ro="0" 
    float hi_enable;

    // @desc: type="bool", alias="lo_med_en", default="1", hide="0", ro="0" 
    float lo_med_en;
    // @desc: type="bool", alias="lo_gsbay_en", default="1", hide="0", ro="0" 
    float lo_gsbay_en;
    // @desc: type="bool", alias="lo_gslum_en", default="1", hide="0", ro="0" 
    float lo_gslum_en;
    // @desc: type="bool", alias="hi_med_en", default="1", hide="0", ro="0" 
    float hi_med_en;
    // @desc: type="bool", alias="hi_gslum_en", default="1", hide="0", ro="0" 
    float hi_gslum_en;

 // @desc: alias="hi_wgt_comp", type="f32", size="[1,1]", range="[0, 1]", default="0.16", digit="[2]", hide="0", ro="0" 
    float hi_wgt_comp;

    // @desc: alias="clipwgt", type="f32", size="[1,1]", range="[0, 1]", default="0.03215", digit="[5]", hide="0", ro="0" 
    float clipwgt;

    // @desc: type="bool", alias="global_pk_en", default="1", hide="0", ro="0" 
    float global_pk_en;
    // @desc: alias="global_pksq", type="f32", size="[1,1]", range="[0, 268435455]", default="1024", digit="[0]", hide="0", ro="0" 
    float global_pksq;

 // @desc: alias="hidif_th", type="f32", size="[1,1]", range="[0, 65535]", default="32767", digit="[0]", hide="0", ro="0" 
 float hidif_th;


    // @desc: alias="lo_filter_strength", type="f32", size="[1,1]", range="[0, 16]", default="1.0", digit="[2]", hide="0", ro="0" 
    float lo_filter_strength;

    // @desc: alias="hi_filter_strength", type="f32", size="[1,1]", range="[0, 16]", default="1.0", digit="[2]", hide="0", ro="0" 
    float hi_filter_strength;



    // @desc: alias="soft_threshold_ratio", type="f32", size="[1,1]", range="[0, 1.0]", default="0.0", digit="[2]", hide="0", ro="0" 
    float soft_threshold_ratio;


} CalibDbV2_BayerTnr_V2_TuningPara_Setting_ISO_t;

typedef struct CalibDbV2_BayerTnr_V2_TuningPara_Setting_s {
    // @desc: alias="SNR_Mode", type="string", size="[1, 1]", range="[0, 64]", default="LSNR", dynamic="0", ui_module_param="index1", ro="0" 
    char *SNR_Mode;
    // @desc: alias="Sensor_Mode", type="string", size="[1, 1]", range="[0, 64]", default="lcg", dynamic="0", hide="0", ro="0" 
    char *Sensor_Mode;
    // @desc: alias="Tuning_ISO", type="struct_list", size="dynamic", ui_module="double_index_list", ro="0" 
    CalibDbV2_BayerTnr_V2_TuningPara_Setting_ISO_t *Tuning_ISO;
    int Tuning_ISO_len;
} CalibDbV2_BayerTnr_V2_TuningPara_Setting_t;

typedef struct CalibDbV2_BayerTnr_V2_TuningPara_s {
    // @desc: type="bool", alias="enable", default="1", hide="0", ro="0" 
    
   _Bool 
        enable;
    // @desc: alias="Setting", type="struct_list", size="dynamic", ui_module="double_index_list", ro="0" 
    CalibDbV2_BayerTnr_V2_TuningPara_Setting_t *Setting;
    int Setting_len;
} CalibDbV2_BayerTnr_V2_TuningPara_t;


typedef struct CalibDbV2_BayerTnr_V2_s {
    // @desc: alias="Version", type="string", size="[1, 1]", range="[0, 64]", default="V2", dynamic="0", hide="0", ro="0" 
    char *Version;
    // @desc: alias="CalibPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_BayerTnr_V2_CalibPara_t CalibPara;
    // @desc: alias="Bayernr3D", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_BayerTnr_V2_TuningPara_t TuningPara;
} CalibDbV2_BayerTnr_V2_t;


// clang-format off
typedef struct CalibDbV2_Cac_SettingByIso_s {
    // @desc: alias="iso", type="u32", size="[1,1]", range="[0, 4294967295]", default="0", digit="[0]", hide="0", ro="0" 
    uint32_t iso;
    // @desc: alias="bypass", type="u8", size="[1,1]", range="[0, 1]", default="0", digit="[0]", hide="0", ro="0" 
    uint8_t bypass;
    // @desc: alias="strength_table", type="f32", size="[0, 22]", range="[0, 1]", default="1.0", digit="[1]", dynamic="0", hide="0", ro="0" 
    float strength_table[22];
} CalibDbV2_Cac_SettingByIso_t;

typedef struct CalibDbV2_Cac_TuningPara_s {
    // @desc: alias="SettingByIso", type="struct_list", size="dynamic", ui_module="double_index_list", ro="0" 
    CalibDbV2_Cac_SettingByIso_t* SettingByIso;
    int SettingByIso_len;
} CalibDbV2_Cac_TuningPara_t;

typedef struct CalibDbV2_Cac_SettingPara_s {
    // @desc: alias="enable", type="u8", size="[1,1]", range="[0, 1]", default="0", digit="[0]", hide="0", ro="0" 
    uint8_t enable;
    // @desc: alias="psf_path", type="string", size="[1, 1]", range="[0, 255]", default="/etc/iqfiles/cac", dynamic="0", hide="0", ro="0" 
    char psf_path[255];
    // @desc: alias="psf_shift_bits", type="u8", size="[1,1]", range="[0, 10]", default="2", digit="[0]", hide="0", ro="0" 
    uint8_t psf_shift_bits;
    // @desc: alias="center_en", type="u8", size="[1,1]", range="[0, 1]", default="0", digit="[0]", hide="0", ro="0" 
    uint8_t center_en;
    // @desc: alias="center_x", type="u16", size="[1,1]", range="[0, 65535]", default="0", digit="[0]", hide="0", ro="0" 
    uint16_t center_x;
    // @desc: alias="center_y", type="u16", size="[1,1]", range="[0, 65535]", default="0", digit="[0]", hide="0", ro="0" 
    uint16_t center_y;
} CalibDbV2_Cac_SettingPara_t;

typedef struct CalibDbV2_Cac_s {
    // @desc: alias="SettingPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Cac_SettingPara_t SettingPara;
    // @desc: alias="TuningPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Cac_TuningPara_t TuningPara;
} CalibDbV2_Cac_t;
// clang-format on
/*

 * ccm_head.h

 *

 *  Copyright (c) 2021 Rockchip Corporation

 *

 * Licensed under the Apache License, Version 2.0 (the "License");

 * you may not use this file except in compliance with the License.

 * You may obtain a copy of the License at

 *

 *      http://www.apache.org/licenses/LICENSE-2.0

 *

 * Unless required by applicable law or agreed to in writing, software

 * distributed under the License is distributed on an "AS IS" BASIS,

 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

 * See the License for the specific language governing permissions and

 * limitations under the License.

 *

 */
/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


/*****************************************************************************/
/**

 * @brief   Global ACCM calibration structure of isp2.0

 */
/*****************************************************************************/

typedef struct CalibDbV2_Ccm_Gain_Sat_Curve_s {
    // @desc: alias="gains", type="f32", size="[1, 4]", range="[0, 256]", default="[4 8 16 32]", digit="[0]", dynamic="0", hide="0", ro="0" 
    float gains[4];
    // @desc: alias="sat", type="f32", size="[1, 4]", range="[0, 100]", default="[100 100 90 50]", digit="[1]", dynamic="0", hide="0", ro="0" 
    float sat[4];
}CalibDbV2_Ccm_Gain_Sat_Curve_t;

typedef struct CalibDbV2_Ccm_Gain_Scale_Curve_s {
    // @desc: alias="gain", type="f32", size="[1, 9]", range="[0, 256]", default="[1 2 4 8 16 32 64 128 256]", digit="[0]", dynamic="0", hide="0", ro="0" 
    float gain[( 9 )];
    // @desc: alias="scale", type="f32", size="[1, 9]", range="[0, 1]", default="[1.00 0.80 0.80 0.90 1.00 1.00 1.00 1.00 1.00]", digit="[2]", dynamic="0", hide="0", ro="0" 
    float scale[( 9 )];
} CalibDbV2_Ccm_Gain_Scale_Curve_t;

typedef struct CalibDbV2_Ccm_Ccm_Matrix_Para_s
{
    // @desc: alias="name", type="string", size="[1, 1]", range="[0, 25]", default="A_100", dynamic="0", hide="0", ro="0" 
    char* name;
    // @desc: alias="illumination", type="string", size="[1, 1]", range="[0, 20]", default="A", dynamic="0", hide="0", ro="0" 
    char* illumination;
    // @desc: alias="saturation", type="f32", size="[1,1]", range="[0.0, 100.0]", default="100.0", digit="[1]", hide="0", ro="0" 
    float saturation;
    // @desc: alias="ccMatrix", type="f32", size="[3, 3]", range="[-8, 7.992]", default="[1.0000 0.0000 0.0000 0.0000 1.0000 0.0000 0.0000 0.0000 1.0000]", digit="[4]", dynamic="0", hide="0", ro="0" 
    float ccMatrix[9];
    // @desc: alias="ccOffsets", type="f32", size="[1, 3]", range="[-4095, 4095]", default="[0.0 0.0 0.0]", digit="[1]", dynamic="0", hide="0", ro="0" 
    float ccOffsets[3];
}CalibDbV2_Ccm_Ccm_Matrix_Para_t;

typedef struct CalibDbV2_Ccm_Accm_Cof_Para_s {
    // @desc: alias="name", type="string", size="[1, 1]", range="[0, 20]", default="A", dynamic="0", hide="0", ro="0" 
    char * name;
    // @desc: alias="awbGain", type="f32", size="[1, 2]", range="[0, 5]", default="[1.0000 1.0000]", digit="[4]", dynamic="0", hide="0", ro="0" 
    float awbGain[2];
    // @desc: alias="minDist", type="f32", size="[1,1]", range="[0.0, 4]", default="0", digit="[4]", hide="0", ro="0" 
    float minDist;
    // @desc: alias="matrixUsed", type="string", size="[1, 2]", range="[0, 25]", default="A_100", dynamic="1", hide="0", ro="0" 
    char** matrixUsed;
    int matrixUsed_len;
    // @desc: alias="gain sat curve", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    CalibDbV2_Ccm_Gain_Sat_Curve_t gain_sat_curve;
} CalibDbV2_Ccm_Accm_Cof_Para_t;

typedef struct CalibDbV2_Ccm_Luma_Ccm_Para_s {
    // @desc: alias="RGB2Y para", type="f32", size="[1, 3]", range="[0, 100]", default="[38 75 15]", digit="[0]", dynamic="0", hide="1", ro="0" 
    float rgb2y_para[3];
    // @desc: alias="bound pos bit", type="f32", size="[1,1]", range="[0, 10]", default="8", digit="[0]", hide="0", ro="0" 
    float low_bound_pos_bit;// low & high y alpha adjust
    // @desc: alias="y alpha curve", type="f32", size="[1, 17]", range="[0, 1024]", default="[0 64 128 192 256 320 384 448 512 576 640 704 768 832 896 960 1024]", digit="[0]", dynamic="0", hide="0", ro="0" 
    float y_alpha_curve[17];
    // @desc: alias="gain alphaScale curve", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    CalibDbV2_Ccm_Gain_Scale_Curve_t gain_alphaScale_curve;
} CalibDbV2_Ccm_Luma_Ccm_Para_t;

typedef struct CalibDbV2_Ccm_illu_estim_Para_s {
     // @desc: type="bool", alias="interp enable", default="0", hide="0", ro="0" 
    
   _Bool 
        interp_enable;
    // @desc: alias="default illu", type="string", size="[1, 1]", range="[0, 20]", default="D65", dynamic="0", hide="0", ro="0" 
    char * default_illu;
    // @desc: alias="weightRB", type="f32", size="[1, 2]", range="[0, 3]", default="[1 1]", digit="[4]", dynamic="0", hide="0", ro="0" 
    float weightRB[2];
    // @desc: alias="prob limit", type="f32", size="[1,1]", range="[0.0, 1]", default="0.2", digit="[6]", hide="0", ro="0" 
    float prob_limit;
    // @desc: alias="frame num", type="u8", size="[1,1]", range="[1, 128]", default="8", digit="[0]", hide="0", ro="0" 
    int frame_no;
} CalibDbV2_Ccm_illu_estim_Para_t;

typedef struct CalibDbV2_Ccm_Tuning_Para_s {
    // @desc: type="bool", alias="damp enable", default="0", hide="0", ro="0" 
    
   _Bool 
        damp_enable;
    // @desc: alias="illuminant estimation", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Ccm_illu_estim_Para_t illu_estim;
    // @desc: alias="aCcmCof", type="struct_list", size="dynamic", ui_module="normal_ui_style", ro="0" 
    CalibDbV2_Ccm_Accm_Cof_Para_t* aCcmCof;
    int aCcmCof_len;
    // @desc: alias="matrixAll", type="struct_list", size="dynamic", ui_module="normal_ui_style", ro="0" 
    CalibDbV2_Ccm_Ccm_Matrix_Para_t* matrixAll;
    int matrixAll_len;
} CalibDbV2_Ccm_Tuning_Para_t;

typedef struct CalibDbV2_Ccm_Manual_Para_s {
    // @desc: alias="ccMatrix", type="f32", size="[3, 3]", range="[-8, 7.992]", default="[1.0000 0.0000 0.0000 0.0000 1.0000 0.0000 0.0000 0.0000 1.0000]", digit="[4]", dynamic="0", hide="0", ro="0" 
    float ccMatrix[9];
    // @desc: alias="ccOffsets", type="f32", size="[1, 3]", range="[-4095, 4095]", default="[0.0 0.0 0.0]", digit="[1]", dynamic="0", hide="0", ro="0" 
    float ccOffsets[3];
} CalibDbV2_Ccm_Manual_Para_t;

typedef enum CalibDbV2_Ccm_Op_Mode_t {
    CALIB_CCM_MODE_MANUAL = 1, /**< run manual lens shading correction */
    CALIB_CCM_MODE_AUTO = 2, /**< run auto lens shading correction */
} CalibDbV2_Ccm_Op_Mode_t;

typedef struct CalibDbV2_Ccm_Control_Para_t {
  // @desc: type="bool", alias="enable", default="0", hide="0", ro="0" 
  
 _Bool 
      enable;
  // @desc: type="enum", alias="mode", enum_def="CalibDbV2_Ccm_Op_Mode_t", default="CALIB_CCM_MODE_AUTO", ro="0" ;
  CalibDbV2_Ccm_Op_Mode_t mode;
   // @desc: alias="wbgain tolerance", type="f32", size="[1,1]", range="[0.0, 1]", default="0.1", digit="[4]", hide="0", ro="0" 
  float wbgain_tolerance;
   // @desc: alias="gain tolerance", type="f32", size="[1,1]", range="[0.0, 1]", default="0.2", digit="[4]", hide="0", ro="0" 
  float gain_tolerance;
} CalibDbV2_Ccm_Control_Para_t;

typedef struct CalibDbV2_Ccm_Para_V2_s {
    // @desc: alias="control", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Ccm_Control_Para_t control;
    // @desc: alias="lumaCCM", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Ccm_Luma_Ccm_Para_t lumaCCM;
    // @desc: alias="manualCCM", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Ccm_Manual_Para_t manualPara;
    // @desc: alias="autoCCM", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Ccm_Tuning_Para_t TuningPara;
} CalibDbV2_Ccm_Para_V2_t;



/*
 * uvnr_head_v1.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */



///////////////////////////uvnr//////////////////////////////////////
typedef struct CalibDbV2_CNRV2_TuningPara_Setting_ISO_s {
    // @desc: alias="iso", type="f32", range="[50, 204800]", default="50", digit="[1]", ui_module_param="index2", ro="0" 
    float iso;

    // @desc: type="bool", alias="hf_bypass", default="0", hide="0", ro="0" 
    float hf_bypass;
    // @desc: type="bool", alias="lf_bypass", default="0", hide="0", ro="0" 
    float lf_bypass;

    // @desc: alias="global_gain", type="f32", size="[1,1]", range="[0, 64.0]", default="1.0", digit="[2]", hide="0", ro="0" 
    float global_gain;
    // @desc: alias="global_gain_alpha", type="f32", size="[1,1]", range="[0, 1.0]", default="0.0", digit="[2]", hide="0", ro="0" 
    float global_gain_alpha;
    // @desc: alias="local_gain_scale", type="f32", size="[1,1]", range="[0, 128.0]", default="1.0", digit="[2]", hide="0", ro="0" 
    float local_gain_scale;

    // @desc: alias="gain_adj_strength_ratio", type="f32", size="[1, 13]", range="[0, 255]", default="1.0", digit="[2]", dynamic="0", hide="0", ro="0" 
    float gain_adj_strength_ratio[13];

    // @desc: alias="color_sat_adj", type="f32", size="[1,1]", range="[1, 255.0]", default="40.0", digit="[2]", hide="0", ro="0" 
    float color_sat_adj;
    // @desc: alias="color_sat_adj_alpha", type="f32", size="[1,1]", range="[0.0, 1.0]", default="0.8", digit="[2]", hide="0", ro="0" 
    float color_sat_adj_alpha;

    // @desc: alias="hf_spikes_reducion_strength", type="f32", size="[1,1]", range="[0.0, 1.0]", default="0.5", digit="[2]", hide="0", ro="0" 
    float hf_spikes_reducion_strength;
    // @desc: alias="hf_denoise_strength", type="f32", size="[1,1]", range="[1, 1023.0]", default="10", digit="[2]", hide="0", ro="0" 
    float hf_denoise_strength;
    // @desc: alias="hf_color_sat", type="f32", size="[1,1]", range="[0.0, 8.0]", default="1.5", digit="[2]", hide="0", ro="0" 
    float hf_color_sat;
    // @desc: alias="hf_denoise_alpha", type="f32", size="[1,1]", range="[0.0, 1.0]", default="0.0", digit="[2]", hide="0", ro="0" 
    float hf_denoise_alpha;
    // @desc: alias="hf_bf_wgt_clip", type="u32", size="[1,1]", range="[0, 255]", default="0", digit="[0]", hide="0", ro="0" 
    int hf_bf_wgt_clip;

    // @desc: alias="thumb_spikes_reducion_strength", type="f32", size="[1,1]", range="[0.0, 1.0]", default="0.2", digit="[2]", hide="0", ro="0" 
    float thumb_spikes_reducion_strength;
    // @desc: alias="thumb_denoise_strength", type="f32", size="[1,1]", range="[1, 1023]", default="4.0", digit="[2]", hide="0", ro="0" 
    float thumb_denoise_strength;
    // @desc: alias="thumb_color_sat", type="f32", size="[1,1]", range="[0.0, 8.0]", default="4.0", digit="[2]", hide="0", ro="0" 
    float thumb_color_sat;


    // @desc: alias="lf_denoise_strength", type="f32", size="[1,1]", range="[1, 1023.0]", default="4.0", digit="[2]", hide="0", ro="0" 
    float lf_denoise_strength;
    // @desc: alias="lf_color_sat", type="f32", size="[1,1]", range="[0.0, 8.0]", default="2.0", digit="[2]", hide="0", ro="0" 
    float lf_color_sat;
    // @desc: alias="lf_denoise_alpha", type="f32", size="[1,1]", range="[0.0, 1.0]", default="1.0", digit="[2]", hide="0", ro="0" 
    float lf_denoise_alpha;

} CalibDbV2_CNRV2_TuningPara_Setting_ISO_t;

typedef struct CalibDbV2_CNRV2_TuningPara_Setting_s {
    // @desc: alias="SNR_Mode", type="string", size="[1, 1]", range="[0, 64]", default="LSNR", dynamic="0", ui_module_param="index1", ro="0" 
    char *SNR_Mode;
    // @desc: alias="Sensor_Mode", type="string", size="[1, 1]", range="[0, 64]", default="lcg", dynamic="0", hide="0", ro="0" 
    char *Sensor_Mode;
    // @desc: alias="Tuning_ISO", type="struct_list", size="dynamic", ui_module="double_index_list", ro="0" 
    CalibDbV2_CNRV2_TuningPara_Setting_ISO_t *Tuning_ISO;
    int Tuning_ISO_len;

} CalibDbV2_CNRV2_TuningPara_Setting_t;

typedef struct CalibDbV2_CNRV2_TuningPara_Kernel_s {
    // @desc: alias="kernel_5x5", type="f32", size="[1, 5]", range="[0, 1]", default="[1.0000 0.8825 0.7788 0.6065 0.3679]", digit="[6]", dynamic="0", hide="0", ro="0" 
    float kernel_5x5[5];
} CalibDbV2_CNRV2_TuningPara_Kernel_t;


typedef struct CalibDbV2_CNRV2_TuningPara_s {
    // @desc: type="bool", alias="enable", default="1", hide="0", ro="0" 
    int enable;
    // @desc: alias="Kernel_Coeff", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_CNRV2_TuningPara_Kernel_t Kernel_Coeff;
    // @desc: alias="Setting", type="struct_list", size="dynamic", ui_module="double_index_list", ro="0" 
    CalibDbV2_CNRV2_TuningPara_Setting_t *Setting;
    int Setting_len;
} CalibDbV2_CNRV2_TuningPara_t;


typedef struct CalibDbV2_CNRV2_s {
    // @desc: alias="Version", type="string", size="[1, 1]", range="[0, 64]", default="V1", dynamic="0", hide="0", ro="0" 
    char *Version;
    // @desc: alias="TuningPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_CNRV2_TuningPara_t TuningPara;
} CalibDbV2_CNRV2_t;


/*
 * cproc_head.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */



// #define M4_BOOL_DESC(ALIAS, DEFAULT, HIDE)

// #define M4_ARRAY_DESC(ALIAS, TYPE, SIZE, RANGE, DEFAULT,DIGIT,DYNAMIC, HIDE)

// #define M4_NUMBER_DESC(ALIAS, TYPE, RANGE, DEFAULT,DIGIT, HIDE)

typedef struct __cproc_param {
    // @desc: type="bool", alias="enable", default="1", hide="0", ro="0" 
    
   _Bool 
        enable;
    // @desc: alias="brightness", type="u8", size="[1,1]", range="[0, 255]", default="128", digit="[0]", hide="0", ro="0" 
    unsigned char brightness;
    // @desc: alias="contrast", type="u8", size="[1,1]", range="[0, 255]", default="128", digit="[0]", hide="0", ro="0" 
    unsigned char contrast;
    // @desc: alias="saturation", type="u8", size="[1,1]", range="[0, 255]", default="128", digit="[0]", hide="0", ro="0" 
    unsigned char saturation;
    // @desc: alias="hue", type="u8", size="[1,1]", range="[0, 255]", default="128", digit="[0]", hide="0", ro="0" 
    unsigned char hue;
} Cproc_Param_t;

typedef struct __cproc {
    // @desc: alias="CprocTuningPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    Cproc_Param_t param;
} CalibDbV2_Cproc_t;


/*
 * cpsl_head.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */



typedef enum Cpsl_LightSource_e {
  INVALID = -1,
  LED = 1,
  IR = 2,
  MIX = 3, /*< led and ir mixture */
  MAX
} Cpsl_LightSource_t;

typedef struct CalibDbV2_Cpsl_Param_s {
  // @desc: type="bool", alias="enable", default="0", hide="0", ro="0" 
  
 _Bool 
      enable;
  // @desc: type="enum", alias="mode", enum_def="RKAiqOPMode_t", default="RK_AIQ_OP_MODE_AUTO", ro="0" 
  RKAiqOPMode_t mode;
  // @desc: type="bool", alias="force_gray", default="0", hide="0", ro="0" 
  
 _Bool 
      force_gray;
  // @desc: type="enum", alias="light_src", enum_def="rk_aiq_cpsls_t", default="LED", ro="0" 
  Cpsl_LightSource_t light_src;
  // @desc: alias="auto_adjust_sens", type="f32", size="[1,1]", range="[0.0, 100.0]", default="50.0", digit="[0]", hide="0", ro="0" 
  float auto_adjust_sens;
  // @desc: alias="auto_on2off_th", type="u32", size="[1,1]", range="[0, 65535]", default="3000", digit="0", hide="0", ro="0" 
  uint32_t auto_on2off_th;
  // @desc: alias="auto_off2on_th", type="u32", size="[1,1]", range="[0, 65535]", default="100", digit="0", hide="0", ro="0" 
  uint32_t auto_off2on_th;
  // @desc: alias="auto_sw_interval", type="u32", size="[1,1]", range="[0, 255]", default="60", digit="0", hide="0", ro="0" 
  uint32_t auto_sw_interval;
  // @desc: type="bool", alias="manual_on", default="0", hide="0", ro="0" 
  
 _Bool 
      manual_on;
  // @desc: alias="manual_strength", type="f32", size="[1,1]", range="[0.0, 100.0]", default="100.0", digit="[2]", hide="0", ro="0" 
  float manual_strength;

} CalibDbV2_Cpsl_Param_t;

typedef struct CalibDbV2_Cpsl_s {
    // @desc: alias="param", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Cpsl_Param_t param;
} CalibDbV2_Cpsl_t;


/*
 * debayer_head.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */



typedef struct __debayer_array {
    // @desc: alias="debayer_filter1", type="u32", size="[1, 9]", range="[08, 65536]", default="[50 100 200 400 800 1600 3200 6400 12800]", digit="[0]", dynamic="0", hide="0", ro="0" 
    int ISO[9];
    // @desc: alias="sharp_strength", type="u8", size="[1, 9]", range="[0, 255]", default="[4 4 4 4 4 4 4 4 4]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char sharp_strength[9];
    // @desc: alias="debayer_hf_offset", type="u16", size="[1, 9]", range="[0, 255]", default="[1 1 1 1 1 1 1 1 1]", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned short debayer_hf_offset[9];
}Debayer_Array_t;

typedef struct __Debayer_Param {
    // @desc: type="bool", alias="debayer_en", default="1", hide="0", ro="1" 
    
   _Bool 
        debayer_en;
    // @desc: alias="debayer_filter1", type="s8", size="[1, 5]", range="[-128, 128]", default="[2 -6 0 6 -2]", digit="[0]", dynamic="0", hide="0", ro="0" 
    int debayer_filter1[5];
    // @desc: alias="debayer_filter2", type="s8", size="[1, 5]", range="[-128, 128]", default="[2 -4 4 -4 2]", digit="[0]", dynamic="0", hide="0", ro="0" 
    int debayer_filter2[5];
    // @desc: alias="debayer_gain_offset", type="u8", size="[1,1]", range="[0, 128]", default="4", digit="[0]", hide="0", ro="0" 
    unsigned char debayer_gain_offset;
    // @desc: alias="debayer_offset", type="u8", size="[1,1]", range="[0, 128]", default="1", digit="[0]", hide="0", ro="0" 
    unsigned char debayer_offset;
    // @desc: type="bool", alias="debayer_clip_en", default="1", hide="0", ro="0" 
    
   _Bool 
        debayer_clip_en;
    // @desc: type="bool", alias="debayer_filter_g_en", default="1", hide="0", ro="0" 
    
   _Bool 
        debayer_filter_g_en;
    // @desc: type="bool", alias="debayer_filter_c_en", default="1", hide="0", ro="0" 
    
   _Bool 
        debayer_filter_c_en;
    // @desc: alias="debayer_thed0", type="u8", size="[1,1]", range="[0, 128]", default="3", digit="[0]", hide="0", ro="0" 
    unsigned char debayer_thed0;
    // @desc: alias="debayer_thed1", type="u8", size="[1,1]", range="[0, 128]", default="6", digit="[0]", hide="0", ro="0" 
    unsigned char debayer_thed1;
    // @desc: alias="debayer_dist_scale", type="u8", size="[1,1]", range="[0, 128]", default="8", digit="[0]", hide="0", ro="0" 
    unsigned char debayer_dist_scale;
    // @desc: alias="debayer_cnr_strength", type="u8", size="[1,1]", range="[0, 128]", default="5", digit="[0]", hide="0", ro="0" 
    unsigned char debayer_cnr_strength;
    // @desc: alias="debayer_shift_num", type="u8", size="[1,1]", range="[0, 128]", default="2", digit="[0]", hide="0", ro="0" 
    unsigned char debayer_shift_num;
    // @desc: alias="ISO_Params", type="struct", ui_module="array_table_ui", index="default", hide="0", ro="0" 
    Debayer_Array_t array;
}Debayer_Param_t;

typedef struct __debayer {
    // @desc: alias="DebayerTuningPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    Debayer_Param_t param;
} CalibDbV2_Debayer_t;


/*
 * fec_head.h
 *
 *  Copyright (c) 2021 Rockchip Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */



typedef struct CalibDbV2_Fec_Param_s {
    unsigned char fec_en;
    char meshfile[256];
    int correct_level;
    double light_center[2]; // light center
    double coefficient[4]; // the distortion coefficient of the fisheye lens
} CalibDbV2_Fec_Param_t;

typedef struct CalibDbV2_FEC_s {
    // @desc: alias="param", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Fec_Param_t param;
} CalibDbV2_FEC_t;


/*
 * ldch_head.h
 *
 *  Copyright (c) 2021 Rockchip Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */



typedef struct CalibDbV2_Ldch_Param_s {
 // @desc: type="bool", alias="ldch_en", default="0", hide="0", ro="0" ;
    unsigned char ldch_en;
 // @desc: alias="meshfile", type="string", size="[1, 1]", range="[0, 256]", default="default_meshfile", dynamic="0", hide="0", ro="0" 
    char meshfile[256];
 // @desc: alias="correct_level", type="u32", size="[1,1]", range="[0, 255]", default="255", digit="[0]", hide="0", ro="0" 
    int correct_level;
 // @desc: alias="correct_level_max", type="u32", size="[1,1]", range="[0, 255]", default="255", digit="[0]", hide="0", ro="0" 
    int correct_level_max;
 // @desc: alias="light_center", type="f64", size="[1, 2]", range="[-10000000000000000, 10000000000000000]", default="0", digit="[8]", dynamic="0", hide="0", ro="0" 
    double light_center[2]; // light center
 // @desc: alias="coefficient", type="f64", size="[1, 4]", range="[-10000000000000000, 10000000000000000]", default="0", digit="[8]", dynamic="0", hide="0", ro="0" 
    double coefficient[4]; // the distortion coefficient of the fisheye lens
} CalibDbV2_Ldch_Param_t;

typedef struct CalibDbV2_LDCH_s {
    // @desc: alias="param", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Ldch_Param_t param;
} CalibDbV2_LDCH_t;


/*

 * lut3d_head.h

 *

 *  Copyright (c) 2021 Rockchip Corporation

 *

 * Licensed under the Apache License, Version 2.0 (the "License");

 * you may not use this file except in compliance with the License.

 * You may obtain a copy of the License at

 *

 *      http://www.apache.org/licenses/LICENSE-2.0

 *

 * Unless required by applicable law or agreed to in writing, software

 * distributed under the License is distributed on an "AS IS" BASIS,

 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

 * See the License for the specific language governing permissions and

 * limitations under the License.

 *

 */
/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */



/*****************************************************************************/
/**

 * @brief   Global 3DLUT calibration structure of isp2.0

 */
/*****************************************************************************/
typedef struct CalibDbV2_Lut3D_Table_Para_s {
    // @desc: alias="Lut R", type="u16", size="[81, 9]", range="[0, 4096]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned short look_up_table_r[729];
    // @desc: alias="Lut G", type="u16", size="[81, 9]", range="[0, 4096]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned short look_up_table_g[729];
    // @desc: alias="Lut B", type="u16", size="[81, 9]", range="[0, 4096]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned short look_up_table_b[729];
}CalibDbV2_Lut3D_Table_Para_t;

typedef struct CalibDbV2_Lut3D_Gain_Alpha_Curve_s {
    // @desc: alias="gain", type="f32", size="[1, 9]", range="[0, 256]", default="[1 2 4 8 16 32 64 128 256]", digit="[0]", dynamic="0", hide="0", ro="0" 
    float gain[9];
    // @desc: alias="Alpha", type="f32", size="[1, 9]", range="[0, 1]", default="1.00", digit="[2]", dynamic="0", hide="0", ro="0" 
    float alpha[9];
} CalibDbV2_Lut3D_Gain_Alpha_Curve_t;

typedef struct CalibDbV2_Lut3D_LutPara_s {
    //  @desc: alias="name", type="string", size="[1, 1]", range="[0, 25]", default="Normal", dynamic="0", hide="0", ro="0" 
    char *name;
     // @desc: alias="awbGain", type="f32", size="[1, 2]", range="[0, 5]", default="[1.0000 1.0000]", digit="[4]", dynamic="0", hide="0", ro="0" 
    float awbGain[2];
    // @desc: alias="gain-alpha curve", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    CalibDbV2_Lut3D_Gain_Alpha_Curve_t gain_alpha;
    // @desc: alias="Table", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Lut3D_Table_Para_t Table;
}CalibDbV2_Lut3D_LutPara_t;

typedef struct CalibDbV2_Lut3D_Auto_Para_s {
    // @desc: type="bool", alias="damp enable", default="0", hide="0", ro="0" 
    
   _Bool 
        damp_en;
    // @desc: alias="lutAll", type="struct_list", size="dynamic", ui_module="normal_ui_style", ro="0" 
    CalibDbV2_Lut3D_LutPara_t* lutAll;
    int lutAll_len;
}CalibDbV2_Lut3D_Auto_Para_t;

typedef struct CalibDbV2_Lut3D_Manual_Para_s {
    // @desc: alias="Table", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Lut3D_Table_Para_t Table;
}CalibDbV2_Lut3D_Manual_Para_t;

typedef enum CalibDbV2_Lut3D_Op_Mode_s {
    CALIB_Lut3D_MODE_MANUAL = 1, /**< run manual 3dlut */
    CALIB_Lut3D_MODE_AUTO = 2, /**< run auto 3dlut */
} CalibDbV2_Lut3D_Op_Mode_t;

typedef struct CalibDbV2_Lut3D_Common_Para_s {
    // @desc: type="bool", alias="enable", default="0", hide="0", ro="0" 
    
   _Bool 
        enable;
    // @desc: type="enum", alias="mode", enum_def="CalibDbV2_Lut3D_Op_Mode_t", default="CALIB_Lut3D_MODE_AUTO", ro="0" ;
    CalibDbV2_Lut3D_Op_Mode_t mode;
   // @desc: alias="gain tolerance", type="f32", size="[1,1]", range="[0.0, 256]", default="0.2", digit="[4]", hide="0", ro="0" 
  float gain_tolerance;
   // @desc: alias="wbgain tolerance", type="f32", size="[1,1]", range="[0.0, 4]", default="0.5", digit="[4]", hide="0", ro="0" 
  float wbgain_tolerance;
}CalibDbV2_Lut3D_Common_Para_t;

typedef struct {
    // @desc: alias="common", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Lut3D_Common_Para_t common;
    // @desc: alias="manualLut3D", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Lut3D_Manual_Para_t MLut3D;
    // @desc: alias="autoLut3D", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Lut3D_Auto_Para_t ALut3D;
} CalibDbV2_Lut3D_Para_V2_t;


/*
 * sharp_head_v1.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */



///////////////////////////sharp//////////////////////////////////////

typedef struct CalibDbV2_SharpV4_TuningPara_Setting_ISO_Luma_s {
    // @desc: alias="luma_point", type="f32", size="[1, 8]", range="[0, 1024]", default="[0 64 128 256 384 640 896 1024]", digit="[1]", dynamic="0", hide="0", ro="0" 
    float luma_point[8];
    // @desc: alias="luma_sigma", type="f32", size="[1, 8]", range="[0, 1023]", default="[8 10 10 12 14 12 12 10]", digit="[1]", dynamic="0", hide="0", ro="0" 
    float luma_sigma[8];
    // @desc: alias="hf_clip", type="f32", size="[1, 8]", range="[0, 1023]", default="[10 20 30 56 56 56 56 30]", digit="[1]", dynamic="0", hide="0", ro="0" 
    float hf_clip[8];
    // @desc: alias="local_sharp_strength", type="f32", size="[1, 8]", range="[0, 1023]", default="[1023 1023 1023 1023 1023 1023 1023 1023]", digit="[1]", dynamic="0", hide="0", ro="0" 
    float local_sharp_strength[8];
} CalibDbV2_SharpV4_TuningPara_Setting_ISO_Luma_t;

typedef struct CalibDbV2_SharpV4_TuningPara_Setting_ISO_kernel_s {

    // @desc: alias="prefilter_coeff", type="f32", size="[1, 3]", range="[0, 1]", default="[0.2042 0.1238 0.0751]", digit="[4]", dynamic="0", hide="0", ro="0" 
    float prefilter_coeff[3];
    // @desc: alias="GaussianFilter_coeff", type="f32", size="[1, 6]", range="[0, 1]", default="[0.2042 0.1238 0.0751]", digit="[4]", dynamic="0", hide="0", ro="0" 
    float GaussianFilter_coeff[6];
    // @desc: alias="hfBilateralFilter_coeff", type="f32", size="[1, 3]", range="[0, 1]", default="[0.2042 0.1238 0.0751]", digit="[4]", dynamic="0", hide="0", ro="0" 
    float hfBilateralFilter_coeff[3];
} CalibDbV2_SharpV4_TuningPara_Setting_ISO_kernel_t;

typedef struct CalibDbV2_SharpV4_TuningPara_Setting_ISO_kernel_sigma_s {

    // @desc: alias="prefilter_sigma", type="f32", size="[1, 1]", range="[0, 100]", default="[1.0]", digit="[2]", dynamic="0", hide="0", ro="0" 
    float prefilter_sigma;
    // @desc: alias="hfBilateralFilter_sigma", type="f32", size="[1, 1]", range="[0, 100]", default="[1.0]", digit="[2]", dynamic="0", hide="0", ro="0" 
    float hfBilateralFilter_sigma;
    // @desc: alias="GaussianFilter_sigma", type="f32", size="[1, 1]", range="[0, 100]", default="[1.0]", digit="[2]", dynamic="0", hide="0", ro="0" 
    float GaussianFilter_sigma;
    // @desc: alias="GaussianFilter_radius", type="f32", size="[1, 1]", range="[1, 2]", default="[2.0]", digit="[0]", dynamic="0", hide="0", ro="0" 
    float GaussianFilter_radius;

} CalibDbV2_SharpV4_TuningPara_Setting_ISO_kernel_sigma_t;

typedef struct CalibDbV2_SharpV4_TuningPara_Setting_ISO_s {
    // @desc: alias="iso", type="f32", range="[50, 204800]", default="50", digit="[1]", ui_module_param="index2", ro="0" 
    float iso;

    // @desc: alias="pbf_gain", type="f32", size="[1,1]", range="[0.0, 2.0]", default="0.5", digit="[2]", hide="0", ro="0" 
    float pbf_gain;
    // @desc: alias="pbf_ratio", type="f32", size="[1,1]", range="[0.0, 1.0]", default="0.5", digit="[2]", hide="0", ro="0" 
    float pbf_ratio;
    // @desc: alias="pbf_add", type="f32", size="[1,1]", range="[0.0, 1023.0]", default="0.0", digit="[2]", hide="0", ro="0" 
    float pbf_add;

    // @desc: alias="gaus_ratio", type="f32", size="[1,1]", range="[0.0, 1.0]", default="0.0", digit="[2]", hide="0", ro="0" 
    float gaus_ratio;

    // @desc: alias="sharp_ratio", type="f32", size="[1,1]", range="[0.0, 32.0]", default="0.5", digit="[2]", hide="0", ro="0" 
    float sharp_ratio;


    // @desc: alias="bf_gain", type="f32", size="[1,1]", range="[0.0, 2.0]", default="0.5", digit="[2]", hide="0", ro="0" 
    float bf_gain;
    // @desc: alias="bf_ratio", type="f32", size="[1,1]", range="[0.0, 1.0]", default="0.5", digit="[2]", hide="0", ro="0" 
    float bf_ratio;
    // @desc: alias="bf_add", type="f32", size="[1,1]", range="[0.0, 1023.0]", default="0.0", digit="[2]", hide="0", ro="0" 
    float bf_add;

    // @desc: alias="luma_para", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    CalibDbV2_SharpV4_TuningPara_Setting_ISO_Luma_t luma_para;

    // @desc: alias="kernel_para", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    CalibDbV2_SharpV4_TuningPara_Setting_ISO_kernel_t kernel_para;

    // @desc: alias="kernel_sigma", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    CalibDbV2_SharpV4_TuningPara_Setting_ISO_kernel_sigma_t kernel_sigma;
} CalibDbV2_SharpV4_TuningPara_Setting_ISO_t;

typedef struct CalibDbV2_SharpV4_TuningPara_Setting_s {
    // @desc: alias="SNR_Mode", type="string", size="[1, 1]", range="[0, 64]", default="LSNR", dynamic="0", ui_module_param="index1", ro="0" 
    char *SNR_Mode;
    // @desc: alias="Sensor_Mode", type="string", size="[1, 1]", range="[0, 64]", default="lcg", dynamic="0", hide="0", ro="0" 
    char *Sensor_Mode;
    // @desc: alias="Tuning_ISO", type="struct_list", size="dynamic", ui_module="double_index_list", ro="0" 
    CalibDbV2_SharpV4_TuningPara_Setting_ISO_t *Tuning_ISO;
    int Tuning_ISO_len;
} CalibDbV2_SharpV4_TuningPara_Setting_t;

typedef struct CalibDbV2_SharpV4_TuningPara_s {
    // @desc: type="bool", alias="enable", default="1", hide="0", ro="0" 
    
   _Bool 
        enable;

    // @desc: type="bool", alias="kernel_sigma_enable", default="1", hide="0", ro="0" 
    
   _Bool 
        kernel_sigma_enable;

    // @desc: alias="Setting", type="struct_list", size="dynamic", ui_module="double_index_list", ro="0" 
    CalibDbV2_SharpV4_TuningPara_Setting_t *Setting;
    int Setting_len;

} CalibDbV2_SharpV4_TuningPara_t;

typedef struct CalibDbV2_SharpV4_s {
    // @desc: alias="Version", type="string", size="[1, 1]", range="[0, 64]", default="V3", dynamic="0", hide="0", ro="0" 
    char *Version;
    // @desc: alias="TuningPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_SharpV4_TuningPara_t TuningPara;
} CalibDbV2_SharpV4_t;


/*
 * thumbnails_head.h
 *
 *  Copyright (c) 2021 Rockchip Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */



typedef struct rkaiq_thumbnails_config_s {
    // @desc: alias="owner_cookies", type="u32", size="[1,1]", range="[0, 65535]", default="1", digit="[0]", hide="0", ro="0" 
    uint32_t owner_cookies;
    // @desc: alias="stream_type", type="u32", size="[1,1]", range="[0, 65535]", default="1", digit="[0]", hide="0", ro="0" 
    uint32_t stream_type;
    // image_source after these nodes, 1 node per bit
    // @desc: alias="after_nodes", type="u32", size="[1,1]", range="[0, 65535]", default="1", digit="[0]", hide="0", ro="0" 
    uint64_t after_nodes;
    // image_source after the node, 1 node per bit
    // @desc: alias="after_nodes", type="u32", size="[1,1]", range="[0, 65535]", default="1", digit="[0]", hide="0", ro="0" 
    uint64_t before_node;
    // fourcc code
    // @desc: alias="format", type="u8", size="[1, 4]", range="[0, 100]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    char format[4];
    // @desc: alias="width_intfactor", type="u32", size="[1,1]", range="[0, 65535]", default="1", digit="[0]", hide="0", ro="0" 
    uint32_t width_intfactor;
    // @desc: alias="height_intfactor", type="u32", size="[1,1]", range="[0, 65535]", default="1", digit="[0]", hide="0", ro="0" 
    uint32_t height_intfactor;
    // @desc: alias="buffer_count", type="s32", size="[1,1]", range="[-65535, 65535]", default="1", digit="[0]", hide="0", ro="0" 
    int32_t buffer_count;
} rkaiq_thumbnails_config_t;

typedef struct CalibDbV2_Thumbnails_Param_s {
    // pointers to thumbnail info array
    // which contains format/width/height/stride
    // @desc: alias="thumbnail_configs", type="struct_list", size="[1, 4]", ui_module="normal_ui_style", ro="0" 
    rkaiq_thumbnails_config_t* thumbnail_configs;
    // total thumbnails count
    uint32_t thumbnail_configs_len;
} CalibDbV2_Thumbnails_Param_t;

typedef struct CalibDbV2_Thumbnails_s {
 // @desc: alias="param", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Thumbnails_Param_t param;
} CalibDbV2_Thumbnails_t;


/*
 * ynr_head_v1.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */



///////////////////////////ynr v1//////////////////////////////////////

typedef struct CalibDbV2_YnrV3_CalibPara_Setting_ISO_s {
    // @desc: alias="iso", type="f32", range="[50, 204800]", default="50", digit="[1]", ui_module_param="index2", ro="0" 
    float iso;
    // @desc: alias="sigma_curve", type="f32", size="[1, 5]", range="[-65535.0, 65535]", default="0.0", digit="[6]", dynamic="0", hide="0", ro="0" 
    double sigma_curve[5];
    // @desc: alias="ynr_lci", type="f32", size="[1,1]", range="[0.0, 2.0]", default="0.5", digit="[3]", hide="0", ro="0" 
    float ynr_lci;
    // @desc: alias="ynr_hci", type="f32", size="[1,1]", range="[0.0, 2.0]", default="0.5", digit="[3]", hide="0", ro="0" 
    float ynr_hci;

} CalibDbV2_YnrV3_CalibPara_Setting_ISO_t;

typedef struct CalibDbV2_YnrV3_CalibPara_Setting_s {
    // @desc: alias="SNR_Mode", type="string", size="[1, 1]", range="[0, 64]", default="LSNR", dynamic="0", ui_module_param="index1", ro="0" 
    char *SNR_Mode;
    // @desc: alias="Sensor_Mode", type="string", size="[1, 1]", range="[0, 64]", default="lcg", dynamic="0", hide="0", ro="0" 
    char *Sensor_Mode;
    // @desc: alias="Calib_ISO", type="struct_list", size="dynamic", ui_module="double_index_list", ro="0" 
    CalibDbV2_YnrV3_CalibPara_Setting_ISO_t *Calib_ISO;
    int Calib_ISO_len;
} CalibDbV2_YnrV3_CalibPara_Setting_t;

typedef struct CalibDbV2_YnrV3_CalibPara_s {
    // @desc: alias="Setting", type="struct_list", size="dynamic", ui_module="double_index_list", ro="0" 
    CalibDbV2_YnrV3_CalibPara_Setting_t *Setting;
    int Setting_len;
} CalibDbV2_YnrV3_CalibPara_t;

typedef struct CalibDbV2_YnrV3_TuningPara_Setting_ISO_LumaParam_s {
    // @desc: alias="lo_lumaPoint", type="f32", size="[1, 6]", range="[0, 256]", default="[0 32 64 128 192 256]", digit="[0]", dynamic="0", hide="0", ro="0" 
    float lo_lumaPoint[6];
    // @desc: alias="lo_ratio", type="f32", size="[1, 6]", range="[0, 2]", default="[1 1 1 1 1 1]", digit="[2]", dynamic="0", hide="0", ro="0" 
    float lo_ratio[6];
    // @desc: alias="hi_lumaPoint", type="f32", size="[1, 6]", range="[0, 256]", default="[0 32 64 128 192 256]", digit="[0]", dynamic="0", hide="0", ro="0" 
    float hi_lumaPoint[6];
    // @desc: alias="hi_ratio", type="f32", size="[1, 6]", range="[0, 2]", default="[1 1 1 1 1 1]", digit="[2]", dynamic="0", hide="0", ro="0" 
    float hi_ratio[6];
} CalibDbV2_YnrV3_TuningPara_Setting_ISO_LumaParam_t;


typedef struct CalibDbV2_YnrV3_TuningPara_Setting_ISO_s {
    // @desc: alias="iso", type="f32", range="[50, 204800]", default="50", digit="[1]", ui_module_param="index2", ro="0" 
    float iso;

    // @desc: type="bool", alias="ynr_bft3x3_bypass", default="0", hide="0", ro="0" 
    float ynr_bft3x3_bypass;
    // @desc: type="bool", alias="ynr_lbft5x5_bypass", default="0", hide="0", ro="0" 
    float ynr_lbft5x5_bypass;
    // @desc: type="bool", alias="ynr_lgft3x3_bypass", default="0", hide="0", ro="0" 
    float ynr_lgft3x3_bypass;
    // @desc: type="bool", alias="ynr_flt1x1_bypass", default="0", hide="0", ro="0" 
    float ynr_flt1x1_bypass;
    // @desc: type="bool", alias="ynr_sft5x5_bypass", default="0", hide="0", ro="0" 
    float ynr_sft5x5_bypass;

    // @desc: alias="ynr_global_gain_alpha", type="f32", size="[1,1]", range="[0, 1.0]", default="0", digit="[2]", hide="0", ro="0" 
    float ynr_global_gain_alpha;
    // @desc: alias="ynr_global_gain", type="f32", size="[1,1]", range="[0, 64]", default="1", digit="[2]", hide="0", ro="0" 
    float ynr_global_gain;

    // @desc: alias="ynr_adjust_thresh", type="f32", size="[1,1]", range="[0, 1.0]", default="1", digit="[2]", hide="0", ro="0" 
    float ynr_adjust_thresh;
    // @desc: alias="ynr_adjust_scale", type="f32", size="[1,1]", range="[0, 16]", default="1", digit="[2]", hide="0", ro="0" 
    float ynr_adjust_scale;

    // @desc: alias="lumaPara", type="struct", ui_module="array_table_ui", index="none", hide="0", ro="0" 
    CalibDbV2_YnrV3_TuningPara_Setting_ISO_LumaParam_t lumaPara;

    // @desc: alias="low_bf1", type="f32", size="[1,1]", range="[0.1, 32]", default="0.5", digit="[2]", hide="0", ro="0" 
    float low_bf1;
    // @desc: alias="low_bf2", type="f32", size="[1,1]", range="[0.1, 32]", default="0.5", digit="[2]", hide="0", ro="0" 
    float low_bf2;

    // @desc: alias="low_thred_adj", type="f32", size="[1,1]", range="[0.0, 31.0]", default="0.25", digit="[2]", hide="0", ro="0" 
    float low_thred_adj;
    // @desc: alias="low_peak_supress", type="f32", size="[1,1]", range="[0.0, 1.0]", default="0.5", digit="[2]", hide="0", ro="0" 
    float low_peak_supress;
    // @desc: alias="low_edge_adj_thresh", type="f32", size="[1,1]", range="[0, 1023]", default="7", digit="[2]", hide="0", ro="0" 
    float low_edge_adj_thresh;
    // @desc: alias="low_lbf_weight_thresh", type="f32", size="[1,1]", range="[0.0, 1.0]", default="0.25", digit="[2]", hide="0", ro="0" 
    float low_lbf_weight_thresh;
    // @desc: alias="low_center_weight", type="f32", size="[1,1]", range="[0.0, 1.0]", default="0.5", digit="[2]", hide="0", ro="0" 
    float low_center_weight;
    // @desc: alias="low_dist_adj", type="f32", size="[1,1]", range="[0.0, 127.0]", default="8.0", digit="[2]", hide="0", ro="0" 
    float low_dist_adj;
    // @desc: alias="low_weight", type="f32", size="[1,1]", range="[0.0, 1.0]", default="0.5", digit="[2]", hide="0", ro="0" 
    float low_weight;
    // @desc: alias="low_filt1_strength", type="f32", size="[1,1]", range="[0.0, 1.0]", default="0.7", digit="[2]", hide="0", ro="0" 
    float low_filt1_strength;
    // @desc: alias="low_filt2_strength", type="f32", size="[1,1]", range="[0.0, 1.0]", default="0.85", digit="[2]", hide="0", ro="0" 
    float low_filt2_strength;
    // @desc: alias="low_bi_weight", type="f32", size="[1,1]", range="[0.0, 1.0]", default="0.2", digit="[2]", hide="0", ro="0" 
    float low_bi_weight;


    // @desc: alias="base_filter_weight1", type="f32", size="[1,1]", range="[0.0, 1.0]", default="0.28", digit="[2]", hide="0", ro="0" 
    float base_filter_weight1;
    // @desc: alias="base_filter_weight2", type="f32", size="[1,1]", range="[0.0, 1.0]", default="0.46", digit="[2]", hide="0", ro="0" 
    float base_filter_weight2;
    // @desc: alias="base_filter_weight3", type="f32", size="[1,1]", range="[0.0, 1.0]", default="0.26", digit="[2]", hide="0", ro="0" 
    float base_filter_weight3;


    // @desc: alias="high_thred_adj", type="f32", size="[1,1]", range="[0.0, 31.0]", default="0.5", digit="[2]", hide="0", ro="0" 
    float high_thred_adj;
    // @desc: alias="high_weight", type="f32", size="[1,1]", range="[0.0, 1.0]", default="0.5", digit="[2]", hide="0", ro="0" 
    float high_weight;
    // @desc: alias="hi_min_adj", type="f32", size="[1,1]", range="[0.0, 1]", default="0.9", digit="[2]", hide="0", ro="0" 
    float hi_min_adj;
    // @desc: alias="hi_edge_thed", type="f32", size="[1,1]", range="[0.0, 255.0]", default="100.0", digit="[2]", hide="0", ro="0" 
    float hi_edge_thed;
    // @desc: alias="high_direction_weight", type="f32", size="[1, 8]", range="[0, 1.0]", default="[1 1 1 1 0.5 0.5 0.5 0.5]", digit="[2]", dynamic="0", hide="0", ro="0" 
    float high_direction_weight[8];

    // @desc: alias="rnr_strength", type="f32", size="[1, 17]", range="[0, 16]", default="1.0", digit="[3]", dynamic="0", hide="0", ro="0" 
    float rnr_strength[17];

} CalibDbV2_YnrV3_TuningPara_Setting_ISO_t;


typedef struct CalibDbV2_YnrV3_TuningPara_Setting_s {
    // @desc: alias="SNR_Mode", type="string", size="[1, 1]", range="[0, 64]", default="LSNR", dynamic="0", ui_module_param="index1", ro="0" 
    char *SNR_Mode;
    // @desc: alias="Sensor_Mode", type="string", size="[1, 1]", range="[0, 64]", default="lcg", dynamic="0", hide="0", ro="0" 
    char *Sensor_Mode;
    // @desc: alias="Tuning_ISO", type="struct_list", size="dynamic", ui_module="double_index_list", ro="0" 
    CalibDbV2_YnrV3_TuningPara_Setting_ISO_t *Tuning_ISO;
    int Tuning_ISO_len;
} CalibDbV2_YnrV3_TuningPara_Setting_t;

typedef struct CalibDbV2_YnrV3_TuningPara_s {
    // @desc: type="bool", alias="enable", default="1", hide="0", ro="0" 
    
   _Bool 
        enable;
    // @desc: alias="Setting", type="struct_list", size="dynamic", ui_module="double_index_list", ro="0" 
    CalibDbV2_YnrV3_TuningPara_Setting_t *Setting;
    int Setting_len;
} CalibDbV2_YnrV3_TuningPara_t;


typedef struct CalibDbV2_YnrV3_s {
    // @desc: alias="Version", type="string", size="[1, 1]", range="[0, 64]", default="V2", dynamic="0", hide="0", ro="0" 
    char *Version;
    // @desc: alias="CalibPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_YnrV3_CalibPara_t CalibPara;
    // @desc: alias="TuningPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_YnrV3_TuningPara_t TuningPara;
} CalibDbV2_YnrV3_t;





typedef struct CalibDbV2_ColorAsGrey_Param_s {
    // @desc: type="bool", alias="enable", default="0", hide="0", ro="0" 
    
   _Bool 
        enable;
} CalibDbV2_ColorAsGrey_Param_t;

typedef struct CalibDbV2_ColorAsGrey_s {
    // @desc: alias="param", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_ColorAsGrey_Param_t param;
} CalibDbV2_ColorAsGrey_t;

typedef struct CalibDbV2_LUMA_DETECT_s {
    unsigned char luma_detect_en;
    int fixed_times;
    float mutation_threshold;
    float mutation_threshold_level2;
} CalibDbV2_LUMA_DETECT_t;

typedef struct CamCalibDbV2ContextIsp30_s {
    // @desc: alias="AEC", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Aec_ParaV2_t ae_calib;
    // @desc: alias="wb_v21", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Wb_Para_V21_t wb_v21;
    // @desc: alias="ablc_calib", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Ablc_t ablc_calib;
    // @desc: alias="ccm_calib", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Ccm_Para_V2_t ccm_calib;
    // @desc: alias="lut3d_calib", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Lut3D_Para_V2_t lut3d_calib;
    // @desc: alias="degamma", type="struct", ui_module="curve_ui_type_A", hide="0", ro="0" 
    CalibDbV2_Adegmma_t adegamma_calib;
    // @desc: alias="agic_calib_v21", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Gic_V21_t agic_calib_v21;
    // @desc: alias="debayer_calib", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Debayer_t debayer;
    // @desc: alias="Amerge_calib", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_merge_V2_t amerge_calib_V2;
    // @desc: alias="Adrc_calib", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_drc_V2_t adrc_calib_V2;
    // @desc: alias="agamma_calib", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_gamma_V30_t agamma_calib_V30;
    // @desc: alias="adehaze_calib", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_dehaze_V30_t adehaze_calib_v30;
    // @desc: alias="adpcc_calib", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Dpcc_t adpcc_calib;
    // @desc: alias="aldch", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_LDCH_t aldch;
    // @desc: alias="cpsl", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Cpsl_t cpsl;
    // @desc: alias="cproc_calib", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Cproc_t cproc;
    // @desc: alias="aie_calib", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_IE_t ie;
    // @desc: alias="colorAsGrey", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_ColorAsGrey_t colorAsGrey;
    // @desc: alias="lsc_v2", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_LSC_t lsc_v2;
    // @desc: alias="bayer2dnr_v2", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Bayer2dnr_V2_t bayer2dnr_v2;
    // @desc: alias="bayertnr_v2", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_BayerTnr_V2_t bayertnr_v2;
    // @desc: alias="ynr_v3", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_YnrV3_t ynr_v3;
    // @desc: alias="cnr_v2", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_CNRV2_t cnr_v2;
    // @desc: alias="sharp_v4", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_SharpV4_t sharp_v4;
    // @desc: alias="cac_calib", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_Cac_t cac_calib;
    // @desc: alias="af_calib", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDbV2_AFV30_t af_v30;
} CamCalibDbV2ContextIsp30_t;



/*
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




typedef enum opMode_e {
    OP_AUTO = 0,
    OP_MANUAL = 1,
    OP_SEMI_AUTO = 2,
    OP_REG_MANUAL = 3,
    OP_INVAL
} opMode_t;

/*
*****************************
* Common
*****************************
*/

typedef enum dayNightScene_e {
    DAYNIGHT_SCENE_DAY = 0,
    DAYNIGHT_SCENE_NIGHT = 1,
    DAYNIGHT_SCENE_INVAL,
} dayNightScene_t;

typedef struct paRange_s {
    float max;
    float min;
} paRange_t;

typedef enum awbRange_e {
    AWB_RANGE_0 = 0,
    AWB_RANGE_1 = 1,
    AWB_RANGE_INVAL,
} awbRange_t;

typedef enum aeMode_e {
    AE_AUTO = 0,
    AE_IRIS_PRIOR = 1,
    AE_SHUTTER_PRIOR = 2,
} aeMode_t;


/*
*****************
*   (-1000, -1000)    (1000, -1000)
*   -------------------
*   |                 |
*   |                 |
*   |       (0,0)     |
*   |                 |
*   |                 |
*   -------------------
*                     (1000, 1000)
*****************
*/
typedef struct paRect_s {
    int x;
    int y;
    unsigned int w;
    unsigned int h;
} paRect_t;

typedef enum aeMeasAreaType_e {
    AE_MEAS_AREA_AUTO = 0,
    AE_MEAS_AREA_UP,
    AE_MEAS_AREA_BOTTOM,
    AE_MEAS_AREA_LEFT,
    AE_MEAS_AREA_RIGHT,
    AE_MEAS_AREA_CENTER,
} aeMeasAreaType_t;

typedef enum expPwrLineFreq_e {
    EXP_PWR_LINE_FREQ_DIS = 0,
    EXP_PWR_LINE_FREQ_50HZ = 1,
    EXP_PWR_LINE_FREQ_60HZ = 2,
} expPwrLineFreq_t;

typedef enum antiFlickerMode_e {
    ANTIFLICKER_NORMAL_MODE = 0,
    ANTIFLICKER_AUTO_MODE = 1,
} antiFlickerMode_t;

typedef struct frameRateInfo_s {
    opMode_t mode;
    unsigned int fps; /* valid when manual mode*/
} frameRateInfo_t;
/*
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 * aec_head.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
typedef enum _RAWAE_WND_NUM {
    RAWAE_WND_1X1 = 0,
    RAWAE_WND_5X5 = 1,
    RAWAE_WND_15X15 = 2,
} RAWAE_WND_NUM;

typedef enum _RAWHIST_WND_NUM {
    RAWHIST_WND_5X5 = 0,
    RAWHIST_WND_15X15 = 2,
} RAWHISST_WND_NUM;

typedef enum _AE_MODE {
    RAWAE_MODE_S_LITE = 0,
    RAWAE_MODE_M_LITE = 1,
    RAWAE_MODE_L_LITE = 2
} AE_MODE;

typedef enum WinSplitMode_s {
    LEFT_AND_RIGHT_MODE = 0,
    LEFT_MODE,
    RIGHT_MODE,
} WinSplitMode;

/*****************************************************************************/
/**
 * @brief   ISP2.0 AEC HW-Meas Config Params
 */
/*****************************************************************************/
typedef struct window {
    uint16_t h_offs;
    uint16_t v_offs;
    uint16_t h_size;
    uint16_t v_size;
} window_t;


typedef struct rawaebig_meas_cfg {
    unsigned char rawae_sel;
    unsigned char wnd_num;
    unsigned char subwin_en[4];
    window_t win;
    window_t subwin[4];
} rawaebig_meas_cfg_t;

typedef struct rawaelite_meas_cfg {
    unsigned char rawae_sel;
    unsigned char wnd_num;
    window_t win;
} rawaelite_meas_cfg_t;

typedef struct yuvae_meas_cfg {
    unsigned char ysel;
    unsigned char wnd_num;
    unsigned char subwin_en[4];
    window_t win;
    window_t subwin[4];
} yuvae_meas_cfg_t;


typedef struct rawhistbig_cfg {
    unsigned char wnd_num;
    unsigned char data_sel;
    unsigned char waterline;
    unsigned char mode;
    unsigned char stepsize;
    unsigned char off;
    unsigned char bcc;
    unsigned char gcc;
    unsigned char rcc;
    window_t win;
    unsigned char weight[225];
} rawhistbig_cfg_t;

typedef struct rawhistlite_cfg {
    unsigned char data_sel;
    unsigned char waterline;
    unsigned char mode;
    unsigned char stepsize;
    unsigned char off;
    unsigned char bcc;
    unsigned char gcc;
    unsigned char rcc;
    window_t win;
    unsigned char weight[25];
} rawhistlite_cfg_t;

typedef struct sihst_win_cfg {
    unsigned char data_sel;
    unsigned char waterline;
    unsigned char auto_stop;
    unsigned char mode;
    unsigned char stepsize;
    window_t win;
} sihst_win_cfg_t;

typedef struct sihst_cfg {
    unsigned char wnd_num;
    sihst_win_cfg_t win_cfg[1];
    unsigned char hist_weight[225];
} sihst_cfg_t;

/*NOTE: name of rawae/rawhist channel has been renamed!
   RawAE0 = RawAE lite,  addr=0x4500  <=> RawHIST0
   RawAE1 = RawAE big2, addr=0x4600 <=> RawHIST1
   RawAE2 = RawAE big3, addr=0x4700 <=> RawHIST2
   RawAE3 = RawAE big1, addr=0x4400, extra aebig <=> RawHIST3
*/
typedef struct rk_aiq_ae_meas_params_s {
    
   _Bool 
          ae_meas_en;
    
   _Bool 
          ae_meas_update;
    rawaelite_meas_cfg_t rawae0;
    rawaebig_meas_cfg_t rawae1;
    rawaebig_meas_cfg_t rawae2;
    rawaebig_meas_cfg_t rawae3;
    yuvae_meas_cfg_t yuvae;
} rk_aiq_ae_meas_params_t;

typedef struct rk_aiq_hist_meas_params_s {
    
   _Bool 
          hist_meas_en;
    
   _Bool 
          hist_meas_update;
    unsigned char ae_swap; // used to choose LITE & BIG
    unsigned char ae_sel; // used for rawae3 & rawhist3
    rawhistlite_cfg_t rawhist0;
    rawhistbig_cfg_t rawhist1;
    rawhistbig_cfg_t rawhist2;
    rawhistbig_cfg_t rawhist3;
    sihst_cfg_t sihist;
} rk_aiq_hist_meas_params_t;
/*****************************************************************************/
/**
 * @brief   ISP2.0 AEC AEC HW-Meas Res Params
 */
/*****************************************************************************/

typedef struct rawhist_stat {
    unsigned int bins[256];
} rawhist_stat_t;

typedef struct sihist_stat_t {
    unsigned int bins[32];
} sihist_stat_t;

typedef struct rawaebig_stat {
    uint16_t channelr_xy[225];
    uint16_t channelg_xy[225];
    uint16_t channelb_xy[225];
    uint16_t channely_xy[225]; //not HW!
    uint64_t wndx_sumr[4];
    uint64_t wndx_sumg[4];
    uint64_t wndx_sumb[4];
    uint16_t wndx_channelr[4]; //not HW!
    uint16_t wndx_channelg[4]; //not HW!
    uint16_t wndx_channelb[4]; //not HW!
    uint16_t wndx_channely[4]; //not HW!
} rawaebig_stat_t;

typedef struct rawaelite_stat {
    uint16_t channelr_xy[25];
    uint16_t channelg_xy[25];
    uint16_t channelb_xy[25];
    uint16_t channely_xy[25]; //not HW!
} rawaelite_stat_t;

typedef struct yuvae_stat {
    uint64_t ro_yuvae_sumy[4];
    unsigned char mean[225];
} yuvae_stat_t;

typedef struct Aec_Stat_Res_s {
    //rawae
    rawaebig_stat_t rawae_big;
    rawaelite_stat_t rawae_lite;
    //rawhist
    rawhist_stat_t rawhist_big;
    rawhist_stat_t rawhist_lite;
} Aec_Stat_Res_t;

typedef struct RkAiqAecHwConfig_s {
    rk_aiq_ae_meas_params_t ae_meas;
    rk_aiq_hist_meas_params_t hist_meas;
    int ae_swap;
    int ae_sel;
} RkAiqAecHwConfig_t;

typedef struct RkAiqAecHwStatsRes_s {
    Aec_Stat_Res_t chn[3];
    Aec_Stat_Res_t extra;
    yuvae_stat_t yuvae;
    sihist_stat_t sihist;
} RkAiqAecHwStatsRes_t;


/*****************************************************************************/
/**
 * @brief   ISP2.0 AEC Exposure Params
 */
/*****************************************************************************/
typedef struct CISFeature_s {
    // @desc: alias="SNR", type="u8", size="[1,1]", range="[0, 1]", default="0", digit="[0]", hide="1", ro="0" 
    uint8_t SNR;
    // @desc: alias="DR", type="u8", size="[1,1]", range="[0, 1]", default="0", digit="[0]", hide="1", ro="0" 
    uint8_t DR;
    // @desc: alias="Sat", type="u8", size="[1,1]", range="[0, 1]", default="0", digit="[0]", hide="1", ro="0" 
    uint8_t Sat;
    // @desc: alias="SEN", type="u8", size="[1,1]", range="[0, 1]", default="0", digit="[0]", hide="1", ro="0" 
    uint8_t SEN;
} CISFeature_t;

typedef struct RkAiqExpRealParam_s {

    // @desc: alias="CISTime", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[6]", hide="0", ro="0" 
    float integration_time;

    // @desc: alias="CISGain", type="f32", size="[1,1]", range="[0, 4096]", default="0", digit="[3]", hide="0", ro="0" 
    float analog_gain;

    // @desc: alias="digital_gain", type="f32", size="[1,1]", range="[0, 4096]", default="0", digit="[3]", hide="1", ro="0" 
    float digital_gain;

    // @desc: alias="isp_dgain", type="f32", size="[1,1]", range="[0, 256]", default="0", digit="[3]", hide="1", ro="0" 
    float isp_dgain;

    // @desc: alias="iso", type="s32", size="[1,1]", range="[0, 524288]", default="0", digit="[0]", hide="1", ro="0" 
    int iso;

    // @desc: alias="DcgMode", type="s32", size="[1,1]", range="[-1, 1]", default="0", digit="[0]", hide="0", ro="0" 
    int dcg_mode;

    // @desc: alias="longfrm_mode", type="s32", size="[1,1]", range="[0, 1]", default="0", digit="[0]", hide="1", ro="0" 
    int longfrm_mode;
} RkAiqExpRealParam_t;

typedef struct RkAiqExpSensorParam_s {

    // @desc: alias="fine_integration_time", type="u32", size="[1,1]", range="[0, 65535]", default="0", digit="[0]", hide="1", ro="0" 
    unsigned int fine_integration_time;

    // @desc: alias="coarse_integration_time", type="u32", size="[1,1]", range="[0, 65535]", default="0", digit="[0]", hide="1", ro="0" 
    unsigned int coarse_integration_time;

    // @desc: alias="analog_gain_code_global", type="u32", size="[1,1]", range="[0, 524288]", default="0", digit="[0]", hide="1", ro="0" 
    unsigned int analog_gain_code_global;

    // @desc: alias="digital_gain_global", type="u32", size="[1,1]", range="[0, 65535]", default="0", digit="[0]", hide="1", ro="0" 
    unsigned int digital_gain_global;

    // @desc: alias="isp_digital_gain", type="u32", size="[1,1]", range="[0, 65535]", default="0", digit="[0]", hide="1", ro="0" 
    unsigned int isp_digital_gain;
} RkAiqExpSensorParam_t;


typedef struct RKAiqExpI2cParam_s {
    // @desc: type="bool", alias="bValid", default="0", hide="1", ro="0" 
    
   _Bool 
                  bValid;

    // @desc: alias="nNumRegs", type="u32", size="[1,1]", range="[0, 65535]", default="0", digit="[0]", hide="1", ro="0" 
    unsigned int nNumRegs;

    // @desc: alias="RegAddr", type="u32", size="[1, 64]", range="[0, 65535]", default="0", digit="[0]", dynamic="0", hide="1", ro="0" 
    unsigned int RegAddr[64];

    // @desc: alias="AddrByteNum", type="u32", size="[1, 64]", range="[0, 65535]", default="0", digit="[0]", dynamic="0", hide="1", ro="0" 
    unsigned int AddrByteNum[64];

    // @desc: alias="RegValue", type="u32", size="[1, 64]", range="[0, 65535]", default="0", digit="[0]", dynamic="0", hide="1", ro="0" 
    unsigned int RegValue[64];

    // @desc: alias="ValueByteNum", type="u32", size="[1, 64]", range="[0, 65535]", default="0", digit="[0]", dynamic="0", hide="1", ro="0" 
    unsigned int ValueByteNum[64];

    // @desc: alias="DelayFrames", type="u32", size="[1, 64]", range="[0, 65535]", default="0", digit="[0]", dynamic="0", hide="1", ro="0" 
    unsigned int DelayFrames[64];

} RKAiqExpI2cParam_t;

typedef struct {
    // @desc: alias="RealPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    RkAiqExpRealParam_t exp_real_params; //real value

    // @desc: alias="RegPara", type="struct", ui_module="normal_ui_style", hide="1", ro="0" 
    RkAiqExpSensorParam_t exp_sensor_params;//reg value
} RkAiqExpParamComb_t;

typedef struct {
    // @desc: alias="step", type="s32", size="[1,1]", range="[0, 65535]", default="0", digit="[0]", hide="1", ro="0" 
    int step;
    // @desc: alias="gain", type="s32", size="[1,1]", range="[0, 65535]", default="0", digit="[0]", hide="1", ro="0" 
    int gain;
    // @desc: type="bool", alias="update", default="0", hide="1", ro="0" 
    
   _Bool 
                  update;
} RkAiqPIrisParam_t;

typedef struct {
    // @desc: alias="pwmDuty", type="s32", size="[1,1]", range="[0, 100]", default="0", digit="[0]", hide="1", ro="0" 
    int pwmDuty; //percent value,range = 0-100
    // @desc: type="bool", alias="update", default="0", hide="1", ro="0" 
    
   _Bool 
              update;
} RkAiqDCIrisParam_t;

typedef struct {
    // @desc: alias="PIris", type="struct", ui_module="normal_ui_style", hide="1", ro="0" 
    RkAiqPIrisParam_t PIris;
    // @desc: alias="DCIris", type="struct", ui_module="normal_ui_style", hide="1", ro="0" 
    RkAiqDCIrisParam_t DCIris;
} RkAiqIrisParamComb_t;

typedef struct RKAiqAecExpInfo_s {

    // @desc: alias="LinearExp", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    RkAiqExpParamComb_t LinearExp;

    // @desc: alias="HdrExp", type="struct_list", size="[1, 3]", ui_module="normal_ui_style", ro="0" 
    RkAiqExpParamComb_t HdrExp[3];

    // @desc: alias="Iris", type="struct", ui_module="normal_ui_style", hide="1", ro="0" 
    RkAiqIrisParamComb_t Iris;

    // @desc: alias="LineLengthPixels(hts)", type="u16", size="[1,1]", range="[0, 65535]", default="0", digit="[0]", hide="0", ro="0" 
    uint16_t line_length_pixels;

    // @desc: alias="FrameLengthLines(vts)", type="u32", size="[1,1]", range="[0, 4294967296]", default="0", digit="[0]", hide="0", ro="0" 
    uint32_t frame_length_lines;

    // @desc: alias="PixelClockFreqMhz", type="f32", size="[1,1]", range="[0, 65535]", default="0", digit="[2]", hide="0", ro="0" 
    float pixel_clock_freq_mhz;

    // @desc: alias="CISFeature_t", type="struct", ui_module="normal_ui_style", hide="1", ro="0" 
    CISFeature_t CISFeature;

    // @desc: alias="I2cPara", type="struct", ui_module="normal_ui_style", hide="1", ro="0" 
    RKAiqExpI2cParam_t exp_i2c_params;
} RKAiqAecExpInfo_t;

/*****************************************************************************/
/**
 * @brief   ISP2.0 AEC transfer Params(from demo to rkaiq)
 */
/*****************************************************************************/

typedef struct RKAiqAecStats_s {
    RkAiqAecHwStatsRes_t ae_data; //AeHwMeas_Res
    RKAiqAecExpInfo_t ae_exp; //AeExp_Info
} RKAiqAecStats_t;

typedef RkAiqAecHwConfig_t html_aec_para_t;
/*
 *  Copyright (c) 2019 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
typedef struct Aec_AeRange_uapi_s {
    float Min;
    float Max;
} Aec_AeRange_uapi_t;

typedef struct Aec_LinAeRange_uapi_s {
    Aec_AeRange_uapi_t stExpTimeRange;
    Aec_AeRange_uapi_t stGainRange;
    Aec_AeRange_uapi_t stIspDGainRange;
    Aec_AeRange_uapi_t stPIrisRange;
} Aec_LinAeRange_uapi_t;

typedef struct Aec_HdrAeRange_uapi_s {
    Aec_AeRange_uapi_t stExpTimeRange[3];
    Aec_AeRange_uapi_t stGainRange[3];
    Aec_AeRange_uapi_t stIspDGainRange[3];
    Aec_AeRange_uapi_t stPIrisRange;
} Aec_HdrAeRange_uapi_t;

typedef struct Uapi_AeAttrV2_uapi_s {
    CalibDb_AeSpeedV2_t stAeSpeed;
    // DelayFrmNum
    uint8_t BlackDelayFrame;
    uint8_t WhiteDelayFrame;
    // Auto/Fixed fps
    CalibDb_AeFrmRateAttrV2_t stFrmRate;
    CalibDb_AntiFlickerAttrV2_t stAntiFlicker;
    // auto range
    Aec_LinAeRange_uapi_t LinAeRange; // result LinAerange
    Aec_HdrAeRange_uapi_t HdrAeRange; // result HdrAerange
} Uapi_AeAttrV2_uapi_t;

// manual exposure
typedef struct Uapi_LinMeAttrV2_uapi_s {
    // @desc: type="bool", alias="ManualTimeEn", default="1", hide="0", ro="0" 
    
   _Bool 
        ManualTimeEn;
    // @desc: type="bool", alias="ManualGainEn", default="1", hide="0", ro="0" 
    
   _Bool 
        ManualGainEn;
    // @desc: type="bool", alias="ManualIspDgainEn", default="1", hide="0", ro="0" 
    
   _Bool 
        ManualIspDgainEn;
    // @desc: alias="TimeValue", type="f32", size="[1,1]", range="[0, 1]", default="0.003", digit="[6]", hide="0", ro="0" 
    float TimeValue; // unit: s = 10^6 us
    // @desc: alias="GainValue", type="f32", size="[1,1]", range="[1, 4096]", default="1", digit="[3]", hide="0", ro="0" 
    float GainValue;
    // @desc: alias="IspDGainValue", type="f32", size="[1,1]", range="[1, 4096]", default="1", digit="[3]", hide="0", ro="0" 
    float IspDGainValue;
} Uapi_LinMeAttrV2_uapi_t;

typedef struct Uapi_HdrMeAttrV2_uapi_s {
    // @desc: type="bool", alias="ManualTimeEn", default="1", hide="0", ro="0" 
    
   _Bool 
        ManualTimeEn;
    // @desc: type="bool", alias="ManualGainEn", default="1", hide="0", ro="0" 
    
   _Bool 
        ManualGainEn;
    // @desc: type="bool", alias="ManualIspDgainEn", default="1", hide="0", ro="0" 
    
   _Bool 
        ManualIspDgainEn;
    // @desc: alias="TimeValue", type="f32", size="[1, 3]", range="[0, 1]", default="0.003", digit="[6]", dynamic="0", hide="0", ro="0" 
    float TimeValue[(3)];
    // @desc: alias="GainValue", type="f32", size="[1, 3]", range="[1, 4096]", default="1.0", digit="[3]", dynamic="0", hide="0", ro="0" 
    float GainValue[(3)];
    // @desc: alias="IspDGainValue", type="f32", size="[1, 3]", range="[1, 4096]", default="1.0", digit="[3]", dynamic="0", hide="0", ro="0" 
    float IspDGainValue[(3)];
} Uapi_HdrMeAttrV2_uapi_t;

typedef struct Uapi_MeAttrV2_uapi_s {
    // @desc: alias="LinearAE", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    Uapi_LinMeAttrV2_uapi_t LinearAE;

    // @desc: alias="HdrAE", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    Uapi_HdrMeAttrV2_uapi_t HdrAE;
} Uapi_MeAttrV2_uapi_t;

typedef struct Aec_uapi_advanced_attr_uapi_s {
    
   _Bool 
        enable;
    uint8_t GridWeights[15 * 15];
    uint8_t DayGridWeights[225];
    uint8_t NightGridWeights[225];
    
   _Bool 
        SetAeRangeEn;
    Aec_LinAeRange_uapi_t SetLinAeRange;
    Aec_HdrAeRange_uapi_t SetHdrAeRange;
} Aec_uapi_advanced_attr_uapi_t;

typedef struct __uapi_expsw_attr_uapi_s {
    rk_aiq_uapi_sync_t sync;
    uint8_t Enable;
    CalibDb_CamRawStatsModeV2_t RawStatsMode;
    CalibDb_CamHistStatsModeV2_t HistStatsMode;
    CalibDb_CamYRangeModeV2_t YRangeMode;
    uint8_t AecRunInterval;

    // @desc: type="enum", alias="OPMode", enum_def="RKAiqOPMode_uapi_t", default="RK_AIQ_OP_MODE_AUTO", ro="0" 
    RKAiqOPMode_t AecOpType;
    Cam15x15UCharMatrix_t GridWeights;
    Uapi_AeAttrV2_uapi_t stAuto;

    // @desc: alias="ManualCtrl", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    Uapi_MeAttrV2_uapi_t stManual;

    Aec_uapi_advanced_attr_uapi_t stAdvanced;
} uapi_expsw_attr_t;

typedef struct uapi_expinfo {
    // @desc: type="bool", alias="IsConverged", default="0", hide="1", ro="0" 
    
   _Bool 
                     IsConverged;
    // @desc: type="bool", alias="IsExpMax", default="0", hide="1", ro="0" 
    
   _Bool 
                     IsExpMax;
    // @desc: alias="LumaDeviation", type="f32", size="[1,1]", range="[-256, 256]", default="0.0", digit="[3]", hide="1", ro="0" 
    float LumaDeviation;
    // @desc: alias="HdrLumaDeviation", type="f32", size="[1, 3]", range="[-256, 256]", default="0.0", digit="[3]", dynamic="0", hide="1", ro="0" 
    float HdrLumaDeviation[3];
    // @desc: alias="MeanLuma", type="f32", size="[1,1]", range="[0, 256]", default="0.0", digit="[2]", hide="0", ro="0" 
    float MeanLuma;
    // @desc: alias="HdrMeanLuma", type="f32", size="[1, 3]", range="[0, 256]", default="0.0", digit="[2]", dynamic="0", hide="0", ro="0" 
    float HdrMeanLuma[3];
    // @desc: alias="GlobalEnvLux", type="f32", size="[1,1]", range="[0, 65535]", default="0.0", digit="[2]", hide="1", ro="0" 
    float GlobalEnvLux;
    // @desc: alias="BlockEnvLux", type="f32", size="[15, 15]", range="[0, 65535]", default="0.0", digit="[2]", dynamic="0", hide="1", ro="0" 
    float BlockEnvLux[((25 > 225) ? 25 : 225)];
    // @desc: alias="CurExpInfo", type="struct", ui_module="normal_ui_style", hide="0", ro="0" ;
    RKAiqAecExpInfo_t CurExpInfo;

    // @desc: alias="Piris", type="u16", size="[1,1]", range="[0, 1024]", default="0", digit="[0]", hide="1", ro="0" 
    unsigned short Piris;

    // @desc: alias="LinePeriodsPerField", type="f32", size="[1,1]", range="[0, 65535]", default="0", digit="[2]", hide="1", ro="0" 
    float LinePeriodsPerField;

    // @desc: alias="PixelPeriodsPerLine", type="f32", size="[1,1]", range="[0, 65535]", default="0", digit="[2]", hide="1", ro="0" 
    float PixelPeriodsPerLine;

    // @desc: alias="PixelClockFreqMHZ", type="f32", size="[1,1]", range="[0, 4096]", default="0", digit="[2]", hide="1", ro="0" 
    float PixelClockFreqMHZ;
} uapi_expinfo_t;

/*****************************************************************************/
/**
 * @brief   ISP AEC HW-Meas Stats Params
 */
/*****************************************************************************/

typedef struct uapi_rawhist_stats_s {
    // @desc: alias="bins", type="u32", size="[1, 256]", range="[0, 268435456]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned int bins[256];
} uapi_rawhist_stats_t;

typedef struct uapi_sihist_stats_s {
    // @desc: alias="bins", type="u32", size="[1, 32]", range="[0, 268435456]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned int bins[32];
} uapi_sihist_stats_t;

typedef struct uapi_rawae_big_stats_s {
    // @desc: alias="channelr_xy", type="u16", size="[1, 225]", range="[0, 1023]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    uint16_t channelr_xy[225];

    // @desc: alias="channelg_xy", type="u16", size="[1, 225]", range="[0, 4095]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    uint16_t channelg_xy[225];

    // @desc: alias="channelb_xy", type="u16", size="[1, 225]", range="[0, 1023]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    uint16_t channelb_xy[225];

    // @desc: alias="channely_xy", type="u16", size="[1, 225]", range="[0, 4095]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    uint16_t channely_xy[225]; //not HW!

    // @desc: alias="wndx_sumr", type="u64", size="[1, 4]", range="[0, 536870912]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    uint64_t wndx_sumr[4];

    // @desc: alias="wndx_sumg", type="u64", size="[1, 4]", range="[0, 4294967296]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    uint64_t wndx_sumg[4];

    // @desc: alias="wndx_sumb", type="u64", size="[1, 4]", range="[0, 536870912]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    uint64_t wndx_sumb[4];

    // @desc: alias="wndx_channelr", type="u16", size="[1, 4]", range="[0, 1023]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    uint16_t wndx_channelr[4]; //not HW!

    // @desc: alias="wndx_channelg", type="u16", size="[1, 4]", range="[0, 4095]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    uint16_t wndx_channelg[4]; //not HW!

    // @desc: alias="wndx_channelb", type="u16", size="[1, 4]", range="[0, 1023]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    uint16_t wndx_channelb[4]; //not HW!

    // @desc: alias="wndx_channely", type="u16", size="[1, 4]", range="[0, 4095]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    uint16_t wndx_channely[4]; //not HW!
} uapi_rawae_big_stats_t;

typedef struct uapi_rawae_lite_stat_s {
    // @desc: alias="channelr_xy", type="u16", size="[1, 25]", range="[0, 1023]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    uint16_t channelr_xy[25];

    // @desc: alias="channelg_xy", type="u16", size="[1, 25]", range="[0, 4095]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    uint16_t channelg_xy[25];

    // @desc: alias="channelb_xy", type="u16", size="[1, 25]", range="[0, 1023]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    uint16_t channelb_xy[25];

    // @desc: alias="channely_xy", type="u16", size="[1, 25]", range="[0, 4095]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    uint16_t channely_xy[25]; //not HW!
} uapi_rawae_lite_stat_t;

typedef struct uapi_yuvae_stats_s {
    // @desc: alias="channely_xy", type="u64", size="[1, 4]", range="[0, 4294967296]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    uint64_t ro_yuvae_sumy[4];

    // @desc: alias="channely_xy", type="u8", size="[1, 225]", range="[0, 255]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned char mean[225];
} uapi_yuvae_stats_t;

typedef struct uapi_raw_stats_s {
    //rawae
    // @desc: alias="rawae_big", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    uapi_rawae_big_stats_t rawae_big;
    // @desc: alias="rawae_lite", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    uapi_rawae_lite_stat_t rawae_lite;
    //rawhist
    // @desc: alias="rawhist_big", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    uapi_rawhist_stats_t rawhist_big;
    // @desc: alias="rawhist_lite", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    uapi_rawhist_stats_t rawhist_lite;
} uapi_raw_stats_t;

typedef struct uapi_ae_hwstats_s {
    // @desc: alias="chn", type="struct_list", size="[1, 3]", ui_module="normal_ui_style", ro="0" 
    uapi_raw_stats_t chn[3];
    // @desc: alias="extra", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    uapi_raw_stats_t extra;
    // @desc: alias="yuvae", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    uapi_yuvae_stats_t yuvae;
    // @desc: alias="sihist", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    uapi_sihist_stats_t sihist;
} uapi_ae_hwstats_t;
/*
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
typedef struct __uapi_wb_mode_t {
  // @desc: type="enum", alias="mode", enum_def="opMode_t", default="OP_AUTO", ro="0" ;
  opMode_t mode;
} uapi_wb_mode_t;

typedef struct __uapi_wb_gain_t {
  // @desc: alias="rgain", type="f32", size="[1,1]", range="[0, 8]", default="0", digit="[6]", hide="0", ro="0" 
    float rgain;
  // @desc: alias="grgain", type="f32", size="[1,1]", range="[0, 8]", default="0", digit="[6]", hide="0", ro="0" 
    float grgain;
  // @desc: alias="gbgain", type="f32", size="[1,1]", range="[0, 8]", default="0", digit="[6]", hide="0", ro="0" 
    float gbgain;
  // @desc: alias="bgain", type="f32", size="[1,1]", range="[0, 8]", default="0", digit="[6]", hide="0", ro="0" 
    float bgain;
} uapi_wb_gain_t;
//typedef struct stat3a_lightType_s
typedef struct rk_tool_awb_stat_wp_res_v201_s {
    // @desc: alias="WpNo", type="s64", size="[1,1]", range="[-9223372036854775808, 9223372036854775807]", default="0", digit="[0]", hide="0", ro="0" 
    long long WpNo;
    // @desc: alias="RgainValue", type="s64", size="[1,1]", range="[-9223372036854775808, 9223372036854775807]", default="0", digit="[0]", hide="0", ro="0" 
    long long RgainValue;
    // @desc: alias="BgainValue", type="s64", size="[1,1]", range="[-9223372036854775808, 9223372036854775807]", default="0", digit="[0]", hide="0", ro="0" 
    long long BgainValue;
} rk_tool_awb_stat_wp_res_v201_t;

typedef struct rk_tool_awb_stat_blk_res_v201_s {
    // @desc: alias="WpNo", type="s64", size="[1,1]", range="[-9223372036854775808, 9223372036854775807]", default="0", digit="[0]", hide="0", ro="0" 
    long long WpNo;
    // @desc: alias="Rvalue", type="s64", size="[1,1]", range="[-9223372036854775808, 9223372036854775807]", default="0", digit="[0]", hide="0", ro="0" 
    long long Rvalue;
    // @desc: alias="Gvalue", type="s64", size="[1,1]", range="[-9223372036854775808, 9223372036854775807]", default="0", digit="[0]", hide="0", ro="0" 
    long long Gvalue;
    // @desc: alias="Bvalue", type="s64", size="[1,1]", range="[-9223372036854775808, 9223372036854775807]", default="0", digit="[0]", hide="0", ro="0" 
    long long Bvalue;
} rk_tool_awb_stat_blk_res_v201_t;

typedef struct rk_tool_awb_stat_wp_res_light_v201_s {
    // @desc: alias="xYType", type="struct_list", size="[1, 2]", ui_module="normal_ui_style", ro="0" 
    rk_tool_awb_stat_wp_res_v201_t xYType[2];
} rk_tool_awb_stat_wp_res_light_v201_t;

typedef struct rk_tool_awb_stat_res2_v30_s {
    // @desc: alias="light", type="struct_list", size="[1, 2]", ui_module="normal_ui_style", ro="0" 
    rk_tool_awb_stat_wp_res_light_v201_t light[7];
    // @desc: alias="WpNo2", type="s32", size="[1, 8]", range="[-2147483648, 2147483647]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int WpNo2[7];
    // @desc: alias="blockResult", type="struct_list", size="[1, 255]", ui_module="normal_ui_style", ro="0" 
    rk_tool_awb_stat_blk_res_v201_t blockResult[225];
    // @desc: alias="multiwindowLightResult", type="struct_list", size="[1, 4]", ui_module="normal_ui_style", ro="0" 
    rk_tool_awb_stat_wp_res_light_v201_t multiwindowLightResult[4];
    // @desc: alias="excWpRangeResult", type="struct_list", size="[1, 4]", ui_module="normal_ui_style", ro="0" 
    rk_tool_awb_stat_wp_res_v201_t excWpRangeResult[4];
    // @desc: alias="WpNoHist", type="u32", size="[1, 8]", range="[0, 4294967295]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned int WpNoHist[8];
} rk_tool_awb_stat_res2_v30_t;

typedef struct rk_tool_awb_measure_wp_res_fl_s {
    // @desc: alias="WpNo", type="u32", size="[1, 1]", range="[0, 4294967295]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned int WpNo;
    // @desc: alias="gain", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float gain[4];//mean rgain  value
    // @desc: alias="WpNoHist_2", type="s32", size="[1, 8]", range="[-2147483648, 2147483647]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int WpNoHist_2[8]; //uselsess
} rk_tool_awb_measure_wp_res_fl_t;

typedef struct rk_tool_awb_measure_blk_res2_fl_s {
    // @desc: alias="WpNo", type="u32", size="[1, 1]", range="[0, 4294967295]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned int WpNo;
    // @desc: alias="gain", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float gain[4];//mean rgain  value
} rk_tool_awb_measure_blk_res2_fl_t;

typedef struct rk_tool_awb_measure_wp_res_light_fl_s {
    // @desc: alias="xYType", type="struct_list", size="[1, 2]", ui_module="normal_ui_style", ro="0" 
    rk_tool_awb_measure_wp_res_fl_t xYType[2];
} rk_tool_awb_measure_wp_res_light_fl_t;

typedef struct rk_tool_awb_measure_blk_res_fl_s {
    // @desc: alias="R", type="f32", size="[1, 1]", range="[0, 1]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float R;//mean r value and normalize to 0~1
    // @desc: alias="G", type="f32", size="[1, 1]", range="[0, 1]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float G;
    // @desc: alias="B", type="f32", size="[1, 1]", range="[0, 1]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float B;
} rk_tool_awb_measure_blk_res_fl_t;

typedef struct rk_tool_awb_effect_para1_s{
    // @desc: alias="hdrFrameChoose", type="s32", size="[1, 1]", range="[-2147483648, 2147483647]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int hdrFrameChoose;
}rk_tool_awb_effect_para1_t;

typedef struct rk_tool_awb_stat_res_full_s {
    // @desc: alias="lightNum", type="s32", size="[1, 1]", range="[-2147483648, 2147483647]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int lightNum;
    // @desc: alias="light", type="struct_list", size="[1, 14]", ui_module="normal_ui_style", ro="0" 
    rk_tool_awb_measure_wp_res_light_fl_t light[14];
    // @desc: type="bool", alias="lightWpResVaLidIll", default="0", hide="0", ro="0" 
    
   _Bool 
                                 lightWpResVaLidIll[14];//for time share
    // @desc: type="bool", alias="lightWpResVaLid", default="0", hide="0", ro="0" 
    
   _Bool 
                                 lightWpResVaLid;//for time share
    // @desc: alias="WpNo", type="s32", size="[1, 2]", range="[-2147483648, 2147483647]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int WpNo[2];//for diff xy type
    // @desc: alias="WpNo2", type="s32", size="[1, 14]", range="[-2147483648, 2147483647]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int WpNo2[14];//for diff illu
    // @desc: type="bool", alias="blkGwResValid", default="0", hide="0", ro="0" 
    
   _Bool 
                           blkGwResValid;
    // @desc: type="bool", alias="blkSgcResVaLid", default="0", hide="0", ro="0" 
    
   _Bool 
                           blkSgcResVaLid;
    // @desc: alias="blkSgcResult", type="struct_list", size="[1, 225]", ui_module="normal_ui_style", ro="0" 
    rk_tool_awb_measure_blk_res_fl_t blkSgcResult[225];
    // @desc: type="bool", alias="blkWpResVaLid", default="0", hide="0", ro="0" 
    
   _Bool 
                            blkWpResVaLid;
    // @desc: alias="blkWpResult", type="struct_list", size="[1, 225]", ui_module="normal_ui_style", ro="0" 
    rk_tool_awb_measure_blk_res2_fl_t blkWpResult[225];
    // @desc: type="bool", alias="excWpResValid", default="0", hide="0", ro="0" 
    
   _Bool 
        excWpResValid;
    // @desc: alias="excWpRangeResult", type="struct_list", size="[1, 4]", ui_module="normal_ui_style", ro="0" 
    rk_tool_awb_measure_wp_res_fl_t excWpRangeResult[4];
    // @desc: alias="extraLightResult", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    rk_tool_awb_measure_wp_res_fl_t extraLightResult;
    // @desc: alias="WpNoHist", type="u32", size="[1, 8]", range="[0, 4294967295]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned int WpNoHist[8];
    // @desc: alias="effectHwPara", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    rk_tool_awb_effect_para1_t effectHwPara;
} rk_tool_awb_stat_res_full_t;

typedef struct rk_tool_awb_smart_run_res_s{
    // @desc: type="bool", alias="blc1Stable", default="0", hide="0", ro="0" 
    
   _Bool 
        blc1Stable;
    // @desc: type="bool", alias="lvStable", default="0", hide="0", ro="0" 
    
   _Bool 
        lvStable;
    // @desc: type="bool", alias="wbgainStable", default="0", hide="0", ro="0" 
    
   _Bool 
        wbgainStable;
    // @desc: type="bool", alias="wpDiffweiStable", default="0", hide="0", ro="0" 
    
   _Bool 
        wpDiffweiStable;
    // @desc: type="bool", alias="statisticsStable", default="0", hide="0", ro="0" 
    
   _Bool 
        statisticsStable;
    // @desc: type="bool", alias="forceRunAwbFlag", default="0", hide="0", ro="0" 
    
   _Bool 
        forceRunAwbFlag;//update by api or prepare;
    // @desc: type="bool", alias="samrtRunAwbFlag2", default="0", hide="0", ro="0" 
    
   _Bool 
        samrtRunAwbFlag2;//update by above paras
    // @desc: alias="wbgainMean", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float wbgainMean[4];
    // @desc: type="bool", alias="algMethodStable", default="0", hide="0", ro="0" 
    
   _Bool 
        algMethodStable;
}rk_tool_awb_smart_run_res_t;

typedef struct rk_tool_awb_illInf_s {
    // @desc: alias="illName", type="string", size="[1, 100]", range="[-128, 127]", default="default", dynamic="0", hide="0", ro="0" 
    char illName[100];
    // @desc: alias="gainValue", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float gainValue[4];
    // @desc: alias="prob_total", type="f32", size="[1, 1]", range="[0, 1]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float prob_total;
    // @desc: alias="prob_dis", type="f32", size="[1, 1]", range="[0, 1]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float prob_dis;
    // @desc: alias="prob_LV", type="f32", size="[1, 1]", range="[0, 1]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float prob_LV;
    // @desc: alias="spatialGainValue", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float spatialGainValue[4];
    // @desc: alias="prob_WPNO", type="f32", size="[1, 1]", range="[0, 1]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float prob_WPNO;
    // @desc: alias="gainValue", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float staWeight;
    // @desc: alias="xyType2Weight", type="f32", size="[1, 1]", range="[0, 1]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float xyType2Weight;
} rk_tool_awb_illInf_t;

typedef struct rk_tool_color_tempture_info_s {
    // @desc: type="bool", alias="valid", default="0", hide="0", ro="0" 
    
   _Bool 
        valid;
    // @desc: alias="CCT", type="f32", size="[1,1]", range="[0, 10000]", default="5000", digit="[0]", hide="0", ro="0" 
    float CCT;
    // @desc: alias="CCRI", type="f32", size="[1,1]", range="[-2, 2]", default="0", digit="[3]", hide="0", ro="0" 
    float CCRI;
} rk_tool_color_tempture_info_t;

typedef struct rk_tool_awb_strategy_result_s {
    // @desc: type="bool", alias="awbConverged", default="0", hide="0", ro="0" 
    
   _Bool 
        awbConverged;
    // @desc: alias="cctGloabl", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    rk_tool_color_tempture_info_t cctGloabl;
    // @desc: alias="lightNum", type="s32", size="[1, 1]", range="[-2147483648, 2147483647]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int lightNum;
    // @desc: alias="smartAwbRunRes", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    rk_tool_awb_smart_run_res_t smartAwbRunRes;
    // @desc: alias="count", type="u32", size="[1, 1]", range="[0, 4294967295]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    unsigned int count;
    // @desc: alias="runInterval", type="u32", size="[1, 1]", range="[0, 4294967295]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    uint32_t runInterval;
    // @desc: alias="tolerance", type="f32", size="[1,1]", range="[0, 10000]", default="5000", digit="[0]", hide="0", ro="0" 
    float tolerance;
    // @desc: alias="dsRate", type="u8", size="[1, 1]", range="[0, 255]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    uint8_t dsRate; //downsample 8x8->Pixel(R,G,B)
    // @desc: alias="width_ds", type="u32", size="[1, 1]", range="[0, 4294967295]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    uint32_t width_ds;
    // @desc: alias="height_ds", type="u32", size="[1, 1]", range="[0, 4294967295]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    uint32_t height_ds;
    // @desc: alias="WPmode", type="s32", size="[1, 1]", range="[-2147483648, 2147483647]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int WPmode;
    // @desc: alias="WPTotalNUM", type="u32", size="[1, 1]", range="[0, 4294967295]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    uint32_t WPTotalNUM;
    // @desc: alias="WPType", type="s32", size="[1, 1]", range="[-2147483648, 2147483647]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int WPType;
    // @desc: alias="LVType", type="s32", size="[1, 1]", range="[-2147483648, 2147483647]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int LVType;
    // @desc: alias="LVValue", type="s32", size="[1, 1]", range="[-2147483648, 2147483647]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int LVValue;// 8bit/1x/1s
    // @desc: alias="fLVValue", type="f32", size="[1,1]", range="[0, 255000]", default="5000", digit="[0]", hide="0", ro="0" 
    float fLVValue;
    // @desc: alias="LVLevel", type="s32", size="[1, 1]", range="[-2147483648, 2147483647]", default="0", digit="[0]", dynamic="0", hide="0", ro="0" 
    int LVLevel;
    // @desc: alias="illInf", type="struct_list", size="[1, 14]", ui_module="normal_ui_style", ro="0" 
    rk_tool_awb_illInf_t illInf[14];//information and measure result in different illuminations
    // @desc: alias="wbGainTepTp3", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float wbGainTepTp3[4];
    // @desc: alias="wbWeiTepTp3", type="f32", size="[1, 1]", range="[0, 100]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float wbWeiTepTp3;//temporal mix statistics
    // @desc: alias="xy_area_type", type="u8", size="[1, 1]", range="[0, 255]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    uint8_t xy_area_type; //enalbe type
    // @desc: type="bool", alias="spaGainEqu2Tem", default="0", hide="0", ro="0" 
    
   _Bool 
        spaGainEqu2Tem;
    // @desc: type="bool", alias="sgcGainEqu2Tem", default="0", hide="0", ro="0" 
    
   _Bool 
        sgcGainEqu2Tem;
    // @desc: alias="wbGainType3", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float wbGainType3[4];
    // @desc: alias="wbGainType1", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float wbGainType1[4];
    // @desc: alias="wbWeightType3", type="f32", size="[1, 1]", range="[0, 100]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float wbWeightType3;
    // @desc: alias="wbGainTep", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float wbGainTep[4];//night gain
    // @desc: alias="wbGainSgc", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float wbGainSgc[4];
    // @desc: alias="wbWeightSgc", type="f32", size="[1, 1]", range="[0, 100]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float wbWeightSgc;
    // @desc: alias="wbGainSpa", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float wbGainSpa[4];//day gain
    // @desc: alias="wbWeightSpa", type="f32", size="[1, 1]", range="[0, 100]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float wbWeightSpa;
    // @desc: alias="varianceLuma", type="f32", size="[1, 1]", range="[0, 2147483647]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float varianceLuma;
    // @desc: alias="wbGainDampFactor", type="f32", size="[1, 1]", range="[0, 1]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float wbGainDampFactor;
    // @desc: type="bool", alias="clipEnalbe", default="0", hide="0", ro="0" 
    
   _Bool 
        clipEnalbe;
    // @desc: type="bool", alias="updateFlag", default="0", hide="0", ro="0" 
    
   _Bool 
        updateFlag;
    // @desc: alias="wbGainIntpStrategy", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float wbGainIntpStrategy[4];//gain by interpartition strategy
    // @desc: alias="wbGainClip", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float wbGainClip[4];//gain by clip
    // @desc: alias="wbGainCaga", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float wbGainCaga[4];//gain by  chromatic adatptation gain adjust
    // @desc: alias="wbGainAdjust", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float wbGainAdjust[4];//gain by color temperature shift
    // @desc: alias="wbGainOffset", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float wbGainOffset[4];//gain by gain shift
    // @desc: alias="wbGainSmooth", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float wbGainSmooth[4];//gain by smooth factor
    // @desc: alias="stat3aAwbLastGainOut", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float stat3aAwbLastGainOut[4];//final gain of last frame
    // @desc: alias="stat3aAwbGainOut", type="f32", size="[1, 4]", range="[0, 8]", default="1", digit="[4]", dynamic="0", hide="0", ro="0" 
    float stat3aAwbGainOut[4];// final gain
    // @desc: alias="algMethod", type="s32", size="[1, 1]", range="[0, 100]", default="1", digit="[0]", dynamic="0", hide="0", ro="0" 
    int algMethod;
} rk_tool_awb_strategy_result_t;

typedef struct __uapi_wb_log_info_t {
    // @desc: alias="awb_stat", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    rk_tool_awb_stat_res2_v30_t awb_stat;
    // @desc: alias="awb_stat_algo", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    rk_tool_awb_stat_res_full_t awb_stat_algo;
    // @desc: alias="awb_strategy_result", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    rk_tool_awb_strategy_result_t awb_strategy_result;
} uapi_wb_log_info_t;

typedef struct __uapi_wb_log_t {
    // @desc: alias="uapi_wb_log_info_t", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    uapi_wb_log_info_t info;
} uapi_wb_log_t;
typedef struct uapiMergeCurrCtlData_s
{
  // @desc: alias="Envlv", type="f32", size="[1,1]", range="[0, 8]", default="0", digit="[6]", hide="0", ro="0" 
  float Envlv;
  // @desc: alias="MoveCoef", type="f32", size="[1,1]", range="[0, 8]", default="0", digit="[6]", hide="0", ro="0" 
  float MoveCoef;
} uapiMergeCurrCtlData_t;
/*
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




/*
 * atmo_head.h
 *
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

typedef struct uapiTmoCurrCtlData_s
{
  // @desc: type="enum", alias="GlobalLumaMode", enum_def="GlobalLumaMode_t", default="GLOBALLUMAMODE_ENVLV", ro="0" 
  GlobalLumaMode_t GlobalLumaMode;
  // @desc: type="enum", alias="Mode", enum_def="DetailsHighLightMode_t", default="DETAILSHIGHLIGHTMODE_ENVLV", ro="0" 
  DetailsHighLightMode_t DetailsHighLightMode;
  // @desc: type="enum", alias="DetailsLowLightMode", enum_def="DetailsLowLightMode_t", default="DETAILSLOWLIGHTMODE_ISO", ro="0" 
  DetailsLowLightMode_t DetailsLowLightMode;
  // @desc: type="enum", alias="GlobalTmoMode", enum_def="TmoTypeMode_t", default="TMOTYPEMODE_DYNAMICRANGE", ro="0" 
  TmoTypeMode_t GlobalTmoMode;
  // @desc: type="enum", alias="LocalTMOMode", enum_def="TmoTypeMode_t", default="TMOTYPEMODE_DYNAMICRANGE", ro="0" 
  TmoTypeMode_t LocalTMOMode;
  float Envlv;
  float ISO;
  float OEPdf;
  float FocusLuma;
  float DarkPdf;
  float DynamicRange;
} uapiTmoCurrCtlData_t;
/*
 *  Copyright (c) 2021 Rockchip Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */




enum { ADRC_NORMAL = 0, ADRC_HDR = 1, ADRC_NIGHT = 2 };

typedef struct DrcInfo_s {
    // @desc: alias="EnvLv", type="f32", size="[1,1]", range="[0, 1]", default="0", digit="[6]", hide="0", ro="0" 
    float EnvLv;
} DrcInfo_t;






typedef struct __ae_uapi {
    // @desc: alias="expsw_attr", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    uapi_expsw_attr_t expsw_attr;
    // @desc: alias="QueryExpInfo", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    uapi_expinfo_t expinfo;
} ae_uapi_t;

typedef struct __awb_uapi {
    // @desc: alias="mode", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    uapi_wb_mode_t mode;
    // @desc: alias="wbgain", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    uapi_wb_gain_t wbgain;
} awb_uapi_t;

typedef struct __amerge_uapi {
    // @desc: alias="ctldata", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    uapiMergeCurrCtlData_t ctldata;
} amerge_uapi_t;

typedef struct __atmo_uapi {
    // @desc: alias="ctldata", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    uapiTmoCurrCtlData_t ctldata;
} atmo_uapi_t;

typedef struct __adrc_uapi {
    // @desc: alias="drc", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    DrcInfo_t drc;
} adrc_uapi_t;

typedef struct __aiq_scene {
    // @desc: alias="main_scene", type="string", size="[1, 1]", range="[0, 32]", default="normal", dynamic="0", hide="0", ro="0" 
    char* main_scene;
    // @desc: alias="sub_scene", type="string", size="[1, 1]", range="[0, 32]", default="day", dynamic="0", hide="0", ro="0" 
    char* sub_scene;
} aiq_scene_t;

typedef struct __work_mode {
    // @desc: type="enum", alias="mode", enum_def="rk_aiq_working_mode_t", default="RK_AIQ_WORKING_MODE_NORMAL", ro="0" ;
    rk_aiq_working_mode_t mode;
} work_mode_t;

typedef struct __aiq_sysctl_desc {
    // @desc: alias="scene", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    aiq_scene_t scene;
    // @desc: alias="work_mode", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    work_mode_t work_mode;
} RkaiqSysCtl_t;

typedef struct __aiq_measure_info {
    // @desc: alias="ae_hwstats", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    uapi_ae_hwstats_t ae_hwstats;
    // @desc: alias="wb_log", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    uapi_wb_log_t wb_log;
} aiq_measure_info_t;

typedef struct __aiq_uapi_t {
    // @desc: alias="ae_uapi", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    ae_uapi_t ae_uapi;
    // @desc: alias="awb_uapi", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    awb_uapi_t awb_uapi;
    // @desc: alias="amerge_uapi", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    amerge_uapi_t amerge_uapi;




    // @desc: alias="adrc_uapi", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    adrc_uapi_t adrc_uapi;

    // @desc: alias="SystemCtl", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    RkaiqSysCtl_t system;
    // @desc: alias="measure_info", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    aiq_measure_info_t measure_info;
} RkaiqUapi_t;



/************************************

IQ
├── common info
├── main scene
│     ├─── name:SceneA
│     ├─── sub scene
│     │     ├── name:SubA0
│     │     ├── CalibV2
│     │     .
│     │     ├── name:SubA1
│     │     ├── CalibV2
│     ├─── name:SceneB
│     ├─── sub scene
│     │     ├── name:SubB0
│     │     ├── CalibV2
│     │     .
│     │     ├── name:SubB1
│     │     ├── CalibV2
│     ├─── name:SceneC
│     ├─── sub scene
│     │     ├── name:SubC0
│     │     ├── CalibV2
│     │     .
│     │     ├── name:SubC1
│     .     └── CalibV2
│     .
│     .
│     ├── name:sceneC
│     ├── ...
│     └── name:sceneN

IQ JSON:{
  platform common info: {},
  sensor common info: {},
  main scene: [
  {
    name: sceneA,
    sub_scene: [
          {
            name: subsceneA0,
                  CalibDbV2: {
                    ae,
                    awb,
                    ...
                  }
          },
          {
            name: subsceneA1,
                  CalibDbV2: {
                    ae,
                    awb,
                    ...
                  }
          },
          .
          .
          .
          ],
  },
  {
    name: sceneB,
          sub_scene: [
          {
            name: subsceneA0,
                  CalibDbV2: {
                    ae,
                    awb,
                    ...
                  }
          },

          ],

  }
  .
  .
  .
  ]
}
***********************************/

typedef struct CamCalibDbModuleDes_s {
    char* name;
    int hw_ver;
    char* sw_ver;
} CamCalibDbModuleDes_t;

typedef struct CamCalibDbV2Context_s {
    CalibDb_Sensor_ParaV2_t* sensor_info;
    int sensor_info_len;
    CalibDb_Module_ParaV2_t* module_info;
    int module_info_len;
    CalibDb_SysStaticCfg_ParaV2_t* sys_cfg;
    int sys_cfg_len;
    char* calib_scene;
} CamCalibDbV2Context_t;

/**
 * PC Tool's json patch is not based on CamCalibDbV2Context_t
 * Then we define an struct most like to PC UI ARCH, when we got new json patch
 * apply patch to CamCalibDbV2Tuning_t and convert to CamCalibDbV2Context_t
 */
typedef struct CamCalibDbV2Tuning_s {
    CalibDb_Sensor_ParaV2_t sensor_calib;
    CalibDb_Module_ParaV2_t module_calib;
    CalibDb_SysStaticCfg_ParaV2_t sys_static_cfg;





    CamCalibDbV2ContextIsp30_t calib_scene;



} CamCalibDbV2Tuning_t;

typedef struct CamCalibSubSceneList_s {
    char* name;
    CamCalibDbV2ContextIsp30_t scene_isp30;




} CamCalibSubSceneList_t;

typedef struct CamCalibMainSceneList_s {
    char* name;
    // 'sub_scene' means Scene list of Ai ...
    CamCalibSubSceneList_t* sub_scene;
    int sub_scene_len;
} CamCalibMainSceneList_t;

typedef struct CamCalibDbProj_s {
    // TODO: move sensor info module etc. to an common struct
    // @desc: alias="SensorInfo", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Sensor_ParaV2_t sensor_calib;
    // @desc: alias="MoudleInfo", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_Module_ParaV2_t module_calib;
    // 'main_scene' means Scene list of A,B,C ...,
    CamCalibMainSceneList_t* main_scene;
    int main_scene_len;
    RkaiqUapi_t* uapi;
    int uapi_len;
    // @desc: alias="SysStaticCfg", type="struct", ui_module="normal_ui_style", hide="0", ro="0" 
    CalibDb_SysStaticCfg_ParaV2_t sys_static_cfg;
} CamCalibDbProj_t;

/*NOTE: SHOULD be defined next to CamCalibDbProj_t */
/*The storage struct of file camgroup.json */
typedef struct CamCalibDbCamgroup_s {
    //test
    int group_awb;
} CamCalibDbCamgroup_t;


