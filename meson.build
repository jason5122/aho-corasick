project('aho-corasick', 'cpp',
  version: '0.1.0',
  license: 'MIT',
  default_options: ['cpp_std=c++20']
)

# This is required for std::format library.
add_project_arguments('-fexperimental-library', language: 'cpp')

executable('aho_corasick', 'ac.cc', 'ac_fast.cc', 'ac_slow.cc', 'tests/test_runner.cc', 'tests/test_main.cc')
