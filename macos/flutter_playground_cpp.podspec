#
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html.
# Run `pod lib lint flutter_playground_cpp.podspec` to validate before publishing.
#
Pod::Spec.new do |s|
  s.name             = 'flutter_playground_cpp'
  s.version          = '0.0.1'
  s.summary          = 'Flutter playground CPP demo'
  s.description      = <<-DESC
Flutter playground CPP demo
                       DESC
  s.homepage         = 'http://example.com'
  s.license          = { :file => '../LICENSE' }
  s.author           = { 'Your Company' => 'email@example.com' }

  # This will ensure the source files in Classes/ are included in the native
  # builds of apps using this FFI plugin. Podspec does not support relative
  # paths, so Classes contains a forwarder C file that relatively imports
  # `../src/*` so that the C sources can be shared among all target platforms.
  s.source           = { :path => '.' }
  s.source_files = 'Classes/**/*.{h,mm,cpp}'
  s.dependency 'FlutterMacOS'

  s.platform = :osx, '10.11'
  s.pod_target_xcconfig = { 'DEFINES_MODULE' => 'YES',
   'CLANG_CXX_LANGUAGE_STANDARD' => 'c++20',
   'CLANG_CXX_LIBRARY' => 'libc++',
 'HEADER_SEARCH_PATHS' => '/usr/local/opt/openssl@3/include',
    'LIBRARY_SEARCH_PATHS' => '/usr/local/opt/openssl@3/lib',
  'OTHER_LDFLAGS' => '-lssl -lcrypto'
  }
  s.swift_version = '5.0'

end
