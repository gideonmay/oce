#! /bin/sh
set -e

mkdir -p build
cd build


#  Default values
: "${OCE_USE_PCH=OFF}"
: "${OCE_COPY_HEADERS_BUILD=OFF}"
: "${OCE_MULTITHREAD_LIBRARY=NONE}"

echo "Timestamp" && date
cmake -DOCE_ENABLE_DEB_FLAG:BOOL=OFF \
      -DCMAKE_BUILD_TYPE:STRING=Release \
      -DOCE_USE_TCL_TEST_FRAMEWORK:BOOL=ON \
      -DOCE_TESTING:BOOL=ON \
      -DOCE_DRAW:BOOL=ON \
      -DOCE_VISUALISATION:BOOL=ON \
      -DOCE_OCAF:BOOL=ON \
      -DOCE_OSX_USE_COCOA:BOOL=OFF \
      -DOCE_DISABLE_X11:BOOL=ON \
      -DOCE_DATAEXCHANGE:BOOL=ON \
      -DOCE_USE_PCH:BOOL="${OCE_USE_PCH}" \
      -DOCE_COPY_HEADERS_BUILD:BOOL="${OCE_COPY_HEADERS_BUILD}" \
      -DOCE_WITH_GL2PS:BOOL=ON \
      -DOCE_WITH_FREEIMAGE:BOOL=ON \
      -DOCE_MULTITHREAD_LIBRARY:STRING="${OCE_MULTITHREAD_LIBRARY}" \
      ..
echo ""
echo "Timestamp" && date
if test "$RUN_TESTS" = true; then
    make -j8 | grep Built

    # Run OCE tests
    echo "Timestamp" && date
    make test

    # Run OCCT tests, but overwrite DrawLaunchTests.draw to write
    # an XML summary file at a specified location
    cat > DrawLaunchTests.draw <<EOT
testgrid -outdir occt -xml summary.xml -refresh 300
exit
EOT

    echo "Timestamp" && date
    cmake -P DrawLaunchTests.cmake || true
else
    make -j8
fi

echo "Timestamp" && date
