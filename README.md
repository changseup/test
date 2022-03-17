# test
+-----------------------------------------------------------+
|															|
|			   WebRTC build instructions					|
|															|
+-----------------------------------------------------------+
-------------------------------------------------------------
version	| Name				| Date			|Description
-------------------------------------------------------------
0.0.1	| changseup kim		| 2022-03-17	|Trial version
-------------------------------------------------------------
+-----------------------------------------------------------+


ref.
* WebRTC (Native code) : https://webrtc.github.io/webrtc-org/native-code/
* Development: https://webrtc.github.io/webrtc-org/native-code/development/


Before You Start
First, be sure to install the prerequisite software.
description: https://webrtc.github.io/webrtc-org/native-code/development/prerequisite-sw/


1. Generation Ninja project files
  A. android_arm64_ssl_rel
    $ gn gen out/android_arm64_ssl_rel --args='target_os="android" target_cpu="arm64" rtc_use_dummy_audio_file_devices=true rtc_include_tests=false rtc_build_examples=false rtc_libvpx_build_vp9=false use_glib=false rtc_use_x11=false is_debug=false use_custom_libcxx=false is_component_build=false rtc_enable_protobuf=false rtc_build_ssl=false rtc_ssl_root="{include absolute path of openssl}" '

    e.g.,
      rtc_ssl_root="/home/cs/workspace/openssl/libs/android/openssl-1.1.1g_no_threads/arm64-v8a/include"
  B. android_arm_ssl_rel
    $ gn gen out/android_arm_ssl_rel --args='target_os="android" target_cpu="arm" rtc_use_dummy_audio_file_devices=true rtc_include_tests=false rtc_build_examples=false rtc_libvpx_build_vp9=false use_glib=false rtc_use_x11=false is_debug=false use_custom_libcxx=false is_component_build=false rtc_enable_protobuf=false rtc_build_ssl=false rtc_ssl_root="{include absolute path of openssl}" '
  C. describe target_cpu for android 
    - To build for ARM64: use target_cpu="arm64"
	- To build for 32-bit x86: use target_cpu="x86"
	- To build for 64-bit x64: use target_cpu="x64"

2. To use openssl library (remove boringssl)
  A. copy file and directory to Ninja project files (e.g., out/android_arm64_ssl_rel)
	remove_boringssl.sh
	./shellscript
  B. run script file 
	e.g., out/android_arm64_ssl_rel$ bash remove_boringssl.sh
  C. delete manually : search for boringssl 
	e.g., out/android_arm64_ssl_rel$ grep -wrn boringssl
	build.ninja
	toolchcain.ninja 
	obj/webrtc.ninja

3. Compiling
  e.g., 
  src$ ninja -C out/android_arm64_ssl_rel
  


enjoy!!
