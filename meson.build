project('aho-corasick', 'cpp',
  version: '0.1.0',
  license: 'MIT',
  default_options: ['cpp_std=c++20']
)

# This is required for std::format library.
add_project_arguments('-fexperimental-library', language: 'cpp')

# TODO: Ensure all conversions are correct. Not doing so will result in subtle, hard-to-detect
#       errors (an hour has already been spent debugging one of those).
add_project_arguments('-Wconversion', language: 'cpp')

executable('aho_corasick', 'main.cc', 'src/ac.cc', 'src/ac_fast.cc', 'src/ac_slow.cc', 'test/test_runner.cc')
