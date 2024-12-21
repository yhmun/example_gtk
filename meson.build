project('example_gtk', 'cpp',
            license: 'MIT',
            version: '0.10.0',
      meson_version: '>= 0.63.0',
    default_options: [
            'warning_level=3',
            'cpp_std=c++20'
        ]
)

cxx = meson.get_compiler('cpp')
proj_args = cxx.get_supported_arguments(
    '-Wno-unused-parameter',
)
add_project_arguments(proj_args, language: 'cpp')

config_h = configuration_data()
configure_file(output: 'config.h', configuration: config_h)

gtk_dep = dependency('gtk+-3.0')

apps = [
    {
           'name': 'simple',
        'sources': ['simple.cpp'],
    },
    {
           'name': 'button',
        'sources': ['button.cpp'],
    },
    {
           'name': 'grid',
        'sources': ['grid.cpp'],
    },
    {
           'name': 'draw',
        'sources': ['draw.cpp'],
    },
]

foreach app : apps
    executable(app.get('name'),
                 sources: app.get('sources'),
                cpp_args: [],
     include_directories: [],
               link_with: [],
            dependencies: [gtk_dep],
        override_options: ['cpp_std=c++20'],
             install_dir: 'bin' / 'sys',
                  install: true
    )
endforeach
