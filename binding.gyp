{
  'targets': [
    {
      'target_name': 'napi-xinput',
      'sources': ['src/napi-xinput.cc'],
      'include_dirs': ['<!@(node -p "require(\'node-addon-api\').include")'],
      'dependencies': ['<!(node -p "require(\'node-addon-api\').gyp")'],
      'cflags!': ['-fno-exceptions'],
      'cflags_cc!': ['-fno-exceptions'],
      'msvs_settings': {
        'VCCLCompilerTool': {'ExceptionHandling': 1},
      },
    }
  ]
}
