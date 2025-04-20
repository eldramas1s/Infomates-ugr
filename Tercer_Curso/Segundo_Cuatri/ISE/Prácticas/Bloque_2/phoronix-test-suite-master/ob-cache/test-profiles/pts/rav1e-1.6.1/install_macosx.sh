#!/bin/sh

7z x Bosphorus_1920x1080_120fps_420_8bit_YUV_Y4M.7z -aoa
unzip -o rav1e-0.5.0-macos.zip
mv rav1e rav1e-mac
chmod +x rav1e-mac

echo "#!/bin/sh
./rav1e-mac Bosphorus_1920x1080_120fps_420_8bit_YUV.y4m --threads \$NUM_CPU_CORES --tiles 8 --output NULL.ivf \$@ > log.out 2>&1
rm -f output
rm -f NULL.ivf
tr -s '\r' '\n' < log.out > \$LOG_FILE" > rav1e
chmod +x rav1e
