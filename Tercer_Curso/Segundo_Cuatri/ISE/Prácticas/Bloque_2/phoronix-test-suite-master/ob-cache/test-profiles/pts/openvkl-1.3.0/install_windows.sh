#!/bin/sh
# Windows OVKL upstream appears borked for their builds and no benchmarks
unzip -o openvkl-1.3.1.x86_64.windows.zip
echo "#!/bin/sh
cd openvkl-1.3.1.x86_64.windows/bin/
LD_LIBRARY_PATH=../lib:\$LD_LIBRARY_PATH ./\$@ > \$LOG_FILE 2>&1" > openvkl
chmod +x openvkl
