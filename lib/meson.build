biguint_lib = shared_library(
        'curiositas_biguint',
        'container/BitVector.cpp',
        'math/BigUInt.cpp',
        'math/SieveEratosthenes.cpp',
        include_directories: biguint_includes,
        install: true,
)

container_tests_exe = executable(
        'container_tests',
        'container/Tests.cpp',
        'container/BitVector.Tests.cpp',
        dependencies: [catch2],
        link_with: [biguint_lib],
        include_directories: [biguint_includes],
)
test('container_tests', container_tests_exe)

math_tests_exe = executable(
        'math_tests',
        'math/Tests.cpp',
        'math/BigUInt.Benchmarks.cpp',
        'math/BigUInt.Tests.cpp',
        'math/SieveEratosthenes.Tests.cpp',
        dependencies: [catch2],
        link_with: [biguint_lib],
        include_directories: [biguint_includes],
)
test('math_tests', math_tests_exe,
     args: ['[test]'])
