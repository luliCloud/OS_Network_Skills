#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int m = board.size(), n = board[0].size();
        for (int i = 0; i < n; i++) {
            if (board[0][i] == 'O') {
                floodEdge(board, 0, i);
            }
            if (board[m - 1][i] == 'O') {
                floodEdge(board, m - 1, i);
            }
        }
        for (int i = 0; i < m; i++) {
            if (board[i][0] == 'O') {
                floodEdge(board, i, 0);
            }
            if (board[i][n - 1] == 'O') {
                floodEdge(board, i, n - 1);
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O') {
                    flood(board, i, j);
                }
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'I') {
                    board[i][j] = 'O';
                }
            }
        }
    }

    void floodEdge(vector<vector<char>>& board, int i, int j) {
        if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size()) {
            return;
        }

        if (board[i][j] == 'I' || board[i][j] == 'X') {
            return;
        }

        board[i][j] = 'I';
        floodEdge(board, i + 1, j);
        floodEdge(board, i - 1, j);
        floodEdge(board, i, j + 1);
        floodEdge(board, i, j - 1);
    }

    void flood(vector<vector<char>>& board, int i, int j) {
        if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size()) {
            return;
        }

        if (board[i][j] == 'I' || board[i][j] == 'X') {
            return;
        }

        board[i][j] = 'X';
        flood(board, i + 1, j);
        flood(board, i - 1, j);
        flood(board, i, j + 1);
        flood(board, i, j - 1);
    }
};

int main() {
    vector<vector<char>> board = {
        {'X','O','X','O','X','O'},
        {'O','X','O','X','O','X'},
        {'X','O','X','O','X','O'},
        {'O','X','O','X','O','X'}
    };

    Solution s;
    s.solve(board);
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
/**
 * valgrind --tool=callgrind ./a.out
 * (base) lu@lu-t3610:~/greenpear/OSlearn/valgrind$ callgrind_annotate callgrind.out.61568 
--------------------------------------------------------------------------------
Profile data file 'callgrind.out.61568' (creator: callgrind-3.18.1)
--------------------------------------------------------------------------------
I1 cache: // Instruction Level 1 cahce 一级指令缓存
D1 cache: // Data level 1 cache
LL cache: // Last level cache
Timerange: Basic block 0 - 375746
Trigger: Program termination
Profiled target:  ./a.out (PID 61568, part 1)
Events recorded:  Ir
Events shown:     Ir
Event sort order: Ir
Thresholds:       99
Include dirs:     
User annotated:   
Auto-annotation:  on

--------------------------------------------------------------------------------
Ir                 
--------------------------------------------------------------------------------
2,352,215 (100.0%)  PROGRAM TOTALS

--------------------------------------------------------------------------------
Ir                file:function
--------------------------------------------------------------------------------
979,754 (41.65%)  ./elf/./elf/dl-lookup.c:_dl_lookup_symbol_x [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
566,747 (24.09%)  ./elf/./elf/dl-lookup.c:do_lookup_x [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
260,314 (11.07%)  ./elf/../sysdeps/x86_64/dl-machine.h:_dl_relocate_object
118,409 ( 5.03%)  ./elf/./elf/dl-lookup.c:check_match [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
108,575 ( 4.62%)  ./elf/./elf/do-rel.h:_dl_relocate_object
 74,295 ( 3.16%)  ./string/../sysdeps/x86_64/strcmp.S:strcmp [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
 23,387 ( 0.99%)  ./elf/./elf/dl-tunables.c:__GI___tunables_init [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
 19,725 ( 0.84%)  ./elf/../sysdeps/generic/dl-protected.h:do_lookup_x
 12,128 ( 0.52%)  ???:std::locale::_Impl::_M_install_facet(std::locale::id const*, std::locale::facet const*) [/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30]
 11,753 ( 0.50%)  ./elf/./elf/dl-version.c:_dl_check_map_versions [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
 10,900 ( 0.46%)  ./elf/../sysdeps/generic/ldsodefs.h:do_lookup_x
 10,240 ( 0.44%)  ./wcsmbs/./wcsmbs/btowc.c:btowc [/usr/lib/x86_64-linux-gnu/libc.so.6]
 10,185 ( 0.43%)  ./elf/../sysdeps/generic/ldsodefs.h:_dl_relocate_object
  7,900 ( 0.34%)  ./elf/./elf/dl-runtime.c:_dl_fixup [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
  4,395 ( 0.19%)  /usr/include/c++/11/bits/stl_vector.h:std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::operator[](unsigned long) [/home/lu/greenpear/OSlearn/valgrind/a.out]
  4,166 ( 0.18%)  ./elf/./elf/dl-reloc.c:_dl_relocate_object [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
  3,782 ( 0.16%)  ./elf/./elf/dl-load.c:_dl_map_object_from_fd [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
  3,774 ( 0.16%)  ./elf/./elf/dl-load.c:open_path [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
  3,456 ( 0.15%)  ./wcsmbs/./wcsmbs/wctob.c:wctob [/usr/lib/x86_64-linux-gnu/libc.so.6]
  3,444 ( 0.15%)  ./elf/../sysdeps/x86_64/dl-trampoline.h:_dl_runtime_resolve_xsave [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
  3,292 ( 0.14%)  ./elf/./elf/dl-cache.c:_dl_cache_libcmp [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
  3,085 ( 0.13%)  ./elf/../sysdeps/x86/dl-cacheinfo.h:intel_check_word.constprop.0 [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
  3,017 ( 0.13%)  ./elf/./elf/dl-load.c:open_verify.constprop.0 [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
  2,848 ( 0.12%)  ./elf/./elf/dl-misc.c:_dl_name_match_p [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
  2,733 ( 0.12%)  ???:std::ctype<wchar_t>::_M_initialize_ctype() [/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30]
  2,332 ( 0.10%)  /usr/include/c++/11/bits/stl_vector.h:std::vector<char, std::allocator<char> >::operator[](unsigned long) [/home/lu/greenpear/OSlearn/valgrind/a.out]
  2,243 ( 0.10%)  ./elf/./elf/dl-load.c:_dl_map_object [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
  2,226 ( 0.09%)  ./elf/./elf/dl-deps.c:_dl_map_object_deps [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
  2,198 ( 0.09%)  ./elf/../bits/stdlib-bsearch.h:intel_check_word.constprop.0
  2,011 ( 0.09%)  ./elf/./elf/dl-tunables.h:__GI___tunables_init
  2,000 ( 0.09%)  ./string/../sysdeps/x86_64/multiarch/memmove-vec-unaligned-erms.S:mempcpy [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
  1,831 ( 0.08%)  cachegrind.cpp:Solution::floodEdge(std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >&, int, int)'2 [/home/lu/greenpear/OSlearn/valgrind/a.out]
  1,676 ( 0.07%)  ./malloc/./malloc/malloc.c:_int_malloc [/usr/lib/x86_64-linux-gnu/libc.so.6]
  1,676 ( 0.07%)  cachegrind.cpp:Solution::solve(std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >&) [/home/lu/greenpear/OSlearn/valgrind/a.out]
  1,586 ( 0.07%)  ./string/../sysdeps/x86_64/multiarch/memcmp-sse4.S:__memcmp_sse4_1 [/usr/lib/x86_64-linux-gnu/libc.so.6]
  1,564 ( 0.07%)  ./string/../sysdeps/x86_64/multiarch/strlen-vec.S:__strlen_sse2 [/usr/lib/x86_64-linux-gnu/libc.so.6]
  1,492 ( 0.06%)  ./elf/./elf/get-dynamic-info.h:_dl_map_object_from_fd
  1,434 ( 0.06%)  ./io/../sysdeps/unix/sysv/linux/open64_nocancel.c:__open_nocancel [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
  1,364 ( 0.06%)  ???:std::ostream::sentry::sentry(std::ostream&) [/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30]
  1,344 ( 0.06%)  ???:std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long) [/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30]
  1,308 ( 0.06%)  ./elf/./elf/rtld.c:dl_main [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
  1,296 ( 0.06%)  ./libio/./libio/iofwrite.c:fwrite [/usr/lib/x86_64-linux-gnu/libc.so.6]
  1,272 ( 0.05%)  ./libio/./libio/fileops.c:_IO_file_xsputn@@GLIBC_2.2.5 [/usr/lib/x86_64-linux-gnu/libc.so.6]
  1,239 ( 0.05%)  ./elf/./elf/dl-cache.c:_dl_load_cache_lookup [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
  1,190 ( 0.05%)  ./elf/./elf/dl-minimal-malloc.c:__minimal_malloc [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
  1,181 ( 0.05%)  cachegrind.cpp:main [/home/lu/greenpear/OSlearn/valgrind/a.out]
  1,176 ( 0.05%)  ???:std::ostream::put(char) [/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30]
  1,136 ( 0.05%)  cachegrind.cpp:Solution::flood(std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >&, int, int)'2 [/home/lu/greenpear/OSlearn/valgrind/a.out]
  1,129 ( 0.05%)  ./elf/./elf/dl-object.c:_dl_new_object [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
  1,036 ( 0.04%)  ./wctype/./wctype/wctype_l.c:wctype_l [/usr/lib/x86_64-linux-gnu/libc.so.6]
  1,020 ( 0.04%)  /usr/include/c++/11/bits/stl_vector.h:std::vector<char, std::allocator<char> >::size() const [/home/lu/greenpear/OSlearn/valgrind/a.out]
  1,009 ( 0.04%)  ./libio/./libio/fileops.c:_IO_file_overflow@@GLIBC_2.2.5 [/usr/lib/x86_64-linux-gnu/libc.so.6]
    976 ( 0.04%)  /usr/include/c++/11/bits/stl_vector.h:std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::size() const [/home/lu/greenpear/OSlearn/valgrind/a.out]
    948 ( 0.04%)  ???:std::locale::id::_M_id() const [/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30]
    920 ( 0.04%)  cachegrind.cpp:Solution::floodEdge(std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >&, int, int) [/home/lu/greenpear/OSlearn/valgrind/a.out]
    901 ( 0.04%)  ./string/../sysdeps/x86_64/multiarch/strlen-vec.S:strlen [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    896 ( 0.04%)  ./wcsmbs/./wcsmbsload.h:btowc
    883 ( 0.04%)  ./elf/../sysdeps/x86_64/dl-machine.h:_dl_start
    816 ( 0.03%)  ./string/../sysdeps/x86_64/multiarch/memset-vec-unaligned-erms.S:memset [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    815 ( 0.03%)  ./elf/./elf/do-rel.h:_dl_start
    792 ( 0.03%)  ./string/../sysdeps/x86_64/multiarch/../strchr.S:index [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    776 ( 0.03%)  ./malloc/./malloc/malloc.c:ptmalloc_init.part.0
    774 ( 0.03%)  ./elf/../sysdeps/nptl/dl-tls_init_tp.c:rtld_mutex_dummy [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    768 ( 0.03%)  ./elf/./elf/dl-profstub.c:_dl_mcount_wrapper_check [/usr/lib/x86_64-linux-gnu/libc.so.6]
    768 ( 0.03%)  ./iconv/./iconv/gconv_simple.c:__gconv_btwoc_ascii [/usr/lib/x86_64-linux-gnu/libc.so.6]
    745 ( 0.03%)  ./elf/./dl-map-segments.h:_dl_map_object_from_fd
    740 ( 0.03%)  ./elf/./elf/dl-tunables.c:__tunable_get_val [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    732 ( 0.03%)  ???:std::ctype<char>::_M_widen_init() const [/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30]
    705 ( 0.03%)  ./stdlib/./stdlib/cxa_finalize.c:__cxa_finalize [/usr/lib/x86_64-linux-gnu/libc.so.6]
    704 ( 0.03%)  ./elf/./elf/dl-minimal.c:strsep [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    694 ( 0.03%)  ./elf/./elf/dl-hwcaps.c:_dl_important_hwcaps [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    666 ( 0.03%)  ???:std::locale::_Impl::_Impl(unsigned long) [/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30]
    596 ( 0.03%)  ./elf/../sysdeps/x86/dl-cacheinfo.h:handle_intel.constprop.0 [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    595 ( 0.03%)  ./malloc/./malloc/malloc.c:_int_free [/usr/lib/x86_64-linux-gnu/libc.so.6]
    560 ( 0.02%)  ./libio/./libio/putc.c:putc [/usr/lib/x86_64-linux-gnu/libc.so.6]
    530 ( 0.02%)  ./elf/./elf/dl-sort-maps.c:dfs_traversal.part.0 [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    530 ( 0.02%)  ./string/../sysdeps/x86_64/multiarch/memmove-vec-unaligned-erms.S:memcpy [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    517 ( 0.02%)  ???:0x00000000048f9a60 [???]
    508 ( 0.02%)  ./elf/./elf/dl-load.c:_dl_init_paths [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    502 ( 0.02%)  ./elf/../sysdeps/x86/dl-prop.h:_dl_map_object_from_fd
    491 ( 0.02%)  ./elf/../elf/dl-sysdep.c:_dl_sysdep_start [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    464 ( 0.02%)  ???:std::ios_base::ios_base() [/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30]
    460 ( 0.02%)  cachegrind.cpp:Solution::flood(std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >&, int, int) [/home/lu/greenpear/OSlearn/valgrind/a.out]
    456 ( 0.02%)  ???:std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*) [/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30]
    453 ( 0.02%)  ./malloc/./malloc/malloc.c:malloc [/usr/lib/x86_64-linux-gnu/libc.so.6]
    436 ( 0.02%)  ./elf/./dl-find_object.h:_dl_find_object_from_map [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    429 ( 0.02%)  ./stdlib/./stdlib/cxa_atexit.c:__cxa_atexit [/usr/lib/x86_64-linux-gnu/libc.so.6]
    421 ( 0.02%)  ./elf/./elf/dl-init.c:call_init.part.0 [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    420 ( 0.02%)  ./elf/./elf/dl-error-skeleton.c:_dl_catch_exception [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    420 ( 0.02%)  ./libio/./libio/iofflush.c:fflush [/usr/lib/x86_64-linux-gnu/libc.so.6]
    414 ( 0.02%)  ./elf/./elf/dl-fini.c:_dl_fini [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    414 ( 0.02%)  ???:std::__cxx11::numpunct<char>::_M_initialize_numpunct(__locale_struct*) [/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30]
    414 ( 0.02%)  ???:std::numpunct<char>::_M_initialize_numpunct(__locale_struct*) [/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30]
    408 ( 0.02%)  ./libio/./libio/libioP.h:fwrite
    392 ( 0.02%)  ./elf/./elf/dl-hwcaps_split.c:_dl_hwcaps_split_masked [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    392 ( 0.02%)  ./elf/./elf/dl-load.c:fillin_rpath.isra.0 [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    392 ( 0.02%)  ./stdlib/./stdlib/cxa_atexit.c:__new_exitfn [/usr/lib/x86_64-linux-gnu/libc.so.6]
    384 ( 0.02%)  ./string/../sysdeps/x86_64/multiarch/memmove-vec-unaligned-erms.S:__mempcpy_sse2_unaligned [/usr/lib/x86_64-linux-gnu/libc.so.6]
    374 ( 0.02%)  ???:std::locale::locale() [/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30]
    360 ( 0.02%)  ???:std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char) [/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30]
    350 ( 0.01%)  ./elf/../elf/dl-tls.c:_dl_allocate_tls_storage [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    350 ( 0.01%)  ???:std::__cxx11::numpunct<wchar_t>::_M_initialize_numpunct(__locale_struct*) [/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30]
    350 ( 0.01%)  ???:std::numpunct<wchar_t>::_M_initialize_numpunct(__locale_struct*) [/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30]
    344 ( 0.01%)  ./elf/./elf/dl-sort-maps.c:_dl_sort_maps [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    342 ( 0.01%)  ./elf/./get-dynamic-info.h:dl_main
    335 ( 0.01%)  ./elf/./elf/dl-environ.c:_dl_next_ld_env_entry [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    333 ( 0.01%)  ???:__cpu_indicator_init [/usr/lib/x86_64-linux-gnu/libgcc_s.so.1]
    310 ( 0.01%)  ./setjmp/../sysdeps/x86_64/setjmp.S:__sigsetjmp [/usr/lib/x86_64-linux-gnu/libc.so.6]
    309 ( 0.01%)  ./libio/./libio/genops.c:__overflow [/usr/lib/x86_64-linux-gnu/libc.so.6]
    294 ( 0.01%)  ???:0x00000000000dc6c0 [/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30]
    278 ( 0.01%)  ./elf/./elf/dl-find_object.c:_dlfo_process_initial [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    276 ( 0.01%)  ???:std::ostream::flush() [/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30]
    273 ( 0.01%)  ???:std::ios_base::Init::Init() [/usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30]
    270 ( 0.01%)  ./libio/./libio/fileops.c:_IO_file_sync@@GLIBC_2.2.5 [/usr/lib/x86_64-linux-gnu/libc.so.6]
    268 ( 0.01%)  ./elf/./elf/dl-lookup-direct.c:_dl_lookup_direct [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    265 ( 0.01%)  ./elf/./elf/dl-object.c:_dl_add_to_namespace_list [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    261 ( 0.01%)  ???:0x00000000048f7f30 [???]
    252 ( 0.01%)  ./libio/./libio/libioP.h:fflush
    252 ( 0.01%)  /usr/include/c++/11/bits/stl_vector.h:std::vector<char, std::allocator<char> >::vector(std::vector<char, std::allocator<char> > const&) [/home/lu/greenpear/OSlearn/valgrind/a.out]
    251 ( 0.01%)  ./elf/./elf/dl-load.c:open_verify.constprop.1 [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    248 ( 0.01%)  ./elf/./elf/dl-find_object.c:_dlfo_sort_mappings [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    245 ( 0.01%)  ./elf/./elf/dl-tunables.c:__GI___tunable_set_val [/usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2]
    244 ( 0.01%)  ./elf/../sysdeps/x86/dl-prop.h:dl_main

--------------------------------------------------------------------------------
-- Auto-annotated source: cachegrind.cpp
--------------------------------------------------------------------------------
Ir             

    .           #include <iostream>
    .           #include <string>
    .           #include <vector>
    .           using namespace std;
    .           
    .           class Solution {
    .           public:
    6 ( 0.00%)      void solve(vector<vector<char>>& board) {
   11 ( 0.00%)          int m = board.size(), n = board[0].size();
   15 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::operator[](unsigned long) (1x)
   16 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::size() const (1x)
   12 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<char, std::allocator<char> >::size() const (1x)
   29 ( 0.00%)          for (int i = 0; i < n; i++) {
   90 ( 0.00%)              if (board[0][i] == 'O') {
   90 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::operator[](unsigned long) (6x)
   66 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<char, std::allocator<char> >::operator[](unsigned long) (6x)
   21 ( 0.00%)                  floodEdge(board, 0, i);
2,178 ( 0.09%)  => cachegrind.cpp:Solution::floodEdge(std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >&, int, int) (3x)
    .                       }
  108 ( 0.00%)              if (board[m - 1][i] == 'O') {
   90 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::operator[](unsigned long) (6x)
   66 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<char, std::allocator<char> >::operator[](unsigned long) (6x)
   27 ( 0.00%)                  floodEdge(board, m - 1, i);
2,193 ( 0.09%)  => cachegrind.cpp:Solution::floodEdge(std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >&, int, int) (3x)
    .                       }
    .                   }
   21 ( 0.00%)          for (int i = 0; i < m; i++) {
   56 ( 0.00%)              if (board[i][0] == 'O') {
   60 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::operator[](unsigned long) (4x)
   44 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<char, std::allocator<char> >::operator[](unsigned long) (4x)
    6 ( 0.00%)                  floodEdge(board, i, 0);
  756 ( 0.03%)  => cachegrind.cpp:Solution::floodEdge(std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >&, int, int) (1x)
    .                       }
   72 ( 0.00%)              if (board[i][n - 1] == 'O') {
   60 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::operator[](unsigned long) (4x)
   44 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<char, std::allocator<char> >::operator[](unsigned long) (4x)
    7 ( 0.00%)                  floodEdge(board, i, n - 1);
  816 ( 0.03%)  => cachegrind.cpp:Solution::floodEdge(std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >&, int, int) (1x)
    .                       }
    .                   }
   21 ( 0.00%)          for (int i = 0; i < m; i++) {
  116 ( 0.00%)              for (int j = 0; j < n; j++) {
  408 ( 0.02%)                  if (board[i][j] == 'O') {
  360 ( 0.02%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::operator[](unsigned long) (24x)
  264 ( 0.01%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<char, std::allocator<char> >::operator[](unsigned long) (24x)
   24 ( 0.00%)                      flood(board, i, j);
3,600 ( 0.15%)  => cachegrind.cpp:Solution::flood(std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >&, int, int) (4x)
    .                           }
    .                       }
    .                   }
   21 ( 0.00%)          for (int i = 0; i < m; i++) {
  116 ( 0.00%)              for (int j = 0; j < n; j++) {
  408 ( 0.02%)                  if (board[i][j] == 'I') {
  360 ( 0.02%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::operator[](unsigned long) (24x)
  264 ( 0.01%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<char, std::allocator<char> >::operator[](unsigned long) (24x)
  104 ( 0.00%)                      board[i][j] = 'O';
  120 ( 0.01%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::operator[](unsigned long) (8x)
   88 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<char, std::allocator<char> >::operator[](unsigned long) (8x)
    .                           }
    .                       }
    .                   }
    4 ( 0.00%)      }
    .           
  360 ( 0.02%)      void floodEdge(vector<vector<char>>& board, int i, int j) {
  849 ( 0.04%)          if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size()) {
  120 ( 0.01%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::operator[](unsigned long) (8x)
  128 ( 0.01%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::size() const (8x)
   96 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<char, std::allocator<char> >::size() const (8x)
   20 ( 0.00%)              return;
    .                   }
    .           
1,012 ( 0.04%)          if (board[i][j] == 'I' || board[i][j] == 'X') {
  240 ( 0.01%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::operator[](unsigned long) (16x)
  176 ( 0.01%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<char, std::allocator<char> >::operator[](unsigned long) (16x)
   22 ( 0.00%)              return;
    .                   }
    .           
  104 ( 0.00%)          board[i][j] = 'I';
  120 ( 0.01%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::operator[](unsigned long) (8x)
   88 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<char, std::allocator<char> >::operator[](unsigned long) (8x)
   72 ( 0.00%)          floodEdge(board, i + 1, j);
  965 ( 0.04%)  => cachegrind.cpp:Solution::floodEdge(std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >&, int, int)'2 (8x)
   72 ( 0.00%)          floodEdge(board, i - 1, j);
  890 ( 0.04%)  => cachegrind.cpp:Solution::floodEdge(std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >&, int, int)'2 (8x)
   56 ( 0.00%)          floodEdge(board, i, j + 1);
1,160 ( 0.05%)  => cachegrind.cpp:Solution::floodEdge(std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >&, int, int)'2 (8x)
   64 ( 0.00%)          floodEdge(board, i, j - 1);
1,040 ( 0.04%)  => cachegrind.cpp:Solution::floodEdge(std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >&, int, int)'2 (8x)
  120 ( 0.01%)      }
    .           
  180 ( 0.01%)      void flood(vector<vector<char>>& board, int i, int j) {
  480 ( 0.02%)          if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size()) {
   60 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::operator[](unsigned long) (4x)
   64 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::size() const (4x)
   48 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<char, std::allocator<char> >::size() const (4x)
    .                       return;
    .                   }
    .           
  676 ( 0.03%)          if (board[i][j] == 'I' || board[i][j] == 'X') {
  120 ( 0.01%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::operator[](unsigned long) (8x)
   88 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<char, std::allocator<char> >::operator[](unsigned long) (8x)
   16 ( 0.00%)              return;
    .                   }
    .           
   52 ( 0.00%)          board[i][j] = 'X';
   60 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::operator[](unsigned long) (4x)
   44 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<char, std::allocator<char> >::operator[](unsigned long) (4x)
   36 ( 0.00%)          flood(board, i + 1, j);
  664 ( 0.03%)  => cachegrind.cpp:Solution::flood(std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >&, int, int)'2 (4x)
   36 ( 0.00%)          flood(board, i - 1, j);
  664 ( 0.03%)  => cachegrind.cpp:Solution::flood(std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >&, int, int)'2 (4x)
   28 ( 0.00%)          flood(board, i, j + 1);
  664 ( 0.03%)  => cachegrind.cpp:Solution::flood(std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >&, int, int)'2 (4x)
   32 ( 0.00%)          flood(board, i, j - 1);
  664 ( 0.03%)  => cachegrind.cpp:Solution::flood(std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >&, int, int)'2 (4x)
   60 ( 0.00%)      }
    .           };
    .           
   12 ( 0.00%)  int main() {
    .               vector<vector<char>> board = {
    .                   {'X','O','X','O','X','O'},
    .                   {'O','X','O','X','O','X'},
    .                   {'X','O','X','O','X','O'},
    .                   {'O','X','O','X','O','X'}
  157 ( 0.01%)      };
4,047 ( 0.17%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::vector(std::initializer_list<std::vector<char, std::allocator<char> > >, std::allocator<std::vector<char, std::allocator<char> > > const&) (1x)
3,212 ( 0.14%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<char, std::allocator<char> >::vector(std::initializer_list<char>, std::allocator<char> const&) (4x)
2,436 ( 0.10%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<char, std::allocator<char> >::~vector() (4x)
   18 ( 0.00%)  => /usr/include/c++/11/bits/allocator.h:std::allocator<std::vector<char, std::allocator<char> > >::~allocator() (1x)
   18 ( 0.00%)  => /usr/include/c++/11/bits/allocator.h:std::allocator<std::vector<char, std::allocator<char> > >::allocator() (1x)
   16 ( 0.00%)  => ???:0x0000000000109240 (4x)
   16 ( 0.00%)  => ???:0x00000000001092d0 (4x)
    .           
    .               Solution s;
    5 ( 0.00%)      s.solve(board);
13,238 ( 0.56%)  => cachegrind.cpp:Solution::solve(std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >&) (1x)
   51 ( 0.00%)      for (int i = 0; i < board.size(); i++) {
   80 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::size() const (5x)
  368 ( 0.02%)          for (int j = 0; j < board[0].size(); j++) {
  420 ( 0.02%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::operator[](unsigned long) (28x)
  336 ( 0.01%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<char, std::allocator<char> >::size() const (28x)
  552 ( 0.02%)              cout << board[i][j] << " ";
9,268 ( 0.39%)  => ???:0x0000000000109200 (24x)
6,499 ( 0.28%)  => ???:0x0000000000109260 (24x)
  360 ( 0.02%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::operator[](unsigned long) (24x)
  264 ( 0.01%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<char, std::allocator<char> >::operator[](unsigned long) (24x)
    .                   }
   20 ( 0.00%)          cout << endl;
5,623 ( 0.24%)  => ???:0x0000000000109230 (4x)
    .               }
    1 ( 0.00%)      return 0;
   36 ( 0.00%)  }
103,613 ( 4.40%)  => cachegrind.cpp:__static_initialization_and_destruction_0(int, int) (1x)
    .           /**
    .            * 注意每一行往后翻到最后才是程序对应的每一行（向右移动滚轴）
    .            * Ir (Instruction Read)
    .           表示从内存中读取指令的次数。
    .           
    .           I1mr (L1 Instruction Cache Miss Read)
    .           表示读取指令时一级指令缓存（L1 Instruction Cache）未命中的次数。
    .           
-- line 100 ----------------------------------------

--------------------------------------------------------------------------------
-- Auto-annotated source: /usr/include/c++/11/bits/stl_vector.h
--------------------------------------------------------------------------------
Ir             

-- line 89 ----------------------------------------
    .                   pointer;
    .           
    .                 struct _Vector_impl_data
    .                 {
    .                   pointer _M_start;
    .                   pointer _M_finish;
    .                   pointer _M_end_of_storage;
    .           
   36 ( 0.00%)          _Vector_impl_data() _GLIBCXX_NOEXCEPT
   54 ( 0.00%)          : _M_start(), _M_finish(), _M_end_of_storage()
   27 ( 0.00%)          { }
    .           
    .           #if __cplusplus >= 201103L
    .                   _Vector_impl_data(_Vector_impl_data&& __x) noexcept
    .                   : _M_start(__x._M_start), _M_finish(__x._M_finish),
    .                     _M_end_of_storage(__x._M_end_of_storage)
    .                   { __x._M_start = __x._M_finish = __x._M_end_of_storage = pointer(); }
    .           #endif
    .           
-- line 107 ----------------------------------------
-- line 120 ----------------------------------------
    .                     // information used by TBAA.
    .                     _Vector_impl_data __tmp;
    .                     __tmp._M_copy_data(*this);
    .                     _M_copy_data(__x);
    .                     __x._M_copy_data(__tmp);
    .                   }
    .                 };
    .           
   99 ( 0.00%)        struct _Vector_impl
   32 ( 0.00%)  => ???:0x0000000000109190 (8x)
    .                   : public _Tp_alloc_type, public _Vector_impl_data
    .                 {
    .                   _Vector_impl() _GLIBCXX_NOEXCEPT_IF(
    .                       is_nothrow_default_constructible<_Tp_alloc_type>::value)
    .                   : _Tp_alloc_type()
    .                   { }
    .           
   54 ( 0.00%)          _Vector_impl(_Tp_alloc_type const& __a) _GLIBCXX_NOEXCEPT
   72 ( 0.00%)          : _Tp_alloc_type(__a)
  104 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::_Vector_base<char, std::allocator<char> >::_Vector_impl_data::_Vector_impl_data() (8x)
   32 ( 0.00%)  => ???:0x0000000000109270 (8x)
   27 ( 0.00%)          { }
    .           
    .           #if __cplusplus >= 201103L
    .                   // Not defaulted, to enforce noexcept(true) even when
    .                   // !is_nothrow_move_constructible<_Tp_alloc_type>.
    .                   _Vector_impl(_Vector_impl&& __x) noexcept
    .                   : _Tp_alloc_type(std::move(__x)), _Vector_impl_data(std::move(__x))
    .                   { }
    .           
-- line 146 ----------------------------------------
-- line 268 ----------------------------------------
    .           #define _GLIBCXX_ASAN_ANNOTATE_BEFORE_DEALLOC
    .           #endif // _GLIBCXX_SANITIZE_STD_ALLOCATOR && _GLIBCXX_SANITIZE_VECTOR
    .                 };
    .           
    .               public:
    .                 typedef _Alloc allocator_type;
    .           
    .                 _Tp_alloc_type&
   92 ( 0.00%)        _M_get_Tp_allocator() _GLIBCXX_NOEXCEPT
   69 ( 0.00%)        { return this->_M_impl; }
    .           
    .                 const _Tp_alloc_type&
   16 ( 0.00%)        _M_get_Tp_allocator() const _GLIBCXX_NOEXCEPT
   12 ( 0.00%)        { return this->_M_impl; }
    .           
    .                 allocator_type
    .                 get_allocator() const _GLIBCXX_NOEXCEPT
    .                 { return allocator_type(_M_get_Tp_allocator()); }
    .           
    .           #if __cplusplus >= 201103L
    .                 _Vector_base() = default;
    .           #else
    .                 _Vector_base() { }
    .           #endif
    .           
   30 ( 0.00%)        _Vector_base(const allocator_type& __a) _GLIBCXX_NOEXCEPT
   40 ( 0.00%)        : _M_impl(__a) { }
  136 ( 0.01%)  => /usr/include/c++/11/bits/stl_vector.h:std::_Vector_base<char, std::allocator<char> >::_Vector_impl::_Vector_impl(std::allocator<char> const&) (4x)
    .           
    .                 // Kept for ABI compatibility.
    .           #if !_GLIBCXX_INLINE_VERSION
    .                 _Vector_base(size_t __n)
    .                 : _M_impl()
    .                 { _M_create_storage(__n); }
    .           #endif
    .           
   32 ( 0.00%)        _Vector_base(size_t __n, const allocator_type& __a)
   20 ( 0.00%)        : _M_impl(__a)
  136 ( 0.01%)  => /usr/include/c++/11/bits/stl_vector.h:std::_Vector_base<char, std::allocator<char> >::_Vector_impl::_Vector_impl(std::allocator<char> const&) (4x)
   36 ( 0.00%)        { _M_create_storage(__n); }
1,132 ( 0.05%)  => /usr/include/c++/11/bits/stl_vector.h:std::_Vector_base<char, std::allocator<char> >::_M_create_storage(unsigned long) (4x)
    .           
    .           #if __cplusplus >= 201103L
    .                 _Vector_base(_Vector_base&&) = default;
    .           
    .                 // Kept for ABI compatibility.
    .           # if !_GLIBCXX_INLINE_VERSION
    .                 _Vector_base(_Tp_alloc_type&& __a) noexcept
    .                 : _M_impl(std::move(__a)) { }
-- line 313 ----------------------------------------
-- line 325 ----------------------------------------
    .                 }
    .           # endif
    .           
    .                 _Vector_base(const allocator_type& __a, _Vector_base&& __x)
    .                 : _M_impl(_Tp_alloc_type(__a), std::move(__x._M_impl))
    .                 { }
    .           #endif
    .           
   45 ( 0.00%)        ~_Vector_base() _GLIBCXX_NOEXCEPT
    .                 {
   63 ( 0.00%)          _M_deallocate(_M_impl._M_start,
  152 ( 0.01%)  => /usr/include/c++/11/bits/stl_vector.h:std::_Vector_base<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::_M_deallocate(std::vector<char, std::allocator<char> >*, unsigned long) (1x)
   58 ( 0.00%)                        _M_impl._M_end_of_storage - _M_impl._M_start);
   54 ( 0.00%)        }
   29 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::_Vector_base<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::_Vector_impl::~_Vector_impl() (1x)
    .           
    .               public:
    .                 _Vector_impl _M_impl;
    .           
    .                 pointer
   54 ( 0.00%)        _M_allocate(size_t __n)
    .                 {
    .                   typedef __gnu_cxx::__alloc_traits<_Tp_alloc_type> _Tr;
   72 ( 0.00%)          return __n != 0 ? _Tr::allocate(_M_impl, __n) : pointer();
1,928 ( 0.08%)  => /usr/include/c++/11/bits/alloc_traits.h:std::allocator_traits<std::allocator<char> >::allocate(std::allocator<char>&, unsigned long) (8x)
   18 ( 0.00%)        }
    .           
    .                 void
   63 ( 0.00%)        _M_deallocate(pointer __p, size_t __n)
    .                 {
    .                   typedef __gnu_cxx::__alloc_traits<_Tp_alloc_type> _Tr;
   18 ( 0.00%)          if (__p)
   54 ( 0.00%)            _Tr::deallocate(_M_impl, __p, __n);
2,479 ( 0.11%)  => /usr/include/c++/11/bits/alloc_traits.h:std::allocator_traits<std::allocator<char> >::deallocate(std::allocator<char>&, char*, unsigned long) (8x)
   27 ( 0.00%)        }
    .           
    .               protected:
    .                 void
   24 ( 0.00%)        _M_create_storage(size_t __n)
    .                 {
   28 ( 0.00%)          this->_M_impl._M_start = this->_M_allocate(__n);
1,028 ( 0.04%)  => /usr/include/c++/11/bits/stl_vector.h:std::_Vector_base<char, std::allocator<char> >::_M_allocate(unsigned long) (4x)
   16 ( 0.00%)          this->_M_impl._M_finish = this->_M_impl._M_start;
   24 ( 0.00%)          this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
   12 ( 0.00%)        }
    .               };
    .           
    .             /**
    .              *  @brief A standard container which offers fixed time access to
    .              *  individual elements in any order.
    .              *
    .              *  @ingroup sequences
    .              *
-- line 372 ----------------------------------------
-- line 545 ----------------------------------------
    .                  *
    .                  *  All the elements of @a __x are copied, but any unused capacity in
    .                  *  @a __x  will not be copied
    .                  *  (i.e. capacity() == size() in the new %vector).
    .                  *
    .                  *  The newly-created %vector uses a copy of the allocator object used
    .                  *  by @a __x (unless the allocator traits dictate a different object).
    .                  */
   48 ( 0.00%)        vector(const vector& __x)
    .                 : _Base(__x.size(),
   84 ( 0.00%)          _Alloc_traits::_S_select_on_copy(__x._M_get_Tp_allocator()))
1,356 ( 0.06%)  => /usr/include/c++/11/bits/stl_vector.h:std::_Vector_base<char, std::allocator<char> >::_Vector_base(unsigned long, std::allocator<char> const&) (4x)
  152 ( 0.01%)  => /usr/include/c++/11/ext/alloc_traits.h:__gnu_cxx::__alloc_traits<std::allocator<char>, char>::_S_select_on_copy(std::allocator<char> const&) (4x)
   48 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<char, std::allocator<char> >::size() const (4x)
   28 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::_Vector_base<char, std::allocator<char> >::_M_get_Tp_allocator() const (4x)
   16 ( 0.00%)  => ???:0x0000000000109240 (4x)
    .                 {
    8 ( 0.00%)          this->_M_impl._M_finish =
   56 ( 0.00%)            std::__uninitialized_copy_a(__x.begin(), __x.end(),
  952 ( 0.04%)  => /usr/include/c++/11/bits/stl_uninitialized.h:char* std::__uninitialized_copy_a<__gnu_cxx::__normal_iterator<char const*, std::vector<char, std::allocator<char> > >, char*, char>(__gnu_cxx::__normal_iterator<char const*, std::vector<char, std::allocator<char> > >, __gnu_cxx::__normal_iterator<char const*, std::vector<char, std::allocator<char> > >, char*, std::allocator<char>&) (4x)
  128 ( 0.01%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<char, std::allocator<char> >::end() const (4x)
  124 ( 0.01%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<char, std::allocator<char> >::begin() const (4x)
    .                                                 this->_M_impl._M_start,
   16 ( 0.00%)                                        _M_get_Tp_allocator());
   28 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::_Vector_base<char, std::allocator<char> >::_M_get_Tp_allocator() (4x)
   40 ( 0.00%)        }
    .           
    .           #if __cplusplus >= 201103L
    .                 /**
    .                  *  @brief  %Vector move constructor.
    .                  *
    .                  *  The newly-created %vector contains the exact contents of the
    .                  *  moved instance.
    .                  *  The contents of the moved instance are a valid, but unspecified
-- line 569 ----------------------------------------
-- line 617 ----------------------------------------
    .                  *  @param  __a  An allocator.
    .                  *
    .                  *  Create a %vector consisting of copies of the elements in the
    .                  *  initializer_list @a __l.
    .                  *
    .                  *  This will call the element type's copy constructor N times
    .                  *  (where N is @a __l.size()) and do no memory reallocation.
    .                  */
   75 ( 0.00%)        vector(initializer_list<value_type> __l,
    .                        const allocator_type& __a = allocator_type())
   25 ( 0.00%)        : _Base(__a)
   66 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::_Vector_base<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::_Vector_base(std::allocator<std::vector<char, std::allocator<char> > > const&) (1x)
    .                 {
   65 ( 0.00%)          _M_range_initialize(__l.begin(), __l.end(),
3,895 ( 0.17%)  => /usr/include/c++/11/bits/stl_vector.h:void std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::_M_range_initialize<std::vector<char, std::allocator<char> > const*>(std::vector<char, std::allocator<char> > const*, std::vector<char, std::allocator<char> > const*, std::forward_iterator_tag) (1x)
   38 ( 0.00%)  => /usr/include/c++/11/initializer_list:std::initializer_list<std::vector<char, std::allocator<char> > >::end() const (1x)
    8 ( 0.00%)  => /usr/include/c++/11/initializer_list:std::initializer_list<std::vector<char, std::allocator<char> > >::begin() const (1x)
    .                                       random_access_iterator_tag());
   35 ( 0.00%)        }
    .           #endif
    .           
    .                 /**
    .                  *  @brief  Builds a %vector from a range.
    .                  *  @param  __first  An input iterator.
    .                  *  @param  __last  An input iterator.
    .                  *  @param  __a  An allocator.
    .                  *
-- line 639 ----------------------------------------
-- line 670 ----------------------------------------
    .           #endif
    .           
    .                 /**
    .                  *  The dtor only erases the elements, and note that if the
    .                  *  elements themselves are pointers, the pointed-to memory is
    .                  *  not touched in any way.  Managing the pointer is the user's
    .                  *  responsibility.
    .                  */
   45 ( 0.00%)        ~vector() _GLIBCXX_NOEXCEPT
    .                 {
   63 ( 0.00%)          std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
1,178 ( 0.05%)  => /usr/include/c++/11/bits/alloc_traits.h:void std::_Destroy<std::vector<char, std::allocator<char> >*, std::vector<char, std::allocator<char> > >(std::vector<char, std::allocator<char> >*, std::vector<char, std::allocator<char> >*, std::allocator<std::vector<char, std::allocator<char> > >&) (1x)
   36 ( 0.00%)                        _M_get_Tp_allocator());
    7 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::_Vector_base<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::_M_get_Tp_allocator() (1x)
    .                   _GLIBCXX_ASAN_ANNOTATE_BEFORE_DEALLOC;
   54 ( 0.00%)        }
  209 ( 0.01%)  => /usr/include/c++/11/bits/stl_vector.h:std::_Vector_base<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::~_Vector_base() (1x)
    .           
    .                 /**
    .                  *  @brief  %Vector assignment operator.
    .                  *  @param  __x  A %vector of identical element and allocator types.
    .                  *
    .                  *  All the elements of @a __x are copied, but any unused capacity in
    .                  *  @a __x will not be copied.
    .                  *
-- line 691 ----------------------------------------
-- line 812 ----------------------------------------
    .                 { return iterator(this->_M_impl._M_start); }
    .           
    .                 /**
    .                  *  Returns a read-only (constant) iterator that points to the
    .                  *  first element in the %vector.  Iteration is done in ordinary
    .                  *  element order.
    .                  */
    .                 const_iterator
   32 ( 0.00%)        begin() const _GLIBCXX_NOEXCEPT
   44 ( 0.00%)        { return const_iterator(this->_M_impl._M_start); }
   48 ( 0.00%)  => /usr/include/c++/11/bits/stl_iterator.h:__gnu_cxx::__normal_iterator<char const*, std::vector<char, std::allocator<char> > >::__normal_iterator(char const* const&) (4x)
    .           
    .                 /**
    .                  *  Returns a read/write iterator that points one past the last
    .                  *  element in the %vector.  Iteration is done in ordinary
    .                  *  element order.
    .                  */
    .                 iterator
    .                 end() _GLIBCXX_NOEXCEPT
-- line 829 ----------------------------------------
-- line 830 ----------------------------------------
    .                 { return iterator(this->_M_impl._M_finish); }
    .           
    .                 /**
    .                  *  Returns a read-only (constant) iterator that points one past
    .                  *  the last element in the %vector.  Iteration is done in
    .                  *  ordinary element order.
    .                  */
    .                 const_iterator
   32 ( 0.00%)        end() const _GLIBCXX_NOEXCEPT
   48 ( 0.00%)        { return const_iterator(this->_M_impl._M_finish); }
   48 ( 0.00%)  => /usr/include/c++/11/bits/stl_iterator.h:__gnu_cxx::__normal_iterator<char const*, std::vector<char, std::allocator<char> > >::__normal_iterator(char const* const&) (4x)
    .           
    .                 /**
    .                  *  Returns a read/write reverse iterator that points to the
    .                  *  last element in the %vector.  Iteration is done in reverse
    .                  *  element order.
    .                  */
    .                 reverse_iterator
    .                 rbegin() _GLIBCXX_NOEXCEPT
-- line 847 ----------------------------------------
-- line 910 ----------------------------------------
    .                 const_reverse_iterator
    .                 crend() const noexcept
    .                 { return const_reverse_iterator(begin()); }
    .           #endif
    .           
    .                 // [23.2.4.2] capacity
    .                 /**  Returns the number of elements in the %vector.  */
    .                 size_type
  584 ( 0.02%)        size() const _GLIBCXX_NOEXCEPT
1,412 ( 0.06%)        { return size_type(this->_M_impl._M_finish - this->_M_impl._M_start); }
    .           
    .                 /**  Returns the size() of the largest possible %vector.  */
    .                 size_type
    .                 max_size() const _GLIBCXX_NOEXCEPT
    .                 { return _S_max_size(_M_get_Tp_allocator()); }
    .           
    .           #if __cplusplus >= 201103L
    .                 /**
-- line 927 ----------------------------------------
-- line 1035 ----------------------------------------
    .                  *  @return  Read/write reference to data.
    .                  *
    .                  *  This operator allows for easy, array-style, data access.
    .                  *  Note that data access with this operator is unchecked and
    .                  *  out_of_range lookups are not defined. (For checked lookups
    .                  *  see at().)
    .                  */
    .                 reference
2,525 ( 0.11%)        operator[](size_type __n) _GLIBCXX_NOEXCEPT
    .                 {
    .                   __glibcxx_requires_subscript(__n);
3,192 ( 0.14%)          return *(this->_M_impl._M_start + __n);
1,010 ( 0.04%)        }
    .           
    .                 /**
    .                  *  @brief  Subscript access to the data contained in the %vector.
    .                  *  @param __n The index of the element for which data should be
    .                  *  accessed.
    .                  *  @return  Read-only (constant) reference to data.
    .                  *
    .                  *  This operator allows for easy, array-style, data access.
-- line 1055 ----------------------------------------
-- line 1569 ----------------------------------------
    .                       clear();
    .                       __throw_exception_again;
    .                     }
    .                   }
    .           
    .                 // Called by the second initialize_dispatch above
    .                 template<typename _ForwardIterator>
    .                   void
   40 ( 0.00%)          _M_range_initialize(_ForwardIterator __first, _ForwardIterator __last,
    .                                       std::forward_iterator_tag)
    .                   {
   30 ( 0.00%)            const size_type __n = std::distance(__first, __last);
   35 ( 0.00%)  => /usr/include/c++/11/bits/stl_iterator_base_funcs.h:std::iterator_traits<std::vector<char, std::allocator<char> > const*>::difference_type std::distance<std::vector<char, std::allocator<char> > const*>(std::vector<char, std::allocator<char> > const*, std::vector<char, std::allocator<char> > const*) (1x)
    .                     this->_M_impl._M_start
   70 ( 0.00%)              = this->_M_allocate(_S_check_init_len(__n, _M_get_Tp_allocator()));
  267 ( 0.01%)  => /usr/include/c++/11/bits/stl_vector.h:std::_Vector_base<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::_M_allocate(unsigned long) (1x)
  138 ( 0.01%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::_S_check_init_len(unsigned long, std::allocator<std::vector<char, std::allocator<char> > > const&) (1x)
    7 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::_Vector_base<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::_M_get_Tp_allocator() (1x)
   34 ( 0.00%)            this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
   10 ( 0.00%)            this->_M_impl._M_finish =
   30 ( 0.00%)              std::__uninitialized_copy_a(__first, __last,
3,387 ( 0.14%)  => /usr/include/c++/11/bits/stl_uninitialized.h:std::vector<char, std::allocator<char> >* std::__uninitialized_copy_a<std::vector<char, std::allocator<char> > const*, std::vector<char, std::allocator<char> >*, std::vector<char, std::allocator<char> > >(std::vector<char, std::allocator<char> > const*, std::vector<char, std::allocator<char> > const*, std::vector<char, std::allocator<char> >*, std::allocator<std::vector<char, std::allocator<char> > >&) (1x)
    .                                                   this->_M_impl._M_start,
   20 ( 0.00%)                                          _M_get_Tp_allocator());
    7 ( 0.00%)  => /usr/include/c++/11/bits/stl_vector.h:std::_Vector_base<std::vector<char, std::allocator<char> >, std::allocator<std::vector<char, std::allocator<char> > > >::_M_get_Tp_allocator() (1x)
   20 ( 0.00%)          }
    .           
    .                 // Called by the first initialize_dispatch above and by the
    .                 // vector(n,value,a) constructor.
    .                 void
    .                 _M_fill_initialize(size_type __n, const value_type& __value)
    .                 {
    .                   this->_M_impl._M_finish =
    .                     std::__uninitialized_fill_n_a(this->_M_impl._M_start, __n, __value,
-- line 1596 ----------------------------------------
-- line 1759 ----------------------------------------
    .                     __throw_length_error(__N(__s));
    .           
    .                   const size_type __len = size() + (std::max)(size(), __n);
    .                   return (__len < size() || __len > max_size()) ? max_size() : __len;
    .                 }
    .           
    .                 // Called by constructors to check initial size.
    .                 static size_type
   50 ( 0.00%)        _S_check_init_len(size_type __n, const allocator_type& __a)
    .                 {
   75 ( 0.00%)          if (__n > _S_max_size(_Tp_alloc_type(__a)))
  264 ( 0.01%)  => /usr/include/c++/11/bits/stl_vector.h:std::vector<char, std::allocator<char> >::_S_max_size(std::allocator<char> const&) (4x)
   16 ( 0.00%)  => ???:0x00000000001091d0 (4x)
   16 ( 0.00%)  => ???:0x0000000000109240 (4x)
    .                     __throw_length_error(
    .                         __N("cannot create std::vector larger than max_size()"));
    5 ( 0.00%)          return __n;
   30 ( 0.00%)        }
    .           
    .                 static size_type
   40 ( 0.00%)        _S_max_size(const _Tp_alloc_type& __a) _GLIBCXX_NOEXCEPT
    .                 {
    .                   // std::distance(begin(), end()) cannot be greater than PTRDIFF_MAX,
    .                   // and realistically we can't store more than PTRDIFF_MAX/sizeof(T)
    .                   // (even if std::allocator_traits::max_size says we can).
   10 ( 0.00%)          const size_t __diffmax
    .                     = __gnu_cxx::__numeric_traits<ptrdiff_t>::__max / sizeof(_Tp);
   20 ( 0.00%)          const size_t __allocmax = _Alloc_traits::max_size(__a);
   27 ( 0.00%)  => /usr/include/c++/11/bits/alloc_traits.h:std::allocator_traits<std::allocator<std::vector<char, std::allocator<char> > > >::max_size(std::allocator<std::vector<char, std::allocator<char> > > const&) (1x)
   30 ( 0.00%)          return (std::min)(__diffmax, __allocmax);
   14 ( 0.00%)  => /usr/include/c++/11/bits/stl_algobase.h:unsigned long const& std::min<unsigned long>(unsigned long const&, unsigned long const&) (1x)
   25 ( 0.00%)        }
    .           
    .                 // Internal erase functions follow.
    .           
    .                 // Called by erase(q1,q2), clear(), resize(), _M_fill_assign,
    .                 // _M_assign_aux.
    .                 void
    .                 _M_erase_at_end(pointer __pos) _GLIBCXX_NOEXCEPT
    .                 {
-- line 1793 ----------------------------------------

--------------------------------------------------------------------------------
The following files chosen for auto-annotation could not be found:
--------------------------------------------------------------------------------
  ./elf/../bits/stdlib-bsearch.h
  ./elf/../elf/dl-sysdep.c
  ./elf/../elf/dl-tls.c
  ./elf/../sysdeps/generic/dl-protected.h
  ./elf/../sysdeps/generic/ldsodefs.h
  ./elf/../sysdeps/nptl/dl-tls_init_tp.c
  ./elf/../sysdeps/x86/dl-cacheinfo.h
  ./elf/../sysdeps/x86/dl-prop.h
  ./elf/../sysdeps/x86_64/dl-machine.h
  ./elf/../sysdeps/x86_64/dl-trampoline.h
  ./elf/./dl-find_object.h
  ./elf/./dl-map-segments.h
  ./elf/./elf/dl-cache.c
  ./elf/./elf/dl-deps.c
  ./elf/./elf/dl-environ.c
  ./elf/./elf/dl-error-skeleton.c
  ./elf/./elf/dl-find_object.c
  ./elf/./elf/dl-fini.c
  ./elf/./elf/dl-hwcaps.c
  ./elf/./elf/dl-hwcaps_split.c
  ./elf/./elf/dl-init.c
  ./elf/./elf/dl-load.c
  ./elf/./elf/dl-lookup-direct.c
  ./elf/./elf/dl-lookup.c
  ./elf/./elf/dl-minimal-malloc.c
  ./elf/./elf/dl-minimal.c
  ./elf/./elf/dl-misc.c
  ./elf/./elf/dl-object.c
  ./elf/./elf/dl-profstub.c
  ./elf/./elf/dl-reloc.c
  ./elf/./elf/dl-runtime.c
  ./elf/./elf/dl-sort-maps.c
  ./elf/./elf/dl-tunables.c
  ./elf/./elf/dl-tunables.h
  ./elf/./elf/dl-version.c
  ./elf/./elf/do-rel.h
  ./elf/./elf/get-dynamic-info.h
  ./elf/./elf/rtld.c
  ./elf/./get-dynamic-info.h
  ./iconv/./iconv/gconv_simple.c
  ./io/../sysdeps/unix/sysv/linux/open64_nocancel.c
  ./libio/./libio/fileops.c
  ./libio/./libio/genops.c
  ./libio/./libio/iofflush.c
  ./libio/./libio/iofwrite.c
  ./libio/./libio/libioP.h
  ./libio/./libio/putc.c
  ./malloc/./malloc/malloc.c
  ./setjmp/../sysdeps/x86_64/setjmp.S
  ./stdlib/./stdlib/cxa_atexit.c
  ./stdlib/./stdlib/cxa_finalize.c
  ./string/../sysdeps/x86_64/multiarch/../strchr.S
  ./string/../sysdeps/x86_64/multiarch/memcmp-sse4.S
  ./string/../sysdeps/x86_64/multiarch/memmove-vec-unaligned-erms.S
  ./string/../sysdeps/x86_64/multiarch/memset-vec-unaligned-erms.S
  ./string/../sysdeps/x86_64/multiarch/strlen-vec.S
  ./string/../sysdeps/x86_64/strcmp.S
  ./wcsmbs/./wcsmbs/btowc.c
  ./wcsmbs/./wcsmbs/wctob.c
  ./wcsmbs/./wcsmbsload.h
  ./wctype/./wctype/wctype_l.c

--------------------------------------------------------------------------------
Ir              
--------------------------------------------------------------------------------
18,639 ( 0.79%)  events annotated
*/