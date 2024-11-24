project('aho-corasick', 'cpp',
  version: '0.1.0',
  license: 'MIT',
  default_options: ['cpp_std=c++20']
)

# This is required for std::format library.
add_project_arguments('-fexperimental-library', '-Wconversion', language: 'cpp')

executable('aho_corasick', 'main.cc', 'src/ac.cc', 'src/ac_fast.cc', 'src/ac_slow.cc', 'test/test_runner.cc')
executable('aho_corasick_alt', 'main.cc', 'src-alt/ac.cc', 'src-alt/ac_fast.cc', 'src-alt/ac_slow.cc', 'test/test_runner.cc')
