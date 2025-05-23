import 'dart:ffi';
import 'dart:io';

import 'package:ffi/ffi.dart';

import 'flutter_playground_cpp_bindings_generated.dart';

const String _libName = 'flutter_playground_cpp';

/// The dynamic library in which the symbols for [FlutterPlaygroundCppBindings] can be found.
final DynamicLibrary _dylib = () {
  if (Platform.isMacOS || Platform.isIOS) {
    return DynamicLibrary.open('$_libName.framework/$_libName');
  }
  if (Platform.isAndroid || Platform.isLinux) {
    return DynamicLibrary.open('/path/to/so/libflutter_playground_cpp.so');
  }
  if (Platform.isWindows) {
    return DynamicLibrary.open('$_libName.dll');
  }
  throw UnsupportedError('Unknown platform: ${Platform.operatingSystem}');
}();

String callSendMessage(String username, String message, String encodedImage) {
  final bindings = FlutterPlaygroundCppBindings(_dylib);

  final usernamePtr = username.toNativeUtf8().cast<Char>();
  final messagePtr = message.toNativeUtf8().cast<Char>();
  final imagePtr = encodedImage.toNativeUtf8().cast<Char>();

  final resultPtr = bindings
      .send_message(
        usernamePtr,
        messagePtr,
        imagePtr,
      )
      .cast<Utf8>();
  final result = resultPtr.toDartString();

  return result;
}

String callGetMessages() {
  final bindings = FlutterPlaygroundCppBindings(_dylib);

  final resultPtr = bindings.get_messages().cast<Utf8>();
  final result = resultPtr.toDartString();

  return result;
}

int main() {
  final result = callSendMessage("Henk", "Heellangbericht", "-1");
  print(result);
  return 0;
}
