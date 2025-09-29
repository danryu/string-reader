project(
    'string-reader',
    'cpp',
    version: '1.0.0',
    default_options: ['warning_level=3', 'werror=false', 'cpp_std=c++23'],
    meson_version: '>=1.1',
)
add_project_arguments('-Wfatal-errors', language: 'cpp')
add_project_arguments('-Wno-missing-field-initializers', language: 'cpp')

executable(
    'example',
    files(
        'src/main.cpp',
    ),
)
