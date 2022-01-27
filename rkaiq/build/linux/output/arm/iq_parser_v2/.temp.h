# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbTypesV2.h"
# 1 "<built-in>"
# 1 "<命令行>"
# 1 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/stdc-predef.h" 1 3 4

# 1 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/stdc-predef.h" 3 4
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
# 52 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/stdc-predef.h" 3 4
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
# 1 "<命令行>" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbTypesV2.h"

# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbTypesV2.h"
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



# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/moduleinfo_head.h" 1
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

# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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




# 1 "/work/linux/rv1109/src/prebuilts/gcc/linux-x86/arm/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/8.3.0/include/stdbool.h" 1 3 4

# 1 "/work/linux/rv1109/src/prebuilts/gcc/linux-x86/arm/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/8.3.0/include/stdbool.h" 3 4
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
# 51 "/work/linux/rv1109/src/prebuilts/gcc/linux-x86/arm/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/8.3.0/include/stdbool.h" 3 4
/* Signal that all the definitions are present.  */
# 22 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 2
# 1 "/work/linux/rv1109/src/prebuilts/gcc/linux-x86/arm/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/8.3.0/include/stdint.h" 1 3 4
# 9 "/work/linux/rv1109/src/prebuilts/gcc/linux-x86/arm/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/8.3.0/include/stdint.h" 3 4
# 1 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/stdint.h" 1 3 4
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





# 1 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/bits/libc-header-start.h" 1 3 4
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







# 1 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/features.h" 1 3 4
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

   The `-ansi' switch to the GNU C compiler, and standards conformance
   options such as `-std=c99', define __STRICT_ANSI__.  If none of
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

   The macros `__GNU_LIBRARY__', `__GLIBC__', and `__GLIBC_MINOR__' are
   defined by this file unconditionally.  `__GNU_LIBRARY__' is provided
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
# 144 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/features.h" 3 4
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
# 213 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/features.h" 3 4
/* If nothing (other than _GNU_SOURCE and _DEFAULT_SOURCE) is defined,
   define _DEFAULT_SOURCE.  */
# 224 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/features.h" 3 4
/* This is to enable the ISO C11 extension.  */





/* This is to enable the ISO C99 extension.  */





/* This is to enable the ISO C90 Amendment 1:1995 extension.  */
# 255 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/features.h" 3 4
/* If none of the ANSI/POSIX macros are defined, or if _DEFAULT_SOURCE
   is defined, use POSIX.1-2008 (or another version depending on
   _XOPEN_SOURCE).  */
# 284 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/features.h" 3 4
/* Some C libraries once required _REENTRANT and/or _THREAD_SAFE to be
   defined in all multithreaded code.  GNU libc has not required this
   for many years.  We now treat them as compatibility synonyms for
   _POSIX_C_SOURCE=199506L, which is the earliest level of POSIX with
   comprehensive support for multithreaded code.  Using them never
   lowers the selected level of POSIX conformance, only raises it.  */
# 394 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/features.h" 3 4
/* The function 'gets' existed in C89, but is impossible to use
   safely.  It has been removed from ISO C11 and ISO C++14.  Note: for
   compatibility with various implementations of <cstdio>, this test
   must consider only the value of __cplusplus when compiling C++.  */






/* Get definitions of __STDC_* predefined macros, if the compiler has
   not preincluded this header automatically.  */
# 1 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/stdc-predef.h" 1 3 4
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
# 407 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/features.h" 2 3 4

/* This macro indicates that the installed library is the GNU C Library.
   For historic reasons the value now is 6 and this will stay from now
   on.  The use of this variable is deprecated.  Use __GLIBC__ and
   __GLIBC_MINOR__ now (see below) when you want to test for a specific
   GNU C library version and use the values in <gnu/lib-names.h> to get
   the sonames of the shared libraries.  */



/* Major and minor version number of the GNU C library package.  Use
   these macros to test for features in specific releases.  */






/* This is here only because every header file already includes this one.  */


# 1 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/sys/cdefs.h" 1 3 4
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
# 49 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/sys/cdefs.h" 3 4
/* GCC can always grok prototypes.  For C++ programs we add throw()
   to help it optimize the function calls.  But this works only with
   gcc 2.8.x and egcs.  For gcc 3.2 and up we even mark C functions
   as non-throwing using a function attribute since programs can use
   the -fexceptions options for C code as well.  */
# 88 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/sys/cdefs.h" 3 4
/* Compilers that are not clang may object to
       #if defined __clang__ && __has_extension(...)
   even though they do not need to evaluate the right-hand side of the &&.  */






/* These two macros are not used in glibc anymore.  They are kept here
   only because some other projects expect the macros to be defined.  */



/* For these things, GCC behaves the ANSI way normally,
   and the non-ANSI way under -traditional.  */




/* This is not a typedef so `const __ptr_t' does the right thing.  */



/* C++ needs to know that types and declarations are C, not C++.  */
# 122 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/sys/cdefs.h" 3 4
/* Fortify support.  */
# 138 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/sys/cdefs.h" 3 4
/* Support for flexible arrays.
   Headers that should use flexible arrays only if they're "real"
   (e.g. only if they won't affect sizeof()) should test
   #if __glibc_c99_flexarr_available.  */
# 162 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/sys/cdefs.h" 3 4
/* __asm__ ("xyz") is used throughout the headers to rename functions
   at the assembly language level.  This is wrapped by the __REDIRECT
   macro, in order to support compilers that can do this some other
   way.  When compilers don't support asm-names at all, we have to do
   preprocessor tricks instead (which don't have exactly the right
   semantics, but it's the best we can do).

   Example:
   int __REDIRECT(setpgrp, (__pid_t pid, __pid_t pgrp), setpgid); */
# 189 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/sys/cdefs.h" 3 4
/*
#elif __SOME_OTHER_COMPILER__

# define __REDIRECT(name, proto, alias) name proto; 	_Pragma("let " #name " = " #alias)
)
*/


/* GCC has various useful declarations that can be made with the
   `__attribute__' syntax.  All of the ways we use this do fine if
   they are omitted for compilers that don't understand it. */




/* At some point during the gcc 2.96 development the `malloc' attribute
   for functions was introduced.  We don't want to use it unconditionally
   (although this would be possible) since it generates warnings.  */






/* Tell the compiler which arguments to an allocation function
   indicate the size of the allocation.  */







/* At some point during the gcc 2.96 development the `pure' attribute
   for functions was introduced.  We don't want to use it unconditionally
   (although this would be possible) since it generates warnings.  */






/* This declaration tells the compiler that the value is constant.  */






/* At some point during the gcc 3.1 development the `used' attribute
   for functions was introduced.  We don't want to use it unconditionally
   (although this would be possible) since it generates warnings.  */
# 249 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/sys/cdefs.h" 3 4
/* Since version 3.2, gcc allows marking deprecated functions.  */






/* Since version 4.5, gcc also allows one to specify the message printed
   when a deprecated function is used.  clang claims to be gcc 4.2, but
   may also support this feature.  */
# 267 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/sys/cdefs.h" 3 4
/* At some point during the gcc 2.8 development the `format_arg' attribute
   for functions was introduced.  We don't want to use it unconditionally
   (although this would be possible) since it generates warnings.
   If several `format_arg' attributes are given for the same function, in
   gcc-3.0 and older, all but the last one are ignored.  In newer gccs,
   all designated arguments are considered.  */






/* At some point during the gcc 2.97 development the `strfmon' format
   attribute for functions was introduced.  We don't want to use it
   unconditionally (although this would be possible) since it
   generates warnings.  */







/* The nonull function attribute allows to mark pointer parameters which
   must not be NULL.  */






/* If fortification mode, we warn about unused results of certain
   function calls which can lead to problems.  */
# 313 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/sys/cdefs.h" 3 4
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
# 359 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/sys/cdefs.h" 3 4
/* GCC 4.3 and above allow passing all anonymous arguments of an
   __extern_always_inline function to some other vararg function.  */





/* It is possible to compile containing GCC extensions even if GCC is
   run in pedantic mode if the uses are carefully marked using the
   `__extension__' keyword.  But this is not generally available before
   version 2.8.  */




/* __restrict is known in EGCS 1.2 and above. */
# 383 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/sys/cdefs.h" 3 4
/* ISO C99 also allows to declare arrays as non-overlapping.  The syntax is
     array_name[restrict]
   GCC 3.1 supports this.  */
# 426 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/sys/cdefs.h" 3 4
/* Describes a char array whose address can safely be passed as the first
   argument to strncpy and strncat, as the char array is not necessarily
   a NUL-terminated string.  */
# 442 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/sys/cdefs.h" 3 4
# 1 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/bits/wordsize.h" 1 3 4
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
# 443 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/sys/cdefs.h" 2 3 4
# 1 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/bits/long-double.h" 1 3 4
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
# 444 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/sys/cdefs.h" 2 3 4
# 477 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/sys/cdefs.h" 3 4
/* __glibc_macro_warning (MESSAGE) issues warning MESSAGE.  This is
   intended for use in preprocessor macros.

   Note: MESSAGE must be a _single_ string; concatenation of string
   literals is not supported.  */
# 490 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/sys/cdefs.h" 3 4
/* Generic selection (ISO C11) is a C-only feature, available in GCC
   since version 4.9.  Previous versions do not provide generic
   selection, even though they might set __STDC_VERSION__ to 201112L,
   when in -std=c11 mode.  Thus, we must check for !defined __GNUC__
   when testing __STDC_VERSION__ for generic selection support.
   On the other hand, Clang also defines __GNUC__, so a clang-specific
   check is required to enable the use of generic selection.  */
# 429 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/features.h" 2 3 4


/* If we don't have __REDIRECT, prototypes will be missing if
   __USE_FILE_OFFSET64 but not __USE_LARGEFILE[64]. */







/* Decide whether we can define 'extern inline' functions in headers.  */







/* This is here only because every header file already includes this one.
   Get the definitions of all the appropriate `__stub_FUNCTION' symbols.
   <gnu/stubs.h> contains `#define __stub_FUNCTION' when FUNCTION is a stub
   that will always return failure (and set errno to ENOSYS).  */
# 1 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/gnu/stubs.h" 1 3 4
/* This file is automatically generated.
   This file selects the right generated file of `__stub_FUNCTION' macros
   based on the architecture being compiled for.  */






# 1 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/gnu/stubs-hard.h" 1 3 4
/* This file is automatically generated.
   It defines a symbol `__stub_FUNCTION' for each function
   in the C library which is a stub, meaning it will fail
   every time called, usually setting errno to ENOSYS.  */
# 11 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/gnu/stubs.h" 2 3 4
# 453 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/features.h" 2 3 4
# 34 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/bits/libc-header-start.h" 2 3 4

/* ISO/IEC TR 24731-2:2010 defines the __STDC_WANT_LIB_EXT2__
   macro.  */
# 45 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/bits/libc-header-start.h" 3 4
/* ISO/IEC TS 18661-1:2014 defines the __STDC_WANT_IEC_60559_BFP_EXT__
   macro.  */







/* ISO/IEC TS 18661-4:2015 defines the
   __STDC_WANT_IEC_60559_FUNCS_EXT__ macro.  */







/* ISO/IEC TS 18661-3:2015 defines the
   __STDC_WANT_IEC_60559_TYPES_EXT__ macro.  */
# 27 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/stdint.h" 2 3 4
# 1 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/bits/types.h" 1 3 4
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




# 1 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/features.h" 1 3 4
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
# 27 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/bits/types.h" 2 3 4
# 1 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/bits/wordsize.h" 1 3 4
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
# 28 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/bits/types.h" 2 3 4

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
   conventional uses of `long' or `long long' type modifiers match the
   types we define, even when a less-adorned type would be the same size.
   This matters for (somewhat) portably writing printf/scanf formats for
   these types, where using the appropriate l or ll format modifiers can
   make the typedefs and the formats match up across all GNU platforms.  If
   we used `long' when it's 64 bits where `long long' is expected, then the
   compiler would warn about the formats not matching the argument types,
   and the programmer changing them to shut up the compiler would break the
   program's portability.

   Here we assume what is presently the case in all the GCC configurations
   we support: long long is always 64 bits, long is always word/address size,
   and int is always 32 bits.  */
# 123 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/bits/types.h" 3 4
/* We want __extension__ before typedef's that use nonstandard base types
   such as `long long' in C89 mode.  */
# 140 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/bits/types.h" 3 4
# 1 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/bits/typesizes.h" 1 3 4
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
# 26 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/bits/typesizes.h" 3 4
/* See <bits/types.h> for the meaning of these macros.  This file exists so
   that <bits/types.h> need not vary across different GNU platforms.  */
# 79 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/bits/typesizes.h" 3 4
/* Number of descriptors that can fit in an `fd_set'.  */
# 141 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/bits/types.h" 2 3 4


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
__extension__ typedef struct { int __val[2]; } __fsid_t; /* Type of file system IDs.  */
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

/* Timer ID returned by `timer_create'.  */
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
# 28 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/stdint.h" 2 3 4
# 1 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/bits/wchar.h" 1 3 4
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
# 29 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/stdint.h" 2 3 4
# 1 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/bits/wordsize.h" 1 3 4
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
# 30 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/stdint.h" 2 3 4

/* Exact integral types.  */

/* Signed.  */
# 1 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/bits/stdint-intn.h" 1 3 4
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




# 1 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/bits/types.h" 1 3 4
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
# 23 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/bits/stdint-intn.h" 2 3 4

typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;
# 35 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/stdint.h" 2 3 4

/* Unsigned.  */
# 1 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/bits/stdint-uintn.h" 1 3 4
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




# 1 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/bits/types.h" 1 3 4
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
# 23 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/bits/stdint-uintn.h" 2 3 4

typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;
# 38 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/stdint.h" 2 3 4


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



/* Types for `void *' pointers.  */
# 93 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/stdint.h" 3 4
typedef int intptr_t;


typedef unsigned int uintptr_t;



/* Largest integral types.  */
typedef __intmax_t intmax_t;
typedef __uintmax_t uintmax_t;
# 113 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/stdint.h" 3 4
/* Limits of integral types.  */

/* Minimum of signed integral types.  */




/* Maximum of signed integral types.  */





/* Maximum of unsigned integral types.  */






/* Minimum of signed integral types having a minimum size.  */




/* Maximum of signed integral types having a minimum size.  */





/* Maximum of unsigned integral types having a minimum size.  */






/* Minimum of fast signed integral types having a minimum size.  */
# 161 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/stdint.h" 3 4
/* Maximum of fast signed integral types having a minimum size.  */
# 172 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/stdint.h" 3 4
/* Maximum of fast unsigned integral types having a minimum size.  */
# 184 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/stdint.h" 3 4
/* Values to test for integral types holding `void *' pointer.  */
# 196 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/stdint.h" 3 4
/* Minimum for largest signed integral type.  */

/* Maximum for largest signed integral type.  */


/* Maximum for largest unsigned integral type.  */



/* Limits of other integer types.  */

/* Limits of `ptrdiff_t' type.  */
# 221 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/stdint.h" 3 4
/* Limits of `sig_atomic_t'.  */



/* Limit of `size_t' type.  */
# 236 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/stdint.h" 3 4
/* Limits of `wchar_t'.  */

/* These constants might also be defined in <wchar.h>.  */




/* Limits of `wint_t'.  */



/* Signed.  */
# 257 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/stdint.h" 3 4
/* Unsigned.  */
# 267 "/work/linux/rv1109/src/buildroot/output/rockchip_rv1126_rv1109/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/stdint.h" 3 4
/* Maximal type.  */
# 10 "/work/linux/rv1109/src/prebuilts/gcc/linux-x86/arm/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/8.3.0/include/stdint.h" 2 3 4
# 23 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 2
# 32 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h"



# 34 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h"
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
# 103 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h"
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
    // M4_ARRAY_DESC("Coeff", "s32", M4_SIZE(1,3), M4_RANGE(-65535,65535), "0", M4_DIGIT(0), M4_DYNAMIC(0))
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
    // M4_ARRAY_DESC("fCoeff", "f32", M4_SIZE(1,3), M4_RANGE(-65535,65535), "0", M4_DIGIT(6), M4_DYNAMIC(0))
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
    // M4_ARRAY_DESC("fCoeff", "f32", M4_SIZE(1,4), M4_RANGE(-65535,65535), "0", M4_DIGIT(6), M4_DYNAMIC(0))
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
    // M4_ARRAY_DESC("fCoeff", "f32", M4_SIZE(1,2), M4_RANGE(-65535,65535), "0", M4_DIGIT(6), M4_DYNAMIC(0))
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
    // M4_ARRAY_DESC("fCoeff", "s16", M4_SIZE(1,3), M4_RANGE(-65535,65535), "0", M4_DIGIT(0), M4_DYNAMIC(0))
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
    // M4_ARRAY_DESC("uCoeff", "u16", M4_SIZE(17,17), M4_RANGE(0,10000), "1024", M4_DIGIT(0), M4_DYNAMIC(0))
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
    
# 511 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 3 4
   _Bool 
# 511 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h"
                               done;
} rk_aiq_uapi_sync_t;

extern int g_rkaiq_isp_hw_ver;
# 529 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h"

# 28 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/moduleinfo_head.h" 2



typedef struct CalibDb_Sensor_Module_s {
    // M4_NUMBER_DESC("FNumber", "f32", M4_RANGE(1,100), "1.6", M4_DIGIT(2),M4_HIDE(0))
    float FNumber;
    // M4_NUMBER_DESC("EFL", "f32", M4_RANGE(0,200), "3.5", M4_DIGIT(2),M4_HIDE(0))
    float EFL;
    // M4_NUMBER_DESC("LensT", "f32", M4_RANGE(0,100), "90", M4_DIGIT(2),M4_HIDE(0))
    float LensT;
    // M4_NUMBER_DESC("IRCutT", "f32", M4_RANGE(0,100), "90", M4_DIGIT(2),M4_HIDE(0))
    float IRCutT;
} CalibDb_Sensor_Module_t;

typedef struct CalibDb_Module_ParaV2_s {
    // M4_STRUCT_DESC("SensorModule", "normal_ui_style")
    CalibDb_Sensor_Module_t sensor_module;
} CalibDb_Module_ParaV2_t;


# 20 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbTypesV2.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/sensorinfo_head.h" 1
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

# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 29 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/sensorinfo_head.h" 2



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
    // M4_ENUM_DESC("GainMode", "CalibDb_ExpGainModeV2_t","EXPGAIN_MODE_LINEAR")
    CalibDb_ExpGainModeV2_t GainMode;

    // M4_ARRAY_DESC("GainRange", "f32", M4_SIZE(1,7), M4_RANGE(-65535,65535), "0", M4_DIGIT(4), M4_DYNAMIC(2))
    float* GainRange;//contains 7 params per line
    int GainRange_len;
} CalibDb_AecGainRangeV2_t;

typedef struct CalibDb_CISNormalTimeSetV2_s {
    // M4_NUMBER_DESC("TimeRegMin", "u16", M4_RANGE(1,100), "1", M4_DIGIT(0),M4_HIDE(0))
    uint16_t CISTimeRegMin;

    // M4_STRUCT_DESC("TimeRegMaxFac", "normal_ui_style")
    Cam2x1FloatMatrix_t CISLinTimeRegMaxFac;

    // M4_STRUCT_DESC("TimeRegOdevity", "normal_ui_style")
    Cam2x1FloatMatrix_t CISTimeRegOdevity;
} CalibDb_CISNormalTimeSetV2_t;

typedef struct CalibDb_CISHdrTimeSetV2_s {
    // M4_ENUM_DESC("name", "CalibDb_HdrFrmNumV2_t","HDR_TWO_FRAME")
    CalibDb_HdrFrmNumV2_t name;

    // M4_BOOL_DESC("CISTimeRegUnEqualEn", "0")
    
# 78 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/sensorinfo_head.h" 3 4
   _Bool 
# 78 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/sensorinfo_head.h"
                           CISTimeRegUnEqualEn;

    // M4_NUMBER_DESC("CISTimeRegMin", "u16", M4_RANGE(1,100), "1", M4_DIGIT(0),M4_HIDE(0))
    uint16_t CISTimeRegMin;

    // M4_STRUCT_DESC("CISHdrTimeRegSumFac", "normal_ui_style")
    Cam2x1FloatMatrix_t CISHdrTimeRegSumFac;

    // M4_STRUCT_DESC("CISTimeRegMax", "normal_ui_style")
    Cam1x3ShortMatrix_t CISTimeRegMax; //specially for Hdr that has limit on sframe/mframe, requiring max time line.value 0: no limit

    // M4_STRUCT_DESC("CISTimeRegOdevity", "normal_ui_style")
    Cam2x1FloatMatrix_t CISTimeRegOdevity;
} CalibDb_CISHdrTimeSetV2_t;

typedef struct CalibDb_CISTimeSet_CombV2_s {
    // M4_STRUCT_DESC("Linear", "normal_ui_style")
    CalibDb_CISNormalTimeSetV2_t Linear;

    // M4_STRUCT_LIST_DESC("Hdr", M4_SIZE(1,2),"normal_ui_style")
    CalibDb_CISHdrTimeSetV2_t Hdr[2];
} CalibDb_CISTimeSet_CombV2_t;

typedef struct CalibDb_AeRangeV2_s {
    // M4_NUMBER_DESC("Min", "f32", M4_RANGE(0,65535), "0", M4_DIGIT(3),M4_HIDE(0))
    float Min;

    // M4_NUMBER_DESC("Max", "f32", M4_RANGE(0,65535), "0", M4_DIGIT(3),M4_HIDE(0))
    float Max;
} CalibDb_AeRangeV2_t;

typedef struct CalibDb_CISGainSetV2_s {
    // M4_STRUCT_DESC("CISAgainRange", "normal_ui_style")
    CalibDb_AeRangeV2_t CISAgainRange; //sensor Again or LCG range

    // M4_STRUCT_DESC("CISExtraAgainRange", "normal_ui_style")
    CalibDb_AeRangeV2_t CISExtraAgainRange; //add for HDR-DCG MODE, HCG range

    // M4_STRUCT_DESC("CISDgainRange", "normal_ui_style")
    CalibDb_AeRangeV2_t CISDgainRange; //sensor Dgain

    // M4_STRUCT_DESC("CISIspDgainRange", "normal_ui_style")
    CalibDb_AeRangeV2_t CISIspDgainRange; //Isp Dgain

    // M4_BOOL_DESC("CISHdrGainIndSetEn", "1")
    
# 123 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/sensorinfo_head.h" 3 4
   _Bool 
# 123 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/sensorinfo_head.h"
                          CISHdrGainIndSetEn; //bit 0:use the same value; bit 1: support use different gain value
} CalibDb_CISGainSetV2_t;

typedef struct CalibDb_CISHdrSetV2_s {
    // M4_BOOL_DESC("hdr_en", "0")
    
# 128 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/sensorinfo_head.h" 3 4
   _Bool 
# 128 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/sensorinfo_head.h"
        hdr_en;

    // M4_ENUM_DESC("hdr_mode", "rk_aiq_isp_hdr_mode_t","RK_AIQ_ISP_HDR_MODE_2_LINE_HDR")
    rk_aiq_isp_hdr_mode_t hdr_mode;

    // M4_ENUM_DESC("line_mode", "rk_aiq_sensor_hdr_line_mode_t","RK_AIQ_SENSOR_HDR_LINE_MODE_STAGGER")
    rk_aiq_sensor_hdr_line_mode_t line_mode;
} CalibDb_CISHdrSetV2_t;

typedef struct CalibDb_Dcg_ParamsV2_s {
    // M4_BOOL_DESC("support_en", "0")
    
# 139 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/sensorinfo_head.h" 3 4
   _Bool 
# 139 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/sensorinfo_head.h"
                       support_en;

    // M4_ENUM_DESC("dcg_optype", "RKAiqOPMode_t","RK_AIQ_OP_MODE_AUTO")
    RKAiqOPMode_t dcg_optype;

    // M4_STRUCT_DESC("dcg_mode", "normal_ui_style")
    Cam1x3IntMatrix_t dcg_mode;

    // M4_NUMBER_DESC("dcg_ratio", "f32", M4_RANGE(1,100), "1", M4_DIGIT(2),M4_HIDE(0))
    float dcg_ratio;

    // M4_BOOL_DESC("sync_switch", "1")
    
# 151 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/sensorinfo_head.h" 3 4
   _Bool 
# 151 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/sensorinfo_head.h"
                       sync_switch;

    // M4_NUMBER_DESC("lcg2hcg_gain_th", "f32", M4_RANGE(1,4096), "32", M4_DIGIT(2),M4_HIDE(0))
    float lcg2hcg_gain_th;

    // M4_NUMBER_DESC("hcg2lcg_gain_th", "f32", M4_RANGE(1,4096), "16", M4_DIGIT(2),M4_HIDE(0))
    float hcg2lcg_gain_th;
} CalibDb_Dcg_ParamsV2_t;

typedef struct CalibDb_DcgSetV2_s {
    // M4_STRUCT_DESC("Linear", "normal_ui_style")
    CalibDb_Dcg_ParamsV2_t Linear;

    // M4_STRUCT_DESC("Hdr", "normal_ui_style")
    CalibDb_Dcg_ParamsV2_t Hdr;
} CalibDb_DcgSetV2_t;

typedef struct CalibDb_ExpUpdateV2_s {
    // M4_NUMBER_DESC("time_update", "s32", M4_RANGE(0,10), "2", M4_DIGIT(0),M4_HIDE(0))
    int time_update;

    // M4_NUMBER_DESC("gain_update", "s32", M4_RANGE(0,10), "2", M4_DIGIT(0),M4_HIDE(0))
    int gain_update;

    // M4_NUMBER_DESC("dcg_update", "s32", M4_RANGE(0,10), "2", M4_DIGIT(0),M4_HIDE(0))
    int dcg_update;
} CalibDb_ExpUpdateV2_t;

typedef struct CalibDb_ExpUpdate_CombV2_s {
    // M4_STRUCT_DESC("Linear", "normal_ui_style")
    CalibDb_ExpUpdateV2_t Linear;

    // M4_STRUCT_DESC("Hdr", "normal_ui_style")
    CalibDb_ExpUpdateV2_t Hdr;
} CalibDb_ExpUpdate_CombV2_t;

typedef struct CalibDb_ResInfoV2_s {
    // M4_NUMBER_DESC("width", "u16", M4_RANGE(0,65535), "0", M4_DIGIT(0),M4_HIDE(0))
    uint16_t width;
    // M4_NUMBER_DESC("height", "u16", M4_RANGE(0,65535), "0", M4_DIGIT(0),M4_HIDE(0))
    uint16_t height;
} CalibDb_ResInfoV2_t;


typedef struct CalibDb_Sensor_ParaV2_s {
    // M4_STRUCT_DESC("Resolution", "normal_ui_style")
    CalibDb_ResInfoV2_t resolution;

    // M4_STRUCT_DESC("Gain2Reg", "normal_ui_style")
    CalibDb_AecGainRangeV2_t Gain2Reg;

    // M4_STRUCT_DESC("Time2Reg", "normal_ui_style")
    Cam1x4FloatMatrix_t Time2Reg;

    // M4_STRUCT_DESC("CISGainSet", "normal_ui_style")
    CalibDb_CISGainSetV2_t CISGainSet;

    // M4_STRUCT_DESC("CISTimeSet", "normal_ui_style")
    CalibDb_CISTimeSet_CombV2_t CISTimeSet;

    // M4_STRUCT_DESC("CISHdrSet", "normal_ui_style")
    CalibDb_CISHdrSetV2_t CISHdrSet;

    // M4_STRUCT_DESC("CISDcgSet", "normal_ui_style")
    CalibDb_DcgSetV2_t CISDcgSet;

    // M4_STRUCT_DESC("CISExpUpdate", "normal_ui_style")
    CalibDb_ExpUpdate_CombV2_t CISExpUpdate;

    // M4_NUMBER_DESC("CISMinFps", "f32", M4_RANGE(1,100), "10", M4_DIGIT(2),M4_HIDE(0))
    float CISMinFps;

    // M4_NUMBER_DESC("CISFlip", "u8", M4_RANGE(0,3), "0", M4_DIGIT(0),M4_HIDE(0))
    uint8_t CISFlip; // bit 0 : mirror, bit 1 : flip , range[0,3]
} CalibDb_Sensor_ParaV2_t;


# 21 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbTypesV2.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/sys_static_cfg_head.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/sys_static_cfg_head.h" 2



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
    // M4_BOOL_DESC("enable", "0")
    
# 67 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/sys_static_cfg_head.h" 3 4
   _Bool 
# 67 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/sys_static_cfg_head.h"
                       enable;

    // M4_STRING_DESC("EnableAlgos", M4_SIZE(1,1), M4_RANGE(0, 32), "ENABLE_AE", M4_DYNAMIC(1))
    EnableAlgoType_t* enable_algos;
    int16_t enable_algos_len;
} CalibDb_AlgoSwitch_t;

typedef struct CalibDb_SysStaticCfg_ParaV2_s {
    // M4_STRUCT_DESC("AlgoSwitch", "normal_ui_style")
    CalibDb_AlgoSwitch_t algoSwitch;
} CalibDb_SysStaticCfg_ParaV2_t;


# 22 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbTypesV2.h" 2
# 30 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbTypesV2.h"
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/ablc_head.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/ablc_head.h" 2







/*****************************************************************************/
/**
 * @brief   ISP2.0 ABLC Config Params
 */
/*****************************************************************************/

typedef struct Blc_data_s {
    // M4_ARRAY_DESC("ISO", "f32", M4_SIZE(1,100), M4_RANGE(0,10000000), "50",M4_DIGIT(4), M4_DYNAMIC(1))
    float* ISO;
    int ISO_len;
    // M4_ARRAY_DESC("R_Channel", "f32", M4_SIZE(1,100), M4_RANGE(0,4095), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* R_Channel;
    int R_Channel_len;
    // M4_ARRAY_DESC("Gr_Channel", "f32", M4_SIZE(1,100), M4_RANGE(0,4095), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* Gr_Channel;
    int Gr_Channel_len;
    // M4_ARRAY_DESC("Gb_Channel", "f32", M4_SIZE(1,100), M4_RANGE(0,4095), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* Gb_Channel;
    int Gb_Channel_len;
    // M4_ARRAY_DESC("B_Channel", "f32", M4_SIZE(1,100), M4_RANGE(0,4095), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* B_Channel;
    int B_Channel_len;
} Blc_data_t;

typedef struct AblcParaV2_s {
    // M4_BOOL_DESC("enable", "1")
    
# 57 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/ablc_head.h" 3 4
   _Bool 
# 57 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/ablc_head.h"
        enable;
    // M4_ARRAY_TABLE_DESC("BLC_Data", "array_table_ui", "none")
    Blc_data_t BLC_Data;
} AblcParaV2_t;


typedef struct CalibDbV2_Ablc_s {
    // M4_STRUCT_DESC("BlcTuningPara", "normal_ui_style")
    AblcParaV2_t BlcTuningPara;
    // M4_STRUCT_DESC("Blc1TuningPara", "normal_ui_style")
    AblcParaV2_t Blc1TuningPara;
} CalibDbV2_Ablc_t;



# 22 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adegamma_head.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adegamma_head.h" 2





/*****************************************************************************/
/**
 * @brief   ISP2.0 Adegamma Config Params
 */
/*****************************************************************************/

typedef struct AdegmmaParaV2_s {
    // M4_BOOL_DESC("degamma_en", "0")
    
# 37 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adegamma_head.h" 3 4
   _Bool 
# 37 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adegamma_head.h"
        degamma_en;
    // M4_ARRAY_DESC("X_axis", "u16", M4_SIZE(1,17),  M4_RANGE(0, 4095), "[0,256,512,768,1024,1280,1536,1792,2048,2304,2560,2816,3072,3328,3584,3840,4096]", M4_DIGIT(0), M4_DYNAMIC(0))
    int X_axis[17];
    // M4_ARRAY_DESC("curve_R", "u16", M4_SIZE(1,17),  M4_RANGE(0, 4095), "[0,256,512,768,1024,1280,1536,1792,2048,2304,2560,2816,3072,3328,3584,3840,4096]", M4_DIGIT(0), M4_DYNAMIC(0))
    int curve_R[17];
    // M4_ARRAY_DESC("curve_G", "u16", M4_SIZE(1,17),  M4_RANGE(0, 4095), "[0,256,512,768,1024,1280,1536,1792,2048,2304,2560,2816,3072,3328,3584,3840,4096]", M4_DIGIT(0), M4_DYNAMIC(0))
    int curve_G[17];
    // M4_ARRAY_DESC("curve_B", "u16", M4_SIZE(1,17),  M4_RANGE(0, 4095), "[0,256,512,768,1024,1280,1536,1792,2048,2304,2560,2816,3072,3328,3584,3840,4096]", M4_DIGIT(0), M4_DYNAMIC(0))
    int curve_B[17];
} AdegmmaParaV2_t;

typedef struct CalibDbV2_Adegmma_s {
    // M4_STRUCT_DESC("DegammaTuningPara", "normal_ui_style")
    AdegmmaParaV2_t DegammaTuningPara;
} CalibDbV2_Adegmma_t;



# 23 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h" 2








typedef struct DehazeData_s {
    // M4_ARRAY_DESC("ISO", "f32", M4_SIZE(1,100), M4_RANGE(0,10000000), "50",M4_DIGIT(4), M4_DYNAMIC(1))
    float* ISO;
    int ISO_len;
    // M4_ARRAY_DESC("dc_min_th", "f32", M4_SIZE(1,100), M4_RANGE(0,255), "64",M4_DIGIT(4), M4_DYNAMIC(1))
    float* dc_min_th;
    int dc_min_th_len;
    // M4_ARRAY_DESC("dc_max_th", "f32", M4_SIZE(1,100), M4_RANGE(0,255), "192",M4_DIGIT(4), M4_DYNAMIC(1))
    float* dc_max_th;
    int dc_max_th_len;
    // M4_ARRAY_DESC("yhist_th", "f32", M4_SIZE(1,100), M4_RANGE(0,255), "249",M4_DIGIT(4), M4_DYNAMIC(1))
    float* yhist_th;
    int yhist_th_len;
    // M4_ARRAY_DESC("yblk_th", "f32", M4_SIZE(1,100), M4_RANGE(0,512), "0.002",M4_DIGIT(4), M4_DYNAMIC(1))
    float* yblk_th;
    int yblk_th_len;
    // M4_ARRAY_DESC("dark_th", "f32", M4_SIZE(1,100), M4_RANGE(0,255), "250",M4_DIGIT(4), M4_DYNAMIC(1))
    float* dark_th;
    int dark_th_len;
    // M4_ARRAY_DESC("bright_min", "f32", M4_SIZE(1,100), M4_RANGE(0,255), "180",M4_DIGIT(4), M4_DYNAMIC(1))
    float* bright_min;
    int bright_min_len;
    // M4_ARRAY_DESC("bright_max", "f32", M4_SIZE(1,100), M4_RANGE(0,255), "240",M4_DIGIT(4), M4_DYNAMIC(1))
    float* bright_max;
    int bright_max_len;
    // M4_ARRAY_DESC("wt_max", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.9",M4_DIGIT(4), M4_DYNAMIC(1))
    float* wt_max;
    int wt_max_len;
    // M4_ARRAY_DESC("air_min", "f32", M4_SIZE(1,100), M4_RANGE(0,255), "200",M4_DIGIT(4), M4_DYNAMIC(1))
    float* air_min;
    int air_min_len;
    // M4_ARRAY_DESC("air_max", "f32", M4_SIZE(1,100), M4_RANGE(0,255), "250",M4_DIGIT(4), M4_DYNAMIC(1))
    float* air_max;
    int air_max_len;
    // M4_ARRAY_DESC("tmax_base", "f32", M4_SIZE(1,100), M4_RANGE(0,255), "125",M4_DIGIT(4), M4_DYNAMIC(1))
    float* tmax_base;
    int tmax_base_len;
    // M4_ARRAY_DESC("tmax_off", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.1",M4_DIGIT(4), M4_DYNAMIC(1))
    float* tmax_off;
    int tmax_off_len;
    // M4_ARRAY_DESC("tmax_max", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.8",M4_DIGIT(4), M4_DYNAMIC(1))
    float* tmax_max;
    int tmax_max_len;
    // M4_ARRAY_DESC("cfg_wt", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.8",M4_DIGIT(4), M4_DYNAMIC(1))
    float* cfg_wt;
    int cfg_wt_len;
    // M4_ARRAY_DESC("cfg_air", "f32", M4_SIZE(1,100), M4_RANGE(0,255), "210",M4_DIGIT(4), M4_DYNAMIC(1))
    float* cfg_air;
    int cfg_air_len;
    // M4_ARRAY_DESC("cfg_tmax", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.2",M4_DIGIT(4), M4_DYNAMIC(1))
    float* cfg_tmax;
    int cfg_tmax_len;
    // M4_ARRAY_DESC("dc_thed", "f32", M4_SIZE(1,100), M4_RANGE(0,255), "2",M4_DIGIT(4), M4_DYNAMIC(1))
    float* dc_thed;
    int dc_thed_len;
    // M4_ARRAY_DESC("dc_weitcur", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "1",M4_DIGIT(4), M4_DYNAMIC(1))
    float* dc_weitcur;
    int dc_weitcur_len;
    // M4_ARRAY_DESC("air_thed", "f32", M4_SIZE(1,100), M4_RANGE(0,255), "2",M4_DIGIT(4), M4_DYNAMIC(1))
    float* air_thed;
    int air_thed_len;
    // M4_ARRAY_DESC("air_weitcur", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.14",M4_DIGIT(4), M4_DYNAMIC(1))
    float* air_weitcur;
    int air_weitcur_len;
} DehazeData_t;

typedef struct Dehaze_Setting_V20_s {
    // M4_BOOL_DESC("en", "1")
    
# 100 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h" 3 4
   _Bool 
# 100 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h"
        en;
    // M4_NUMBER_DESC("stab_fnum", "f32", M4_RANGE(0,31), "8.0", M4_DIGIT(4))
    float stab_fnum;
    // M4_NUMBER_DESC("sigma", "f32", M4_RANGE(0,255), "6.0", M4_DIGIT(4))
    float sigma;
    // M4_NUMBER_DESC("wt_sigma", "f32", M4_RANGE(0,256), "8.0", M4_DIGIT(4))
    float wt_sigma;
    // M4_NUMBER_DESC("air_sigma", "f32", M4_RANGE(0,255), "120.0", M4_DIGIT(4))
    float air_sigma;
    // M4_NUMBER_DESC("tmax_sigma", "f32", M4_RANGE(0,1), "0.0100", M4_DIGIT(4))
    float tmax_sigma;
    // M4_ARRAY_TABLE_DESC("DehazeData", "array_table_ui", "none")
    DehazeData_t DehazeData;
} Dehaze_Setting_V20_t;

typedef struct EnhanceData_s {
    // M4_ARRAY_DESC("ISO", "f32", M4_SIZE(1,100), M4_RANGE(0,10000000), "50",M4_DIGIT(4), M4_DYNAMIC(1))
    float* ISO;
    int ISO_len;
    // M4_ARRAY_DESC("enhance_value", "f32", M4_SIZE(1,100), M4_RANGE(0,32), "1",M4_DIGIT(4), M4_DYNAMIC(1))
    float* enhance_value;
    int enhance_value_len;
} EnhanceData_t;

typedef struct Enhance_Setting_V20_s {
    // M4_BOOL_DESC("en", "1")
    
# 126 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h" 3 4
   _Bool 
# 126 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h"
        en;
    // M4_ARRAY_TABLE_DESC("EnhanceData", "array_table_ui", "none")
    EnhanceData_t EnhanceData;
} Enhance_Setting_V20_t;

typedef struct HistData_s {
    // M4_ARRAY_DESC("ISO", "f32", M4_SIZE(1,100), M4_RANGE(0,10000000), "50",M4_DIGIT(4), M4_DYNAMIC(1))
    float* ISO;
    int ISO_len;
    // M4_ARRAY_DESC("hist_gratio", "f32", M4_SIZE(1,100), M4_RANGE(0,32), "2",M4_DIGIT(4), M4_DYNAMIC(1))
    float* hist_gratio;
    int hist_gratio_len;
    // M4_ARRAY_DESC("hist_th_off", "f32", M4_SIZE(1,100), M4_RANGE(0,255), "64",M4_DIGIT(4), M4_DYNAMIC(1))
    float* hist_th_off;
    int hist_th_off_len;
    // M4_ARRAY_DESC("hist_k", "f32", M4_SIZE(1,100), M4_RANGE(0,8), "2",M4_DIGIT(4), M4_DYNAMIC(1))
    float* hist_k;
    int hist_k_len;
    // M4_ARRAY_DESC("hist_min", "f32", M4_SIZE(1,100), M4_RANGE(0,2), "0.016",M4_DIGIT(4), M4_DYNAMIC(1))
    float* hist_min;
    int hist_min_len;
    // M4_ARRAY_DESC("hist_scale", "f32", M4_SIZE(1,100), M4_RANGE(0,32), "0.09",M4_DIGIT(4), M4_DYNAMIC(1))
    float* hist_scale;
    int hist_scale_len;
    // M4_ARRAY_DESC("cfg_gratio", "f32", M4_SIZE(1,100), M4_RANGE(0,32), "2",M4_DIGIT(4), M4_DYNAMIC(1))
    float* cfg_gratio;
    int cfg_gratio_len;
} HistData_t;

typedef struct Hist_setting_V20_s {
    // M4_BOOL_DESC("en", "1")
    
# 157 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h" 3 4
   _Bool 
# 157 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h"
        en;
    // M4_BOOL_DESC("hist_para_en", "1")
    
# 159 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h" 3 4
   _Bool 
# 159 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h"
         hist_para_en;
    // M4_BOOL_DESC("hist_channel", "1")
    
# 161 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h" 3 4
   _Bool 
# 161 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h"
         hist_channel;
    // M4_ARRAY_TABLE_DESC("HistData", "array_table_ui","none")
    HistData_t HistData;
} Hist_setting_V20_t;

typedef struct CalibDbDehazeV20_s {
    // M4_BOOL_DESC("Enable", "1")
    
# 168 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h" 3 4
   _Bool 
# 168 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h"
        Enable;
    // M4_NUMBER_DESC("cfg_alpha", "f32", M4_RANGE(0,1), "1", M4_DIGIT(4))
    float cfg_alpha;
    // M4_NUMBER_DESC("ByPassThr", "f32", M4_RANGE(0,1), "0", M4_DIGIT(4))
    float ByPassThr;
    // M4_STRUCT_DESC("dehaze_setting", "normal_ui_style")
    Dehaze_Setting_V20_t dehaze_setting;
    // M4_STRUCT_DESC("enhance_setting", "normal_ui_style")
    Enhance_Setting_V20_t enhance_setting;
    // M4_STRUCT_DESC("hist_setting", "normal_ui_style")
    Hist_setting_V20_t hist_setting;
} CalibDbDehazeV20_t;

typedef struct CalibDbV2_dehaze_V20_s {
    // M4_STRUCT_DESC("DehazeTuningPara", "normal_ui_style")
    CalibDbDehazeV20_t DehazeTuningPara;
} CalibDbV2_dehaze_V20_t;

typedef struct DehazeDataV21_s {
    // M4_ARRAY_DESC("EnvLv", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* EnvLv;
    int EnvLv_len;
    // M4_ARRAY_DESC("dc_min_th", "f32", M4_SIZE(1,100), M4_RANGE(0,255), "64",M4_DIGIT(4), M4_DYNAMIC(1))
    float* dc_min_th;
    int dc_min_th_len;
    // M4_ARRAY_DESC("dc_max_th", "f32", M4_SIZE(1,100), M4_RANGE(0,255), "192",M4_DIGIT(4), M4_DYNAMIC(1))
    float* dc_max_th;
    int dc_max_th_len;
    // M4_ARRAY_DESC("yhist_th", "f32", M4_SIZE(1,100), M4_RANGE(0,255), "249",M4_DIGIT(4), M4_DYNAMIC(1))
    float* yhist_th;
    int yhist_th_len;
    // M4_ARRAY_DESC("yblk_th", "f32", M4_SIZE(1,100), M4_RANGE(0,512), "0.002",M4_DIGIT(4), M4_DYNAMIC(1))
    float* yblk_th;
    int yblk_th_len;
    // M4_ARRAY_DESC("dark_th", "f32", M4_SIZE(1,100), M4_RANGE(0,255), "250",M4_DIGIT(4), M4_DYNAMIC(1))
    float* dark_th;
    int dark_th_len;
    // M4_ARRAY_DESC("bright_min", "f32", M4_SIZE(1,100), M4_RANGE(0,255), "180",M4_DIGIT(4), M4_DYNAMIC(1))
    float* bright_min;
    int bright_min_len;
    // M4_ARRAY_DESC("bright_max", "f32", M4_SIZE(1,100), M4_RANGE(0,255), "240",M4_DIGIT(4), M4_DYNAMIC(1))
    float* bright_max;
    int bright_max_len;
    // M4_ARRAY_DESC("wt_max", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.9",M4_DIGIT(4), M4_DYNAMIC(1))
    float* wt_max;
    int wt_max_len;
    // M4_ARRAY_DESC("air_min", "f32", M4_SIZE(1,100), M4_RANGE(0,255), "200",M4_DIGIT(4), M4_DYNAMIC(1))
    float* air_min;
    int air_min_len;
    // M4_ARRAY_DESC("air_max", "f32", M4_SIZE(1,100), M4_RANGE(0,255), "250",M4_DIGIT(4), M4_DYNAMIC(1))
    float* air_max;
    int air_max_len;
    // M4_ARRAY_DESC("tmax_base", "f32", M4_SIZE(1,100), M4_RANGE(0,255), "125",M4_DIGIT(4), M4_DYNAMIC(1))
    float* tmax_base;
    int tmax_base_len;
    // M4_ARRAY_DESC("tmax_off", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.1",M4_DIGIT(4), M4_DYNAMIC(1))
    float* tmax_off;
    int tmax_off_len;
    // M4_ARRAY_DESC("tmax_max", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.8",M4_DIGIT(4), M4_DYNAMIC(1))
    float* tmax_max;
    int tmax_max_len;
    // M4_ARRAY_DESC("cfg_wt", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.8",M4_DIGIT(4), M4_DYNAMIC(1))
    float* cfg_wt;
    int cfg_wt_len;
    // M4_ARRAY_DESC("cfg_air", "f32", M4_SIZE(1,100), M4_RANGE(0,255), "210",M4_DIGIT(4), M4_DYNAMIC(1))
    float* cfg_air;
    int cfg_air_len;
    // M4_ARRAY_DESC("cfg_tmax", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.2",M4_DIGIT(4), M4_DYNAMIC(1))
    float* cfg_tmax;
    int cfg_tmax_len;
    // M4_ARRAY_DESC("dc_weitcur", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "1",M4_DIGIT(4), M4_DYNAMIC(1))
    float* dc_weitcur;
    int dc_weitcur_len;
    // M4_ARRAY_DESC("bf_weight", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.5",M4_DIGIT(4), M4_DYNAMIC(1))
    float* bf_weight;
    int bf_weight_len;
    // M4_ARRAY_DESC("range_sigma", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.04",M4_DIGIT(4), M4_DYNAMIC(1))
    float* range_sigma;
    int range_sigma_len;
    // M4_ARRAY_DESC("space_sigma_pre", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.4",M4_DIGIT(4), M4_DYNAMIC(1))
    float* space_sigma_pre;
    int space_sigma_pre_len;
    // M4_ARRAY_DESC("space_sigma_cur", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.8",M4_DIGIT(4), M4_DYNAMIC(1))
    float* space_sigma_cur;
    int space_sigma_cur_len;
} DehazeDataV21_t;

typedef struct Dehaze_Setting_V21_s {
    // M4_BOOL_DESC("en", "1")
    
# 257 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h" 3 4
   _Bool 
# 257 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h"
        en;
    // M4_BOOL_DESC("air_lc_en", "1")
    
# 259 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h" 3 4
   _Bool 
# 259 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h"
        air_lc_en;
    // M4_NUMBER_DESC("stab_fnum", "f32", M4_RANGE(0,31), "8.0", M4_DIGIT(4))
    float stab_fnum;
    // M4_NUMBER_DESC("sigma", "f32", M4_RANGE(0,255), "6.0", M4_DIGIT(4))
    float sigma;
    // M4_NUMBER_DESC("wt_sigma", "f32", M4_RANGE(0,256), "8.0", M4_DIGIT(4))
    float wt_sigma;
    // M4_NUMBER_DESC("air_sigma", "f32", M4_RANGE(0,255), "120.0", M4_DIGIT(4))
    float air_sigma;
    // M4_NUMBER_DESC("tmax_sigma", "f32", M4_RANGE(0,1), "0.0100", M4_DIGIT(4))
    float tmax_sigma;
    // M4_NUMBER_DESC("pre_wet", "f32", M4_RANGE(0,1), "0.0100", M4_DIGIT(4))
    float pre_wet;
    // M4_ARRAY_TABLE_DESC("DehazeData", "array_table_ui", "none")
    DehazeDataV21_t DehazeData;
} Dehaze_Setting_V21_t;

typedef struct EnhanceDataV21_s {
    // M4_ARRAY_DESC("EnvLv", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* EnvLv;
    int EnvLv_len;
    // M4_ARRAY_DESC("enhance_value", "f32", M4_SIZE(1,100), M4_RANGE(0,32), "1",M4_DIGIT(4), M4_DYNAMIC(1))
    float* enhance_value;
    int enhance_value_len;
    // M4_ARRAY_DESC("enhance_chroma", "f32", M4_SIZE(1,100), M4_RANGE(0,32), "1",M4_DIGIT(4), M4_DYNAMIC(1))
    float* enhance_chroma;
    int enhance_chroma_len;
} EnhanceDataV21_t;

typedef struct Enhance_Setting_V21_s {
    // M4_BOOL_DESC("en", "1")
    
# 290 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h" 3 4
   _Bool 
# 290 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h"
        en;
    // M4_ARRAY_DESC("enhance_curve", "f32", M4_SIZE(1,17),  M4_RANGE(0, 1024), "[0,64,128,192,256,320,384,448,512,576,640,704,768,832,896,960,1023]", M4_DIGIT(0), M4_DYNAMIC(0))
    float enhance_curve[17];
    // M4_ARRAY_TABLE_DESC("EnhanceData", "array_table_ui", "none")
    EnhanceDataV21_t EnhanceData;
} Enhance_Setting_V21_t;

typedef struct HistDataV21_s {
    // M4_ARRAY_DESC("EnvLv", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* EnvLv;
    int EnvLv_len;
    // M4_ARRAY_DESC("hist_gratio", "f32", M4_SIZE(1,100), M4_RANGE(0,32), "2",M4_DIGIT(4), M4_DYNAMIC(1))
    float* hist_gratio;
    int hist_gratio_len;
    // M4_ARRAY_DESC("hist_th_off", "f32", M4_SIZE(1,100), M4_RANGE(0,255), "64",M4_DIGIT(4), M4_DYNAMIC(1))
    float* hist_th_off;
    int hist_th_off_len;
    // M4_ARRAY_DESC("hist_k", "f32", M4_SIZE(1,100), M4_RANGE(0,8), "2",M4_DIGIT(4), M4_DYNAMIC(1))
    float* hist_k;
    int hist_k_len;
    // M4_ARRAY_DESC("hist_min", "f32", M4_SIZE(1,100), M4_RANGE(0,2), "0.016",M4_DIGIT(4), M4_DYNAMIC(1))
    float* hist_min;
    int hist_min_len;
    // M4_ARRAY_DESC("hist_scale", "f32", M4_SIZE(1,100), M4_RANGE(0,32), "0.09",M4_DIGIT(4), M4_DYNAMIC(1))
    float* hist_scale;
    int hist_scale_len;
    // M4_ARRAY_DESC("cfg_gratio", "f32", M4_SIZE(1,100), M4_RANGE(0,32), "2",M4_DIGIT(4), M4_DYNAMIC(1))
    float* cfg_gratio;
    int cfg_gratio_len;
} HistDataV21_t;

typedef struct Hist_setting_V21_s {
    // M4_BOOL_DESC("en", "1")
    
# 323 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h" 3 4
   _Bool 
# 323 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h"
        en;
    // M4_BOOL_DESC("hist_para_en", "1")
    
# 325 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h" 3 4
   _Bool 
# 325 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h"
        hist_para_en;
    // M4_ARRAY_TABLE_DESC("HistData", "array_table_ui","none")
    HistDataV21_t HistData;
} Hist_setting_V21_t;

typedef struct CalibDbDehazeV21_s {
    // M4_BOOL_DESC("en", "1")
    
# 332 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h" 3 4
   _Bool 
# 332 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adehaze_head.h"
        Enable;
    // M4_NUMBER_DESC("cfg_alpha", "f32", M4_RANGE(0,1), "1", M4_DIGIT(4))
    float cfg_alpha;
    // M4_NUMBER_DESC("ByPassThr", "f32", M4_RANGE(0,1), "0", M4_DIGIT(4))
    float ByPassThr;
    // M4_STRUCT_DESC("dehaze_setting", "normal_ui_style")
    Dehaze_Setting_V21_t dehaze_setting;
    // M4_STRUCT_DESC("enhance_setting", "normal_ui_style")
    Enhance_Setting_V21_t enhance_setting;
    // M4_STRUCT_DESC("hist_setting", "normal_ui_style")
    Hist_setting_V21_t hist_setting;
} CalibDbDehazeV21_t;

typedef struct CalibDbV2_dehaze_V21_s {
    // M4_STRUCT_DESC("DehazeTuningPara", "normal_ui_style")
    CalibDbDehazeV21_t DehazeTuningPara;
} CalibDbV2_dehaze_V21_t;

typedef struct CalibDbV2_dehaze_V30_s {
    // M4_STRUCT_DESC("DehazeTuningPara", "normal_ui_style")
    CalibDbDehazeV21_t DehazeTuningPara;
} CalibDbV2_dehaze_V30_t;



# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h" 2






typedef struct CalibDb_Dpcc_set_RK_V20_s {
    // M4_ARRAY_DESC("RK_enable", "u8", M4_SIZE(1,13),  M4_RANGE(0, 1), "[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char RK_enable[13];
    // M4_ARRAY_DESC("rb_sw_mindis", "u8", M4_SIZE(1,13),  M4_RANGE(0, 255), "[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char rb_sw_mindis[13];
    // M4_ARRAY_DESC("g_sw_mindis", "u8", M4_SIZE(1,13),  M4_RANGE(0, 255), "[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char g_sw_mindis[13];
    // M4_ARRAY_DESC("sw_dis_scale_min", "u8", M4_SIZE(1,13),  M4_RANGE(0, 63), "[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char sw_dis_scale_min[13];
    // M4_ARRAY_DESC("sw_dis_scale_max", "u8", M4_SIZE(1,13),  M4_RANGE(0, 63), "[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char sw_dis_scale_max[13];
} CalibDb_Dpcc_set_RK_V20_t;

typedef struct CalibDb_Dpcc_set_LC_V20_s {
    // M4_ARRAY_DESC("LC_enable", "u8", M4_SIZE(1,13),  M4_RANGE(0, 1), "[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char LC_enable[13];
    // M4_ARRAY_DESC("rb_line_thr", "u8", M4_SIZE(1,13),  M4_RANGE(0, 255), "[8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,8,8,8]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char rb_line_thr[13];
    // M4_ARRAY_DESC("g_line_thr", "u8", M4_SIZE(1,13),  M4_RANGE(0, 255), "[8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,8,8,8]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char g_line_thr[13];
    // M4_ARRAY_DESC("rb_line_mad_fac", "u8", M4_SIZE(1,13),  M4_RANGE(0, 63), "[4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,4,4,4]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char rb_line_mad_fac[13];
    // M4_ARRAY_DESC("g_line_mad_fac", "u8", M4_SIZE(1,13),  M4_RANGE(0, 63), "[4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,4,4,4]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char g_line_mad_fac[13];
} CalibDb_Dpcc_set_LC_V20_t;

typedef struct CalibDb_Dpcc_set_PG_V20_s {
    // M4_ARRAY_DESC("PG_enable", "u8", M4_SIZE(1,13),  M4_RANGE(0, 1), "[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char PG_enable[13];
    // M4_ARRAY_DESC("rb_pg_fac", "u8", M4_SIZE(1,13),  M4_RANGE(0, 63), "[4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,4,4,4]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char rb_pg_fac[13];
    // M4_ARRAY_DESC("g_pg_fac", "u8", M4_SIZE(1,13),  M4_RANGE(0, 63), "[3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,3,3,3]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char g_pg_fac[13];
} CalibDb_Dpcc_set_PG_V20_t;

typedef struct CalibDb_Dpcc_set_RND_V20_s {
    // M4_ARRAY_DESC("RND_enable", "u8", M4_SIZE(1,13),  M4_RANGE(0, 1), "[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char RND_enable[13];
    // M4_ARRAY_DESC("rb_rnd_thr", "u8", M4_SIZE(1,13),  M4_RANGE(0, 255), "[8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,8,8,8]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char rb_rnd_thr[13];
    // M4_ARRAY_DESC("g_rnd_thr", "u8", M4_SIZE(1,13),  M4_RANGE(0, 255), "[8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,8,8,8]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char g_rnd_thr[13];
    // M4_ARRAY_DESC("rb_rnd_offs", "u8", M4_SIZE(1,13),  M4_RANGE(0, 3), "[3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,3,3,3]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char rb_rnd_offs[13];
    // M4_ARRAY_DESC("g_rnd_offs", "u8", M4_SIZE(1,13),  M4_RANGE(0, 3), "[3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,3,3,3]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char g_rnd_offs[13];
} CalibDb_Dpcc_set_RND_V20_t;

typedef struct CalibDb_Dpcc_set_RG_V20_s {
    // M4_ARRAY_DESC("RG_enable", "u8", M4_SIZE(1,13),  M4_RANGE(0, 1), "[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char RG_enable[13];
    // M4_ARRAY_DESC("rb_rg_fac", "u8", M4_SIZE(1,13),  M4_RANGE(0, 63), "[8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,8,8,8]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char rb_rg_fac[13];
    // M4_ARRAY_DESC("g_rg_fac", "u8", M4_SIZE(1,13),  M4_RANGE(0, 63), "[8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,8,8,8]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char g_rg_fac[13];
} CalibDb_Dpcc_set_RG_V20_t;

typedef struct CalibDb_Dpcc_set_RO_V20_s {
    // M4_ARRAY_DESC("RO_enable", "u8", M4_SIZE(1,13),  M4_RANGE(0, 1), "[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char RO_enable[13];
    // M4_ARRAY_DESC("rb_ro_lim", "u8", M4_SIZE(1,13),  M4_RANGE(0, 3), "[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char rb_ro_lim[13];
    // M4_ARRAY_DESC("g_ro_lim", "u8", M4_SIZE(1,13),  M4_RANGE(0, 3), "[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char g_ro_lim[13];
} CalibDb_Dpcc_set_RO_V20_t;

typedef struct CalibDb_Dpcc_set_V20_s {
    // M4_STRUCT_DESC("RK", "normal_ui_style")
    CalibDb_Dpcc_set_RK_V20_t RK;
    // M4_STRUCT_DESC("LC", "normal_ui_style")
    CalibDb_Dpcc_set_LC_V20_t LC;
    // M4_STRUCT_DESC("PG", "normal_ui_style")
    CalibDb_Dpcc_set_PG_V20_t PG;
    // M4_STRUCT_DESC("RND", "normal_ui_style")
    CalibDb_Dpcc_set_RND_V20_t RND;
    // M4_STRUCT_DESC("RG", "normal_ui_style")
    CalibDb_Dpcc_set_RG_V20_t RG;
    // M4_STRUCT_DESC("RO", "normal_ui_style")
    CalibDb_Dpcc_set_RO_V20_t RO;
} CalibDb_Dpcc_set_V20_t;

typedef struct FastData_s {
    // M4_ARRAY_DESC("ISO", "f32", M4_SIZE(1,100), M4_RANGE(50,10000000), "50",M4_DIGIT(2), M4_DYNAMIC(1))
    float* ISO;
    int ISO_len;
    // M4_ARRAY_DESC("Single_level", "u32", M4_SIZE(1,100), M4_RANGE(1,10), "1",M4_DIGIT(0), M4_DYNAMIC(1))
    int* Single_level;
    int Single_level_len;
    // M4_ARRAY_DESC("Double_level", "u32", M4_SIZE(1,100), M4_RANGE(1,10), "1",M4_DIGIT(0), M4_DYNAMIC(1))
    int* Double_level;
    int Double_level_len;
    // M4_ARRAY_DESC("Triple_level", "u32", M4_SIZE(1,100), M4_RANGE(1,10), "1",M4_DIGIT(0), M4_DYNAMIC(1))
    int* Triple_level;
    int Triple_level_len;
} FastData_t;

typedef struct CalibDb_Dpcc_Fast_Mode_V20_s {
    // M4_BOOL_DESC("Fast_mode_en", "1")
    
# 128 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h" 3 4
   _Bool 
# 128 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h"
                 Fast_mode_en;
    // M4_BOOL_DESC("Single_enable", "1")
    
# 130 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h" 3 4
   _Bool 
# 130 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h"
        Single_enable;
    // M4_BOOL_DESC("Double_enable", "1")
    
# 132 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h" 3 4
   _Bool 
# 132 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h"
        Double_enable;
    // M4_BOOL_DESC("Triple_enable", "1")
    
# 134 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h" 3 4
   _Bool 
# 134 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h"
        Triple_enable;
    // M4_ARRAY_TABLE_DESC("Fast_Data", "array_table_ui", "none")
    FastData_t Fast_Data;
} CalibDb_Dpcc_Fast_Mode_V20_t;

typedef struct SetData_s {
    // M4_STRUCT_DESC("RK", "normal_ui_style")
    CalibDb_Dpcc_set_RK_V20_t RK;
    // M4_STRUCT_DESC("LC", "normal_ui_style")
    CalibDb_Dpcc_set_LC_V20_t LC;
    // M4_STRUCT_DESC("PG", "normal_ui_style")
    CalibDb_Dpcc_set_PG_V20_t PG;
    // M4_STRUCT_DESC("RND", "normal_ui_style")
    CalibDb_Dpcc_set_RND_V20_t RND;
    // M4_STRUCT_DESC("RG", "normal_ui_style")
    CalibDb_Dpcc_set_RG_V20_t RG;
    // M4_STRUCT_DESC("RO", "normal_ui_style")
    CalibDb_Dpcc_set_RO_V20_t RO;
} SetData_t;

typedef struct SetEnable_s {
    // M4_ARRAY_DESC("ISO", "u32", M4_SIZE(1,13),  M4_RANGE(50, 100000000), "[50, 100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600, 51200, 102400, 204800]", M4_DIGIT(4), M4_DYNAMIC(0))
    int ISO[13];
    // M4_ARRAY_DESC("fix_set", "u16", M4_SIZE(1,13),  M4_RANGE(0, 1), "[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]", M4_DIGIT(0), M4_DYNAMIC(0))
    int fix_set[13];
    // M4_ARRAY_DESC("set1", "u16", M4_SIZE(1,13),  M4_RANGE(0, 1), "[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]", M4_DIGIT(0), M4_DYNAMIC(0))
    int set1[13];
    // M4_ARRAY_DESC("set2", "u16", M4_SIZE(1,13),  M4_RANGE(0, 1), "[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]", M4_DIGIT(0), M4_DYNAMIC(0))
    int set2[13];
    // M4_ARRAY_DESC("set3", "u16", M4_SIZE(1,13),  M4_RANGE(0, 1), "[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]", M4_DIGIT(0), M4_DYNAMIC(0))
    int set3[13];
} SetEnable_t;

typedef struct CalibDb_Dpcc_Expert_Mode_V20_s {
    //M4_BOOL_DESC("stage1_Enable", "1")
    
# 169 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h" 3 4
   _Bool 
# 169 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h"
              stage1_Enable;
    // M4_BOOL_DESC("grayscale_mode", "0")
    
# 171 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h" 3 4
   _Bool 
# 171 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h"
              grayscale_mode;
    // M4_BOOL_DESC("dpcc_out_sel", "1")
    
# 173 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h" 3 4
   _Bool 
# 173 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h"
              dpcc_out_sel;
    // M4_BOOL_DESC("stage1_g_3x3", "0")
    
# 175 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h" 3 4
   _Bool 
# 175 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h"
               stage1_g_3x3;
    // M4_BOOL_DESC("stage1_rb_3x3", "0")
    
# 177 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h" 3 4
   _Bool 
# 177 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h"
               stage1_rb_3x3;
    // M4_BOOL_DESC("stage1_inc_rb_center", "1")
    
# 179 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h" 3 4
   _Bool 
# 179 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h"
           stage1_inc_rb_center;
    // M4_BOOL_DESC("stage1_inc_g_center", "1")
    
# 181 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h" 3 4
   _Bool 
# 181 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h"
           stage1_inc_g_center;
    // M4_NUMBER_DESC("rk_out_sel", "u8", M4_RANGE(0,2), "0", M4_DIGIT(0))
    unsigned char rk_out_sel;
    // M4_STRUCT_DESC("SetEnable", "array_table_ui")
    SetEnable_t SetEnable;
    // M4_ARRAY_TABLE_DESC("set1", "array_table_ui", "none")
    SetData_t set1;
    // M4_ARRAY_TABLE_DESC("set2", "array_table_ui", "none")
    SetData_t set2;
    // M4_ARRAY_TABLE_DESC("set3", "array_table_ui", "none")
    SetData_t set3;
} CalibDb_Dpcc_Expert_Mode_V20_t;

typedef struct CalibDb_Dpcc_Pdaf_V20_s {
    // M4_BOOL_DESC("en", "0")
    
# 196 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h" 3 4
   _Bool 
# 196 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h"
        en;
    // M4_ARRAY_DESC("point_en", "u16", M4_SIZE(1,16),  M4_RANGE(1, 10), "[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char point_en[16];
    // M4_NUMBER_DESC("offsetx", "u8", M4_RANGE(0,100), "0", M4_DIGIT(0))
    int offsetx;
    // M4_NUMBER_DESC("offsety", "u8", M4_RANGE(0,100), "0", M4_DIGIT(0))
    int offsety;
    // M4_NUMBER_DESC("wrapx", "u8", M4_RANGE(0,255), "0", M4_DIGIT(0))
    unsigned char wrapx;
    // M4_NUMBER_DESC("wrapy", "u8", M4_RANGE(0,255), "0", M4_DIGIT(0))
    unsigned char wrapy;
    // M4_NUMBER_DESC("wrapx_num", "u8", M4_RANGE(0,1023), "0", M4_DIGIT(0))
    int wrapx_num;
    // M4_NUMBER_DESC("wrapy_num", "u8", M4_RANGE(0,1023), "0", M4_DIGIT(0))
    int wrapy_num;
    // M4_ARRAY_MARK_DESC("point_x", "u16", M4_SIZE(1,16),  M4_RANGE(1, 255), "[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char point_x[16];
    // M4_ARRAY_MARK_DESC("point_y", "u16", M4_SIZE(1,16),  M4_RANGE(1, 255), "[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char point_y[16];
    // M4_NUMBER_DESC("forward_med", "u8", M4_RANGE(0,1), "0", M4_DIGIT(0))
    unsigned char forward_med;
} CalibDb_Dpcc_Pdaf_V20_t;

typedef struct SensorDpccData_s {
    // M4_ARRAY_DESC("ISO", "f32", M4_SIZE(1,100), M4_RANGE(50,10000000), "50",M4_DIGIT(4), M4_DYNAMIC(1))
    float* ISO;
    int ISO_len;
    // M4_ARRAY_DESC("level_single", "u32", M4_SIZE(1,100), M4_RANGE(1,10000000), "1",M4_DIGIT(0), M4_DYNAMIC(1))
    int* level_single;
    int level_single_len;
    // M4_ARRAY_DESC("level_multiple", "u32", M4_SIZE(1,100), M4_RANGE(1,10000000), "1",M4_DIGIT(0), M4_DYNAMIC(1))
    int* level_multiple;
    int level_multiple_len;
} SensorDpccData_t;

typedef struct CalibDb_Dpcc_Sensor_V20_s {
    // M4_BOOL_DESC("sensor_dpcc_auto_en", "1")
    
# 233 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h" 3 4
   _Bool 
# 233 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h"
        sensor_dpcc_auto_en;
    // M4_NUMBER_DESC("max_level", "u8", M4_RANGE(0,100), "1", M4_DIGIT(0))
    int max_level;
    // M4_ARRAY_TABLE_DESC("SensorDpcc_Data", "array_table_ui", "none")
    SensorDpccData_t SensorDpcc_Data;
} CalibDb_Dpcc_Sensor_V20_t;

typedef struct CalibDbDpccV20_s {
    // M4_BOOL_DESC("Enable", "1")
    
# 242 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h" 3 4
   _Bool 
# 242 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adpcc_head.h"
                               Enable;
    // M4_STRUCT_DESC("Fast_Mode", "normal_ui_style")
    CalibDb_Dpcc_Fast_Mode_V20_t Fast_Mode;
    // M4_STRUCT_DESC("Expert_Mode", "normal_ui_style")
    CalibDb_Dpcc_Expert_Mode_V20_t Expert_Mode;
    // M4_STRUCT_DESC("CalibDb_Dpcc_Pdaf_V20_t", "normal_ui_style")
    CalibDb_Dpcc_Pdaf_V20_t Dpcc_pdaf;
    // M4_STRUCT_DESC("Sensor_dpcc", "normal_ui_style")
    CalibDb_Dpcc_Sensor_V20_t Sensor_dpcc;
} CalibDbDpccV20_t;

typedef struct CalibDbV2_Dpcc_s {
    // M4_STRUCT_DESC("DpccTuningPara", "normal_ui_style")
    CalibDbDpccV20_t DpccTuningPara;
} CalibDbV2_Dpcc_t;


# 25 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adrc_head.h" 1



typedef struct AdrcGain_s {
    // M4_ARRAY_DESC("EnvLv", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0",M4_DIGIT(3), M4_DYNAMIC(1))
    float* EnvLv;
    int EnvLv_len;
    // M4_ARRAY_DESC("DrcGain", "f32", M4_SIZE(1,100), M4_RANGE(1,8), "4",M4_DIGIT(2), M4_DYNAMIC(1))
    float* DrcGain; //sw_drc_gain
    int DrcGain_len;
    // M4_ARRAY_DESC("Alpha", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.2",M4_DIGIT(2), M4_DYNAMIC(1))
    float* Alpha;
    int Alpha_len;
    // M4_ARRAY_DESC("Clip", "f32", M4_SIZE(1,100), M4_RANGE(0,64), "16",M4_DIGIT(2), M4_DYNAMIC(1))
    float* Clip; //sw_drc_position, step: 1/255
    int Clip_len;
} AdrcGain_t;

typedef struct HighLight_s {
    // M4_ARRAY_DESC("EnvLv", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0",M4_DIGIT(3), M4_DYNAMIC(1))
    float* EnvLv;
    int EnvLv_len;
    // M4_ARRAY_DESC("Strength", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "1",M4_DIGIT(2), M4_DYNAMIC(1))
    float* Strength; //sw_drc_weig_maxl,  range[0,1], step 1/16
    int Strength_len;
} HighLight_t;

typedef struct LocalData_s
{
    // M4_ARRAY_DESC("EnvLv", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0",M4_DIGIT(2), M4_DYNAMIC(1))
    float* EnvLv;
    int EnvLv_len;
    // M4_ARRAY_DESC("LocalWeit", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "1",M4_DIGIT(2), M4_DYNAMIC(1))
    float* LocalWeit; //sw_drc_weig_bilat, range[0 , 1], step: 1/16
    int LocalWeit_len;
    // M4_ARRAY_DESC("GlobalContrast", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0",M4_DIGIT(3), M4_DYNAMIC(1))
    float* GlobalContrast; //sw_drc_lpdetail_ratio, setp 1/4096
    int GlobalContrast_len;
    // M4_ARRAY_DESC("LoLitContrast", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0",M4_DIGIT(3), M4_DYNAMIC(1))
    float* LoLitContrast; //sw_drc_hpdetail_ratio, setp 1/4096
    int LoLitContrast_len;
} LocalData_t;

typedef struct local_s {
    // M4_ARRAY_TABLE_DESC("LocalTMOData", "array_table_ui", "none")
    LocalData_t LocalTMOData;
    // M4_NUMBER_DESC("curPixWeit", "f32", M4_RANGE(0,1), "0.37", M4_DIGIT(3))
    float curPixWeit; //sw_drc_weicur_pix,  range[0,1],step: 1/255
    // M4_NUMBER_DESC("preFrameWeit", "f32", M4_RANGE(0,1), "1.0", M4_DIGIT(3))
    float preFrameWeit;//sw_adrc_weipre_frame ,range[0,1],step: 1/255
    // M4_NUMBER_DESC("Range_force_sgm", "f32", M4_RANGE(0,1), "0.0", M4_DIGIT(4))
    float Range_force_sgm; //sw_drc_force_sgm_inv0 ,range[0,1], step 1/8191
    // M4_NUMBER_DESC("Range_sgm_cur", "f32", M4_RANGE(0,1), "0.125", M4_DIGIT(4))
    float Range_sgm_cur; //sw_drc_range_sgm_inv1, range[0,1], step 1/8191
    // M4_NUMBER_DESC("Range_sgm_pre", "f32", M4_RANGE(0,1), "0.125", M4_DIGIT(4))
    float Range_sgm_pre; //sw_drc_range_sgm_inv0,range[0,1], step 1/8191
    // M4_NUMBER_DESC("Space_sgm_cur", "u16", M4_RANGE(0,4095), "4068", M4_DIGIT(0))
    int Space_sgm_cur; //sw_drc_space_sgm_inv1
    // M4_NUMBER_DESC("Space_sgm_pre", "u16", M4_RANGE(0,4095), "3968", M4_DIGIT(0))
    int Space_sgm_pre; //sw_drc_space_sgm_inv0
} local_t;

typedef enum CompressMode_e {
    COMPRESS_AUTO = 0,
    COMPRESS_MANUAL = 1,
} CompressMode_t;

typedef struct Compress_s {
    // M4_ENUM_DESC("Mode", "CompressMode_t", "COMPRESS_AUTO")
    CompressMode_t Mode;
    // M4_ARRAY_MARK_DESC("Manual_curve", "u32", M4_SIZE(1,17),  M4_RANGE(0, 8192), "[0, 558, 1087, 1588, 2063, 2515, 2944, 3353, 3744, 4473, 5139, 5751, 6316, 6838, 7322, 7772, 8192]", M4_DIGIT(0), M4_DYNAMIC(0), "curve_table")
    uint16_t Manual_curve[17];
} Compress_t;

typedef struct CalibDbV2_Adrc_s {
    // M4_BOOL_DESC("Enable", "1")
    
# 77 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adrc_head.h" 3 4
   _Bool 
# 77 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adrc_head.h"
        Enable;
    // M4_ARRAY_TABLE_DESC("DrcGain", "array_table_ui", "none")
    AdrcGain_t DrcGain;
    // M4_ARRAY_TABLE_DESC("HiLight", "array_table_ui", "none")
    HighLight_t HiLight;
    // M4_STRUCT_DESC("LocalTMOSetting", "normal_ui_style")
    local_t LocalTMOSetting;
    // M4_STRUCT_DESC("CompressSetting", "normal_ui_style")
    Compress_t CompressSetting;
    // M4_ARRAY_DESC("Scale_y", "u16", M4_SIZE(1,17),  M4_RANGE(0, 2048), "[0,2,20,76,193,381,631,772,919,1066,1211,1479,1700,1863,1968,2024,2048]", M4_DIGIT(0), M4_DYNAMIC(0))
    int Scale_y[17];
    // M4_NUMBER_DESC("ByPassThr", "f32", M4_RANGE(0,1), "0", M4_DIGIT(4))
    float ByPassThr;
    // M4_NUMBER_DESC("Edge_Weit", "f32",  M4_RANGE(0,1), "1",M4_DIGIT(3))
    float Edge_Weit; //sw_drc_edge_scl, range[0,1], step 1/255
    // M4_BOOL_DESC("OutPutLongFrame", "0")
    
# 93 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adrc_head.h" 3 4
   _Bool 
# 93 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adrc_head.h"
         OutPutLongFrame; //sw_drc_min_ogain
    // M4_NUMBER_DESC("IIR_frame", "u8", M4_RANGE(1,1000), "16", M4_DIGIT(0))
    int IIR_frame; //sw_drc_iir_frame, range [1, 1000]
    // M4_NUMBER_DESC("Tolerance", "f32", M4_RANGE(0,1), "0", M4_DIGIT(3))
    float Tolerance;
    // M4_NUMBER_DESC("damp", "f32", M4_RANGE(0,1), "0.9", M4_DIGIT(3))
    float damp;
} CalibDbV2_Adrc_t;

typedef struct CalibDbV2_drc_s {
    // M4_STRUCT_DESC("DrcTuningPara", "normal_ui_style")
    CalibDbV2_Adrc_t DrcTuningPara;
} CalibDbV2_drc_t;

typedef struct LocalDataV2_s
{
    // M4_ARRAY_DESC("EnvLv", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0",M4_DIGIT(2), M4_DYNAMIC(1))
    float* EnvLv;
    int EnvLv_len;
    // M4_ARRAY_DESC("LocalWeit", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "1",M4_DIGIT(2), M4_DYNAMIC(1))
    float* LocalWeit; //sw_drc_weig_bilat, range[0 , 1], step: 1/16
    int LocalWeit_len;
    // M4_ARRAY_DESC("LocalAutoEnable", "u8", M4_SIZE(1,100), M4_RANGE(0,1), "1",M4_DIGIT(0), M4_DYNAMIC(1))
    int* LocalAutoEnable; //sw_adrc_enable_soft_thd, range[0 , 1], step: 1
    int LocalAutoEnable_len;
    // M4_ARRAY_DESC("LocalAutoWeit", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.037477",M4_DIGIT(5), M4_DYNAMIC(1))
    float* LocalAutoWeit; //sw_adrc_bilat_soft_thd, range[0 , 1], step: 1/0x3fff
    int LocalAutoWeit_len;
    // M4_ARRAY_DESC("GlobalContrast", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0",M4_DIGIT(3), M4_DYNAMIC(1))
    float* GlobalContrast; //sw_drc_lpdetail_ratio, setp 1/4096
    int GlobalContrast_len;
    // M4_ARRAY_DESC("LoLitContrast", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0",M4_DIGIT(3), M4_DYNAMIC(1))
    float* LoLitContrast; //sw_drc_hpdetail_ratio, setp 1/4096
    int LoLitContrast_len;
} LocalDataV2_t;

typedef struct localV2_s {
    // M4_ARRAY_TABLE_DESC("LocalData", "array_table_ui", "none")
    LocalDataV2_t LocalData;
    // M4_NUMBER_DESC("curPixWeit", "f32", M4_RANGE(0,1), "0.37", M4_DIGIT(3))
    float curPixWeit; //sw_drc_weicur_pix,  range[0,1],step: 1/255
    // M4_NUMBER_DESC("preFrameWeit", "f32", M4_RANGE(0,1), "1.0", M4_DIGIT(3))
    float preFrameWeit;//sw_adrc_weipre_frame ,range[0,1],step: 1/255
    // M4_NUMBER_DESC("Range_force_sgm", "f32", M4_RANGE(0,1), "0.0", M4_DIGIT(4))
    float Range_force_sgm; //sw_drc_force_sgm_inv0 ,range[0,1], step 1/8191
    // M4_NUMBER_DESC("Range_sgm_cur", "f32", M4_RANGE(0,1), "0.125", M4_DIGIT(4))
    float Range_sgm_cur; //sw_drc_range_sgm_inv1, range[0,1], step 1/8191
    // M4_NUMBER_DESC("Range_sgm_pre", "f32", M4_RANGE(0,1), "0.125", M4_DIGIT(4))
    float Range_sgm_pre; //sw_drc_range_sgm_inv0,range[0,1], step 1/8191
    // M4_NUMBER_DESC("Space_sgm_cur", "u16", M4_RANGE(0,4095), "4068", M4_DIGIT(0))
    int Space_sgm_cur; //sw_drc_space_sgm_inv1
    // M4_NUMBER_DESC("Space_sgm_pre", "u16", M4_RANGE(0,4095), "3968", M4_DIGIT(0))
    int Space_sgm_pre; //sw_drc_space_sgm_inv0
} localV2_t;

typedef struct CalibDbV2_Adrc_V2_s {
    // M4_BOOL_DESC("Enable", "1")
    
# 150 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adrc_head.h" 3 4
   _Bool 
# 150 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adrc_head.h"
        Enable;
    // M4_ARRAY_TABLE_DESC("DrcGain", "array_table_ui", "none")
    AdrcGain_t DrcGain;
    // M4_ARRAY_TABLE_DESC("HiLight", "array_table_ui", "none")
    HighLight_t HiLight;
    // M4_STRUCT_DESC("LocalSetting", "normal_ui_style")
    localV2_t LocalSetting;
    // M4_STRUCT_DESC("CompressSetting", "normal_ui_style")
    Compress_t CompressSetting;
    // M4_ARRAY_DESC("Scale_y", "u16", M4_SIZE(1,17),  M4_RANGE(0, 2048), "[0,2,20,76,193,381,631,772,919,1066,1211,1479,1700,1863,1968,2024,2048]", M4_DIGIT(0), M4_DYNAMIC(0))
    int Scale_y[17];
    // M4_NUMBER_DESC("ByPassThr", "f32", M4_RANGE(0,1), "0", M4_DIGIT(4))
    float ByPassThr;
    // M4_NUMBER_DESC("Edge_Weit", "f32",  M4_RANGE(0,1), "1",M4_DIGIT(3))
    float Edge_Weit; //sw_drc_edge_scl, range[0,1], step 1/255
    // M4_BOOL_DESC("OutPutLongFrame", "0")
    
# 166 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adrc_head.h" 3 4
   _Bool 
# 166 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adrc_head.h"
         OutPutLongFrame; //sw_drc_min_ogain
    // M4_NUMBER_DESC("IIR_frame", "u8", M4_RANGE(1,1000), "16", M4_DIGIT(0))
    int IIR_frame; //sw_drc_iir_frame, range [1, 1000]
    // M4_NUMBER_DESC("Tolerance", "f32", M4_RANGE(0,1), "0", M4_DIGIT(3))
    float Tolerance;
    // M4_NUMBER_DESC("damp", "f32", M4_RANGE(0,1), "0.9", M4_DIGIT(3))
    float damp;
} CalibDbV2_Adrc_V2_t;

typedef struct CalibDbV2_drc_V2_s {
    // M4_STRUCT_DESC("DrcTuningPara", "normal_ui_style")
    CalibDbV2_Adrc_V2_t DrcTuningPara;
} CalibDbV2_drc_V2_t;


       
# 26 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h" 2



// #define M4_STRUCT_DESC(ALIAS, SIZE, UI_MODULE)
// #define M4_NUMBER_DESC(ALIAS, TYPE, SIZE, RANGE, DEFAULT)
// #define M4_STRING_DESC(ALIAS, SIZE, RANGE, DEFAULT)
// #define M4_ENUM_DESC(ALIAS, ENUM, DEFAULT)

# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 33 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h" 2





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
    // M4_NUMBER_DESC("BlackDelay", "u8", M4_RANGE(0,255), "0", M4_DIGIT(0),M4_HIDE(0))
    uint8_t BlackDelay;

    // M4_NUMBER_DESC("WhiteDelay", "u8", M4_RANGE(0,255), "0", M4_DIGIT(0),M4_HIDE(0))
    uint8_t WhiteDelay;
} CalibDb_AeDelayFrmNumV2_t;

typedef struct CalibDb_AeSpeedV2_s {
    // M4_BOOL_DESC("SmoothEn", "1")
    
# 125 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h" 3 4
   _Bool 
# 125 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h"
                           SmoothEn;
    // M4_BOOL_DESC("DyDampEn", "1")
    
# 127 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h" 3 4
   _Bool 
# 127 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h"
                           DyDampEn;
    // M4_NUMBER_DESC("DampOver", "f32", M4_RANGE(0,1.00), "0.15", M4_DIGIT(2),M4_HIDE(0))
    float DampOver;

    // M4_NUMBER_DESC("DampUnder", "f32", M4_RANGE(0,1.00), "0.45", M4_DIGIT(2),M4_HIDE(0))
    float DampUnder;

    // M4_NUMBER_DESC("DampDark2Bright", "f32", M4_RANGE(0,1.00), "0.15", M4_DIGIT(2),M4_HIDE(0))
    float DampDark2Bright;

    // M4_NUMBER_DESC("DampBright2Dark", "f32", M4_RANGE(0,1.00), "0.45", M4_DIGIT(2),M4_HIDE(0))
    float DampBright2Dark;
} CalibDb_AeSpeedV2_t;

typedef struct CalibDb_AeFrmRateAttrV2_s {
    // M4_BOOL_DESC("isFpsFix", "1")
    
# 143 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h" 3 4
   _Bool 
# 143 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h"
                           isFpsFix;

    // M4_NUMBER_DESC("FpsValue", "f32", M4_RANGE(0,200), "0", M4_DIGIT(1),M4_HIDE(0))
    float FpsValue;
} CalibDb_AeFrmRateAttrV2_t;

typedef struct CalibDb_AntiFlickerAttrV2_s {
    // M4_BOOL_DESC("enable", "1")
    
# 151 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h" 3 4
   _Bool 
# 151 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h"
                                  enable;

    // M4_ENUM_DESC("Frequency", "CalibDb_FlickerFreqV2_t","AECV2_FLICKER_FREQUENCY_50HZ")
    CalibDb_FlickerFreqV2_t Frequency;

    // M4_ENUM_DESC("Mode", "CalibDb_AntiFlickerModeV2_t","AECV2_ANTIFLICKER_AUTO_MODE")
    CalibDb_AntiFlickerModeV2_t Mode;
} CalibDb_AntiFlickerAttrV2_t;

//manual exposure
typedef struct CalibDb_LinMeAttrV2_s {
    // M4_BOOL_DESC("ManualTimeEn", "1")
    
# 163 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h" 3 4
   _Bool 
# 163 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h"
                        ManualTimeEn;

    // M4_BOOL_DESC("ManualGainEn", "1")
    
# 166 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h" 3 4
   _Bool 
# 166 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h"
                        ManualGainEn;

    // M4_BOOL_DESC("ManualIspDgainEn", "1")
    
# 169 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h" 3 4
   _Bool 
# 169 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h"
                        ManualIspDgainEn;

    // M4_NUMBER_DESC("TimeValue", "f32", M4_RANGE(0,1), "0.003", M4_DIGIT(6),M4_HIDE(0))
    float TimeValue; //unit: s = 10^6 us

    // M4_NUMBER_DESC("GainValue", "f32", M4_RANGE(1,4096), "1", M4_DIGIT(3),M4_HIDE(0))
    float GainValue;

    // M4_NUMBER_DESC("IspDGainValue", "f32", M4_RANGE(1,4096), "1", M4_DIGIT(3),M4_HIDE(0))
    float IspDGainValue;
} CalibDb_LinMeAttrV2_t;

typedef struct CalibDb_HdrMeAttrV2_s {
    // M4_BOOL_DESC("ManualTimeEn", "1")
    
# 183 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h" 3 4
   _Bool 
# 183 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h"
                           ManualTimeEn;

    // M4_BOOL_DESC("ManualGainEn", "1")
    
# 186 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h" 3 4
   _Bool 
# 186 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h"
                           ManualGainEn;

    // M4_BOOL_DESC("ManualIspDgainEn", "1")
    
# 189 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h" 3 4
   _Bool 
# 189 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h"
                           ManualIspDgainEn;

    // M4_ARRAY_DESC("TimeValue", "f32", M4_SIZE(1,3), M4_RANGE(0,1), "0.003", M4_DIGIT(6), M4_DYNAMIC(0))
    float TimeValue[(3)];

    // M4_ARRAY_DESC("GainValue", "f32", M4_SIZE(1,3), M4_RANGE(1,4096), "1.0", M4_DIGIT(3), M4_DYNAMIC(0))
    float GainValue[(3)];

    // M4_ARRAY_DESC("IspDGainValue", "f32", M4_SIZE(1,3), M4_RANGE(1,4096), "1.0", M4_DIGIT(3), M4_DYNAMIC(0))
    float IspDGainValue[(3)];
} CalibDb_HdrMeAttrV2_t;

typedef struct CalibDb_MeAttrV2_s {
    // M4_STRUCT_DESC("LinearAE", "normal_ui_style")
    CalibDb_LinMeAttrV2_t LinearAE;

    // M4_STRUCT_DESC("HdrAE", "normal_ui_style")
    CalibDb_HdrMeAttrV2_t HdrAE;
} CalibDb_MeAttrV2_t;

//win_scale = [h_off, v_off, h_size, v_size], range=[0,1]
typedef struct CalibDb_Aec_WinScale_s {
    // M4_NUMBER_DESC("h_offs", "f32", M4_RANGE(0,1), "0", M4_DIGIT(2),M4_HIDE(0))
    float h_offs;

    // M4_NUMBER_DESC("v_offs", "f32", M4_RANGE(0,1), "0", M4_DIGIT(2),M4_HIDE(0))
    float v_offs;

    // M4_NUMBER_DESC("h_size", "f32", M4_RANGE(0,1), "1", M4_DIGIT(2),M4_HIDE(0))
    float h_size;

    // M4_NUMBER_DESC("v_size", "f32", M4_RANGE(0,1), "1", M4_DIGIT(2),M4_HIDE(0))
    float v_size;
} CalibDb_Aec_WinScale_t;

typedef struct CalibDb_Aec_WinScaleV2_t {

    // M4_STRUCT_DESC("InRawWinScale", "normal_ui_style")
    CalibDb_Aec_WinScale_t InRawWinScale;

    // M4_STRUCT_DESC("TmoRawWinScale", "normal_ui_style")
    CalibDb_Aec_WinScale_t TmoRawWinScale;

    // M4_STRUCT_DESC("YuvWinScale", "normal_ui_style")
    CalibDb_Aec_WinScale_t YuvWinScale;
} CalibDb_Aec_WinScaleV2_t;

typedef struct CalibDb_AeEnvLvCalibV2_s {
    // M4_NUMBER_DESC("CalibFNumber", "f32", M4_RANGE(0,256), "1.6", M4_DIGIT(2),M4_HIDE(0))
    float CalibFNumber;

    // M4_ARRAY_DESC("CurveCoeff", "f32", M4_SIZE(1,2), M4_RANGE(-1024,1024), "1.0", M4_DIGIT(5), M4_DYNAMIC(0))
    float CurveCoeff[2];//y=ax+b, Coeff=[a,b]
} CalibDb_AeEnvLvCalibV2_t;

typedef struct CalibDb_AecCommon_AttrV2_s {
    // M4_BOOL_DESC("Enable", "1")
    
# 246 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h" 3 4
   _Bool 
# 246 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h"
                                     Enable;

    // M4_NUMBER_DESC("AecRunInterval", "u8", M4_RANGE(0,255), "0", M4_DIGIT(0),M4_HIDE(0))
    uint8_t AecRunInterval;

    // M4_ENUM_DESC("AecOpType", "RKAiqOPMode_t","RK_AIQ_OP_MODE_AUTO")
    RKAiqOPMode_t AecOpType;

    // M4_ENUM_DESC("HistStatsMode", "CalibDb_CamHistStatsModeV2_t","CAM_HISTV2_MODE_G")
    CalibDb_CamHistStatsModeV2_t HistStatsMode;

    // M4_ENUM_DESC("RawStatsMode", "CalibDb_CamRawStatsModeV2_t","CAM_RAWSTATSV2_MODE_G")
    CalibDb_CamRawStatsModeV2_t RawStatsMode;

    // M4_ENUM_DESC("YRangeMode", "CalibDb_CamYRangeModeV2_t","CAM_YRANGEV2_MODE_FULL")
    CalibDb_CamYRangeModeV2_t YRangeMode;

    // M4_ARRAY_DESC("AecGridWeight", "u8", M4_SIZE(15,15), M4_RANGE(0,32), "1", M4_DIGIT(0), M4_DYNAMIC(0))
    uint8_t AecGridWeight[(225)];

    // M4_STRUCT_DESC("AecManualCtrl", "normal_ui_style")
    CalibDb_MeAttrV2_t AecManualCtrl;

    // M4_STRUCT_DESC("AecSpeed", "normal_ui_style")
    CalibDb_AeSpeedV2_t AecSpeed;

    // M4_STRUCT_DESC("AecDelayFrmNum", "normal_ui_style")
    CalibDb_AeDelayFrmNumV2_t AecDelayFrmNum;

    // M4_STRUCT_DESC("AecFrameRateMode", "normal_ui_style")
    CalibDb_AeFrmRateAttrV2_t AecFrameRateMode;

    // M4_STRUCT_DESC("AecAntiFlicker", "normal_ui_style")
    CalibDb_AntiFlickerAttrV2_t AecAntiFlicker;

    // M4_STRUCT_DESC("AecEnvLvCalib", "normal_ui_style")
    CalibDb_AeEnvLvCalibV2_t AecEnvLvCalib;

    // M4_STRUCT_DESC("AecWinScale", "normal_ui_style")
    CalibDb_Aec_WinScaleV2_t AecWinScale;
} CalibDb_AecCommon_AttrV2_t;

/*****************************************************************************/
/**
 * @brief   ISP2.0 AEC algo LinAE Config Params
 */
/*****************************************************************************/
typedef struct CalibDb_LinExpInitExpV2_s {
    // M4_NUMBER_DESC("InitTimeValue", "f32", M4_RANGE(0,1), "0.003", M4_DIGIT(6),M4_HIDE(0))
    float InitTimeValue;

    // M4_NUMBER_DESC("InitGainValue", "f32", M4_RANGE(1,4096), "1", M4_DIGIT(3),M4_HIDE(0))
    float InitGainValue;

    // M4_NUMBER_DESC("InitIspDGainValue", "f32", M4_RANGE(1,4096), "1", M4_DIGIT(3),M4_HIDE(0))
    float InitIspDGainValue;

    // M4_NUMBER_DESC("InitPIrisGainValue", "s32", M4_RANGE(1,4096), "1024", M4_DIGIT(0),M4_HIDE(0))
    int InitPIrisGainValue;

    // M4_NUMBER_DESC("InitDCIrisDutyValue", "s32", M4_RANGE(0,100), "100", M4_DIGIT(0),M4_HIDE(0))
    int InitDCIrisDutyValue;
} CalibDb_LinExpInitExpV2_t;

typedef struct CalibDb_LinAeRoute_AttrV2_s {
    // M4_ARRAY_DESC("TimeDot", "f32", M4_SIZE(1,6), M4_RANGE(0,1), "0", M4_DIGIT(6), M4_DYNAMIC(1))
    float* TimeDot;
    int TimeDot_len;
    // M4_ARRAY_DESC("GainDot", "f32", M4_SIZE(1,6), M4_RANGE(1,4096), "1", M4_DIGIT(3), M4_DYNAMIC(1))
    float* GainDot;
    int GainDot_len;
    // M4_ARRAY_DESC("IspDGainDot", "f32", M4_SIZE(1,6), M4_RANGE(1,4096), "1", M4_DIGIT(3), M4_DYNAMIC(1))
    float* IspDGainDot;
    int IspDGainDot_len;
    // M4_ARRAY_DESC("PIrisDot", "s32", M4_SIZE(1,6), M4_RANGE(1,4096), "1024", M4_DIGIT(0), M4_DYNAMIC(1))
    int* PIrisDot;
    int PIrisDot_len;
} CalibDb_LinAeRoute_AttrV2_t;

typedef struct CalibDb_AecDynamicSetpointV2_s {
    // M4_ARRAY_DESC("ExpLevel", "f32", M4_SIZE(1,6), M4_RANGE(0,4096), "0", M4_DIGIT(5), M4_DYNAMIC(1))
    float* ExpLevel;
    int ExpLevel_len;
    // M4_ARRAY_DESC("DySetpoint", "f32", M4_SIZE(1,6), M4_RANGE(0,255), "40", M4_DIGIT(2), M4_DYNAMIC(1))
    float* DySetpoint;
    int DySetpoint_len;
} CalibDb_AecDynamicSetpointV2_t;

typedef struct CalibDb_BacklitSetPointV2_s {
    // M4_ARRAY_DESC("ExpLevel", "f32", M4_SIZE(1,6), M4_RANGE(0,4096), "0", M4_DIGIT(5), M4_DYNAMIC(1))
    float* ExpLevel;
    int ExpLevel_len;
    // M4_ARRAY_DESC("NonOEPdfTh", "f32", M4_SIZE(1,6), M4_RANGE(0,1), "0.4", M4_DIGIT(2), M4_DYNAMIC(1))
    float* NonOEPdfTh;
    int NonOEPdfTh_len;
    // M4_ARRAY_DESC("LowLightPdfTh", "f32", M4_SIZE(1,6), M4_RANGE(0,1), "0.2", M4_DIGIT(2), M4_DYNAMIC(1))
    float* LowLightPdfTh;
    int LowLightPdfTh_len;
    // M4_ARRAY_DESC("TargetLLLuma", "f32", M4_SIZE(1,6), M4_RANGE(0,255), "20", M4_DIGIT(2), M4_DYNAMIC(1))
    float* TargetLLLuma;
    int TargetLLLuma_len;
} CalibDb_BacklitSetPointV2_t;

typedef struct CalibDb_AecBacklightV2_s {
    // M4_BOOL_DESC("Enable", "0")
    
# 351 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h" 3 4
   _Bool 
# 351 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h"
                               Enable;

    // M4_NUMBER_DESC("StrBias", "f32", M4_RANGE(-500,500), "0", M4_DIGIT(2),M4_HIDE(1))
    float StrBias;//uint: %

    // M4_ENUM_DESC("MeasArea", "CalibDb_AecMeasAreaModeV2_t","AECV2_MEASURE_AREA_AUTO")
    CalibDb_AecMeasAreaModeV2_t MeasArea;

    // M4_NUMBER_DESC("OEROILowTh", "f32", M4_RANGE(0,255), "150", M4_DIGIT(2),M4_HIDE(0))
    float OEROILowTh;

    // M4_NUMBER_DESC("LumaDistTh", "f32", M4_RANGE(0,100), "10", M4_DIGIT(2),M4_HIDE(0))
    float LumaDistTh;//uint: %

    // M4_NUMBER_DESC("LvLowTh", "f32", M4_RANGE(0,100), "7.5", M4_DIGIT(4),M4_HIDE(0))
    float LvLowTh;

    // M4_NUMBER_DESC("LvHighTh", "f32", M4_RANGE(0,100), "0.3125", M4_DIGIT(4),M4_HIDE(0))
    float LvHighTh;

    // M4_ARRAY_TABLE_DESC("BacklitSetPoint", "array_table_ui", M4_INDEX_DEFAULT)
    CalibDb_BacklitSetPointV2_t BacklitSetPoint;
} CalibDb_AecBacklightV2_t;

typedef struct CalibDb_OverExpSetPointV2_s {
    // M4_ARRAY_DESC("OEpdf", "f32", M4_SIZE(1,6), M4_RANGE(0,1), "0", M4_DIGIT(2), M4_DYNAMIC(1))
    float* OEpdf;
    int OEpdf_len;
    // M4_ARRAY_DESC("LowLightWeight", "f32", M4_SIZE(1,6), M4_RANGE(0,20), "1", M4_DIGIT(2), M4_DYNAMIC(1))
    float* LowLightWeight;
    int LowLightWeight_len;
    // M4_ARRAY_DESC("HighLightWeight", "f32", M4_SIZE(1,6), M4_RANGE(0,20), "2", M4_DIGIT(2), M4_DYNAMIC(1))
    float* HighLightWeight;
    int HighLightWeight_len;
} CalibDb_OverExpSetPointV2_t;

typedef struct CalibDb_AecOverExpCtrlV2_s {
    // M4_BOOL_DESC("Enable", "0")
    
# 389 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h" 3 4
   _Bool 
# 389 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h"
                              Enable;

    // M4_NUMBER_DESC("StrBias", "f32", M4_RANGE(-500,500), "0", M4_DIGIT(2),M4_HIDE(1))
    float StrBias; //uint: %

    // M4_NUMBER_DESC("MaxWeight", "f32", M4_RANGE(0,20), "8", M4_DIGIT(2),M4_HIDE(0))
    float MaxWeight;

    // M4_NUMBER_DESC("HighLightTh", "f32", M4_RANGE(0,255), "150", M4_DIGIT(2),M4_HIDE(0))
    float HighLightTh;

    // M4_NUMBER_DESC("LowLightTh", "f32", M4_RANGE(0,255), "30", M4_DIGIT(2),M4_HIDE(0))
    float LowLightTh;

    // M4_ARRAY_TABLE_DESC("OverExpSetPoint", "array_table_ui", M4_INDEX_DEFAULT)
    CalibDb_OverExpSetPointV2_t OverExpSetPoint;
} CalibDb_AecOverExpCtrlV2_t;

typedef struct CalibDb_LinearAE_AttrV2_s {
    // M4_BOOL_DESC("RawStatsEn", "1")
    
# 409 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h" 3 4
   _Bool 
# 409 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h"
                                   RawStatsEn;

    // M4_NUMBER_DESC("ToleranceIn", "f32", M4_RANGE(0,100), "10", M4_DIGIT(2),M4_HIDE(0))
    float ToleranceIn;//uint: %

    // M4_NUMBER_DESC("ToleranceOut", "f32", M4_RANGE(0,100), "15", M4_DIGIT(2),M4_HIDE(0))
    float ToleranceOut;//uint: %

    // M4_NUMBER_DESC("Evbias", "f32", M4_RANGE(-500,500), "0", M4_DIGIT(2),M4_HIDE(1))
    float Evbias; //uint: %

    // M4_ENUM_DESC("StrategyMode", "CalibDb_AeStrategyModeV2_t","AECV2_STRATEGY_MODE_LOWLIGHT_PRIOR")
    CalibDb_AeStrategyModeV2_t StrategyMode;

    // M4_STRUCT_DESC("InitExp", "normal_ui_style")
    CalibDb_LinExpInitExpV2_t InitExp;

    // M4_ARRAY_TABLE_DESC("Route", "array_table_ui", M4_INDEX_DEFAULT)
    CalibDb_LinAeRoute_AttrV2_t Route;

    // M4_ARRAY_TABLE_DESC("DySetpoint", "array_table_ui", M4_INDEX_DEFAULT)
    CalibDb_AecDynamicSetpointV2_t DySetpoint;

    // M4_STRUCT_DESC("BackLightCtrl", "normal_ui_style")
    CalibDb_AecBacklightV2_t BackLightCtrl;

    // M4_STRUCT_DESC("OverExpCtrl", "normal_ui_style")
    CalibDb_AecOverExpCtrlV2_t OverExpCtrl;
} CalibDb_LinearAE_AttrV2_t;

/*****************************************************************************/
/**
 * @brief   ISP2.0 AEC algo HdrAE Config Params
 */
/*****************************************************************************/
typedef struct CalibDb_HdrExpInitExpV2_s {
    // M4_ARRAY_DESC("InitTimeValue", "f32", M4_SIZE(1,3), M4_RANGE(0,1), "0.01", M4_DIGIT(6), M4_DYNAMIC(0))
    float InitTimeValue[(3)];

    // M4_ARRAY_DESC("InitGainValue", "f32", M4_SIZE(1,3), M4_RANGE(1,4096), "1.0", M4_DIGIT(3), M4_DYNAMIC(0))
    float InitGainValue[(3)];

    // M4_ARRAY_DESC("InitIspDGainValue", "f32", M4_SIZE(1,3), M4_RANGE(1,4096), "1.0", M4_DIGIT(3), M4_DYNAMIC(0))
    float InitIspDGainValue[(3)];

    // M4_NUMBER_DESC("InitPIrisGainValue", "s32", M4_RANGE(1,4096), "1024", M4_DIGIT(0),M4_HIDE(0))
    int InitPIrisGainValue;

    // M4_NUMBER_DESC("InitDCIrisDutyValue", "s32", M4_RANGE(0,100), "100", M4_DIGIT(0),M4_HIDE(0))
    int InitDCIrisDutyValue;
} CalibDb_HdrExpInitExpV2_t;

typedef struct CalibDb_ExpRatioV2_s {
    // M4_ARRAY_DESC("RatioExpDot", "f32", M4_SIZE(1,6), M4_RANGE(0,1), "0", M4_DIGIT(4), M4_DYNAMIC(1))
    float* RatioExpDot;
    int RatioExpDot_len;
    // M4_ARRAY_DESC("M2SRatioFix", "f32", M4_SIZE(1,6), M4_RANGE(1,256), "8", M4_DIGIT(2), M4_DYNAMIC(1))
    float* M2SRatioFix;
    int M2SRatioFix_len;
    // M4_ARRAY_DESC("L2MRatioFix", "f32", M4_SIZE(1,6), M4_RANGE(1,256), "8", M4_DIGIT(2), M4_DYNAMIC(1))
    float* L2MRatioFix;
    int L2MRatioFix_len;
    // M4_ARRAY_DESC("M2SRatioMax", "f32", M4_SIZE(1,6), M4_RANGE(1,256), "64", M4_DIGIT(2), M4_DYNAMIC(1))
    float* M2SRatioMax;
    int M2SRatioMax_len;
    // M4_ARRAY_DESC("L2MRatioMax", "f32", M4_SIZE(1,6), M4_RANGE(1,256), "64", M4_DIGIT(2), M4_DYNAMIC(1))
    float* L2MRatioMax;
    int L2MRatioMax_len;
} CalibDb_ExpRatioV2_t;

typedef struct CalibDb_ExpRatioCtrlV2_s {
    // M4_ENUM_DESC("ExpRatioType", "CalibDb_HdrAeRatioTypeV2_t","AECV2_HDR_RATIOTYPE_MODE_AUTO")
    CalibDb_HdrAeRatioTypeV2_t ExpRatioType;

    // M4_ARRAY_TABLE_DESC("ExpRatio", "array_table_ui", M4_INDEX_DEFAULT)
    CalibDb_ExpRatioV2_t ExpRatio;
} CalibDb_ExpRatioCtrlV2_t;

typedef struct CalibDb_HdrAeRoute_AttrV2_s {
    // M4_ARRAY_DESC("Frm0TimeDot", "f32", M4_SIZE(1,6), M4_RANGE(0,1), "0", M4_DIGIT(6), M4_DYNAMIC(1))
    float* Frm0TimeDot;
    int Frm0TimeDot_len;
    // M4_ARRAY_DESC("Frm0GainDot", "f32", M4_SIZE(1,6), M4_RANGE(1,4096), "1", M4_DIGIT(3), M4_DYNAMIC(1))
    float* Frm0GainDot;
    int Frm0GainDot_len;
    // M4_ARRAY_DESC("Frm0IspDGainDot", "f32", M4_SIZE(1,6), M4_RANGE(1,4096), "1", M4_DIGIT(3), M4_DYNAMIC(1))
    float* Frm0IspDGainDot;
    int Frm0IspDGainDot_len;
    // M4_ARRAY_DESC("Frm1TimeDot", "f32", M4_SIZE(1,6), M4_RANGE(0,1), "0", M4_DIGIT(6), M4_DYNAMIC(1))
    float* Frm1TimeDot;
    int Frm1TimeDot_len;
    // M4_ARRAY_DESC("Frm1GainDot", "f32", M4_SIZE(1,6), M4_RANGE(1,4096), "1", M4_DIGIT(3), M4_DYNAMIC(1))
    float* Frm1GainDot;
    int Frm1GainDot_len;
    // M4_ARRAY_DESC("Frm1IspDGainDot", "f32", M4_SIZE(1,6), M4_RANGE(1,4096), "1", M4_DIGIT(3), M4_DYNAMIC(1))
    float* Frm1IspDGainDot;
    int Frm1IspDGainDot_len;
    // M4_ARRAY_DESC("Frm2TimeDot", "f32", M4_SIZE(1,6), M4_RANGE(0,1), "0", M4_DIGIT(6), M4_DYNAMIC(1))
    float* Frm2TimeDot;
    int Frm2TimeDot_len;
    // M4_ARRAY_DESC("Frm2GainDot", "f32", M4_SIZE(1,6), M4_RANGE(1,4096), "1", M4_DIGIT(3), M4_DYNAMIC(1))
    float* Frm2GainDot;
    int Frm2GainDot_len;
    // M4_ARRAY_DESC("Frm2IspDGainDot", "f32", M4_SIZE(1,6), M4_RANGE(1,4096), "1", M4_DIGIT(3), M4_DYNAMIC(1))
    float* Frm2IspDGainDot;
    int Frm2IspDGainDot_len;
    // M4_ARRAY_DESC("PIrisDot", "s32", M4_SIZE(1,6), M4_RANGE(1,4096), "1024", M4_DIGIT(0), M4_DYNAMIC(1))
    int* PIrisDot;
    int PIrisDot_len;
} CalibDb_HdrAeRoute_AttrV2_t;

typedef struct CalibDb_LfrmSetPointV2_s
{
    // M4_ARRAY_DESC("LExpLevel", "f32", M4_SIZE(1,6), M4_RANGE(0,4096), "0", M4_DIGIT(5), M4_DYNAMIC(1))
    float* LExpLevel;
    int LExpLevel_len;
    // M4_ARRAY_DESC("NonOEPdfTh", "f32", M4_SIZE(1,6), M4_RANGE(0,1), "0.4", M4_DIGIT(2), M4_DYNAMIC(1))
    float* NonOEPdfTh;
    int NonOEPdfTh_len;
    // M4_ARRAY_DESC("LowLightPdfTh", "f32", M4_SIZE(1,6), M4_RANGE(0,1), "0.2", M4_DIGIT(2), M4_DYNAMIC(1))
    float* LowLightPdfTh;
    int LowLightPdfTh_len;
    // M4_ARRAY_DESC("LSetPoint", "f32", M4_SIZE(1,6), M4_RANGE(0,255), "40", M4_DIGIT(2), M4_DYNAMIC(1))
    float* LSetPoint;
    int LSetPoint_len;
    // M4_ARRAY_DESC("TargetLLLuma", "f32", M4_SIZE(1,6), M4_RANGE(0,255), "20", M4_DIGIT(2), M4_DYNAMIC(1))
    float* TargetLLLuma;
    int TargetLLLuma_len;
} CalibDb_LfrmSetPointV2_t;

typedef struct CalibDb_LfrmCtrlV2_s
{
    // M4_NUMBER_DESC("OEROILowTh", "f32", M4_RANGE(0,255), "150", M4_DIGIT(2),M4_HIDE(0))
    float OEROILowTh;

    // M4_NUMBER_DESC("LvLowTh", "f32", M4_RANGE(0,100), "7.5", M4_DIGIT(4),M4_HIDE(0))
    float LvLowTh;

    // M4_NUMBER_DESC("LvHighTh", "f32", M4_RANGE(0,100), "0.3125", M4_DIGIT(4),M4_HIDE(0))
    float LvHighTh;

    // M4_ARRAY_TABLE_DESC("LfrmSetPoint", "array_table_ui", M4_INDEX_DEFAULT)
    CalibDb_LfrmSetPointV2_t LfrmSetPoint;
} CalibDb_LfrmCtrlV2_t;

typedef struct CalibDb_MfrmCtrlV2_s
{
    // M4_ARRAY_DESC("MExpLevel", "f32", M4_SIZE(1,6), M4_RANGE(0,4096), "0", M4_DIGIT(5), M4_DYNAMIC(1))
    float* MExpLevel;
    int MExpLevel_len;
    // M4_ARRAY_DESC("MSetPoint", "f32", M4_SIZE(1,6), M4_RANGE(0,255), "40", M4_DIGIT(2), M4_DYNAMIC(1))
    float* MSetPoint;
    int MSetPoint_len;
} CalibDb_MfrmCtrlV2_t;

typedef struct CalibDb_SfrmSetPointV2_s
{
    // M4_ARRAY_DESC("SExpLevel", "f32", M4_SIZE(1,6), M4_RANGE(0,4096), "0", M4_DIGIT(6), M4_DYNAMIC(1))
    float* SExpLevel;
    int SExpLevel_len;
    // M4_ARRAY_DESC("SSetPoint", "f32", M4_SIZE(1,6), M4_RANGE(0,255), "20", M4_DIGIT(2), M4_DYNAMIC(1))
    float* SSetPoint;
    int SSetPoint_len;
    // M4_ARRAY_DESC("TargetHLLuma", "f32", M4_SIZE(1,6), M4_RANGE(0,255), "150", M4_DIGIT(2), M4_DYNAMIC(1))
    float* TargetHLLuma;
    int TargetHLLuma_len;
} CalibDb_SfrmSetPointV2_t;

typedef struct CalibDb_SfrmCtrlV2_s
{
    // M4_BOOL_DESC("HLROIExpandEn", "0")
    
# 580 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h" 3 4
   _Bool 
# 580 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h"
                               HLROIExpandEn;

    // M4_NUMBER_DESC("HLLumaTolerance", "f32", M4_RANGE(0,100), "12", M4_DIGIT(2),M4_HIDE(0))
    float HLLumaTolerance;//unit:%

    // M4_ARRAY_TABLE_DESC("SfrmSetPoint", "array_table_ui", M4_INDEX_DEFAULT)
    CalibDb_SfrmSetPointV2_t SfrmSetPoint;
} CalibDb_SfrmCtrlV2_t;

typedef struct CalibDb_LongFrmCtrlV2_s {
    // M4_ENUM_DESC("mode", "CalibDb_AeHdrLongFrmModeV2_t","AECV2_HDR_LONGFRMMODE_NORMAL")
    CalibDb_AeHdrLongFrmModeV2_t mode;

    // M4_NUMBER_DESC("SfrmMinLine", "u16", M4_RANGE(0,1024), "2", M4_DIGIT(0),M4_HIDE(0))
    uint16_t SfrmMinLine;//uint:line

    // M4_NUMBER_DESC("LfrmModeExpTh", "f32", M4_RANGE(0,100), "0.62", M4_DIGIT(4),M4_HIDE(0))
    float LfrmModeExpTh;
} CalibDb_LongFrmCtrlV2_t;

typedef struct CalibDb_HdrAE_AttrV2_s {
    // M4_NUMBER_DESC("ToleranceIn", "f32", M4_RANGE(0,100), "10", M4_DIGIT(2),M4_HIDE(0))
    float ToleranceIn;//unit:%

    // M4_NUMBER_DESC("ToleranceOut", "f32", M4_RANGE(0,100), "15", M4_DIGIT(2),M4_HIDE(0))
    float ToleranceOut;//unit:%

    // M4_NUMBER_DESC("Evbias", "f32", M4_RANGE(-500,500), "0", M4_DIGIT(0),M4_HIDE(1))
    float Evbias;

    // M4_ENUM_DESC("StrategyMode", "CalibDb_AeStrategyModeV2_t","AECV2_STRATEGY_MODE_LOWLIGHT_PRIOR")
    CalibDb_AeStrategyModeV2_t StrategyMode;

    // M4_NUMBER_DESC("LumaDistTh", "f32", M4_RANGE(0,100), "10", M4_DIGIT(2),M4_HIDE(0))
    float LumaDistTh; //used for area-growing,unit:%

    // M4_STRUCT_DESC("InitExp", "normal_ui_style")
    CalibDb_HdrExpInitExpV2_t InitExp;

    // M4_ARRAY_TABLE_DESC("Route", "array_table_ui", M4_INDEX_DEFAULT)
    CalibDb_HdrAeRoute_AttrV2_t Route;

    // M4_STRUCT_DESC("ExpRatioCtrl", "normal_ui_style")
    CalibDb_ExpRatioCtrlV2_t ExpRatioCtrl;

    // M4_STRUCT_DESC("LongFrmMode", "normal_ui_style")
    CalibDb_LongFrmCtrlV2_t LongFrmMode;

    // M4_STRUCT_DESC("LframeCtrl", "normal_ui_style")
    CalibDb_LfrmCtrlV2_t LframeCtrl;

    // M4_ARRAY_TABLE_DESC("MframeCtrl", "array_table_ui", M4_INDEX_DEFAULT)
    CalibDb_MfrmCtrlV2_t MframeCtrl;

    // M4_STRUCT_DESC("SframeCtrl", "normal_ui_style")
    CalibDb_SfrmCtrlV2_t SframeCtrl;
} CalibDb_HdrAE_AttrV2_t;

/*****************************************************************************/
/**
 * @brief   ISP2.0 AEC algo SyncTest Config Params
 */
/*****************************************************************************/
typedef struct CalibDb_LinAlterExpV2_s {
    // M4_NUMBER_DESC("TimeValue", "f32", M4_RANGE(0,1), "0.01", M4_DIGIT(6),M4_HIDE(0))
    float TimeValue;

    // M4_NUMBER_DESC("GainValue", "f32", M4_RANGE(1,4096), "1", M4_DIGIT(3),M4_HIDE(0))
    float GainValue;

    // M4_NUMBER_DESC("IspDGainValue", "f32", M4_RANGE(1,4096), "1", M4_DIGIT(3),M4_HIDE(0))
    float IspDGainValue;

    // M4_NUMBER_DESC("PIrisGainValue", "s32", M4_RANGE(1,4096), "1024", M4_DIGIT(0),M4_HIDE(0))
    int PIrisGainValue;

    // M4_NUMBER_DESC("DcgMode", "s32", M4_RANGE(-1,1), "0", M4_DIGIT(0),M4_HIDE(0))
    int DcgMode;
} CalibDb_LinAlterExpV2_t;

typedef struct CalibDb_HdrAlterExpV2_s {
    // M4_ARRAY_DESC("TimeValue", "f32", M4_SIZE(1,3), M4_RANGE(0,1), "0.01", M4_DIGIT(6), M4_DYNAMIC(0))
    float TimeValue[(3)];

    // M4_ARRAY_DESC("GainValue", "f32", M4_SIZE(1,3), M4_RANGE(1,4096), "1.0", M4_DIGIT(3), M4_DYNAMIC(0))
    float GainValue[(3)];

    // M4_ARRAY_DESC("IspDGainValue", "f32", M4_SIZE(1,3), M4_RANGE(1,4096), "1.0", M4_DIGIT(3), M4_DYNAMIC(0))
    float IspDGainValue[(3)];

    // M4_NUMBER_DESC("PIrisGainValues", "s32", M4_RANGE(1,4096), "1024", M4_DIGIT(0),M4_HIDE(0))
    int PIrisGainValue;

    // M4_ARRAY_DESC("DcgMode", "s32", M4_SIZE(1,3), M4_RANGE(-1,1), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    int DcgMode[(3)];
} CalibDb_HdrAlterExpV2_t;

typedef struct CalibDb_AlterExpV2_s {
    // M4_STRUCT_LIST_DESC("LinearAE", M4_SIZE_DYNAMIC,"normal_ui_style")
    CalibDb_LinAlterExpV2_t* LinearAE;
    int LinearAE_len;

    // M4_STRUCT_LIST_DESC("HdrAE", M4_SIZE_DYNAMIC,"normal_ui_style")
    CalibDb_HdrAlterExpV2_t* HdrAE;
    int HdrAE_len;
} CalibDb_AlterExpV2_t;

typedef struct CalibDb_AeSyncTestV2_s {
    // M4_BOOL_DESC("Enable", "0")
    
# 689 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h" 3 4
   _Bool 
# 689 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h"
                               Enable;

    // M4_NUMBER_DESC("IntervalFrm", "s32", M4_RANGE(0,1024), "5", M4_DIGIT(0),M4_HIDE(0))
    int IntervalFrm;

    // M4_STRUCT_DESC("AlterExp", "normal_ui_style")
    CalibDb_AlterExpV2_t AlterExp;
} CalibDb_AeSyncTestV2_t;

/*****************************************************************************/
/**
 * @brief   ISP2.0 AEC algo IrisCtrl Config Params
 */
/*****************************************************************************/
typedef struct CalibDb_MIris_AttrV2_s {
    // M4_NUMBER_DESC("PIrisGainValue", "s32", M4_RANGE(1,4096), "1024", M4_DIGIT(0),M4_HIDE(0))
    int PIrisGainValue;

    // M4_NUMBER_DESC("DCIrisHoldValue", "s32", M4_RANGE(0,100), "50", M4_DIGIT(0),M4_HIDE(0))
    int DCIrisHoldValue;
} CalibDb_MIris_AttrV2_t;

typedef struct CalibDb_PIris_AttrV2_s {
    // M4_NUMBER_DESC("TotalStep", "u16", M4_RANGE(0,1024), "81", M4_DIGIT(0),M4_HIDE(0))
    uint16_t TotalStep;

    // M4_NUMBER_DESC("EffcStep", "u16", M4_RANGE(0,1024), "64", M4_DIGIT(0),M4_HIDE(0))
    uint16_t EffcStep;

    // M4_BOOL_DESC("ZeroIsMax", "1")
    
# 719 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h" 3 4
   _Bool 
# 719 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h"
                        ZeroIsMax;

    // M4_ARRAY_DESC("StepTable", "u16", M4_SIZE(1,1024), M4_RANGE(1,4096), "1024", M4_DIGIT(0), M4_DYNAMIC(0))
    uint16_t StepTable[(1024)];
} CalibDb_PIris_AttrV2_t;

typedef struct CalibDb_DCIris_AttrV2_s {
    // M4_NUMBER_DESC("Kp", "f32", M4_RANGE(0,10), "1", M4_DIGIT(2),M4_HIDE(0))
    float Kp;
    // M4_NUMBER_DESC("Ki", "f32", M4_RANGE(0,10), "0.2", M4_DIGIT(2),M4_HIDE(0))
    float Ki;
    // M4_NUMBER_DESC("Kd", "f32", M4_RANGE(0,10), "0.5", M4_DIGIT(2),M4_HIDE(0))
    float Kd;
    // M4_NUMBER_DESC("MinPwmDuty", "s32", M4_RANGE(0,100), "0", M4_DIGIT(0),M4_HIDE(0))
    int MinPwmDuty;
    // M4_NUMBER_DESC("MaxPwmDuty", "s32", M4_RANGE(0,100), "100", M4_DIGIT(0),M4_HIDE(0))
    int MaxPwmDuty;
    // M4_NUMBER_DESC("OpenPwmDuty", "s32", M4_RANGE(0,100), "50", M4_DIGIT(0),M4_HIDE(0))
    int OpenPwmDuty;
    // M4_NUMBER_DESC("ClosePwmDuty", "s32", M4_RANGE(0,100), "60", M4_DIGIT(0),M4_HIDE(0))
    int ClosePwmDuty;
} CalibDb_DCIris_AttrV2_t;

typedef struct CalibDb_AecIrisCtrlV2_s {
    // M4_BOOL_DESC("Enable", "0")
    
# 744 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h" 3 4
   _Bool 
# 744 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h"
                                Enable;

    // M4_ENUM_DESC("IrisType", "CalibDb_IrisTypeV2_t","IRISV2_DC_TYPE")
    CalibDb_IrisTypeV2_t IrisType;

    // M4_BOOL_DESC("ManualEn", "0")
    
# 750 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h" 3 4
   _Bool 
# 750 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h"
                                ManualEn;

    // M4_STRUCT_DESC("ManualAttr", "normal_ui_style")
    CalibDb_MIris_AttrV2_t ManualAttr;

    // M4_STRUCT_DESC("InitAttr", "normal_ui_style")
    CalibDb_MIris_AttrV2_t InitAttr;

    // M4_STRUCT_DESC("PIrisAttr", "normal_ui_style")
    CalibDb_PIris_AttrV2_t PIrisAttr;

    // M4_STRUCT_DESC("DCIrisAttr", "normal_ui_style")
    CalibDb_DCIris_AttrV2_t DCIrisAttr;
} CalibDb_AecIrisCtrlV2_t;

/*****************************************************************************/
/**
 * @brief   Global AEC tuning structure of isp2.0
 */
/*****************************************************************************/
typedef struct CalibDb_Aec_ParaV2_s {
    // M4_STRUCT_DESC("CommCtrl", "normal_ui_style")
    CalibDb_AecCommon_AttrV2_t CommCtrl;

    // M4_STRUCT_DESC("LinearAeCtrl", "normal_ui_style")
    CalibDb_LinearAE_AttrV2_t LinearAeCtrl;

    // M4_STRUCT_DESC("HdrAeCtrl", "normal_ui_style")
    CalibDb_HdrAE_AttrV2_t HdrAeCtrl;

    // M4_STRUCT_DESC("IrisCtrl", "normal_ui_style")
    CalibDb_AecIrisCtrlV2_t IrisCtrl;

    // M4_STRUCT_DESC("SyncTest", "normal_ui_style")
    CalibDb_AeSyncTestV2_t SyncTest; //special module for debug
} CalibDb_Aec_ParaV2_t;


# 27 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/af_head.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/af_head.h" 2








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
    // M4_ARRAY_DESC("QuickFoundThersZoomIdx", "u16", M4_SIZE(1,32), M4_RANGE(0,65535), "0", M4_DIGIT(0), M4_DYNAMIC(1))
    unsigned short *QuickFoundThersZoomIdx;
    int QuickFoundThersZoomIdx_len;
    // M4_ARRAY_DESC("QuickFoundThers", "f32", M4_SIZE(1,32), M4_RANGE(0,1), "0", M4_DIGIT(3), M4_DYNAMIC(1))
    float *QuickFoundThers;
    int QuickFoundThers_len;
    // M4_ARRAY_DESC("SearchStepZoomIdx", "u16", M4_SIZE(1,32), M4_RANGE(0,65535), "0", M4_DIGIT(0), M4_DYNAMIC(1))
    unsigned short *SearchStepZoomIdx;
    int SearchStepZoomIdx_len;
    // M4_ARRAY_DESC("SearchStep", "u16", M4_SIZE(1,32), M4_RANGE(0,65535), "0", M4_DIGIT(0), M4_DYNAMIC(1))
    unsigned short *SearchStep;
    int SearchStep_len;
    // M4_ARRAY_DESC("StopStepZoomIdx", "u16", M4_SIZE(1,32), M4_RANGE(0,65535), "0", M4_DIGIT(0), M4_DYNAMIC(1))
    unsigned short *StopStepZoomIdx;
    int StopStepZoomIdx_len;
    // M4_ARRAY_DESC("StopStep", "u16", M4_SIZE(1,32), M4_RANGE(0,65535), "0", M4_DIGIT(0), M4_DYNAMIC(1))
    unsigned short *StopStep;
    int StopStep_len;
    // M4_NUMBER_DESC("SkipHighPassZoomIdx", "u16", M4_RANGE(0, 65535), "0", M4_DIGIT(0))
    unsigned short SkipHighPassZoomIdx;
    // M4_NUMBER_DESC("SkipHighPassGain", "f32", M4_RANGE(0, 1000), "0", M4_DIGIT(3))
    float SkipHighPassGain;
    // M4_NUMBER_DESC("SwitchDirZoomIdx", "u16", M4_RANGE(0, 65535), "0", M4_DIGIT(0))
    unsigned short SwitchDirZoomIdx;

    // M4_NUMBER_DESC("Spotlight HighlightRatio", "f32", M4_RANGE(0, 1), "0.014", M4_DIGIT(3))
    float SpotlightHighlightRatio;
    // M4_ARRAY_DESC("Spotlight LumaRatio", "f32", M4_SIZE(1,3), M4_RANGE(0,1), "[0.3, 0.5, 0.8]", M4_DIGIT(3), M4_DYNAMIC(0))
    float SpotlightLumaRatio[3];
    // M4_ARRAY_DESC("Spotlight BlkCnt", "f32", M4_SIZE(1,3), M4_RANGE(0,1), "[0.2, 0.5, 0.25]", M4_DIGIT(3), M4_DYNAMIC(0))
    float SpotlightBlkCnt[3];
} CalibDbV2_Af_ContrastZoom_t;

typedef struct CalibDbV2_Af_Contrast_s {
    // M4_BOOL_DESC("enable", "0")
    
# 105 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/af_head.h" 3 4
   _Bool 
# 105 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/af_head.h"
        enable;
    // M4_ENUM_DESC("SearchStrategy", "CalibDbV2_Af_SS_t", "CalibDbV2_CAM_AFM_FSS_ADAPTIVE_RANGE")
    CalibDbV2_Af_SS_t Afss; /**< enumeration type for search strategy */
    // M4_ENUM_DESC("FullDir", "CalibDbV2_Af_SearchDir_t", "CalibDbV2_CAM_AFM_ADAPTIVE_SEARCH")
    CalibDbV2_Af_SearchDir_t FullDir;
    // M4_ARRAY_DESC("FullRangeTbl", "u16", M4_SIZE(1,65), M4_RANGE(0,64), "0", M4_DIGIT(0), M4_DYNAMIC(1))
    unsigned short *FullRangeTbl; /**< full range search table*/
    int FullRangeTbl_len;
    // M4_ENUM_DESC("AdaptiveDir", "CalibDbV2_Af_SearchDir_t", "CalibDbV2_CAM_AFM_ADAPTIVE_SEARCH")
    CalibDbV2_Af_SearchDir_t AdaptiveDir;
    // M4_ARRAY_DESC("AdaptRangeTbl", "u16", M4_SIZE(1,65), M4_RANGE(0,64), "0", M4_DIGIT(0), M4_DYNAMIC(1))
    unsigned short *AdaptRangeTbl; /**< adaptive range search table*/
    int AdaptRangeTbl_len;
    // M4_ARRAY_DESC("TrigThers", "f32", M4_SIZE(1,32), M4_RANGE(0,1), "0", M4_DIGIT(3), M4_DYNAMIC(1))
    float *TrigThers; /**< AF trigger threshold */
    int TrigThers_len;
    // M4_ARRAY_DESC("TrigThersFv", "f32", M4_SIZE(1,32), M4_RANGE(0,100000000000), "0", M4_DIGIT(0), M4_DYNAMIC(1))
    float *TrigThersFv; /**< AF trigger threshold */
    int TrigThersFv_len;
    // M4_NUMBER_DESC("LumaTrigThers", "f32", M4_RANGE(0,1), "0", M4_DIGIT(3),M4_HIDE(0))
    float LumaTrigThers;
    // M4_NUMBER_DESC("ExpTrigThers", "f32", M4_RANGE(0,1), "0", M4_DIGIT(3),M4_HIDE(0))
    float ExpTrigThers;

    // M4_NUMBER_DESC("StableThers", "f32", M4_RANGE(0,1), "0", M4_DIGIT(3),M4_HIDE(0))
    float StableThers; /**< AF stable threshold */
    // M4_NUMBER_DESC("StableFrames", "u16", M4_RANGE(0,65535), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned short StableFrames; /**< AF stable  status must hold frames */
    // M4_NUMBER_DESC("StableTime", "u16", M4_RANGE(0,65535), "0", M4_DIGIT(3),M4_HIDE(0))
    unsigned short StableTime; /**< AF stable status must hold time */

    // M4_NUMBER_DESC("SceneDiffEnable", "u8", M4_RANGE(0, 1), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned char SceneDiffEnable;
    // M4_NUMBER_DESC("SceneDiffThers", "f32", M4_RANGE(0,1), "0", M4_DIGIT(3),M4_HIDE(0))
    float SceneDiffThers;
    // M4_NUMBER_DESC("SceneDiffBlkThers", "u16", M4_RANGE(0,225), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned short SceneDiffBlkThers;
    // M4_NUMBER_DESC("CenterSceneDiffThers", "f32", M4_RANGE(0,1), "0", M4_DIGIT(3),M4_HIDE(0))
    float CenterSceneDiffThers;

    // M4_NUMBER_DESC("ValidMaxMinRatio", "f32", M4_RANGE(0,1), "0", M4_DIGIT(3),M4_HIDE(0))
    float ValidMaxMinRatio;
    // M4_NUMBER_DESC("ValidValueThers", "f32", M4_RANGE(0,1), "0", M4_DIGIT(3),M4_HIDE(0))
    float ValidValueThers;

    // M4_NUMBER_DESC("OutFocusValue", "f32", M4_RANGE(0,1000000), "0", M4_DIGIT(3),M4_HIDE(0))
    float OutFocusValue; /**< out of focus vlaue*/
    // M4_NUMBER_DESC("OutFocusPos", "u16", M4_RANGE(0,65), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned short OutFocusPos; /**< out of focus position*/

    // M4_NUMBER_DESC("WeightEnable", "u8", M4_RANGE(0, 1), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned char WeightEnable;
    // M4_ARRAY_DESC("Weight", "u16", M4_SIZE(15,15), M4_RANGE(0,65535), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned short Weight[225]; /**< weight */

    // M4_NUMBER_DESC("SearchPauseLumaEnable", "u8", M4_RANGE(0, 1), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned char SearchPauseLumaEnable;
    // M4_NUMBER_DESC("SearchPauseLumaThers", "f32", M4_RANGE(0,1), "0", M4_DIGIT(3),M4_HIDE(0))
    float SearchPauseLumaThers;
    // M4_NUMBER_DESC("StableFrames", "u16", M4_RANGE(0,65535), "0", M4_DIGIT(3),M4_HIDE(0))
    unsigned short SearchLumaStableFrames;
    // M4_NUMBER_DESC("SearchLumaStableThers", "f32", M4_RANGE(0,1), "0", M4_DIGIT(3),M4_HIDE(0))
    float SearchLumaStableThers;

    // M4_NUMBER_DESC("Stage1QuickFoundThers", "f32", M4_RANGE(0,1), "0", M4_DIGIT(3),M4_HIDE(0))
    float Stage1QuickFoundThers;
    // M4_NUMBER_DESC("Stage2QuickFoundThers", "f32", M4_RANGE(0,1), "0", M4_DIGIT(3),M4_HIDE(0))
    float Stage2QuickFoundThers;

    // M4_NUMBER_DESC("FlatValue", "f32", M4_RANGE(0,65535), "0", M4_DIGIT(3),M4_HIDE(0))
    float FlatValue;

    // M4_NUMBER_DESC("PointLightLumaTh", "u16", M4_RANGE(0,65535), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned short PointLightLumaTh; /**< point light luma threshold */
    // M4_NUMBER_DESC("PointLightCntTh", "u16", M4_RANGE(0,65535), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned short PointLightCntTh; /**< point light count threshold */

    // M4_STRUCT_DESC("ZoomConfig", "normal_ui_style")
    CalibDbV2_Af_ContrastZoom_t ZoomCfg;
} CalibDbV2_Af_Contrast_t;

typedef struct CalibDbV2_Af_Laser_s {
    // M4_BOOL_DESC("enable", "0")
    
# 188 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/af_head.h" 3 4
   _Bool 
# 188 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/af_head.h"
        enable;
    // M4_ARRAY_DESC("vcmDot", "f32", M4_SIZE(1,7), M4_RANGE(0,64), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    float vcmDot[7];
    // M4_ARRAY_DESC("distanceDot", "f32", M4_SIZE(1,7), M4_RANGE(0,65535), "0", M4_DIGIT(4), M4_DYNAMIC(0))
    float distanceDot[7];
} CalibDbV2_Af_Laser_t;

typedef struct CalibDbV2_Af_Pdaf_fineSearch_s {
    // M4_NUMBER_DESC("confidence", "u32", M4_RANGE(0,1000), "0", M4_DIGIT(0))
    unsigned int confidence;
    // M4_NUMBER_DESC("range", "s32", M4_RANGE(0,64), "0", M4_DIGIT(0))
    int range;
    // M4_NUMBER_DESC("stepPos", "s32", M4_RANGE(1,64), "1", M4_DIGIT(0))
    int stepPos;
} CalibDbV2_Af_Pdaf_fineSearch_t;

typedef struct CalibDbV2_Af_PdafIsoPara_s {
    // M4_NUMBER_DESC("iso", "u32", M4_RANGE(0, 1000000), "0", M4_DIGIT(0))
    int iso;
    // M4_NUMBER_DESC("pdNoiseFactor", "f32", M4_RANGE(0,1), "0", M4_DIGIT(3),M4_HIDE(0))
    float pdNoiseFactor;
    // M4_NUMBER_DESC("pdConfdRatio1", "f32", M4_RANGE(0,1), "0", M4_DIGIT(3),M4_HIDE(0))
    float pdConfdRatio1;
    // M4_NUMBER_DESC("pdConfdRatio2", "f32", M4_RANGE(0,1), "0", M4_DIGIT(3),M4_HIDE(0))
    float pdConfdRatio2;
    // M4_NUMBER_DESC("pdConfdRhresh", "f32", M4_RANGE(0,1), "0", M4_DIGIT(3),M4_HIDE(0))
    float pdConfdThresh;
    // M4_NUMBER_DESC("defocusPdThresh", "f32", M4_RANGE(0,1), "0", M4_DIGIT(3),M4_HIDE(0))
    float defocusPdThresh;
    // M4_NUMBER_DESC("stablePdRatio", "f32", M4_RANGE(0,255), "0", M4_DIGIT(3),M4_HIDE(0))
    float stablePdRatio;
    // M4_NUMBER_DESC("stablePdOffset", "f32", M4_RANGE(0,255), "0", M4_DIGIT(3),M4_HIDE(0))
    float stablePdOffset;
    // M4_NUMBER_DESC("stableCntRatio", "f32", M4_RANGE(0,1), "0", M4_DIGIT(3),M4_HIDE(0))
    float stableCntRatio;
    // M4_NUMBER_DESC("noconfCntThresh", "u16", M4_RANGE(0,255), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned short noconfCntThresh;
    // M4_STRUCT_LIST_DESC("fineSearchTbl", M4_SIZE(1,10), "normal_ui_style")
    CalibDbV2_Af_Pdaf_fineSearch_t* fineSearchTbl;
    int fineSearchTbl_len;
} CalibDbV2_Af_PdafIsoPara_t;

typedef struct CalibDbV2_Af_Pdaf_s {
    // M4_BOOL_DESC("enable", "0")
    
# 232 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/af_head.h" 3 4
   _Bool 
# 232 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/af_head.h"
        enable;
    // M4_NUMBER_DESC("pdVsCdDebug", "u8", M4_RANGE(0, 1), "0", M4_DIGIT(0))
    unsigned char pdVsCdDebug;
    // M4_NUMBER_DESC("pdDataBit", "u16", M4_RANGE(1,16), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned short pdDataBit;
    // M4_NUMBER_DESC("pdBlkLevel", "u16", M4_RANGE(1,1023), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned short pdBlkLevel;
    // M4_NUMBER_DESC("pdSearchRadius", "u16", M4_RANGE(0,32), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned short pdSearchRadius;
    // M4_NUMBER_DESC("pdMirrorInCalib", "u8", M4_RANGE(0, 1), "0", M4_DIGIT(0))
    unsigned char pdMirrorInCalib;
    // M4_NUMBER_DESC("pdWidth", "u16", M4_RANGE(0, 65535), "0", M4_DIGIT(0))
    unsigned short pdWidth;
    // M4_NUMBER_DESC("pdHeight", "u16", M4_RANGE(0, 65535), "0", M4_DIGIT(0))
    unsigned short pdHeight;
    // M4_STRUCT_LIST_DESC("pdIsoPara", M4_SIZE(1,16), "normal_ui_style")
    CalibDbV2_Af_PdafIsoPara_t* pdIsoPara;
    int pdIsoPara_len;
} CalibDbV2_Af_Pdaf_t;

typedef struct CalibDbV2_Af_VcmCfg_s {
    // M4_NUMBER_DESC("start current", "s32", M4_RANGE(-1, 2048), "-1", M4_DIGIT(0))
    int start_current;
    // M4_NUMBER_DESC("rated current", "s32", M4_RANGE(-1, 2048), "-1", M4_DIGIT(0))
    int rated_current;
    // M4_NUMBER_DESC("step mode", "s32", M4_RANGE(-1, 1000), "-1", M4_DIGIT(0))
    int step_mode;
    // M4_NUMBER_DESC("extra delay", "s32", M4_RANGE(-10000,10000), "0", M4_DIGIT(0))
    int extra_delay;
    // M4_NUMBER_DESC("posture diff", "f32", M4_RANGE(0,1), "0", M4_DIGIT(3))
    float posture_diff;
} CalibDbV2_Af_VcmCfg_t;

typedef struct CalibDbV2_Af_MeasIsoCfg_s {
    // M4_NUMBER_DESC("iso", "u32", M4_RANGE(0, 1000000), "0", M4_DIGIT(0))
    int iso;
    // M4_NUMBER_DESC("afmThres", "u16", M4_RANGE(0, 255), "4", M4_DIGIT(0))
    unsigned short afmThres;
    // M4_ARRAY_MARK_DESC("Gamma_curve", "u16", M4_SIZE(1,17),  M4_RANGE(0, 1023), "[0,45,108,179,245,344,409,459,500,567,622,676,759,833,896,962,1023]", M4_DIGIT(0), M4_DYNAMIC(0), "curve_table")
    unsigned short gammaY[17];
    // M4_ARRAY_DESC("gaussWeight", "u8", M4_SIZE(1,3), M4_RANGE(0,128), "[16,14,14]", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char gaussWeight[3];
} CalibDbV2_Af_MeasIsoCfg_t;

typedef struct CalibDbV2_Af_DefCode_s {
    // M4_NUMBER_DESC("code", "u8", M4_RANGE(0, 64), "0", M4_DIGIT(0))
    unsigned char code;
} CalibDbV2_Af_DefCode_t;

typedef struct CalibDbV2_Af_FocusCode_s {
    // M4_NUMBER_DESC("focus position", "f32", M4_RANGE(0, 1000000), "0", M4_DIGIT(3), M4_HIDE(1))
    float pos;
    // M4_ARRAY_DESC("focus code", "s16", M4_SIZE(1,5000), M4_RANGE(-32768,32767), "0", M4_DIGIT(0), M4_DYNAMIC(1), M4_HIDE(1))
    short *code;
    int code_len;
} CalibDbV2_Af_FocusCode_t;

typedef struct CalibDbV2_Af_ZoomFocusTbl_s {
    // M4_NUMBER_DESC("widemod deviate", "u32", M4_RANGE(0, 1000), "0", M4_DIGIT(0))
    int widemod_deviate;
    // M4_NUMBER_DESC("telemod deviate", "u32", M4_RANGE(0, 1000), "0", M4_DIGIT(0))
    int telemod_deviate;
    // M4_ARRAY_DESC("zoom move dot", "u32", M4_SIZE(1,32), M4_RANGE(0,1000000), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    int *zoom_move_dot;
    int zoom_move_dot_len;
    // M4_ARRAY_DESC("zoom move step", "u32", M4_SIZE(1,32), M4_RANGE(0,1000000), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    int *zoom_move_step;
    int zoom_move_step_len;
    // M4_ARRAY_DESC("focal length", "f32", M4_SIZE(1,5000), M4_RANGE(0,10000), "0", M4_DIGIT(3), M4_DYNAMIC(1), M4_HIDE(1))
    float *focal_length;
    int focal_length_len;
    // M4_ARRAY_DESC("zoom code", "s16", M4_SIZE(1,5000), M4_RANGE(-32768,32767), "0", M4_DIGIT(0), M4_DYNAMIC(1), M4_HIDE(1))
    short *zoomcode;
    int zoomcode_len;
    // M4_STRUCT_LIST_DESC("focus code", M4_SIZE_DYNAMIC, "normal_ui_style", M4_HIDE(1))
    CalibDbV2_Af_FocusCode_t *focuscode;
    int focuscode_len;

    // M4_ARRAY_DESC("zoom search table", "s32", M4_SIZE(1,100), M4_RANGE(-32768,32767), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    int *ZoomSearchTbl;
    // M4_NUMBER_DESC("zoom search table number", "u32", M4_RANGE(0, 100), "0", M4_DIGIT(0))
    int ZoomSearchTbl_len;
    // M4_NUMBER_DESC("zoom search reference curve", "u32", M4_RANGE(0, 32), "0", M4_DIGIT(0))
    int ZoomSearchRefCurveIdx;
    // M4_NUMBER_DESC("zoom search margin", "u32", M4_RANGE(0, 100000), "0", M4_DIGIT(0))
    int FocusSearchMargin;
    // M4_ARRAY_DESC("zoom search plus range", "u32", M4_SIZE(1,100), M4_RANGE(0,32767), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    int *FocusSearchPlusRange;
    int FocusSearchPlusRange_len;
    // M4_NUMBER_DESC("focus stage1 step", "u32", M4_RANGE(0, 100), "0", M4_DIGIT(0))
    int FocusStage1Step;
    // M4_NUMBER_DESC("quickFndRate", "f32", M4_RANGE(0,1), "0", M4_DIGIT(3),M4_HIDE(0))
    float QuickFndRate;
    // M4_NUMBER_DESC("quickFndMinFv", "f32", M4_RANGE(0,2147483647), "0", M4_DIGIT(0),M4_HIDE(0))
    float QuickFndMinFv;
    // M4_NUMBER_DESC("search zoom range", "u32", M4_RANGE(0, 100000), "0", M4_DIGIT(0))
    int searchZoomRange;
    // M4_NUMBER_DESC("search focus range", "u32", M4_RANGE(0, 100000), "0", M4_DIGIT(0))
    int searchFocusRange;
    // M4_NUMBER_DESC("search emax", "f32", M4_RANGE(0,100000), "0", M4_DIGIT(3),M4_HIDE(0))
    float searchEmax;
    // M4_NUMBER_DESC("search eavg", "f32", M4_RANGE(0,100000), "0", M4_DIGIT(3),M4_HIDE(0))
    float searchEavg;

    // M4_NUMBER_DESC("IsZoomFocusRec", "u8", M4_RANGE(0, 1), "0", M4_DIGIT(0))
    unsigned char IsZoomFocusRec;
    // M4_STRING_DESC("ZoomInfoDir", M4_SIZE(1,1), M4_RANGE(0, 64), "/data/", M4_DYNAMIC(0))
    char *ZoomInfoDir;
} CalibDbV2_Af_ZoomFocusTbl_t;

typedef struct CalibDb_Af_LdgParam_s {
    // M4_NUMBER_DESC("enable", "u8", M4_RANGE(0, 1), "0", M4_DIGIT(0))
    unsigned char enable;
    // M4_NUMBER_DESC("ldg xl", "u32", M4_RANGE(0, 255), "0", M4_DIGIT(0))
    int ldg_xl;
    // M4_NUMBER_DESC("ldg yl", "u32", M4_RANGE(0, 255), "0", M4_DIGIT(0))
    int ldg_yl;
    // M4_NUMBER_DESC("ldg kl", "u32", M4_RANGE(0, 2147483647), "0", M4_DIGIT(0))
    int ldg_kl;
    // M4_NUMBER_DESC("ldg xh", "u32", M4_RANGE(0, 255), "0", M4_DIGIT(0))
    int ldg_xh;
    // M4_NUMBER_DESC("ldg yh", "u32", M4_RANGE(0, 255), "0", M4_DIGIT(0))
    int ldg_yh;
    // M4_NUMBER_DESC("ldg kh", "u32", M4_RANGE(0, 2147483647), "0", M4_DIGIT(0))
    int ldg_kh;
} CalibDbV2_Af_LdgParam_t;

typedef struct CalibDb_Af_HighLightParam_s {
    // M4_NUMBER_DESC("ther0", "u32", M4_RANGE(0, 255), "245", M4_DIGIT(0))
    int ther0;
    // M4_NUMBER_DESC("ther1", "u32", M4_RANGE(0, 255), "200", M4_DIGIT(0))
    int ther1;
} CalibDbV2_Af_HighLightParam_t;

typedef struct CalibDbV2_AF_Tuning_Para_s {
    // M4_ENUM_DESC("mode", "CalibDbV2_AF_MODE_t", "CalibDbV2_AF_MODE_CONTINUOUS_PICTURE")
    CalibDbV2_AF_MODE_t af_mode;
    // M4_NUMBER_DESC("win_h_offs", "u16", M4_RANGE(0,2000), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned short win_h_offs;
    // M4_NUMBER_DESC("win_v_offs", "u16", M4_RANGE(0,2000), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned short win_v_offs;
    // M4_NUMBER_DESC("win_h_size", "u16", M4_RANGE(0,2000), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned short win_h_size;
    // M4_NUMBER_DESC("win_v_size", "u16", M4_RANGE(0,2000), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned short win_v_size;
    // M4_NUMBER_DESC("win_h_offs in video", "u16", M4_RANGE(0,2000), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned short video_win_h_offs;
    // M4_NUMBER_DESC("win_v_offs in video", "u16", M4_RANGE(0,2000), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned short video_win_v_offs;
    // M4_NUMBER_DESC("win_h_size in video", "u16", M4_RANGE(0,2000), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned short video_win_h_size;
    // M4_NUMBER_DESC("win_v_size in video", "u16", M4_RANGE(0,2000), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned short video_win_v_size;
    // M4_STRUCT_DESC("fixed mode", "normal_ui_style")
    CalibDbV2_Af_DefCode_t fixed_mode;
    // M4_STRUCT_DESC("macro mode", "normal_ui_style")
    CalibDbV2_Af_DefCode_t macro_mode;
    // M4_STRUCT_DESC("infinity mode", "normal_ui_style")
    CalibDbV2_Af_DefCode_t infinity_mode;
    // M4_STRUCT_DESC("ldg param", "normal_ui_style")
    CalibDbV2_Af_LdgParam_t ldg_param;
    // M4_STRUCT_DESC("high light", "normal_ui_style")
    CalibDbV2_Af_HighLightParam_t highlight;
    // M4_STRUCT_DESC("contrast af", "normal_ui_style")
    CalibDbV2_Af_Contrast_t contrast_af;
    // M4_STRUCT_DESC("video contrast af", "normal_ui_style")
    CalibDbV2_Af_Contrast_t video_contrast_af;
    // M4_STRUCT_DESC("laser af", "normal_ui_style")
    CalibDbV2_Af_Laser_t laser_af;
    // M4_STRUCT_DESC("pdaf", "normal_ui_style")
    CalibDbV2_Af_Pdaf_t pdaf;
    // M4_STRUCT_DESC("vcmcfg", "normal_ui_style")
    CalibDbV2_Af_VcmCfg_t vcmcfg;
    // M4_STRUCT_DESC("zoomfocus_tbl", "normal_ui_style")
    CalibDbV2_Af_ZoomFocusTbl_t zoomfocus_tbl;
    // M4_STRUCT_LIST_DESC("meas iso config", M4_SIZE(1,13), "normal_ui_style")
    CalibDbV2_Af_MeasIsoCfg_t measiso_cfg[13];
} CalibDbV2_AF_Tuning_Para_t;

typedef struct {
    // M4_STRUCT_DESC("TuningPara", "normal_ui_style")
    CalibDbV2_AF_Tuning_Para_t TuningPara;
} CalibDbV2_AF_t;

typedef struct CalibDbV2_AfV30_MeasCfg_s {
    // M4_NUMBER_DESC("table index", "u32", M4_RANGE(0, 1000000), "0", M4_DIGIT(0))
    unsigned int tbl_idx;
    // M4_NUMBER_DESC("afmThres", "u16", M4_RANGE(0, 255), "4", M4_DIGIT(0))
    unsigned short afmThres;
    // M4_ARRAY_MARK_DESC("Gamma Curve", "u16", M4_SIZE(1,17),  M4_RANGE(0, 1023), "[0,45,108,179,245,344,409,459,500,567,622,676,759,833,896,962,1023]", M4_DIGIT(0), M4_DYNAMIC(0), "curve_table")
    unsigned short gammaY[17];
    // M4_NUMBER_DESC("v1fv reliable", "f32", M4_RANGE(0, 1), "0", M4_DIGIT(3))
    float v1fv_reliable;
    // M4_NUMBER_DESC("v2fv reliable", "f32", M4_RANGE(0, 1), "0", M4_DIGIT(3))
    float v2fv_reliable;
    // M4_NUMBER_DESC("v1 fir sel", "u8", M4_RANGE(0, 1), "0", M4_DIGIT(0))
    unsigned char v1_fir_sel;
    // M4_ARRAY_DESC("v1 band", "f32", M4_SIZE(1,2), M4_RANGE(0, 1), "0", M4_DIGIT(3), M4_DYNAMIC(0))
    float v1_band[2];
    // M4_ARRAY_DESC("vertical first iir filter", "s16", M4_SIZE(1,9), M4_RANGE(-255,255), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    short v1_iir_coe[9];
    // M4_ARRAY_DESC("vertical first fir filter", "s16", M4_SIZE(1,3), M4_RANGE(-2047,2047), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    short v1_fir_coe[3];
    // M4_ARRAY_DESC("v2 band", "f32", M4_SIZE(1,2), M4_RANGE(0, 1), "0", M4_DIGIT(3), M4_DYNAMIC(0))
    float v2_band[2];
    // M4_ARRAY_DESC("vertical second iir filter", "s16", M4_SIZE(1,3), M4_RANGE(-2047,2047), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    short v2_iir_coe[3];
    // M4_ARRAY_DESC("vertical second fir filter", "s16", M4_SIZE(1,3), M4_RANGE(-2047,2047), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    short v2_fir_coe[3];
    // M4_ARRAY_DESC("h1 band", "f32", M4_SIZE(1,2), M4_RANGE(0, 1), "0", M4_DIGIT(3), M4_DYNAMIC(0))
    float h1_band[2];
    // M4_ARRAY_DESC("horizontal first iir1 filter", "s16", M4_SIZE(1,6), M4_RANGE(-2047,2047), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    short h1_iir1_coe[6];
    // M4_ARRAY_DESC("horizontal first iir2 filter", "s16", M4_SIZE(1,6), M4_RANGE(-2047,2047), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    short h1_iir2_coe[6];
    // M4_ARRAY_DESC("h2 band", "f32", M4_SIZE(1,2), M4_RANGE(0, 1), "0", M4_DIGIT(3), M4_DYNAMIC(0))
    float h2_band[2];
    // M4_ARRAY_DESC("horizontal second iir1 filter", "s16", M4_SIZE(1,6), M4_RANGE(-2047,2047), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    short h2_iir1_coe[6];
    // M4_ARRAY_DESC("horizontal second iir2 filter", "s16", M4_SIZE(1,6), M4_RANGE(-2047,2047), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    short h2_iir2_coe[6];
    // M4_NUMBER_DESC("ldg enable", "u8", M4_RANGE(0, 1), "0", M4_DIGIT(0))
    unsigned char ldg_en;
    // M4_NUMBER_DESC("vertical minluma thresh", "u8", M4_RANGE(0, 255), "0", M4_DIGIT(0))
    unsigned char ve_ldg_lumth_l;
    // M4_NUMBER_DESC("vertical gain for minluma", "u8", M4_RANGE(0, 255), "0", M4_DIGIT(0))
    unsigned char ve_ldg_gain_l;
    // M4_NUMBER_DESC("vertical slope low", "u16", M4_RANGE(0, 8191), "0", M4_DIGIT(0))
    unsigned short ve_ldg_gslp_l;
    // M4_NUMBER_DESC("vertical maxluma thresh", "u8", M4_RANGE(0, 255), "0", M4_DIGIT(0))
    unsigned char ve_ldg_lumth_h;
    // M4_NUMBER_DESC("vertical gain for maxluma", "u8", M4_RANGE(0, 255), "0", M4_DIGIT(0))
    unsigned char ve_ldg_gain_h;
    // M4_NUMBER_DESC("vertical slope high", "u16", M4_RANGE(0, 8191), "0", M4_DIGIT(0))
    unsigned short ve_ldg_gslp_h;
    // M4_NUMBER_DESC("horizontal minluma thresh", "u8", M4_RANGE(0, 255), "0", M4_DIGIT(0))
    unsigned char ho_ldg_lumth_l;
    // M4_NUMBER_DESC("horizontal gain for minluma", "u8", M4_RANGE(0, 255), "0", M4_DIGIT(0))
    unsigned char ho_ldg_gain_l;
    // M4_NUMBER_DESC("horizontal slope low", "u16", M4_RANGE(0, 8191), "0", M4_DIGIT(0))
    unsigned short ho_ldg_gslp_l;
    // M4_NUMBER_DESC("horizontal maxluma thresh", "u8", M4_RANGE(0, 255), "0", M4_DIGIT(0))
    unsigned char ho_ldg_lumth_h;
    // M4_NUMBER_DESC("horizontal gain for maxluma", "u8", M4_RANGE(0, 255), "0", M4_DIGIT(0))
    unsigned char ho_ldg_gain_h;
    // M4_NUMBER_DESC("horizontal slope high", "u16", M4_RANGE(0, 8191), "0", M4_DIGIT(0))
    unsigned short ho_ldg_gslp_h;
    // M4_NUMBER_DESC("vertical fv thresh", "u16", M4_RANGE(0, 4095), "0", M4_DIGIT(0))
    unsigned short v_fv_thresh;
    // M4_NUMBER_DESC("horizontal fv thresh", "u16", M4_RANGE(0, 4095), "0", M4_DIGIT(0))
    unsigned short h_fv_thresh;
    // M4_NUMBER_DESC("highlight thresh", "u16", M4_RANGE(0, 4095), "0", M4_DIGIT(0))
    unsigned short highlit_thresh;
    // M4_NUMBER_DESC("vertical fv ratio", "f32", M4_RANGE(0, 1), "0.5", M4_DIGIT(3))
    float v_fv_ratio;
} CalibDbV2_AfV30_MeasCfg_t;

typedef struct CalibDbV2_AfV30_IsoMeasCfg_s {
    // M4_NUMBER_MARK_DESC("iso", "f32", M4_RANGE(50, 204800), "50", M4_DIGIT(1), "index2")
    float iso;
    // M4_NUMBER_DESC("meas table index", "u32", M4_RANGE(0, 100), "0", M4_DIGIT(0))
    int idx;
} CalibDbV2_AfV30_IsoMeasCfg_t;

typedef struct CalibDbV2_AfV30_ZoomMeas_s {
    // M4_NUMBER_MARK_DESC("zoom index", "u32", M4_RANGE(0, 100000), "0", M4_DIGIT(0), "index1")
    int zoom_idx;
    // M4_STRUCT_LIST_DESC("meas iso config", M4_SIZE(1,13), "double_index_list")
    CalibDbV2_AfV30_IsoMeasCfg_t measiso[13];
} CalibDbV2_AfV30_ZoomMeas_t;

typedef struct CalibDbV2_AFV30_Tuning_Para_s {
    // M4_ENUM_DESC("mode", "CalibDbV2_AF_MODE_t", "CalibDbV2_AF_MODE_CONTINUOUS_PICTURE")
    CalibDbV2_AF_MODE_t af_mode;
    // M4_NUMBER_DESC("win_h_offs", "u16", M4_RANGE(0,2000), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned short win_h_offs;
    // M4_NUMBER_DESC("win_v_offs", "u16", M4_RANGE(0,2000), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned short win_v_offs;
    // M4_NUMBER_DESC("win_h_size", "u16", M4_RANGE(0,2000), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned short win_h_size;
    // M4_NUMBER_DESC("win_v_size", "u16", M4_RANGE(0,2000), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned short win_v_size;
    // M4_NUMBER_DESC("win_h_offs in video", "u16", M4_RANGE(0,2000), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned short video_win_h_offs;
    // M4_NUMBER_DESC("win_v_offs in video", "u16", M4_RANGE(0,2000), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned short video_win_v_offs;
    // M4_NUMBER_DESC("win_h_size in video", "u16", M4_RANGE(0,2000), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned short video_win_h_size;
    // M4_NUMBER_DESC("win_v_size in video", "u16", M4_RANGE(0,2000), "0", M4_DIGIT(0),M4_HIDE(0))
    unsigned short video_win_v_size;
    // M4_STRUCT_DESC("fixed mode", "normal_ui_style")
    CalibDbV2_Af_DefCode_t fixed_mode;
    // M4_STRUCT_DESC("macro mode", "normal_ui_style")
    CalibDbV2_Af_DefCode_t macro_mode;
    // M4_STRUCT_DESC("infinity mode", "normal_ui_style")
    CalibDbV2_Af_DefCode_t infinity_mode;
    // M4_STRUCT_DESC("contrast af", "normal_ui_style")
    CalibDbV2_Af_Contrast_t contrast_af;
    // M4_STRUCT_DESC("video contrast af", "normal_ui_style")
    CalibDbV2_Af_Contrast_t video_contrast_af;
    // M4_STRUCT_DESC("laser af", "normal_ui_style")
    CalibDbV2_Af_Laser_t laser_af;
    // M4_STRUCT_DESC("pdaf", "normal_ui_style")
    CalibDbV2_Af_Pdaf_t pdaf;
    // M4_STRUCT_DESC("vcmcfg", "normal_ui_style")
    CalibDbV2_Af_VcmCfg_t vcmcfg;
    // M4_STRUCT_DESC("zoomfocus_tbl", "normal_ui_style")
    CalibDbV2_Af_ZoomFocusTbl_t zoomfocus_tbl;
    // M4_STRUCT_LIST_DESC("zoom meas", M4_SIZE_DYNAMIC, "double_index_list")
    CalibDbV2_AfV30_ZoomMeas_t *zoom_meas;
    int zoom_meas_len;
    // M4_STRUCT_LIST_DESC("meas config table", M4_SIZE_DYNAMIC, "normal_ui_style")
    CalibDbV2_AfV30_MeasCfg_t *meascfg_tbl;
    int meascfg_tbl_len;
} CalibDbV2_AFV30_Tuning_Para_t;

typedef struct {
    // M4_STRUCT_DESC("TuningPara", "normal_ui_style")
    CalibDbV2_AFV30_Tuning_Para_t TuningPara;
} CalibDbV2_AFV30_t;


# 28 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/agamma_head.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/agamma_head.h" 2






typedef enum GammaType_e {
    GAMMATYPE_LOG = 0,
    GAMMATYPE_EQU = 1,
} GammaType_t;

typedef struct CalibDbGammaV2_s {
    // M4_BOOL_DESC("Gamma_en", "1")
    
# 37 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/agamma_head.h" 3 4
   _Bool 
# 37 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/agamma_head.h"
        Gamma_en;
    // M4_ENUM_DESC("Gamma_out_segnum", "GammaType_t", "GAMMATYPE_LOG")
    GammaType_t Gamma_out_segnum;
    // M4_NUMBER_DESC("Gamma_out_offset", "u16", M4_RANGE(0,4095), "0", M4_DIGIT(0))
    uint16_t Gamma_out_offset;
    // M4_ARRAY_MARK_DESC("Gamma_curve", "u16", M4_SIZE(1,45),  M4_RANGE(0, 4095), "[0, 6, 11, 17, 22, 28, 33, 39, 44, 55, 66, 77, 88, 109, 130, 150, 170, 210, 248, 286, 323, 393, 460, 525, 586, 702, 809, 909, 1002, 1172, 1325, 1462, 1588, 1811, 2004, 2174, 2327, 2590, 2813, 3006, 3177, 3467, 3708, 3915, 4095.0000]", M4_DIGIT(4), M4_DYNAMIC(0), "curve_table")
    uint16_t Gamma_curve[45];
} CalibDbGammaV2_t;

typedef struct CalibDbV2_gamma_s {
    // M4_STRUCT_DESC("GammaTuningPara", "curve_ui_type_A")
    CalibDbGammaV2_t GammaTuningPara;
} CalibDbV2_gamma_t;

typedef struct CalibDbGammaV30_s {
    // M4_BOOL_DESC("Gamma_en", "1")
    
# 53 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/agamma_head.h" 3 4
   _Bool 
# 53 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/agamma_head.h"
        Gamma_en;
    // M4_NUMBER_DESC("Gamma_out_offset", "u16", M4_RANGE(0,4095), "0", M4_DIGIT(0))
    uint16_t Gamma_out_offset;
    // M4_ARRAY_MARK_DESC("Gamma_curve", "u16", M4_SIZE(1,49),  M4_RANGE(0, 4095), "[0, 93, 128, 154, 175, 194, 211, 226, 240, 266, 289, 310, 329, 365, 396, 425, 451, 499, 543, 582, 618, 684, 744, 798, 848, 938, 1019, 1093, 1161, 1285, 1396, 1498, 1592, 1761, 1914, 2052, 2181, 2414, 2622, 2813, 2989, 3153, 3308, 3454, 4593, 3727, 3854, 3977, 4095]", M4_DIGIT(0), M4_DYNAMIC(0), "curve_table")
    uint16_t Gamma_curve[49];;
} CalibDbGammaV30_t;

typedef struct CalibDbV2_gamma_V30_s {
    // M4_STRUCT_DESC("GammaTuningPara", "curve_ui_type_A")
    CalibDbGammaV30_t GammaTuningPara;
} CalibDbV2_gamma_V30_t;



# 29 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/agic_head.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/agic_head.h" 2



typedef struct Gic_setting_v20_s {
    // M4_ARRAY_DESC("ISO", "f32", M4_SIZE(1,100), M4_RANGE(0,10000000), "50",M4_DIGIT(4), M4_DYNAMIC(1))
    float* ISO;
    int ISO_len;
    // M4_ARRAY_DESC("min_busy_thre", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "160",M4_DIGIT(4), M4_DYNAMIC(1))
    float* min_busy_thre;
    int min_busy_thre_len;
    // M4_ARRAY_DESC("min_grad_thr1", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "32",M4_DIGIT(4), M4_DYNAMIC(1))
    float* min_grad_thr1;
    int min_grad_thr1_len;
    // M4_ARRAY_DESC("min_grad_thr2", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "32",M4_DIGIT(4), M4_DYNAMIC(1))
    float* min_grad_thr2;
    int min_grad_thr2_len;
    // M4_ARRAY_DESC("k_grad1", "f32", M4_SIZE(1,100), M4_RANGE(0,15), "5",M4_DIGIT(4), M4_DYNAMIC(1))
    float* k_grad1;
    int k_grad1_len;
    // M4_ARRAY_DESC("k_grad1", "f32", M4_SIZE(1,100), M4_RANGE(0,15), "1",M4_DIGIT(4), M4_DYNAMIC(1))
    float* k_grad2;
    int k_grad2_len;
    // M4_ARRAY_DESC("gb_thre", "f32", M4_SIZE(1,100), M4_RANGE(0,15), "7",M4_DIGIT(4), M4_DYNAMIC(1))
    float* gb_thre;
    int gb_thre_len;
    // M4_ARRAY_DESC("maxCorV", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "40",M4_DIGIT(4), M4_DYNAMIC(1))
    float* maxCorV;
    int maxCorV_len;
    // M4_ARRAY_DESC("maxCorVboth", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "8",M4_DIGIT(4), M4_DYNAMIC(1))
    float* maxCorVboth;
    int maxCorVboth_len;
    // M4_ARRAY_DESC("dark_thre", "f32", M4_SIZE(1,100), M4_RANGE(0,2047), "120",M4_DIGIT(4), M4_DYNAMIC(1))
    float* dark_thre;
    int dark_thre_len;
    // M4_ARRAY_DESC("dark_threHi", "f32", M4_SIZE(1,100), M4_RANGE(0,2047), "240",M4_DIGIT(4), M4_DYNAMIC(1))
    float* dark_threHi;
    int dark_threHi_len;
    // M4_ARRAY_DESC("k_grad1_dark", "f32", M4_SIZE(1,100), M4_RANGE(0,15), "6",M4_DIGIT(4), M4_DYNAMIC(1))
    float* k_grad1_dark;
    int k_grad1_dark_len;
    // M4_ARRAY_DESC("k_grad2_dark", "f32", M4_SIZE(1,100), M4_RANGE(0,15), "1",M4_DIGIT(4), M4_DYNAMIC(1))
    float* k_grad2_dark;
    int k_grad2_dark_len;
    // M4_ARRAY_DESC("min_grad_thr_dark1", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "64",M4_DIGIT(4), M4_DYNAMIC(1))
    float* min_grad_thr_dark1;
    int min_grad_thr_dark1_len;
    // M4_ARRAY_DESC("min_grad_thr_dark2", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "32",M4_DIGIT(4), M4_DYNAMIC(1))
    float* min_grad_thr_dark2;
    int min_grad_thr_dark2_len;
    // M4_ARRAY_DESC("noiseCurve_0", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* noiseCurve_0;
    int noiseCurve_0_len;
    // M4_ARRAY_DESC("noiseCurve_1", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* noiseCurve_1;
    int noiseCurve_1_len;
    // M4_ARRAY_DESC("GValueLimitLo", "f32", M4_SIZE(1,100), M4_RANGE(0,4095), "1280",M4_DIGIT(4), M4_DYNAMIC(1))
    float* GValueLimitLo;
    int GValueLimitLo_len;
    // M4_ARRAY_DESC("GValueLimitHi", "f32", M4_SIZE(1,100), M4_RANGE(0,4095), "1760",M4_DIGIT(4), M4_DYNAMIC(1))
    float* GValueLimitHi;
    int GValueLimitHi_len;
    // M4_ARRAY_DESC("textureStrength", "f32", M4_SIZE(1,100), M4_RANGE(0,2), "1",M4_DIGIT(4), M4_DYNAMIC(1))
    float* textureStrength;
    int textureStrength_len;
    // M4_ARRAY_DESC("ScaleLo", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* ScaleLo;
    int ScaleLo_len;
    // M4_ARRAY_DESC("ScaleHi", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* ScaleHi;
    int ScaleHi_len;
    // M4_ARRAY_DESC("globalStrength", "f32", M4_SIZE(1,100), M4_RANGE(0,2), "1",M4_DIGIT(4), M4_DYNAMIC(1))
    float* globalStrength;
    int globalStrength_len;
    // M4_ARRAY_DESC("noise_coea", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* noise_coea;
    int noise_coea_len;
    // M4_ARRAY_DESC("noise_coeb", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* noise_coeb;
    int noise_coeb_len;
    // M4_ARRAY_DESC("diff_clip", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* diff_clip;
    int diff_clip_len;
} Gic_setting_v20_t;

typedef struct Gic_setting_v21_s {
    // M4_ARRAY_DESC("ISO", "f32", M4_SIZE(1,100), M4_RANGE(0,10000000), "50",M4_DIGIT(4), M4_DYNAMIC(1))
    float* ISO;
    int ISO_len;
    // M4_ARRAY_DESC("min_busy_thre", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "160",M4_DIGIT(4), M4_DYNAMIC(1))
    float* min_busy_thre;
    int min_busy_thre_len;
    // M4_ARRAY_DESC("min_grad_thr1", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "32",M4_DIGIT(4), M4_DYNAMIC(1))
    float* min_grad_thr1;
    int min_grad_thr1_len;
    // M4_ARRAY_DESC("min_grad_thr2", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "32",M4_DIGIT(4), M4_DYNAMIC(1))
    float* min_grad_thr2;
    int min_grad_thr2_len;
    // M4_ARRAY_DESC("k_grad1", "f32", M4_SIZE(1,100), M4_RANGE(0,15), "5",M4_DIGIT(4), M4_DYNAMIC(1))
    float* k_grad1;
    int k_grad1_len;
    // M4_ARRAY_DESC("k_grad1", "f32", M4_SIZE(1,100), M4_RANGE(0,15), "1",M4_DIGIT(4), M4_DYNAMIC(1))
    float* k_grad2;
    int k_grad2_len;
    // M4_ARRAY_DESC("gb_thre", "f32", M4_SIZE(1,100), M4_RANGE(0,15), "7",M4_DIGIT(4), M4_DYNAMIC(1))
    float* gb_thre;
    int gb_thre_len;
    // M4_ARRAY_DESC("maxCorV", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "40",M4_DIGIT(4), M4_DYNAMIC(1))
    float* maxCorV;
    int maxCorV_len;
    // M4_ARRAY_DESC("maxCorVboth", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "8",M4_DIGIT(4), M4_DYNAMIC(1))
    float* maxCorVboth;
    int maxCorVboth_len;
    // M4_ARRAY_DESC("dark_thre", "f32", M4_SIZE(1,100), M4_RANGE(0,2047), "120",M4_DIGIT(4), M4_DYNAMIC(1))
    float* dark_thre;
    int dark_thre_len;
    // M4_ARRAY_DESC("dark_threHi", "f32", M4_SIZE(1,100), M4_RANGE(0,2047), "240",M4_DIGIT(4), M4_DYNAMIC(1))
    float* dark_threHi;
    int dark_threHi_len;
    // M4_ARRAY_DESC("k_grad1_dark", "f32", M4_SIZE(1,100), M4_RANGE(0,15), "6",M4_DIGIT(4), M4_DYNAMIC(1))
    float* k_grad1_dark;
    int k_grad1_dark_len;
    // M4_ARRAY_DESC("k_grad2_dark", "f32", M4_SIZE(1,100), M4_RANGE(0,15), "1",M4_DIGIT(4), M4_DYNAMIC(1))
    float* k_grad2_dark;
    int k_grad2_dark_len;
    // M4_ARRAY_DESC("min_grad_thr_dark1", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "64",M4_DIGIT(4), M4_DYNAMIC(1))
    float* min_grad_thr_dark1;
    int min_grad_thr_dark1_len;
    // M4_ARRAY_DESC("min_grad_thr_dark2", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "32",M4_DIGIT(4), M4_DYNAMIC(1))
    float* min_grad_thr_dark2;
    int min_grad_thr_dark2_len;
    // M4_ARRAY_DESC("noiseCurve_0", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* noiseCurve_0;
    int noiseCurve_0_len;
    // M4_ARRAY_DESC("noiseCurve_1", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* noiseCurve_1;
    int noiseCurve_1_len;
    // M4_ARRAY_DESC("NoiseScale", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* NoiseScale;
    int NoiseScale_len;
    // M4_ARRAY_DESC("NoiseBase", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* NoiseBase;
    int NoiseBase_len;
    // M4_ARRAY_DESC("globalStrength", "f32", M4_SIZE(1,100), M4_RANGE(0,2), "1",M4_DIGIT(4), M4_DYNAMIC(1))
    float* globalStrength;
    int globalStrength_len;
    // M4_ARRAY_DESC("diff_clip", "f32", M4_SIZE(1,100), M4_RANGE(0,1023), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* diff_clip;
    int diff_clip_len;
} Gic_setting_v21_t;

typedef struct CalibDbGicV20_s {
    // M4_BOOL_DESC("enable", "0")
    
# 176 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/agic_head.h" 3 4
   _Bool 
# 176 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/agic_head.h"
                       enable;
    // M4_BOOL_DESC("edge_en", "0")
    
# 178 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/agic_head.h" 3 4
   _Bool 
# 178 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/agic_head.h"
                       edge_en;
    // M4_BOOL_DESC("noise_cut_en", "0")
    
# 180 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/agic_head.h" 3 4
   _Bool 
# 180 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/agic_head.h"
                       noise_cut_en;
    // M4_NUMBER_DESC("gr_ration", "u8", M4_RANGE(0,3), "0", M4_DIGIT(0))
    unsigned char gr_ration;
    // M4_ARRAY_TABLE_DESC("GicData", "array_table_ui","none")
    Gic_setting_v20_t GicData;
} CalibDbGicV20_t;

typedef struct CalibDbV2_Gic_V20_s {
    // M4_STRUCT_DESC("GicTuningPara", "normal_ui_style")
    CalibDbGicV20_t GicTuningPara;
} CalibDbV2_Gic_V20_t;

typedef struct CalibDbGicV21_s {
    // M4_BOOL_DESC("enable", "0")
    
# 194 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/agic_head.h" 3 4
   _Bool 
# 194 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/agic_head.h"
                       enable;
    // M4_NUMBER_DESC("gr_ration", "u8", M4_RANGE(0,3), "0", M4_DIGIT(0))
    unsigned char gr_ration;
    // M4_ARRAY_TABLE_DESC("GicData", "array_table_ui", "none")
    Gic_setting_v21_t GicData;
} CalibDbGicV21_t;

typedef struct CalibDbV2_Gic_V21_s {
    // M4_STRUCT_DESC("GicTuningPara", "normal_ui_style")
    CalibDbGicV21_t GicTuningPara;
} CalibDbV2_Gic_V21_t;



# 30 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aie_head.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aie_head.h" 2



// #define M4_BOOL_DESC(ALIAS, DEFAULT, HIDE)

// #define M4_ARRAY_DESC(ALIAS, TYPE, SIZE, RANGE, DEFAULT,DIGIT,DYNAMIC, HIDE)

// #define M4_NUMBER_DESC(ALIAS, TYPE, RANGE, DEFAULT,DIGIT, HIDE)

typedef struct __ie_param {
    // M4_BOOL_DESC("enable", "1", 0)
    
# 35 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aie_head.h" 3 4
   _Bool 
# 35 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aie_head.h"
        enable;
    // M4_NUMBER_DESC("mode", "u8", M4_RANGE(0,6), "0", M4_DIGIT(0), 0)
    unsigned char mode;
}IE_Param_t;

typedef struct __ie {
    // M4_STRUCT_DESC("IETuningPara", "normal_ui_style")
    IE_Param_t param;
} CalibDbV2_IE_t;


# 31 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/alsc_head.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/alsc_head.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/algos/alsc/rk_aiq_types_alsc_hw.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/algos/alsc/rk_aiq_types_alsc_hw.h" 2


//MEMO: rkisp2-config.h/rkisp3-config.h -> ISP2X_LSC_DATA_TBL_SIZE is 290
# 37 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/algos/alsc/rk_aiq_types_alsc_hw.h"


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
    
# 54 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/algos/alsc/rk_aiq_types_alsc_hw.h" 3 4
   _Bool 
# 54 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/algos/alsc/rk_aiq_types_alsc_hw.h"
        lsc_en;
} rk_aiq_lsc_cfg_t;


# 25 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/alsc_head.h" 2


# 39 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/alsc_head.h"
typedef struct lsc_name_s {
    // M4_STRING_DESC("name", M4_SIZE(1,1), M4_RANGE(0, 32), "default", M4_DYNAMIC(0))
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
    // M4_NUMBER_DESC("usedForCase", "u32", M4_RANGE(0,100), "0", M4_DIGIT(0))
    uint32_t usedForCase;
    // M4_STRING_DESC("name", M4_SIZE(1,1), M4_RANGE(0, 32), "default", M4_DYNAMIC(0))
    char name[( 32U )];
    // M4_ARRAY_DESC("wbGain", "f32", M4_SIZE(1,2), M4_RANGE(0,10000), "0", M4_DIGIT(4), M4_DYNAMIC(0))
    float wbGain[2];
    // M4_STRUCT_LIST_DESC("tableUsed", M4_SIZE_DYNAMIC, "normal_ui_style")
    lsc_name_t* tableUsed;
    int tableUsed_len;
    // M4_ARRAY_DESC("gains", "f32", M4_SIZE(1,100), M4_RANGE(0,10000), "0", M4_DIGIT(4), M4_DYNAMIC(1))
    float* gains;
    int gains_len;
    // M4_ARRAY_DESC("vig", "f32", M4_SIZE(1,100), M4_RANGE(0,100), "0", M4_DIGIT(2), M4_DYNAMIC(1))
    float* vig;
    int vig_len;
} CalibDbV2_AlscCof_ill_t;

typedef struct CalibDbV2_Lsc_Resolution_s {
    // M4_STRING_DESC("name", M4_SIZE(1,1), M4_RANGE(0, 32), "default", M4_DYNAMIC(0))
    char name[( 32U )];





    // M4_ARRAY_DESC("lsc_sect_size_x", "u16", M4_SIZE(1,16), M4_RANGE(0,10000), "0", M4_DIGIT(0), M4_DYNAMIC(0))



    uint16_t lsc_sect_size_x[16];





    // M4_ARRAY_DESC("lsc_sect_size_y", "u16", M4_SIZE(1,16), M4_RANGE(0,10000), "0", M4_DIGIT(0), M4_DYNAMIC(0))



    uint16_t lsc_sect_size_y[16];
} CalibDbV2_Lsc_Resolution_t;

typedef struct CalibDbV2_Lsc_Common_s {
    // M4_BOOL_DESC("enable", "1")
    
# 98 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/alsc_head.h" 3 4
   _Bool 
# 98 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/alsc_head.h"
                                   enable;
    // M4_STRUCT_LIST_DESC("resolutionAll", M4_SIZE_DYNAMIC, "normal_ui_style")
    CalibDbV2_Lsc_Resolution_t* resolutionAll;
    int resolutionAll_len;
} CalibDbV2_Lsc_Common_t;

typedef struct CalibDbV2_AlscCof_s {
    // M4_BOOL_DESC("damp_enable", "1")
    
# 106 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/alsc_head.h" 3 4
   _Bool 
# 106 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/alsc_head.h"
                                   damp_enable;
    // M4_STRUCT_LIST_DESC("illAll", M4_SIZE_DYNAMIC, "normal_ui_style")
    CalibDbV2_AlscCof_ill_t* illAll;
    int illAll_len;
} CalibDbV2_AlscCof_t;

//represent a cell of tableAll in xml/json
typedef struct CalibDbV2_LscTableProfile_s {
    // M4_STRING_DESC("name", M4_SIZE(1,1), M4_RANGE(0, 32), "default", M4_DYNAMIC(0))
    char name[( 32U )];
    // M4_STRING_DESC("resolution", M4_SIZE(1,1), M4_RANGE(0, 32), "default", M4_DYNAMIC(0))
    char resolution[( 32U )];
    // M4_STRING_DESC("illumination", M4_SIZE(1,1), M4_RANGE(0, 32), "default", M4_DYNAMIC(0))
    char illumination[( 32U )];
    // M4_NUMBER_DESC("vignetting", "f32", M4_RANGE(0,100), "100", M4_DIGIT(0))
    float vignetting;

    // M4_STRUCT_DESC("lsc_samples_red", "normal_ui_style")
    Cam17x17UShortMatrix_t lsc_samples_red;
    // M4_STRUCT_DESC("lsc_samples_greenR", "normal_ui_style")
    Cam17x17UShortMatrix_t lsc_samples_greenR;
    // M4_STRUCT_DESC("lsc_samples_greenB", "normal_ui_style")
    Cam17x17UShortMatrix_t lsc_samples_greenB;
    // M4_STRUCT_DESC("lsc_samples_blue", "normal_ui_style")
    Cam17x17UShortMatrix_t lsc_samples_blue;
} CalibDbV2_LscTableProfile_t;

typedef struct CalibDbV2_LscTable {
    // M4_STRUCT_LIST_DESC("tableAll", M4_SIZE_DYNAMIC, "normal_ui_style")
    CalibDbV2_LscTableProfile_t* tableAll;
    int tableAll_len;
} CalibDbV2_LscTable_t;

typedef struct CalibDb_LscV2_s {
    // M4_STRUCT_DESC("common", "normal_ui_style")
    CalibDbV2_Lsc_Common_t common;
    // M4_STRUCT_DESC("alscCoef", "normal_ui_style")
    CalibDbV2_AlscCof_t alscCoef;
    // M4_STRUCT_DESC("table_list", "normal_ui_style")
    CalibDbV2_LscTable_t tbl;
} CalibDbV2_LSC_t;


# 32 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/amerge_head.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/amerge_head.h" 2



typedef struct MergeOECurveV20_s {
    // M4_ARRAY_DESC("EnvLv", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* EnvLv;
    int EnvLv_len;
    // M4_ARRAY_DESC("Smooth", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.4",M4_DIGIT(4), M4_DYNAMIC(1))
    float* Smooth;
    int Smooth_len;
    // M4_ARRAY_DESC("Offset", "f32", M4_SIZE(1,100), M4_RANGE(108,300), "210",M4_DIGIT(4), M4_DYNAMIC(1))
    float* Offset;
    int Offset_len;
} MergeOECurveV20_t;

typedef struct MergeMDCurveV20_s {
    // M4_ARRAY_DESC("MoveCoef", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* MoveCoef;
    int MoveCoef_len;
    // M4_ARRAY_DESC("LM_smooth", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.4",M4_DIGIT(4), M4_DYNAMIC(1))
    float* LM_smooth;
    int LM_smooth_len;
    // M4_ARRAY_DESC("LM_offset", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.38",M4_DIGIT(4), M4_DYNAMIC(1))
    float* LM_offset;
    int LM_offset_len;
    // M4_ARRAY_DESC("MS_smooth", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.4",M4_DIGIT(4), M4_DYNAMIC(1))
    float* MS_smooth;
    int MS_smooth_len;
    // M4_ARRAY_DESC("MS_offset", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.38",M4_DIGIT(4), M4_DYNAMIC(1))
    float* MS_offset;
    int MS_offset_len;
} MergeMDCurveV20_t;

typedef struct MergeV20_s {
    // M4_ARRAY_TABLE_DESC("OECurve", "array_table_ui", "none")
    MergeOECurveV20_t OECurve;
    // M4_ARRAY_TABLE_DESC("MDCurve", "array_table_ui", "none")
    MergeMDCurveV20_t MDCurve;
    // M4_NUMBER_DESC("ByPassThr", "f32", M4_RANGE(0,1), "0", M4_DIGIT(4))
    float ByPassThr;
    // M4_NUMBER_DESC("OECurve_damp", "f32", M4_RANGE(0,1), "0.9", M4_DIGIT(4))
    float OECurve_damp;
    // M4_NUMBER_DESC("MDCurveLM_damp", "f32", M4_RANGE(0,1), "0.9", M4_DIGIT(4))
    float MDCurveLM_damp;
    // M4_NUMBER_DESC("MDCurveMS_damp", "f32", M4_RANGE(0,1), "0.9", M4_DIGIT(4))
    float MDCurveMS_damp;
} MergeV20_t;

typedef struct CalibDbV2_merge_s {
    // M4_STRUCT_DESC("MergeTuningPara", "normal_ui_style")
    MergeV20_t MergeTuningPara;
} CalibDbV2_merge_t;

typedef enum MergeBaseFrame_e {
    BASEFRAME_LONG = 0,
    BASEFRAME_SHORT = 1,
} MergeBaseFrame_t;

typedef struct LongFrameModeData_s {
    // M4_ARRAY_TABLE_DESC("OECurve", "array_table_ui", "none")
    MergeOECurveV20_t OECurve;
    // M4_ARRAY_TABLE_DESC("MDCurve", "array_table_ui", "none")
    MergeMDCurveV20_t MDCurve;
    // M4_NUMBER_DESC("OECurve_damp", "f32", M4_RANGE(0,1), "0.9", M4_DIGIT(4))
    float OECurve_damp;
    // M4_NUMBER_DESC("MDCurveLM_damp", "f32", M4_RANGE(0,1), "0.9", M4_DIGIT(4))
    float MDCurveLM_damp;
    // M4_NUMBER_DESC("MDCurveMS_damp", "f32", M4_RANGE(0,1), "0.9", M4_DIGIT(4))
    float MDCurveMS_damp;
} LongFrameModeData_t;

typedef struct MergeMDCurveV21Short_s {
    // M4_ARRAY_DESC("MoveCoef", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* MoveCoef;
    int MoveCoef_len;
    // M4_ARRAY_DESC("Coef", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.05",M4_DIGIT(4), M4_DYNAMIC(1))
    float* Coef;
    int Coef_len;
    // M4_ARRAY_DESC("ms_thd0", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0",M4_DIGIT(1), M4_DYNAMIC(1))
    float* ms_thd0;
    int ms_thd0_len;
    // M4_ARRAY_DESC("lm_thd0", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0",M4_DIGIT(1), M4_DYNAMIC(1))
    float* lm_thd0;
    int lm_thd0_len;
} MergeMDCurveV21Short_t;

typedef struct ShortFrameModeData_s {
    // M4_ARRAY_TABLE_DESC("OECurve", "array_table_ui", "none")
    MergeOECurveV20_t OECurve;
    // M4_ARRAY_TABLE_DESC("MDCurve", "array_table_ui", "none")
    MergeMDCurveV21Short_t MDCurve;
    // M4_NUMBER_DESC("OECurve_damp", "f32", M4_RANGE(0,1), "0.9", M4_DIGIT(4))
    float OECurve_damp;
    // M4_NUMBER_DESC("MDCurve_damp", "f32", M4_RANGE(0,1), "0.9", M4_DIGIT(4))
    float MDCurve_damp;
} ShortFrameModeData_t;

typedef struct MergeV21_s {
    // M4_ENUM_DESC("BaseFrm", "MergeBaseFrame_t", "BASEFRAME_LONG")
    MergeBaseFrame_t BaseFrm;
    // M4_NUMBER_DESC("ByPassThr", "f32", M4_RANGE(0,1), "0", M4_DIGIT(4))
    float ByPassThr;
    // M4_STRUCT_DESC("LongFrmModeData", "normal_ui_style")
    LongFrameModeData_t LongFrmModeData;
    // M4_STRUCT_DESC("ShortFrmModeData", "normal_ui_style")
    ShortFrameModeData_t ShortFrmModeData;
} MergeV21_t;

typedef struct CalibDbV2_merge_V2_s {
    // M4_STRUCT_DESC("MergeTuningPara", "normal_ui_style")
    MergeV21_t MergeTuningPara;
} CalibDbV2_merge_V2_t;



# 33 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/atmo_head.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/atmo_head.h" 2



typedef enum GlobalLumaMode_e {
    GLOBALLUMAMODE_ENVLV = 0,
    GLOBALLUMAMODE_ISO = 1,
} GlobalLumaMode_t;

typedef struct GlobalLumaData_s
{
    // M4_ARRAY_DESC("EnvLv", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* EnvLv;
    int EnvLv_len;
    // M4_ARRAY_DESC("ISO", "f32", M4_SIZE(1,100), M4_RANGE(0,10000000), "50",M4_DIGIT(4), M4_DYNAMIC(1))
    float* ISO;
    int ISO_len;
    // M4_ARRAY_DESC("Strength", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.25",M4_DIGIT(4), M4_DYNAMIC(1))
    float* Strength;
    int Strength_len;
} GlobalLumaData_t;

typedef struct CalibDbGlobalLuma_s
{
    // M4_ENUM_DESC("Mode", "GlobalLumaMode_t", "GLOBALLUMAMODE_ENVLV")
    GlobalLumaMode_t Mode;
    // M4_ARRAY_TABLE_DESC("GlobalLumaData", "array_table_ui", "none")
    GlobalLumaData_t GlobalLumaData;
    // M4_NUMBER_DESC("Tolerance", "f32", M4_RANGE(0,0.2), "0", M4_DIGIT(4))
    float Tolerance;
} CalibDbGlobalLuma_t;

typedef enum DetailsHighLightMode_e {
    DETAILSHIGHLIGHTMODE_OEPDF = 0,
    DETAILSHIGHLIGHTMODE_ENVLV = 1,
} DetailsHighLightMode_t;

typedef struct HighLightData_s
{
    // M4_ARRAY_DESC("OEPdf", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* OEPdf;
    int OEPdf_len;
    // M4_ARRAY_DESC("EnvLv", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* EnvLv;
    int EnvLv_len;
    // M4_ARRAY_DESC("Strength", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.5",M4_DIGIT(4), M4_DYNAMIC(1))
    float* Strength;
    int Strength_len;
} HighLightData_t;

typedef struct CalibDbDetailsHighLight_s
{
    // M4_ENUM_DESC("Mode", "DetailsHighLightMode_t", "DETAILSHIGHLIGHTMODE_ENVLV")
    DetailsHighLightMode_t Mode;
    // M4_ARRAY_TABLE_DESC("HighLightData", "array_table_ui", "none")
    HighLightData_t HighLightData;
    // M4_NUMBER_DESC("Tolerance", "f32", M4_RANGE(0,0.2), "0", M4_DIGIT(4))
    float Tolerance;
} CalibDbDetailsHighLight_t;

typedef enum DetailsLowLightMode_e {
    DETAILSLOWLIGHTMODE_FOCUSLUMA = 0,
    DETAILSLOWLIGHTMODE_DARKPDF = 1,
    DETAILSLOWLIGHTMODE_ISO = 2,
} DetailsLowLightMode_t;

typedef struct LowLightData_s
{
    // M4_ARRAY_DESC("FocusLuma", "f32", M4_SIZE(1,100), M4_RANGE(0,100), "1",M4_DIGIT(4), M4_DYNAMIC(1))
    float* FocusLuma;
    int FocusLuma_len;
    // M4_ARRAY_DESC("DarkPdf", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* DarkPdf;
    int DarkPdf_len;
    // M4_ARRAY_DESC("ISO", "f32", M4_SIZE(1,100), M4_RANGE(0,10000000), "50",M4_DIGIT(4), M4_DYNAMIC(1))
    float* ISO;
    int ISO_len;
    // M4_ARRAY_DESC("Strength", "f32", M4_SIZE(1,100), M4_RANGE(1,4), "1",M4_DIGIT(4), M4_DYNAMIC(1))
    float* Strength;
    int Strength_len;
} LowLightData_t;

typedef struct CalibDbDetailsLowLight_s
{
    // M4_ENUM_DESC("Mode", "DetailsLowLightMode_t", "DETAILSLOWLIGHTMODE_ISO")
    DetailsLowLightMode_t Mode;
    // M4_ARRAY_TABLE_DESC("LowLightData", "array_table_ui", "none")
    LowLightData_t LowLightData;
    // M4_NUMBER_DESC("Tolerance", "f32", M4_RANGE(0,0.2), "0", M4_DIGIT(4))
    float Tolerance;
} CalibDbDetailsLowLight_t;

typedef enum TmoTypeMode_e {
    TMOTYPEMODE_DYNAMICRANGE = 0,
    TMOTYPEMODE_ENVLV = 1,
} TmoTypeMode_t;

typedef struct TmoData_s
{
    // M4_ARRAY_DESC("DynamicRange", "f32", M4_SIZE(1,100), M4_RANGE(1,84), "1",M4_DIGIT(4), M4_DYNAMIC(1))
    float* DynamicRange;
    int DynamicRange_len;
    // M4_ARRAY_DESC("EnvLv", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0",M4_DIGIT(4), M4_DYNAMIC(1))
    float* EnvLv;
    int EnvLv_len;
    // M4_ARRAY_DESC("Strength", "f32", M4_SIZE(1,100), M4_RANGE(0,1), "0.5",M4_DIGIT(4), M4_DYNAMIC(1))
    float* Strength;
    int Strength_len;
} TmoData_t;

typedef struct CalibDbLocalTMO_s
{
    // M4_ENUM_DESC("Mode", "TmoTypeMode_t", "TMOTYPEMODE_DYNAMICRANGE")
    TmoTypeMode_t Mode;
    // M4_ARRAY_TABLE_DESC("LocalTmoData", "array_table_ui", "none")
    TmoData_t LocalTmoData;
    // M4_NUMBER_DESC("Tolerance", "f32", M4_RANGE(0,0.2), "0", M4_DIGIT(4))
    float Tolerance;
} CalibDbLocalTMO_t;

typedef struct CalibDbGlobaTMO_s
{
    // M4_BOOL_DESC("Enable", "1")
    
# 146 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/atmo_head.h" 3 4
   _Bool 
# 146 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/atmo_head.h"
                Enable;
    // M4_NUMBER_DESC("IIR", "f32", M4_RANGE(1,1000), "64", M4_DIGIT(0))
    float IIR;
    // M4_ENUM_DESC("Mode", "TmoTypeMode_t", "TMOTYPEMODE_DYNAMICRANGE")
    TmoTypeMode_t Mode;
    // M4_ARRAY_TABLE_DESC("GlobalTmoData", "array_table_ui", "none")
    TmoData_t GlobalTmoData;
    // M4_NUMBER_DESC("Tolerance", "f32", M4_RANGE(0,0.2), "0", M4_DIGIT(4))
    float Tolerance;
} CalibDbGlobaTMO_t;

typedef struct CalibDbTmoV20_s
{
    // M4_BOOL_DESC("Enable", "1")
    
# 160 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/atmo_head.h" 3 4
   _Bool 
# 160 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/atmo_head.h"
                Enable;
    // M4_STRUCT_DESC("GlobalLuma", "normal_ui_style")
    CalibDbGlobalLuma_t GlobalLuma;
    // M4_STRUCT_DESC("DetailsHighLight", "normal_ui_style")
    CalibDbDetailsHighLight_t DetailsHighLight;
    // M4_STRUCT_DESC("DetailsLowLight", "normal_ui_style")
    CalibDbDetailsLowLight_t DetailsLowLight;
    // M4_STRUCT_DESC("LocalTMO", "normal_ui_style")
    CalibDbLocalTMO_t LocalTMO;
    // M4_STRUCT_DESC("GlobaTMO", "normal_ui_style")
    CalibDbGlobaTMO_t GlobaTMO;
    // M4_NUMBER_DESC("damp", "f32", M4_RANGE(0,1), "0.9", M4_DIGIT(4))
    float damp;
} CalibDbTmoV20_t;

typedef struct CalibDbV2_tmo_s
{
    // M4_STRUCT_DESC("TmoTuningPara", "normal_ui_style")
    CalibDbTmoV20_t TmoTuningPara;
} CalibDbV2_tmo_t;



# 34 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h" 2









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
  // M4_ENUM_DESC("domain", "CalibDbV2_Awb_Ext_Range_Domain_t", "CALIB_AWB_EXTRA_RANGE_DOMAIN_UV")
  CalibDbV2_Awb_Ext_Range_Domain_t domain;/*0uv domain,1 xy domain*/
  // M4_ENUM_DESC("mode", "CalibDbV2_Awb_Ext_Range_Mode_t", "CALIB_AWB_EXCLUDE_WP_MODE")
  CalibDbV2_Awb_Ext_Range_Mode_t mode;
  // M4_ARRAY_DESC("region", "s32", M4_SIZE(1,4), M4_RANGE(-8192, 8191), "0", M4_DIGIT(0), M4_DYNAMIC(0))
  int region[4];
} CalibDbV2_ExtRange_t;

typedef struct CalibDbV2_Yuv3D_Range_Ill_s {
  // M4_NUMBER_DESC("b_uv", "s32", M4_RANGE(-65536,65535), "0", M4_DIGIT(0), M4_HIDE(1))
  int b_uv; //17+0 s
  // M4_NUMBER_DESC("slope_inv_neg_uv", "s32", M4_RANGE(-262144,262143), "0", M4_DIGIT(0))
  int slope_inv_neg_uv; //9+10s //-1/k
  // M4_NUMBER_DESC("slope_factor_uv", "s32", M4_RANGE(-16384,16383), "0", M4_DIGIT(0), M4_HIDE(1))
  int slope_factor_uv; //1+14s // 1/(-1/k+k)
  // M4_NUMBER_DESC("slope_ydis", "s32", M4_RANGE(-262144,262143), "0", M4_DIGIT(0), M4_HIDE(1))
  int slope_ydis; //9+10s //k
  // M4_NUMBER_DESC("b_ydis", "s32", M4_RANGE(-65536,65535), "0", M4_DIGIT(0), M4_HIDE(1))
  int b_ydis; //17+0s
  // M4_NUMBER_DESC("ref_v", "u8", M4_RANGE(0,255), "0", M4_DIGIT(0), M4_HIDE(1))
  unsigned char ref_v;//8u
  // M4_ARRAY_DESC("dis", "u16", M4_SIZE(1,6), M4_RANGE(0,4095), "0", M4_DIGIT(0), M4_DYNAMIC(0))
  unsigned short dis[6];//8+4 u
  // M4_ARRAY_DESC("th", "u8", M4_SIZE(1,6), M4_RANGE(0,255), "0", M4_DIGIT(0), M4_DYNAMIC(0))
  unsigned char th[6]; //8u
} CalibDbV2_Yuv3D_Range_Ill_t;

typedef struct CalibDbV2_Yuv3D_2_Range_Ill_s {
  // M4_ARRAY_DESC("thcurve_u", "f32", M4_SIZE(1,6), M4_RANGE(0,255), "0", M4_DIGIT(0), M4_DYNAMIC(0))
  float thcurve_u[6];
  // M4_ARRAY_DESC("thcure_th", "f32", M4_SIZE(1,6), M4_RANGE(0,8), "0", M4_DIGIT(4), M4_DYNAMIC(0))
  float thcure_th[6];
  // M4_ARRAY_DESC("lineVector", "f32", M4_SIZE(1,6), M4_RANGE(0,255), "0", M4_DIGIT(4), M4_DYNAMIC(0), M4_HIDE(1))
  float lineVector[6];
  // M4_NUMBER_DESC("disP1P2", "u8", M4_RANGE(0,255), "0", M4_DIGIT(0), M4_HIDE(1))
  unsigned char disP1P2;
} CalibDbV2_Yuv3D_2_Range_Ill_t;

typedef struct CalibDbV2_Tcs_Range_Ill_s {
  // M4_ARRAY_DESC("normal", "f32", M4_SIZE(1,4), M4_RANGE(-8,8), "0", M4_DIGIT(4), M4_DYNAMIC(0))
  float normal[4];
  // M4_ARRAY_DESC("big", "f32", M4_SIZE(1,4), M4_RANGE(-8,8), "0", M4_DIGIT(4), M4_DYNAMIC(0))
  float big[4];
  // M4_ARRAY_DESC("small", "f32", M4_SIZE(1,4), M4_RANGE(-8,8), "0", M4_DIGIT(4), M4_DYNAMIC(0))
  float small[4];
} CalibDbV2_Tcs_Range_Ill_t;

typedef struct CalibDbV2_Tcs_Range_Ill2_s {
  // M4_ARRAY_DESC("normal", "f32", M4_SIZE(1,4), M4_RANGE(-8,8), "0", M4_DIGIT(4), M4_DYNAMIC(0))
  float normal[4];
  // M4_ARRAY_DESC("big", "f32", M4_SIZE(1,4), M4_RANGE(-8,8), "0", M4_DIGIT(4), M4_DYNAMIC(0))
  float big[4];
} CalibDbV2_Tcs_Range_Ill2_t;

typedef struct CalibDbV2_Uv_Range_Ill_s {
  // M4_ARRAY_DESC("u", "f32", M4_SIZE(1,4), M4_RANGE(0,255), "0", M4_DIGIT(1), M4_DYNAMIC(0))
  float u[4];
  // M4_ARRAY_DESC("v", "f32", M4_SIZE(1,4), M4_RANGE(0,255), "0", M4_DIGIT(1), M4_DYNAMIC(0))
  float v[4];
} CalibDbV2_Uv_Range_Ill_t;

typedef enum CalibDbV2_Awb_DoorType_e {
  CALIB_AWB_DOOR_TYPE_INDOOR = 1,
  CALIB_AWB_DOOR_TYPE_AMBIGUITY = 2,
  CALIB_AWB_DOOR_TYPE_OUTDOOR = 3,
} CalibDbV2_Awb_DoorType_t;

typedef struct CalibDbV2_Awb_Light_V20_s {
  // M4_STRING_DESC("name", M4_SIZE(1,1), M4_RANGE(0, 16), "default", M4_DYNAMIC(0))
  char* name;
  // M4_ENUM_DESC("doorType", "CalibDbV2_Awb_DoorType_t", "CALIB_AWB_DOOR_TYPE_AMBIGUITY")
  CalibDbV2_Awb_DoorType_t doorType;
  // M4_ARRAY_DESC("standardGainValue", "f32", M4_SIZE(1,4), M4_RANGE(0,4), "1.0", M4_DIGIT(4), M4_DYNAMIC(0))
  float standardGainValue[4];
  // M4_ARRAY_TABLE_DESC("uvRegion", "array_table_ui", M4_INDEX_DEFAULT)
  CalibDbV2_Uv_Range_Ill_t uvRegion;
  // M4_ARRAY_TABLE_DESC("xyRegion", "array_table_ui", M4_INDEX_DEFAULT)
  CalibDbV2_Tcs_Range_Ill_t xyRegion;
  // M4_STRUCT_DESC("yuvRegion", "normal_ui_style")
  CalibDbV2_Yuv3D_Range_Ill_t yuvRegion;
  // M4_ARRAY_DESC("staWeight", "u8", M4_SIZE(1,16), M4_RANGE(0,100), "0", M4_DIGIT(0), M4_DYNAMIC(0))
  unsigned char staWeight[16];
  // M4_ARRAY_DESC("dayGainLvThSet", "u32", M4_SIZE(1,2), M4_RANGE(0,255000), "0", M4_DIGIT(0), M4_DYNAMIC(0))
  unsigned int dayGainLvThSet[2];
  // M4_ARRAY_DESC("defaultDayGainLow", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
  float defaultDayGainLow[4];//spatial gain
  // M4_ARRAY_DESC("defaultDayGainHigh", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
  float defaultDayGainHigh[4];
  // M4_BOOL_DESC("xyType2Enable", "1", M4_HIDE(1))
  
# 150 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h" 3 4
 _Bool 
# 150 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h"
       xyType2Enable;
} CalibDbV2_Awb_Light_V20_t;

typedef enum CalibDb_Window_Mode_e {
  CALIB_AWB_WINDOW_CFG_AUTO = 0,
  CALIB_AWB_WINDOW_CFG_FIXED,
} CalibDb_Window_Mode_t;

typedef struct CalibDbV2_StatWindow_s {
  // M4_ENUM_DESC("mode", "CALIB_AWB_WINDOW_CFG_AUTO", "CALIB_AWB_WINDOW_CFG_AUTO")
  CalibDb_Window_Mode_t mode;
  // M4_ARRAY_DESC("window", "f32", M4_SIZE(1,4), M4_RANGE(0,100), "[0,0,1,1]", M4_DIGIT(2), M4_DYNAMIC(0))
  float window[4];//percent 100% ,between[0,100]
} CalibDbV2_StatWindow_t;

typedef struct CalibDbV2_Awb_Cct_Clip_Cfg_s {
  // M4_BOOL_DESC("enable", "0")
  
# 167 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h" 3 4
 _Bool 
# 167 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h"
      enable;
  // M4_ARRAY_DESC("cct", "f32", M4_SIZE(1,5), M4_RANGE(0,10000), "0", M4_DIGIT(0), M4_DYNAMIC(1))
  float* cct;
  int cct_len;
  // M4_ARRAY_DESC("cri_bound_up", "f32", M4_SIZE(1,5), M4_RANGE(0,1), "0", M4_DIGIT(4), M4_DYNAMIC(1))
  float* cri_bound_up;
  int cri_bound_up_len;
  // M4_ARRAY_DESC("cri_bound_low", "f32", M4_SIZE(1,5), M4_RANGE(0,1), "0", M4_DIGIT(4), M4_DYNAMIC(1))
  float* cri_bound_low;
  int cri_bound_low_len;
} CalibDbV2_Awb_Cct_Clip_Cfg_t;

typedef struct CalibDbV2_Awb_Cct_DaylightClip_Cfg_s {
  // M4_BOOL_DESC("enable", "0")
  
# 181 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h" 3 4
 _Bool 
# 181 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h"
       enable;
  // M4_NUMBER_DESC("outdoor_cct_min", "f32", M4_RANGE(0,10000), "5000", M4_DIGIT(0))
  float outdoor_cct_min;
} CalibDbV2_Awb_Cct_DaylightClip_Cfg_t;

typedef struct CalibDbV2_Awb_Limit_Range_s {
  // M4_ARRAY_DESC("lumaValue", "f32", M4_SIZE(1,5), M4_RANGE(0,255000), "0", M4_DIGIT(1), M4_DYNAMIC(1))
  float *lumaValue;
  int lumaValue_len;
  // M4_ARRAY_DESC("maxR", "u16", M4_SIZE(1,5), M4_RANGE(0,255), "230", M4_DIGIT(0), M4_DYNAMIC(1))
  unsigned short *maxR;
  int maxR_len;
  // M4_ARRAY_DESC("minR", "u16", M4_SIZE(1,5), M4_RANGE(0,255), "3", M4_DIGIT(0), M4_DYNAMIC(1))
  unsigned short *minR;
  int minR_len;
  // M4_ARRAY_DESC("maxG", "u16", M4_SIZE(1,5), M4_RANGE(0,255), "230", M4_DIGIT(0), M4_DYNAMIC(1))
  unsigned short *maxG;
  int maxG_len;
  // M4_ARRAY_DESC("minG", "u16", M4_SIZE(1,5), M4_RANGE(0,255), "3", M4_DIGIT(0), M4_DYNAMIC(1))
  unsigned short *minG;
  int minG_len;
  // M4_ARRAY_DESC("maxB", "u16", M4_SIZE(1,5), M4_RANGE(0,255), "230", M4_DIGIT(0), M4_DYNAMIC(1))
  unsigned short *maxB;
  int maxB_len;
  // M4_ARRAY_DESC("minB", "u16", M4_SIZE(1,5), M4_RANGE(0,255), "3", M4_DIGIT(0), M4_DYNAMIC(1))
  unsigned short *minB;
  int minB_len;
  // M4_ARRAY_DESC("maxY", "u16", M4_SIZE(1,5), M4_RANGE(0,255), "230", M4_DIGIT(0), M4_DYNAMIC(1))
  unsigned short *maxY;
  int maxY_len;
  // M4_ARRAY_DESC("minY", "u16", M4_SIZE(1,5), M4_RANGE(0,255), "3", M4_DIGIT(0), M4_DYNAMIC(1))
  unsigned short *minY;
  int minY_len;
} CalibDbV2_Awb_Limit_Range_t;

typedef struct CalibDbV2_Rgb2Tcs_s {
  // M4_ARRAY_DESC("pseudoLuminanceWeight", "f32", M4_SIZE(1,3), M4_RANGE(0,1), "0.3", M4_DIGIT(6), M4_DYNAMIC(0))
  float pseudoLuminanceWeight[3];
  // M4_ARRAY_DESC("rotationMat", "f32", M4_SIZE(3,3), M4_RANGE(0,1), "0.3", M4_DIGIT(6), M4_DYNAMIC(0))
  float rotationMat[9];
} CalibDbV2_Rgb2Tcs_t;

typedef struct CalibDbV2_Awb_Sgc_Cblk_s {
  // M4_NUMBER_DESC("index", "u16", M4_RANGE(1,24), "1", M4_DIGIT(0))
  unsigned short index;
  // M4_NUMBER_DESC("meanC", "f32", M4_RANGE(0,255), "0", M4_DIGIT(6))
  float meanC;
  // M4_NUMBER_DESC("meanH", "f32", M4_RANGE(-180,180), "0", M4_DIGIT(6))
  float meanH;
} CalibDbV2_Awb_Sgc_Cblk_t;

typedef struct CalibDbV2_Awb_Sgc_Ls_s {
  // M4_STRING_DESC("name", M4_SIZE(1,1), M4_RANGE(0, 16), "default", M4_DYNAMIC(0))
  char* name;
  // M4_NUMBER_DESC("RGain", "f32", M4_RANGE(0,8), "1", M4_DIGIT(6))
  float RGain;
  // M4_NUMBER_DESC("BGain", "f32", M4_RANGE(0,8), "1", M4_DIGIT(6))
  float BGain;
} CalibDbV2_Awb_Sgc_Ls_t;

typedef struct CalibDbV2_Awb_Sgc_s {
  // M4_BOOL_DESC("enable", "0")
  
# 243 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h" 3 4
 _Bool 
# 243 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h"
      enable;
  // M4_STRUCT_LIST_DESC("colorBlock", M4_SIZE(1,24), "normal_ui_style")
  CalibDbV2_Awb_Sgc_Cblk_t *colorBlock;
  int colorBlock_len;
  // M4_STRUCT_LIST_DESC("lsUsedForEstimation", M4_SIZE(1,7), "normal_ui_style")
  CalibDbV2_Awb_Sgc_Ls_t *lsUsedForEstimation;
  int lsUsedForEstimation_len;
  // M4_NUMBER_DESC("alpha", "f32", M4_RANGE(0,1), "1", M4_DIGIT(4))
  float alpha;
} CalibDbV2_Awb_Sgc_t;

typedef enum CalibDbV2_Awb_Hdr_Fr_Ch_Mode_e {
  CALIB_AWB_HDR_FRAME_CHOOSE_MODE_MANUAL = 0,
  CALIB_AWB_HDR_FRAME_CHOOSE_MODE_AUTO
} CalibDbV2_Awb_Hdr_Fr_Ch_Mode_t;

typedef struct CalibDbV2_Awb_Hdr_Fr_Ch_s {
  // M4_ENUM_DESC("frameChooseMode", "CalibDbV2_Awb_Hdr_Fr_Ch_Mode_t", "CALIB_AWB_HDR_FRAME_CHOOSE_MODE_AUTO")
  CalibDbV2_Awb_Hdr_Fr_Ch_Mode_t frameChooseMode;
  // M4_NUMBER_DESC("frameChoose", "u8", M4_RANGE(0,2), "1", M4_DIGIT(0))
  unsigned char frameChoose;
} CalibDbV2_Awb_Hdr_Fr_Ch_t;

typedef enum CalibDbV2_Awb_Mul_Win_Mode_e {
  CALIB_AWB_WIN_USELESS = 0,
  CALIB_AWB_WIN_EXTRAWP = 1,
  CALIB_AWB_WIN_WEIGHTWP = 2,
} CalibDbV2_Awb_Mul_Win_Mode_t;

typedef struct CalibDbV2_Awb_Mul_Win_s {
  // M4_BOOL_DESC("enable", "1")
  
# 274 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h" 3 4
 _Bool 
# 274 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h"
       enable;
  // M4_ENUM_DESC("multiwindowMode", "CalibDbV2_Awb_Mul_Win_Mode_t", "CALIB_AWB_WIN_USELESS")
  CalibDbV2_Awb_Mul_Win_Mode_t multiwindowMode;
  // M4_ARRAY_DESC("window", "u16", M4_SIZE(8,4), M4_RANGE(0,8191), "0", M4_DIGIT(0), M4_DYNAMIC(0))
  float window[8][4];//8  windows in pixel domain ,hOffset,vOffser,hSize,vSize;
  // M4_ARRAY_DESC("weight", "u16", M4_SIZE(8,4), M4_RANGE(0,10), "0", M4_DIGIT(4), M4_DYNAMIC(0))
  float weight;//weight for 8  windows;
} CalibDbV2_Awb_Mul_Win_t;

typedef struct CalibDbV2_Wb_Awb_Div_WpTh_s{
  //  M4_ARRAY_DESC("lumaValue", "f32", M4_SIZE(1,5), M4_RANGE(0,255000), "0", M4_DIGIT(1), M4_DYNAMIC(1))
  float *lumaValue;
  int lumaValue_len;
  // M4_ARRAY_DESC("low", "f32", M4_SIZE(1,5), M4_RANGE(0,100000), "0", M4_DIGIT(0), M4_DYNAMIC(1))
  float *low;
  int low_len;
  // M4_ARRAY_DESC("high", "f32", M4_SIZE(1,5), M4_RANGE(0,100000), "0", M4_DIGIT(0), M4_DYNAMIC(1))
  float *high;
  int high_len;
}CalibDbV2_Wb_Awb_Div_WpTh_t;

typedef struct CalibDbV2_Wb_Awb_Div_s {
  // M4_NUMBER_DESC("lumaValThLow", "u32", M4_RANGE(0, 255000), "0", M4_DIGIT(0))
  unsigned int lumaValThLow;
  // M4_NUMBER_DESC("lumaValThLow2", "u32", M4_RANGE(0, 255000), "0", M4_DIGIT(0))
  unsigned int lumaValThLow2;
  // M4_NUMBER_DESC("lumaValThHigh", "u32", M4_RANGE(0, 255000), "0", M4_DIGIT(0))
  unsigned int lumaValThHigh;
  // M4_NUMBER_DESC("lumaValThHigh2", "u32", M4_RANGE(0, 255000), "0", M4_DIGIT(0))
  unsigned int lumaValThHigh2;
  // M4_ARRAY_TABLE_DESC("wpNumTh", "array_table_ui", M4_INDEX_DEFAULT)
  CalibDbV2_Wb_Awb_Div_WpTh_t wpNumTh;
} CalibDbV2_Wb_Awb_Div_t;

typedef struct CalibDbV2_Wb_Awb_Caga_s {
  // M4_BOOL_DESC("enable", "1")
  
# 310 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h" 3 4
 _Bool 
# 310 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h"
      enable;
  // M4_ARRAY_DESC("targetGain", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
  float targetGain[4];//cagaTargetGain
  // M4_NUMBER_DESC("laCalcFactor", "f32", M4_RANGE(0, 255), "0", M4_DIGIT(4))
  float laCalcFactor;
} CalibDbV2_Wb_Awb_Caga_t;

typedef struct CalibDbV2_Wb_Awb_Prob_Calc_Dis_s {
  // M4_NUMBER_DESC("proDis_THH", "f32", M4_RANGE(0, 8), "0", M4_DIGIT(4))
  float proDis_THH; //threshold for distance probality calculation// rename to do
  // M4_NUMBER_DESC("proDis_THL", "f32", M4_RANGE(0, 8), "0", M4_DIGIT(4))
  float proDis_THL;
} CalibDbV2_Wb_Awb_Prob_Calc_Dis_t;

typedef struct CalibDbV2_Wb_Awb_Prob_Calc_Lv_s {
  // M4_NUMBER_DESC("outdoorLumaValThLow", "u32", M4_RANGE(0, 255000), "0", M4_DIGIT(0))
  unsigned int outdoorLumaValThLow;
  // M4_NUMBER_DESC("outdoorLumaValThHigh", "u32", M4_RANGE(0, 255000), "0", M4_DIGIT(0))
  unsigned int outdoorLumaValThHigh;// threshold for luminance probality calculation
} CalibDbV2_Wb_Awb_Prob_Calc_Lv_t;

typedef struct CalibDbV2_Wb_Awb_Prob_Calc_Wp_s {
  // M4_NUMBER_DESC("wpNumPercTh", "f32", M4_RANGE(0, 1), "0", M4_DIGIT(6))
  float wpNumPercTh;
  // M4_NUMBER_DESC("wpNumPercTh2", "f32", M4_RANGE(0, 1), "0", M4_DIGIT(6))
  float wpNumPercTh2;
} CalibDbV2_Wb_Awb_Prob_Calc_Wp_t;

typedef struct CalibDbV2_Wb_Awb_Convg_s {
  // M4_NUMBER_DESC("varThforUnDamp", "f32", M4_RANGE(0, 1), "0", M4_DIGIT(4))
  float varThforUnDamp;
  // M4_NUMBER_DESC("varThforDamp", "f32", M4_RANGE(0, 1), "0", M4_DIGIT(4))
  float varThforDamp;
} CalibDbV2_Wb_Awb_Convg_t;

typedef struct CalibDbV2_Awb_Tolerance_s {
  // M4_ARRAY_DESC("lumaValue", "f32", M4_SIZE(1,4), M4_RANGE(0,255000), "0", M4_DIGIT(0), M4_DYNAMIC(1))
  float* lumaValue;
  int lumaValue_len;
  // M4_ARRAY_DESC("toleranceValue", "f32", M4_SIZE(1,4), M4_RANGE(0,1), "0", M4_DIGIT(4), M4_DYNAMIC(1))
  float* toleranceValue;
  int toleranceValue_len;
} CalibDbV2_Awb_Tolerance_t;

typedef struct CalibDbV2_Awb_runinterval_s {
  // M4_ARRAY_DESC("lumaValue", "f32", M4_SIZE(1,4), M4_RANGE(0,255000), "0", M4_DIGIT(0), M4_DYNAMIC(1))
  float *lumaValue;
  int lumaValue_len;
  // M4_ARRAY_DESC("intervalValue", "f32", M4_SIZE(1,4), M4_RANGE(0,255), "0", M4_DIGIT(0), M4_DYNAMIC(1))
  float *intervalValue;
  int intervalValue_len;
} CalibDbV2_Awb_runinterval_t;

typedef struct CalibDbV2_Awb_DampFactor_s {
  // M4_NUMBER_DESC("dFStep", "f32", M4_RANGE(0, 1), "0", M4_DIGIT(4))
  float dFStep;
  // M4_NUMBER_DESC("dFMin", "f32", M4_RANGE(0, 1), "0", M4_DIGIT(4))
  float dFMin;
  // M4_NUMBER_DESC("dFMax", "f32", M4_RANGE(0, 1), "0", M4_DIGIT(4))
  float dFMax;
  // M4_NUMBER_DESC("lvIIRsize", "u32", M4_RANGE(0, 128), "0", M4_DIGIT(0))
  int lvIIRsize;
  // M4_NUMBER_DESC("lvVarTh", "f32", M4_RANGE(0, 100), "0", M4_DIGIT(4))
  float lvVarTh;
} CalibDbV2_Awb_DampFactor_t;

typedef struct CalibDbV2_Awb_Cct_Lut_Cfg_Lv_s {
  // M4_NUMBER_DESC("lumaValue", "f32", M4_RANGE(0, 255000), "0", M4_DIGIT(0))
  float lumaValue;
  // M4_NUMBER_DESC("ct_grid_num", "s32", M4_RANGE(0, 32), "0", M4_DIGIT(0))
  int ct_grid_num;
  // M4_NUMBER_DESC("cri_grid_num", "s32", M4_RANGE(0, 32), "0", M4_DIGIT(0))
  int cri_grid_num;
  // M4_ARRAY_DESC("ct_in_range", "f32", M4_SIZE(1,2), M4_RANGE(0,10000), "0", M4_DIGIT(0), M4_DYNAMIC(0))
  float ct_in_range[2];//min,max, equal distance sapmle
  // M4_ARRAY_DESC("cri_in_range", "f32", M4_SIZE(1,2), M4_RANGE(-2,2), "0", M4_DIGIT(4), M4_DYNAMIC(0))
  float cri_in_range[2];//min,max
  // M4_ARRAY_DESC("ct_lut_out", "f32", M4_SIZE(9,7), M4_RANGE(0,10000), "0", M4_DIGIT(0), M4_DYNAMIC(0))
  float *ct_lut_out;
  int ct_lut_out_len;
  // M4_ARRAY_DESC("cri_lut_out", "f32", M4_SIZE(9,7), M4_RANGE(-2,2), "0", M4_DIGIT(4), M4_DYNAMIC(0))
  float *cri_lut_out;
  int cri_lut_out_len;
} CalibDbV2_Awb_Cct_Lut_Cfg_Lv_t;

typedef struct CalibDbV2_Awb_GainAdjust_s {
  // M4_BOOL_DESC("enable", "1")
  
# 397 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h" 3 4
 _Bool 
# 397 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h"
      enable;
  // M4_STRUCT_LIST_DESC("lutAll", M4_SIZE(1,8), "normal_ui_style")
  CalibDbV2_Awb_Cct_Lut_Cfg_Lv_t *lutAll;
  int lutAll_len;
} CalibDbV2_Awb_GainAdjust_t;

typedef struct CalibDbV2_Awb_Remosaic_Para_s {
  // M4_BOOL_DESC("enable", "1")
  
# 405 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h" 3 4
 _Bool 
# 405 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h"
      enable;
  // M4_BOOL_DESC("applyInvWbGainEnable", "1")
  
# 407 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h" 3 4
 _Bool 
# 407 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h"
      applyInvWbGainEnable;
  // M4_ARRAY_DESC("sensorWbGain", "f32", M4_SIZE(1,4), M4_RANGE(0,4), "1", M4_DIGIT(4), M4_DYNAMIC(0))
  float sensorWbGain[4];
} CalibDbV2_Awb_Remosaic_Para_t;

typedef struct CalibDbV2_Awb_xyRegion_stable_WpTh_s {
    // M4_ARRAY_DESC("lumaValue", "f32", M4_SIZE(1,5), M4_RANGE(0,255000), "0", M4_DIGIT(1), M4_DYNAMIC(1))
    float *lumaValue;
    int lumaValue_len;
    // M4_ARRAY_DESC("forBigType", "f32", M4_SIZE(1,5), M4_RANGE(0,100000), "0", M4_DIGIT(0), M4_DYNAMIC(1))
    float *forBigType;
    int forBigType_len;
    // M4_ARRAY_DESC("forExtraType", "f32", M4_SIZE(1,5), M4_RANGE(0,100000), "0", M4_DIGIT(0), M4_DYNAMIC(1))
    float *forExtraType;
    int forExtraType_len;
} CalibDbV2_Awb_xyRegion_stable_WpTh_t;

typedef struct CalibDbV2_Awb_xyRegion_stable_s {
  // M4_BOOL_DESC("enable", "1")
  
# 426 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h" 3 4
 _Bool 
# 426 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h"
      enable;
  //  M4_ARRAY_TABLE_DESC("wpNumTh", "array_table_ui", M4_INDEX_DEFAULT)
  CalibDbV2_Awb_xyRegion_stable_WpTh_t wpNumTh;
  // M4_NUMBER_DESC("xyTypeListSize", "s32", M4_RANGE(0, 65535), "0", M4_DIGIT(0))
  int xyTypeListSize;// xyTypeListSize ==0 will disable this function
  // M4_NUMBER_DESC("varianceLumaTh", "f32", M4_RANGE(0, 100), "0", M4_DIGIT(4))
  float varianceLumaTh;
} CalibDbV2_Awb_xyRegion_stable_t;

typedef struct CalibDbV2_Awb_gain_offset_cfg_s{
  // M4_BOOL_DESC("enable", "1")
  
# 437 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h" 3 4
 _Bool 
# 437 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h"
      enable;
  // M4_ARRAY_DESC("offset", "f32", M4_SIZE(1,4), M4_RANGE(-8,8), "0", M4_DIGIT(4), M4_DYNAMIC(0))
  float offset[4];//rggb
}CalibDbV2_Awb_gain_offset_cfg_t;

typedef struct CalibDbV2_Wb_Awb_Ext_Com_Para_t{
  // M4_STRING_DESC("lightSourceForFirstFrame", M4_SIZE(1,1), M4_RANGE(-128, 127), "default", M4_DYNAMIC(0))
  char *lightSourceForFirstFrame;
  // M4_ARRAY_TABLE_DESC("tolerance", "array_table_ui", M4_INDEX_DEFAULT)
  CalibDbV2_Awb_Tolerance_t tolerance;//wb gain diff th for awb gain update, set 0 to disable this function
  // M4_ARRAY_TABLE_DESC("runInterval", "array_table_ui", M4_INDEX_DEFAULT)
  CalibDbV2_Awb_runinterval_t runInterval;
  // M4_STRUCT_DESC("dampFactor", "normal_ui_style")
  CalibDbV2_Awb_DampFactor_t dampFactor;
  // M4_STRUCT_DESC("wbGainAdjust", "normal_ui_style")
  CalibDbV2_Awb_GainAdjust_t wbGainAdjust;
  // M4_STRUCT_DESC("wbGainDaylightClip", "normal_ui_style")
  CalibDbV2_Awb_Cct_DaylightClip_Cfg_t wbGainDaylightClip;
  // M4_STRUCT_DESC("wbGainClip", "normal_ui_style")
  CalibDbV2_Awb_Cct_Clip_Cfg_t wbGainClip;
  // M4_STRUCT_DESC("division", "normal_ui_style")
  CalibDbV2_Wb_Awb_Div_t division;
  // M4_ARRAY_DESC("defaultNightGain", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
  float defaultNightGain[4];
  // M4_ARRAY_DESC("lumaValueMatrix", "u32", M4_SIZE(1,16), M4_RANGE(0,255000), "1", M4_DIGIT(0), M4_DYNAMIC(0))
  unsigned int lumaValueMatrix[16];
  // M4_ARRAY_DESC("defaultNightGainWeight", "u8", M4_SIZE(1,16), M4_RANGE(0,100), "1", M4_DIGIT(0), M4_DYNAMIC(0))
  unsigned char defaultNightGainWeight[16];
  // M4_STRUCT_DESC("probCalcDis", "normal_ui_style")
  CalibDbV2_Wb_Awb_Prob_Calc_Dis_t probCalcDis;
  // M4_STRUCT_DESC("probCalcLv", "normal_ui_style")
  CalibDbV2_Wb_Awb_Prob_Calc_Lv_t probCalcLv;
  // M4_STRUCT_DESC("probCalcWp", "normal_ui_style")
  CalibDbV2_Wb_Awb_Prob_Calc_Wp_t probCalcWp;
  // M4_STRUCT_DESC("converged", "normal_ui_style")
  CalibDbV2_Wb_Awb_Convg_t converged;
  // M4_STRUCT_DESC("xyRegionStableSelection", "normal_ui_style")
  CalibDbV2_Awb_xyRegion_stable_t xyRegionStableSelection;
  // M4_ARRAY_DESC("weightForNightGainCalc", "u8", M4_SIZE(1,16), M4_RANGE(0,100), "1", M4_DIGIT(0), M4_DYNAMIC(1))
  unsigned char *weightForNightGainCalc;
  int weightForNightGainCalc_len;
  // M4_STRUCT_DESC("singleColorProces", "normal_ui_style")
  CalibDbV2_Awb_Sgc_t singleColorProces;
  // M4_ARRAY_DESC("lineRgBg", "f32", M4_SIZE(1,3), M4_RANGE(-2147483648,2147483647), "1", M4_DIGIT(4), M4_DYNAMIC(0), M4_HIDE(1))
  float lineRgBg[3];
  // M4_ARRAY_DESC("lineRgProjCCT", "f32", M4_SIZE(1,3), M4_RANGE(-2147483648,2147483647), "1", M4_DIGIT(4), M4_DYNAMIC(0), M4_HIDE(1))
  float lineRgProjCCT[3];
  // M4_STRUCT_DESC("chrAdpttAdj", "normal_ui_style", M4_HIDE(1))
  CalibDbV2_Wb_Awb_Caga_t chrAdpttAdj;
  // M4_STRUCT_DESC("remosaicCfg", "normal_ui_style")
  CalibDbV2_Awb_Remosaic_Para_t remosaicCfg;
  // M4_STRUCT_DESC("wbGainOffset", "normal_ui_style")
  CalibDbV2_Awb_gain_offset_cfg_t wbGainOffset;
} CalibDbV2_Wb_Awb_Ext_Com_Para_t;


typedef struct CalibDbV2_Wb_Awb_Para_V20_t {
  // M4_STRUCT_DESC("hdrPara", "normal_ui_style")
  CalibDbV2_Awb_Hdr_Fr_Ch_t hdrPara;
  // M4_BOOL_DESC("lscBypassEnable", "0");
  
# 497 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h" 3 4
 _Bool 
# 497 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h"
                     lscBypassEnable;
  // M4_BOOL_DESC("uvDetectionEnable", "1");
  
# 499 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h" 3 4
 _Bool 
# 499 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h"
                     uvDetectionEnable;
  // M4_BOOL_DESC("xyDetectionEnable", "1");
  
# 501 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h" 3 4
 _Bool 
# 501 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h"
                     xyDetectionEnable;
  // M4_BOOL_DESC("yuvDetectionEnable", "1");
  
# 503 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h" 3 4
 _Bool 
# 503 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h"
                     yuvDetectionEnable;
  // CXF CHECK
  // M4_STRING_DESC("lsUsedForYuvDet", M4_SIZE(1,7), M4_RANGE(-128,127), "light", M4_DYNAMIC(1), M4_HIDE(1));
  char** lsUsedForYuvDet;
  int lsUsedForYuvDet_len;
  // M4_NUMBER_DESC("yuvDetRef_u", "u8", M4_RANGE(0,255), "0", M4_DIGIT(0), M4_HIDE(1))
  unsigned char yuvDetRef_u; //8u //cxf3333
  // M4_ENUM_DESC("downScaleMode", "CalibDbV2_Awb_Down_Scale_Mode_t","CALIB_AWB_DS_4X4");
  CalibDbV2_Awb_Down_Scale_Mode_t downScaleMode;
  // M4_ENUM_DESC("blkMeasureMode", "CalibDbV2_Awb_Blk_Stat_Mode_V20_t","CALIB_AWB_BLK_STAT_MODE_ALL_V200");
  CalibDbV2_Awb_Blk_Stat_Mode_V20_t blkMeasureMode;
  // M4_STRUCT_DESC("mainWindow", "normal_ui_style")
  CalibDbV2_StatWindow_t mainWindow;
  // M4_ARRAY_TABLE_DESC("limitRange", "array_table_ui", M4_INDEX_DEFAULT)
  CalibDbV2_Awb_Limit_Range_t limitRange;
  // M4_STRUCT_DESC("rgb2TcsPara", "normal_ui_style", M4_HIDE(1))
  CalibDbV2_Rgb2Tcs_t rgb2TcsPara;
  // M4_STRUCT_DESC("multiWindow", "normal_ui_style")
  CalibDbV2_Awb_Mul_Win_t multiWindow;
  // M4_STRUCT_LIST_DESC("extraWpRange", M4_SIZE(1,7), "normal_ui_style")
  CalibDbV2_ExtRange_t extraWpRange[7];
  // M4_STRUCT_LIST_DESC("lightSources", M4_SIZE(1,7), "normal_ui_style")
  CalibDbV2_Awb_Light_V20_t* lightSources;
  int lightSources_len;
} CalibDbV2_Wb_Awb_Para_V20_t;

typedef struct CalibDbV2_Awb_Luma_Weight_Enable_Th_s {
  // M4_NUMBER_DESC("wpDiffWeiNoTh", "f32", M4_RANGE(0,1), "0", M4_DIGIT(4))
  float wpDiffWeiNoTh;
  // M4_NUMBER_DESC("wpDiffWeiLvValueTh", "u32", M4_RANGE(0,255000), "0", M4_DIGIT(0))
  unsigned int wpDiffWeiLvValueTh;
} CalibDbV2_Awb_Luma_Weight_Enable_Th_t;

typedef struct CalibDbV2_Awb_Luma_Weight_Lv_Ratio_s {
  // M4_NUMBER_DESC("ratioValue", "f32", M4_RANGE(0,1), "0", M4_DIGIT(4))
  float ratioValue;
  // M4_ARRAY_DESC("weight", "f32", M4_SIZE(1,9), M4_RANGE(0,1), "0", M4_DIGIT(4), M4_DYNAMIC(0))
  float weight[9] ;
} CalibDbV2_Awb_Luma_Weight_Lv_Ratio_t;

typedef struct CalibDbV2_Awb_Luma_Weight_Lv_s {
  // M4_NUMBER_DESC("LvValue", "f32", M4_RANGE(0,255000), "0", M4_DIGIT(0))
  float LvValue;
  // M4_STRUCT_LIST_DESC("ratioSet", M4_SIZE(1,4), "normal_ui_style")
  CalibDbV2_Awb_Luma_Weight_Lv_Ratio_t* ratioSet;
  int ratioSet_len;
} CalibDbV2_Awb_Luma_Weight_Lv_t;

typedef struct CalibDbV2_Awb_Luma_Weight_s {
  //with differernt luma ,the different weight in WP sum
  // M4_BOOL_DESC("enable", "0");
  
# 554 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h" 3 4
 _Bool 
# 554 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h"
      enable;
  // M4_STRUCT_DESC("wpDiffWeiEnableTh", "normal_ui_style")
  CalibDbV2_Awb_Luma_Weight_Enable_Th_t wpDiffWeiEnableTh;
  // M4_ARRAY_DESC("wpDiffwei_y", "u8", M4_SIZE(1,9), M4_RANGE(0,255), "0", M4_DIGIT(0), M4_DYNAMIC(0))
  unsigned char wpDiffwei_y[9];
  // M4_ARRAY_DESC("perfectBin", "u8", M4_SIZE(1,8), M4_RANGE(0,1), "0", M4_DIGIT(0), M4_DYNAMIC(0))
  unsigned char perfectBin[8];// true means the luma is appropriate
  // M4_STRUCT_LIST_DESC("wpDiffWeightLvSet", M4_SIZE(1,4), "normal_ui_style")
  CalibDbV2_Awb_Luma_Weight_Lv_t* wpDiffWeightLvSet;
  int wpDiffWeightLvSet_len;
} CalibDbV2_Awb_Luma_Weight_t;

typedef struct CalibDbV2_Awb_Light_V21_s {
  // M4_STRING_DESC("name", M4_SIZE(1,1), M4_RANGE(0, 32), "default", M4_DYNAMIC(0))
  char* name;
  // M4_ENUM_DESC("doorType", "CalibDbV2_Awb_DoorType_t", "CALIB_AWB_DOOR_TYPE_AMBIGUITY")
  CalibDbV2_Awb_DoorType_t doorType;
  // M4_ARRAY_DESC("standardGainValue", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "0", M4_DIGIT(4), M4_DYNAMIC(0))
  float standardGainValue[4];
  // M4_ARRAY_TABLE_DESC("uvRegion", "array_table_ui", M4_INDEX_DEFAULT)
  CalibDbV2_Uv_Range_Ill_t uvRegion;
  // M4_ARRAY_TABLE_DESC("xyRegion", "array_table_ui", M4_INDEX_DEFAULT)
  CalibDbV2_Tcs_Range_Ill2_t xyRegion;
  // M4_STRUCT_DESC("rtYuvRegion", "normal_ui_style")
  CalibDbV2_Yuv3D_2_Range_Ill_t rtYuvRegion;
  // M4_ARRAY_DESC("staWeight", "u8", M4_SIZE(1,16), M4_RANGE(0,100), "0", M4_DIGIT(0), M4_DYNAMIC(0))
  unsigned char staWeight[16];
  // M4_ARRAY_DESC("dayGainLvThSet", "u8", M4_SIZE(1,2), M4_RANGE(0,255000), "0", M4_DIGIT(0), M4_DYNAMIC(0))
  unsigned int dayGainLvThSet[2];
  // M4_ARRAY_DESC("defaultDayGainLow", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
  float defaultDayGainLow[4];//spatial gain
  // M4_ARRAY_DESC("defaultDayGainHigh", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
  float defaultDayGainHigh[4];
  // M4_NUMBER_DESC("xyType2Enable", "u8", M4_RANGE(0,1), "1", M4_DIGIT(0), M4_HIDE(1))
  unsigned char xyType2Enable;
} CalibDbV2_Awb_Light_V21_t;

typedef struct CalibDbV2_Wb_Awb_Para_V21_t {
  // M4_STRUCT_DESC("hdrPara", "normal_ui_style")
  CalibDbV2_Awb_Hdr_Fr_Ch_t hdrPara;//hdrFrameChoose;
  // M4_BOOL_DESC("lscBypassEnable", "0");
  
# 595 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h" 3 4
 _Bool 
# 595 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h"
                     lscBypassEnable;
  // M4_BOOL_DESC("uvDetectionEnable", "0");
  
# 597 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h" 3 4
 _Bool 
# 597 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h"
                     uvDetectionEnable;
  // M4_BOOL_DESC("xyDetectionEnable", "0");
  
# 599 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h" 3 4
 _Bool 
# 599 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h"
                     xyDetectionEnable;
  // M4_BOOL_DESC("yuvDetectionEnable", "0");
  
# 601 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h" 3 4
 _Bool 
# 601 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h"
                     yuvDetectionEnable;
  // M4_STRING_DESC("lsUsedForYuvDet", M4_SIZE(1,7), M4_RANGE(0, 16), "default", M4_DYNAMIC(1), M4_HIDE(1))
  char** lsUsedForYuvDet;
  int lsUsedForYuvDet_len;
  // M4_BOOL_DESC("blkStatisticsEnable", "0");
  
# 606 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h" 3 4
 _Bool 
# 606 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h"
                     blkStatisticsEnable;
  // M4_ENUM_DESC("downScaleMode", "CalibDbV2_Awb_Down_Scale_Mode_t", "CALIB_AWB_DS_8X8")
  CalibDbV2_Awb_Down_Scale_Mode_t downScaleMode;
  // M4_ENUM_DESC("blkMeasureMode", "CalibDbV2_Awb_Blk_Stat_Mode_V21_t", "CALIB_AWB_BLK_STAT_MODE_REALWP_V201")
  CalibDbV2_Awb_Blk_Stat_Mode_V21_t blkMeasureMode;
  // M4_STRUCT_DESC("mainWindow", "normal_ui_style")
  CalibDbV2_StatWindow_t mainWindow;
  // M4_ARRAY_TABLE_DESC("limitRange", "array_table_ui", M4_INDEX_DEFAULT)
  CalibDbV2_Awb_Limit_Range_t limitRange;
  // M4_STRUCT_DESC("rgb2TcsPara", "normal_ui_style", M4_HIDE(1))
  CalibDbV2_Rgb2Tcs_t rgb2TcsPara;
  // M4_ARRAY_DESC("rgb2RotationYuvMat", "f32", M4_SIZE(4,4), M4_RANGE(-255,255), "0", M4_DIGIT(6), M4_DYNAMIC(0), M4_HIDE(1))
  float rgb2RotationYuvMat[16];
  //several winow in uv or xy domain
  // M4_STRUCT_LIST_DESC("extraWpRange", M4_SIZE(1,7), "normal_ui_style")
  CalibDbV2_ExtRange_t extraWpRange[7];
  // M4_STRUCT_DESC("wpDiffLumaWeight", "normal_ui_style")
  CalibDbV2_Awb_Luma_Weight_t wpDiffLumaWeight;
  // M4_BOOL_DESC("wpDiffBlkWeiEnable", "0");
  
# 625 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h" 3 4
 _Bool 
# 625 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h"
                wpDiffBlkWeiEnable;
  // M4_ARRAY_DESC("wpDiffBlkWeight", "u16", M4_SIZE(15,15), M4_RANGE(0,63), "0", M4_DIGIT(0), M4_DYNAMIC(0))
  unsigned short wpDiffBlkWeight[225];
  // M4_STRUCT_LIST_DESC("lightSources", M4_SIZE(1,7), "normal_ui_style")
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
  // M4_NUMBER_DESC("CCT", "f32", M4_RANGE(0,10000), "5000", M4_DIGIT(0))
  float CCT;
  // CXF CHECK
  // M4_NUMBER_DESC("CCRI", "f32", M4_RANGE(-2,2), "0", M4_DIGIT(3))
  float CCRI;
} CalibDbV2_Awb_Cct_t;
typedef struct CalibDbV2_Wb_Mwb_Cfg_Para_s{
  // M4_ARRAY_DESC("mwbGain", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1.0", M4_DIGIT(4), M4_DYNAMIC(0))
  float mwbGain[4];
  // M4_ENUM_DESC("scene", "CalibDbV2_Wb_Mwb_Scene_t", "CALIB_WB_SCENE_DAYLIGHT");
  CalibDbV2_Wb_Mwb_Scene_t scene;
  // M4_STRUCT_DESC("cct", "normal_ui_style")
  CalibDbV2_Awb_Cct_t cct;
}CalibDbV2_Wb_Mwb_Cfg_Para_t;

typedef struct CalibDbV2_Wb_Mwb_Para_s {
  // M4_ENUM_DESC("mode", "CalibDbV2_Wb_Mwb_Mode_t", "CALIB_MWB_MODE_WBGAIN");
  CalibDbV2_Wb_Mwb_Mode_t mode;
  // M4_STRUCT_DESC("cfg", "normal_ui_style")
  CalibDbV2_Wb_Mwb_Cfg_Para_t cfg;
} CalibDbV2_Wb_Mwb_Para_t;

typedef enum CalibDbV2_Wb_Op_Mode_e {
  CALIB_WB_MODE_MANUAL = 0, /**< run manual white balance */
  CALIB_WB_MODE_AUTO = 1, /**< run auto white balance */
} CalibDbV2_Wb_Op_Mode_t;

typedef struct CalibDbV2_Wb_Para_t {
  // M4_BOOL_DESC("byPass", "0");
  
# 679 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h" 3 4
 _Bool 
# 679 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_head.h"
      byPass;
  // M4_ENUM_DESC("mode", "CalibDbV2_Wb_Op_Mode_t", "CALIB_WB_MODE_AUTO");
  CalibDbV2_Wb_Op_Mode_t mode;//replace awbEnable
} CalibDbV2_Wb_Para_t;

typedef struct CalibDbV2_Wb_Para_V20_s {
  // M4_STRUCT_DESC("control", "normal_ui_style")
  CalibDbV2_Wb_Para_t control;
  // M4_STRUCT_DESC("manualPara", "normal_ui_style")
  CalibDbV2_Wb_Mwb_Para_t manualPara;
  // M4_STRUCT_DESC("autoPara", "normal_ui_style")
  CalibDbV2_Wb_Awb_Para_V20_t autoPara;
  // M4_STRUCT_DESC("autoExtPara", "normal_ui_style")
  CalibDbV2_Wb_Awb_Ext_Com_Para_t autoExtPara;
} CalibDbV2_Wb_Para_V20_t;

typedef struct CalibDbV2_Wb_Para_V21_s {
  // M4_STRUCT_DESC("control", "normal_ui_style")
  CalibDbV2_Wb_Para_t control;
  // M4_STRUCT_DESC("manualPara", "normal_ui_style")
  CalibDbV2_Wb_Mwb_Para_t manualPara;
  // M4_STRUCT_DESC("autoPara", "normal_ui_style")
  CalibDbV2_Wb_Awb_Para_V21_t autoPara;
  // M4_STRUCT_DESC("autoExtPara", "normal_ui_style")
  CalibDbV2_Wb_Awb_Ext_Com_Para_t autoExtPara;
} CalibDbV2_Wb_Para_V21_t;


# 35 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/bayer2dnr_head_v2.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/bayer2dnr_head_v2.h" 2



////////////////////////bayernr V2//////////////////////////////////////
typedef struct CalibDbV2_Bayer2dnr_V2_CalibPara_Setting_ISO_s {
    // M4_NUMBER_MARK_DESC("iso", "f32", M4_RANGE(50, 204800), "50", M4_DIGIT(1), "index2")
    float iso;

    // M4_ARRAY_DESC("lumapoint", "s32", M4_SIZE(1,16), M4_RANGE(0,65535), "0.0", M4_DIGIT(0), M4_DYNAMIC(0))
    int lumapoint[16];

    // M4_ARRAY_DESC("sigma", "s32", M4_SIZE(1,16), M4_RANGE(0,65535), "0.0", M4_DIGIT(0), M4_DYNAMIC(0))
    int sigma[16];

} CalibDbV2_Bayer2dnr_V2_CalibPara_Setting_ISO_t;

typedef struct CalibDbV2_Bayer2dnr_V2_CalibPara_Setting_s {
    // M4_STRING_MARK_DESC("SNR_Mode", M4_SIZE(1,1), M4_RANGE(0, 64), "LSNR",M4_DYNAMIC(0), "index1")
    char *SNR_Mode;
    // M4_STRING_DESC("Sensor_Mode", M4_SIZE(1,1), M4_RANGE(0, 64), "lcg", M4_DYNAMIC(0))
    char *Sensor_Mode;
    // M4_STRUCT_LIST_DESC("Calib_ISO", M4_SIZE_DYNAMIC, "double_index_list")
    CalibDbV2_Bayer2dnr_V2_CalibPara_Setting_ISO_t *Calib_ISO;
    int Calib_ISO_len;

} CalibDbV2_Bayer2dnr_V2_CalibPara_Setting_t;

typedef struct CalibDbV2_Bayer2dnr_V2_CalibPara_s {
    // M4_STRUCT_LIST_DESC("Setting", M4_SIZE_DYNAMIC, "double_index_list")
    CalibDbV2_Bayer2dnr_V2_CalibPara_Setting_t *Setting;
    int Setting_len;
} CalibDbV2_Bayer2dnr_V2_CalibPara_t;

typedef struct CalibDbV2_Bayer2dnr_V2_TuningPara_Setting_ISO_s {
    // M4_NUMBER_MARK_DESC("iso", "f32", M4_RANGE(50, 204800), "50", M4_DIGIT(1), "index2")
    float iso;

    // M4_BOOL_DESC("gauss_guide", "1")
    
# 62 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/bayer2dnr_head_v2.h" 3 4
   _Bool 
# 62 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/bayer2dnr_head_v2.h"
        gauss_guide;

    // M4_NUMBER_DESC("filter_strength", "f32", M4_RANGE(0, 16), "0.5", M4_DIGIT(2))
    float filter_strength;

    // M4_NUMBER_DESC("edgesofts", "f32", M4_RANGE(0, 16.0), "1.0", M4_DIGIT(2))
    float edgesofts;

    // M4_NUMBER_DESC("ratio", "f32", M4_RANGE(0, 1.0), "0.2", M4_DIGIT(2))
    float ratio;

    // M4_NUMBER_DESC("weight", "f32", M4_RANGE(0, 1.0), "1.0", M4_DIGIT(2))
    float weight;

} CalibDbV2_Bayer2dnr_V2_TuningPara_Setting_ISO_t;

typedef struct CalibDbV2_Bayer2dnr_V2_TuningPara_Setting_s {
    // M4_STRING_MARK_DESC("SNR_Mode", M4_SIZE(1,1), M4_RANGE(0, 64), "LSNR",M4_DYNAMIC(0), "index1")
    char *SNR_Mode;
    // M4_STRING_DESC("Sensor_Mode", M4_SIZE(1,1), M4_RANGE(0, 64), "lcg", M4_DYNAMIC(0))
    char *Sensor_Mode;
    // M4_STRUCT_LIST_DESC("Tuning_ISO", M4_SIZE_DYNAMIC, "double_index_list")
    CalibDbV2_Bayer2dnr_V2_TuningPara_Setting_ISO_t *Tuning_ISO;
    int Tuning_ISO_len;
} CalibDbV2_Bayer2dnr_V2_TuningPara_Setting_t;

typedef struct CalibDbV2_Bayer2dnr_V2_TuningPara_s {
    // M4_BOOL_DESC("enable", "1")
    
# 90 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/bayer2dnr_head_v2.h" 3 4
   _Bool 
# 90 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/bayer2dnr_head_v2.h"
        enable;
    // M4_STRUCT_LIST_DESC("Setting", M4_SIZE_DYNAMIC, "double_index_list")
    CalibDbV2_Bayer2dnr_V2_TuningPara_Setting_t *Setting;
    int Setting_len;
} CalibDbV2_Bayer2dnr_V2_TuningPara_t;



typedef struct CalibDbV2_Bayer2dnr_V2_s {
    // M4_STRING_DESC("Version", M4_SIZE(1,1), M4_RANGE(0, 64), "V2", M4_DYNAMIC(0))
    char *Version;
    // M4_STRUCT_DESC("CalibPara", "normal_ui_style")
    CalibDbV2_Bayer2dnr_V2_CalibPara_t CalibPara;
    // M4_STRUCT_DESC("Bayernr2D", "normal_ui_style")
    CalibDbV2_Bayer2dnr_V2_TuningPara_t TuningPara;
    // M4_STRUCT_DESC("Bayernr3D", "normal_ui_style")
} CalibDbV2_Bayer2dnr_V2_t;


# 36 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/bayertnr_head_v2.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/bayertnr_head_v2.h" 2



////////////////////////bayernr V2//////////////////////////////////////
typedef struct CalibDbV2_BayerTnr_V2_CalibPara_Setting_ISO_s {
    // M4_NUMBER_MARK_DESC("iso", "f32", M4_RANGE(50, 204800), "50", M4_DIGIT(1), "index2")
    float iso;

    // M4_ARRAY_DESC("lumapoint", "s32", M4_SIZE(1,16), M4_RANGE(0,65535), "0.0", M4_DIGIT(0), M4_DYNAMIC(0))
    int lumapoint[16];

    // M4_ARRAY_DESC("sigma", "s32", M4_SIZE(1,16), M4_RANGE(0,65535), "0.0", M4_DIGIT(0), M4_DYNAMIC(0))
    int sigma[16];

    // M4_ARRAY_DESC("lumapoint2", "s32", M4_SIZE(1,16), M4_RANGE(0,65535), "0.0", M4_DIGIT(0), M4_DYNAMIC(0))
    int lumapoint2[16];

    // M4_ARRAY_DESC("lo_sigma", "s32", M4_SIZE(1,16), M4_RANGE(0,65535), "0.0", M4_DIGIT(0), M4_DYNAMIC(0))
    int lo_sigma[16];

    // M4_ARRAY_DESC("hi_sigma", "s32", M4_SIZE(1,16), M4_RANGE(0,65535), "0.0", M4_DIGIT(0), M4_DYNAMIC(0))
    int hi_sigma[16];

} CalibDbV2_BayerTnr_V2_CalibPara_Setting_ISO_t;

typedef struct CalibDbV2_BayerTnr_V2_CalibPara_Setting_s {
    // M4_STRING_MARK_DESC("SNR_Mode", M4_SIZE(1,1), M4_RANGE(0, 64), "LSNR",M4_DYNAMIC(0), "index1")
    char *SNR_Mode;
    // M4_STRING_DESC("Sensor_Mode", M4_SIZE(1,1), M4_RANGE(0, 64), "lcg", M4_DYNAMIC(0))
    char *Sensor_Mode;
    // M4_STRUCT_LIST_DESC("Calib_ISO", M4_SIZE_DYNAMIC, "double_index_list")
    CalibDbV2_BayerTnr_V2_CalibPara_Setting_ISO_t *Calib_ISO;
    int Calib_ISO_len;

} CalibDbV2_BayerTnr_V2_CalibPara_Setting_t;

typedef struct CalibDbV2_BayerTnr_V2_CalibPara_s {
    // M4_STRUCT_LIST_DESC("Setting", M4_SIZE_DYNAMIC, "double_index_list")
    CalibDbV2_BayerTnr_V2_CalibPara_Setting_t *Setting;
    int Setting_len;
} CalibDbV2_BayerTnr_V2_CalibPara_t;


typedef struct CalibDbV2_BayerTnr_V2_TuningPara_Setting_ISO_s {
    // M4_NUMBER_MARK_DESC("iso", "f32", M4_RANGE(50, 204800), "50", M4_DIGIT(1), "index2")
    float iso;

    // M4_NUMBER_DESC("thumbds", "f32", M4_RANGE(0, 8), "8", M4_DIGIT(2))
    float thumbds;

    // M4_BOOL_DESC("lo_enable", "1")
    float lo_enable;

    // M4_BOOL_DESC("hi_enable", "1")
    float hi_enable;

    // M4_BOOL_DESC("lo_med_en", "1")
    float lo_med_en;
    // M4_BOOL_DESC("lo_gsbay_en", "1")
    float lo_gsbay_en;
    // M4_BOOL_DESC("lo_gslum_en", "1")
    float lo_gslum_en;
    // M4_BOOL_DESC("hi_med_en", "1")
    float hi_med_en;
    // M4_BOOL_DESC("hi_gslum_en", "1")
    float hi_gslum_en;

 // M4_NUMBER_DESC("hi_wgt_comp", "f32", M4_RANGE(0, 1), "0.16", M4_DIGIT(2))
    float hi_wgt_comp;

    // M4_NUMBER_DESC("clipwgt", "f32", M4_RANGE(0, 1), "0.03215", M4_DIGIT(5))
    float clipwgt;

    // M4_BOOL_DESC("global_pk_en", "1")
    float global_pk_en;
    // M4_NUMBER_DESC("global_pksq", "f32", M4_RANGE(0, 268435455), "1024", M4_DIGIT(0))
    float global_pksq;

 // M4_NUMBER_DESC("hidif_th", "f32", M4_RANGE(0, 65535), "32767", M4_DIGIT(0))
 float hidif_th;


    // M4_NUMBER_DESC("lo_filter_strength", "f32", M4_RANGE(0, 16), "1.0", M4_DIGIT(2))
    float lo_filter_strength;

    // M4_NUMBER_DESC("hi_filter_strength", "f32", M4_RANGE(0, 16), "1.0", M4_DIGIT(2))
    float hi_filter_strength;



    // M4_NUMBER_DESC("soft_threshold_ratio", "f32", M4_RANGE(0, 1.0), "0.0", M4_DIGIT(2))
    float soft_threshold_ratio;


} CalibDbV2_BayerTnr_V2_TuningPara_Setting_ISO_t;

typedef struct CalibDbV2_BayerTnr_V2_TuningPara_Setting_s {
    // M4_STRING_MARK_DESC("SNR_Mode", M4_SIZE(1,1), M4_RANGE(0, 64), "LSNR",M4_DYNAMIC(0), "index1")
    char *SNR_Mode;
    // M4_STRING_DESC("Sensor_Mode", M4_SIZE(1,1), M4_RANGE(0, 64), "lcg", M4_DYNAMIC(0))
    char *Sensor_Mode;
    // M4_STRUCT_LIST_DESC("Tuning_ISO", M4_SIZE_DYNAMIC, "double_index_list")
    CalibDbV2_BayerTnr_V2_TuningPara_Setting_ISO_t *Tuning_ISO;
    int Tuning_ISO_len;
} CalibDbV2_BayerTnr_V2_TuningPara_Setting_t;

typedef struct CalibDbV2_BayerTnr_V2_TuningPara_s {
    // M4_BOOL_DESC("enable", "1")
    
# 132 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/bayertnr_head_v2.h" 3 4
   _Bool 
# 132 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/bayertnr_head_v2.h"
        enable;
    // M4_STRUCT_LIST_DESC("Setting", M4_SIZE_DYNAMIC, "double_index_list")
    CalibDbV2_BayerTnr_V2_TuningPara_Setting_t *Setting;
    int Setting_len;
} CalibDbV2_BayerTnr_V2_TuningPara_t;


typedef struct CalibDbV2_BayerTnr_V2_s {
    // M4_STRING_DESC("Version", M4_SIZE(1,1), M4_RANGE(0, 64), "V2", M4_DYNAMIC(0))
    char *Version;
    // M4_STRUCT_DESC("CalibPara", "normal_ui_style")
    CalibDbV2_BayerTnr_V2_CalibPara_t CalibPara;
    // M4_STRUCT_DESC("Bayernr3D", "normal_ui_style")
    CalibDbV2_BayerTnr_V2_TuningPara_t TuningPara;
} CalibDbV2_BayerTnr_V2_t;


# 37 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/cac_head.h" 1
# 18 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/cac_head.h"
// clang-format off
typedef struct CalibDbV2_Cac_SettingByIso_s {
    // M4_NUMBER_DESC("iso", "u32", M4_RANGE(0,4294967295), "0", M4_DIGIT(0),M4_HIDE(0))
    uint32_t iso;
    // M4_NUMBER_DESC("bypass", "u8",M4_RANGE(0,1), "0", M4_DIGIT(0),M4_HIDE(0))
    uint8_t bypass;
    // M4_ARRAY_DESC("strength_table", "f32", M4_SIZE(0,22), M4_RANGE(0,1), "1.0", M4_DIGIT(1), M4_DYNAMIC(0))
    float strength_table[22];
} CalibDbV2_Cac_SettingByIso_t;

typedef struct CalibDbV2_Cac_TuningPara_s {
    // M4_STRUCT_LIST_DESC("SettingByIso", M4_SIZE_DYNAMIC, "double_index_list")
    CalibDbV2_Cac_SettingByIso_t* SettingByIso;
    int SettingByIso_len;
} CalibDbV2_Cac_TuningPara_t;

typedef struct CalibDbV2_Cac_SettingPara_s {
    // M4_NUMBER_DESC("enable", "u8", M4_RANGE(0,1), "0", M4_DIGIT(0),M4_HIDE(0))
    uint8_t enable;
    // M4_STRING_DESC("psf_path", M4_SIZE(1,1), M4_RANGE(0, 255), "/etc/iqfiles/cac", M4_DYNAMIC(0))
    char psf_path[255];
    // M4_NUMBER_DESC("psf_shift_bits", "u8", M4_RANGE(0,10), "2", M4_DIGIT(0),M4_HIDE(0))
    uint8_t psf_shift_bits;
    // M4_NUMBER_DESC("center_en", "u8", M4_RANGE(0,1), "0", M4_DIGIT(0),M4_HIDE(0))
    uint8_t center_en;
    // M4_NUMBER_DESC("center_x", "u16", M4_RANGE(0,65535), "0", M4_DIGIT(0),M4_HIDE(0))
    uint16_t center_x;
    // M4_NUMBER_DESC("center_y", "u16", M4_RANGE(0,65535), "0", M4_DIGIT(0),M4_HIDE(0))
    uint16_t center_y;
} CalibDbV2_Cac_SettingPara_t;

typedef struct CalibDbV2_Cac_s {
    // M4_STRUCT_DESC("SettingPara", "normal_ui_style")
    CalibDbV2_Cac_SettingPara_t SettingPara;
    // M4_STRUCT_DESC("TuningPara", "normal_ui_style")
    CalibDbV2_Cac_TuningPara_t TuningPara;
} CalibDbV2_Cac_t;
// clang-format on
# 38 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/ccm_head.h" 1
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
# 23 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/ccm_head.h"
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/ccm_head.h" 2


# 34 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/ccm_head.h"
/*****************************************************************************/
/**

 * @brief   Global ACCM calibration structure of isp2.0

 */
# 38 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/ccm_head.h"
/*****************************************************************************/

typedef struct CalibDbV2_Ccm_Gain_Sat_Curve_s {
    // M4_ARRAY_DESC("gains", "f32", M4_SIZE(1,4), M4_RANGE(0,256), "[4,8,16,32]", M4_DIGIT(0), M4_DYNAMIC(0))
    float gains[4];
    // M4_ARRAY_DESC("sat", "f32", M4_SIZE(1,4), M4_RANGE(0,100), "[100,100,90,50]", M4_DIGIT(1), M4_DYNAMIC(0))
    float sat[4];
}CalibDbV2_Ccm_Gain_Sat_Curve_t;

typedef struct CalibDbV2_Ccm_Gain_Scale_Curve_s {
    // M4_ARRAY_DESC("gain", "f32", M4_SIZE(1,9), M4_RANGE(0,256), "[1,2,4,8,16,32,64,128,256]", M4_DIGIT(0), M4_DYNAMIC(0))
    float gain[( 9 )];
    // M4_ARRAY_DESC("scale", "f32", M4_SIZE(1,9), M4_RANGE(0,1), "[1.00,0.80,0.80,0.90,1.00,1.00,1.00,1.00,1.00]", M4_DIGIT(2), M4_DYNAMIC(0))
    float scale[( 9 )];
} CalibDbV2_Ccm_Gain_Scale_Curve_t;

typedef struct CalibDbV2_Ccm_Ccm_Matrix_Para_s
{
    // M4_STRING_DESC("name", M4_SIZE(1,1), M4_RANGE(0, 25), "A_100",M4_DYNAMIC(0))
    char* name;
    // M4_STRING_DESC("illumination", M4_SIZE(1,1), M4_RANGE(0, 20), "A",M4_DYNAMIC(0))
    char* illumination;
    // M4_NUMBER_DESC("saturation", "f32", M4_RANGE(0.0, 100.0), "100.0", M4_DIGIT(1))
    float saturation;
    // M4_ARRAY_DESC("ccMatrix", "f32", M4_SIZE(3,3), M4_RANGE(-8,7.992), "[1.0000,0.0000,0.0000,0.0000,1.0000,0.0000,0.0000,0.0000,1.0000]", M4_DIGIT(4), M4_DYNAMIC(0))
    float ccMatrix[9];
    // M4_ARRAY_DESC("ccOffsets", "f32", M4_SIZE(1,3), M4_RANGE(-4095,4095), "[0.0,0.0,0.0]", M4_DIGIT(1), M4_DYNAMIC(0))
    float ccOffsets[3];
}CalibDbV2_Ccm_Ccm_Matrix_Para_t;

typedef struct CalibDbV2_Ccm_Accm_Cof_Para_s {
    // M4_STRING_DESC("name", M4_SIZE(1,1), M4_RANGE(0, 20), "A",M4_DYNAMIC(0))
    char * name;
    // M4_ARRAY_DESC("awbGain", "f32", M4_SIZE(1,2), M4_RANGE(0,5), "[1.0000,1.0000]", M4_DIGIT(4), M4_DYNAMIC(0))
    float awbGain[2];
    // M4_NUMBER_DESC("minDist", "f32", M4_RANGE(0.0, 4), "0", M4_DIGIT(4))
    float minDist;
    // M4_STRING_DESC("matrixUsed", M4_SIZE(1,2), M4_RANGE(0, 25), "A_100",M4_DYNAMIC(1))
    char** matrixUsed;
    int matrixUsed_len;
    // M4_ARRAY_TABLE_DESC("gain sat curve", "array_table_ui", M4_INDEX_DEFAULT)
    CalibDbV2_Ccm_Gain_Sat_Curve_t gain_sat_curve;
} CalibDbV2_Ccm_Accm_Cof_Para_t;

typedef struct CalibDbV2_Ccm_Luma_Ccm_Para_s {
    // M4_ARRAY_DESC("RGB2Y para", "f32", M4_SIZE(1,3), M4_RANGE(0,100), "[38 75 15]", M4_DIGIT(0),  M4_DYNAMIC(0), M4_HIDE(1))
    float rgb2y_para[3];
    // M4_NUMBER_DESC("bound pos bit", "f32", M4_RANGE(0, 10), "8", M4_DIGIT(0))
    float low_bound_pos_bit;// low & high y alpha adjust
    // M4_ARRAY_DESC("y alpha curve", "f32", M4_SIZE(1,17), M4_RANGE(0,1024), "[0,64,128,192,256,320,384,448,512,576,640,704,768,832,896,960,1024]", M4_DIGIT(0), M4_DYNAMIC(0))
    float y_alpha_curve[17];
    // M4_ARRAY_TABLE_DESC("gain alphaScale curve", "array_table_ui", M4_INDEX_DEFAULT)
    CalibDbV2_Ccm_Gain_Scale_Curve_t gain_alphaScale_curve;
} CalibDbV2_Ccm_Luma_Ccm_Para_t;

typedef struct CalibDbV2_Ccm_illu_estim_Para_s {
     // M4_BOOL_DESC("interp enable", "0")
    
# 95 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/ccm_head.h" 3 4
   _Bool 
# 95 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/ccm_head.h"
        interp_enable;
    // M4_STRING_DESC("default illu", M4_SIZE(1,1), M4_RANGE(0, 20), "D65",M4_DYNAMIC(0))
    char * default_illu;
    // M4_ARRAY_DESC("weightRB", "f32", M4_SIZE(1,2), M4_RANGE(0,3), "[1,1]", M4_DIGIT(4), M4_DYNAMIC(0))
    float weightRB[2];
    // M4_NUMBER_DESC("prob limit", "f32", M4_RANGE(0.0, 1), "0.2", M4_DIGIT(6))
    float prob_limit;
    // M4_NUMBER_DESC("frame num", "u8", M4_RANGE(1, 128), "8", M4_DIGIT(0))
    int frame_no;
} CalibDbV2_Ccm_illu_estim_Para_t;

typedef struct CalibDbV2_Ccm_Tuning_Para_s {
    // M4_BOOL_DESC("damp enable", "0")
    
# 108 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/ccm_head.h" 3 4
   _Bool 
# 108 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/ccm_head.h"
        damp_enable;
    // M4_STRUCT_DESC("illuminant estimation", "normal_ui_style")
    CalibDbV2_Ccm_illu_estim_Para_t illu_estim;
    // M4_STRUCT_LIST_DESC("aCcmCof", M4_SIZE_DYNAMIC, "normal_ui_style")
    CalibDbV2_Ccm_Accm_Cof_Para_t* aCcmCof;
    int aCcmCof_len;
    // M4_STRUCT_LIST_DESC("matrixAll",  M4_SIZE_DYNAMIC, "normal_ui_style")
    CalibDbV2_Ccm_Ccm_Matrix_Para_t* matrixAll;
    int matrixAll_len;
} CalibDbV2_Ccm_Tuning_Para_t;

typedef struct CalibDbV2_Ccm_Manual_Para_s {
    // M4_ARRAY_DESC("ccMatrix", "f32", M4_SIZE(3,3), M4_RANGE(-8,7.992), "[1.0000,0.0000,0.0000,0.0000,1.0000,0.0000,0.0000,0.0000,1.0000]", M4_DIGIT(4), M4_DYNAMIC(0))
    float ccMatrix[9];
    // M4_ARRAY_DESC("ccOffsets", "f32", M4_SIZE(1,3), M4_RANGE(-4095,4095), "[0.0,0.0,0.0]", M4_DIGIT(1), M4_DYNAMIC(0))
    float ccOffsets[3];
} CalibDbV2_Ccm_Manual_Para_t;

typedef enum CalibDbV2_Ccm_Op_Mode_t {
    CALIB_CCM_MODE_MANUAL = 1, /**< run manual lens shading correction */
    CALIB_CCM_MODE_AUTO = 2, /**< run auto lens shading correction */
} CalibDbV2_Ccm_Op_Mode_t;

typedef struct CalibDbV2_Ccm_Control_Para_t {
  // M4_BOOL_DESC("enable", "0")
  
# 133 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/ccm_head.h" 3 4
 _Bool 
# 133 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/ccm_head.h"
      enable;
  // M4_ENUM_DESC("mode", "CalibDbV2_Ccm_Op_Mode_t", "CALIB_CCM_MODE_AUTO");
  CalibDbV2_Ccm_Op_Mode_t mode;
   // M4_NUMBER_DESC("wbgain tolerance", "f32", M4_RANGE(0.0, 1), "0.1", M4_DIGIT(4))
  float wbgain_tolerance;
   // M4_NUMBER_DESC("gain tolerance", "f32", M4_RANGE(0.0, 1), "0.2", M4_DIGIT(4))
  float gain_tolerance;
} CalibDbV2_Ccm_Control_Para_t;

typedef struct CalibDbV2_Ccm_Para_V2_s {
    // M4_STRUCT_DESC("control", "normal_ui_style")
    CalibDbV2_Ccm_Control_Para_t control;
    // M4_STRUCT_DESC("lumaCCM", "normal_ui_style")
    CalibDbV2_Ccm_Luma_Ccm_Para_t lumaCCM;
    // M4_STRUCT_DESC("manualCCM", "normal_ui_style")
    CalibDbV2_Ccm_Manual_Para_t manualPara;
    // M4_STRUCT_DESC("autoCCM", "normal_ui_style")
    CalibDbV2_Ccm_Tuning_Para_t TuningPara;
} CalibDbV2_Ccm_Para_V2_t;



# 39 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/cnr_head_v2.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/cnr_head_v2.h" 2



///////////////////////////uvnr//////////////////////////////////////
typedef struct CalibDbV2_CNRV2_TuningPara_Setting_ISO_s {
    // M4_NUMBER_MARK_DESC("iso", "f32", M4_RANGE(50, 204800), "50", M4_DIGIT(1), "index2")
    float iso;

    // M4_BOOL_DESC("hf_bypass", "0")
    float hf_bypass;
    // M4_BOOL_DESC("lf_bypass", "0")
    float lf_bypass;

    // M4_NUMBER_DESC("global_gain", "f32", M4_RANGE(0, 64.0), "1.0", M4_DIGIT(2), M4_HIDE(0))
    float global_gain;
    // M4_NUMBER_DESC("global_gain_alpha", "f32", M4_RANGE(0, 1.0), "0.0", M4_DIGIT(2), M4_HIDE(0))
    float global_gain_alpha;
    // M4_NUMBER_DESC("local_gain_scale", "f32", M4_RANGE(0, 128.0), "1.0", M4_DIGIT(2), M4_HIDE(0))
    float local_gain_scale;

    // M4_ARRAY_DESC("gain_adj_strength_ratio", "f32", M4_SIZE(1,13), M4_RANGE(0,255), "1.0", M4_DIGIT(2), M4_DYNAMIC(0))
    float gain_adj_strength_ratio[13];

    // M4_NUMBER_DESC("color_sat_adj", "f32", M4_RANGE(1, 255.0), "40.0", M4_DIGIT(2))
    float color_sat_adj;
    // M4_NUMBER_DESC("color_sat_adj_alpha", "f32", M4_RANGE(0.0, 1.0), "0.8", M4_DIGIT(2))
    float color_sat_adj_alpha;

    // M4_NUMBER_DESC("hf_spikes_reducion_strength", "f32", M4_RANGE(0.0, 1.0), "0.5", M4_DIGIT(2))
    float hf_spikes_reducion_strength;
    // M4_NUMBER_DESC("hf_denoise_strength", "f32", M4_RANGE(1, 1023.0), "10", M4_DIGIT(2))
    float hf_denoise_strength;
    // M4_NUMBER_DESC("hf_color_sat", "f32", M4_RANGE(0.0, 8.0), "1.5", M4_DIGIT(2))
    float hf_color_sat;
    // M4_NUMBER_DESC("hf_denoise_alpha", "f32", M4_RANGE(0.0, 1.0), "0.0", M4_DIGIT(2))
    float hf_denoise_alpha;
    // M4_NUMBER_DESC("hf_bf_wgt_clip", "u32", M4_RANGE(0, 255), "0", M4_DIGIT(0), M4_HIDE(0))
    int hf_bf_wgt_clip;

    // M4_NUMBER_DESC("thumb_spikes_reducion_strength", "f32", M4_RANGE(0.0, 1.0), "0.2", M4_DIGIT(2))
    float thumb_spikes_reducion_strength;
    // M4_NUMBER_DESC("thumb_denoise_strength", "f32", M4_RANGE(1, 1023), "4.0", M4_DIGIT(2))
    float thumb_denoise_strength;
    // M4_NUMBER_DESC("thumb_color_sat", "f32", M4_RANGE(0.0, 8.0), "4.0", M4_DIGIT(2))
    float thumb_color_sat;


    // M4_NUMBER_DESC("lf_denoise_strength", "f32", M4_RANGE(1, 1023.0), "4.0", M4_DIGIT(2))
    float lf_denoise_strength;
    // M4_NUMBER_DESC("lf_color_sat", "f32", M4_RANGE(0.0, 8.0), "2.0", M4_DIGIT(2))
    float lf_color_sat;
    // M4_NUMBER_DESC("lf_denoise_alpha", "f32", M4_RANGE(0.0, 1.0), "1.0", M4_DIGIT(2))
    float lf_denoise_alpha;

} CalibDbV2_CNRV2_TuningPara_Setting_ISO_t;

typedef struct CalibDbV2_CNRV2_TuningPara_Setting_s {
    // M4_STRING_MARK_DESC("SNR_Mode", M4_SIZE(1,1), M4_RANGE(0, 64), "LSNR",M4_DYNAMIC(0), "index1")
    char *SNR_Mode;
    // M4_STRING_DESC("Sensor_Mode", M4_SIZE(1,1), M4_RANGE(0, 64), "lcg", M4_DYNAMIC(0))
    char *Sensor_Mode;
    // M4_STRUCT_LIST_DESC("Tuning_ISO", M4_SIZE_DYNAMIC, "double_index_list")
    CalibDbV2_CNRV2_TuningPara_Setting_ISO_t *Tuning_ISO;
    int Tuning_ISO_len;

} CalibDbV2_CNRV2_TuningPara_Setting_t;

typedef struct CalibDbV2_CNRV2_TuningPara_Kernel_s {
    // M4_ARRAY_DESC("kernel_5x5", "f32", M4_SIZE(1,5), M4_RANGE(0,1), "[1.0000,0.8825,0.7788,0.6065,0.3679]", M4_DIGIT(6), M4_DYNAMIC(0))
    float kernel_5x5[5];
} CalibDbV2_CNRV2_TuningPara_Kernel_t;


typedef struct CalibDbV2_CNRV2_TuningPara_s {
    // M4_BOOL_DESC("enable", "1")
    int enable;
    // M4_STRUCT_DESC("Kernel_Coeff", "normal_ui_style")
    CalibDbV2_CNRV2_TuningPara_Kernel_t Kernel_Coeff;
    // M4_STRUCT_LIST_DESC("Setting", M4_SIZE_DYNAMIC, "double_index_list")
    CalibDbV2_CNRV2_TuningPara_Setting_t *Setting;
    int Setting_len;
} CalibDbV2_CNRV2_TuningPara_t;


typedef struct CalibDbV2_CNRV2_s {
    // M4_STRING_DESC("Version", M4_SIZE(1,1), M4_RANGE(0, 64), "V1", M4_DYNAMIC(0))
    char *Version;
    // M4_STRUCT_DESC("TuningPara", "normal_ui_style")
    CalibDbV2_CNRV2_TuningPara_t TuningPara;
} CalibDbV2_CNRV2_t;


# 40 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/cproc_head.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/cproc_head.h" 2



// #define M4_BOOL_DESC(ALIAS, DEFAULT, HIDE)

// #define M4_ARRAY_DESC(ALIAS, TYPE, SIZE, RANGE, DEFAULT,DIGIT,DYNAMIC, HIDE)

// #define M4_NUMBER_DESC(ALIAS, TYPE, RANGE, DEFAULT,DIGIT, HIDE)

typedef struct __cproc_param {
    // M4_BOOL_DESC("enable", "1", 0)
    
# 35 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/cproc_head.h" 3 4
   _Bool 
# 35 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/cproc_head.h"
        enable;
    // M4_NUMBER_DESC("brightness", "u8", M4_RANGE(0,255), "128", M4_DIGIT(0), 0)
    unsigned char brightness;
    // M4_NUMBER_DESC("contrast", "u8", M4_RANGE(0,255), "128", M4_DIGIT(0), 0)
    unsigned char contrast;
    // M4_NUMBER_DESC("saturation", "u8", M4_RANGE(0,255), "128", M4_DIGIT(0), 0)
    unsigned char saturation;
    // M4_NUMBER_DESC("hue", "u8", M4_RANGE(0,255), "128", M4_DIGIT(0), 0)
    unsigned char hue;
} Cproc_Param_t;

typedef struct __cproc {
    // M4_STRUCT_DESC("CprocTuningPara", "normal_ui_style")
    Cproc_Param_t param;
} CalibDbV2_Cproc_t;


# 41 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/cpsl_head.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/cpsl_head.h" 2



typedef enum Cpsl_LightSource_e {
  INVALID = -1,
  LED = 1,
  IR = 2,
  MIX = 3, /*< led and ir mixture */
  MAX
} Cpsl_LightSource_t;

typedef struct CalibDbV2_Cpsl_Param_s {
  // M4_BOOL_DESC("enable", "0")
  
# 37 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/cpsl_head.h" 3 4
 _Bool 
# 37 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/cpsl_head.h"
      enable;
  // M4_ENUM_DESC("mode", "RKAiqOPMode_t", "RK_AIQ_OP_MODE_AUTO")
  RKAiqOPMode_t mode;
  // M4_BOOL_DESC("force_gray", "0")
  
# 41 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/cpsl_head.h" 3 4
 _Bool 
# 41 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/cpsl_head.h"
      force_gray;
  // M4_ENUM_DESC("light_src", "rk_aiq_cpsls_t", "LED")
  Cpsl_LightSource_t light_src;
  // M4_NUMBER_DESC("auto_adjust_sens", "f32", M4_RANGE(0.0,100.0), "50.0", M4_DIGIT(0))
  float auto_adjust_sens;
  // M4_NUMBER_DESC("auto_on2off_th", u32, M4_RANGE(0,65535), 3000, 0)
  uint32_t auto_on2off_th;
  // M4_NUMBER_DESC("auto_off2on_th", u32, M4_RANGE(0,65535), 100, 0)
  uint32_t auto_off2on_th;
  // M4_NUMBER_DESC("auto_sw_interval", u32, M4_RANGE(0,255), 60, 0)
  uint32_t auto_sw_interval;
  // M4_BOOL_DESC("manual_on", "0")
  
# 53 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/cpsl_head.h" 3 4
 _Bool 
# 53 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/cpsl_head.h"
      manual_on;
  // M4_NUMBER_DESC("manual_strength", "f32", M4_RANGE(0.0,100.0), "100.0", M4_DIGIT(2))
  float manual_strength;

} CalibDbV2_Cpsl_Param_t;

typedef struct CalibDbV2_Cpsl_s {
    // M4_STRUCT_DESC("param", "normal_ui_style")
    CalibDbV2_Cpsl_Param_t param;
} CalibDbV2_Cpsl_t;


# 42 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/debayer_head.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/debayer_head.h" 2



typedef struct __debayer_array {
    // M4_ARRAY_DESC("debayer_filter1", "u32", M4_SIZE(1,9),  M4_RANGE(08, 65536), "[50,100,200,400,800,1600,3200,6400,12800]", M4_DIGIT(0), M4_DYNAMIC(0), 0)
    int ISO[9];
    // M4_ARRAY_DESC("sharp_strength", "u8", M4_SIZE(1,9),  M4_RANGE(0, 255), "[4,4,4,4,4,4,4,4,4]", M4_DIGIT(0), M4_DYNAMIC(0), 0)
    unsigned char sharp_strength[9];
    // M4_ARRAY_DESC("debayer_hf_offset", "u16", M4_SIZE(1,9),  M4_RANGE(0, 255), "[1,1,1,1,1,1,1,1,1]", M4_DIGIT(0), M4_DYNAMIC(0), 0)
    unsigned short debayer_hf_offset[9];
}Debayer_Array_t;

typedef struct __Debayer_Param {
    // M4_BOOL_DESC("debayer_en", "1", 0, M4_HIDE(1))
    
# 38 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/debayer_head.h" 3 4
   _Bool 
# 38 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/debayer_head.h"
        debayer_en;
    // M4_ARRAY_DESC("debayer_filter1", "s8", M4_SIZE(1,5),  M4_RANGE(-128, 128), "[2,-6,0,6,-2]", M4_DIGIT(0), M4_DYNAMIC(0), 0)
    int debayer_filter1[5];
    // M4_ARRAY_DESC("debayer_filter2", "s8", M4_SIZE(1,5),  M4_RANGE(-128, 128), "[2,-4,4,-4,2]", M4_DIGIT(0), M4_DYNAMIC(0), 0)
    int debayer_filter2[5];
    // M4_NUMBER_DESC("debayer_gain_offset", "u8", M4_RANGE(0,128), "4", M4_DIGIT(0), 0)
    unsigned char debayer_gain_offset;
    // M4_NUMBER_DESC("debayer_offset", "u8", M4_RANGE(0,128), "1", M4_DIGIT(0), 0)
    unsigned char debayer_offset;
    // M4_BOOL_DESC("debayer_clip_en", "1", 0)
    
# 48 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/debayer_head.h" 3 4
   _Bool 
# 48 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/debayer_head.h"
        debayer_clip_en;
    // M4_BOOL_DESC("debayer_filter_g_en", "1", 0)
    
# 50 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/debayer_head.h" 3 4
   _Bool 
# 50 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/debayer_head.h"
        debayer_filter_g_en;
    // M4_BOOL_DESC("debayer_filter_c_en", "1", 0)
    
# 52 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/debayer_head.h" 3 4
   _Bool 
# 52 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/debayer_head.h"
        debayer_filter_c_en;
    // M4_NUMBER_DESC("debayer_thed0", "u8", M4_RANGE(0,128), "3", M4_DIGIT(0), 0)
    unsigned char debayer_thed0;
    // M4_NUMBER_DESC("debayer_thed1", "u8", M4_RANGE(0,128), "6", M4_DIGIT(0), 0)
    unsigned char debayer_thed1;
    // M4_NUMBER_DESC("debayer_dist_scale", "u8", M4_RANGE(0,128), "8", M4_DIGIT(0), 0)
    unsigned char debayer_dist_scale;
    // M4_NUMBER_DESC("debayer_cnr_strength", "u8", M4_RANGE(0,128), "5", M4_DIGIT(0), 0)
    unsigned char debayer_cnr_strength;
    // M4_NUMBER_DESC("debayer_shift_num", "u8", M4_RANGE(0,128), "2", M4_DIGIT(0), 0)
    unsigned char debayer_shift_num;
    // M4_ARRAY_TABLE_DESC("ISO_Params", "array_table_ui", "default")
    Debayer_Array_t array;
}Debayer_Param_t;

typedef struct __debayer {
    // M4_STRUCT_DESC("DebayerTuningPara", "normal_ui_style")
    Debayer_Param_t param;
} CalibDbV2_Debayer_t;


# 43 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/fec_head.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/fec_head.h" 2



typedef struct CalibDbV2_Fec_Param_s {
    unsigned char fec_en;
    char meshfile[256];
    int correct_level;
    double light_center[2]; // light center
    double coefficient[4]; // the distortion coefficient of the fisheye lens
} CalibDbV2_Fec_Param_t;

typedef struct CalibDbV2_FEC_s {
    // M4_STRUCT_DESC("param", "normal_ui_style")
    CalibDbV2_Fec_Param_t param;
} CalibDbV2_FEC_t;


# 44 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/ldch_head.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/ldch_head.h" 2



typedef struct CalibDbV2_Ldch_Param_s {
 // M4_BOOL_DESC("ldch_en", "0");
    unsigned char ldch_en;
 // M4_STRING_DESC("meshfile", M4_SIZE(1,1), M4_RANGE(0, 256), "default_meshfile", M4_DYNAMIC(0))
    char meshfile[256];
 // M4_NUMBER_DESC("correct_level", "u32", M4_RANGE(0,255), "255", M4_DIGIT(0))
    int correct_level;
 // M4_NUMBER_DESC("correct_level_max", "u32", M4_RANGE(0,255), "255", M4_DIGIT(0))
    int correct_level_max;
 // M4_ARRAY_DESC("light_center", "f64", M4_SIZE(1,2), M4_RANGE(-10000000000000000,10000000000000000), "0", M4_DIGIT(8), M4_DYNAMIC(0))
    double light_center[2]; // light center
 // M4_ARRAY_DESC("coefficient", "f64", M4_SIZE(1,4), M4_RANGE(-10000000000000000,10000000000000000), "0", M4_DIGIT(8), M4_DYNAMIC(0))
    double coefficient[4]; // the distortion coefficient of the fisheye lens
} CalibDbV2_Ldch_Param_t;

typedef struct CalibDbV2_LDCH_s {
    // M4_STRUCT_DESC("param", "normal_ui_style")
    CalibDbV2_Ldch_Param_t param;
} CalibDbV2_LDCH_t;


# 45 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/lut3d_head.h" 1
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
# 23 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/lut3d_head.h"
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/lut3d_head.h" 2



/*****************************************************************************/
/**

 * @brief   Global 3DLUT calibration structure of isp2.0

 */
# 31 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/lut3d_head.h"
/*****************************************************************************/
typedef struct CalibDbV2_Lut3D_Table_Para_s {
    // M4_ARRAY_DESC("Lut R", "u16", M4_SIZE(81,9), M4_RANGE(0,4096), "0", M4_DIGIT(0),  M4_DYNAMIC(0))
    unsigned short look_up_table_r[729];
    // M4_ARRAY_DESC("Lut G", "u16", M4_SIZE(81,9), M4_RANGE(0,4096), "0", M4_DIGIT(0),  M4_DYNAMIC(0))
    unsigned short look_up_table_g[729];
    // M4_ARRAY_DESC("Lut B", "u16", M4_SIZE(81,9), M4_RANGE(0,4096), "0", M4_DIGIT(0),  M4_DYNAMIC(0))
    unsigned short look_up_table_b[729];
}CalibDbV2_Lut3D_Table_Para_t;

typedef struct CalibDbV2_Lut3D_Gain_Alpha_Curve_s {
    // M4_ARRAY_DESC("gain", "f32", M4_SIZE(1,9), M4_RANGE(0,256), "[1,2,4,8,16,32,64,128,256]", M4_DIGIT(0), M4_DYNAMIC(0))
    float gain[9];
    // M4_ARRAY_DESC("Alpha", "f32", M4_SIZE(1,9), M4_RANGE(0,1), "1.00", M4_DIGIT(2), M4_DYNAMIC(0))
    float alpha[9];
} CalibDbV2_Lut3D_Gain_Alpha_Curve_t;

typedef struct CalibDbV2_Lut3D_LutPara_s {
    //  M4_STRING_DESC("name", M4_SIZE(1,1), M4_RANGE(0, 25), "Normal",M4_DYNAMIC(0))
    char *name;
     // M4_ARRAY_DESC("awbGain", "f32", M4_SIZE(1,2), M4_RANGE(0,5), "[1.0000,1.0000]", M4_DIGIT(4), M4_DYNAMIC(0))
    float awbGain[2];
    // M4_ARRAY_TABLE_DESC("gain-alpha curve", "array_table_ui", M4_INDEX_DEFAULT)
    CalibDbV2_Lut3D_Gain_Alpha_Curve_t gain_alpha;
    // M4_STRUCT_DESC("Table", "normal_ui_style")
    CalibDbV2_Lut3D_Table_Para_t Table;
}CalibDbV2_Lut3D_LutPara_t;

typedef struct CalibDbV2_Lut3D_Auto_Para_s {
    // M4_BOOL_DESC("damp enable", "0")
    
# 61 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/lut3d_head.h" 3 4
   _Bool 
# 61 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/lut3d_head.h"
        damp_en;
    // M4_STRUCT_LIST_DESC("lutAll", M4_SIZE_DYNAMIC, "normal_ui_style")
    CalibDbV2_Lut3D_LutPara_t* lutAll;
    int lutAll_len;
}CalibDbV2_Lut3D_Auto_Para_t;

typedef struct CalibDbV2_Lut3D_Manual_Para_s {
    // M4_STRUCT_DESC("Table", "normal_ui_style")
    CalibDbV2_Lut3D_Table_Para_t Table;
}CalibDbV2_Lut3D_Manual_Para_t;

typedef enum CalibDbV2_Lut3D_Op_Mode_s {
    CALIB_Lut3D_MODE_MANUAL = 1, /**< run manual 3dlut */
    CALIB_Lut3D_MODE_AUTO = 2, /**< run auto 3dlut */
} CalibDbV2_Lut3D_Op_Mode_t;

typedef struct CalibDbV2_Lut3D_Common_Para_s {
    // M4_BOOL_DESC("enable", "0")
    
# 79 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/lut3d_head.h" 3 4
   _Bool 
# 79 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/lut3d_head.h"
        enable;
    // M4_ENUM_DESC("mode", "CalibDbV2_Lut3D_Op_Mode_t", "CALIB_Lut3D_MODE_AUTO");
    CalibDbV2_Lut3D_Op_Mode_t mode;
   // M4_NUMBER_DESC("gain tolerance", "f32", M4_RANGE(0.0, 256), "0.2", M4_DIGIT(4))
  float gain_tolerance;
   // M4_NUMBER_DESC("wbgain tolerance", "f32", M4_RANGE(0.0, 4), "0.5", M4_DIGIT(4))
  float wbgain_tolerance;
}CalibDbV2_Lut3D_Common_Para_t;

typedef struct {
    // M4_STRUCT_DESC("common", "normal_ui_style")
    CalibDbV2_Lut3D_Common_Para_t common;
    // M4_STRUCT_DESC("manualLut3D", "normal_ui_style")
    CalibDbV2_Lut3D_Manual_Para_t MLut3D;
    // M4_STRUCT_DESC("autoLut3D", "normal_ui_style")
    CalibDbV2_Lut3D_Auto_Para_t ALut3D;
} CalibDbV2_Lut3D_Para_V2_t;


# 46 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/sharp_head_v4.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/sharp_head_v4.h" 2



///////////////////////////sharp//////////////////////////////////////

typedef struct CalibDbV2_SharpV4_TuningPara_Setting_ISO_Luma_s {
    // M4_ARRAY_DESC("luma_point", "f32", M4_SIZE(1,8), M4_RANGE(0,1024), "[0, 64, 128, 256, 384, 640, 896, 1024]", M4_DIGIT(1), M4_DYNAMIC(0))
    float luma_point[8];
    // M4_ARRAY_DESC("luma_sigma", "f32", M4_SIZE(1,8), M4_RANGE(0,1023), "[8, 10, 10, 12, 14, 12, 12, 10]", M4_DIGIT(1), M4_DYNAMIC(0))
    float luma_sigma[8];
    // M4_ARRAY_DESC("hf_clip", "f32", M4_SIZE(1,8), M4_RANGE(0,1023), "[10, 20, 30, 56, 56, 56, 56, 30]", M4_DIGIT(1), M4_DYNAMIC(0))
    float hf_clip[8];
    // M4_ARRAY_DESC("local_sharp_strength", "f32", M4_SIZE(1,8), M4_RANGE(0,1023), "[1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023]", M4_DIGIT(1), M4_DYNAMIC(0))
    float local_sharp_strength[8];
} CalibDbV2_SharpV4_TuningPara_Setting_ISO_Luma_t;

typedef struct CalibDbV2_SharpV4_TuningPara_Setting_ISO_kernel_s {

    // M4_ARRAY_DESC("prefilter_coeff", "f32", M4_SIZE(1,3), M4_RANGE(0,1), "[0.2042,0.1238,0.0751]", M4_DIGIT(4), M4_DYNAMIC(0))
    float prefilter_coeff[3];
    // M4_ARRAY_DESC("GaussianFilter_coeff", "f32", M4_SIZE(1,6), M4_RANGE(0,1), "[0.2042,0.1238,0.0751]", M4_DIGIT(4), M4_DYNAMIC(0))
    float GaussianFilter_coeff[6];
    // M4_ARRAY_DESC("hfBilateralFilter_coeff", "f32", M4_SIZE(1,3), M4_RANGE(0,1), "[0.2042,0.1238,0.0751]", M4_DIGIT(4), M4_DYNAMIC(0))
    float hfBilateralFilter_coeff[3];
} CalibDbV2_SharpV4_TuningPara_Setting_ISO_kernel_t;

typedef struct CalibDbV2_SharpV4_TuningPara_Setting_ISO_kernel_sigma_s {

    // M4_ARRAY_DESC("prefilter_sigma", "f32", M4_SIZE(1,1), M4_RANGE(0,100), "[1.0]", M4_DIGIT(2), M4_DYNAMIC(0))
    float prefilter_sigma;
    // M4_ARRAY_DESC("hfBilateralFilter_sigma", "f32", M4_SIZE(1,1), M4_RANGE(0,100), "[1.0]", M4_DIGIT(2), M4_DYNAMIC(0))
    float hfBilateralFilter_sigma;
    // M4_ARRAY_DESC("GaussianFilter_sigma", "f32", M4_SIZE(1,1), M4_RANGE(0,100), "[1.0]", M4_DIGIT(2), M4_DYNAMIC(0))
    float GaussianFilter_sigma;
    // M4_ARRAY_DESC("GaussianFilter_radius", "f32", M4_SIZE(1,1), M4_RANGE(1,2), "[2.0]", M4_DIGIT(0), M4_DYNAMIC(0))
    float GaussianFilter_radius;

} CalibDbV2_SharpV4_TuningPara_Setting_ISO_kernel_sigma_t;

typedef struct CalibDbV2_SharpV4_TuningPara_Setting_ISO_s {
    // M4_NUMBER_MARK_DESC("iso", "f32", M4_RANGE(50, 204800), "50", M4_DIGIT(1), "index2")
    float iso;

    // M4_NUMBER_DESC("pbf_gain", "f32", M4_RANGE(0.0, 2.0), "0.5", M4_DIGIT(2))
    float pbf_gain;
    // M4_NUMBER_DESC("pbf_ratio", "f32", M4_RANGE(0.0, 1.0), "0.5", M4_DIGIT(2))
    float pbf_ratio;
    // M4_NUMBER_DESC("pbf_add", "f32", M4_RANGE(0.0, 1023.0), "0.0", M4_DIGIT(2))
    float pbf_add;

    // M4_NUMBER_DESC("gaus_ratio", "f32", M4_RANGE(0.0, 1.0), "0.0", M4_DIGIT(2))
    float gaus_ratio;

    // M4_NUMBER_DESC("sharp_ratio", "f32", M4_RANGE(0.0, 32.0), "0.5", M4_DIGIT(2))
    float sharp_ratio;


    // M4_NUMBER_DESC("bf_gain", "f32", M4_RANGE(0.0, 2.0), "0.5", M4_DIGIT(2))
    float bf_gain;
    // M4_NUMBER_DESC("bf_ratio", "f32", M4_RANGE(0.0, 1.0), "0.5", M4_DIGIT(2))
    float bf_ratio;
    // M4_NUMBER_DESC("bf_add", "f32", M4_RANGE(0.0, 1023.0), "0.0", M4_DIGIT(2))
    float bf_add;

    // M4_ARRAY_TABLE_DESC("luma_para", "array_table_ui", "none")
    CalibDbV2_SharpV4_TuningPara_Setting_ISO_Luma_t luma_para;

    // M4_ARRAY_TABLE_DESC("kernel_para", "array_table_ui", "none")
    CalibDbV2_SharpV4_TuningPara_Setting_ISO_kernel_t kernel_para;

    // M4_ARRAY_TABLE_DESC("kernel_sigma", "array_table_ui", "none")
    CalibDbV2_SharpV4_TuningPara_Setting_ISO_kernel_sigma_t kernel_sigma;
} CalibDbV2_SharpV4_TuningPara_Setting_ISO_t;

typedef struct CalibDbV2_SharpV4_TuningPara_Setting_s {
    // M4_STRING_MARK_DESC("SNR_Mode", M4_SIZE(1,1), M4_RANGE(0, 64), "LSNR",M4_DYNAMIC(0), "index1")
    char *SNR_Mode;
    // M4_STRING_DESC("Sensor_Mode", M4_SIZE(1,1), M4_RANGE(0, 64), "lcg", M4_DYNAMIC(0))
    char *Sensor_Mode;
    // M4_STRUCT_LIST_DESC("Tuning_ISO", M4_SIZE_DYNAMIC, "double_index_list")
    CalibDbV2_SharpV4_TuningPara_Setting_ISO_t *Tuning_ISO;
    int Tuning_ISO_len;
} CalibDbV2_SharpV4_TuningPara_Setting_t;

typedef struct CalibDbV2_SharpV4_TuningPara_s {
    // M4_BOOL_DESC("enable", "1")
    
# 110 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/sharp_head_v4.h" 3 4
   _Bool 
# 110 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/sharp_head_v4.h"
        enable;

    // M4_BOOL_DESC("kernel_sigma_enable", "1")
    
# 113 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/sharp_head_v4.h" 3 4
   _Bool 
# 113 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/sharp_head_v4.h"
        kernel_sigma_enable;

    // M4_STRUCT_LIST_DESC("Setting", M4_SIZE_DYNAMIC, "double_index_list")
    CalibDbV2_SharpV4_TuningPara_Setting_t *Setting;
    int Setting_len;

} CalibDbV2_SharpV4_TuningPara_t;

typedef struct CalibDbV2_SharpV4_s {
    // M4_STRING_DESC("Version", M4_SIZE(1,1), M4_RANGE(0, 64), "V3", M4_DYNAMIC(0))
    char *Version;
    // M4_STRUCT_DESC("TuningPara", "normal_ui_style")
    CalibDbV2_SharpV4_TuningPara_t TuningPara;
} CalibDbV2_SharpV4_t;


# 47 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/thumbnails_head.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/thumbnails_head.h" 2



typedef struct rkaiq_thumbnails_config_s {
    // M4_NUMBER_DESC("owner_cookies", "u32", M4_RANGE(0,65535), "1", M4_DIGIT(0))
    uint32_t owner_cookies;
    // M4_NUMBER_DESC("stream_type", "u32", M4_RANGE(0,65535), "1", M4_DIGIT(0))
    uint32_t stream_type;
    // image_source after these nodes, 1 node per bit
    // M4_NUMBER_DESC("after_nodes", "u32", M4_RANGE(0,65535), "1", M4_DIGIT(0))
    uint64_t after_nodes;
    // image_source after the node, 1 node per bit
    // M4_NUMBER_DESC("after_nodes", "u32", M4_RANGE(0,65535), "1", M4_DIGIT(0))
    uint64_t before_node;
    // fourcc code
    // M4_ARRAY_DESC("format", "u8", M4_SIZE(1,4), M4_RANGE(0,100), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    char format[4];
    // M4_NUMBER_DESC("width_intfactor", "u32", M4_RANGE(0,65535), "1", M4_DIGIT(0))
    uint32_t width_intfactor;
    // M4_NUMBER_DESC("height_intfactor", "u32", M4_RANGE(0,65535), "1", M4_DIGIT(0))
    uint32_t height_intfactor;
    // M4_NUMBER_DESC("buffer_count", "s32", M4_RANGE(-65535,65535), "1", M4_DIGIT(0))
    int32_t buffer_count;
} rkaiq_thumbnails_config_t;

typedef struct CalibDbV2_Thumbnails_Param_s {
    // pointers to thumbnail info array
    // which contains format/width/height/stride
    // M4_STRUCT_LIST_DESC("thumbnail_configs", M4_SIZE(1,4), "normal_ui_style")
    rkaiq_thumbnails_config_t* thumbnail_configs;
    // total thumbnails count
    uint32_t thumbnail_configs_len;
} CalibDbV2_Thumbnails_Param_t;

typedef struct CalibDbV2_Thumbnails_s {
 // M4_STRUCT_DESC("param", "normal_ui_style")
    CalibDbV2_Thumbnails_Param_t param;
} CalibDbV2_Thumbnails_t;


# 48 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/ynr_head_v3.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/ynr_head_v3.h" 2



///////////////////////////ynr v1//////////////////////////////////////

typedef struct CalibDbV2_YnrV3_CalibPara_Setting_ISO_s {
    // M4_NUMBER_MARK_DESC("iso", "f32", M4_RANGE(50, 204800), "50", M4_DIGIT(1), "index2")
    float iso;
    // M4_ARRAY_DESC("sigma_curve", "f32", M4_SIZE(1,5), M4_RANGE(-65535.0, 65535), "0.0", M4_DIGIT(6), M4_DYNAMIC(0))
    double sigma_curve[5];
    // M4_NUMBER_DESC("ynr_lci", "f32", M4_RANGE(0.0, 2.0), "0.5", M4_DIGIT(3))
    float ynr_lci;
    // M4_NUMBER_DESC("ynr_hci", "f32", M4_RANGE(0.0, 2.0), "0.5", M4_DIGIT(3))
    float ynr_hci;

} CalibDbV2_YnrV3_CalibPara_Setting_ISO_t;

typedef struct CalibDbV2_YnrV3_CalibPara_Setting_s {
    // M4_STRING_MARK_DESC("SNR_Mode", M4_SIZE(1,1), M4_RANGE(0, 64), "LSNR",M4_DYNAMIC(0), "index1")
    char *SNR_Mode;
    // M4_STRING_DESC("Sensor_Mode", M4_SIZE(1,1), M4_RANGE(0, 64), "lcg", M4_DYNAMIC(0))
    char *Sensor_Mode;
    // M4_STRUCT_LIST_DESC("Calib_ISO", M4_SIZE_DYNAMIC, "double_index_list")
    CalibDbV2_YnrV3_CalibPara_Setting_ISO_t *Calib_ISO;
    int Calib_ISO_len;
} CalibDbV2_YnrV3_CalibPara_Setting_t;

typedef struct CalibDbV2_YnrV3_CalibPara_s {
    // M4_STRUCT_LIST_DESC("Setting", M4_SIZE_DYNAMIC, "double_index_list")
    CalibDbV2_YnrV3_CalibPara_Setting_t *Setting;
    int Setting_len;
} CalibDbV2_YnrV3_CalibPara_t;

typedef struct CalibDbV2_YnrV3_TuningPara_Setting_ISO_LumaParam_s {
    // M4_ARRAY_DESC("lo_lumaPoint", "f32", M4_SIZE(1,6), M4_RANGE(0,256), "[0,32,64,128,192,256]", M4_DIGIT(0), M4_DYNAMIC(0))
    float lo_lumaPoint[6];
    // M4_ARRAY_DESC("lo_ratio", "f32", M4_SIZE(1,6), M4_RANGE(0,2), "[1,1,1,1,1,1]", M4_DIGIT(2), M4_DYNAMIC(0))
    float lo_ratio[6];
    // M4_ARRAY_DESC("hi_lumaPoint", "f32", M4_SIZE(1,6), M4_RANGE(0,256), "[0,32,64,128,192,256]", M4_DIGIT(0), M4_DYNAMIC(0))
    float hi_lumaPoint[6];
    // M4_ARRAY_DESC("hi_ratio", "f32", M4_SIZE(1,6), M4_RANGE(0,2), "[1,1,1,1,1,1]", M4_DIGIT(2), M4_DYNAMIC(0))
    float hi_ratio[6];
} CalibDbV2_YnrV3_TuningPara_Setting_ISO_LumaParam_t;


typedef struct CalibDbV2_YnrV3_TuningPara_Setting_ISO_s {
    // M4_NUMBER_MARK_DESC("iso", "f32", M4_RANGE(50, 204800), "50", M4_DIGIT(1), "index2")
    float iso;

    // M4_BOOL_DESC("ynr_bft3x3_bypass", "0")
    float ynr_bft3x3_bypass;
    // M4_BOOL_DESC("ynr_lbft5x5_bypass", "0")
    float ynr_lbft5x5_bypass;
    // M4_BOOL_DESC("ynr_lgft3x3_bypass", "0")
    float ynr_lgft3x3_bypass;
    // M4_BOOL_DESC("ynr_flt1x1_bypass", "0")
    float ynr_flt1x1_bypass;
    // M4_BOOL_DESC("ynr_sft5x5_bypass", "0")
    float ynr_sft5x5_bypass;

    // M4_NUMBER_DESC("ynr_global_gain_alpha", "f32", M4_RANGE(0, 1.0), "0", M4_DIGIT(2))
    float ynr_global_gain_alpha;
    // M4_NUMBER_DESC("ynr_global_gain", "f32", M4_RANGE(0, 64), "1", M4_DIGIT(2))
    float ynr_global_gain;

    // M4_NUMBER_DESC("ynr_adjust_thresh", "f32", M4_RANGE(0, 1.0), "1", M4_DIGIT(2))
    float ynr_adjust_thresh;
    // M4_NUMBER_DESC("ynr_adjust_scale", "f32", M4_RANGE(0, 16), "1", M4_DIGIT(2))
    float ynr_adjust_scale;

    // M4_ARRAY_TABLE_DESC("lumaPara", "array_table_ui", "none")
    CalibDbV2_YnrV3_TuningPara_Setting_ISO_LumaParam_t lumaPara;

    // M4_NUMBER_DESC("low_bf1", "f32", M4_RANGE(0.1, 32), "0.5", M4_DIGIT(2))
    float low_bf1;
    // M4_NUMBER_DESC("low_bf2", "f32", M4_RANGE(0.1, 32), "0.5", M4_DIGIT(2))
    float low_bf2;

    // M4_NUMBER_DESC("low_thred_adj", "f32", M4_RANGE(0.0, 31.0), "0.25", M4_DIGIT(2))
    float low_thred_adj;
    // M4_NUMBER_DESC("low_peak_supress", "f32", M4_RANGE(0.0, 1.0), "0.5", M4_DIGIT(2))
    float low_peak_supress;
    // M4_NUMBER_DESC("low_edge_adj_thresh", "f32", M4_RANGE(0, 1023), "7", M4_DIGIT(2))
    float low_edge_adj_thresh;
    // M4_NUMBER_DESC("low_lbf_weight_thresh", "f32", M4_RANGE(0.0, 1.0), "0.25", M4_DIGIT(2))
    float low_lbf_weight_thresh;
    // M4_NUMBER_DESC("low_center_weight", "f32", M4_RANGE(0.0, 1.0), "0.5", M4_DIGIT(2))
    float low_center_weight;
    // M4_NUMBER_DESC("low_dist_adj", "f32", M4_RANGE(0.0, 127.0), "8.0", M4_DIGIT(2))
    float low_dist_adj;
    // M4_NUMBER_DESC("low_weight", "f32", M4_RANGE(0.0, 1.0), "0.5", M4_DIGIT(2))
    float low_weight;
    // M4_NUMBER_DESC("low_filt1_strength", "f32", M4_RANGE(0.0, 1.0), "0.7", M4_DIGIT(2))
    float low_filt1_strength;
    // M4_NUMBER_DESC("low_filt2_strength", "f32", M4_RANGE(0.0, 1.0), "0.85", M4_DIGIT(2))
    float low_filt2_strength;
    // M4_NUMBER_DESC("low_bi_weight", "f32", M4_RANGE(0.0, 1.0), "0.2", M4_DIGIT(2))
    float low_bi_weight;


    // M4_NUMBER_DESC("base_filter_weight1", "f32", M4_RANGE(0.0, 1.0), "0.28", M4_DIGIT(2))
    float base_filter_weight1;
    // M4_NUMBER_DESC("base_filter_weight2", "f32", M4_RANGE(0.0, 1.0), "0.46", M4_DIGIT(2))
    float base_filter_weight2;
    // M4_NUMBER_DESC("base_filter_weight3", "f32", M4_RANGE(0.0, 1.0), "0.26", M4_DIGIT(2))
    float base_filter_weight3;


    // M4_NUMBER_DESC("high_thred_adj", "f32", M4_RANGE(0.0, 31.0), "0.5", M4_DIGIT(2))
    float high_thred_adj;
    // M4_NUMBER_DESC("high_weight", "f32", M4_RANGE(0.0, 1.0), "0.5", M4_DIGIT(2))
    float high_weight;
    // M4_NUMBER_DESC("hi_min_adj", "f32", M4_RANGE(0.0, 1), "0.9", M4_DIGIT(2))
    float hi_min_adj;
    // M4_NUMBER_DESC("hi_edge_thed", "f32", M4_RANGE(0.0, 255.0), "100.0", M4_DIGIT(2))
    float hi_edge_thed;
    // M4_ARRAY_DESC("high_direction_weight", "f32", M4_SIZE(1,8), M4_RANGE(0,1.0), "[1  1  1  1  0.5  0.5  0.5  0.5]", M4_DIGIT(2), M4_DYNAMIC(0))
    float high_direction_weight[8];

    // M4_ARRAY_DESC("rnr_strength", "f32", M4_SIZE(1,17), M4_RANGE(0,16), "1.0", M4_DIGIT(3), M4_DYNAMIC(0))
    float rnr_strength[17];

} CalibDbV2_YnrV3_TuningPara_Setting_ISO_t;


typedef struct CalibDbV2_YnrV3_TuningPara_Setting_s {
    // M4_STRING_MARK_DESC("SNR_Mode", M4_SIZE(1,1), M4_RANGE(0, 64), "LSNR",M4_DYNAMIC(0), "index1")
    char *SNR_Mode;
    // M4_STRING_DESC("Sensor_Mode", M4_SIZE(1,1), M4_RANGE(0, 64), "lcg", M4_DYNAMIC(0))
    char *Sensor_Mode;
    // M4_STRUCT_LIST_DESC("Tuning_ISO", M4_SIZE_DYNAMIC, "double_index_list")
    CalibDbV2_YnrV3_TuningPara_Setting_ISO_t *Tuning_ISO;
    int Tuning_ISO_len;
} CalibDbV2_YnrV3_TuningPara_Setting_t;

typedef struct CalibDbV2_YnrV3_TuningPara_s {
    // M4_BOOL_DESC("enable", "1")
    
# 161 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/ynr_head_v3.h" 3 4
   _Bool 
# 161 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/ynr_head_v3.h"
        enable;
    // M4_STRUCT_LIST_DESC("Setting", M4_SIZE_DYNAMIC, "double_index_list")
    CalibDbV2_YnrV3_TuningPara_Setting_t *Setting;
    int Setting_len;
} CalibDbV2_YnrV3_TuningPara_t;


typedef struct CalibDbV2_YnrV3_s {
    // M4_STRING_DESC("Version", M4_SIZE(1,1), M4_RANGE(0, 64), "V2", M4_DYNAMIC(0))
    char *Version;
    // M4_STRUCT_DESC("CalibPara", "normal_ui_style")
    CalibDbV2_YnrV3_CalibPara_t CalibPara;
    // M4_STRUCT_DESC("TuningPara", "normal_ui_style")
    CalibDbV2_YnrV3_TuningPara_t TuningPara;
} CalibDbV2_YnrV3_t;


# 49 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 2



typedef struct CalibDbV2_ColorAsGrey_Param_s {
    // M4_BOOL_DESC("enable", "0")
    
# 54 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h" 3 4
   _Bool 
# 54 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbV2TypesIsp3x.h"
        enable;
} CalibDbV2_ColorAsGrey_Param_t;

typedef struct CalibDbV2_ColorAsGrey_s {
    // M4_STRUCT_DESC("param", "normal_ui_style")
    CalibDbV2_ColorAsGrey_Param_t param;
} CalibDbV2_ColorAsGrey_t;

typedef struct CalibDbV2_LUMA_DETECT_s {
    unsigned char luma_detect_en;
    int fixed_times;
    float mutation_threshold;
    float mutation_threshold_level2;
} CalibDbV2_LUMA_DETECT_t;

typedef struct CamCalibDbV2ContextIsp30_s {
    // M4_STRUCT_DESC("AEC", "normal_ui_style")
    CalibDb_Aec_ParaV2_t ae_calib;
    // M4_STRUCT_DESC("wb_v21", "normal_ui_style")
    CalibDbV2_Wb_Para_V21_t wb_v21;
    // M4_STRUCT_DESC("ablc_calib", "normal_ui_style")
    CalibDbV2_Ablc_t ablc_calib;
    // M4_STRUCT_DESC("ccm_calib", "normal_ui_style")
    CalibDbV2_Ccm_Para_V2_t ccm_calib;
    // M4_STRUCT_DESC("lut3d_calib", "normal_ui_style")
    CalibDbV2_Lut3D_Para_V2_t lut3d_calib;
    // M4_STRUCT_DESC("degamma", "curve_ui_type_A")
    CalibDbV2_Adegmma_t adegamma_calib;
    // M4_STRUCT_DESC("agic_calib_v21", "normal_ui_style")
    CalibDbV2_Gic_V21_t agic_calib_v21;
    // M4_STRUCT_DESC("debayer_calib", "normal_ui_style")
    CalibDbV2_Debayer_t debayer;
    // M4_STRUCT_DESC("Amerge_calib", "normal_ui_style")
    CalibDbV2_merge_V2_t amerge_calib_V2;
    // M4_STRUCT_DESC("Adrc_calib", "normal_ui_style")
    CalibDbV2_drc_V2_t adrc_calib_V2;
    // M4_STRUCT_DESC("agamma_calib", "normal_ui_style")
    CalibDbV2_gamma_V30_t agamma_calib_V30;
    // M4_STRUCT_DESC("adehaze_calib", "normal_ui_style")
    CalibDbV2_dehaze_V30_t adehaze_calib_v30;
    // M4_STRUCT_DESC("adpcc_calib", "normal_ui_style")
    CalibDbV2_Dpcc_t adpcc_calib;
    // M4_STRUCT_DESC("aldch", "normal_ui_style")
    CalibDbV2_LDCH_t aldch;
    // M4_STRUCT_DESC("cpsl", "normal_ui_style")
    CalibDbV2_Cpsl_t cpsl;
    // M4_STRUCT_DESC("cproc_calib", "normal_ui_style")
    CalibDbV2_Cproc_t cproc;
    // M4_STRUCT_DESC("aie_calib", "normal_ui_style")
    CalibDbV2_IE_t ie;
    // M4_STRUCT_DESC("colorAsGrey", "normal_ui_style")
    CalibDbV2_ColorAsGrey_t colorAsGrey;
    // M4_STRUCT_DESC("lsc_v2", "normal_ui_style")
    CalibDbV2_LSC_t lsc_v2;
    // M4_STRUCT_DESC("bayer2dnr_v2", "normal_ui_style")
    CalibDbV2_Bayer2dnr_V2_t bayer2dnr_v2;
    // M4_STRUCT_DESC("bayertnr_v2", "normal_ui_style")
    CalibDbV2_BayerTnr_V2_t bayertnr_v2;
    // M4_STRUCT_DESC("ynr_v3", "normal_ui_style")
    CalibDbV2_YnrV3_t ynr_v3;
    // M4_STRUCT_DESC("cnr_v2", "normal_ui_style")
    CalibDbV2_CNRV2_t cnr_v2;
    // M4_STRUCT_DESC("sharp_v4", "normal_ui_style")
    CalibDbV2_SharpV4_t sharp_v4;
    // M4_STRUCT_DESC("cac_calib", "normal_ui_style")
    CalibDbV2_Cac_t cac_calib;
    // M4_STRUCT_DESC("af_calib", "normal_ui_style")
    CalibDbV2_AFV30_t af_v30;
} CamCalibDbV2ContextIsp30_t;


# 31 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbTypesV2.h" 2

# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqUapitypes.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/uAPI2/rk_aiq_user_api_common.h" 1
# 10 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/uAPI2/rk_aiq_user_api_common.h"
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
# 22 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqUapitypes.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_uapi_head.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_head.h" 1
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
# 22 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_uapi_head.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/algos/ae/rk_aiq_types_ae_hw.h" 1
# 21 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/algos/ae/rk_aiq_types_ae_hw.h"
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
#pragma pack(1)
typedef struct window {
    uint16_t h_offs;
    uint16_t v_offs;
    uint16_t h_size;
    uint16_t v_size;
} window_t;
#pragma pack()


#pragma pack(1)
typedef struct rawaebig_meas_cfg {
    unsigned char rawae_sel;
    unsigned char wnd_num;
    unsigned char subwin_en[4];
    window_t win;
    window_t subwin[4];
} rawaebig_meas_cfg_t;
#pragma pack()

#pragma pack(1)
typedef struct rawaelite_meas_cfg {
    unsigned char rawae_sel;
    unsigned char wnd_num;
    window_t win;
} rawaelite_meas_cfg_t;
#pragma pack()

#pragma pack(1)
typedef struct yuvae_meas_cfg {
    unsigned char ysel;
    unsigned char wnd_num;
    unsigned char subwin_en[4];
    window_t win;
    window_t subwin[4];
} yuvae_meas_cfg_t;
#pragma pack()


#pragma pack(1)
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
#pragma pack()

#pragma pack(1)
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
#pragma pack()

#pragma pack(1)
typedef struct sihst_win_cfg {
    unsigned char data_sel;
    unsigned char waterline;
    unsigned char auto_stop;
    unsigned char mode;
    unsigned char stepsize;
    window_t win;
} sihst_win_cfg_t;
#pragma pack()

#pragma pack(1)
typedef struct sihst_cfg {
    unsigned char wnd_num;
    sihst_win_cfg_t win_cfg[1];
    unsigned char hist_weight[225];
} sihst_cfg_t;
#pragma pack()

/*NOTE: name of rawae/rawhist channel has been renamed!
   RawAE0 = RawAE lite,  addr=0x4500  <=> RawHIST0
   RawAE1 = RawAE big2, addr=0x4600 <=> RawHIST1
   RawAE2 = RawAE big3, addr=0x4700 <=> RawHIST2
   RawAE3 = RawAE big1, addr=0x4400, extra aebig <=> RawHIST3
*/
typedef struct rk_aiq_ae_meas_params_s {
    
# 145 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/algos/ae/rk_aiq_types_ae_hw.h" 3 4
   _Bool 
# 145 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/algos/ae/rk_aiq_types_ae_hw.h"
          ae_meas_en;
    
# 146 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/algos/ae/rk_aiq_types_ae_hw.h" 3 4
   _Bool 
# 146 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/algos/ae/rk_aiq_types_ae_hw.h"
          ae_meas_update;
    rawaelite_meas_cfg_t rawae0;
    rawaebig_meas_cfg_t rawae1;
    rawaebig_meas_cfg_t rawae2;
    rawaebig_meas_cfg_t rawae3;
    yuvae_meas_cfg_t yuvae;
} rk_aiq_ae_meas_params_t;

typedef struct rk_aiq_hist_meas_params_s {
    
# 155 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/algos/ae/rk_aiq_types_ae_hw.h" 3 4
   _Bool 
# 155 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/algos/ae/rk_aiq_types_ae_hw.h"
          hist_meas_en;
    
# 156 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/algos/ae/rk_aiq_types_ae_hw.h" 3 4
   _Bool 
# 156 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/algos/ae/rk_aiq_types_ae_hw.h"
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
    // M4_NUMBER_DESC("SNR", "u8", M4_RANGE(0,1), "0", M4_DIGIT(0),M4_HIDE(1))
    uint8_t SNR;
    // M4_NUMBER_DESC("DR", "u8", M4_RANGE(0,1), "0", M4_DIGIT(0),M4_HIDE(1))
    uint8_t DR;
    // M4_NUMBER_DESC("Sat", "u8", M4_RANGE(0,1), "0", M4_DIGIT(0),M4_HIDE(1))
    uint8_t Sat;
    // M4_NUMBER_DESC("SEN", "u8", M4_RANGE(0,1), "0", M4_DIGIT(0),M4_HIDE(1))
    uint8_t SEN;
} CISFeature_t;

typedef struct RkAiqExpRealParam_s {

    // M4_NUMBER_DESC("CISTime", "f32", M4_RANGE(0,1), "0", M4_DIGIT(6))
    float integration_time;

    // M4_NUMBER_DESC("CISGain", "f32", M4_RANGE(0,4096), "0", M4_DIGIT(3))
    float analog_gain;

    // M4_NUMBER_DESC("digital_gain", "f32", M4_RANGE(0,4096), "0", M4_DIGIT(3),M4_HIDE(1))
    float digital_gain;

    // M4_NUMBER_DESC("isp_dgain", "f32", M4_RANGE(0,256), "0", M4_DIGIT(3),M4_HIDE(1))
    float isp_dgain;

    // M4_NUMBER_DESC("iso", "s32", M4_RANGE(0,524288), "0", M4_DIGIT(0),M4_HIDE(1))
    int iso;

    // M4_NUMBER_DESC("DcgMode", "s32", M4_RANGE(-1,1), "0", M4_DIGIT(0))
    int dcg_mode;

    // M4_NUMBER_DESC("longfrm_mode", "s32", M4_RANGE(0,1), "0", M4_DIGIT(0),M4_HIDE(1))
    int longfrm_mode;
} RkAiqExpRealParam_t;

typedef struct RkAiqExpSensorParam_s {

    // M4_NUMBER_DESC("fine_integration_time", "u32", M4_RANGE(0,65535), "0", M4_DIGIT(0),M4_HIDE(1))
    unsigned int fine_integration_time;

    // M4_NUMBER_DESC("coarse_integration_time", "u32", M4_RANGE(0,65535), "0", M4_DIGIT(0),M4_HIDE(1))
    unsigned int coarse_integration_time;

    // M4_NUMBER_DESC("analog_gain_code_global", "u32", M4_RANGE(0,524288), "0", M4_DIGIT(0),M4_HIDE(1))
    unsigned int analog_gain_code_global;

    // M4_NUMBER_DESC("digital_gain_global", "u32", M4_RANGE(0,65535), "0", M4_DIGIT(0),M4_HIDE(1))
    unsigned int digital_gain_global;

    // M4_NUMBER_DESC("isp_digital_gain", "u32", M4_RANGE(0,65535), "0", M4_DIGIT(0),M4_HIDE(1))
    unsigned int isp_digital_gain;
} RkAiqExpSensorParam_t;


typedef struct RKAiqExpI2cParam_s {
    // M4_BOOL_DESC("bValid", "0",M4_HIDE(1))
    
# 290 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/algos/ae/rk_aiq_types_ae_hw.h" 3 4
   _Bool 
# 290 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/algos/ae/rk_aiq_types_ae_hw.h"
                  bValid;

    // M4_NUMBER_DESC("nNumRegs", "u32", M4_RANGE(0,65535), "0", M4_DIGIT(0),M4_HIDE(1))
    unsigned int nNumRegs;

    // M4_ARRAY_DESC("RegAddr", "u32", M4_SIZE(1,64), M4_RANGE(0,65535), "0", M4_DIGIT(0), M4_DYNAMIC(0),M4_HIDE(1))
    unsigned int RegAddr[64];

    // M4_ARRAY_DESC("AddrByteNum", "u32", M4_SIZE(1,64), M4_RANGE(0,65535), "0", M4_DIGIT(0), M4_DYNAMIC(0),M4_HIDE(1))
    unsigned int AddrByteNum[64];

    // M4_ARRAY_DESC("RegValue", "u32", M4_SIZE(1,64), M4_RANGE(0,65535), "0", M4_DIGIT(0), M4_DYNAMIC(0),M4_HIDE(1))
    unsigned int RegValue[64];

    // M4_ARRAY_DESC("ValueByteNum", "u32", M4_SIZE(1,64), M4_RANGE(0,65535), "0", M4_DIGIT(0), M4_DYNAMIC(0),M4_HIDE(1))
    unsigned int ValueByteNum[64];

    // M4_ARRAY_DESC("DelayFrames", "u32", M4_SIZE(1,64), M4_RANGE(0,65535), "0", M4_DIGIT(0), M4_DYNAMIC(0),M4_HIDE(1))
    unsigned int DelayFrames[64];

} RKAiqExpI2cParam_t;

typedef struct {
    // M4_STRUCT_DESC("RealPara", "normal_ui_style")
    RkAiqExpRealParam_t exp_real_params; //real value

    // M4_STRUCT_DESC("RegPara", "normal_ui_style",M4_HIDE(1))
    RkAiqExpSensorParam_t exp_sensor_params;//reg value
} RkAiqExpParamComb_t;

typedef struct {
    // M4_NUMBER_DESC("step", "s32", M4_RANGE(0,65535), "0", M4_DIGIT(0),M4_HIDE(1))
    int step;
    // M4_NUMBER_DESC("gain", "s32", M4_RANGE(0,65535), "0", M4_DIGIT(0),M4_HIDE(1))
    int gain;
    // M4_BOOL_DESC("update", "0",M4_HIDE(1))
    
# 326 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/algos/ae/rk_aiq_types_ae_hw.h" 3 4
   _Bool 
# 326 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/algos/ae/rk_aiq_types_ae_hw.h"
                  update;
} RkAiqPIrisParam_t;

typedef struct {
    // M4_NUMBER_DESC("pwmDuty", "s32", M4_RANGE(0,100), "0", M4_DIGIT(0),M4_HIDE(1))
    int pwmDuty; //percent value,range = 0-100
    // M4_BOOL_DESC("update", "0",M4_HIDE(1))
    
# 333 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/algos/ae/rk_aiq_types_ae_hw.h" 3 4
   _Bool 
# 333 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/algos/ae/rk_aiq_types_ae_hw.h"
              update;
} RkAiqDCIrisParam_t;

typedef struct {
    // M4_STRUCT_DESC("PIris", "normal_ui_style",M4_HIDE(1))
    RkAiqPIrisParam_t PIris;
    // M4_STRUCT_DESC("DCIris", "normal_ui_style",M4_HIDE(1))
    RkAiqDCIrisParam_t DCIris;
} RkAiqIrisParamComb_t;

typedef struct RKAiqAecExpInfo_s {

    // M4_STRUCT_DESC("LinearExp", "normal_ui_style")
    RkAiqExpParamComb_t LinearExp;

    // M4_STRUCT_LIST_DESC("HdrExp", M4_SIZE(1,3), "normal_ui_style")
    RkAiqExpParamComb_t HdrExp[3];

    // M4_STRUCT_DESC("Iris", "normal_ui_style",M4_HIDE(1))
    RkAiqIrisParamComb_t Iris;

    // M4_NUMBER_DESC("LineLengthPixels(hts)", "u16", M4_RANGE(0,65535), "0", M4_DIGIT(0))
    uint16_t line_length_pixels;

    // M4_NUMBER_DESC("FrameLengthLines(vts)", "u32", M4_RANGE(0,4294967296), "0", M4_DIGIT(0))
    uint32_t frame_length_lines;

    // M4_NUMBER_DESC("PixelClockFreqMhz", "f32", M4_RANGE(0,65535), "0", M4_DIGIT(2))
    float pixel_clock_freq_mhz;

    // M4_STRUCT_DESC("CISFeature_t", "normal_ui_style",M4_HIDE(1))
    CISFeature_t CISFeature;

    // M4_STRUCT_DESC("I2cPara", "normal_ui_style",M4_HIDE(1))
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
# 23 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_uapi_head.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/common/rk_aiq_comm.h" 1
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
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_uapi_head.h" 2
# 32 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_uapi_head.h"
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
    // M4_BOOL_DESC("ManualTimeEn", "1")
    
# 67 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_uapi_head.h" 3 4
   _Bool 
# 67 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_uapi_head.h"
        ManualTimeEn;
    // M4_BOOL_DESC("ManualGainEn", "1")
    
# 69 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_uapi_head.h" 3 4
   _Bool 
# 69 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_uapi_head.h"
        ManualGainEn;
    // M4_BOOL_DESC("ManualIspDgainEn", "1")
    
# 71 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_uapi_head.h" 3 4
   _Bool 
# 71 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_uapi_head.h"
        ManualIspDgainEn;
    // M4_NUMBER_DESC("TimeValue", "f32", M4_RANGE(0,1), "0.003", M4_DIGIT(6),M4_HIDE(0))
    float TimeValue; // unit: s = 10^6 us
    // M4_NUMBER_DESC("GainValue", "f32", M4_RANGE(1,4096), "1", M4_DIGIT(3),M4_HIDE(0))
    float GainValue;
    // M4_NUMBER_DESC("IspDGainValue", "f32", M4_RANGE(1,4096), "1", M4_DIGIT(3),M4_HIDE(0))
    float IspDGainValue;
} Uapi_LinMeAttrV2_uapi_t;

typedef struct Uapi_HdrMeAttrV2_uapi_s {
    // M4_BOOL_DESC("ManualTimeEn", "1")
    
# 82 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_uapi_head.h" 3 4
   _Bool 
# 82 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_uapi_head.h"
        ManualTimeEn;
    // M4_BOOL_DESC("ManualGainEn", "1")
    
# 84 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_uapi_head.h" 3 4
   _Bool 
# 84 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_uapi_head.h"
        ManualGainEn;
    // M4_BOOL_DESC("ManualIspDgainEn", "1")
    
# 86 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_uapi_head.h" 3 4
   _Bool 
# 86 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_uapi_head.h"
        ManualIspDgainEn;
    // M4_ARRAY_DESC("TimeValue", "f32", M4_SIZE(1,3), M4_RANGE(0,1), "0.003", M4_DIGIT(6), M4_DYNAMIC(0))
    float TimeValue[(3)];
    // M4_ARRAY_DESC("GainValue", "f32", M4_SIZE(1,3), M4_RANGE(1,4096), "1.0", M4_DIGIT(3), M4_DYNAMIC(0))
    float GainValue[(3)];
    // M4_ARRAY_DESC("IspDGainValue", "f32", M4_SIZE(1,3), M4_RANGE(1,4096), "1.0", M4_DIGIT(3), M4_DYNAMIC(0))
    float IspDGainValue[(3)];
} Uapi_HdrMeAttrV2_uapi_t;

typedef struct Uapi_MeAttrV2_uapi_s {
    // M4_STRUCT_DESC("LinearAE", "normal_ui_style")
    Uapi_LinMeAttrV2_uapi_t LinearAE;

    // M4_STRUCT_DESC("HdrAE", "normal_ui_style")
    Uapi_HdrMeAttrV2_uapi_t HdrAE;
} Uapi_MeAttrV2_uapi_t;

typedef struct Aec_uapi_advanced_attr_uapi_s {
    
# 104 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_uapi_head.h" 3 4
   _Bool 
# 104 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_uapi_head.h"
        enable;
    uint8_t GridWeights[15 * 15];
    uint8_t DayGridWeights[225];
    uint8_t NightGridWeights[225];
    
# 108 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_uapi_head.h" 3 4
   _Bool 
# 108 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_uapi_head.h"
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

    // M4_ENUM_DESC("OPMode", "RKAiqOPMode_uapi_t","RK_AIQ_OP_MODE_AUTO")
    RKAiqOPMode_t AecOpType;
    Cam15x15UCharMatrix_t GridWeights;
    Uapi_AeAttrV2_uapi_t stAuto;

    // M4_STRUCT_DESC("ManualCtrl", "normal_ui_style")
    Uapi_MeAttrV2_uapi_t stManual;

    Aec_uapi_advanced_attr_uapi_t stAdvanced;
} uapi_expsw_attr_t;

typedef struct uapi_expinfo {
    // M4_BOOL_DESC("IsConverged", "0",M4_HIDE(1))
    
# 134 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_uapi_head.h" 3 4
   _Bool 
# 134 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_uapi_head.h"
                     IsConverged;
    // M4_BOOL_DESC("IsExpMax", "0",M4_HIDE(1))
    
# 136 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_uapi_head.h" 3 4
   _Bool 
# 136 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/aec_uapi_head.h"
                     IsExpMax;
    // M4_NUMBER_DESC("LumaDeviation", "f32", M4_RANGE(-256,256), "0.0", M4_DIGIT(3),M4_HIDE(1))
    float LumaDeviation;
    // M4_ARRAY_DESC("HdrLumaDeviation", "f32", M4_SIZE(1,3), M4_RANGE(-256,256), "0.0", M4_DIGIT(3), M4_DYNAMIC(0), M4_HIDE(1))
    float HdrLumaDeviation[3];
    // M4_NUMBER_DESC("MeanLuma", "f32", M4_RANGE(0,256), "0.0", M4_DIGIT(2))
    float MeanLuma;
    // M4_ARRAY_DESC("HdrMeanLuma", "f32", M4_SIZE(1,3), M4_RANGE(0,256), "0.0", M4_DIGIT(2), M4_DYNAMIC(0))
    float HdrMeanLuma[3];
    // M4_NUMBER_DESC("GlobalEnvLux", "f32", M4_RANGE(0,65535), "0.0", M4_DIGIT(2),M4_HIDE(1))
    float GlobalEnvLux;
    // M4_ARRAY_DESC("BlockEnvLux", "f32", M4_SIZE(15,15), M4_RANGE(0,65535), "0.0", M4_DIGIT(2), M4_DYNAMIC(0), M4_HIDE(1))
    float BlockEnvLux[((25 > 225) ? 25 : 225)];
    // M4_STRUCT_DESC("CurExpInfo", "normal_ui_style");
    RKAiqAecExpInfo_t CurExpInfo;

    // M4_NUMBER_DESC("Piris", "u16", M4_RANGE(0,1024), "0", M4_DIGIT(0),M4_HIDE(1))
    unsigned short Piris;

    // M4_NUMBER_DESC("LinePeriodsPerField", "f32", M4_RANGE(0,65535), "0", M4_DIGIT(2),M4_HIDE(1))
    float LinePeriodsPerField;

    // M4_NUMBER_DESC("PixelPeriodsPerLine", "f32", M4_RANGE(0,65535), "0", M4_DIGIT(2),M4_HIDE(1))
    float PixelPeriodsPerLine;

    // M4_NUMBER_DESC("PixelClockFreqMHZ", "f32", M4_RANGE(0,4096), "0", M4_DIGIT(2),M4_HIDE(1))
    float PixelClockFreqMHZ;
} uapi_expinfo_t;

/*****************************************************************************/
/**
 * @brief   ISP AEC HW-Meas Stats Params
 */
/*****************************************************************************/

typedef struct uapi_rawhist_stats_s {
    // M4_ARRAY_DESC("bins", "u32", M4_SIZE(1,256), M4_RANGE(0,268435456), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned int bins[256];
} uapi_rawhist_stats_t;

typedef struct uapi_sihist_stats_s {
    // M4_ARRAY_DESC("bins", "u32", M4_SIZE(1,32), M4_RANGE(0,268435456), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned int bins[32];
} uapi_sihist_stats_t;

typedef struct uapi_rawae_big_stats_s {
    // M4_ARRAY_DESC("channelr_xy", "u16", M4_SIZE(1,225), M4_RANGE(0,1023), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    uint16_t channelr_xy[225];

    // M4_ARRAY_DESC("channelg_xy", "u16", M4_SIZE(1,225), M4_RANGE(0,4095), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    uint16_t channelg_xy[225];

    // M4_ARRAY_DESC("channelb_xy", "u16", M4_SIZE(1,225), M4_RANGE(0,1023), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    uint16_t channelb_xy[225];

    // M4_ARRAY_DESC("channely_xy", "u16", M4_SIZE(1,225), M4_RANGE(0,4095), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    uint16_t channely_xy[225]; //not HW!

    // M4_ARRAY_DESC("wndx_sumr", "u64", M4_SIZE(1,4), M4_RANGE(0,536870912), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    uint64_t wndx_sumr[4];

    // M4_ARRAY_DESC("wndx_sumg", "u64", M4_SIZE(1,4), M4_RANGE(0,4294967296), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    uint64_t wndx_sumg[4];

    // M4_ARRAY_DESC("wndx_sumb", "u64", M4_SIZE(1,4), M4_RANGE(0,536870912), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    uint64_t wndx_sumb[4];

    // M4_ARRAY_DESC("wndx_channelr", "u16", M4_SIZE(1,4), M4_RANGE(0,1023), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    uint16_t wndx_channelr[4]; //not HW!

    // M4_ARRAY_DESC("wndx_channelg", "u16", M4_SIZE(1,4), M4_RANGE(0,4095), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    uint16_t wndx_channelg[4]; //not HW!

    // M4_ARRAY_DESC("wndx_channelb", "u16", M4_SIZE(1,4), M4_RANGE(0,1023), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    uint16_t wndx_channelb[4]; //not HW!

    // M4_ARRAY_DESC("wndx_channely", "u16", M4_SIZE(1,4), M4_RANGE(0,4095), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    uint16_t wndx_channely[4]; //not HW!
} uapi_rawae_big_stats_t;

typedef struct uapi_rawae_lite_stat_s {
    // M4_ARRAY_DESC("channelr_xy", "u16", M4_SIZE(1,25), M4_RANGE(0,1023), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    uint16_t channelr_xy[25];

    // M4_ARRAY_DESC("channelg_xy", "u16", M4_SIZE(1,25), M4_RANGE(0,4095), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    uint16_t channelg_xy[25];

    // M4_ARRAY_DESC("channelb_xy", "u16", M4_SIZE(1,25), M4_RANGE(0,1023), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    uint16_t channelb_xy[25];

    // M4_ARRAY_DESC("channely_xy", "u16", M4_SIZE(1,25), M4_RANGE(0,4095), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    uint16_t channely_xy[25]; //not HW!
} uapi_rawae_lite_stat_t;

typedef struct uapi_yuvae_stats_s {
    // M4_ARRAY_DESC("channely_xy", "u64", M4_SIZE(1,4), M4_RANGE(0,4294967296), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    uint64_t ro_yuvae_sumy[4];

    // M4_ARRAY_DESC("channely_xy", "u8", M4_SIZE(1,225), M4_RANGE(0,255), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned char mean[225];
} uapi_yuvae_stats_t;

typedef struct uapi_raw_stats_s {
    //rawae
    // M4_STRUCT_DESC("rawae_big", "normal_ui_style")
    uapi_rawae_big_stats_t rawae_big;
    // M4_STRUCT_DESC("rawae_lite", "normal_ui_style")
    uapi_rawae_lite_stat_t rawae_lite;
    //rawhist
    // M4_STRUCT_DESC("rawhist_big", "normal_ui_style")
    uapi_rawhist_stats_t rawhist_big;
    // M4_STRUCT_DESC("rawhist_lite", "normal_ui_style")
    uapi_rawhist_stats_t rawhist_lite;
} uapi_raw_stats_t;

typedef struct uapi_ae_hwstats_s {
    // M4_STRUCT_LIST_DESC("chn", M4_SIZE(1,3), "normal_ui_style")
    uapi_raw_stats_t chn[3];
    // M4_STRUCT_DESC("extra", "normal_ui_style")
    uapi_raw_stats_t extra;
    // M4_STRUCT_DESC("yuvae", "normal_ui_style")
    uapi_yuvae_stats_t yuvae;
    // M4_STRUCT_DESC("sihist", "normal_ui_style")
    uapi_sihist_stats_t sihist;
} uapi_ae_hwstats_t;
# 23 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqUapitypes.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h" 1
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
# 28 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h"
typedef struct __uapi_wb_mode_t {
  // M4_ENUM_DESC("mode", "opMode_t", "OP_AUTO");
  opMode_t mode;
} uapi_wb_mode_t;

typedef struct __uapi_wb_gain_t {
  // M4_NUMBER_DESC("rgain", "f32", M4_RANGE(0,8), "0", M4_DIGIT(6))
    float rgain;
  // M4_NUMBER_DESC("grgain", "f32", M4_RANGE(0,8), "0", M4_DIGIT(6))
    float grgain;
  // M4_NUMBER_DESC("gbgain", "f32", M4_RANGE(0,8), "0", M4_DIGIT(6))
    float gbgain;
  // M4_NUMBER_DESC("bgain", "f32", M4_RANGE(0,8), "0", M4_DIGIT(6))
    float bgain;
} uapi_wb_gain_t;
# 53 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h"
//typedef struct stat3a_lightType_s
typedef struct rk_tool_awb_stat_wp_res_v201_s {
    // M4_NUMBER_DESC("WpNo", "s64", M4_RANGE(-9223372036854775808,9223372036854775807), "0", M4_DIGIT(0), M4_HIDE(0))
    long long WpNo;
    // M4_NUMBER_DESC("RgainValue", "s64", M4_RANGE(-9223372036854775808,9223372036854775807), "0", M4_DIGIT(0), M4_HIDE(0))
    long long RgainValue;
    // M4_NUMBER_DESC("BgainValue", "s64", M4_RANGE(-9223372036854775808,9223372036854775807), "0", M4_DIGIT(0), M4_HIDE(0))
    long long BgainValue;
} rk_tool_awb_stat_wp_res_v201_t;

typedef struct rk_tool_awb_stat_blk_res_v201_s {
    // M4_NUMBER_DESC("WpNo", "s64", M4_RANGE(-9223372036854775808,9223372036854775807), "0", M4_DIGIT(0), M4_HIDE(0))
    long long WpNo;
    // M4_NUMBER_DESC("Rvalue", "s64", M4_RANGE(-9223372036854775808,9223372036854775807), "0", M4_DIGIT(0), M4_HIDE(0))
    long long Rvalue;
    // M4_NUMBER_DESC("Gvalue", "s64", M4_RANGE(-9223372036854775808,9223372036854775807), "0", M4_DIGIT(0), M4_HIDE(0))
    long long Gvalue;
    // M4_NUMBER_DESC("Bvalue", "s64", M4_RANGE(-9223372036854775808,9223372036854775807), "0", M4_DIGIT(0), M4_HIDE(0))
    long long Bvalue;
} rk_tool_awb_stat_blk_res_v201_t;

typedef struct rk_tool_awb_stat_wp_res_light_v201_s {
    // M4_STRUCT_LIST_DESC("xYType", M4_SIZE(1,2), "normal_ui_style")
    rk_tool_awb_stat_wp_res_v201_t xYType[2];
} rk_tool_awb_stat_wp_res_light_v201_t;

typedef struct rk_tool_awb_stat_res2_v30_s {
    // M4_STRUCT_LIST_DESC("light", M4_SIZE(1,2), "normal_ui_style")
    rk_tool_awb_stat_wp_res_light_v201_t light[7];
    // M4_ARRAY_DESC("WpNo2", "s32", M4_SIZE(1,8), M4_RANGE(-2147483648,2147483647), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    int WpNo2[7];
    // M4_STRUCT_LIST_DESC("blockResult", M4_SIZE(1,255), "normal_ui_style")
    rk_tool_awb_stat_blk_res_v201_t blockResult[225];
    // M4_STRUCT_LIST_DESC("multiwindowLightResult", M4_SIZE(1,4), "normal_ui_style")
    rk_tool_awb_stat_wp_res_light_v201_t multiwindowLightResult[4];
    // M4_STRUCT_LIST_DESC("excWpRangeResult", M4_SIZE(1,4), "normal_ui_style")
    rk_tool_awb_stat_wp_res_v201_t excWpRangeResult[4];
    // M4_ARRAY_DESC("WpNoHist", "u32", M4_SIZE(1,8), M4_RANGE(0,4294967295), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned int WpNoHist[8];
} rk_tool_awb_stat_res2_v30_t;

typedef struct rk_tool_awb_measure_wp_res_fl_s {
    // M4_ARRAY_DESC("WpNo", "u32", M4_SIZE(1,1), M4_RANGE(0,4294967295), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned int WpNo;
    // M4_ARRAY_DESC("gain", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float gain[4];//mean rgain  value
    // M4_ARRAY_DESC("WpNoHist_2", "s32", M4_SIZE(1,8), M4_RANGE(-2147483648,2147483647), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    int WpNoHist_2[8]; //uselsess
} rk_tool_awb_measure_wp_res_fl_t;

typedef struct rk_tool_awb_measure_blk_res2_fl_s {
    // M4_ARRAY_DESC("WpNo", "u32", M4_SIZE(1,1), M4_RANGE(0,4294967295), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned int WpNo;
    // M4_ARRAY_DESC("gain", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float gain[4];//mean rgain  value
} rk_tool_awb_measure_blk_res2_fl_t;

typedef struct rk_tool_awb_measure_wp_res_light_fl_s {
    // M4_STRUCT_LIST_DESC("xYType", M4_SIZE(1,2), "normal_ui_style")
    rk_tool_awb_measure_wp_res_fl_t xYType[2];
} rk_tool_awb_measure_wp_res_light_fl_t;

typedef struct rk_tool_awb_measure_blk_res_fl_s {
    // M4_ARRAY_DESC("R", "f32", M4_SIZE(1,1), M4_RANGE(0,1), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float R;//mean r value and normalize to 0~1
    // M4_ARRAY_DESC("G", "f32", M4_SIZE(1,1), M4_RANGE(0,1), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float G;
    // M4_ARRAY_DESC("B", "f32", M4_SIZE(1,1), M4_RANGE(0,1), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float B;
} rk_tool_awb_measure_blk_res_fl_t;

typedef struct rk_tool_awb_effect_para1_s{
    // M4_ARRAY_DESC("hdrFrameChoose", "s32", M4_SIZE(1,1), M4_RANGE(-2147483648,2147483647), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    int hdrFrameChoose;
}rk_tool_awb_effect_para1_t;

typedef struct rk_tool_awb_stat_res_full_s {
    // M4_ARRAY_DESC("lightNum", "s32", M4_SIZE(1,1), M4_RANGE(-2147483648,2147483647), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    int lightNum;
    // M4_STRUCT_LIST_DESC("light", M4_SIZE(1,14), "normal_ui_style")
    rk_tool_awb_measure_wp_res_light_fl_t light[14];
    // M4_BOOL_DESC("lightWpResVaLidIll", "0")
    
# 135 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h" 3 4
   _Bool 
# 135 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h"
                                 lightWpResVaLidIll[14];//for time share
    // M4_BOOL_DESC("lightWpResVaLid", "0")
    
# 137 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h" 3 4
   _Bool 
# 137 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h"
                                 lightWpResVaLid;//for time share
    // M4_ARRAY_DESC("WpNo", "s32", M4_SIZE(1,2), M4_RANGE(-2147483648,2147483647), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    int WpNo[2];//for diff xy type
    // M4_ARRAY_DESC("WpNo2", "s32", M4_SIZE(1,14), M4_RANGE(-2147483648,2147483647), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    int WpNo2[14];//for diff illu
    // M4_BOOL_DESC("blkGwResValid", "0")
    
# 143 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h" 3 4
   _Bool 
# 143 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h"
                           blkGwResValid;
    // M4_BOOL_DESC("blkSgcResVaLid", "0")
    
# 145 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h" 3 4
   _Bool 
# 145 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h"
                           blkSgcResVaLid;
    // M4_STRUCT_LIST_DESC("blkSgcResult", M4_SIZE(1,225), "normal_ui_style")
    rk_tool_awb_measure_blk_res_fl_t blkSgcResult[225];
    // M4_BOOL_DESC("blkWpResVaLid", "0")
    
# 149 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h" 3 4
   _Bool 
# 149 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h"
                            blkWpResVaLid;
    // M4_STRUCT_LIST_DESC("blkWpResult", M4_SIZE(1,225), "normal_ui_style")
    rk_tool_awb_measure_blk_res2_fl_t blkWpResult[225];
    // M4_BOOL_DESC("excWpResValid", "0")
    
# 153 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h" 3 4
   _Bool 
# 153 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h"
        excWpResValid;
    // M4_STRUCT_LIST_DESC("excWpRangeResult", M4_SIZE(1,4), "normal_ui_style")
    rk_tool_awb_measure_wp_res_fl_t excWpRangeResult[4];
    // M4_STRUCT_DESC("extraLightResult", "normal_ui_style")
    rk_tool_awb_measure_wp_res_fl_t extraLightResult;
    // M4_ARRAY_DESC("WpNoHist", "u32", M4_SIZE(1,8), M4_RANGE(0,4294967295), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned int WpNoHist[8];
    // M4_STRUCT_DESC("effectHwPara", "normal_ui_style")
    rk_tool_awb_effect_para1_t effectHwPara;
} rk_tool_awb_stat_res_full_t;

typedef struct rk_tool_awb_smart_run_res_s{
    // M4_BOOL_DESC("blc1Stable", "0")
    
# 166 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h" 3 4
   _Bool 
# 166 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h"
        blc1Stable;
    // M4_BOOL_DESC("lvStable", "0")
    
# 168 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h" 3 4
   _Bool 
# 168 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h"
        lvStable;
    // M4_BOOL_DESC("wbgainStable", "0")
    
# 170 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h" 3 4
   _Bool 
# 170 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h"
        wbgainStable;
    // M4_BOOL_DESC("wpDiffweiStable", "0")
    
# 172 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h" 3 4
   _Bool 
# 172 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h"
        wpDiffweiStable;
    // M4_BOOL_DESC("statisticsStable", "0")
    
# 174 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h" 3 4
   _Bool 
# 174 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h"
        statisticsStable;
    // M4_BOOL_DESC("forceRunAwbFlag", "0")
    
# 176 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h" 3 4
   _Bool 
# 176 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h"
        forceRunAwbFlag;//update by api or prepare;
    // M4_BOOL_DESC("samrtRunAwbFlag2", "0")
    
# 178 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h" 3 4
   _Bool 
# 178 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h"
        samrtRunAwbFlag2;//update by above paras
    // M4_ARRAY_DESC("wbgainMean", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float wbgainMean[4];
    // M4_BOOL_DESC("algMethodStable", "0")
    
# 182 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h" 3 4
   _Bool 
# 182 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h"
        algMethodStable;
}rk_tool_awb_smart_run_res_t;

typedef struct rk_tool_awb_illInf_s {
    // M4_STRING_DESC("illName", M4_SIZE(1,100), M4_RANGE(-128, 127), "default", M4_DYNAMIC(0))
    char illName[100];
    // M4_ARRAY_DESC("gainValue", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float gainValue[4];
    // M4_ARRAY_DESC("prob_total", "f32", M4_SIZE(1,1), M4_RANGE(0,1), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float prob_total;
    // M4_ARRAY_DESC("prob_dis", "f32", M4_SIZE(1,1), M4_RANGE(0,1), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float prob_dis;
    // M4_ARRAY_DESC("prob_LV", "f32", M4_SIZE(1,1), M4_RANGE(0,1), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float prob_LV;
    // M4_ARRAY_DESC("spatialGainValue", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float spatialGainValue[4];
    // M4_ARRAY_DESC("prob_WPNO", "f32", M4_SIZE(1,1), M4_RANGE(0,1), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float prob_WPNO;
    // M4_ARRAY_DESC("gainValue", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float staWeight;
    // M4_ARRAY_DESC("xyType2Weight", "f32", M4_SIZE(1,1), M4_RANGE(0,1), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float xyType2Weight;
} rk_tool_awb_illInf_t;

typedef struct rk_tool_color_tempture_info_s {
    // M4_BOOL_DESC("valid", "0")
    
# 208 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h" 3 4
   _Bool 
# 208 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h"
        valid;
    // M4_NUMBER_DESC("CCT", "f32", M4_RANGE(0,10000), "5000", M4_DIGIT(0))
    float CCT;
    // M4_NUMBER_DESC("CCRI", "f32", M4_RANGE(-2,2), "0", M4_DIGIT(3))
    float CCRI;
} rk_tool_color_tempture_info_t;

typedef struct rk_tool_awb_strategy_result_s {
    // M4_BOOL_DESC("awbConverged", "0")
    
# 217 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h" 3 4
   _Bool 
# 217 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h"
        awbConverged;
    // M4_STRUCT_DESC("cctGloabl", "normal_ui_style")
    rk_tool_color_tempture_info_t cctGloabl;
    // M4_ARRAY_DESC("lightNum", "s32", M4_SIZE(1,1), M4_RANGE(-2147483648,2147483647), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    int lightNum;
    // M4_STRUCT_DESC("smartAwbRunRes", "normal_ui_style")
    rk_tool_awb_smart_run_res_t smartAwbRunRes;
    // M4_ARRAY_DESC("count", "u32", M4_SIZE(1,1), M4_RANGE(0,4294967295), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    unsigned int count;
    // M4_ARRAY_DESC("runInterval", "u32", M4_SIZE(1,1), M4_RANGE(0,4294967295), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    uint32_t runInterval;
    // M4_NUMBER_DESC("tolerance", "f32", M4_RANGE(0,10000), "5000", M4_DIGIT(0))
    float tolerance;
    // M4_ARRAY_DESC("dsRate", "u8", M4_SIZE(1,1), M4_RANGE(0,255), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    uint8_t dsRate; //downsample 8x8->Pixel(R,G,B)
    // M4_ARRAY_DESC("width_ds", "u32", M4_SIZE(1,1), M4_RANGE(0,4294967295), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    uint32_t width_ds;
    // M4_ARRAY_DESC("height_ds", "u32", M4_SIZE(1,1), M4_RANGE(0,4294967295), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    uint32_t height_ds;
    // M4_ARRAY_DESC("WPmode", "s32", M4_SIZE(1,1), M4_RANGE(-2147483648,2147483647), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    int WPmode;
    // M4_ARRAY_DESC("WPTotalNUM", "u32", M4_SIZE(1,1), M4_RANGE(0,4294967295), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    uint32_t WPTotalNUM;
    // M4_ARRAY_DESC("WPType", "s32", M4_SIZE(1,1), M4_RANGE(-2147483648,2147483647), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    int WPType;
    // M4_ARRAY_DESC("LVType", "s32", M4_SIZE(1,1), M4_RANGE(-2147483648,2147483647), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    int LVType;
    // M4_ARRAY_DESC("LVValue", "s32", M4_SIZE(1,1), M4_RANGE(-2147483648,2147483647), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    int LVValue;// 8bit/1x/1s
    // M4_NUMBER_DESC("fLVValue", "f32", M4_RANGE(0,255000), "5000", M4_DIGIT(0))
    float fLVValue;
    // M4_ARRAY_DESC("LVLevel", "s32", M4_SIZE(1,1), M4_RANGE(-2147483648,2147483647), "0", M4_DIGIT(0), M4_DYNAMIC(0))
    int LVLevel;
    // M4_STRUCT_LIST_DESC("illInf", M4_SIZE(1,14), "normal_ui_style")
    rk_tool_awb_illInf_t illInf[14];//information and measure result in different illuminations
    // M4_ARRAY_DESC("wbGainTepTp3", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float wbGainTepTp3[4];
    // M4_ARRAY_DESC("wbWeiTepTp3", "f32", M4_SIZE(1,1), M4_RANGE(0,100), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float wbWeiTepTp3;//temporal mix statistics
    // M4_ARRAY_DESC("xy_area_type", "u8", M4_SIZE(1,1), M4_RANGE(0,255), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    uint8_t xy_area_type; //enalbe type
    // M4_BOOL_DESC("spaGainEqu2Tem", "0")
    
# 259 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h" 3 4
   _Bool 
# 259 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h"
        spaGainEqu2Tem;
    // M4_BOOL_DESC("sgcGainEqu2Tem", "0")
    
# 261 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h" 3 4
   _Bool 
# 261 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h"
        sgcGainEqu2Tem;
    // M4_ARRAY_DESC("wbGainType3", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float wbGainType3[4];
    // M4_ARRAY_DESC("wbGainType1", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float wbGainType1[4];
    // M4_ARRAY_DESC("wbWeightType3", "f32", M4_SIZE(1,1), M4_RANGE(0,100), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float wbWeightType3;
    // M4_ARRAY_DESC("wbGainTep", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float wbGainTep[4];//night gain
    // M4_ARRAY_DESC("wbGainSgc", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float wbGainSgc[4];
    // M4_ARRAY_DESC("wbWeightSgc", "f32", M4_SIZE(1,1), M4_RANGE(0,100), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float wbWeightSgc;
    // M4_ARRAY_DESC("wbGainSpa", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float wbGainSpa[4];//day gain
    // M4_ARRAY_DESC("wbWeightSpa", "f32", M4_SIZE(1,1), M4_RANGE(0,100), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float wbWeightSpa;
    // M4_ARRAY_DESC("varianceLuma", "f32", M4_SIZE(1,1), M4_RANGE(0,2147483647), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float varianceLuma;
    // M4_ARRAY_DESC("wbGainDampFactor", "f32", M4_SIZE(1,1), M4_RANGE(0,1), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float wbGainDampFactor;
    // M4_BOOL_DESC("clipEnalbe", "0")
    
# 283 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h" 3 4
   _Bool 
# 283 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h"
        clipEnalbe;
    // M4_BOOL_DESC("updateFlag", "0")
    
# 285 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h" 3 4
   _Bool 
# 285 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/awb_uapi_head.h"
        updateFlag;
    // M4_ARRAY_DESC("wbGainIntpStrategy", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float wbGainIntpStrategy[4];//gain by interpartition strategy
    // M4_ARRAY_DESC("wbGainClip", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float wbGainClip[4];//gain by clip
    // M4_ARRAY_DESC("wbGainCaga", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float wbGainCaga[4];//gain by  chromatic adatptation gain adjust
    // M4_ARRAY_DESC("wbGainAdjust", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float wbGainAdjust[4];//gain by color temperature shift
    // M4_ARRAY_DESC("wbGainOffset", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float wbGainOffset[4];//gain by gain shift
    // M4_ARRAY_DESC("wbGainSmooth", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float wbGainSmooth[4];//gain by smooth factor
    // M4_ARRAY_DESC("stat3aAwbLastGainOut", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float stat3aAwbLastGainOut[4];//final gain of last frame
    // M4_ARRAY_DESC("stat3aAwbGainOut", "f32", M4_SIZE(1,4), M4_RANGE(0,8), "1", M4_DIGIT(4), M4_DYNAMIC(0))
    float stat3aAwbGainOut[4];// final gain
    // M4_ARRAY_DESC("algMethod", "s32", M4_SIZE(1,1), M4_RANGE(0,100), "1", M4_DIGIT(0), M4_DYNAMIC(0))
    int algMethod;
} rk_tool_awb_strategy_result_t;

typedef struct __uapi_wb_log_info_t {
    // M4_STRUCT_DESC("awb_stat", "normal_ui_style")
    rk_tool_awb_stat_res2_v30_t awb_stat;
    // M4_STRUCT_DESC("awb_stat_algo", "normal_ui_style")
    rk_tool_awb_stat_res_full_t awb_stat_algo;
    // M4_STRUCT_DESC("awb_strategy_result", "normal_ui_style")
    rk_tool_awb_strategy_result_t awb_strategy_result;
} uapi_wb_log_info_t;

typedef struct __uapi_wb_log_t {
    // M4_STRUCT_DESC("uapi_wb_log_info_t", "normal_ui_style")
    uapi_wb_log_info_t info;
} uapi_wb_log_t;
# 24 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqUapitypes.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/amerge_uapi_head.h" 1
# 10 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/amerge_uapi_head.h"
typedef struct uapiMergeCurrCtlData_s
{
  // M4_NUMBER_DESC("Envlv", "f32", M4_RANGE(0,8), "0", M4_DIGIT(6))
  float Envlv;
  // M4_NUMBER_DESC("MoveCoef", "f32", M4_RANGE(0,8), "0", M4_DIGIT(6))
  float MoveCoef;
} uapiMergeCurrCtlData_t;
# 25 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqUapitypes.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/atmo_uapi_head.h" 1
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




# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/atmo_head.h" 1
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
# 22 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/atmo_uapi_head.h" 2

typedef struct uapiTmoCurrCtlData_s
{
  // M4_ENUM_DESC("GlobalLumaMode", "GlobalLumaMode_t", "GLOBALLUMAMODE_ENVLV")
  GlobalLumaMode_t GlobalLumaMode;
  // M4_ENUM_DESC("Mode", "DetailsHighLightMode_t", "DETAILSHIGHLIGHTMODE_ENVLV")
  DetailsHighLightMode_t DetailsHighLightMode;
  // M4_ENUM_DESC("DetailsLowLightMode", "DetailsLowLightMode_t", "DETAILSLOWLIGHTMODE_ISO")
  DetailsLowLightMode_t DetailsLowLightMode;
  // M4_ENUM_DESC("GlobalTmoMode", "TmoTypeMode_t", "TMOTYPEMODE_DYNAMICRANGE")
  TmoTypeMode_t GlobalTmoMode;
  // M4_ENUM_DESC("LocalTMOMode", "TmoTypeMode_t", "TMOTYPEMODE_DYNAMICRANGE")
  TmoTypeMode_t LocalTMOMode;
  float Envlv;
  float ISO;
  float OEPdf;
  float FocusLuma;
  float DarkPdf;
  float DynamicRange;
} uapiTmoCurrCtlData_t;
# 26 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqUapitypes.h" 2
# 1 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/adrc_uapi_head.h" 1
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
    // M4_NUMBER_DESC("EnvLv", "f32", M4_RANGE(0,1), "0", M4_DIGIT(6))
    float EnvLv;
} DrcInfo_t;
# 27 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqUapitypes.h" 2






typedef struct __ae_uapi {
    // M4_STRUCT_DESC("expsw_attr", "normal_ui_style")
    uapi_expsw_attr_t expsw_attr;
    // M4_STRUCT_DESC("QueryExpInfo", "normal_ui_style")
    uapi_expinfo_t expinfo;
} ae_uapi_t;

typedef struct __awb_uapi {
    // M4_STRUCT_DESC("mode", "normal_ui_style")
    uapi_wb_mode_t mode;
    // M4_STRUCT_DESC("wbgain", "normal_ui_style")
    uapi_wb_gain_t wbgain;
} awb_uapi_t;

typedef struct __amerge_uapi {
    // M4_STRUCT_DESC("ctldata", "normal_ui_style")
    uapiMergeCurrCtlData_t ctldata;
} amerge_uapi_t;

typedef struct __atmo_uapi {
    // M4_STRUCT_DESC("ctldata", "normal_ui_style")
    uapiTmoCurrCtlData_t ctldata;
} atmo_uapi_t;

typedef struct __adrc_uapi {
    // M4_STRUCT_DESC("drc", "normal_ui_style")
    DrcInfo_t drc;
} adrc_uapi_t;

typedef struct __aiq_scene {
    // M4_STRING_DESC("main_scene", M4_SIZE(1,1), M4_RANGE(0, 32), "normal", M4_DYNAMIC(0))
    char* main_scene;
    // M4_STRING_DESC("sub_scene", M4_SIZE(1,1), M4_RANGE(0, 32), "day", M4_DYNAMIC(0))
    char* sub_scene;
} aiq_scene_t;

typedef struct __work_mode {
    // M4_ENUM_DESC("mode", "rk_aiq_working_mode_t", "RK_AIQ_WORKING_MODE_NORMAL");
    rk_aiq_working_mode_t mode;
} work_mode_t;

typedef struct __aiq_sysctl_desc {
    // M4_STRUCT_DESC("scene", "normal_ui_style")
    aiq_scene_t scene;
    // M4_STRUCT_DESC("work_mode", "normal_ui_style")
    work_mode_t work_mode;
} RkaiqSysCtl_t;

typedef struct __aiq_measure_info {
    // M4_STRUCT_DESC("ae_hwstats", "normal_ui_style")
    uapi_ae_hwstats_t ae_hwstats;
    // M4_STRUCT_DESC("wb_log", "normal_ui_style")
    uapi_wb_log_t wb_log;
} aiq_measure_info_t;

typedef struct __aiq_uapi_t {
    // M4_STRUCT_DESC("ae_uapi", "normal_ui_style")
    ae_uapi_t ae_uapi;
    // M4_STRUCT_DESC("awb_uapi", "normal_ui_style")
    awb_uapi_t awb_uapi;
    // M4_STRUCT_DESC("amerge_uapi", "normal_ui_style")
    amerge_uapi_t amerge_uapi;




    // M4_STRUCT_DESC("adrc_uapi", "normal_ui_style")
    adrc_uapi_t adrc_uapi;

    // M4_STRUCT_DESC("SystemCtl", "normal_ui_style")
    RkaiqSysCtl_t system;
    // M4_STRUCT_DESC("measure_info", "normal_ui_style")
    aiq_measure_info_t measure_info;
} RkaiqUapi_t;
# 33 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbTypesV2.h" 2



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
# 168 "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/include/iq_parser_v2/RkAiqCalibDbTypesV2.h"
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
    // M4_STRUCT_DESC("SensorInfo", "normal_ui_style")
    CalibDb_Sensor_ParaV2_t sensor_calib;
    // M4_STRUCT_DESC("MoudleInfo", "normal_ui_style")
    CalibDb_Module_ParaV2_t module_calib;
    // 'main_scene' means Scene list of A,B,C ...,
    CamCalibMainSceneList_t* main_scene;
    int main_scene_len;
    RkaiqUapi_t* uapi;
    int uapi_len;
    // M4_STRUCT_DESC("SysStaticCfg", "normal_ui_style")
    CalibDb_SysStaticCfg_ParaV2_t sys_static_cfg;
} CamCalibDbProj_t;

/*NOTE: SHOULD be defined next to CamCalibDbProj_t */
/*The storage struct of file camgroup.json */
typedef struct CamCalibDbCamgroup_s {
    //test
    int group_awb;
} CamCalibDbCamgroup_t;


