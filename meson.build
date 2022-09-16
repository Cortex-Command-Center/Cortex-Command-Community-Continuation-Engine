project(
  'C4', ['cpp', 'c'],
  version : 'rel-1',
  default_options : ['cpp_std=c++17', 'buildtype=release'],
  meson_version : '>=0.53'
)

# Build Environment Setup
deps=[]
if host_machine.system() in ['linux', 'osx']
  deps = [
    dependency('allegro'),
    dependency('loadpng'),
    dependency('flac'),
    dependency('minizip'),
    dependency('luajit'),
    #dependency('lua52', required : false),
    dependency('threads'),
    dependency('liblz4'),
    dependency('libpng'),
    dependency('boost'), #needed for luabind
  ]
  # Add a safety net on weird linux distros that store lua in a different way
  luadep = dependency('lua52', required : false)
  if not luadep.found()
    luadep = dependency('lua5.2')
  endif
  deps += luadep

  if host_machine.system() == 'linux'
    deps += dependency('x11')
  endif
endif

elfname = 'CortexCommand'
compiler = meson.get_compiler('cpp')
build_rpath = ''
link_args = []
extra_args = []
preprocessor_flags = []
suffix = ''

# Used for GCC compatible compilers
if compiler.get_argument_syntax() == 'gcc'
  # Build against system libraries on Linux
  message('GCC detected')

  # Set RUNPATH so that C4 can find libfmod.so without needing to set LD_LIBRARY_PATH
  build_rpath = '$ORIGIN:$ORIGIN/../external/lib/linux/x86_64'

  # Set preprocessor flags and cpp arguments according to build options
  buildtype_debug = get_option('debug')
  if buildtype_debug
    # Add '_debug' suffix for debug builds
    elfname += '_debug'
    # Disable #pragma region complaints
    extra_args = ['-Wno-unknown-pragmas']

    debug_type = get_option('debug_type')
    if debug_type == 'release'
      # Enable minimal debug features
      preprocessor_flags += ['-DDEBUG_RELEASE_BUILD']
    elif debug_type == 'minimal'
      # Enable some debug features
      preprocessor_flags += ['-DDEBUGMODE']
    elif debug_type == 'full'
      # Enable all debug features (may slow down game)
      preprocessor_flags += ['-DDEBUG_BUILD', '-DDEBUGMODE']
    endif
  else
    # Disable all warnings for Release builds
    extra_args = ['-w']
    # Disable all debug features
    preprocessor_flags += ['-DRELEASE_BUILD']
  endif

  if compiler.get_id() == 'gcc' and compiler.version().version_compare('<9')
    # Link stdc++fs if GCC version < 9
    link_args += ['-lstdc++fs']
  endif
# Used for MSVC compatible compilers
elif compiler.get_argument_syntax() == 'msvc'
  # TODO - add MSVC related arguments and stuff in here
  message('CL detected')

  elfname = 'Cortex Command'
  extra_args += [
    '-permissive-',
    '-D_HAS_ITERATOR_DEBUGGING=0',
    '-D_HAS_AUTO_PTR_ETC=1'
  ]
  add_project_link_arguments([
      'winmm.lib',
      'ws2_32.lib',
      'dinput8.lib',
      'ddraw.lib',
      'dxguid.lib',
      'dsound.lib'
    ],
    language:'cpp'
  )

  if host_machine.cpu_family() == 'x64'
    elfname += ' x64'
  endif

  preprocessor_flags += [
    '-D_CRT_SECURE_NO_DEPRECATE',
    '-D_WINDOWS',
    '-DWIN32',
    '-DWIN32_LEAN_AND_MEAN'
  ]
  link_args += ['-ignore:4099', '-ignore:4217']

  buildtype_debug = get_option('debug')
  if buildtype_debug
    elfname += '.debug'
    debug_type = get_option('debug_type')
    if debug_type == 'release'
      # Enable minimal debug features
      preprocessor_flags += ['-DDEBUG_RELEASE_BUILD']
    elif debug_type == 'minimal'
      elfname += '.minimal'
      # Enable some debug features
      preprocessor_flags += ['-DDEBUGMODE']
    elif debug_type == 'full'
      elfname += '.full'
      # Enable all debug features (may slow down game)
      preprocessor_flags += ['-DDEBUG_BUILD', '-DDEBUGMODE']
    endif
  else
    preprocessor_flags += ['-DRELEASE_BUILD', '-DNDEBUG']
  endif
else
  error('Using unknown compiler, please use a GCC or MSVC compatible compiler')
endif

# Configuration
conf_data = configuration_data()
prefix = get_option('prefix')

conf_data.set_quoted(
  'BASEDATAPATH',
  prefix/get_option('data_install_dir')
#  strip_directory : true
)

if suffix == ''
  suffix = []
  conf_data.set('EXENAME', elfname)
else
  conf_data.set('EXENAME', elfname + '.' + suffix)
endif

if get_option('install_runner')
  conf_data.set('EXERUNNER', 'CortexCommand')
  conf_data.set('EXEPATH', prefix/get_option('libdir')/'CortexCommand')
else
  conf_data.set('EXERUNNER', conf_data.get('EXENAME'))
  conf_data.set('EXEPATH', prefix/get_option('bindir'))
endif

# Sources Setup
pch = 'System/StandardIncludes.h'
sources = []
source_inc_dirs = include_directories(
  'Activities',
  'Entities',
  'GUI',
  'Lua',
  'Managers',
  'Menus',
  'Resources',
  'System'
)

subdir('Activities')
subdir('Entities')
subdir('GUI')
subdir('Lua')
subdir('Managers')
subdir('Menus')
subdir('System')
subdir('Resources')

# External Libraries
external_objects = []
external_libs = []
subdir('external')

install_rpath = prefix/get_option('fmod_dir')

# Target Definitions
c4elf = executable(
  # Source options
  elfname, ['Main.cpp', sources],
  include_directories : [
    source_inc_dirs,
    external_inc_dirs
  ],
  cpp_pch : pch,

  # Link options
  link_with : external_libs,
  objects : [external_objects],
  dependencies : deps,

  # Compiler setup
  cpp_args : [extra_args, preprocessor_flags],
  link_args : link_args,
  build_rpath : build_rpath,

  # Executable name options
  name_suffix : suffix,

  # Meson options
  build_by_default : true,
  gui_app : true,

  # Install options
  install : true,
  install_rpath : install_rpath,
  install_dir : get_option('install_runner') ?
  get_option('libdir')/'CortexCommand' : get_option('bindir')
)

# Installing
base_exclude_files = [
  'Base.rte/Settings.ini',
  'Launch Actor Editor.bat',
  'Launch Area Editor.bat',
  'Launch Assembly Editor.bat',
  'Launch Gib Editor.bat',
  'Launch Scene Editor.bat',
  'LogConsole.txt',
  'LogLoading.txt',
  'LogLoadingWarning.txt',
  'Start Dedicated Server.bat'
]

if get_option('install_data')
  install_subdir(
    get_option('c4_data_dir'),
    exclude_directories : [
      '.git', '.github', 'Metagames.rte', 'Scenes.rte'
    ],
    exclude_files : base_exclude_files,
    install_dir : get_option('data_install_dir'),
    strip_directory : true
  )
endif
