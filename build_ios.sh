#!/bin/bash

# Basing on https://raw.github.com/st3fan/ios-openssl/master/build.sh - thanks!

set -x
set -e



# Setup paths to stuff we need

DEVELOPER="/Applications/Xcode.app/Contents/Developer"

SDK_VERSION="7.0"
MIN_VERSION="4.3"

IPHONEOS_PLATFORM="${DEVELOPER}/Platforms/iPhoneOS.platform"
IPHONEOS_SDK="${IPHONEOS_PLATFORM}/Developer/SDKs/iPhoneOS${SDK_VERSION}.sdk"
IPHONEOS_GCC="/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang"

IPHONESIMULATOR_PLATFORM="${DEVELOPER}/Platforms/iPhoneSimulator.platform"
IPHONESIMULATOR_SDK="${IPHONESIMULATOR_PLATFORM}/Developer/SDKs/iPhoneSimulator${SDK_VERSION}.sdk"
IPHONESIMULATOR_GCC="/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang"

# Make sure things actually exist

if [ ! -d "$IPHONEOS_PLATFORM" ]; then
  echo "Cannot find $IPHONEOS_PLATFORM"
  exit 1
fi

if [ ! -d "$IPHONEOS_SDK" ]; then
  echo "Cannot find $IPHONEOS_SDK"
  exit 1
fi

if [ ! -x "$IPHONEOS_GCC" ]; then
  echo "Cannot find $IPHONEOS_GCC"
  exit 1
fi

if [ ! -d "$IPHONESIMULATOR_PLATFORM" ]; then
  echo "Cannot find $IPHONESIMULATOR_PLATFORM"
  exit 1
fi

if [ ! -d "$IPHONESIMULATOR_SDK" ]; then
  echo "Cannot find $IPHONESIMULATOR_SDK"
  exit 1
fi

if [ ! -x "$IPHONESIMULATOR_GCC" ]; then
  echo "Cannot find $IPHONESIMULATOR_GCC"
  exit 1
fi

# Clean up whatever was left from our previous build

buildCrypt()
{
	export ARCH=$1
	export CC="$2 -miphoneos-version-min=${MIN_VERSION}"
	export SDK=$3
	export CFLAGS="-arch ${ARCH} -isysroot ${SDK} $4"
	export LDFLAGS="-arch ${ARCH}"
	
	make -j5 library	
}


#buildCrypt "armv7" "${IPHONEOS_GCC}" "${IPHONEOS_SDK}" ""
#buildCrypt "armv7s" "${IPHONEOS_GCC}" "${IPHONEOS_SDK}" ""
#buildCrypt "arm64" "${IPHONEOS_GCC}" "${IPHONEOS_SDK}" ""
#buildCrypt "i386" "${IPHONESIMULATOR_GCC}" "${IPHONESIMULATOR_SDK}" ""
#buildCrypt "x86_64 -arch i386" "${IPHONESIMULATOR_GCC}" "${IPHONESIMULATOR_SDK}" ""
buildCrypt "armv7 -arch armv7s -arch arm64" "${IPHONEOS_GCC}" "${IPHONEOS_SDK}" ""

# Aggregate library and include files